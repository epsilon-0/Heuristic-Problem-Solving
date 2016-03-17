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
#ifndef PROGRAM_OPTIONS_ERRORS_H_INCLUDED
#define PROGRAM_OPTIONS_ERRORS_H_INCLUDED
#include <stdexcept>
#include <string>
namespace ProgramOptions {

//! thrown when a value for an option has an unexpected type
class BadValue : public std::logic_error {
public:
	BadValue(const std::string& msg)
		: std::logic_error(msg)
	{}
	~BadValue() throw () {}
	std::string getOptionName() const {
		return optionName_;
	}
private:
	std::string optionName_;
};

//! thrown when a wrong type is used when extracting a value from a ValueHolder 
class BadCast : public std::bad_cast {
public:
	BadCast(const std::string& msg) 
		: what_(msg) {
	}
	~BadCast() throw () {}
	const char* what() const throw() {
		return what_.c_str();
	}
private:
	std::string what_;
};

//! thrown when an option has an illegal name
class BadOptionName : public std::logic_error {
public:
	BadOptionName(const std::string& name)
		: std::logic_error(std::string("bad option name: ").append(name))
	{}
	~BadOptionName() throw () {}
};

//! thrown when more than one option in a context has the same name
class DuplicateOption : public std::logic_error {
public:
	DuplicateOption(const std::string& name, const std::string& ctx)
		: std::logic_error(ctx + " - " + "Duplicate Option: '" + name + "'")
		, name_(name)
		, ctxDesc_(ctx)
	{}
	const std::string& getOptionName() const {return name_;}
	const std::string& getContextName() const {return ctxDesc_;}
	~DuplicateOption() throw() {}
private:
	const std::string name_;
	const std::string ctxDesc_;
};

//! thrown when an unknown option is requested
class UnknownOption : public std::logic_error {
public:
	UnknownOption(const std::string& name)
		: std::logic_error(std::string("unknown option: ").append(name))
	{}
	~UnknownOption() throw() {}
};

//! thrown when there's ambiguity amoung several possible options.
class AmbiguousOption : public std::logic_error {
public:
	AmbiguousOption(const std::string& optname)
		: std::logic_error(std::string("ambiguous option: ").append(optname))
	{}
	~AmbiguousOption() throw () {}
};

//! thrown when there are several occurrences of an option in one source
class MultipleOccurences : public std::logic_error {
public:
	MultipleOccurences(const std::string& opt)
		: std::logic_error(std::string("multiple occurences: ").append(opt))
	{}
	~MultipleOccurences() throw () {}
};

}
#endif
