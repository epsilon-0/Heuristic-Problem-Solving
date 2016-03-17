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
#ifndef PROGRAM_OPTIONS_PROGRAM_OPTIONS_H_INCLUDED
#define PROGRAM_OPTIONS_PROGRAM_OPTIONS_H_INCLUDED
#include "value.h"
#include "detail/refcountable.h"
#include <iosfwd>
#include <set>
#include <map>
#include <vector>
#include <stdexcept>
#include <memory>
namespace ProgramOptions {

//! Represents one program option.
/*!
 * An Option consists of a description (long name, short name, description),
 * a (typed) value, and an optional default value.
 */
class Option : public detail::RefCountable {
public:
	/*!
	* \pre longName != ""
	* \pre vd != 0
	* \param longName    name (and unique key) of the option
	* \param shortName   possible alias name
	* \param description description of the option, used for printing help
	* \param value       value object to be associated with this option
	* \param arg         optional argument description
	*
	* \note 
	*   Occurrences of %D and %A in description are replaced 
	*   with the value's default value and the argument description,
	*   respectively.
	*/
	Option( const std::string& longName, char shortName,
		const char* description, Value* value, const char* arg = 0);

	~Option();

	const std::string& name()           const   { return name_; }
	char               alias()          const   { return description_[0]; }
	Value*             value()          const   { return value_; }
	const char*        description()    const;
	const char*        argDescription() const;
	const std::string& defaultValue()   const;
	bool               assignDefault()  const;
	std::size_t        maxColumn()      const;
	void               formatDescription(std::string& out) const;
private:
	const char* arg() const;
	std::string name_;        // name (and unique key) of option
	const char* description_; // description of the option (used for --help)
	Value*      value_;       // the option's value manager
};

typedef detail::IntrusiveSharedPtr<Option> SharedOptPtr;

class OptionInitHelper;
class OptionContext;
class OptionParser;
class ParsedValues;
class ParsedOptions;

//! A list of options logically grouped under a caption
/*!
 * The class provides a logical grouping of options that
 * is mainly useful for printing help.
 */
class OptionGroup {
public:
	typedef std::vector<SharedOptPtr>  OptionList;
	typedef OptionList::const_iterator option_iterator;

	/*!
	 * Creates a new group of options under the given caption
	 */
	OptionGroup(const std::string& caption = "");
	//! Creates a new hidden group
	/*!
	 * A hidden group is a group that is ignored 
	 * in the description of a context object
	 * \see OptionContext::description()	 
	 */
	static OptionGroup createHidden();
	
	~OptionGroup();

	//! Returns the caption of this group.
	std::string caption() const { return caption_; }

	std::size_t size()    const { return options_.size();  }
	bool        empty()   const { return options_.empty(); }
	bool        hidden()  const;
	option_iterator begin() const { return options_.begin(); }
	option_iterator end()   const { return options_.end();   }
	
	//! Returns an object that can be used to add options.
	/*!
	 * \par usage \n
	 * \code
	 * OptionGroup g("Some Options");
	 * g.addOptions()
	 *   ("opt1", value<int>(), "some int value")   // <- no semicolon
	 *   ("opt2", value<double>())                  // <- no semicolon
	 *   ("opt3", value<char>())                    // <- no semicolon
	 * ;                                            // <- note the semicolon!
	 * \endcode
	 */
	OptionInitHelper addOptions();

	//! Adds option to this group
	void addOption(std::auto_ptr<Option> option);

	typedef void (*FormatFunction)(std::string& out, const Option& option, std::size_t maxW);
	//! Creates a formated description of all options in this group.
	void format(std::string& out, FormatFunction f, size_t maxW) const;

