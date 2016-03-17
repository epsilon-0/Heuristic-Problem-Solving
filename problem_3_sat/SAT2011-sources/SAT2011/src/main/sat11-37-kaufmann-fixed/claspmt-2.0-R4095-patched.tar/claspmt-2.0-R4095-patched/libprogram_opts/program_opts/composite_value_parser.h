//
//  Copyright (c) Benjamin Kaufmann 2010
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
#ifndef PROGRAM_OPTIONS_COMPOSITE_VALUE_PARSER_H_INCLUDED
#define PROGRAM_OPTIONS_COMPOSITE_VALUE_PARSER_H_INCLUDED
#include <istream>
#include "value_parser.h"
#include <vector>
#include <utility>
#include <cassert>
namespace ProgramOptions { 

template <class T>
struct ComponentSeparator {
	static bool isSeparator(char x) {
		return x == ',' || x == ';';
	}
};

template <class T>
StringSlice parseComponent(const StringSlice& in, T& res, char optTerm) {
	if (in.size() == 0 || !in.ok()) return in.parsed(false);
	// find end of component slice
	const char* ptr = in.data();
	const char* end = in.data() + in.size();
	while (ptr != end && *ptr != optTerm && !ComponentSeparator<T>::isSeparator(*ptr)) {
		++ptr;
	}
	size_t toParse= ptr - in.data();
	// try to parse current component
	StringSlice x = parseValue(StringSlice(in.data(), toParse), res, 0);
	if (x.complete()) {
		return in.parsed(true, toParse + (ptr != end && *ptr==optTerm));
	}
	return in.parsed(false);
}

//! parses a sequence of Ts
template <class T>
StringSlice parseValue(const StringSlice& in, std::vector<T>& result, int extra) {
	StringSlice x = in;
	T temp;
	size_t rSize = result.size();
	do {
		StringSlice n = parseComponent(x, temp, 0);
		if (!n.ok()) {
			result.resize(rSize);
			return in.parsed(false);
		}
		result.push_back(temp);
		if (n.complete()) {
			return in.parsed(true, in.size());
		}
		assert(ComponentSeparator<T>::isSeparator(n.data()[0]));
		x = n.parsed(true, 1);
	} while (!x.complete());
	if (extra) { return x; }
	result.resize(rSize);
	return in.parsed(false);
}

//! parses a pair<T,U> as '('? valT [, valU] ')'?
template <class T, class U>
StringSlice parseValue(const StringSlice& in, std::pair<T, U>& result, int extra) {
	if (in.size() == 0) return in.parsed(false);
	StringSlice x = in;
	char term = 0;
	if (x.data()[0] == '(') {
		x    = x.parsed(true, 1);
		term = ')';
		extra+= 1;
	}
	T tempT;
	x = parseComponent(x, tempT, term);
	if (x.ok()) {
		if (x.complete()) {
			result.first = tempT;
			return x;
		}
		else if (x.data()[0] == ',') {
			U tempU;
			x = parseValue(x.parsed(true, 1), tempU, extra);
			if (!x.complete() && x.ok() && term != 0 && x.data()[0] == term) {
				x      = x.parsed(true, 1);
				term   = 0;
				extra -= 1;
			}
			if (term == 0 && (x.complete() || (x.ok() && extra))) {
				result.first = tempT;
				result.second= tempU;
				return x;
			}
		}
	}
	return in.parsed(false);
}
}
#endif
