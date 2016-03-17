// 
// Copyright (c) 2010, Benjamin Kaufmann
// 
// This file is part of Clasp. See http://www.cs.uni-potsdam.de/clasp/ 
// 
// Clasp is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Clasp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Clasp; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
#ifndef DISABLE_MULTI_THREADING
#include <clasp/parallel_solve.h>
#include <clasp/solver.h>
#include <clasp/clause.h>
#include <clasp/shared_clause.h>
#include <clasp/clasp_facade.h>
#include <clasp/util/thread.h>
#include <clasp/util/timer.h>
#include <clasp/minimize_constraint.h>
#include <tbb/compat/condition_variable>
#include <tbb/concurrent_queue.h>

namespace Clasp { 
/////////////////////////////////////////////////////////////////////////////////////////
// Semaphore
/////////////////////////////////////////////////////////////////////////////////////////
class Semaphore {
public:
	explicit Semaphore(int counter = 0) : counter_(counter) {}
	// Sets the internal counter to c.
	// PRE: no thread is blocked on the semaphore
	//      (i.e. internal counter is >= 0)
	// NOTE: not thread-safe
	void unsafe_reset(int c = 0) {
		assert(counter_ >= 0);
		counter_ = c;
	}

	// Decrement the semaphore's counter.
	// If the counter is zero or less prior to the call
	// the calling thread is suspended.
	void down() {
		std::unique_lock<tbb::mutex> lock(semMutex_);
		if (--counter_ < 0) semCond_.wait(lock);
	}
	// EFFECT: atomically
	//  if ( (counter-1) > minC ) 
	//    down(), return true;
	//   return false;
	bool try_down(int val = -1) {
		std::unique_lock<tbb::mutex> lock(semMutex_);
		if ((counter_-1) > val) {
			if (--counter_ < 0) semCond_.wait(lock);
			return true;
		}
		return false;
	}
	
	// Increments the semaphore's counter
	// and resumes one thread which has called down() 
	// if the counter was less than zero prior to the call.
	void up() {
		bool notify;
		{
			std::unique_lock<tbb::mutex> lock(semMutex_);
			notify = (++counter_ <= 0);
		}
		if (notify) semCond_.notify_one();
	}
	
