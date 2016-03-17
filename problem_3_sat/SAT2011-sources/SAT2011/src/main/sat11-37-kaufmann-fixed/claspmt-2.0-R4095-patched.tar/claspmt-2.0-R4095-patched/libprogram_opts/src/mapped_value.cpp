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
#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif
#include <program_opts/mapped_value.h>
namespace ProgramOptions {  
	
ValueMap::ValueMap()  {}
ValueMap::~ValueMap() {}

const ValueHolder& ValueMap::operator [](const std::string& name) const {
	MapType::const_iterator it = map_.find(name);
	if (it == map_.end()) {
		throw UnknownOption(name);
	}
	return it->second;
}

ValueHolder::ValueHolder() : value_(0), vptr_(0) {}
ValueHolder::ValueHolder(const ValueHolder& other)
	: value_(other.clone())
	, vptr_(other.vptr_) {	
}
ValueHolder& ValueHolder::operator=(ValueHolder other) {
	other.swap(*this);
	return *this;
}
ValueHolder::~ValueHolder() {
	if (!empty()) {
		value_ = (*vptr_)[vcall_destroy](value_);
	}
}
const std::type_info& ValueHolder::type() const {
	if (!empty()) {
		return *static_cast<const std::type_info*>( (*vptr_)[vcall_typeid](0) );
	}
	struct internal_empty_type {};
	return typeid(internal_empty_type);
}
void* ValueHolder::clone() const {
	return empty() 
		? 0
		: (*vptr_)[vcall_clone](value_);
}
void ValueHolder::swap(ValueHolder& other) {
	std::swap(value_, other.value_);
	std::swap(vptr_, other.vptr_);
}

}
