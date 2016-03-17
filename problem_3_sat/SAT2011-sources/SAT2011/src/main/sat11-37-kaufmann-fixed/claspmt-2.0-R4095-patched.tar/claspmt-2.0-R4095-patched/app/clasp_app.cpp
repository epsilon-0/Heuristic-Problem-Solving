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
#include "clasp_app.h"
#include "alarm.h"
#include <iostream>
#include <fstream>
#include <clasp/clause.h>
/////////////////////////////////////////////////////////////////////////////////////////
// Application
/////////////////////////////////////////////////////////////////////////////////////////
namespace Clasp {
#if !defined(CLASP_USAGE)
#define CLASP_USAGE   "clasp [number] [options] [file]"
#endif
#if !defined (SIGUSR1)
#define SIGUSR1 SIGTERM
#endif
#if !defined(SIGUSR2)
#define SIGUSR2 SIGTERM
#endif
namespace {
std::ostream& operator << (std::ostream& os, Literal l) {
	if (l.sign()) os << '-';
	os << l.var();
	return os;
}
std::istream& operator >> (std::istream& in, Literal& l) {
	int i;
	if (in >> i) {
		l = Literal(i >= 0 ? Var(i) : Var(-i), i < 0);
	}
	return in;
}

}
/////////////////////////////////////////////////////////////////////////////////////////
// public functions & basic helpers
/////////////////////////////////////////////////////////////////////////////////////////
Application::Application() : timeToFirst_(-1.0), timeToLast_(-1.0), facade_(0), stopped_(0)  {}
Application& Application::instance() {
	static Application inst;
	return inst;
}
void Application::sigHandler(int sig) {
	Application::instance().kill(sig);
}

// Kills any pending alarm
void Application::killAlarm() {
	if (cmdOpts_.basic.timeout>0) {
		setAlarm(0); 
	}
}

// Called on timeout or signal.
// Prints summary and then kills the application.
void Application::kill(int sig) {
	if (stopped_ == 0) {
		stopped_ = sig; // ignore further kill requests
		SCOPE_ALARM_LOCK();
		fprintf(stderr, "\n*** INTERRUPTED! ***\n");
		if (!facade_ || !facade_->terminate()) {
			cpuTotalTime_.stop();
			for (int i = 0; i != sizeof(timer_)/sizeof(Timer<RealTime>); ++i) { 
				timer_[i].stop(); 
			}
			if (facade_ && facade_->state() != ClaspFacade::state_not_started) {
				printResult(sig);
			}
			bool hasModel = config_.global.ctx.enumerator()->enumerated > 0;
			fflush(stdout);
			fflush(stderr);
			_exit(hasModel ?  S_SATISFIABLE : S_UNKNOWN);
		}
		else {
			// multiple threads are active - shutdown was initiated
			fprintf(stderr, "*** Shutting down threads...\n");
		}	
	}
}

void Application::installSigHandlers() {
	if (signal(SIGINT, &Application::sigHandler) == SIG_IGN) {
		signal(SIGINT, SIG_IGN);
	}
	if (signal(SIGTERM, &Application::sigHandler) == SIG_IGN) {
		signal(SIGTERM, SIG_IGN);
	}
	if (SIGUSR1 != SIGTERM && (signal(SIGUSR1, &Application::sigHandler) == SIG_IGN)) {
		signal(SIGUSR1, SIG_IGN);
	}
	if (SIGUSR2 != SIGTERM && (signal(SIGUSR2, &Application::sigHandler) == SIG_IGN)) {
		signal(SIGUSR2, SIG_IGN);
	}
	if (cmdOpts_.basic.timeout > 0) {
		setAlarmHandler(&Application::sigHandler);
		if (setAlarm(cmdOpts_.basic.timeout) == 0) {
			messages.warning.push_back("Could not set time limit!");
		}
	}
}

std::istream& Application::getStream() {
	if (generic.input.empty() || generic.input[0] == "stdin") {
		generic.input.resize(1, "stdin");
		return std::cin;
	}
	else {
		static std::ifstream file;
		if (file.is_open()) return file;
		file.open(generic.input[0].c_str());
		if (!file) { throw std::runtime_error("Can not read from '"+generic.input[0]+"'");  }
		return file;
	}
}

void Application::printHelp() const {
	printf("clasp %s\n", CLASP_VERSION);
	printf("\nusage: %s\n", CLASP_USAGE);
	printf("%s\n", getHelp().c_str());
	printf("\nusage: %s\n", CLASP_USAGE);
	printf("Default commandline:\nclasp %s\n", getDefaults().c_str());
	fflush(stdout);
}

void Application::printVersion() const {
	printf("clasp %s\n", CLASP_VERSION);	
	printf("Configured with: WITH_CLASPRE=%d WITH_THREADS=%d", WITH_CLASPRE, WITH_THREADS);
#ifndef DISABLE_MULTI_THREADING
	printf(" (TBB_VERSION=%d.%d)", TBB_VERSION_MAJOR, TBB_VERSION_MINOR);
#endif
	printf("\n%s\n", CLASP_LEGAL);
	fflush(stdout);
}

void Application::printTemplate() const {
	printf("# clasp %s portfolio file\n", CLASP_VERSION);
	printf("# A portfolio file contains (possibly empty) a list of configurations.\n");
	printf("# Each of which must have the following format:\n");
	printf("#   [<name>]: <options>\n");
	printf("# where <name> is an arbitrary string and <options> is a list of\n");
	printf("# command-line options from \"Search Options\" and/or \"Lookback Options\".\n");
	printf("#\n");
	printf("# SEE: clasp --help\n");
	printf("#\n");
	printf("# NOTE: Options given on the command-line are added to all configurations in a\n"
	       "#       portfolio file. If an option is given both on the command-line and in a\n"
	       "#       portfolio configuration, the one from the command-line is preferred.\n");
	printf("#\n");
	printf("# EXAMPLE for up to 5 threads:\n");
	printf("[VSIDS]:   --heu=VSIDS\n");
	printf("[LUBY]:    --restarts=256\n");
	printf("[LUBY-SP]: --restarts=256 --save-p\n");
	printf("[HUANG]:   --berk-max=512 --berk-huang --estimate\n");
	printf("[LOCAL-R]: --restarts=100,1.5,10000 --local-restarts\n");
}

/////////////////////////////////////////////////////////////////////////////////////////
// run - clasp's "main"-function
/////////////////////////////////////////////////////////////////////////////////////////
int Application::run(int argc, char** argv) {
	if (!parse(argc, argv, "clasp", parsePositional)) {
		// command-line error
		ERROR_OUT("*** clasp", messages.error.c_str());
		return S_ERROR;
	}
	if ((generic.help&&(printHelp(),1)) || (generic.version&&(printVersion(),1))) {
		return EXIT_SUCCESS;
	}
	if (claspre_.listFeatures) {
		claspre_.printFeatures();
		return EXIT_SUCCESS;
	}
	if (config_.thread.genTemplate) {
		printTemplate();
		return EXIT_SUCCESS;
	}	
	installSigHandlers();
	int retStatus = S_UNKNOWN;
	try {
		StreamInput input(getStream(), detectFormat(getStream()));
		cmdOpts_.applyDefaults(input.format());
		configureOutput(input.format());
		if (cmdOpts_.basic.stats > 1) {
			config_.thread.threadConfig(0)->solver().stats.enableJumpStats();
		}
		ClaspFacade clasp; facade_ = &clasp;
		timer_[0].start();
		cpuTotalTime_.start();
		clasp.solve(input, config_, this);
		timer_[0].stop();
		cpuTotalTime_.stop();
		int sig = stopped_++; // disable signal handler
		killAlarm();          // kill any pending alarms;
		printResult(sig);
		if      (clasp.result() == ClaspFacade::result_unsat) retStatus = S_UNSATISFIABLE;
		else if (clasp.result() == ClaspFacade::result_sat)   retStatus = S_SATISFIABLE;
		else                                                  retStatus = S_UNKNOWN;
	}
	catch (const std::bad_alloc& e) { retStatus = exception(S_MEMORY, e.what()); }
	catch (const std::exception& e) { retStatus = exception(S_ERROR, e.what()); }
#ifndef COMPETITION_MODE
		return retStatus;
#else
		fflush(stdout);
		fflush(stderr);
		_exit(retStatus);
#endif
}

int Application::exception(int status, const char* what) {
	stopped_ = SIGTERM;
	timer_[0].stop();
	cpuTotalTime_.stop();
	ERROR_OUT("*** clasp", what);
	if (facade_) {
		printResult(stopped_);
	}
	fflush(stdout);
	fflush(stderr);
	_exit(status);
}

/////////////////////////////////////////////////////////////////////////////////////////
// State & Result functions
/////////////////////////////////////////////////////////////////////////////////////////
// Generates a summary after search has stopped or has been interrupted.
// The summary is then passed to the output object which is responsible
// for printing.
void Application::printResult(int sig) {
	OutputFormat::RunSummary sol(config_.global.ctx);
	sol.complete         = (sig == 0 && !facade_->more());
	sol.term             = sig;
	sol.consequences     = config_.global.consequences() ? config_.global.cbType() : 0;
	sol.totalTime        = timer_[0].total();
	sol.solveTime        = facade_->state() == ClaspFacade::state_solve ? timer_[ClaspFacade::state_solve].total():0.0;
	sol.modelTime        = timeToFirst_ != -1.0 ? timeToFirst_ : 0.0;
	double ttl           = timeToLast_ != -1.0 ? timeToLast_ : 0.0;
	sol.unsatTime        = sol.complete && sol.solveTime-ttl >= 0.001 ? sol.solveTime-ttl : 0.0;
	sol.cpuTime          = cpuTotalTime_.total();
	if (config_.global.onlyPre) {
		if (sig) return;
		if (facade_->api()) { // asp-mode
			facade_->result() == ClaspFacade::result_unsat
				? (void)(std::cout << "0\n0\nB+\n1\n0\nB-\n1\n0\n0\n")
				: facade_->api()->writeProgram(std::cout);
			delete facade_->releaseApi();
		}
		else {
			if (facade_->result() != ClaspFacade::result_unsat) {
				WARNING_OUT("Search not started because of option '--pre'!");
			}
			out_->reportResult(sol, 0, 0);
		}
		return;
	}
	SolveStats agg;
	PodVector<const SolveStats*>::type stats;
	if (cmdOpts_.basic.stats) {
		if (config_.thread.numThreads() <= 1) {
			stats.push_back(&config_.thread.master()->solver().stats);
		}
		else {
			stats.reserve(config_.thread.numThreads()+1);
			const SolveStats* m = &config_.thread.master()->solver().stats;
			if (m->jumps)    { agg.enableJumpStats(); }
			if (m->parallel) { agg.enableParallelStats(); }
			stats.push_back(&agg);
			for (uint32 i = 0; i != config_.thread.numThreads(); ++i) {
				agg.accu(config_.thread.threadConfig(i)->solver().stats);
				if (cmdOpts_.basic.stats > 1) {
					stats.push_back(&config_.thread.threadConfig(i)->solver().stats);
				}
			}
		}
	}
	out_->reportResult(sol, !stats.empty() ? &stats[0] : 0, (uint32)stats.size());
	if (!lemmaOut_.empty()) {
		try { writeLemmas(); } 
		catch (const std::exception& e) {
			ERROR_OUT("clasp", e.what());
		}
	}
}

// State-transition callback called by ClaspFacade.
// Handles timing and notifies output object
void Application::state(ClaspFacade::Event e, ClaspFacade& f) { 
	SCOPE_ALARM_LOCK();
	if (e == ClaspFacade::event_state_enter) {
		while (!messages.warning.empty()) {
			WARNING_OUT(messages.warning.back().c_str());
			messages.warning.pop_back();
		}
		out_->reportState(f.state(), true, 0);
		timer_[f.state()].start();
	}
	else if (e == ClaspFacade::event_state_exit) {
		timer_[f.state()].stop();
		out_->reportState(f.state(), false, timer_[f.state()].total());
	}
}

// Event callback called by ClaspFacade.
// Notifies output object about models
void Application::event(const Solver& s, ClaspFacade::Event e, ClaspFacade& f) {
	if (e == ClaspFacade::event_model) {
		timer_[f.state()].lap();
		timeToLast_ = timer_[f.state()].total();
		if (timeToFirst_ == -1.0) {  timeToFirst_ = timeToLast_; }
		if (!out_->quiet()){
			SCOPE_ALARM_LOCK();
			model(s, *s.sharedContext()->enumerator(), config_.global.consequences());
		}
	}
	else if (e == ClaspFacade::event_p_prepared) {
		if (config_.global.onlyPre) {
			if (f.api()) f.releaseApi(); // keep api so that we can later print the program
			// HACK: release constraints and strategies - no longer needed
			config_.thread.reset();
			config_.global.ctx.satPrepro.reset(0);
			config_.global.ctx.startAddConstraints(config_.thread.master()->solver(), 0);
		}
		else if (!lemmaIn_.empty()) {
			readLemmas();	
		}
		out_->initSolve(s, f.api());
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// status & output
/////////////////////////////////////////////////////////////////////////////////////////
// Creates output object suitable for given input format
void Application::configureOutput(Input::Format f) {
	if (config_.global.onlyPre) {
		generic.verbose = 0;
	}
	if (config_.global.consequences()) {
		if (cmdOpts_.basic.quiet.first == 3) {
			// backward compatibility HACK: map --quiet to --quiet=1 when computing consequences
			cmdOpts_.basic.quiet.first = 1;
		}
		if (cmdOpts_.basic.quiet.second == -1) {
			cmdOpts_.basic.quiet.second = 2;
		}
	}
	if (claspre_.features == 0) {
		if (cmdOpts_.basic.outf != BasicOptions::out_json) {
			DefaultOutput::Format outFormat = DefaultOutput::format_asp;
			if      (f == Input::DIMACS) { outFormat = DefaultOutput::format_sat09; }
			else if (f == Input::OPB)    { outFormat = DefaultOutput::format_pb09; }
			else if (f == Input::SMODELS && cmdOpts_.basic.outf == BasicOptions::out_comp) {
				outFormat = DefaultOutput::format_aspcomp;
			}
			out_.reset(new DefaultOutput(generic.verbose, cmdOpts_.basic.quiet, outFormat, cmdOpts_.basic.ifs));
		}
		else {
			out_.reset(new JsonOutput(generic.verbose, cmdOpts_.basic.quiet));
		}
	}
	else if (f == Input::SMODELS) {
		// claspre output
		out_.reset(claspre_.createOutput(generic.verbose, cmdOpts_.basic.quiet, DefaultOutput::format_asp));
		config_.thread.setThreads(1);
		if (!claspre_.hasLimit) {
			config_.thread.master()->solve.limits = SearchLimits(500,20);
		}
		cmdOpts_.basic.stats = 2;
		config_.global.progress = out_.get();
	}
	else { throw std::runtime_error("Feature extraction not supported for current input format!"); }
	if (out_->verbosity() > 1) {
		config_.global.progress = out_.get();
	}
	out_->init(std::string("clasp version ")+CLASP_VERSION, generic.input[0]);
}
void Application::model(const Solver& s, const Enumerator& e, bool cons) {
	if (!cons) { out_->reportModel(s, e); }
	else       { out_->reportConsequences(s, e,  config_.global.cbType()); }
}
/////////////////////////////////////////////////////////////////////////////////////////
// internal helpers
/////////////////////////////////////////////////////////////////////////////////////////
// NOTE: ON WINDOWS this function is unsafe if called from time-out handler because
// it has potential races with the main thread
void Application::writeLemmas() {
	Solver& s = config_.thread.master()->solver();
	if (s.clearAssumptions()) {
		std::ofstream file(lemmaOut_.c_str());
		if (!file) throw std::runtime_error("Could not open file: "+lemmaOut_);
		LitVec lits;
		for (LitVec::size_type i = 0; i != s.numLearntConstraints(); ++i) {
			if (s.getLearnt(i).type() == Constraint_t::learnt_conflict) {
				lits.clear();			
				const ClauseHead& c = (const ClauseHead&)s.getLearnt(i);
				c.toLits(lits);
				for (LitVec::size_type i = 0; i != lits.size(); ++i) {
					file << lits[i] << " ";
				}
				file << "0\n";
				if (!file) throw std::runtime_error("Error writing file: "+lemmaOut_);
			}
		}
	}
}

void Application::readLemmas() {
	std::ifstream file(lemmaIn_.c_str());
	if (!file) throw std::runtime_error("Could not open file: "+lemmaIn_);
	Solver& s = config_.thread.master()->solver();
	ClauseCreator clause(&s);
	for (;file;) {
		for (std::string ignore; file && (file.peek() == 'c' || file.peek() == 'p'); ) {
			std::getline(file, ignore);
		}
		clause.start();
		Literal x;
		for (; file >> x && x.var() != 0; ) { 
			if (!s.validVar(x.var())) throw std::runtime_error("Bad variable in file: "+lemmaIn_);
			clause.add(x);
		}
		if (!file || !clause.end()) {
			break;
		}
	}
	if (!file.eof() && !s.hasConflict()) {
		throw std::runtime_error("Error reading file: "+lemmaIn_);
	}
}

} // end of namespace clasp

