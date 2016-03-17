// 
// Copyright (c) 2006-2011, Benjamin Kaufmann
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
#include <clasp/cb_enumerator.h>
#include <clasp/solver.h>
#include <clasp/clause.h>
#include <clasp/shared_clause.h>
#include <clasp/util/mutex.h>
#include <stdio.h> // sprintf
#ifdef _MSC_VER
#pragma warning (disable : 4996) // sprintf may be unfase
#endif
namespace Clasp { namespace detail {

struct SingleThreadImpl : public CBConsequences::GlobalConstraint {
	ClauseHead*     set(Solver& s, const LitVec& c) {
		return c.size() > 1
			? Clause::newLearntClause(s, c, ClauseExtra().setType(Constraint_t::learnt_other))
			: 0;
	}
	mt::SharedLiterals* getShared() { return 0; }
};

struct MultiThreadImpl : public CBConsequences::GlobalConstraint {
	MultiThreadImpl() : current(0) {}
	typedef mt::SharedLiterals SharedLiterals;
	ClauseHead*     set(Solver& s, const LitVec& c) {
		SharedLiterals* newShared = SharedLiterals::newShareable(c, Constraint_t::learnt_other, 2);
		set(newShared);
		ClauseCreator::Result ret = ClauseCreator::integrate(s, newShared, 
			ClauseCreator::clause_explicit|ClauseCreator::clause_no_add|ClauseCreator::clause_known_order);
		return ret.local;
	}
	void set(SharedLiterals* x) {
		SharedLiterals* old = current;
		{ mt::SpinMutex::scoped_lock lock(mutex);
			current = x;
		}
		if (old) old->release();
	}
	mt::SharedLiterals* getShared() {
		mt::SpinMutex::scoped_lock lock(mutex);
		return current 
			? current->share()
			: 0;
	}
	mt::SpinMutex   mutex;
	SharedLiterals* current;
};

}

CBConsequences::CBConsequences(Consequences_t type) 
	: Enumerator(0)
	, current_(0)
	, type_(type) {
	current_ = 0;
}

CBConsequences::~CBConsequences() {
	delete current_;
}

Enumerator::SolveConstraint* CBConsequences::doInit(SharedContext& ctx, uint32 t, bool start) {
	delete current_;
	current_ = 0;
	if (start) {
		if (!ctx.symTab().used()) {
			ctx.symTab().startInit();
			char buf[1024];
			for (Var v = 1; v <= ctx.numVars(); ++v) {
				sprintf(buf, "%u", v);
				ctx.symTab().addUnique(v, buf).lit = posLit(v);
			}
			ctx.symTab().endInit();
		}
		const SymbolTable& index = ctx.symTab();
		for (SymbolTable::const_iterator it = index.curBegin(); it != index.end(); ++it) {
			if (!it->second.name.empty()) { 
				ctx.setFrozen(it->second.lit.var(), true);
				if (type_ == cautious_consequences) {
					it->second.lit.watch();  
				}
			}
		} 
		return 0;
	}
	else if (t <= 1) { current_ = new detail::SingleThreadImpl;  }
	else             { current_ = new detail::MultiThreadImpl;   }
	return new CBConstraint();
}

bool CBConsequences::ignoreSymmetric() const { return true; }

void CBConsequences::updateModel(Solver& s) {
	C_.clear();
	type_ == brave_consequences
			? updateBraveModel(s)
			: updateCautiousModel(s);
	for (LitVec::size_type i = 0; i != C_.size(); ++i) {
		s.clearSeen(C_[i].var());
	}
}

void CBConsequences::add(Solver& s, Literal p) {
	assert(s.isTrue(p));
	if (!s.seen(p.var())) {
		C_.push_back(~p); // invert literal: store nogood as clause
		if (s.level(p.var()) > s.level(C_[0].var())) {
			std::swap(C_[0], C_.back());
		}
		s.markSeen(p);
	}
}

void CBConsequences::updateBraveModel(Solver& s) {
	const SymbolTable& index = s.sharedContext()->symTab();
	for (SymbolTable::const_iterator it = index.begin(); it != index.end(); ++it) {
		if (!it->second.name.empty()) {
			Literal& p = it->second.lit;
			if (s.isTrue(p))  { p.watch(); }
			if (!p.watched()) { add(s, ~p); }
		}
	}
}

void CBConsequences::updateCautiousModel(Solver& s) {
	const SymbolTable& index = s.sharedContext()->symTab();
	for (SymbolTable::const_iterator it = index.begin(); it != index.end(); ++it) {
		Literal& p = it->second.lit;
		if (p.watched()) { 
			if      (s.isFalse(p))  { p.clearWatch(); }
			else if (s.isTrue(p))   { add(s, p); }
		}
	}
}

// integrate current global constraint into s
bool CBConsequences::updateConstraint(Solver& s, bool) {
	assert(s.getEnumerationConstraint() && "CBConsequences solver not attached!");
	mt::SharedLiterals* x = current_->getShared();
	return static_cast<CBConstraint*>(s.getEnumerationConstraint())->integrate(s, x);		
}

Constraint* CBConsequences::addNewConstraint(Solver& s) {
	// create and set new global constraint
	ClauseHead* ret = current_->set(s, C_);
	if (ret) {
		// add new local constraint to the given solver
		CBConstraint* con = static_cast<CBConstraint*>(s.getEnumerationConstraint());
		assert(con && "CBConsequences solver not attached!");
		con->add(s, ret);
	}
	return ret;
}

bool CBConsequences::backtrack(Solver& s) {
	if (C_.empty()) {
		// no more consequences possible
		s.clearAssumptions();
		return false;
	}
	// C_ stores the violated nogood, ie. the new integrity constraint.
	// C_[0] is the literal assigned on the highest DL and hence the
	// decision level on which we must analyze the conflict.
	uint32 newDl = s.level(C_[0].var());
	if (getHighestActiveLevel() < newDl) {
		// C_ is not the most important nogood, ie. there is some other
		// nogood that is violated below C_. 
		newDl = getHighestActiveLevel() - 1;
	}
	s.undoUntil(newDl, true);
	Constraint* c = addNewConstraint(s);
	if (s.isFalse(C_[0])) {
		// C_ is still violated - set and resolve conflict
		return s.force(C_[0], c) || s.resolveConflict();
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
// class CBConsequences::CBConstraint
/////////////////////////////////////////////////////////////////////////////////////////
Constraint* CBConsequences::CBConstraint::cloneAttach(Solver& other) {
	CBConstraint* ret = new CBConstraint();
	ret->setMinimize(cloneMini(other));
	return ret;
}
void CBConsequences::CBConstraint::destroy(Solver* s, bool detach) {
	assert(!s || s->decisionLevel() == s->rootLevel());
	if (!locked.empty()) {
		static_cast<ClauseHead*>(locked.back())->destroy(s, true);
		locked.pop_back();
	}
	for (ConstraintDB::size_type i = 0; i != locked.size(); ++i) {
		static_cast<ClauseHead*>(locked[i])->destroy(s, false);
	}
	locked.clear();
	SolveConstraint::destroy(s, detach);
}
void CBConsequences::CBConstraint::add(Solver& s, Constraint* c) {
	if (!locked.empty()) {
		static_cast<ClauseHead*>(locked.back())->detach(s);
		ConstraintDB::size_type j = 0; 
		for (ConstraintDB::size_type i = 0; i != locked.size(); ++i) {
			ClauseHead* c = (ClauseHead*)locked[i];
			if (c->locked(s)) locked[j++] = c;
			else c->destroy(&s, false);
		}
		locked.erase(locked.begin()+j, locked.end());
	}
	locked.push_back(c);
}
bool CBConsequences::CBConstraint::integrate(Solver& s, mt::SharedLiterals* clause) {
	if (!clause) return true;
	ClauseCreator::Result ret;
	if (clause->size() > 0) {
		ret = ClauseCreator::integrate(s, clause, ClauseCreator::clause_explicit|ClauseCreator::clause_no_add);
		if (ret.local) { add(s, ret.local); }
	}
	else {
		s.setStopConflict();
		ret.ok = false;
	}
	return ret.ok;
}

}
