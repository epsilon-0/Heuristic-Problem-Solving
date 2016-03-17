// 
// Copyright (c) 2010, Benjamin Kaufmann
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
#ifndef CLASP_SHARED_CLAUSE_H_INCLUDED
#define CLASP_SHARED_CLAUSE_H_INCLUDED

#ifdef _MSC_VER
#pragma warning (disable : 4200) // nonstandard extension used : zero-sized array
#pragma once
#endif

#include <clasp/solver_types.h>

namespace Clasp { namespace mt {

//! An array of literals that can be shared between multiple threads
class SharedLiterals {
public:
	//! creates a shareable (ref-counted) object containing the literals in lits
	/*!
	 * \note The reference count is set to numRefs
	 */
	static SharedLiterals* newShareable(const LitVec& lits, ConstraintType t, uint32 numRefs = 1) {
		return newShareable(!lits.empty() ? &lits[0]:0, static_cast<uint32>(lits.size()), t, numRefs);
	}
	static SharedLiterals* newShareable(const Literal* lits, uint32 size, ConstraintType t, uint32 numRefs = 1);
	
	//! returns a pointer to the beginning of the literal array
	const Literal* begin() const { return lits_; }
	//! returns a pointer to the end of the literal array
	const Literal* end()   const { return lits_+size(); }
	//! returns the number of literals in the array
	uint32         size()  const { return size_type_ >> 2; }
	//! returns the type of constraint from which the literals originated
	ConstraintType type()  const { return ConstraintType( size_type_ & uint32(3) ); }
	//! simplifies the literals w.r.t to the assignment in s
	/*!
	 * returns the number of non-false literals in this object or 0 if
	 * the array contains a true literal.
	 * \note If the object is currently not shared, simplify() removes
	 * all false literals from the array.
	 */
	uint32 simplify(Solver& s);

	void            release();
  SharedLiterals* share();
	bool            unique() const { return refCount_ <= 1; }
private:
	void destroy();
	SharedLiterals(const Literal* lits, uint32 size, ConstraintType t, uint32 numRefs);
	SharedLiterals(const SharedLiterals&);
	SharedLiterals& operator=(const SharedLiterals&);
	std::atomic<int32> refCount_;
	uint32             size_type_;
	Literal            lits_[0];
};

//! Stores the local part of a shared clause
/*!
 * The local part of a shared clause consists of a
 * clause head and and a pointer to the shared literals.
 * Since the local part is owned by a particular solver 
 * it can be safely modified. Destroying a SharedLitsClause 
 * means destroying the local part and decreasing the
 * shared literals' reference count.
 */
class SharedLitsClause : public ClauseHead {
public:
	//! Attaches a new local part to shared_lits to be used in the given solver
	/*!
	 * \param s The solver in which this clause will be used
	 * \param shared_lits The shared literals of this clause
	 * \param e Initial data for the new (local) clause
	 * \param lits watches and cache literal for the new (local) clause
	 * \param addRef increment ref count of shared_lits
	 */
	static ClauseHead* newClause(Solver& s, mt::SharedLiterals* shared_lits, const ClauseExtra& e, const Literal* lits, bool addRef = true);
	
	Constraint*    cloneAttach(Solver& other);
	void           reason(Solver& s, Literal p, LitVec& out);
	bool           minimize(Solver& s, Literal p, CCMinRecursive* rec);
	bool           isReverseReason(const Solver& s, Literal p, uint32 maxL, uint32 maxN);
	bool           simplify(Solver& s, bool);
	void           destroy(Solver* s, bool detach);
	bool           isSatisfied(const Solver& s, LitVec& freeLits);
	uint32         size() const { return data_.shared->size(); }
	void           toLits(LitVec& out) const;
private:
	SharedLitsClause(Solver& s, SharedLiterals* x, const Literal* lits, const ClauseExtra&,  bool addRef);
	PropResult     propagateTail(Solver& s, Literal, uint32 pos);
	BoolPair       strengthen(Solver& s, Literal p, bool allowToShort);
};

} }

#endif
