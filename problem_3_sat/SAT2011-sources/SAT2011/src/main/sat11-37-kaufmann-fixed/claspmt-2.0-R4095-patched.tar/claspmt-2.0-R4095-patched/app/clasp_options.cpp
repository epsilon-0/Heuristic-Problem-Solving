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
#include "clasp_options.h"
#include "program_opts/typed_value.h"  
#include "program_opts/composite_value_parser.h"  // pair and vector
#include <clasp/satelite.h>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace ProgramOptions;
using namespace std;

namespace Clasp { 
/////////////////////////////////////////////////////////////////////////////////////////
// Parseing & Mapping of options
/////////////////////////////////////////////////////////////////////////////////////////
// a little helper to make parsing more comfortable
template <class T>
inline bool parse(const std::string& str, T& out) {
	return ProgramOptions::DefaultParser<T>::parse(str, out);
}

// maps positional options to options number or file
bool parsePositional(const std::string& t, std::string& out) {
	int num;
	if   (parse(t, num)) { out = "number"; }
	else                 { out = "file";   }
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Clasp specific basic options
/////////////////////////////////////////////////////////////////////////////////////////
BasicOptions::BasicOptions() : timeout(-1), quiet(-1,-1), stats(0), outf(0), ifs(' ') {}
void BasicOptions::initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden) {
	OptionGroup basic("Basic Options");
	basic.addOptions()
		("stats"      , storeTo(stats)->implicitValue("1"), "Print extended statistics")
		("quiet,q"    , storeTo(quiet)->implicitValue("3,3"), 
			"Configure printing of models and optimize values\n"
			"      <m>: print models          (0=all, 1=best/last, 2=no)\n"
			"      <o>: print optimize values (0=all, 1=best, 2=no)", "<m,o>")
		("outf", storeTo(outf), "Output in (0) default, (1) recent competition, (2) JSON format")
		("time-limit" , storeTo(timeout), "Set time limit to %A seconds", "<n>")
	;
	hidden.addOptions()
		("ifs", storeTo(ifs, &BasicOptions::mapIfs), "Internal field separator\n")
	;
	root.add(basic);
}

bool BasicOptions::mapIfs(const std::string& s, char& ifs) {
	if (s.empty() || s.size() > 2) return false;
	ifs = s[0];
	if (ifs == '\\' && s.size() > 1) {
		ifs = s[1];
		switch (ifs) {
			case 't' : ifs = '\t'; break;
			case 'n' : ifs = '\n'; break;
			case '\\': ifs = '\\'; break;
			case 'v' : ifs = '\v'; break;
		}
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Clasp specific mode options
/////////////////////////////////////////////////////////////////////////////////////////
void GeneralOptions::initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden) {
#ifndef DISABLE_MULTI_THREADING
	OptionGroup threadOps("Clasp - Thread Options");
	threadOps.addOptions() 
		("create-template,g" , flag(thread->genTemplate), "Generate a template portfolio file and exit")
		("threads,t", lazy<int>(this, &GeneralOptions::mapThreads)->defaultValue("1")->state(Value::value_defaulted), 
			"Number of threads to use\n"
			"      Default: %D / Valid: 0 <= %A < 64", "<n>")
		("portfolio,p", storeTo(thread->portfolio), 
			"Portfolio file to use for all but the master thread", "<file>")
		("force-gp", flag(thread->forceGP), 
			"Force guiding path scheme even if portfolio is used\n")
		("copy-problem", flag(thread->distribute.copyProblem), 
			"Copy (instead of share) problem between threads\n")
		("global-restarts", custom(this, &GeneralOptions::mapCustom)->defaultValue("0")->state(Value::value_defaulted),
		 "Configure global restart policy\n"
		 "      Default: %D / Valid: <n>[,strat>]\n"
		 "        <n> : Maximal number of global restarts (0=disable)\n"
		 "     <strat>: Restart strategy (see --restarts)\n", "<arg>")
		("distribute", custom(this, &GeneralOptions::mapCustom)->defaultValue("no")->state(Value::value_defaulted),
			"Configure nogood distribution\n"
			"      Default: %D\n"
			"      Valid:   <type>[,<lbd>]\n"
			"        <type> : Nogoods to distribute (no, all, short, conflict, loop)\n"
			"        <lbd>  : Distribute only if lbd <= <lbd>")
		("integrate", custom(this, &GeneralOptions::mapCustom)->defaultValue("gp,1024")->state(Value::value_defaulted),
			"Configure nogood integration\n"
			"      Default: %D\n"
			"      Valid:   <pick>[,<grace>]\n"
			"        <pick>  : Selector to apply (all, unsat, gp, heuristic)\n"
			"        <grace> : Keep at least last <grace> shared nogoods")
	;
#endif
	OptionGroup general("Clasp - General Options");
	general.addOptions()
		("number,n", storeTo(global->numModels)->defaultValue("1")->state(Value::value_defaulted), 
			"Enumerate at most %A models (0 for all)\n"
			"      Default: %D (0 when optimizing/computing consequences)", "<n>")
		("solution-recording", flag(global->record)        , "Add conflicts for computed models")
		("restart-on-model"  , flag(global->restartOnModel), "Restart (instead of backtrack) after each model")
		("project"           , flag(global->project)       , "Project models to named atoms in enumeration mode\n")
		
		("brave"    , flag(global->brave)   , "Compute brave consequences")
		("cautious" , flag(global->cautious), "Compute cautious consequences\n")

		("pre" , flag(global->onlyPre), "Run ASP preprocessor and exit")
 
		("opt-ignore" , flag(global->opt.no) , "Ignore minimize statements")
		("opt-heuristic" , storeTo(global->opt.heu)->implicitValue("1"), "Consider minimize statements in heuristics")
		("opt-hierarch", storeTo(global->opt.hierarch)->implicitValue("1"), "Enable hierarchical optimization")
		("opt-all"    , lazy<vector<int> >(this, &GeneralOptions::mapVec), "Compute all models <= %A", "<opt>")
		("opt-value"  , lazy<vector<int> >(this, &GeneralOptions::mapVec), 
			"Initialize objective function(s)\n"
			"      Valid:   <n1[,n2,n3,...]>\n")
		
		("supp-models",flag(global->supported), "Compute supported models (no unfounded set check)\n")
		
		("trans-ext", storeTo(global->transExt, &GeneralOptions::parseExtRule)->defaultValue("no")->state(Value::value_defaulted),
			"Configure handling of Lparse-like extended rules\n"
			"      Default: %D\n"
			"      Valid:   all, choice, card, weight, integ, dynamic, no (0)\n"
			"        all    : Transform all extended rules to basic rules\n"
			"        choice : Transform choice rules, but keep cardinality and weight rules\n"
			"        card   : Transform cardinality rules, but keep choice and weight rules\n"
			"        weight : Transform cardinality and weight rules, but keep choice rules\n"
			"        integ  : Transform cardinality integrity constraints\n"
			"        dynamic: Transform \"simple\" extended rules, but keep more complex ones\n"
			"        no     : Do not transform extended rules\n")

		("eq", storeTo(global->eq.iters)->defaultValue("5")->state(Value::value_defaulted), 
			"Configure equivalence preprocessing\n"
			"      Default: %D\n"
			"      Valid:\n"
			"        -1 : Run to fixpoint\n"
			"        0  : Do not run equivalence preprocessing\n"
			"        > 0: Run for at most %A iterations", "<n>")
		("backprop",flag(global->eq.backprop), "Enable backpropagation in ASP-preprocessing\n")
		
		("sat-prepro", lazy<std::vector<int> >(this, &GeneralOptions::mapVec)->implicitValue("-1")->defaultValue("0")->state(Value::value_defaulted),
			"Configure SatELite-like preprocessing\n"
			"      Default: %D / Implicit: -1\n"
			"      Valid: <n1[,n2,n3,n4,n5]> (0=disable)\n"
			"        <n1>: Run for at most <n1> iterations           (-1=run to fixpoint)\n"
			"        <n2>: Run variable elimination with cutoff <n2> (-1=no cutoff)\n"
			"        <n3>: Run for at most <n3> seconds              (-1=no time limit)\n"
			"        <n4>: Disable if <n4>%% of vars are frozen       (-1=no limit)\n"
			"        <n5>: Run blocked clause elimination (0=no,1=limited,2=full)","<arg>")
	;
#ifndef DISABLE_MULTI_THREADING
	root.add(threadOps);
#endif
	root.add(general);
	hidden.addOptions()
		("project-opt", storeTo(global->projectOpts), "Additional options for projection as octal digit\n")
		("dfs-eq"     , flag(global->eq.dfOrder)    , "Enable df-order in eq-preprocessing\n")
	;
}

bool GeneralOptions::parseExtRule(const std::string& s, GlobalOptions::ExtRuleMode& i){
	std::string temp = toLower(s);
	bool b = temp == "all";
	if ( b || parse(s, b)) {
		i = b ? ProgramBuilder::mode_transform : ProgramBuilder::mode_native;
		return true;
	}
	else if (temp == "choice")  { i = ProgramBuilder::mode_transform_choice; return true; }
	else if (temp == "card")    { i = ProgramBuilder::mode_transform_card; return true; }
	else if (temp == "weight")  { i = ProgramBuilder::mode_transform_weight; return true; }
	else if (temp == "integ")   { i = ProgramBuilder::mode_transform_integ; return true; }
	else if (temp == "dynamic") { i = ProgramBuilder::mode_transform_dynamic; return true; }
	return false;
}

bool GeneralOptions::mapThreads(GeneralOptions* this_, const std::string&, const int* v) {
	this_->thread->setThreads( *v );
	return false;
}

bool GeneralOptions::mapVec(GeneralOptions* this_, const std::string& n, const std::vector<int>* v) {
	if (n == "sat-prepro") {
		if (!v->empty() && v->at(0) != 0) {
			SatElite::SatElite* pre = new SatElite::SatElite();
			pre->options.maxIters = v->size()>0 ? v->at(0) : -1;
			pre->options.maxOcc   = v->size()>1 ? v->at(1) : -1;
			pre->options.maxTime  = v->size()>2 ? v->at(2) : -1;
			pre->options.maxFrozen= v->size()>3 && v->at(3) > 0 ? (v->at(3)/100.0) : 1.0;
			if (v->size() > 4 && v->at(4) >= 0) {
				pre->options.bce    = (uint32)v->at(4);
			}
			this_->global->ctx.satPrepro.reset(pre);
		}
		this_->satPreDefault = false;
	}
	else if (n == "opt-all" || !this_->global->opt.all) {
		this_->global->opt.vals.assign(v->begin(), v->end());
		this_->global->opt.all = (n == "opt-all");
	}
	return false; // delete v on return
}

bool GeneralOptions::mapCustom(GeneralOptions* this_, const std::string& key, const std::string* value) {
	std::pair<std::string, int> parsed;
	ThreadOptions::Distribution& opts = this_->thread->distribute;
	if (key == "distribute") {
		parsed.second = 2;
		if (!parse(*value, parsed)) { return false; }
		if      (parsed.first == "all")      opts.types = (Constraint_t::learnt_conflict | Constraint_t::learnt_loop);
		else if (parsed.first == "no")       opts.types = 0;
		else if (parsed.first == "short")    opts.types = Constraint_t::max_value+1;
		else if (parsed.first == "conflict") opts.types = Constraint_t::learnt_conflict;
		else if (parsed.first == "loop")     opts.types = Constraint_t::learnt_loop;
		else                                 return false;
		opts.lbd = static_cast<uint8>(parsed.second);
		return true;
	}
	else if (key == "integrate") {
		parsed.second = 1024;
		if (!parse(*value, parsed)) { return false; }
		if      (parsed.first == "all")       opts.filter = ThreadOptions::Distribution::filter_no;
		else if (parsed.first == "gp")        opts.filter = ThreadOptions::Distribution::filter_gp;
		else if (parsed.first == "unsat")     opts.filter = ThreadOptions::Distribution::filter_sat;
		else if (parsed.first == "heuristic") opts.filter = ThreadOptions::Distribution::filter_heuristic;
		else                       return false;
		opts.grace = static_cast<uint32>(parsed.second);
		return true;
	}
	else if (key == "global-restarts") {
		std::pair<int, std::vector<double> > arg; arg.first = 0;
		if (parse(*value, arg)) {
			arg.second.resize(3, 0.0);
			this_->thread->restarts.maxR     = uint32(arg.first);
			this_->thread->restarts.sched.init(uint32(arg.second[0]), arg.second[1], uint32(arg.second[2]));
			return true;
		}
		return false;
	}
	else {
		return false; // value is not valid
	}
}

bool GeneralOptions::validateOptions(const ProgramOptions::ParsedOptions& vm, Messages& m) {
	if (vm.count("opt-value") && vm.count("opt-all")) {
		m.warning.push_back("'opt-all' and 'opt-value' are mutually exclusive!");
	}
	if (global->supported && vm.count("eq") == 0) {
		global->eq.disable();
	}
	if (!thread->portfolio.empty()) {
		std::ifstream test(thread->portfolio.c_str());
		if (!test) {
			m.error = "Could not open portfolio file '";
			m.error += thread->portfolio;
			m.error += "'";
			return false;
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Clasp specific search options
/////////////////////////////////////////////////////////////////////////////////////////
void SearchOptions::initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden) {
	OptionGroup search("Clasp - Search Options");
	search.addOptions()
		("no-lookback"   , flag(this, &SearchOptions::mapFlag), "Disable lookback strategies (learning, restarts,...)\n")
		("lookahead"     , storeTo(local->heuristic().lookahead, &SearchOptions::parseLookahead)->implicitValue("atom")->defaultValue("no")->state(Value::value_defaulted),
			"Configure failed-literal detection (fld)\n"
			"      Default: %D (atom, if --nolookback)\n"
			"      Valid:   atom, body, hybrid, no (0)\n"
			"        atom  : Apply failed-literal detection to atoms\n"
			"        body  : Apply failed-literal detection to bodies\n"
			"        hybrid: Apply Nomore++-like failed-literal detection\n"
			"        no (0): Do not apply failed-literal detection", "<arg>")
		("initial-lookahead", storeTo(local->heuristic().lookaheadNum), "Restrict fld to %A decisions\n", "<n>")

		("heuristic", storeTo(local->heuristic().name, &SearchOptions::parseHeuristic)->defaultValue("Berkmin")->state(Value::value_defaulted), 
			"Configure decision heuristic\n"
			"      Default: %D (Unit, if --no-lookback)\n"
			"      Valid:   Berkmin, Vmtf, Vsids, Unit, None\n"
			"        Berkmin: Apply BerkMin-like heuristic\n"
			"        Vmtf   : Apply Siege-like heuristic\n"
			"        Vsids  : Apply Chaff-like heuristic\n"
			"        Unit   : Apply Smodels-like heuristic\n"
			"        None   : Select the first free variable")
		("rand-freq", lazy<double>(this, &SearchOptions::mapRandFreq)->defaultValue("0.0")->state(Value::value_defaulted), 
			"Make random decisions with probability %A\n"
			"      Default: %D\n"
			"      Valid:   [0.0...1.0]\n", "<p>")

		("rand-prob", custom(this, &SearchOptions::mapRandProb)->implicitValue("50,20")->defaultValue("no")->state(Value::value_defaulted),
			"Configure random probing\n"
			"      Default: %D / Implicit: 50,20\n"
			"      Valid:   no (0), <n1,n2> (<n1> >= 0, <n2> > 0)\n"
			"        no     : Do not run random probing\n"
			"        <n1,n2>: Run <n1> random passes up to at most <n2> conflicts each\n", "<n1,n2>")
		("rand-watches", flag(this, &SearchOptions::mapFlag)->defaultValue("true")->state(Value::value_defaulted),
			"Configure watched literal initialization\n"
			"      Default: %D\n"
			"      Valid:   yes (1), no (0)\n"
			"        yes: Randomly determine watched literals\n"
			"        no : Watch first and last literal in a nogood")
		("seed"    , lazy<int>(this, &SearchOptions::mapInt),    "Set random number generator's seed to %A\n", "<n>")
		("search-limit", custom(this, &SearchOptions::mapLimits), "Terminate search after <n> conflicts or <m> restarts\n", "<n,m>")
	;
	
	OptionGroup lookback("Clasp - Lookback Options");
	lookback.addOptions()
		("restarts,r", custom(this, &SearchOptions::mapCustom)->defaultValue("100,1.5")->state(Value::value_defaulted),
			"Configure restart policy\n"
			"      Default: %D\n"
			"      Valid:   <n1[,n2,n3]> (<n1> >= 0, <n2>,<n3> > 0), no\n"
			"        <n1>          : Run Luby et al.'s sequence with unit length <n1>\n"
			"        <n1>,<n2>     : Run geometric sequence of <n1>*(<n2>^i) conflicts\n"
			"        <n1>,<n2>,<n3>: Run Biere's inner-outer geometric sequence (<n3>=outer)\n"
			"        <n1> = 0, no  : Disable restarts")
		("local-restarts"  , flag(local->solve.restart.local), "Enable Ryvchin et al.'s local restarts")
		("bounded-restarts", flag(local->solve.restart.bounded), "Enable (bounded) restarts during model enumeration")
		("reset-restarts",   flag(local->solve.restart.resetOnModel), "Reset restart strategy during model enumeration")
		("save-progress"   , storeTo(solverOpts->saveProgress)->implicitValue("1"), "Enable RSat-like progress saving on backjumps > %A\n", "<n>")

		("shuffle,s", custom(this, &SearchOptions::mapCustom)->defaultValue("0,0")->state(Value::value_defaulted),
			"Configure shuffling after restarts\n"
			"      Default: %D\n"
			"      Valid:   <n1,n2> (<n1> >= 0, <n2> >= 0)\n"
			"        <n1> > 0: Shuffle problem after <n1> and re-shuffle every <n2> restarts\n"
			"        <n1> = 0: Do not shuffle problem after restarts\n"
			"        <n2> = 0: Do not re-shuffle problem\n", "<n1,n2>")

		("deletion,d", custom(this, &SearchOptions::mapCustom)->defaultValue("3.0,1.1,3.0")->state(Value::value_defaulted), 
			"Configure size of learnt nogood database\n"
			"      Default: %D\n"
			"      Valid:   <n1[,n2,n3]> (<n3> >= <n1> >= 0, <n2> >= 1.0), no\n"
			"        <n1,n2,n3>: Store at most min(P/<n1>*(<n2>^i),P*<n3>) learnt nogoods,\n"
			"                    P and i being initial problem size and number of restarts\n"
			"        no        : Do not delete learnt nogoods")
		("reduce-on-restart", flag(local->solve.reduce.reduceOnRestart), "Delete some learnt nogoods after every restart\n")
		("estimate", flag(local->solve.reduce.estimate), "Use estimated problem complexity to init learnt db\n")

		("strengthen", storeTo(solverOpts->cflMinAntes, &SearchOptions::parseAntes)->defaultValue("yes")->state(Value::value_defaulted),
			"Configure conflict nogood strengthening\n"
			"      Default: %D\n"
			"      Valid:   bin, tern, yes (1), no (0)\n"
			"        bin : Check only binary antecedents for self-subsumption\n"
			"        tern: Check binary and ternary antecedents for self-subsumption\n"
			"        yes : Check all antecedents for self-subsumption\n"
			"        no  : Do not check antecedents for self-subsumption")
		("recursive-str", flag(solverOpts->strengthenRecursive), "Enable MiniSAT-like conflict nogood strengthening\n")
		
		("loops", storeTo(local->loopRep, &SearchOptions::parseLoops)->defaultValue("common")->state(Value::value_defaulted),
			"Configure representation/learning of loop formulas\n"
			"      Default: %D\n"
			"      Valid:   common, distinct, shared, no\n"
			"        common  : Create loop nogoods for atoms in an unfounded set\n"
			"        distinct: Create distinct loop nogood for each atom in an unfounded set\n"
			"        shared  : Create loop formula for a whole unfounded set\n"
			"        no      : Do not learn loop formulas\n")


		("contraction", lazy<int>(this, &SearchOptions::mapInt)->defaultValue("250")->state(Value::value_defaulted),
			"Configure (temporary) contraction of learnt nogoods\n"
			"      Default: %D\n"
			"      Valid:\n"
			"        0  : Do not contract learnt nogoods\n"
			"        > 0: Contract learnt nogoods containing more than %A literals\n", "<n>")
	;

	hidden.addOptions()
		("loops-in-heu", storeTo(local->heuristic().loops), "Consider loop nogoods in heuristic")
		("berk-max", storeTo(local->heuristic().extra.berkMax), "Consider at most <n> nogoods in Berkmin")
		("berk-moms", flag(local->heuristic().berkMoms), "Enable/Disable MOMs in Berkmin")
		("berk-huang",flag(local->heuristic().berkHuang), "Enable/Disable Huang-scoring in Berkmin")
		("berk-once",flag(local->heuristic().berkOnce), "Score sets (instead of multisets) in Berkmin")
		("vmtf-mtf",storeTo(local->heuristic().extra.vmtfMtf), "In Vmtf move up to <n> conflict-literals to the front")
		("nant",flag(local->heuristic().nant), "In Unit count only atoms in NAnt(P)")
		("reverse-arcs",storeTo(solverOpts->reverseArcs), "Enable reverse-arc learning")
		("otfs",storeTo(solverOpts->otfs)->implicitValue("1"), "Enable on-the-fly subsumption")
		("dinit",custom(this, &SearchOptions::mapCustom), "Set initial min/max learnt db size")
		("dfrac", custom(this, &SearchOptions::mapCustom), "Set fraction of nogoods to delete on reduction")
		("dsched", custom(this, &SearchOptions::mapCustom), "Set alternative deletion schedule (see restarts)")
		("dalgo", storeTo(solverOpts->reduceAlgo), "Use (0) basic, (1) sorted-in-place, (2) sorted deletion")
		("dscore", storeTo(solverOpts->reduceScore), "Use (0) activity, (1) lbd, (2) combined scores")
		("dglue", storeTo(solverOpts->reduceGlue), "Don't delete constraints with lbd <= x")
		("update-lbd", flag(solverOpts->updateLbd), "Dynamically update lbds?")
	;
	root.add(search);
	root.add(lookback);
}

bool SearchOptions::parseHeuristic(const std::string& s, std::string& out) {
	std::string temp = toLower(s);
	if      (temp == "berkmin")   { out = temp; return true; }
	else if (temp == "vmtf")      { out = temp; return true; }
	else if (temp == "vsids")     { out = temp; return true; }
	else if (temp == "unit")      { out = temp; return true; }
	else if (temp == "none")      { out = temp; return true; }
	return false;
}

bool SearchOptions::parseLoops(const std::string& s, LocalOptions::LoopMode& i) {
	std::string temp = toLower(s);
	bool b = temp == "common";
	if (b || parse(s, b)) {
		i = b ? DefaultUnfoundedCheck::common_reason : DefaultUnfoundedCheck::only_reason;
		return true;
	}
	else if (temp == "shared")    { i = DefaultUnfoundedCheck::shared_reason; return true; }
	else if (temp == "distinct")  { i = DefaultUnfoundedCheck::distinct_reason; return true; }
	return false;
}

bool SearchOptions::parseLookahead(const std::string& s, HeuristicOptions::LookaheadType& i) {
	std::string temp = toLower(s);
	bool b;
	if (parse(s, b)) {
		i = b ? Lookahead::atom_lookahead : Lookahead::no_lookahead;
		return true;
	}
	else if (temp == "atom")      { i = Lookahead::atom_lookahead; return true; }
	else if (temp == "body")      { i = Lookahead::body_lookahead; return true; }
	else if (temp == "hybrid")    { i = Lookahead::hybrid_lookahead; return true; }
	return false;
}

bool SearchOptions::parseAntes(const std::string& s, SolverStrategies::CflMinAntes& i) {
	std::string temp = toLower(s);
	bool b = temp == "all";
	if (b || parse(s, b)) {
		i = b ? SolverStrategies::all_antes : SolverStrategies::no_antes;
		return true;
	}
	else if (temp == "bin")   { i = SolverStrategies::binary_antes; return true; }
	else if (temp == "tern")  { i = SolverStrategies::binary_ternary_antes; return true; }
	return false;
}

bool SearchOptions::mapRandFreq(SearchOptions* this_, const std::string&, const double* v) {
	this_->solveOpts->setRandomProbability(*v);
	return false;
}

bool SearchOptions::mapRandProb(SearchOptions* this_, const std::string&, const std::string* value) {
	std::pair<int, int> r(0, 0);
	if (parse(*value, r) || *value == "no") {
		this_->solveOpts->setRandomizeParams(r.first, r.second);
		return true;
	}
	return false;
}

bool SearchOptions::mapFlag(SearchOptions* this_, const std::string& n, const bool* val) {
	if (n == "rand-watches") {
		this_->solverOpts->randomWatches = *val;
	}
	else if (n == "no-lookback" && *val) {
		this_->solverOpts->search = Clasp::SolverStrategies::no_learning;
	}
	return false;
}

bool SearchOptions::mapInt(SearchOptions* this_, const std::string& n, const int* val) {
	if (n == "seed") {
		this_->solverOpts->rng.srand(static_cast<uint32>(*val));	
	}
	else if (n == "contraction") {
		this_->solverOpts->setCompressionStrategy(static_cast<uint32>(*val));
	}
	return false;
}

bool SearchOptions::mapCustom(SearchOptions* this_, const std::string& n, const std::string* value) {
	if (n == "restarts" || n == "deletion" || n == "dsched") {
		std::vector<double> v;
		ScheduleStrategy* sched = 0;
		if (n != "deletion") {
			sched = n[0] == 'r' 
				? &this_->solveOpts->restart.sched 
				: &this_->solveOpts->reduce.sched;
		}
		if (parse(*value, v)) {
			if (sched) {
				v.resize(3, 0.0);
				sched->init(uint32(v[0]), v[1], uint32(v[2]));
			}
			else {
				if (v.empty())  v.push_back(3.0);
				if (v.size()==1)v.push_back(1.1);
				if (v.size()==2)v.push_back(3.0);
				this_->solveOpts->reduce.setStrategy(v[0], v[1], v[2]);
			}
			return true;
		}
		else if (*value == "no") {
			if   (sched) { sched->init(0,0,0); }
			else         { this_->solveOpts->reduce.disable = true;     }
		}
		else { return false; }
		return true;
	}
	else if (n == "shuffle") {
		std::pair<int, int> shuf;
		if (parse(*value, shuf)) {
			this_->solveOpts->setShuffleParams(shuf.first, shuf.second);
			return true;
		}
	}
	else if (n == "dinit") {
		std::pair<int, int> init(0, -1);
		if (parse(*value, init)) {
			this_->solveOpts->reduce.setInit((uint32)init.first, (uint32)init.second);
			return true;
		}
	}
	else if (n == "dfrac") {
		double f = .75;
		if (parse(*value, f)) {
			this_->solveOpts->reduce.setReduceFraction(f);
			return true;
		}
	}
	return false;
}

bool SearchOptions::mapLimits(SearchOptions* this_, const std::string&, const std::string* value) {
	std::pair<int, int> p(-1,-1);
	if (parse(*value, p)) {
		this_->local->solve.limits = SearchLimits(static_cast<uint64>(p.first), static_cast<uint64>(p.second));
		return true;
	}
	return false;
}
	
bool SearchOptions::validateOptions(const ProgramOptions::ParsedOptions& vm, Messages& m) {
	if (solverOpts->search == Clasp::SolverStrategies::no_learning) {	
		if (vm.count("heuristic") == 0) { local->heuristic().name = "unit"; }
		if (vm.count("lookahead") == 0) { local->heuristic().lookahead = Lookahead::atom_lookahead; }
		bool warn = local->solve.restart.local || local->solve.restart.bounded || local->solve.reduce.reduceOnRestart;
		if (warn || vm.count("restarts") || vm.count("deletion") || vm.count("rand-prob") || vm.count("shuffle")) {
			m.warning.push_back("lookback-options ignored because lookback strategy is not used!");     
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
// clasp option validation
/////////////////////////////////////////////////////////////////////////////////////////
void ClaspOptions::setConfig(ClaspConfig* config) {
	assert(config && "clasp options: config must not be 0!\n");
	mode.global   = &config->global;
	mode.thread   = &config->thread;
	search.local  = config->thread.master();
	this->config  = config;      
	search.solverOpts = &search.local->solver().strategies();
	search.solveOpts  = &search.local->solve;
}
void ClaspOptions::initOptions(ProgramOptions::OptionContext& root, ProgramOptions::OptionGroup& hidden) {
	if (mode.global == 0) {
		throw std::runtime_error("clasp options: config not set!");
	}
	mode.initOptions(root, hidden);
	search.initOptions(root, hidden);
	basic.initOptions(root, hidden);
}

bool ClaspOptions::validateOptions(const ProgramOptions::ParsedOptions& vm, Messages& m) {
	if (mode.validateOptions(vm, m) && search.validateOptions(vm, m)) {
		if (config->thread.numThreads() > 1) {
			if (config->thread.portfolio.empty()) {
				config->thread.forceGP = true;
				for (uint32 i = 1; i < config->thread.numThreads(); ++i) {
					config->thread.threadConfig(i)->initFrom(*config->thread.threadConfig(0));
				}
			}
			else {
				std::ifstream portfolio(config->thread.portfolio.c_str());
				populateThreadConfigs(portfolio, vm, m);
			}
		}
		return config->validate(m.error);
	}
	return false;
}

void ClaspOptions::applyDefaults(Input::Format f) {
	if (f != Input::SMODELS && mode.satPreDefault) {
		SatElite::SatElite* pre = new SatElite::SatElite();
		pre->options.maxIters = 20;
		pre->options.maxOcc   = 25;
		pre->options.maxTime  = 120;
		pre->options.maxFrozen= 1.0;
		mode.global->ctx.satPrepro.reset(pre);		
	}
}

bool ClaspOptions::populateThreadConfigs(std::istream& in, const ProgramOptions::ParsedOptions& vm, Messages& m) {
	StringSeq configs;
	for (std::string line; std::getline(in, line); ) {
		if (line.empty()) continue;
		if (line[0] == '[') {
			configs.push_back(line);
			if ((uint32)configs.size() == config->thread.numThreads()) {
				break;
			}
		}
		else if (line[0] != '#') {
			m.error = "Portfolio file has unrecognized format!";
			return false;
		}
	}		
	if (configs.empty()) {
		configs.push_back("");
	}
	bool addSeed = false;
	for (uint32 x = 0, i = 0; i != config->thread.numThreads(); ++i) {
		if (!parseConfig(configs[x], i, vm, m)) {
			return false;
		}
		if (addSeed) {
			config->thread.threadConfig(i)->solver().strategies().rng.srand(i);
		}
		if (++x == (uint32)configs.size()) {
			x = 0;
			addSeed = true;
		}		
	}
	return true;
}

bool ClaspOptions::parseConfig(const std::string& in, uint32 id, const ProgramOptions::ParsedOptions& vm, Messages& m) {
	std::string::size_type pos = in.find("]:");
	std::string configOpts, configName;
	if (pos != std::string::npos) {
		configName.assign(in.begin()+1, in.begin()+pos);
		if ( (pos = in.find_first_not_of(' ', pos+2)) == std::string::npos ) {
			pos = in.size();
		}
		configOpts.assign(in.begin()+pos, in.end());
	}
	else {
		configOpts = in;
	}
	try {
		ProgramOptions::OptionContext root;
		ProgramOptions::OptionGroup   hidden = ProgramOptions::OptionGroup::createHidden();
		SearchOptions opts;
		opts.local     = config->thread.threadConfig(id);
		opts.solveOpts = &opts.local->solve;
		opts.solverOpts= &opts.local->solver().strategies();
		opts.initOptions(root, hidden);
		root.add(hidden);
		// 1. all from command-line
		ProgramOptions::ParsedOptions parsed(vm);
		// 2. all from current config
		parsed.assign(ProgramOptions::parseCommandString(configOpts, root));
		// 3. any defaults
		root.assignDefaults(parsed);
		if (!opts.validateOptions(parsed, m)) {
			return false;
		}
	}
	catch(const std::exception& e) {
		std::string err("Config '");
		err += configName;
		err += "': ";
		err += e.what();
		throw std::runtime_error(err);
	}
	return true;
}
}
