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
#ifndef PROGRAM_OPTIONS_VALUE_H_INCLUDED
#define PROGRAM_OPTIONS_VALUE_H_INCLUDED
#ifdef _MSC_VER
#pragma warning (disable : 4786)
#pragma warning (disable : 4503)
#endif
#include <string>
#include <typeinfo>
#include <cstddef>
#if defined(_MSC_VER) && _MSC_VER <= 1200
namespace std { using ::size_t; }
#endif

namespace ProgramOptions {
	
//! Manages the value of an option and defines how it is parsed from a string.
/*!
 * The library maintains a 1:1-relationship between options and their values.
 * That is, an option has exactly one value and a value has exactly one
 * state w.r.t its option. 
 */
class Value {
public:
	//! Possible states of an option value
	enum ValueState { 
		value_unassigned = 0, /**< no value assigned */
		value_defaulted  = 1, /**< a default value is assigned */
		value_parsed     = 2  /**< a parsed value is assigned */
	};
	virtual ~Value();

	//! Returns the current state of this value
	ValueState state() const { return state_; }
	/*!
	 * Sets the (initial) state of this value to s.
	 */
	Value* state(Value::ValueState s) {
		state(true, s);
		return this;
	}
	
	//! Returns true if value can be implicitly created from an empty string.
	/*!
	 * \note the implicit value comes into play if the corresponding 
	 *       option is present but without an adjacent value.
	 *
	 * \note an explicit value for an implicit value is only used if
	 *       it is unambiguously given. E.g. on the command-line one has
	 *       to use '--option=value' or '-ovalue' but *not* '--option value'
	 *       or '-o value'.
	 */
	bool isImplicit() const { return extra_[implicit_value] != 0; }
	
	/*!
	 * Sets an implicit value, which will be used
	 * if option is given without an adjacent value,
	 * e.g. '--option' instead of '--option value'
	 * \see bool Value::isImplicit() const
	 */
	Value* implicitValue(const char* str) {
		setExtraValue(Value::implicit_value, str);
		return this;
	}

	//! Returns true if value is the value of an option flag.
	/*!
	 * Similar to isImplicit but with the difference that
	 * an explicit value is only used if given via
	 * the option name (i.e. '--option=value' will use 'value' 
	 * but '-ovalue' will use the implicit value).
	 *
	 * Used for options like '--help' or '--version'.
	 *
	 * \note
	 *   The implicit value is 'true' if option is present and 
	 *   no other implicit value was set.
	 */
	bool isFlag() const { return hasFlag(is_flag_flag); }
	/*!
	 * Marks the value as flag. 
	 * \see bool Value::isFlag() const
	 */
	Value* flag() {
		setFlag(Value::is_flag_flag);
		return implicitValue("1");
	}

	//! Returns true if the value of this option can be composed from multiple source.
	bool isComposing() const { return hasFlag(composing_flag); }
	/*!
	 * Marks the value as composing.
	 * \see Value::isComposing()
	 */
	Value* composing() {
		setFlag(Value::composing_flag);
		return this;
	}

	//! Returns true if the value has a default value
	bool hasDefault()  const { return extra_[default_value] != 0; }

	//! Returns the value's default value or "" if no such value exists
	const std::string& defaultValue() const {
		return hasDefault() ? *extra_[default_value] : empty_string_s; 
	}

	/*!
	 * Sets a default value, which will be used
	 * if the option is not given.
	 *
	 * \note
	 *   The default value is only applied if the state of
	 *   this value is not already equal to value_defaulted
	 *
	 * \see state()
	 */
	Value* defaultValue(const char* str) {
		setExtraValue(Value::default_value, str);
		return this;
	}
	
	//! Parses the given string and updates the value's state
	/*!
	 * \param name      The name of the option associated with this value
	 * \param value     The value to parse
	 * \param asDefault Whether or not value is the option's default value
	 *   
	 * \return 
	 * - true if the given string contains a valid value
	 * - false otherwise
	 *
	 * \post if true is returned, state() is either value_parsed or
	 *       value_defaulted depending on whether asDefault is false
	 *       or true, respectively.
	 */
	bool parse(const std::string& name, const std::string& value, bool asDefault = false) {
		ValueState s = asDefault ? value_defaulted : value_parsed;
		if (value.empty()) {
			return isImplicit() && state(doParse(name, *extra_[implicit_value]), s);
		}
		return state(doParse(name, value), s);
	}
protected:
	typedef unsigned char byte_t;
	enum Flag { 
		  is_flag_flag       = 1 // implicit and type bool
		, composing_flag     = 2 // multiple values allowed?
		, owns_default_flag  = 4 //	owns its default value?	
		, owns_implicit_flag = 8 // owns its implicit value?
		, has_location_flag  = 16// has fixed storage location?
	};
	enum ExtraValue { default_value = 0, implicit_value = 1 };
	Value(byte_t flagSet, ValueState initial = value_unassigned);
	void setFlag(byte_t f)     { flagSet_ |= byte_t(f); }
	void clearFlag(byte_t f)   { flagSet_ &= ~byte_t(f);}
	bool hasFlag(byte_t f)const{ return (flagSet_ & byte_t(f)) != 0; }
	bool state(bool b, ValueState s) {
		if (b) { state_ = s; }
		return b;
	}
	bool hasImplicit() const { return extra_[implicit_value] != 0; }
	void setExtraValue(ExtraValue e, const char* str);
	virtual bool doParse(const std::string& name, const std::string& value) = 0;
private:
	void    release(ExtraValue e);
	byte_t  extra2Flag(ExtraValue e) const { return e == default_value ? owns_default_flag : owns_implicit_flag; }
	byte_t             flagSet_; // value properties
	ValueState         state_;   // current state 
	const std::string* extra_[2];// optional default and implicit value
	static std::string empty_string_s; // ""
};
}
#endif
