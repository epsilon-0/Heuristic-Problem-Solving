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

#include <clasp/shared_clause.h>
#include <clasp/clause.h>
#include <clasp/solver.h>
namespace Clasp { namespace mt {

/////////////////////////////////////////////////////////////////////////////////////////
// SharedLiterals
/////////////////////////////////////////////////////////////////////////////////////////
SharedLiterals* SharedLiterals::newShareable(const Literal* lits, uint32 size, ConstraintType t, uint32 numRefs) {
	#pragma message TODO("replace with CACHE_LINE_ALIGNED alloc")
	void* m = ::operator new(sizeof(SharedLiterals)+(size*sizeof(Literal)));
	return new (m) SharedLiterals(lits, size, t, numRefs);
}

SharedLiterals::SharedLiterals(const Literal* a_lits, uint32 size, ConstraintType t, uint32 refs) 
	: size_type_( (size << 2) + t ) {
	refCount_ = refs;
	std::memcpy(lits_, a_lits, size*sizeof(Literal));
}

uint32 SharedLiterals::simplify(Solver& s) {
	bool   removeFalse = unique();
	uint32   newSize   = 0;
	Literal* r         = lits_;
	Literal* e         = lits_+size();
	ValueRep v;
	for (Literal* c = r; r != e; ++r) {
		if ( (v = s.value(r->var())) == value_free ) {
			if (c != r) *c = *r;
			++c; ++newSize;
		}
		else if (v == trueValue(*r)) {
			newSize = 0; break;
		}
		else if (!removeFalse) ++c;
	}
	if (removeFalse && newSize != size()) {
		size_type_ = (newSize << 2) | (size_type_ & uint32(3));
	}
	return newSize;
}

void SharedLiterals::release() {
	if (--refCount_ == 0) {
		this->~SharedLiterals();
		::operator delete(this);
	}
}
SharedLiterals* SharedLiterals::share() {
	++refCount_;
	return this;
}

/////////////////////////////////////////////////////////////////////////////////////////
// SharedLitsClause
/////////////////////////////////////////////////////////////////////////////////////////
ClauseHead* SharedLitsClause::newClause(Solver& s, SharedLiterals* shared_lits, const ClauseExtra& e, const Literal* lits, bool addRef) {
	return new (s.allocSmall()) SharedLitsClause(s, shared_lits, lits, e, addRef);
}

SharedLitsClause::SharedLitsClause(Solver& s, SharedLiterals* shared_lits, const Literal* w, const ClauseExtra& e, bool addRef) 
	: ClauseHead(e) {
	static_assert(sizeof(SharedLitsClause) <= 32);
	data_.shared = addRef ? shared_lits->share() : shared_lits;
	std::memcpy(head_, w, std::min((uint32)ClauseHead::HEAD_LITS, shared_lits->size())*sizeof(Literal));
	attach(s);
}

Constraint* SharedLitsClause::cloneAttach(Solver& other) {
	return SharedLitsClause::newClause(other, data_.shared, ClauseExtra().setType(this->type()), head_);
}

Constraint::PropResult SharedLitsClause::propagateTail(Solver& s, Literal, uint32 pos) {
	Literal  other = head_[1^pos];
	for (const Literal* r = data_.shared->begin(), *end = data_.shared->end(); r != end; ++r) {
		// at this point we know that head_[2] is false so we only need to check 
		// that we do not watch the other watched literal twice!
		if (!s.isFalse(*r) && *r != other) {
			head_[pos] = *r; // replace watch
			s.addWatch(~*r, ClauseWatch(this));
			// try to replace cache literal
			switch( std::min(static_cast<uint32>(8), static_cast<uint32>(end-r)) ) {
				case 8: if (!s.isFalse(*++r) && *r != other) { head_[2] = *r; return PropResult(true, false); }
				case 7: if (!s.isFalse(*++r) && *r != other) { head_[2] = *r; return PropResult(true, false); }
				case 6: if (!s.isFalse(*++r) && *r != other) { head_[2] = *r; return PropResult(true, false); }
				case 5: if (!s.isFalse(*++r) && *r != other) { head_[2] = *r; return PropResult(true, false); }
				case 4: if (!s.isFalse(*++r) && *r != other) { head_[2] = *r; return PropResult(true, false); }
				case 3: if (!s.isFalse(*++r) && *r != other) { head_[2] = *r; return PropResult(true, false); }
				case 2: if (!s.isFalse(*++r) && *r != other) { head_[2] = *r; return PropResult(true, false); }
				default: return PropResult(true, false);
			}
		}
	}
	return PropResult(s.force(other, this), true);
}

void SharedLitsClause::reason(Solver& s, Literal p, LitVec& out) {
	ClauseHead::bumpActivity();
	LitVec::size_type i = out.size();
	for (const Literal* r = data_.shared->begin(), *end = data_.shared->end(); r != end; ++r) {
		if (*r != p) { out.push_back(~*r); }
	}
	if (s.strategies().updateLbd && ClauseHead::type() != Constraint_t::static_constraint) {
		setLbd( s.computeLbd(p, &out[0]+i, &out[0]+out.size()) );
	}
}

bool SharedLitsClause::minimize(Solver& s, Literal p, CCMinRecursive* rec) {
	ClauseHead::bumpActivity();
	for (const Literal* r = data_.shared->begin(), *end = data_.shared->end(); r != end; ++r) {
		if (*r != p && !s.ccMinimize(~*r, rec)) { return false; }
	}
	return true;
}

bool SharedLitsClause::isReverseReason(const Solver& s, Literal p, uint32 maxL, uint32 maxN) {
	uint32 notSeen = 0;
	for (const Literal* r = data_.shared->begin(), *end = data_.shared->end(); r != end; ++r) {
		if (*r == p) continue;
		if (!isRevLit(s, *r, maxL)) return false;
		if (!s.seen(r->var()) && ++notSeen > maxN) return false;
	}
	return true;
}

bool SharedLitsClause::simplify(Solver& s, bool reinit) {
	if (ClauseHead::satisfied(s)) {
		detach(s);
		return true;
	}
	uint32 optSize = data_.shared->simplify(s);
	if (optSize == 0) {
		detach(s);
		return true;
	}
	else if (optSize <= Clause::MAX_SHORT_LEN) {
		Literal lits[Clause::MAX_SHORT_LEN];
		Literal* j = lits;
		for (const Literal* r = data_.shared->begin(), *e = data_.shared->end(); r != e; ++r) {
			if (!s.isFalse(*r)) *j++ = *r;
		}
		uint32 rep= extra_.rep;
		// detach & destroy but do not release memory
		detach(s);
		SharedLitsClause::destroy(0, false);
		// construct short clause in "this"
		ClauseHead* h = Clause::newShortClause(s, this, lits, static_cast<uint32>(j-lits), ClauseExtra());
		// restore extra data - safe because memory layout has not changed!
		extra_.rep = rep;
		return h->simplify(s, reinit);
	}
	else if (s.isFalse(head_[2])) {
		// try to replace cache lit with non-false literal
		for (const Literal* r = data_.shared->begin(), *e = data_.shared->end(); r != e; ++r) {
			if (!s.isFalse(*r) && std::find(head_, head_+2, *r) == head_+2) {
				head_[2] = *r;
				break;
			}
		}
	}
	return false;
}

void SharedLitsClause::destroy(Solver* s, bool detachFirst) {
	if (s && detachFirst) {
		ClauseHead::detach(*s);
	}
	data_.shared->release();
	void* mem = this;
	this->~SharedLitsClause();
	if (s) {
		// return memory to solver
		s->freeSmall(mem);
	}
}

bool SharedLitsClause::isSatisfied(const Solver& s, LitVec& freeLits) {
	if (ClauseHead::satisfied(s)) {
		return true;
	}
	Literal* head = head_;
	ValueRep v;
	for (const Literal* r = data_.shared->begin(), *end = data_.shared->end(); r != end; ++r) {
		if ( (v = s.value(r->var())) == value_free ) {
			freeLits.push_back(*r);
		}
		else if (v == trueValue(*r)) {
			head[2] = *r; // remember as cache literal
			return true;
		}
	}
	return false;
}

void SharedLitsClause::toLits(LitVec& out) const {
	out.insert(out.end(), data_.shared->begin(), data_.shared->end());
}

ClauseHead::BoolPair SharedLitsClause::strengthen(Solver&, Literal, bool) {
	return BoolPair(false, false);
}

} }

