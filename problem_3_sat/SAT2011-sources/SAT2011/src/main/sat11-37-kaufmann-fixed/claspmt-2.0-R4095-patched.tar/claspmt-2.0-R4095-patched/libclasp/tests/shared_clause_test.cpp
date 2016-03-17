// 
// Copyright (c) 2009, Benjamin Kaufmann
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

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>
#include <algorithm>
#include <clasp/shared_clause.h>
#include <clasp/solver.h>

#ifdef _MSC_VER
#pragma warning (disable : 4267) //  conversion from 'size_t' to unsigned int
#pragma once
#endif


namespace Clasp { namespace Test {
using namespace Clasp::mt;
class OtherClausesTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(OtherClausesTest);
	CPPUNIT_TEST(testClauseCtorAddsWatches);
	CPPUNIT_TEST(testPropSharedClauseConflict);
	CPPUNIT_TEST(testPropRandomClauses);
	CPPUNIT_TEST(testPropAlreadySatisfied);
	CPPUNIT_TEST(testReasonBumpsActivityIfLearnt);
	CPPUNIT_TEST(testSimplifySAT);
	CPPUNIT_TEST(testSimplifyUnique);
	CPPUNIT_TEST(testSimplifyShared);

	CPPUNIT_TEST(testCloneShared);
	CPPUNIT_TEST_SUITE_END(); 
public:
	OtherClausesTest() {
		a1 = posLit(ctx.addVar(Var_t::atom_var));
		a2 = posLit(ctx.addVar(Var_t::atom_var));
		a3 = posLit(ctx.addVar(Var_t::atom_var));
		b1 = posLit(ctx.addVar(Var_t::body_var));
		b2 = posLit(ctx.addVar(Var_t::body_var));
		b3 = posLit(ctx.addVar(Var_t::body_var));

		for (int i = 6; i < 15; ++i) {
			ctx.addVar(Var_t::atom_var);
		}
		ctx.startAddConstraints(solver, 10);
	}
	void testClauseCtorAddsWatches() {
		makeLits(2, 2);
		ClauseHead* sharedCl= createShared(solver, clLits, ClauseExtra());
		ctx.add(sharedCl);
		CPPUNIT_ASSERT_EQUAL(2, countWatches(solver, sharedCl, clLits));
	}

	void testPropSharedClauseConflict() {
		makeLits(2, 2);
		ClauseHead* c = createShared(solver, clLits, ClauseExtra());
		simplePropTest(c);
	}

	void testPropRandomClauses() {
		for (int i = 0; i != 100; ++i) {
			solver.reset();
			SharedContext cc;
			solver.strategies().randomWatches = true;
			for (int j = 0; j < 12; ++j) { cc.addVar(Var_t::atom_var); }
			cc.startAddConstraints(solver,1);
			
			makeRandomClause( (rand() % 10) + 2 );
			ClauseHead* c = createShared(solver, clLits, ClauseExtra());
			cc.add(c);
			check(c);
		}
	}

	void testPropAlreadySatisfied() {
		makeLits(2, 2);
		ClauseHead* c1 = createShared(solver, clLits, ClauseExtra());
		solver.add(c1);

		// satisfy the clauses...
		solver.force(clLits[3], 0);
		solver.propagate();

		// ...make all but one literal false
		solver.force(~clLits[0], 0);
		solver.force(~clLits[1], 0);
		solver.propagate();

		// ...and assert that the last literal is still unassigned
		CPPUNIT_ASSERT(value_free == solver.value(clLits[2].var()));
	}

	void testReasonBumpsActivityIfLearnt() {
		makeLits(4, 0);
		ctx.endInit(1);
		ClauseExtra e; e.setType(Constraint_t::learnt_conflict);
		ClauseHead* c = createShared(solver, clLits, e);
		solver.addLearnt(c, (uint32)clLits.size());
		
		solver.assume(~clLits[0]);
		solver.propagate();
		solver.assume(~clLits[1]);
		solver.propagate();
		solver.assume(~clLits[2]);
		solver.propagate();
		
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue( clLits[3] ) );
		uint32 a = c->activity().score();
		LitVec r;
		solver.reason(clLits[3], r);
		CPPUNIT_ASSERT_EQUAL(a+1, c->activity().score());
	}

	void testSimplifySAT() {
		makeLits(3, 2);
		ClauseHead* c1 = createShared(solver, clLits, ClauseExtra());
		solver.add(c1);
		
		solver.force( ~clLits[4], 0);
		solver.force( clLits[3], 0 );
		solver.propagate();

		CPPUNIT_ASSERT_EQUAL(true, c1->simplify(solver, false));
	}

	void testSimplifyUnique() {
		makeLits(3, 3);
		ClauseHead* c = createShared(solver, clLits, ClauseExtra());
		solver.add(c);
		
		solver.force(~clLits[2], 0);
		solver.force(~clLits[3], 0);
		solver.propagate();

		CPPUNIT_ASSERT_EQUAL(false, c->simplify(solver, false));
		CPPUNIT_ASSERT(4 == c->size());
		CPPUNIT_ASSERT_EQUAL(2, countWatches(solver, c, clLits));
	}

