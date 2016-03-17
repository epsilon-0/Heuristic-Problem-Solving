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
#include <program_opts/app_options.h>
#include <program_opts/typed_value.h>
#include <program_opts/composite_value_parser.h>
#include <cctype>
#include <limits.h>
#include <cstring>

using namespace ProgramOptions;
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
// Generic Options - independent of concrete system
/////////////////////////////////////////////////////////////////////////////////////////
GenericOptions::GenericOptions() 
	: verbose(0)
	, help(false)
	, version(false) {}

void GenericOptions::initOptions(OptionContext& root, OptionGroup& hidden) {
	OptionGroup basic("Basic Options");
	basic.addOptions()
		("help,h"   , flag(help),    "Print help information and exit")
		("version,v", flag(version), "Print version information and exit")    
		("verbose,V", storeTo(verbose)->implicitValue(LIT_TO_STRING(INT_MAX)), "Verbosity level", "<n>")
	;
	root.add(basic);
	hidden.addOptions()
		("file,f", storeTo(input)->composing(), "Input files\n")
	;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Parsing & Validation of command line
/////////////////////////////////////////////////////////////////////////////////////////
bool AppOptions::parse(int argc, char** argv, const char* appName, ProgramOptions::PosOption p) {
	ParsedOptions parsed;
	try {
		OptionContext  allOpts("Application Options");
		OptionGroup hidden = OptionGroup::createHidden();
		generic.initOptions(allOpts, hidden);
		initOptions(allOpts, hidden);
		messages.clear();
		allOpts.add(hidden);
		parsed.assign(parseCommandLine(argc, argv, allOpts, false, p));
		allOpts.assignDefaults(parsed);
		if (generic.help || generic.version) { 
			help_      = allOpts.description(0);
			defaults_  = allOpts.defaults(appName ? strlen(appName) + 1 : 2);
			return true;
		}
		return generic.validateOptions(parsed, messages) 
			&&   validateOptions(parsed, messages);
	}
	catch(const std::exception& e) {
		messages.error = e.what();
		return false;
	}
	return true;
}

bool AppOptions::parseFiles(const std::string& , std::string& out) {
	out = "file";
	return true;
}
