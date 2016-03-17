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
#ifndef PROGRAM_OPTIONS_MAPPED_VALUE_H_INCLUDED
#define PROGRAM_OPTIONS_MAPPED_VALUE_H_INCLUDED
#ifdef _MSC_VER
#pragma warning (disable : 4786)
#pragma warning (disable : 4503)
#endif
#include "detail/value_holder.h"
#include "typed_value.h"
#include <string>
#include <cstddef>
#include <map>
#if defined(_MSC_VER) && _MSC_VER <= 1200
namespace std { using ::size_t; }
#endif

namespace ProgramOptions { 
///////////////////////////////////////////////////////////////////////////////
// Value holding
///////////////////////////////////////////////////////////////////////////////
class ValueHolder {
public:
	ValueHolder();
	//! Stores a *copy* of value.
	template <class T>
	ValueHolder(const T& value)
		: value_(new T(value))
		, vptr_(detail::vtable(static_cast<const T*>(0))) {
	}
	//! Assimilates value.
	/*!
	 * \pre delete value is valid
	 */
	template <class T>
	ValueHolder(T* value) 
		: value_(value) 
		, vptr_(detail::vtable(static_cast<const T*>(0))) {
	}
	ValueHolder(const ValueHolder& other);
	ValueHolder& operator=(ValueHolder);
	//! Assimilates value.
	template <class T>
	ValueHolder& operator=(T* value) {
		*this = ValueHolder();
		value_= value;
		vptr_ = detail::vtable(static_cast<const T*>(0));
		return *this;
	}
	~ValueHolder();
	void   swap(ValueHolder& other);
	//! Returns true if holder does not contain a value.
	bool   empty()       const { return value_ == 0; }
	//! Returns the type of the stored value.
	const  std::type_info& 
		     type()        const;
	
	// NOT INTENDED for general use!
	// Public only because template friends are not supported
	// by some compilers
	void*  raw()         const { return value_; }
private:
	enum { vcall_clone = 0, vcall_destroy = 1, vcall_typeid = 2 };
	typedef detail::vptr_type vptr_type;
	void* clone()   const;
	void*     value_;
  vptr_type vptr_;          
};
//! Cast for extracting typed value from a ValueHolder.
/*!
* \throw BadCast if value is not of type T
*/
template <class T>
const T& value_cast(const ValueHolder& v, const T* = 0) {
	if (v.type() == typeid(T)) {
		return *static_cast<const T*>(v.raw());
	}
	std::string err("Can't extract '");
	err += typeid(T).name();
	err += "' from holder holding '";
	err += v.type().name();
	err += "'";
	throw BadValue(err.c_str());
}
/*!
 * \overload
 */
template <class T>
T&       value_cast(ValueHolder& v, const T* p = 0) {
	return const_cast<T&>(value_cast(const_cast<const ValueHolder&>(v), p));
}
///////////////////////////////////////////////////////////////////////////////
// ValueMap
///////////////////////////////////////////////////////////////////////////////
//! Type for storing anonymous values
/*!
 * Maps option names to their values
 */
class ValueMap {
public:
	ValueMap();
	~ValueMap();
	bool               empty() const { return map_.empty(); }
	size_t             size()  const { return map_.size(); }
	size_t             count(const std::string& name) const { return map_.count(name); }
	void               clear()       { map_.clear(); }
	const ValueHolder& operator[](const std::string& name) const;

	template <class T>
	static bool add(ValueMap* this_, const std::string& name, const T* value) {
		MapType::iterator it = this_->map_.find(name);
		if (it == this_->map_.end()) {
			this_->map_[name] = const_cast<T*>(value);
			return true;
		}
		else {
			value_cast<T>(it->second) = *value;
			return false;
		}
	}
private:
	ValueMap(const ValueMap&);
	ValueMap& operator=(const ValueMap&);
	typedef std::map<std::string, ValueHolder> MapType;
	MapType map_;
};

/*!
 * Creates a mapped value, i.e. a value that is created on demand and
 * stored in a given value map.
 *
 * \see OptionGroup::addOptions()
 */
template <class T>
inline LazyValue<T>* mapped(ValueMap& map, typename detail::Parser<T>::type p = &DefaultParser<T>::parse) {
	return new LazyValue<T>(&DefaultCreator<T>::create, detail::Notifier<T>(&map, &ValueMap::add<T>), p);
}

inline LazyValue<bool>* flag(ValueMap& map, detail::Parser<bool>::type p = &DefaultParser<bool>::parse) {
	return flag(&map, &ValueMap::add<bool>, p);
}


}
#endif