	// Resumes currently blocked threads
	// EFFECT: atomically executes
	//   while (counter < 0) up();
	void unblockAll() {
		std::unique_lock<tbb::mutex> lock(semMutex_);
		if (counter_ < 0) {
			counter_ = 0;
			semCond_.notify_all();
		}
	}
private:
	Semaphore(const Semaphore&);
	Semaphore& operator=(const Semaphore&);
	typedef std::condition_variable cv;
	cv         semCond_;  // waiting threads
	tbb::mutex semMutex_; // mutex for updating counter
	int        counter_;  // semaphore's counter
};
/////////////////////////////////////////////////////////////////////////////////////////
// ParallelSolve::Impl
/////////////////////////////////////////////////////////////////////////////////////////
struct ParallelSolve::SharedData {
	typedef tbb::concurrent_queue<const LitVec*> queue;
	SharedData() { reset(); }
	void reset() {
		workSem.unsafe_reset();
		workQ.clear();
	}
	tbb::mutex        modelM;      // model-mutex 
	Semaphore         workSem;     // work-semaphore
	queue             workQ;       // work-queue
};

/////////////////////////////////////////////////////////////////////////////////////////
// Thread-state & message queue
/////////////////////////////////////////////////////////////////////////////////////////
// Thhread-local MessageQueue for storing some of the messages of Message_t
struct MessageQueue {
	enum MType { update_message = 0, message_types = 1 };
	MessageQueue() { reset(); }
	uint32 top()         const    { return time; }
	uint32 top(MType m)  const    { return queue[m]; }
	void   pop(uint32 t)          { time = t; }
	void   pop(MType m, uint32 t) { queue[m] = t; }
	void   reset()                {
		restart = UINT64_MAX;
		pop(0);
		for (int i = 0; i != message_types; ++i) { pop(MType(i), 0); }
	}
	uint64 restart;
	uint32 time;
	uint32 queue[message_types];
};

struct ParallelSolve::ThreadInfo {
	ThreadInfo() : thread(0), handler(0) {}
	~ThreadInfo() { delete handler; delete thread; }
	std::thread*     thread; // or 0 for master
	ParallelHandler* handler;
	MessageQueue     msg;
	SolveStats       aggStats;
};

/////////////////////////////////////////////////////////////////////////////////////////
// ParallelSolve
/////////////////////////////////////////////////////////////////////////////////////////
ParallelSolve::ThreadControlFlags::ThreadControlFlags() {
	reset();
}
void ParallelSolve::ThreadControlFlags::reset() {
	workReq    = 0;
	restartReq = 0;
	control    = 0;
	messages   = 0;
	updates    = 0;
}

// sets flag flag if not yet set
// return: true if flag was set, false if flag is already set
bool ParallelSolve::ThreadControlFlags::setFlag(Flag flag) {
	for (uint32 x = control, y = flag; (x & y) == 0;) {
		if (control.compare_and_swap(x|y, x) == x) {
			return true;
		}
		x = control;
	}
	return false;
}

ParallelSolve::ParallelSolve()
	: SolveAlgorithm()
	, shared_(new SharedData)
	, thread_(0)
	, globalR_(0,0.0,0)
	, maxRestarts_(0)
	, numThreads_(1)
	, nextId_(1)
	, intGrace_(1024)
	, intFlags_(ClauseCreator::clause_not_root_sat | ClauseCreator::clause_no_add)
	, intHeuristic_(false)
	, forceGP_(true) {
}

ParallelSolve::~ParallelSolve() {
	delete shared_;
	releaseThreads();
}

uint32 ParallelSolve::hardwareThreads() {
	return std::thread::hardware_concurrency();
}

void ParallelSolve::releaseThreads() {
	if (thread_) {
		for (int i = 0; i != numThreads_; ++i) {
			delete thread_[i];
		}
		delete [] thread_;
		thread_ = 0;
	}
}

void ParallelSolve::initThreads() {
	releaseThreads();
	thread_ = new ThreadInfo*[numThreads_];
	for (int i = 0; i != numThreads_; ++i) {
		thread_[i] = new ThreadInfo();
	}
}

void ParallelSolve::setForceGP(bool gp) {
	forceGP_ = gp;
}

void ParallelSolve::setIntegrate(uint32 grace, uint8 filter) {
	typedef ThreadOptions::Distribution Dist;
	intGrace_     = grace;
	intFlags_     = ClauseCreator::clause_not_root_sat | ClauseCreator::clause_no_add;
	intHeuristic_ = filter == Dist::filter_heuristic;
	if (filter == Dist::filter_sat) {
		intFlags_ |= (ClauseCreator::clause_not_root_sat | ClauseCreator::clause_not_sat);
	}
	else if (filter == Dist::filter_gp) {
		intFlags_ |= ClauseCreator::clause_not_root_sat;
	}
}

void ParallelSolve::setRestarts(uint32 maxR, const ScheduleStrategy& rs) {
	maxRestarts_ = maxR;
	globalR_     = rs;
}

// prepare parallel solving
SharedContext* ParallelSolve::init(int numT, SharedContext& ctx) {
	assert(numT >= 1 && "Illegal number of threads");
	shared_->reset();
	exception_  = 0;
	initialPath_= 0;
	numThreads_ = static_cast<uint32>(numT);
	msg_.reset();
	initThreads();
	return &ctx;
}

// add new client thread
void ParallelSolve::addThread(Solver& s, SharedContext* ctx, SolveParams& p) {
	assert(thread_ && "ParallelSolve::init() not called!");
	assert(nextId_ < ParallelSolve::numThreads() && (s.id() == 0 || s.id() == nextId_));
	s.setId(nextId_++);
	initThread(s, p);
	thread_[s.id()]->thread  = new std::thread(std::bind2nd(std::mem_fun(&ParallelSolve::runThread), ThreadParams(ctx, s.id())), this);
}

// prepares s for solving by setting up its parallel handler
void ParallelSolve::initThread(Solver& s, const SolveParams& p) {
	assert(thread_ && "ParallelSolve::init() not called!");
	ParallelHandler* h           = new ParallelHandler(this, s, p);
	thread_[s.id()]->handler     = h;
	if (s.stats.jumps)    thread_[s.id()]->aggStats.enableJumpStats();
	s.stats.enableParallelStats();
	thread_[s.id()]->aggStats.enableParallelStats();
	thread_[s.id()]->msg.restart = globalR_.current();
	if (s.id() == 0) {
		h->init(s);
	}
}

void ParallelSolve::runThread(ThreadParams p) {
	ParallelHandler* h = thread_[p.second]->handler;
	SharedContext* ctx = p.first;
	if (ctx->attach(h->solver())) {
		doSolve(h->solver(), h->params(), LitVec());
		ctx->detach(h->solver());
	}
	else {
		terminateComplete(true);
		endSolve(h->solver());
	}
}

bool ParallelSolve::doSolve(Solver& s, const SolveParams& p, const LitVec& assume) {
	startSolve(s, p, assume);
	MinimizeConstraint* min = 0;
	try {
		for (PathPtr a(0); requestWork(s, a);) {
			thread_[s.id()]->aggStats.accu(s.stats);
			s.stats.reset();
			if (initPath(s, *a) && (!min || min->integrateNext(s))) {
				if (solvePath(s, p) == value_free) {
					terminateComplete(false);
					s.stats.parallel->terminated = true;
				}
				s.clearStopConflict();
			}
			if (min || enumerator()->optimizeHierarchical()) {
				// path is unsat and hierarchical optimization is active;
				// relax minimize constraint to avoid problems during simplification
				min  = enumerator()->constraint(s)->minimize();
				min->restoreOptimum();
			}
		}
	}
	catch (const std::bad_alloc&)     { terminate(); exception_ = "OUT OF MEMORY!"; }
	catch (const std::runtime_error&) { terminate(); exception_ = "RUNTIME ERROR!"; }
	catch (const std::exception&)     { terminate(); exception_ = "UNKNOWN ERROR!"; }
	return endSolve(s);
}


// called once by each solver before solving process starts
// once all solvers are ready, we initialize the work-queue
void ParallelSolve::startSolve(Solver& s, const SolveParams& p, const LitVec& assume) {
	assert(thread_ && "ParallelSolve::init() not called!");
	if (s.id() == 0) {
		// attach the master thread
		enumerator_  = s.sharedContext()->enumerator();
		initialPath_ = &assume;
		initThread(s, p);
	}
	// block on semaphore until all but one thread is waiting
	if (!shared_->workSem.try_down(-numThreads_)) {
		// all but this thread wait for work!
		assert(msg_.workReq == 0 && shared_->workQ.empty());
		initQueue();
		// wake up all blocked threads
		shared_->workSem.unblockAll();
	}
}

// called once by each solver just after solving process has stopped
bool ParallelSolve::endSolve(Solver& s) {
	assert(msg_.terminate());
	thread_[s.id()]->handler->release();
	if (!msg_.quit()) {
		s.clearAssumptions();
		if (s.hasConflict()) {
			msg_.setFlag(ThreadControlFlags::complete_flag);
		}
	}
	s.stats.parallel->cpuTime = ThreadTime::getTime();
	s.stats.accu(thread_[s.id()]->aggStats);
	// wake up any waiting threads
	shared_->workSem.unblockAll();
	// this thread is leaving
	shared_->workSem.up();
	if (s.id() == 0) {
		// join with the other solvers
		for (int i = 1; i != numThreads_; ++i) {
			thread_[i]->thread->join();
		}
		if (exception_) {
			throw std::runtime_error(exception_);
		}
		enumerator()->reportResult(msg_.complete());
	}
	return !msg_.complete();
}

// forced termination from outside
bool ParallelSolve::terminate() {
	// do not use postMessage() to avoid possible
	// deadlock because of unblockAll()!
	msg_.setFlag(ThreadControlFlags::quit_flag);
	++msg_.messages;
	return true;
}

// terminated from inside of algorithm
void ParallelSolve::terminateComplete(bool complete) {
	postMessage(Message_t::terminate_message);
	if (complete) {
		msg_.setFlag(ThreadControlFlags::complete_flag);
	}
}

// terminated because of unsat, check if there is more to do
void ParallelSolve::terminateUnsat(Solver& s, bool complete) {
	if (!msg_.terminate()) {
		if (complete && enumerator()->optimizeHierarchical() && s.popRootLevel(s.rootLevel(), false)) {
			// Problem is unsat and hierarchical optimization is active.
			// The active level is at its optimum, but lower-priority levels might
			// still be non-optimal.
			// Notify other threads to prepare for solving next priority level.
			postMessage(Message_t::unsat_message);
			assert(s.decisionLevel() == 0);
			return;
		}
		// nothing more to do - post terminate message
		terminateComplete(complete);
	}
}

// post message to all threads
void ParallelSolve::postMessage(MessageType m) {
	if (m < Message_t::not_a_control_message) {
		// control message - notify all if new
		ThreadControlFlags::Flag cf = static_cast<ThreadControlFlags::Flag>((uint32(1)<<m));
		if (msg_.setFlag(cf)) {
			++msg_.messages;
			shared_->workSem.unblockAll();
		}
	}
	else if (m == Message_t::split_message) {
		++msg_.workReq;
		++msg_.messages;
	}
	else if (m == Message_t::update_message) {
		++msg_.updates;
		++msg_.messages;
	}
	else {
		assert("ERROR: Unknown message type!\n");
	}
}

// tries to get new work for the given solver
bool ParallelSolve::requestWork(Solver& s, PathPtr& out) { 
	const LitVec* a;
	while (!msg_.terminate()) {
		// only clear path and stop conflict - we don't propagate() here
		// because we would then have to handle any eventual conflicts
		if (!s.popRootLevel(s.rootLevel(), false)) {
			// s has a real top-level conflict - 
			// there is nothing we can do to continue
			terminateComplete(true); 
		}	
		else if (shared_->workQ.try_pop(a)) {
			assert(s.decisionLevel() == 0);
			// got new work from work-queue
			bool splitted = a != initialPath_;
			out           = a;
			if (!splitted) out.release(); // do not take over ownership of initial gp!
			thread_[s.id()]->msg.restart = globalR_.current();
			thread_[s.id()]->handler->prepareForGP(*a, splitted);
			// propagate any new facts now that we have new work
			if (s.simplify()) { return true; }
			// s now has a conflict - either an artifical stop conflict
			// or a real conflict - we'll handle it in the next iteration
			// via the call to popRootLevel()
		}
		else if (msg_.restart()) {
			// a restart request is active - we are fine with
			// this but did not yet had a chance to react on it
			waitOnRestart(s);
		}
		else if (msg_.allowSplit()) {
			// gp mode is active - request a split	
			// and wait until someone has work for us
			postMessage(Message_t::split_message);
			if (!shared_->workSem.try_down(-numThreads_)) {
				// we are the last man standing, there is no
				// work left - quitting time?
				terminateUnsat(s, true);
			}
		}
		else {
			// portfolio mode is active - no splitting, no work left
			// quitting time? 
			terminateUnsat(s, true);
		}
	}
	return false;
}

// handles an active restart request
// returns true to signal that s should restart otherwise false
bool ParallelSolve::waitOnRestart(Solver& s) {
	assert(msg_.restart());
	// react once
	if (!thread_[s.id()]->handler->handleRestartMessage(s)) {
		msg_.setFlag(ThreadControlFlags::inhibit_restart_flag);
	}
	// loop because the semaphore counter may be positive
	while (shared_->workSem.try_down(-numThreads_)) {
		if (msg_.terminate()) {
			return true;
		}
		if (!msg_.restart()) {
			return msg_.allowRestart();
		}
		// request still active - continue waiting
	}
	// last man standing - complete restart request
	msg_.workReq   = 0;
	msg_.restartReq= 0;
	bool hasUnsat  = msg_.unsatRestart();
	msg_.control  -= (msg_.control & (uint32(ThreadControlFlags::unsat_flag|ThreadControlFlags::restart_flag)));
	if (!hasUnsat) {
		globalR_.next();
		if ( (maxRestarts_ -= maxRestarts_ > 0) == 0 ) {
			globalR_.init(0, 0.0, 0);
		}
	}
	if (hasUnsat || msg_.allowRestart()) {
		initQueue();
	}
	if (hasUnsat && enumerator()->optimizeHierarchical()) {
		if (enumerator()->enumerated == 0 || !enumerator()->constraint(s)->minimize()->shared_unsafe()->optimizeNext()) {
			terminateComplete(true);
		}
	}
	// wake up all blocked threads
	shared_->workSem.unblockAll();
	return msg_.terminate() || msg_.allowRestart();
}

// If guiding path scheme is active only one
// thread can start with gp (typically empty) and this
// thread must then split up search-space dynamically.
// Otherwise, all threads can start with initial gp
// TODO:
//  heuristic for initial splits?
void ParallelSolve::initQueue() {
	shared_->workQ.clear();
	int end = numThreads_;
	if (forceGP_) {
		msg_.setFlag(ThreadControlFlags::allow_gp_flag);
		end = 1;
	}
	else {
		msg_.setFlag(ThreadControlFlags::inhibit_restart_flag);
	}
	for (int i = 0; i != end; ++i) {
		shared_->workQ.push(initialPath_);
	}
}

// adds work to the work-queue
void ParallelSolve::pushWork(LitVec& work) { 
	LitVec* v = new LitVec;
	v->swap(work);
	shared_->workQ.push(v);
	shared_->workSem.up();
}

// called whenever some solver has found a model
bool ParallelSolve::backtrackFromModel(Solver& s) { 
	Enumerator::Result r;
	{
		// grab lock - models must be processed sequentially
		// in order to simplify printing and to avoid duplicates
		// in all non-trivial enumeration modes
		std::unique_lock<tbb::mutex> lock(shared_->modelM);
		// first check if the model is still valid once all
		// information is integrated into the solver
		uint32 dl = s.decisionLevel();
		if (!thread_[s.id()]->handler->isModel(s)) {
			// model no longer a (unique) model - continue search
			s.stats.removeModel(dl);
			return true;
		}
		r = enumerator()->backtrackFromModel(s);
		if (r == Enumerator::enumerate_stop_enough || (r == Enumerator::enumerate_stop_complete && s.decisionLevel() == 0)) {
			// must be called while holding the lock - otherwise
			// we have a race condition with solvers that
			// are currently blocking on the mutex and we could enumerate 
			// more model than requested by the user
			terminateComplete(s.decisionLevel() == 0);
		}
		else if (!enumerator()->trivial(thread_[s.id()]->handler->disjointPath())) {
			// enumerator is not trivial w.r.t current search scheme
			// force update of other solvers
			postMessage(Message_t::update_message);
			thread_[s.id()]->msg.pop(MessageQueue::update_message, msg_.updates);
		}
		if (enumerator()->enumerated == 1 && !enumerator()->supportsRestarts()) {
			msg_.setFlag(ThreadControlFlags::inhibit_restart_flag);
			msg_.setFlag(ThreadControlFlags::allow_gp_flag);
		}
	}
	return r == Enumerator::enumerate_continue && !msg_.terminate();
}

// updates s with new messages and uses s to create a new guiding path
// if necessary and possible
bool ParallelSolve::handleMessages(Solver& s) {
	// check if there are new messages for s
	uint32 hId      = s.id();
	uint32 gt       = msg_.messages;
	MessageQueue& m = thread_[hId]->msg;
	if (m.top() != gt) {
		ParallelHandler* h = thread_[hId]->handler;
		if (msg_.hasControlMsg()) {
			if (msg_.terminate()) {
				return h->handleTerminateMessage(s);
			}
			if (msg_.restart() && waitOnRestart(s)) {
				s.setStopConflict();
				return false;
			}
		}
		uint32 mt;
		if (m.top(MessageQueue::update_message) != (mt = msg_.updates) ) {
			m.pop(MessageQueue::update_message, mt);
			if (!h->handleModelMessage(s)) {
				return false;
			}
		}
		mt = msg_.workReq; 
		if (mt <= 0) {
			m.pop(gt);
		}
		else if (s.splittable() && h->splittable()) {
			// First declare split request as handled
			// and only then do the actual split.
			// This way, we minimize the chance for 
			// "over"-splitting, i.e. one split request handled
			// by more than one thread.
			if (--msg_.workReq == 0) {
				m.pop(gt);
			}
			h->handleSplitMessage(s);
		}
	}
	if (s.stats.conflicts >= m.restart) {
		requestRestart();
		m.restart *= 2;
	}
	return true;
}

bool ParallelSolve::validModel(Solver& s, bool forceUpdate, bool disjointPath) {
	assert(s.numFreeVars() == 0);
	uint32 hId      = s.id();
	MessageQueue& m = thread_[hId]->msg;
	uint32       mt = msg_.updates;
	if (m.top(MessageQueue::update_message) != mt) {
		m.pop(MessageQueue::update_message, mt);
		forceUpdate = true;
	}
	if (forceUpdate && !enumerator()->update(s, disjointPath)) {
		return false;
	}
	return s.numFreeVars() == 0 && !msg_.terminate();
}

void ParallelSolve::requestRestart() {
	if (msg_.allowRestart() && ++msg_.restartReq == numThreads_) {
		postMessage(Message_t::restart_message);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// ParallelHandler
/////////////////////////////////////////////////////////////////////////////////////////
ParallelHandler::ParallelHandler(ParallelSolve* ctrl, Solver& s, const SolveParams& p) 
	: solver_(&s)
	, params_(&p)
	, intTail_(0)
	, messageHandler_(ctrl)
	, updateModel_(false) {
	s.addPost(&messageHandler_);
	s.addPost(this);
}

void ParallelHandler::prepareForGP(const LitVec& out, bool fromSplit) {
	gp_.reset();
	gp_.split = fromSplit;
	solver_->stats.parallel->newGP(out.size());
}

void ParallelHandler::detach(bool onyMessageHandler) {
	// mark removed propagators by creating "self-loop"
	if (messageHandler_.next != &messageHandler_) {
		solver_->removePost(&messageHandler_);
		messageHandler_.next = &messageHandler_;
	}
	if (!onyMessageHandler && this->next != this) {
		solver_->removePost(this);
		this->next = this;
	}
		
}

void ParallelHandler::release() {
	detach(false);
	updateModel_ = false;
	while (!integrated_.empty()) {
		ClauseHead* c = (ClauseHead*)integrated_.back();
		integrated_.pop_back();
		if (c->locked(*solver_) || c->activity().score() > 0) {
			solver_->addLearnt(c, c->size());
		}
		else {
			c->destroy(solver_, true);
		}
	}
}

void ParallelHandler::attach() {
	if (messageHandler_.next == &messageHandler_) {
		messageHandler_.next = 0;
		solver_->addPost(&messageHandler_);
	}
	if (this->next == this) {
		this->next = 0;
		solver_->addPost(this);
	}
}

bool ParallelHandler::simplify(Solver& s, bool sh) {
	ClauseDB::size_type i, j, end = integrated_.size();
	for (i = j = 0; i != end; ++i) {
		Constraint* c = integrated_[i];
		if (c->simplify(s, sh)) { 
			c->destroy(&s, false); 
			intTail_ -= (i < intTail_); 
		}
		else                    { 
			integrated_[j++] = c;  
		}
	}
	shrinkVecTo(integrated_, j);
	if (intTail_ > integrated_.size()) intTail_ = integrated_.size();
	return false;
}

bool ParallelHandler::propagateFixpoint(Solver& s) {
	// Skip update of model while assumption literal is not yet assigned.
	// This is necessary during hierarchical optimization because otherwise
	// integrating a too strong optimum might irrevocably force the assumption literal
	// which would defeat its purpose.
	if (updateModel_ && s.isTrue(s.sharedContext_unsafe()->tagLiteral())) {
		if (!ctrl()->enumerator()->update(s, disjointPath())) {
			return false;
		}
		updateModel_ = false;
	}
	mt::SharedLiterals* temp[5];
	uint32 rec;
	do {
		rec = s.sharedContext()->receive(s, temp, 5);
		if (!integrateClauses(s, temp, rec)) {
			return false;
		}
		if (s.queueSize() > 0 && !s.propagateUntil(this)) {
			return false;
		}
	} while (rec == 5);
	return true;
}

bool ParallelHandler::integrateClauses(Solver& s, mt::SharedLiterals** arr, uint32 num) {
	assert(!s.hasConflict() && &s == solver_);
	ClauseCreator::Result ret(0, true);
	ClauseExtra e; e.setType(Constraint_t::learnt_other);
	uint32 intFlags = ctrl()->integrateFlags();
	for (uint32 i = 0; i != num && ret.ok; ++i) {
		ret = ClauseCreator::integrate(s, arr[i], intFlags, e);
		if (ret.local) {
			add(ret.local);
		}
	}
	return ret.ok;
}

void ParallelHandler::add(ClauseHead* h) {
	if (intTail_ < integrated_.size()) {
		ClauseHead* o = (ClauseHead*)integrated_[intTail_];
		integrated_[intTail_] = h;
		assert(o);
		if (!ctrl()->integrateUseHeuristic() || o->locked(*solver_) || o->activity().score() > 0) {
			solver_->addLearnt(o, o->size());
		}
		else {
			o->destroy(solver_, true);
		}
	}
	else {
		integrated_.push_back(h);
	}
	if (++intTail_ >= ctrl()->integrateGrace()) {
		intTail_ = 0;
	}
}

bool ParallelHandler::isModel(Solver& s) {
	assert(s.numFreeVars() == 0);
	if (ctrl()->validModel(s, updateModel_, disjointPath())) {
		updateModel_ = false;
		return true;
	}
	return false;
}

bool ParallelHandler::handleSplitMessage(Solver& s) {
	assert(&s == solver_ && solver_->decisionLevel() > solver_->rootLevel());
	s.updateGuidingPath(gp_.path, gp_.pos, gp_.impl);
	LitVec newGP(gp_.path);
	s.pushRootLevel();
	newGP.push_back(~s.decision(s.rootLevel()));
	++s.stats.parallel->splits;
	setDisjointPath(true);
	ctrl()->pushWork(newGP);
	return true;
}

bool ParallelHandler::handleModelMessage(Solver& s) {
	assert(&s == solver_); (void)s;
	updateModel_ = true;
	return true;
}

bool ParallelHandler::handleTerminateMessage(Solver& s) {
	assert(&s == solver_);
	// handle termination message once and then ignore
	// all further messages
	s.stats.parallel->terminated = true;
	detach(false);
	s.setStopConflict();
	return false;
}

bool ParallelHandler::handleRestartMessage(Clasp::Solver&) {
	// TODO
	// we may want to implement some heuristic, like
	// computing a local var order. 
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
// GlobalQueue
/////////////////////////////////////////////////////////////////////////////////////////
GlobalQueue::GlobalQueue(uint32 maxT, uint32 types, uint32 lbd) : Distributor(maxT, types, lbd), queue_(0) {
	assert(maxT < 64);
	queue_     = new Queue(maxT);
	threadId_  = new ThreadInfo[maxT];
	for (uint32 i = 0; i != maxT; ++i) {
		threadId_[i].id = queue_->addThread();
	}
}
GlobalQueue::~GlobalQueue() {
	release();
}
void GlobalQueue::release() {
	if (queue_) {
		for (uint32 i = 0; i != queue_->maxThreads(); ++i) {
			Queue::ThreadId& id = getThreadId(i);
			uint64 mask = uint64(1) << i;
			for (ClauseNode n; queue_->tryConsume(id, n); ) { 
				if ((n.targetMask & mask) != 0) {
					n.lits->release();
				}
			}
		}
		delete queue_;
		queue_ = 0;
		delete [] threadId_;
	}
}
mt::SharedLiterals* GlobalQueue::doPublish(const Solver& s, const Literal* lits, uint32 size, const ClauseExtra& extra) {
	ClauseNode n;
	n.targetMask = ((uint64(1) << queue_->maxThreads()) - 1) ^ (uint64(1) << s.id());
	n.lits       =  mt::SharedLiterals::newShareable(lits, size, extra.type(), queue_->maxThreads());
	queue_->publish(n, getThreadId(s.id()));
	return n.lits;
}
uint32 GlobalQueue::receive(const Solver& in, mt::SharedLiterals** out, uint32 maxn) {
	uint32 r = 0;
	Queue::ThreadId& id = getThreadId(in.id());
	uint64 mask = uint64(1) << in.id();
	for (ClauseNode n; r != maxn && queue_->tryConsume(id, n); ) {
		if ( (n.targetMask & mask) != 0 ) {
			out[r++] = n.lits;
		}
	}
	return r;
}
} // namespace Clasp
#endif