	std::size_t maxColumn() const;
private:
	friend class OptionContext;
	std::string caption_;
	OptionList  options_;
};

class OptionInitHelper {
public:
	explicit OptionInitHelper(OptionGroup& owner);
	OptionInitHelper& operator()(const char* name,
		Value* val,
		const char* description = 0, const char* extra = 0);
private:
	OptionGroup* owner_;
};


//! A (logically grouped) list of unique options
/*!
 * An option context stores a list of option groups.
 * Options in a context have to be unique (w.r.t name and alias) 
 * within that context.
 *
 * An OptionContext defines the granularity of option parsing
 * and option lookup.
 */
class OptionContext {
private:
	typedef std::size_t                               key_type;
	typedef std::map<std::string, key_type>           Name2Key;
	typedef std::vector<OptionGroup>                  GroupList;
	typedef Name2Key::const_iterator                  index_iterator;
	typedef std::pair<index_iterator, index_iterator> PrefixRange;
	typedef OptionGroup::OptionList                   OptionList;
public:
	//! Type for identifying an option within a context
	typedef OptionList::const_iterator      option_iterator;
	typedef OptionGroup::FormatFunction     FormatFunction;
	
	OptionContext(const std::string& caption = "");
	~OptionContext();

	const std::string& caption() const { return caption_; }
	
	//! Adds the given group of options to this context
	/*!
	 * \note  If this object already contains a group with
	 *        the same caption as group, the groups are merged.
	 *
	 * \throw DuplicateOption if an option in group
	 *        has the same short or long name as one of the
	 *        options in this context.
	 */
	OptionContext& add(const OptionGroup& group);

	//! Adds all groups (and their options) from other to this context.
	/*!
	 * \throw DuplicateOption if an option in other
	 *        has the same short or long name as one of the
	 *        options in this context.
	 *
	 * \see OptionContext& add(const OptionGroup&);
	 */
	OptionContext& add(const OptionContext& other);
	
	option_iterator begin() const { return options_.begin(); }
	option_iterator end()   const { return options_.end();   }

	//! Returns the number of options in this context.
	std::size_t size() const   { return options_.size(); }
	//! Returns the number of groups in this context
	std::size_t groups() const { return groups_.size(); }

	enum FindType { find_name = 1, find_prefix = 2, find_name_or_prefix = find_name|find_prefix, find_alias = 4 };
	
	//! Returns the option with the given key.
	/*!
	 * \note The second parameter defines how key is interpreted:
	 *        - find_name:   search for an option whose name equals key.
	 *        - find_prefix: search for an option whose name starts with the given key
	 *        - find_alias:  search for an option whose alias equals key.
	 *       .
	 *
	 * \note if second parameter is find_alias, a starting '-'
	 *       in key is valid but not required.
	 *
	 * \throw UnknownOption if no option matches key
	 * \throw AmbiguousOption if more than one option matches key
	 */
	option_iterator find(const char* key, FindType t = find_name) const;
	/*!
	 * Behaves like find but returns end() instead of throwing
	 * UnknownOption or AmbiguousOption
	 */
	option_iterator tryFind(const char* key, FindType t = find_name) const;
	
	//! Creates a formated description of all options in this context.
	/*!
	 * \note hidden groups are ignored unless addHidden is true
	 */
	std::string description(FormatFunction f, bool addHidden = false) const;
	
	//! Creates a formated description of the default command-line of this context.
	std::string defaults(std::size_t prefixSize = 0) const;
	
	//! Same as os << this->toString().
	friend std::ostream& operator<<(std::ostream& os,  const OptionContext& ctx);

	//! Assigns any default values to all options not in exclude 
	/*!
	 * \throw BadValue if some default value is actually invalid for its option
	 */
	bool assignDefaults(const ParsedOptions& exclude) const;
private:
	PrefixRange findImpl(const char* key, FindType t) const;
	void        insertOption(size_t groupId, const SharedOptPtr& o);
	size_t      findGroup(const std::string& name) const;
	
	Name2Key    index_;
	OptionList  options_;
	GroupList   groups_;
	std::string caption_;
};

class OptionParser;
class ParsedValues;

//! Set of options holding a parsed value
class ParsedOptions {
public:
	ParsedOptions();
	~ParsedOptions();
	bool        empty()                        const  { return parsed_.empty(); }
	std::size_t size()                         const  { return parsed_.size(); }
	std::size_t count(const std::string& name) const  { return parsed_.count(name); }
	
