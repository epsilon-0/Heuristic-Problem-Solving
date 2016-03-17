// 
// Copyright (c) 2006-2007, Benjamin Kaufmann
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
#ifndef CLASP_CLASP_APP_H_INCLUDED
#define CLASP_CLASP_APP_H_INCLUDED

#ifdef _MSC_VER
#pragma warning (disable : 4200) // nonstandard extension used : zero-sized array
#pragma once
#endif
#include "clasp_options.h"
#include "clasp_output.h"
#include <program_opts/typed_value.h>
#include <clasp/util/timer.h>
#include <string>
#include <vector>
#include <iosfwd>
#include <memory>
#include <stdio.h>
#include <signal.h>
/////////////////////////////////////////////////////////////////////////////////////////
// Output macros and app exit codes
/////////////////////////////////////////////////////////////////////////////////////////
#define ERROR_OUT(system,msg)  ( fflush(stdout), fprintf(stderr, "%s ERROR: %s\n", system, msg), fflush(stderr) )
#define WARNING_OUT(msg)       ( fflush(stdout), fprintf(stderr, "Warning: %s\n", msg), fflush(stderr) ) 

// exit codes
#define S_SATISFIABLE   10  // problem is satisfiable
#define S_UNSATISFIABLE 20  // problem was proved to be unsatisfiable
#define S_UNKNOWN       0   // satisfiablity of problem not knwon; search was interrupted or did not start
#define S_ERROR EXIT_FAILURE// internal error, except out of memory
#define S_MEMORY        127 // out of memory
/////////////////////////////////////////////////////////////////////////////////////////
// Clasp::Application
/////////////////////////////////////////////////////////////////////////////////////////
namespace Clasp {
	
class Application : public AppOptions, public ClaspFacade::Callback {
public:
	static Application& instance();    // returns the singleton instance
	static void sigHandler(int sig);   // signal/timeout handler
	void   installSigHandlers();       // adds handlers for SIGINT, SIGTERM, SIGALRM
	int    run(int argc, char** argv); // "entry-point"
	void   printHelp()    const;
	void   printVersion() const;
	void   printTemplate()const;
private:
	Application();
	Application(const Application&);
	const Application& operator=(const Application&);
	// -------------------------------------------------------------------------------------------
	// AppOptions interface
	void initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden) {
		claspre_.initOptions(root);
		cmdOpts_.setConfig(&config_);
		cmdOpts_.initOptions(root, hidden);
		ProgramOptions::OptionGroup basic("Basic Options");
		basic.addOptions()
			("lemma-out" , ProgramOptions::storeTo(lemmaOut_), "Write learnt lemmas to %A on exit", "<file>")
			("lemma-in"  , ProgramOptions::storeTo(lemmaIn_) , "Read additional clauses from %A"  , "<file>")
		;
		root.add(basic);
		generic.verbose = 1;
		const ProgramOptions::Option& o = **root.find("verbose");
		o.value()->defaultValue("1");
	}
	bool validateOptions(const ProgramOptions::ParsedOptions& vm, Messages& m) {
		return claspre_.validateOptions(vm) && cmdOpts_.validateOptions(vm, m);
	}
	// -------------------------------------------------------------------------------------------
	// ClaspFacade::Callback interface
	void state(ClaspFacade::Event e, ClaspFacade& f);
	void event(const Solver& s, ClaspFacade::Event e, ClaspFacade& f);
	void warning(const char* msg) { messages.warning.push_back(msg); }
	void reportRestart(const Solver&, uint64, uint32);
	// -------------------------------------------------------------------------------------------
	std::istream& getStream();
	void killAlarm();
	void kill(int sig);
	void readLemmas();
	void writeLemmas();
	int  exception(int status, const char* what);
	// -------------------------------------------------------------------------------------------  
	// Status information & output
	void configureOutput(Input::Format f);
	void model(const Solver& s, const Enumerator& e, bool cons);
	void printResult(int sig);
	// -------------------------------------------------------------------------------------------  
	ClaspConfig                   config_;
	ClaspOptions                  cmdOpts_;
	Claspre::Options              claspre_;
	Timer<ProcessTime>            cpuTotalTime_;
	Timer<RealTime>               timer_[ClaspFacade::num_states]; // one for each state
	double                        timeToFirst_;                    // time to first model
	double                        timeToLast_;                     // time to last model
	std::string                   lemmaOut_;
	std::string                   lemmaIn_;
	ClaspFacade*                  facade_;
	std::auto_ptr<OutputFormat>   out_;
	volatile sig_atomic_t         stopped_;
};

}
#endif
