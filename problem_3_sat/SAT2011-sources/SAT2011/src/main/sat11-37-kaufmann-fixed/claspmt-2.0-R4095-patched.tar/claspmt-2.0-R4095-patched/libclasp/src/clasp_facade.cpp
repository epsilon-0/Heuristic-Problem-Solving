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
#include <clasp/clasp_facade.h>
#include <clasp/model_enumerators.h>
#include <clasp/cb_enumerator.h>
#include <clasp/weight_constraint.h>
#include <clasp/minimize_constraint.h>
#include <clasp/parallel_solve.h>
namespace Clasp {
/////////////////////////////////////////////////////////////////////////////////////////
// HeuristicOptions
/////////////////////////////////////////////////////////////////////////////////////////
HeuristicOptions::HeuristicOptions() 
	: name("berkmin")
	, lookahead(Lookahead::no_lookahead)
	, lookaheadNum(-1)
	, loops(-1)
	, berkMoms(true)
	, berkHuang(false)
	, berkOnce(false) 
	, nant(false) {
		extra.berkMax = -1;
}

DecisionHeuristic* HeuristicOptions::createHeuristic() const {
	DecisionHeuristic* heu = 0;
	if (name == "berkmin") {
		bool   l = loops == -1 || loops == 1;
		uint32 m = extra.berkMax < 0 ? 0 : extra.berkMax;
		heu = new ClaspBerkmin(m, l, berkMoms, berkHuang, berkOnce);
	}
	else if (name == "vmtf") {
		uint32 m = extra.vmtfMtf < 0 ? 8 : extra.vmtfMtf;
		heu = new ClaspVmtf( m, loops == 1);
	}
	else if (name == "vsids") {
		heu = new ClaspVsids(loops == 1);
	}
	else if (name == "none") {
		heu = new SelectFirst();
	}
	if (lookahead != Lookahead::no_lookahead || lookaheadNum != -1) {
		return new UnitHeuristic(lookahead, nant, heu, lookaheadNum);
	}
	return heu;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Local- & ThreadOptions
/////////////////////////////////////////////////////////////////////////////////////////
LocalOptions::LocalOptions() : loopRep(DefaultUnfoundedCheck::common_reason), solver_(new Solver()), heuristic_(new HeuristicOptions()) {}
LocalOptions::~LocalOptions() {
	delete heuristic_;
	delete solver_;
}
HeuristicOptions& LocalOptions::heuristic() {
	if (heuristic_) return *heuristic_;
	heuristic_ = new HeuristicOptions();
	return *heuristic_;
}

void LocalOptions::applyHeuristic() {
	if (heuristic_) {
		DecisionHeuristic* h = heuristic_->createHeuristic();
		delete heuristic_;
		heuristic_ = 0;		
		solver_->strategies().heuristic.reset(h);
	}
}

bool LocalOptions::validate(std::string& err) {
	if (solver_ && solver_->strategies().search == SolverStrategies::no_learning) {
		if (heuristic_ && heuristic_->name != "unit" && heuristic_->name != "none") {
			err  = "Heuristic '";
			err += heuristic_->name;
			err += "' requires lookback strategy!";
			return false;
		}
		SolverStrategies* s = &solver_->strategies();
		s->cflMinAntes = SolverStrategies::no_antes;
		s->setCompressionStrategy(0);
		s->saveProgress = 0;
		solve.restart.sched.init(0, 0.0, 0);
		solve.reduce.setStrategy(-1.0, 0.0, 0.0);
		solve.setRandomizeParams(0,0);
		solve.setShuffleParams(0,0);
		solve.restart.local = solve.restart.bounded = solve.reduce.reduceOnRestart = false;
	}
	return true;
}

void LocalOptions::initFrom(const LocalOptions& other) {
	if (other.heuristic_) {
		heuristic()      = *other.heuristic_;
	}
	SolverStrategies* st = &solver_->strategies();
	st->rng          = other.solver_->strategies().rng;
	st->search       = other.solver_->strategies().search;
	st->saveProgress = other.solver_->strategies().saveProgress;
	st->cflMinAntes  = other.solver_->strategies().cflMinAntes;
	st->strengthenRecursive = other.solver_->strategies().strengthenRecursive;
	st->randomWatches= other.solver_->strategies().randomWatches;
	st->setCompressionStrategy(other.solver_->strategies().compress());
	
	solve   = other.solve;
	loopRep = other.loopRep;

}

ThreadOptions::ThreadOptions() : forceGP(false), genTemplate(false), numThreads_(1), master_(new LocalOptions()), threads_(0) {}
ThreadOptions::Distribution::Distribution() 
	: grace(1024), lbd(0), types(0), filter(filter_gp), copyProblem(false)  {} 
ThreadOptions::~ThreadOptions() {
	delete [] threads_;
	delete master_;
}

void ThreadOptions::setThreads(uint32 num) {
	if (num != numThreads_ && num > 0) {
		delete [] threads_;
		threads_    = new LocalOptions[num-1];
		numThreads_ = num;
	}
}

void ThreadOptions::reset() {
	for (uint32 i = 0; i != numThreads_; ++i) {
		threadConfig(i)->solver().reset();
	}
}
bool ThreadOptions::validate(std::string& err) {
	if (!master_->validate(err)) return false;
	for (uint32 i = 1; i != numThreads_; ++i) {
		if (!threads_[i-1].validate(err)) return false;
	}
	return true;
}
void ThreadOptions::applyHeuristic() {
	master_->applyHeuristic();
	for (uint32 i = 1; i != numThreads_; ++i) {
		threads_[i-1].applyHeuristic();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// GlobalOptions & ClaspConfig
/////////////////////////////////////////////////////////////////////////////////////////
GlobalOptions::GlobalOptions()
	: progress(0)
	, transExt(ProgramBuilder::mode_native)
	, numModels(-1)
	, projectOpts(7)
	, supported(false) 
	, project(false)
	, record(false)
	, restartOnModel(false)
	, brave(false)
	, cautious(false)
	, onlyPre(false) {
}

ProgramBuilder* GlobalOptions::createApi(Clasp::mt::Shared_DependencyGraph** out) {
	ProgramBuilder* api = new ProgramBuilder();
	*out                = supported ? 0 : new mt::Shared_DependencyGraph();
	api->setExtendedRuleMode(transExt);
	api->startProgram(ctx, *out, eq);
	return api;
}

Enumerator* GlobalOptions::initEnumerator(Enumerator::Report* r) {
	ModelEnumerator* e = 0;
	Enumerator* ret    = 0;
	if (consequences()) {
		ret = new CBConsequences(brave ? CBConsequences::brave_consequences : CBConsequences::cautious_consequences);
	}
	else if (record) {
		ret = (e = new RecordEnumerator());
	}
	else {
		ret = (e = new BacktrackEnumerator(projectOpts));
	}
	if (e) { e->setEnableProjection(project); }
	ret->setRestartOnModel(restartOnModel);
	ret->setReport(r);
	if (progress) {
		ret->enableProgressReport(progress);
	}
	return ret;
}

bool ClaspConfig::validate(std::string& err) {
	if (!thread.validate(err)) {
		return false;
	}
	if (global.brave && global.cautious) {
		err = "Options 'brave' and 'cautious' are mutually exclusive!";
		return false;
	}
	if (global.restartOnModel) { global.record  = true; }
	return true;
}

IncrementalControl::IncrementalControl()  {}
IncrementalControl::~IncrementalControl() {}
/////////////////////////////////////////////////////////////////////////////////////////
// ClaspFacade
/////////////////////////////////////////////////////////////////////////////////////////
ClaspFacade::ClaspFacade() 
	: config_(0)
	, inc_(0)
	, cb_(0)
	, input_(0)
	, ctrl_(0)
	, api_(0)
	, graph_(0)
	, ufs_(0)
	, result_(result_unknown)
	, state_(state_not_started)
	, step_(0)
	, more_(true) {
}

void ClaspFacade::init(Input& problem, ClaspConfig& config, IncrementalControl* inc, Callback* c) {
	config_ = &config;
	inc_    = inc;
	cb_     = c;
	input_  = &problem;
	ctrl_   = 0;
	result_ = result_unknown;
	state_  = state_not_started;
	step_   = 0;
	more_   = true;
	validateWeak();
	config.thread.applyHeuristic();
	if (config.thread.numThreads() > 1 && !config.thread.distribute.copyProblem) {
		config.global.ctx.enableConstraintSharing();
	}
}

void ClaspFacade::validateWeak(ThreadOptions& cfg) {
	bool warnUnit = true;
	bool warnInit = true;
	for (uint32 i = 0; i != cfg.numThreads(); ++i) {
		HeuristicOptions& h = cfg.threadConfig(i)->heuristic();
		if (h.name == "unit") {
			if (h.lookahead == Lookahead::no_lookahead) {
				if (warnUnit) {
					warning("Unit-heuristic implies lookahead. Forcing atom-lookahead!");
					warnUnit = false;
				}
				h.lookahead = Lookahead::atom_lookahead;
			}
			else if (h.lookaheadNum != -1) {
				if (warnInit) {
					warning("Unit-heuristic implies lookahead. Ignoring 'initial-lookahead'!");
					warnInit = false;
				}
				h.lookaheadNum = -1;
			}
		}
		else if (h.lookaheadNum != -1 && h.lookahead == Lookahead::no_lookahead) {
			h.lookahead = Lookahead::atom_lookahead;
		}
	}
}

void ClaspFacade::validateWeak() {
	if (inc_) {
		if (config_->global.onlyPre) {
			warning("Option 'onlyPre' is ignored in incremental setting!"); 
			config_->global.onlyPre = false;
		}
	}
	if (config_->global.supported && config_->global.eq.iters != 0) {
		warning("Supported models requires --eq=0. Disabling eq-preprocessor!");
		config_->global.eq.disable();
	}
	if (config_->global.opt.all || config_->global.opt.no) {
		config_->global.opt.hierarch = 0;
	}
	validateWeak(config_->thread);
}

// Non-incremental solving...
void ClaspFacade::solve(Input& problem, ClaspConfig& config, Callback* c) {
	init(problem, config, 0, c);
	LocalOptions* master = config.thread.master();
	if (!read() || !preprocess()) {
		result_ = result_unsat;
		more_   = false;
		reportSolution(*config.global.ctx.enumerator(), true);
	}
	else if (!config.global.onlyPre) {
		setProblemSize();
		AutoState state(this, state_solve);
		ctrl_   = createSolveObject(config); // deleted by AutoState
		more_   = ctrl_->solve(config.global.ctx, master->solve, LitVec());
	}
}

// Incremental solving...
void ClaspFacade::solveIncremental(Input& problem, ClaspConfig& config, IncrementalControl& inc, Callback* c) {
	init(problem, config, &inc, c);
	LitVec assume;
	LocalOptions* master = config_->thread.master();
	do {
		inc.initStep(*this);
		result_   = result_unknown;
		more_     = true;
		if (!read() || !preprocess()) {
			result_ = result_unsat;
			more_   = false;
			reportSolution(*config.global.ctx.enumerator(), true);
			break;
		}
		else {
			setProblemSize();
			AutoState state(this, state_solve);
			assume.clear();
			problem.getAssumptions(assume);
			ctrl_    = createSolveObject(config);
			more_    = ctrl_->solve(config.global.ctx, master->solve, assume);
			if (result_ == result_unknown && !more_) {
				// initial assumptions are unsat
				result_ = result_unsat;
			}
		}
	} while (inc.nextStep(*this) && ++step_);
}

// Creates a ProgramBuilder-object if necessary and reads
// the input by calling input_->read().
// Returns false, if the problem is trivially UNSAT.
bool ClaspFacade::read() {
	AutoState state(this, state_read);
	Input::ApiPtr ptr(&config_->global.ctx);
	if (input_->format() == Input::SMODELS) {
		if (step_ == 0) {
			Clasp::mt::Shared_DependencyGraph* dg;
			api_   = config_->global.createApi(&dg);
			graph_ = dg;
			ufs_   = 0;
		}
		if (inc_) {
			api_->updateProgram();
		}
		ptr.api= api_.get();
	}
	if (input_->format() == Input::DIMACS && config_->global.numModels == -1) {
		config_->global.numModels = 1;
	}
	if (config_->global.opt.hierarch > 0 && !config_->global.opt.no) {
		config_->global.ctx.requestTagLiteral();
	}
	if (!input_->read(config_->thread.master()->solver(), ptr, config_->global.numModels)) {
		return false;
	}
	return true;
}

// Prepare the solving state:
//  - if necessary, transforms the input to nogoods by calling ProgramBuilder::endProgram()
//  - fires event_p_prepared after input was transformed to nogoods
//  - adds any minimize statements to the solver and initializes the enumerator
//  - calls Solver::endInit().
// Returns false, if the problem is trivially UNSAT.
bool ClaspFacade::preprocess() {
	AutoState state(this, state_preprocess);
	Solver& master = config_->thread.master()->solver();
	SharedMinimizeData* m = 0;
	Input::ApiPtr ptr(&config_->global.ctx);
	if (api_.get()) {
		if (!api_->endProgram(master)) {
			fireEvent(master, event_p_prepared);
			return false;
		}
		if (graph_.get() && graph_->nodes() > 0 && !ufs_) {
			ufs_ = new DefaultUnfoundedCheck(config_->thread.master()->loopRep);
			ufs_->attachTo(master, graph_.get());
		}
		ptr.api = api_.get();
	}
	if (!config_->global.opt.no && step_ == 0) {
		MinimizeBuilder builder;
		input_->addMinimize(builder, ptr);
		if (builder.hasRules()) {
			if (!config_->global.opt.vals.empty()) {
				const WeightVec& opt = config_->global.opt.vals;
				for (uint32 i = 0; i != opt.size(); ++i) {
					builder.setOptimum(i, opt[i]);
				}
			}
			m = builder.build(master, config_->global.ctx.tagLiteral());
		}
		if (!builder.hasRules() || (builder.numRules() == 1 && config_->global.opt.hierarch < 2)) {
			config_->global.ctx.removeTagLiteral();
		}
	}
	fireEvent(master, event_p_prepared);
	if (!inc_ && api_.is_owner()) {
		api_ = 0;
	}
	if (!initEnumeration(m) || !config_->global.ctx.endInit(config_->thread.numThreads())) {
		return false;
	}
	return true;
}

// Configures the given minimize constraint and adds it to the enumerator.
// Optimize values that are given in config are added to min.
bool ClaspFacade::configureMinimize(SharedMinimizeData* min) const {
	min->setMode(config_->global.opt.all ? MinimizeMode_t::enumerate : MinimizeMode_t::optimize, config_->global.opt.hierarch);
	if (config_->global.consequences()) {
		warning("Minimize statements: Consequences may depend on enumeration order!");
	}
	if (config_->global.project) {
		for (const WeightLiteral* it = min->lits; !isSentinel(it->first); ++it) {
			if ( !config_->global.ctx.project(it->first.var()) ) {
				warning("Projection: Optimization values may depend on enumeration order!");
				break;
			}
		}
	}
	config_->global.ctx.enumerator()->setMinimize(min, config_->global.opt.heu);
	return true;
}

// Finalizes initialization of model enumeration.
// Configures and adds an eventual minimize constraint,
// sts the number of models to compute and adds warnings
// if this number conflicts with the preferred number of the enumerator.
bool ClaspFacade::initEnumeration(SharedMinimizeData* min)  {
	Enumerator* e = step_ == 0 ? config_->global.initEnumerator(this) : config_->global.ctx.enumerator();
	config_->global.ctx.addEnumerator(e);
	if (step_ == 0) {
		if (min && !configureMinimize(min)) {
			return false;
		}
		uint32 defM = !e->minimize() && !config_->global.consequences();
		if (config_->global.numModels == -1) { 
			config_->global.numModels = defM; 
		}
		else if (config_->global.numModels > 0 && defM == 0) {
			if (config_->global.consequences()) {
				warning("Option '--number' not 0: last model may not cover consequences!");
			}
			if (e->minimize()) {
				warning("Option '--number' not 0: Optimality of last model not guaranteed!");
			}
		}
		if (config_->thread.numThreads() > 1) {
			bool forceST = config_->global.project && !config_->global.record;
			if (forceST) {
				warning("Multi-Threading disabled - Selected reasoning mode not supported!");
				config_->thread.setThreads(1);
			}
			else if (config_->thread.numThreads() > ClaspFacade::hardware_concurrency()) {
				warning("Oversubscription: Number of threads exceeds hardware concurrency!");
			}
		}
	}
	config_->global.ctx.enumerator()->enumerate(config_->global.numModels);
	return true;
}

// Computes a value that represents the problem size.
// The value is then used by the reduce-heuristic
// to determine the initial learnt db size.
void ClaspFacade::setProblemSize() const {
	const SharedContext& ctx  = config_->global.ctx;
	uint32 estimate = 0;
	uint32 ps;
	for (uint32 i = 0; i != config_->thread.numThreads(); ++i) {
		LocalOptions* o = config_->thread.threadConfig(i);
		if (o->solve.reduce.estimate) {
			if (estimate == 0) {
				estimate = ctx.problemComplexity();
			}
			ps = estimate;
		}
		else if (input_->format() != Input::DIMACS) {
			double r = ctx.numVars() / std::max(1.0, double(ctx.numConstraints()));
			if (r < 0.1 || r > 10.0) {
				ps = std::max(ctx.numVars(), ctx.numConstraints());
			}
			else {
				ps = std::min(ctx.numVars(), ctx.numConstraints());
			}
		}
		else {
			ps = ctx.numConstraints();
		}
		o->solve.reduce.setProblemSize(ps);
	}
}

#ifndef DISABLE_MULTI_THREADING
uint32 ClaspFacade::hardware_concurrency() { return ParallelSolve::hardwareThreads(); }
SolveAlgorithm* ClaspFacade::createSolveObject(ClaspConfig& config) const {
	if (config.thread.numThreads() == 1) {
		return new SimpleSolve();
	}
	// parallel solving
	int numT = config.thread.numThreads();
	std::auto_ptr<ParallelSolve> ctrl(new ParallelSolve());
	ctrl->setForceGP(config.thread.forceGP);
	ctrl->setIntegrate(config.thread.distribute.grace, config.thread.distribute.filter);
	ctrl->setRestarts(config.thread.restarts.maxR, config.thread.restarts.sched);
	SharedContext* ctx   = ctrl->init(numT, config.global.ctx);
	LocalOptions* master = config.thread.master();
	bool enableJumpStats = master->solver().stats.jumps != 0;
	for (int i = 1; i != numT; ++i) {
		LocalOptions* ti = config.thread.threadConfig(i);
		if (enableJumpStats) {
			ti->solver().stats.enableJumpStats();
		}
		if (ufs_) {
			DefaultUnfoundedCheck* u = new DefaultUnfoundedCheck(ti->loopRep);
			u->attachTo(ti->solver(), graph_.get());
		}
		ctrl->addThread(ti->solver(), ctx, ti->solve);
	}
	std::auto_ptr<GlobalQueue> dist;
	if (config.thread.distribute.types != 0) {
		dist.reset(new GlobalQueue(numT, config.thread.distribute.types, config.thread.distribute.lbd));
		ctx->enableLearntSharing(dist.release());
	}
	return ctrl.release();
}
#else
uint32 ClaspFacade::hardware_concurrency() { return 1; }
SolveAlgorithm* ClaspFacade::createSolveObject(ClaspConfig&) const {
	return new SimpleSolve();
}
#endif

}
