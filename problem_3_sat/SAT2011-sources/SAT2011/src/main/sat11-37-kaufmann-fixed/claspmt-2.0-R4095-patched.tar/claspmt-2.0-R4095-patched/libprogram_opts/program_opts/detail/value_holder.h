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
#ifndef PROGRAM_OPTIONS_VALUE_HOLDER_IMPL_H_INCLUDED
#define PROGRAM_OPTIONS_VALUE_HOLDER_IMPL_H_INCLUDED

#include <typeinfo>

namespace ProgramOptions { namespace detail {

///////////////////////////////////////////////////////////////////////////////
// "VTables" for ValueHolder
///////////////////////////////////////////////////////////////////////////////
typedef void* (*vcall_type)(const void*);
typedef vcall_type vtable_type[3];
typedef vtable_type* vptr_type;
// workaround: some compilers don't support
// out-of-class definition of member templates.
template <class T>
inline vptr_type vtable(const T* = 0);

template <class T>
struct VTable {
	static void* clone(const void* o)   { return new T(*static_cast<const T*>(o));  }
	static void* destroy(const void* o) { delete static_cast<const T*>(o); return 0;}
	static void* typeinfo(const void*)  { 
		return const_cast<void*>(
			static_cast<const void*>(&typeid(T))
		);
	}
	static vtable_type vtable_s;
};
template <class T>
vtable_type VTable<T>::vtable_s = {
	  &VTable<T>::clone
	, &VTable<T>::destroy
	, &VTable<T>::typeinfo
};
template <class T>
inline vptr_type vtable(const T*) { return &VTable<T>::vtable_s; }

} }
#endif
