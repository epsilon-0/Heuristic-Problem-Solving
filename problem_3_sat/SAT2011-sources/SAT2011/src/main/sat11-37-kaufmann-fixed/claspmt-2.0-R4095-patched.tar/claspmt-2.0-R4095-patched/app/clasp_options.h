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
#ifndef CLASP_CLASP_OPTIONS_H_INCLUDED
#define CLASP_CLASP_OPTIONS_H_INCLUDED

#ifdef _MSC_VER
#pragma warning (disable : 4200) // nonstandard extension used : zero-sized array
#pragma once
#endif

#include <string>
#include <utility>
#include <program_opts/app_options.h>
#include <clasp/clasp_facade.h>
#include <clasp/solver.h>
#include <iosfwd>

namespace Clasp {

/////////////////////////////////////////////////////////////////////////////////////////
// Option groups - Mapping between command-line options and libclasp objects
/////////////////////////////////////////////////////////////////////////////////////////
// Function for mapping positional options
bool parsePositional(const std::string& s, std::string& out);

// Group "Basic Options"
struct BasicOptions {
	BasicOptions();
	typedef std::pair<int, int> QPair;
	static bool mapIfs(const std::string& s, char& ifs);
	void initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden);
	int         timeout;// timeout in seconds (default: none=-1)
	QPair       quiet;  // configure printing of models and optimization values
	int         stats;  // print statistics
	int         outf;   // output format
	char        ifs;    // field separator
	enum OutputFormat {
		out_def     = 0,
		out_comp    = 1,
		out_json    = 2
	};
};

// Group "Clasp - General Options"
// Options of this group are mapped to ClaspConfig::api
// and ClaspConfig::enumerate
struct GeneralOptions {
	GeneralOptions() : global(0), satPreDefault(true) {}
	static bool mapVec(GeneralOptions*, const std::string&, const std::vector<int>* v);
	static bool mapCustom(GeneralOptions*, const std::string& k, const std::string* v);
	static bool mapThreads(GeneralOptions*, const std::string&, const int* v);
	static bool parseExtRule(const std::string& s, GlobalOptions::ExtRuleMode& i);
	void initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden);
	bool validateOptions(const ProgramOptions::ParsedOptions& parsed, Messages&);
	GlobalOptions* global;
	ThreadOptions* thread;
	bool           satPreDefault;
};

// Groups "Clasp - Search Options" and "Clasp - Lookback Options"
// Options of these groups are mapped to ClaspConfig::solve 
// and ClaspConfig::solver
struct SearchOptions {
	SearchOptions() : local(0), solverOpts(0), solveOpts(0) {}
	void initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden);
	bool validateOptions(const ProgramOptions::ParsedOptions& parsed, Messages&);
	// value parsing 
	static bool parseHeuristic(const std::string& s, std::string&);
	static bool parseLookahead(const std::string& s, HeuristicOptions::LookaheadType& i);
	static bool parseAntes(const std::string& s, SolverStrategies::CflMinAntes& i);
	static bool parseLoops(const std::string& s, LocalOptions::LoopMode& i);
	// value mapping
	static bool mapCustom(SearchOptions*, const std::string&, const std::string* v);
	static bool mapFlag(SearchOptions* this_, const std::string& flag, const bool* val);
	static bool mapInt(SearchOptions* this_, const std::string& key, const int* val);
	static bool mapRandFreq(SearchOptions* this_, const std::string& s, const double* val);
	static bool mapRandProb(SearchOptions* this_, const std::string& key, const std::string* value);
	static bool mapLimits(SearchOptions* this_, const std::string& key, const std::string* value);
	LocalOptions*      local;
	SolverStrategies*  solverOpts;
	SolveParams*       solveOpts;
};

// Combines all groups and drives initialization/validation 
// of command-line options.
class ClaspOptions {
public:
	ClaspOptions() {}
	BasicOptions   basic;
	// Sets the configuration object in which parsed options are stored.
	// Must be called once before option parsing begins
	void setConfig(ClaspConfig* config);

	void initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden);
	bool validateOptions(const ProgramOptions::ParsedOptions& parsed, Messages&);
	void applyDefaults(Input::Format f);
private:
	bool populateThreadConfigs(std::istream& in, const ProgramOptions::ParsedOptions& parsed, Messages&);
	bool parseConfig(const std::string& str, uint32 id, const ProgramOptions::ParsedOptions& parsed, Messages&);
	GeneralOptions mode;
	SearchOptions  search;
	ClaspConfig*   config;
};

}
#endif

