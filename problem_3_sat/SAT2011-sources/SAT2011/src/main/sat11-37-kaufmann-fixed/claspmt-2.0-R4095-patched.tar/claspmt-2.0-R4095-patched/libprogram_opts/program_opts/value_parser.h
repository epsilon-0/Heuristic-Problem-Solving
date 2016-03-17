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
#ifndef PROGRAM_OPTIONS_VALUE_PARSER_H_INCLUDED
#define PROGRAM_OPTIONS_VALUE_PARSER_H_INCLUDED
#include "detail/input_stream.h"
namespace ProgramOptions { 

struct StringSlice {
	StringSlice(const std::string& s)    : ptr_(s.c_str()), len_(s.size()<<1) {}
	StringSlice(const char* p, size_t s) : ptr_(p), len_(s<<1) {}
	StringSlice parsed(bool ok, size_t numParsed = 0) const {
		StringSlice ret(*this);
		if (!ok) ret.len_ |= 1;
		else ret.skip(numParsed);
		return ret;
	}
	const char* data()     const { return ptr_; }
	size_t      size()     const { return len_>>1; }
	bool        ok()       const { return !error(); }
	bool        error()    const { return (len_&1) != 0; }
	bool        complete() const { return ok() && size() == 0; }
	operator    bool()     const { return complete(); }
private:
	void skip(size_t num);
	const char* ptr_;
	size_t      len_;
};

template <class T> struct no_parser_for_type;

//! called if no parser for T was found
template <class T>
StringSlice parseValue(const StringSlice& in, T& out, ...) {
	sizeof(no_parser_for_type<T>);
	return in.parsed(false);
}

struct FlagStr { 
  std::string str; bool val; 
  static const FlagStr* find(const std::string& s);
  static const FlagStr* find(const char* s);
	static const FlagStr* findImpl(const char* s, std::size_t len);
	//! parses "1" | "0" | "yes" | "no" | "true" | "false" | "on" | "off"
	static StringSlice parse(const StringSlice& slice, bool& out, int);
  static FlagStr map_s[8];
};

std::string toLower(const std::string& in);

//! calls operator>>(std::istream&, T&) to parse a value
template <class T>
StringSlice parseValue(const StringSlice& in, T& v, double extra) {
	detail::input_stream<char> str(in.data(), in.size());
	if ( (str>>v) ) {
		StringSlice ret = in.parsed(true, (size_t)str.tellg());
		return ret.complete() || extra > 0.0 ? ret : in.parsed(false);
	}
	return in.parsed(false);
}

inline StringSlice parseValue(const StringSlice& in, bool& v, int extra) {
	return FlagStr::parse(in, v, extra);
}
inline StringSlice parseValue(const StringSlice& in, std::string& v, int) {
	v.assign(in.data(), in.size());
	return in.parsed(true, in.size());
}

template <class T>
struct DefaultParser {
	static bool parse(const std::string& str, T& out) {
		return parseValue(StringSlice(str), out, 0);
	}
};

template <class T>
struct DefaultCreator {
	static T* create() { return new T(); }
};

}
#endif