	//! Assigns the parsed values in p to their options
	/*!
	 * Parsed values for options that already have a value (and are
   * not composing) are ignored. On the other hand, parsed values
	 * overwrite any existing default values.
	 *
	 * \param p parsed values to assign
	 *
	 * \throw MultipleOccurences if p contains more than one value 
	 *        for a non-composing option
	 * \throw BadValue if p contains a value that is invalid for its option
	 * 
	 */
	bool        assign(const ParsedValues& p);
private:
	std::set<std::string> parsed_;
	bool assign(const Option& o, const std::string& value);
};

/*!
* Container of option-value-pairs representing values found by a parser
*/
class ParsedValues {
public:
	typedef std::pair<SharedOptPtr, std::string> OptionAndValue;
	typedef std::vector<OptionAndValue> Values;
	typedef Values::const_iterator iterator;

	/*!
	* \param a_ctx The OptionContext for which this object stores raw-values.
	*/
	explicit ParsedValues(const OptionContext& a_ctx)
		: ctx(&a_ctx)
		, prepared_(true)
	{}
	const OptionContext* ctx;
	
	//! Adds a value for option opt.
	void add(const std::string& opt, const std::string& value);

	void prepare() const;

	iterator begin() const { return parsed_.begin(); }
	iterator end()   const { return parsed_.end(); }

	void clear() { parsed_.clear(); prepared_ = true; }
private:
	friend class OptionParser;
	void add(const SharedOptPtr& opt, const std::string& value) {
		parsed_.push_back(OptionAndValue(opt, value));
		prepared_ = false;
	}
	mutable Values parsed_;  
	mutable bool   prepared_;
};

//! Base class for options parsers.
class OptionParser {
public:
	enum OptionType {short_opt, long_opt, end_opt, no_opt};
	OptionParser(OptionContext& o, bool allowUnreg);
	virtual ~OptionParser();
	ParsedValues parse();
protected:
	OptionType getOptionType(const char* o) const;
	SharedOptPtr getOption(const char* name, OptionType t) const;
	// PRE: key.get() != 0
	void addOptionValue(const SharedOptPtr& key, const std::string& value) {
		pv_.add(key, value);
	}
private:
	virtual void doParse() = 0;
	ParsedValues pv_;
	bool allowUnreg_; 
};

///////////////////////////////////////////////////////////////////////////////
// parse functions
///////////////////////////////////////////////////////////////////////////////
/*!
 * A function type that is used by parsers for processing tokens that
 * have no option name. Concrete functions shall either return true
 * and store the name of the option that should receive the token as value 
 * in its second argument or return false to signal an error.
 */
typedef bool (*PosOption)(const std::string&, std::string&);

/*!
* Parses the command line starting at index 1 and removes
* all found options from argv.
* \param argc nr of arguments in argv
* \param argv the command line arguments
* \param ctx options to search in the command line.
* \param allowUnregistered Allow arguments that match no option in ctx
* \param posParser parse function for positional options
*
* \return A ParsedOptions-Object containing names and values for all options found.
* 
* \throw std::runtime_error if command line syntax is incorrect
* \throw UnknownOption if allowUnregistered is false and an argument is found
* that does not match any option.
*/
ParsedValues parseCommandLine(int& argc, char** argv, OptionContext& ctx,
	bool allowUnregistered = true,
	PosOption posParser = 0);

/*!
* Parses the command line given in the first parameter
* \param cmd command line to parse
* \param ctx options to search in the command string.
* \param allowUnregistered Allow arguments that match no option in ctx
* \param posParser parse function for positional options
*
* \return A ParsedOptions-Object containing names and values for all options found.
* 
* \throw std::runtime_error if command line syntax is incorrect
* \throw UnknownOption if an argument is found that does not match any option.
*/
ParsedValues parseCommandString(const std::string& cmd, OptionContext& ctx, bool allowUnreg = false, PosOption posParser = 0);

/*!
* Parses a config file having the format key = value.
* \param is the stream representing the config file
* \param o options to search in the config file
* \param allowUnregistered Allow arguments that match no option in ctx
* 
* \return A ParsedOptions-Object containing names and values for all options found.
*
* \throw std::runtime_error if config file has incorrect syntax.
* \throw UnknownOption if allowUnregistered is false and an argument is found
* \note keys are option's long names.
* \note lines starting with # are treated as comments and are ignored.
*/
ParsedValues parseCfgFile(std::istream& is, OptionContext& o, bool allowUnregistered);

}

#endif
