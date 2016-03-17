// 
// Copyright (c) 2006-2010, Benjamin Kaufmann
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
#include <clasp/solver_types.h>
#include <clasp/solver.h>
#include <clasp/shared_clause.h>
#include <clasp/enumerator.h>
#include <clasp/util/mutex.h>
namespace Clasp {

/////////////////////////////////////////////////////////////////////////////////////////
// ImplicationList
/////////////////////////////////////////////////////////////////////////////////////////
ImplicationList::ImplicationList(const ImplicationList& other) : base_type(other) {
	copy(other.learnt());
}
ImplicationList::~ImplicationList() {
	clear(true);
}
void ImplicationList::clear(bool releaseMem) {
	base_type::clear(releaseMem);
	for (Block* x = learnt(); x; ) {
		Block* t = x;
		x = x->next;
		delete t;
	}
	setLearnt(0);
}
void ImplicationList::copy(Block* other) {
	Block* bList = 0;
	for (Block* x = other; x ; x = x->next) {
#pragma message TODO("CACHE_ALIGN")
		Block* n = new Block();
		std::memcpy(n->data, x->data, x->size * sizeof(Literal));
		n->size  = x->size;
		if (bList != 0) { bList->next = n; }
		bList = n;
	}
	setLearnt(bList);
}

ImplicationList& ImplicationList::operator=(const ImplicationList& other) {
	if (this != &other) {
		clear(true);
		base_type::operator=(other);
		copy(other.learnt());
	}
	return *this;
}

void ImplicationList::Block::add(const Literal* x, uint32 a_size) {
	std::copy(x, x+a_size, data+size);
	if (a_size == 1) {
		data[size].watch();
	}
	size += a_size;
}

void ImplicationList::addLearnt(Literal p, Literal q) {
	Literal nc[2] = {p, q};
	uint32 size   = 1 + !isSentinel(q);
	if (learnt() == 0 || (learnt()->size + size) > Block::block_cap) {
		Block* x   = new Block();
		x->add(nc, size);
		publish(x);
	}
	else {
		learnt()->add(nc, size);
	}
}

bool ImplicationList::hasLearntImplication(Literal p, Literal q) const {
	const bool binary = isSentinel(q);
	Literal r,s;
	for (Block* x = learnt(); x; x = x->next) {
		for (const Literal* it = x->data, *end = x->data+x->size; it != end; ) {
			if (it->watched()) {
				// implication from binary clause
				if (*it == p || *it == q) return true;
				++it;
			}
			else {
				// implication from ternary clause
				r = *it++;
				s = *it++;
				if (!binary && ((r == p && s == q) || (r == q && s == p))) {
					return true;
				}
			}
		}
	}
	return false;
}

Antecedent ImplicationList::getReverseReason(Solver& s, uint32 maxLev) const {
	if (empty()) return Antecedent(0);
	(void)right_end(); // prefetch
	for (SWL::const_left_iterator it = left_begin(), end = left_end(); it != end; ++it) {
		if (isRevLit(s, *it, maxLev)) {
			return Antecedent(~*it);
		}
	}
	Literal q, r;
	for (SWL::const_right_iterator it = right_begin(), end = right_end(); it != end; ++it) {
		q = it->first;
		r = it->second;
		if (isRevLit(s, q, maxLev) && isRevLit(s, r, maxLev)) {
			return Antecedent(~q, ~r);
		}
	}
	if (Block* x = learnt()) {
		// check newly learnt binary/ternary clauses
		do {
			for (const Literal* it = x->data, *end = x->data+x->size; it != end;) {
				q = *it++;
				if (isRevLit(s, q, maxLev)) {
					if (q.watched()) {
						return Antecedent(~q);
					}
					else if (isRevLit(s, r = *it++, maxLev)) {
						return Antecedent(~q, ~r);	
					}
				}
				else { it += !q.watched(); }
			}
			x = x->next;
		} while (x);
	}
	return Antecedent(0);
}

// Moved to solver.cpp  
//  - bool ImplicationList::propagate(Solver& s, Literal p) const;
// 
/////////////////////////////////////////////////////////////////////////////////////////
// ClauseHead
/////////////////////////////////////////////////////////////////////////////////////////
ClauseHead::ClauseHead(const ClauseExtra& init) {
	static_assert(sizeof(ClauseHead)<=32);
	extra_.data.type = init.type();
	extra_.data.act  = init.activity();
	extra_.data.lbd  = std::min(init.lbd(), uint32(ClauseHead::MAX_LBD));
	extra_.data.key  = !init.tagged() ? 0 : TAGGED_CLAUSE;
	head_[2]         = negLit(0);
}

void ClauseHead::attach(Solver& s) {
	assert(head_[0] != head_[1] && head_[1] != head_[2]);
	s.addWatch(~head_[0], ClauseWatch(this));
	s.addWatch(~head_[1], ClauseWatch(this));
}

void ClauseHead::detach(Solver& s) {
	s.removeWatch(~head_[0], this);
	s.removeWatch(~head_[1], this);
}

bool ClauseHead::locked(const Solver& s) const {
	return (s.isTrue(head_[0]) && s.reason(head_[0]) == this)
	  ||   (s.isTrue(head_[1]) && s.reason(head_[1]) == this);
}

bool ClauseHead::satisfied(const Solver& s) {
	return s.isTrue(head_[0]) || s.isTrue(head_[1]) || s.isTrue(head_[2]);
}

bool ClauseHead::toImplication(Solver& s) {
	ConstraintType t = ClauseHead::type();
	if (isSentinel(head_[1])) {
		assert(!tagged());
		s.addUnary(head_[0], ClauseHead::type());
		detach(s);
		return true;
	}
	if ( (t != Constraint_t::static_constraint || s.sharedContext()->unique())
		&& !tagged()
		&& (s.decisionLevel() == 0 || !ClauseHead::locked(s)) ) {
		int size = 2 + (!s.isFalse(head_[2]) || s.level(head_[2].var()) > 0);
		if (size == 2) {
			s.addBinary(head_[0], head_[1], t);
		}
		else {
			s.addTernary(head_[0], head_[1], head_[2], t);
		}
		detach(s);
		return true;
	}
	// clause can't be transformed at the moment
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Distributor
/////////////////////////////////////////////////////////////////////////////////////////
Distributor::Distributor(uint32 maxShare, uint32 typesToShare, uint32 maxLbd) : maxShare_(maxShare), lbdMax_(maxLbd), typeMask_(typesToShare) {}
Distributor::~Distributor() {}

mt::SharedLiterals* Distributor::publish(const Solver& source, const Literal* lits, uint32 size, const ClauseExtra& extra) {
	if (maxShare_ > 1 && !extra.tagged() && (size <= 3 || (extra.rootLbd() <= lbdMax_ && (extra.type() & typeMask_) != 0))) {
		return doPublish(source, lits, size, extra);
	}
	return 0;
}

void Distributor::publishShort(const Solver& s, ConstraintType t, Literal p, Literal q, Literal r) {
	if (maxShare_ > 1) {
		Literal lits[3] = {p, q, r};
		mt::SharedLiterals* shared = doPublish(s, lits, 1 + (q != negLit(0)) + (r != negLit(0)), ClauseExtra().setType(t));
		if (shared) { shared->release(); }
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// SmallClauseAlloc
/////////////////////////////////////////////////////////////////////////////////////////
SmallClauseAlloc::SmallClauseAlloc() : blocks_(0), freeList_(0) { }
SmallClauseAlloc::~SmallClauseAlloc() { 
	Block* r = blocks_;
	while (r) {
		Block* t = r;
		r = r->next;
		::operator delete(t);
	}
}

void SmallClauseAlloc::allocBlock() {
	Block* r = (Block*)::operator new(sizeof(Block));
	for (uint32 i = 0; i < Block::num_chunks-1; ++i) {
		r->chunk[i].next = &r->chunk[i+1];
	}
	r->chunk[Block::num_chunks-1].next = freeList_;
	freeList_ = r->chunk;
	r->next   = blocks_;
	blocks_   = r;
}

SatPreprocessor::~SatPreprocessor() {}
void SatPreprocessor::reportProgress(char t, uint32 min, uint32 max) {
	ctx_->enumerator()->reportPreProgress(t, *this, min, max);
}

/////////////////////////////////////////////////////////////////////////////////////////
// SharedContext
/////////////////////////////////////////////////////////////////////////////////////////
SharedContext::SharedContext() 
	: symTabPtr_(new SharedSymTab()), mutex_(new mt::Mutex()), master_(0), distributor_(0), lastInit_(0), lastTopLevel_(0), shareCount_(0), shareConstr_(false) {
	addVar(Var_t::atom_body_var);
	problem_.vars = 0;
	numBin_       = numTern_    = 0;
	learntBin_    = learntTern_ = 0;
	addEnumerator(0);
}

SharedContext::SharedContext(const SharedContext& rhs,  InitMode) 
	: mutex_(new mt::Mutex()), master_(0), distributor_(0), lastInit_(0), lastTopLevel_(0), shareCount_(0), shareConstr_(false) {
	symTabPtr_ = rhs.symTabPtr_;
	++symTabPtr_->refs;
	addVar(Var_t::atom_body_var);
	problem_.vars = 0;
	numBin_       = numTern_    = 0;
	learntBin_    = learntTern_ = 0;
	addEnumerator(0);
}

SharedContext::~SharedContext() {
	if (--symTabPtr_->refs == 0) delete symTabPtr_;
	delete mutex_;
	PodVector<SWL>::destruct(btig_);
}

void SharedContext::reset() {
	this->~SharedContext();
	new (this) SharedContext();	
}

void SharedContext::reserveVars(uint32 varGuess) {
	varInfo_.reserve(varGuess);
	btig_.reserve(varGuess*2);
}

Var SharedContext::addVar(VarType t, bool eq) {
	Var v = varInfo_.numVars();
	varInfo_.add(t == Var_t::body_var);
	if (eq) varInfo_.toggle(v, VarInfo::EQ);
	++problem_.vars;
	return v;
}

void SharedContext::requestTagLiteral() {
	if (tag_ == posLit(0)) {
		tag_ = negLit(0);
	}
}

void SharedContext::removeTagLiteral() {
	assert(master());
	if (!isSentinel(tag_)) {
		master()->force(tag_, 0);
	}
	tag_ = posLit(0);
}

void SharedContext::requestData(Var v) {
	master()->assign_.requestData(v + 1);
}

void SharedContext::setFrozen(Var v, bool b) {
	assert(validVar(v)); 
	if (b != varInfo_.isSet(v, VarInfo::FROZEN)) {
		varInfo_.toggle(v, VarInfo::FROZEN);
		b ? ++problem_.vars_frozen : --problem_.vars_frozen;
	}
}
void SharedContext::eliminate(Var v) {
	assert(validVar(v) && unique() && master()->decisionLevel() == 0); 
	if (!eliminated(v)) {
		varInfo_.toggle(v, VarInfo::ELIM);
		++problem_.vars_eliminated;
		// assign var to true - no longer a decision variable!
		master()->assign_.eliminate(v);
	}
}

void SharedContext::simplifyBtig(Literal p) {
	assert(master_ != 0);
	SWL& negPList = btig_[(~p).index()];
	SWL& pList    = btig_[ (p).index()];
	numBin_      -= (uint32)negPList.left_size();
	numTern_     -= (uint32)negPList.right_size();
	for (SWL::left_iterator it = negPList.left_begin(), end = negPList.left_end(); it != end; ++it) {
		remove_bin(btig_[(~*it).index()], p);
	}
	// remove every ternary clause containing p -> clause is satisfied
	for (SWL::right_iterator it = negPList.right_begin(), end = negPList.right_end(); it != end; ++it) {
		remove_tern(btig_[ (~it->first).index() ], p);
		remove_tern(btig_[ (~it->second).index() ], p);
	}
	// transform ternary clauses containing ~p to binary clause
	for (SWL::right_iterator it = pList.right_begin(), end = pList.right_end(); it != end; ++it) {
		Literal q = it->first;
		Literal r = it->second;
		--numTern_;
		remove_tern(btig_[(~q).index()], ~p);
		remove_tern(btig_[(~r).index()], ~p);
		if (master_->value(q.var()) == value_free && master_->value(r.var()) == value_free) {
			// clause is binary on dl 0
			addBinary(q, r);
		}
		// else: clause is SAT and removed when the satisfied literal is processed
	}
	releaseVec(pList);
	releaseVec(negPList);
}

void SharedContext::startAddConstraints(Solver& master, uint32 constraintGuess) {
	assert( (master_ == 0 && shareCount_ == 0) || (master_ == &master && shareCount_ == 1) );
	if (master_ == 0) {
		Antecedent::checkPlatformAssumptions();
		master_     = &master;
		shareCount_ = 1;
	}
	if (tag_ == negLit(0)) {
		// add aux var for tag literal
		tag_ = posLit(addVar(Var_t::atom_var));
		setFrozen(tag_.var(), true);
		--problem_.vars;
	}
	btig_.resize((numVars()+1)<<1);
	if (satPrepro.get()) {
		satPrepro->setContext(*this);
	}
	master_->startInit(this, constraintGuess);
	lastInit_ = master_->constraints_.size();
}

void SharedContext::add(Constraint* c) {
	assert(master_ && unique());
	++problem_.constraints;
	master()->constraints_.push_back(c);
}

bool SharedContext::addUnary(Literal p) {
	assert(master_ && unique());
	return master()->addUnary(p, Constraint_t::static_constraint);
}

void SharedContext::addPost(PostPropagator* p) {
	assert(master_ && unique());
	return master()->addPost(p);
}

void SharedContext::addEnumerator(Enumerator* en) {
	if (en == 0) {
		en = new NullEnumerator();
	}
	enumerator_.reset(en);
	enumerator_->startInit(*this);
}
 
uint32 SharedContext::numConstraints() const {
	return numBinary() + numTernary() + master()->constraints_.size();
}

bool SharedContext::endInit(uint32 shareCount) {
	assert(master_ && unique());
	if (master()->hasConflict()) return false;
	if (!master()->post_.init(*master())) {
		return false;
	}
	struct Holder {
		~Holder() { if (con) con->destroy(master, true); }
		Solver*     master;
		Constraint* con;
	} enumC = { master(), enumerator()->endInit(*this, shareCount) };
	if (satPrepro.get()) {
		SatPrepro temp(satPrepro.release());
		bool r = temp->preprocess(enumerator()->enumerate());
		satPrepro.reset(temp.release());
		if (!r) return false;
	}
	master_->setEnumerationConstraint(enumC.con);
	enumC.con = 0;
	if (!master()->endInit()) return false;
	lastTopLevel_ = master()->units_;
	shareCount_   = shareCount;
	problem_.constraints_binary = numBin_;
	problem_.constraints_ternary= numTern_;
	return true;
}

bool SharedContext::attach(Solver& other) {
	assert(!unique() && master_ && master_ != &other);
	Var oldV = other.numVars();
	other.startInit(this, static_cast<uint32>(master_->constraints_.size()-lastInit_));
	// 1. clone assignment
	other.assign_.requestData(master()->assign_.numData());
	LitVec::size_type prevTs = other.trail().size();
	const LitVec& trail      = master()->trail();
	Antecedent null;
	for (LitVec::size_type i = other.units_; i < trail.size(); ++i) {
		if (!other.force(trail[i], null)) {
			return false;
		}
		other.markSeen(trail[i].var());
	}
	other.units_        = static_cast<uint32>(trail.size());
	other.lastSimplify_ = other.constraints_.empty() ? trail.size() : prevTs;
	if (satPrepro.get()) {
		for (Var v = oldV+1; v <= other.numVars(); ++v) {
			if (eliminated(v) && other.value(v) == value_free) {
				other.assign_.eliminate(v);
			}
		}
	}
	// 2. clone & attach constraints
	const Solver::ConstraintDB& db = master()->constraints_;
	for (LitVec::size_type i = lastInit_; i < db.size(); ++i) {
		if (Constraint* c = db[i]->cloneAttach(other)) {
			other.constraints_.push_back(c);
		}
		if (other.hasConflict()) return false;
	}
	Constraint* c = master_->getEnumerationConstraint();
	other.setEnumerationConstraint( c ? c->cloneAttach(other) : 0 );
	// 3. endInit
	return (other.post_.init(other) && other.endInit())
		|| (detach(other), false);
}

void SharedContext::detach(Solver& s) {
	s.setEnumerationConstraint(0);
	if (master() == &s) {
		master_     = 0;
		shareCount_ = 0;
	}
}

uint32 SharedContext::problemComplexity() const {
	assert(master_);
	uint32 r = numBinary() + numTernary();
	for (uint32 i = 0; i != master()->constraints_.size(); ++i) {
		r += master()->constraints_[i]->estimateComplexity(*master());
	}
	return r;
}

bool SharedContext::learnBinary(Literal p, Literal q) {
	bool add = false;
	mt::Mutex::scoped_lock lock(*mutex_);
	if (!btig_[(~p).index()].hasLearntImplication(q)) {
		btig_[(~p).index()].addLearnt(q);
		btig_[(~q).index()].addLearnt(p);
		add = true;
		++learntBin_;
	}	
	return add;
}

bool SharedContext::learnTernary(Literal p, Literal q, Literal r) {
	bool add = false;
	mt::Mutex::scoped_lock lock(*mutex_);
	if (!btig_[(~p).index()].hasLearntImplication(q, r)) {
		btig_[(~p).index()].addLearnt(q, r);
		btig_[(~q).index()].addLearnt(p, r);
		btig_[(~r).index()].addLearnt(p, q);
		add = true;
		++learntTern_;
	}	
	return add;
}

mt::SharedLiterals* SharedContext::distribute(const Solver& s, const Literal* lits, uint32 size, const ClauseExtra& extra) const {
	mt::SharedLiterals* ret = distributor_.get() ? distributor_->publish(s, lits, size, extra) : 0;
	if (ret && s.stats.parallel) ++s.stats.parallel->shared;
	return ret;
}

void SharedContext::distributeShared(const Solver& s, Literal p, Literal q, Literal r, ConstraintType t) const {
	if (distributor_.get()) {
		distributor_->publishShort(s, t, p, q, r);
	}
}

uint32 SharedContext::receive(const Solver& target, mt::SharedLiterals** out, uint32 maxOut) const {
	if (distributor_.get()) {
		return distributor_->receive(target, out, maxOut);
	}
	return 0;
}

}