	void testSimplifyShared() {
		makeLits(3, 3);
		SharedLiterals* sLits   = SharedLiterals::newShareable(clLits, Constraint_t::learnt_conflict);
		CPPUNIT_ASSERT(sLits->unique() && sLits->type() == Constraint_t::learnt_conflict && sLits->size() == 6);
		SharedLiterals* other   = sLits->share();
		CPPUNIT_ASSERT(!sLits->unique());
		
		solver.force(~clLits[2], 0);
		solver.force(~clLits[3], 0);
		solver.propagate();

		CPPUNIT_ASSERT_EQUAL(uint32(4), sLits->simplify(solver));
		CPPUNIT_ASSERT_EQUAL(uint32(6), sLits->size());
		sLits->release();
		other->release();
	}

	void testCloneShared() {
		makeLits(3, 2);
		ClauseHead* c = createShared(solver, clLits, ClauseExtra());
		ctx.endInit(2);
		Solver solver2;
		ctx.attach(solver2);
		ClauseHead* clone = (ClauseHead*)c->cloneAttach(solver2);
		LitVec lits;
		clone->toLits(lits);
		CPPUNIT_ASSERT(lits == clLits);
		CPPUNIT_ASSERT(countWatches(solver2, clone, clLits) == 2);
		c->destroy(&solver, true);

		for (uint32 i = 0; i != clLits.size()-1; ++i) {
			solver2.assume(~clLits[i]);
			solver2.propagate();
		}
		CPPUNIT_ASSERT(solver2.isTrue(clLits.back()));
		CPPUNIT_ASSERT(solver2.reason(clLits.back()) == clone);

		clone->destroy(&solver2, true);
		
	}
private:
	Solver solver;
	SharedContext ctx;
	LitVec clLits;
	Literal a1, a2, a3, b1, b2, b3;
	ClauseHead* createShared(Solver& s, const LitVec& lits, const ClauseExtra& e) {
		assert(lits.size() >= 2);
		SharedLiterals* shared_lits = SharedLiterals::newShareable(lits, e.type());
		return SharedLitsClause::newClause(s, shared_lits, e, &lits[0], false);
	}
	
	void simplePropTest(ClauseHead* c) {
		solver.add(c);
		solver.assume(~clLits[0]);
		solver.propagate();
		solver.assume( ~clLits.back() );
		solver.propagate();
		solver.assume(~clLits[1]);
		solver.propagate();

		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue( clLits[2] ) );
		CPPUNIT_ASSERT_EQUAL(true, c->locked(solver));
		Antecedent reason = solver.reason(clLits[2]);
		CPPUNIT_ASSERT(reason == c);

		LitVec r;
		reason.reason(solver, clLits[2], r);
		CPPUNIT_ASSERT(std::find(r.begin(), r.end(), ~clLits[0]) != r.end());
		CPPUNIT_ASSERT(std::find(r.begin(), r.end(), ~clLits[1]) != r.end());
		CPPUNIT_ASSERT(std::find(r.begin(), r.end(), ~clLits[3]) != r.end());
	}
	int countWatches(const Solver& s, ClauseHead* c, const LitVec& lits) {
		int w     = 0;
		for (LitVec::size_type i = 0; i != lits.size(); ++i) {
			w += s.hasWatch(~lits[i], c);
		}
		return w;
	}
	void check(ClauseHead* c) {
		std::string s = toString(clLits);
		std::random_shuffle(clLits.begin(), clLits.end());
		CPPUNIT_ASSERT( value_free == solver.value(clLits.back().var()) );
		for (LitVec::size_type i = 0; i != clLits.size() - 1; ++i) {
			CPPUNIT_ASSERT( value_free == solver.value(clLits[i].var()) );
			solver.force(~clLits[i], 0);
			solver.propagate();
		}
		CPPUNIT_ASSERT_EQUAL_MESSAGE(s.c_str(), true, solver.isTrue(clLits.back()));

		Antecedent reason = solver.reason(clLits.back());
		CPPUNIT_ASSERT(reason == c);
		LitVec r;
		c->reason(solver, clLits.back(), r);
		for (LitVec::size_type i = 0; i != clLits.size() - 1; ++i) {
			LitVec::iterator it = std::find(r.begin(), r.end(), ~clLits[i]);
			CPPUNIT_ASSERT_MESSAGE(s.c_str(), it != r.end());
			r.erase(it);
		}
		while (!r.empty() && isSentinel(r.back())) r.pop_back();
		CPPUNIT_ASSERT(r.empty());
	}
	std::string toString(const LitVec& c) {
		std::string res="[";
		for (int i = 0; i != c.size(); ++i) {
			if (c[i].sign()) {
				res += '~';
			}
			res += ('a' + i);
			res += ' ';
		}
		res+="]";
		return res;
	}
	void makeLits(int pos, int neg) {
		clLits.clear();
		int size = pos + neg;
		LitVec lit(size);
		for (int i = 0; i < pos; ++i) {
			lit[i] = posLit(i+1);
			clLits.push_back(lit[i]);
		}
		for (int i = pos; i < pos + neg; ++i) {
			lit[i] = negLit(i+1);
			clLits.push_back(lit[i]);
		}
	}
	void makeRandomClause(int size) {
		int pos = rand() % size + 1;
		makeLits( pos, size - pos ); 
	}
};
CPPUNIT_TEST_SUITE_REGISTRATION(OtherClausesTest);
} } 
