//
//  Copyright (c) Benjamin Kaufmann 2004
//
//  This is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version. 
// 
//  This file is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this file; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//
// NOTE: ProgramOptions is inspired by Boost.Program_options
//       see: www.boost.org/libs/program_options
//
#ifdef _MSC_VER
#pragma warning (disable : 4786)
#pragma warning (disable : 4503)
#pragma warning (disable : 4996)
#endif
#include <program_opts/program_options.h>
#include <program_opts/errors.h>
#include <program_opts/value_parser.h>
#include <cassert>
#include <cstring>
#include <climits>
#include <ostream>  // for op<<
#include <istream>  // for CfgFileParser
#include <algorithm>// std::sort
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
using namespace std;

namespace ProgramOptions { namespace detail {

static void defaultFormat(std::string& temp, const ProgramOptions::Option& o, std::size_t maxW) {
	size_t bufSize = std::max(maxW, o.maxColumn()) + 3;
	char*  buffer  = new char[bufSize];
	size_t n       = sprintf(buffer, "  --%s", o.name().c_str());
	const char* arg= o.argDescription();
	if (o.value()->isImplicit() && *arg) {
		n += sprintf(buffer+n, "[=%s]", arg);
	}
	if (o.alias()) {
		n += sprintf(buffer+n, ",-%c", o.alias());
	}
	if (!o.value()->isImplicit()) {
		n += sprintf(buffer+n, "%c%s", (!o.alias()?'=':' '), arg);
	}
	if (*o.description()) {
		if (n < maxW) n += sprintf(buffer+n, "%-*.*s", int(maxW-n), int(maxW-n), " ");
		buffer[n++] = ':';
		buffer[n++] = ' ';
		assert(n <= bufSize);
		temp.append(buffer, n);
		o.formatDescription(temp);
	}
	delete [] buffer;
}
} // namespace detail
///////////////////////////////////////////////////////////////////////////////
// class Value
///////////////////////////////////////////////////////////////////////////////
std::string Value::empty_string_s("");

Value::Value(byte_t flags, ValueState initial) : flagSet_(flags), state_(initial)  {
	extra_[default_value] = extra_[implicit_value] = 0;
}
Value::~Value() {
	release(default_value);
	release(implicit_value);
}
void Value::release(ExtraValue e) {
	byte_t f = extra2Flag(e);
	if (hasFlag(f)) {
		delete extra_[e];
		clearFlag(f);
	}
	extra_[e] = 0;
}
void Value::setExtraValue(ExtraValue e, const char* str) {
	if (!str) return;
	release(e);
	ExtraValue other = static_cast<ExtraValue>(1 - e);
	if (!*str) {
		// share empty
		extra_[e] = &empty_string_s;
	}
	else if (const FlagStr* x = FlagStr::find(str)) {
		// share with flag
		extra_[e] = &x->str;
	}
	else if (extra_[other] && *extra_[other] == str) {
		// share with other if possible
		extra_[e] = extra_[other];
	}
	else {
		// create new owned string
		extra_[e] = new std::string(str);
		setFlag( extra2Flag(e) );
	}
}
///////////////////////////////////////////////////////////////////////////////
// class Option
///////////////////////////////////////////////////////////////////////////////
Option::Option(const string& longName, char alias, const char* desc, Value* v, const char* arg)
	: name_(longName)
	, value_(v) {
	assert(v);
	assert(!longName.empty());
	if (arg == 0)  arg  = "";
	if (desc == 0) desc = "";
	// [alias|arg|0|desc|0]
	std::size_t nDesc   = strlen(desc);
	std::size_t nArg    = strlen(arg);
	std::size_t bufSize = (nDesc + nArg + 3);
	char*       buffer  = new char[bufSize];
	char*       b       = buffer;
	*b++                = alias;
	std::memcpy(b, arg, nArg*sizeof(char));
	b                  += nArg;
	*b++                = '\0';
	std::memcpy(b, desc, nDesc*sizeof(char));
	buffer[bufSize-1]   = '\0';
	description_        = buffer;
}

Option::~Option() {
	delete value_;
	delete [] description_;
}
std::size_t Option::maxColumn() const {
	std::size_t col = 4 + name_.size(); //  --name
	if (alias()) {
		col += 3; // ,-o
	}
	std::size_t argN = strlen(argDescription());
	if (argN) {
		col += (argN + 1); // =arg
		if (value()->isImplicit()) {
			col += 2; // []
		}
	}
	return col;
}

void Option::formatDescription(std::string& out) const {
	const char* desc = description();
	std::size_t minS = strlen(desc);
	std::string argD(argDescription() ? argDescription() : "");
	out.reserve(out.size() + minS);
	for (;; ++desc) {
		while (*desc && *desc != '%') {
			out += *desc++;
		}
		if (!*desc++ || !*desc) break;
		if (*desc == 'D') {
			out += value()->defaultValue();
		}
		else if (*desc == 'A') {
			out += argD;
		}
		else {
			out += *desc;
		}
	}
}

const char* Option::description() const {
	return &description_[2] + strlen(arg());
}
const char* Option::arg() const {
	return &description_[1];
}
const char* Option::argDescription() const {
	if (*arg() || value_->isImplicit()) {
		return arg();
	}
	return "<arg>";
}
bool Option::assignDefault() const {
	if (value()->hasDefault() && value()->state() != Value::value_defaulted) {
		return value()->parse(name(), value()->defaultValue(), true);
	}
	return true;
}
const std::string& Option::defaultValue() const { return value()->defaultValue(); }
///////////////////////////////////////////////////////////////////////////////
// class OptionGroup
///////////////////////////////////////////////////////////////////////////////
OptionGroup::OptionGroup(const std::string& caption) : caption_(caption) {}
OptionGroup OptionGroup::createHidden() {
	return OptionGroup(std::string("\0", 1));
}

OptionGroup::~OptionGroup() { }

OptionInitHelper OptionGroup::addOptions() {
	return OptionInitHelper(*this);
}

void OptionGroup::addOption(std::auto_ptr<Option> option) {
	SharedOptPtr opt(option.release());
	options_.push_back(opt);
}

std::size_t OptionGroup::maxColumn() const {
	std::size_t maxW = 0;
	for (option_iterator it = options_.begin(), end = options_.end(); it != end; ++it) {
		maxW = std::max(maxW, (*it)->maxColumn());
	}
	return maxW;
}

void OptionGroup::format(std::string& out, FormatFunction f, size_t maxW) const {
	if (f == 0) f = detail::defaultFormat;
	if (caption().length()) {
		out += "\n";
		out += caption();
		out += ":\n\n";
	}
	for (option_iterator it = options_.begin(), end = options_.end(); it != end; ++it) {
		f(out, **it, maxW);
		out += "\n";
	}
}
bool OptionGroup::hidden() const {
	return caption_.size() == 1 && caption_[0] == '\0';
}
///////////////////////////////////////////////////////////////////////////////
// class OptionInitHelper
///////////////////////////////////////////////////////////////////////////////
OptionInitHelper::OptionInitHelper(OptionGroup& owner)
	: owner_(&owner) { }

OptionInitHelper& OptionInitHelper::operator()(const char* name, Value* val, const char* desc, const char* extra) {
	std::auto_ptr<Value> value(val);
	if (!name || !*name) {
		throw BadOptionName("");
	}
	const char* n = strchr(name, ',');
	string longName; char shortName = 0;
	if (!n) {
		longName = name;
	}
	else {
		longName.assign(name, n);
		++n;
		if (!*n || *(n+1)) {
			// empty or too long short name
			throw BadOptionName(name);
		}
		shortName = *n;
	}
	owner_->addOption(auto_ptr<Option>(new Option(longName, shortName, desc, value.release(), extra)));
	return *this;
}
///////////////////////////////////////////////////////////////////////////////
// class OptionContext
///////////////////////////////////////////////////////////////////////////////
OptionContext::OptionContext(const std::string& cap)
	: caption_(cap) {
}
OptionContext::~OptionContext()
{}

size_t OptionContext::findGroup(const std::string& name) const {
	for (size_t i = 0; i != groups_.size(); ++i) {
		if (groups_[i].caption() == name) { return i; }
	}
	return size_t(-1);
}

OptionContext& OptionContext::add(const OptionGroup& options) {
	size_t k = findGroup(options.caption());
	if (k >= groups_.size()) {
		// add as new group
		k = groups_.size();
		groups_.push_back(OptionGroup(options.caption()));
	}
	for (option_iterator it = options.begin(), end = options.end(); it != end; ++it) {
		insertOption(k, *it);
	}
	return *this;
}

OptionContext& OptionContext::add(const OptionContext& other) {
	if (this == &other) return *this;
	for (size_t g = 0; g != other.groups_.size(); ++g) {
		add(other.groups_[g]);
	}
	return *this;
}


void OptionContext::insertOption(size_t groupId, const SharedOptPtr& opt) {
	const string& l = opt->name();
	key_type k(options_.size());
	if (opt->alias()) {
		char sName[2] = {'-', opt->alias()};
		std::string shortName(sName, 2);
		if (!index_.insert(Name2Key::value_type(shortName, k)).second) {
			throw DuplicateOption(l, caption());
		}
	}
	if (!l.empty()) {
		if (!index_.insert(Name2Key::value_type(l, k)).second) {
			throw DuplicateOption(l, caption());
		}
	}
	options_.push_back(opt);
	groups_[groupId].options_.push_back(opt);
}

OptionContext::option_iterator OptionContext::find(const char* key, FindType t) const {
	PrefixRange r = findImpl(key, t);
	if (std::distance(r.first, r.second) == 0) {
		throw UnknownOption(caption() + "::" + (key ? key : ""));
	}
	if (std::distance(r.first, r.second) > 1) {
		std::string str = "'";
		str += key;
		str += "' could be:";
		for (; r.first != r.second; ++r.first) { 
			str += "\n  " + r.first->first;
		}
		throw AmbiguousOption(str);
	}
	return options_.begin() + r.first->second;
}

OptionContext::option_iterator OptionContext::tryFind(const char* key, FindType t) const {
	PrefixRange r = findImpl(key, t);
	if (std::distance(r.first, r.second) == 0 || std::distance(r.first, r.second) > 1) {
		return end();
	}
	return options_.begin() + r.first->second;
}

OptionContext::PrefixRange OptionContext::findImpl(const char* key, FindType t) const {
	std::string k(key ? key : "");
	if (t == find_alias && !k.empty() && k[0] != '-') {
		k   += k[0];
		k[0] = '-';
	}
	index_iterator it   = index_.lower_bound(k);
	if (it != index_.end()) {
		if ( (it->first == k) && ( (t & (find_alias|find_name)) != 0 ) ) {
			return PrefixRange(it, ++index_iterator(it));
		}
		index_iterator up = it;
		if ( (t & find_prefix) != 0 ) {
			k += char(CHAR_MAX);
			up = index_.upper_bound(k);
		}
		return PrefixRange(it, up);
	}
	return PrefixRange(index_.end(), index_.end()); 
}

std::string OptionContext::description(FormatFunction f, bool addHidden) const {
	if (f == 0) f = detail::defaultFormat;
	size_t maxW = 23;
	for (size_t i = 0; i != groups(); ++i) {
		maxW = std::max(maxW, groups_[i].maxColumn());
	}
	std::string temp; temp.reserve(1024);
	std::string out;
	for (int g = 0; g < 2; ++g) {
		// print all sub-groups followed by main group
		for (std::size_t i = (g == 0), end = (g == 0) ? groups_.size() : 1; i < end; ++i) {
			temp.clear();
			if (!groups_[i].hidden() || addHidden) {
				groups_[i].format(temp, f, maxW);
			}
			out  += temp;
		}
	}
	return out;
}

std::string OptionContext::defaults(std::size_t n) const {
	std::size_t line = n, x = 0;
	std::string defs; defs.reserve(options_.size());
	for (int g = 0; g < 2; ++g) {
		// print all sub-groups followed by main group
		for (std::size_t i = (g == 0), end = (g == 0) ? groups_.size() : 1; i < end; ++i) {
			if (!groups_[i].hidden()) {
				for (option_iterator it = groups_[i].begin(), end = groups_[i].end(); it != end; ++it) {
					const Option& o = **it;
					if (o.value()->hasDefault()) {
						x = defs.size();
						defs += "--";
						defs += o.name();
						defs += '=';
						defs += o.value()->defaultValue();
						defs += ' ';
						if ( (line += (defs.size() - x)) > 64) {
							defs += '\n';
							defs.append(n, ' ');
							line = n;
						}
					}
				}
			}
		}
	}
	return defs;	
}
std::ostream& operator<<(std::ostream& os, const OptionContext& grp) {
	os << grp.description(detail::defaultFormat);
	return os;
}

bool OptionContext::assignDefaults(const ParsedOptions& opts) const {
	for (option_iterator it = begin(), end = this->end(); it != end; ++it) {
		const Option& o = **it;
		if (opts.count(o.name()) == 0 && !o.assignDefault()) {
			std::string d("'");
			d += o.defaultValue();
			d += "': invalid default value for Option '";
			d += o.name();
			d += "'";
			throw BadValue(d);	
		}
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////
// class ParsedOptions
///////////////////////////////////////////////////////////////////////////////
ParsedOptions::ParsedOptions()  {}
ParsedOptions::~ParsedOptions() { parsed_.clear(); }
bool ParsedOptions::assign(const ParsedValues& p) {
	if (!p.ctx) return false;
	p.prepare();
	// assign parsed values
	for (ParsedValues::iterator it = p.begin(), end = p.end(); it != end; ++it) {
		const Option& o = *it->first;;
		if (!assign(o, it->second)) {
			std::string d("'");
			d += it->second;
			d += "': invalid value for Option '";
			d += o.name();
			d += "'";
			throw BadValue(d);	
		}
	}
	return true;
}
bool ParsedOptions::assign(const Option& o, const std::string& value) {
	if (parsed_.count(o.name()) > 0 && !o.value()->isComposing()) {
		return true;
	}
	if (!o.value()->parse(o.name(), value)) {
		return false;
	}
	parsed_.insert(o.name());
	return true;
}
///////////////////////////////////////////////////////////////////////////////
// class ParsedValues
///////////////////////////////////////////////////////////////////////////////
namespace {
template <class P>
struct LessFirst {
	bool operator()(const P& lhs, const P& rhs) const {
		return lhs.first.get() < rhs.first.get();
	}
};
}
void ParsedValues::add(const std::string& name, const std::string& value) {
	OptionContext::option_iterator it = ctx->tryFind(name.c_str());
	if (it != ctx->end()) {
		add(*it, value);
	}
}

void ParsedValues::prepare() const {
	if (!prepared_ && parsed_.size() > 1) {
		LessFirst<OptionAndValue> lessKey;
		std::sort(parsed_.begin(), parsed_.end(), lessKey);
		for (Values::const_iterator it = parsed_.begin()
			, next = parsed_.begin()+1
			, end  = parsed_.end(); next != end; ) {
			if (it->first.get() != next->first.get()) {
				it = next++;
			}
			else if (!it->first->value()->isComposing()) {
				std::string d("Option '");
				d += it->first->name();
				d += "'";
				throw MultipleOccurences(d);
			}
			else {
				it   = std::upper_bound(parsed_.begin(), parsed_.end(), *it, lessKey);
				next = it != end ? it+1 : end;
			}
		}
	}
	prepared_ = true;
}
///////////////////////////////////////////////////////////////////////////////
// class OptionParser
///////////////////////////////////////////////////////////////////////////////
OptionParser::OptionParser(OptionContext& o, bool allowUnreg)
	: pv_(o)
	, allowUnreg_(allowUnreg)
{}

OptionParser::~OptionParser()
{}

ParsedValues OptionParser::parse() {
	doParse();
	return pv_;
}

OptionParser::OptionType OptionParser::getOptionType(const char* o) const {
	if (*o == '-' && *(o + 1) == '-') {
		return  *(o + 2) != '\0' ? long_opt : end_opt;
	}
	return *o == '-' && *(o + 1) != '\0' ? short_opt : no_opt;
}

SharedOptPtr OptionParser::getOption(const char* name, OptionType t) const {
	assert(t == short_opt || t == long_opt);
	try {
		OptionContext::FindType ft = (t == short_opt ? OptionContext::find_alias : OptionContext::find_name_or_prefix);
		return *pv_.ctx->find(name, ft);
	}
	catch (const UnknownOption&) {
		if (allowUnreg_) { return SharedOptPtr(0); }
		throw;
	}
}
namespace {   
///////////////////////////////////////////////////////////////////////////////
// class CommandLineParser
///////////////////////////////////////////////////////////////////////////////    
class CommandLineParser : public OptionParser {
public:
	CommandLineParser(OptionContext& o, bool allowUnreg, PosOption po)
		: OptionParser(o, allowUnreg)
		, posOpt_(po)
	{}
	std::vector<const char*> remaining;
private:
	virtual const char* next() = 0;
	void doParse() {
		bool breakEarly  = false;
		SharedOptPtr po(0);
		std::string poName, poNameLast;
		const char* curr;
		while ( (curr=next()) && !breakEarly ) {
			switch(getOptionType(curr)) {
				case short_opt: if (handleShortOpt(curr + 1)) curr = 0; break;
				case long_opt:  if (handleLongOpt(curr + 2)) curr = 0;  break;
				case end_opt:   curr = 0; breakEarly = true; break;
				case no_opt:  
				if (!posOpt_ || !posOpt_(curr, poName)) {
					po = getOption("Positional Option", long_opt);
				}
				else if (poName != poNameLast) {
					po = getOption(poName.c_str(), long_opt);
					poNameLast = poName;
				}
				if (po.get())  {
					addOptionValue(po, curr);
					curr = 0;
				}
				break;
				default:
					assert(0);
			}
			if (curr) {
				remaining.push_back(curr);
			}
		}
		while (curr)  {
			remaining.push_back(curr);
			curr = next();
		}
	}
	bool handleShortOpt(const char* optName) {
		// either -o value or -o[value|opts]
		char optn[2];
		optn[1] = '\0';
		SharedOptPtr o;
		while (*optName) {
			optn[0]         = *optName;
			const char* val = optName + 1;
			if ( (o = getOption(optn, short_opt)).get() ) {
				if (o->value()->isImplicit()) {
					// -ovalue or -oopts
					if (!o->value()->isFlag()) {
						// consume (possibly empty) value
						addOptionValue(o, val);
						return true;
					}
					else {
						// -o + more options
						addOptionValue(o, "");
						++optName;
					}
				}
				else if (*val != 0 || (val = next())) {
					// -ovalue or -o value
					addOptionValue(o, val);
					return true;
				}
				else {
					throw runtime_error(string("required parameter missing after -") + optn);
				}
			}
			else {
				return false;
			}
		}
		return true;
	}
	bool handleLongOpt(const char* optName) {
		string name(optName);
		string value;
		string::size_type p = name.find('='); 
		if (p != string::npos) {
			value.assign(name, p + 1, string::npos);
			name.erase(p, string::npos);
		}
		SharedOptPtr o;
		if ( (o = getOption(name.c_str(), long_opt)).get() ) {
			if (!o->value()->isImplicit() && value.empty()) {
				if (const char* v = next()) { value = v; }
				else { throw runtime_error(string("required parameter missing after --") + optName); }
			}
			// value given with 'opt=value' are always used, even
			// if opt is a flag
			addOptionValue(o, value);
			return true;
		}
		return false;
	}
	PosOption posOpt_;

};

class ArgvParser : public CommandLineParser {
public:
	ArgvParser(OptionContext& o, bool allowUnreg, int startPos, char** argv, PosOption po)
		: CommandLineParser(o, allowUnreg, po)
		, currentArg_(0)
		, argPos_(startPos)
		, argv_(argv) {
	}

private:
	const char* next() {
		currentArg_ = argv_[argPos_++];
		return currentArg_;
	}
	char*  currentArg_;
	int    argPos_;
	char** argv_;	
};

class CommandStringParser : public CommandLineParser {
public:
	CommandStringParser(const std::string& cmd, OptionContext& o, bool allowUnreg, PosOption po)
		: CommandLineParser(o, allowUnreg, po)
		, cmd_(cmd)
		, pos_(0)
		, end_(0) {
	}
private:
	const char* next() {
		while (end_ != cmd_.size() && std::isspace(static_cast<unsigned char>(cmd_[end_]))) {
			++end_;
		}
		if ((pos_ = end_) >= cmd_.size()) return 0;
		while (end_ != cmd_.size() && !std::isspace(static_cast<unsigned char>(cmd_[end_]))) {
			++end_;
		}
		if (end_ != cmd_.size()) {
			cmd_[end_++] = '\0';
		}
		return cmd_.c_str() + pos_;
	}
	CommandStringParser& operator=(const CommandStringParser&);
	std::string             cmd_;
	std::string::size_type  pos_;
	std::string::size_type  end_;
};
///////////////////////////////////////////////////////////////////////////////
// class CfgFileParser
///////////////////////////////////////////////////////////////////////////////    
class CfgFileParser : public OptionParser
{
public:
	CfgFileParser(OptionContext& o, bool allowUnreg, std::istream& in)
		: OptionParser(o, allowUnreg)
		, in_(in)
	{}
private:
	inline void trimLeft(std::string& str, const std::string& charList = " \t") {
		std::string::size_type pos = str.find_first_not_of(charList);
		if (pos != 0)
			str.erase(0, pos);
	}
	inline void trimRight(std::string& str, const std::string& charList = " \t") {
		std::string::size_type pos = str.find_last_not_of(charList);
		if (pos != std::string::npos)
			str.erase(pos + 1, std::string::npos);
	}
	bool splitHalf( const std::string& str, const std::string& seperator,
		std::string& leftSide,
		std::string& rightSide) {
		std::string::size_type sepPos = str.find(seperator);
		leftSide.assign(str, 0, sepPos);
		if (sepPos != std::string::npos) {
			rightSide.assign(str, sepPos + seperator.length(), std::string::npos);
			return true;
		}
		return false;
	}
	void doParse() {
		int lineNr = 0;
		std::string sectionName;      // current section name
		std::string sectionValue;     // current section value
		bool inSection = false;       // true if multi line section value
		SharedOptPtr opt;
		// reads the config file.
		// A config file may only contain empty lines, single line comments or
		// sections structured in a name = value fashion.
		// value can span multiple lines, but parts in different lines than name
		// must not contain a '='-Character.
		for (std::string line; std::getline(in_, line);) {
			++lineNr;
			trimLeft(line);
			trimRight(line);

			if (line.empty() || line.find("#") == 0) {
				// An empty line or single line comment stops a multi line section value.
				if (inSection) {
					if ( (opt = getOption(sectionName.c_str(), long_opt)).get() )
						addOptionValue(opt, sectionValue);
					inSection = false;
				}
				continue;
			}
			std::string::size_type pos;
			if ( (pos = line.find("=")) != std::string::npos) {
				// A new section terminates a multi line section value.
				// First process the current section value...
				if (inSection) {
					if ( (opt = getOption(sectionName.c_str(), long_opt)).get() )
						addOptionValue(opt, sectionValue);
					inSection = false;
				}
				// ...then save the new section's value.
				splitHalf(line, "=", sectionName, sectionValue);
				trimRight(sectionName);
				trimLeft(sectionValue, " \t\n");
				inSection = true;
			}
			else if (inSection) {
				sectionValue += " ";
				sectionValue += line;
			}
			else {
				throw std::runtime_error("illegal option file format");
			}
		}
		if (inSection) { // file does not end with an empty line
			if ( (opt = getOption(sectionName.c_str(), long_opt)).get() )
				addOptionValue(opt, sectionValue);
		}
	}
	std::istream& in_;
};

} // end unnamed namespace

ParsedValues parseCommandLine(int& argc, char** argv, OptionContext& o, bool allowUnreg, PosOption po) {
	ArgvParser pa(o, allowUnreg, 1, argv, po);
	ParsedValues ret = pa.parse();
	argc = 1 + (int)pa.remaining.size();
	for (int i = 1; i != argc; ++i) {
		argv[i] = const_cast<char*>(pa.remaining[i-1]);
	}
	argv[argc] = 0;
	return ret;
}

ParsedValues parseCommandString(const std::string& cmd, OptionContext& o, bool allowUnreg, PosOption po) {
	CommandStringParser parser(cmd, o, allowUnreg, po);
	return parser.parse();
}

ParsedValues parseCfgFile(std::istream& in, OptionContext& o, bool allowUnreg) {
	CfgFileParser p(o, allowUnreg, in);
	return p.parse();
}

}
