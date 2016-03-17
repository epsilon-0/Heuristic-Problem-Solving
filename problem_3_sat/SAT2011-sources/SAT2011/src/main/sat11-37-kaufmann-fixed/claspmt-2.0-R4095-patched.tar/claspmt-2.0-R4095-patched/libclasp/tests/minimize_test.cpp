// 
// Copyright (c) 2006, Benjamin Kaufmann
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
#include <clasp/minimize_constraint.h>

#include <clasp/solver.h>

namespace Clasp { namespace Test {
class MinimizeTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(MinimizeTest);
	CPPUNIT_TEST(testEmpty);
	CPPUNIT_TEST(testOneLevelLits);
	CPPUNIT_TEST(testMultiLevelLits);
	CPPUNIT_TEST(testMultiLevelWeightsAreReused);
	CPPUNIT_TEST(testMergeComplementaryLits);
	CPPUNIT_TEST(testMergeComplementaryLits2);
	CPPUNIT_TEST(testOrder);
	CPPUNIT_TEST(testSkipLevel);
	CPPUNIT_TEST(testReassertAfterBacktrack);
	CPPUNIT_TEST(testConflict);
	CPPUNIT_TEST(testOptimize);
	CPPUNIT_TEST(testEnumerate);
	CPPUNIT_TEST(testComputeImplicationLevel);
	CPPUNIT_TEST(testSetModelMayBacktrackMultiLevels);
	CPPUNIT_TEST(testPriorityBug);
	CPPUNIT_TEST(testStrengthenImplication);
	CPPUNIT_TEST(testRootLevelMadness);
	CPPUNIT_TEST(testIntegrateOptimum);
	CPPUNIT_TEST(testIntegrateOptimumConflict);

	CPPUNIT_TEST(testReasonBug);
	CPPUNIT_TEST(testSmartBacktrack);
	CPPUNIT_TEST(testBacktrackToTrue);
	CPPUNIT_TEST(testMultiAssignment);
	CPPUNIT_TEST(testBugBacktrackFromFalse);
	CPPUNIT_TEST(testBugBacktrackToTrue);
	CPPUNIT_TEST(testWeightNullBug);
	CPPUNIT_TEST(testAdjust);
	CPPUNIT_TEST(testAdjustFact);
	CPPUNIT_TEST(testAssumption);

	CPPUNIT_TEST(testHierarchicalSetModel);
	CPPUNIT_TEST(testHierarchical);
	CPPUNIT_TEST_SUITE_END(); 
public:
	MinimizeTest() {
		a     = posLit(ctx.addVar(Var_t::atom_var));
		b     = posLit(ctx.addVar(Var_t::atom_var));
		c     = posLit(ctx.addVar(Var_t::atom_var));
		d     = posLit(ctx.addVar(Var_t::atom_var));
		e     = posLit(ctx.addVar(Var_t::atom_var));
		f     = posLit(ctx.addVar(Var_t::atom_var));
		x     = posLit(ctx.addVar(Var_t::atom_var));
		y     = posLit(ctx.addVar(Var_t::atom_var));
		ctx.startAddConstraints(solver);
	}
	void setUp()    { newMin = 0; data = 0; }
	void tearDown() { 
		if (newMin) { 
			newMin->destroy(&solver, true); 
		} 
		if (data) {
			data->destroy();
		}
	}

	void testEmpty() {
		newMin = MinimizeBuilder().buildAndAttach(solver);
		CPPUNIT_ASSERT(countMinLits() == 0);
	}

	void testOneLevelLits() {
		WeightLitVec min;
		solver.force(c, 0);
		solver.force(~e, 0);
		solver.propagate();
		min.push_back( WeightLiteral(a, 1) );
		min.push_back( WeightLiteral(b, 2) );
		min.push_back( WeightLiteral(c, 1) ); // true lit
		min.push_back( WeightLiteral(a, 2) ); // duplicate lit
		min.push_back( WeightLiteral(d, 1) );
		min.push_back( WeightLiteral(e, 2) ); // false lit
		newMin = MinimizeBuilder().addRule(min).buildAndAttach(solver);
		CPPUNIT_ASSERT(newMin->numRules() == 1);
		CPPUNIT_ASSERT(countMinLits() == 3);
		CPPUNIT_ASSERT(newMin->shared()->sum()[0] == 1);
		const SharedMinimizeData* data = newMin->shared();
		CPPUNIT_ASSERT(data->lits[0].first == a && data->lits[0].second == 3);
		for (const WeightLiteral* it = data->lits; !isSentinel(it->first); ++it) {
			CPPUNIT_ASSERT_MESSAGE("Minimize lits not sorted!", it->second >= (it+1)->second);
			CPPUNIT_ASSERT(solver.hasWatch(it->first, newMin));
			CPPUNIT_ASSERT(solver.sharedContext()->frozen(it->first.var()));
		}
		newMin->destroy(&solver, true);
		newMin = 0;
		CPPUNIT_ASSERT(!solver.hasWatch(a, newMin));
	}

	void testMultiLevelLits() {
		MinimizeBuilder builder;
		WeightLitVec min;
		solver.force(c, 0);
		solver.force(~e, 0);
		solver.propagate();
		min.push_back( WeightLiteral(a, 1) );
		min.push_back( WeightLiteral(b, 1) );
		min.push_back( WeightLiteral(c, 1) ); // true lit
		min.push_back( WeightLiteral(b, 2) ); // duplicate lit
		min.push_back( WeightLiteral(d, 1) );
		min.push_back( WeightLiteral(b, 1) ); // duplicate lit
		
		builder.addRule(min);
		min.clear();
		min.push_back( WeightLiteral(e, 2) ); // false lit
		min.push_back( WeightLiteral(f, 1) );
		min.push_back( WeightLiteral(x, 2) );
		min.push_back( WeightLiteral(y, 3) );
		min.push_back( WeightLiteral(b, 1) ); // duplicate lit
		builder.addRule(min);
		min.clear();
		min.push_back( WeightLiteral(b, 2) ); // duplicate lit
		min.push_back( WeightLiteral(a, 1) ); // duplicate lit
		min.push_back( WeightLiteral(a, 2) ); // duplicate lit
		min.push_back( WeightLiteral(c, 2) ); // true lit
		min.push_back( WeightLiteral(d, 1) ); // duplicate lit
		builder.addRule(min);
		
		newMin = builder.buildAndAttach(solver);
		CPPUNIT_ASSERT(newMin->numRules() == 3);
		CPPUNIT_ASSERT(countMinLits() == 6);
		const SharedMinimizeData* data = newMin->shared();
		CPPUNIT_ASSERT(data->sum()[0] == 1 && data->sum()[1] == 0 && data->sum()[2] == 2);
		CPPUNIT_ASSERT(data->lits[0].first == b);
		CPPUNIT_ASSERT(data->weights.size() == 11);
		for (const WeightLiteral* it = data->lits; !isSentinel(it->first); ++it) {
			CPPUNIT_ASSERT(solver.hasWatch(it->first, newMin));
		}
	}

	void testMultiLevelWeightsAreReused() {
		MinimizeBuilder builder;
		WeightLitVec min;
		min.push_back( WeightLiteral(a, 1) );
		min.push_back( WeightLiteral(b, 1) );
		min.push_back( WeightLiteral(b, 2) );
		min.push_back( WeightLiteral(c, 1) );
		min.push_back( WeightLiteral(d, 3) );
		builder.addRule(min);
		
		min.clear();
		min.push_back( WeightLiteral(b, 1) );
		min.push_back( WeightLiteral(d, 1) );
		builder.addRule(min);
		
		newMin = builder.buildAndAttach(solver);
		// b = 0
		// d = 0
		// a = 2
		// c = 2
		// weights: [(0,3)(1,1)][(0,1)] + [(1,0)] for sentinel
		CPPUNIT_ASSERT(newMin->shared()->weights.size() == 4);
	}

	void testMergeComplementaryLits() {
		MinimizeBuilder builder;
		WeightLitVec min;
		min.push_back( WeightLiteral(a, 1) );
		min.push_back( WeightLiteral(b, 1) );
		min.push_back( WeightLiteral(c, 2) );
		min.push_back( WeightLiteral(d, 1) );
		min.push_back( WeightLiteral(~d, 2) );
		builder.addRule(min);
		min.clear();
		min.push_back( WeightLiteral(~c, 1) );
		min.push_back( WeightLiteral(e, 1) );
		builder.addRule(min);
		newMin = builder.buildAndAttach(solver);
		CPPUNIT_ASSERT(countMinLits() == 5);
		CPPUNIT_ASSERT(newMin->shared()->sum()[0] == 1 && newMin->shared()->sum()[1] == 1);

		solver.assume(c) && solver.propagate();
		CPPUNIT_ASSERT(newMin->sum(1) == 0);

	}

	void testMergeComplementaryLits2() {
		MinimizeBuilder builder;
		WeightLitVec min;
		min.push_back( WeightLiteral(a, 1) );
		min.push_back( WeightLiteral(~a, 1) );
		builder.addRule(min);
		min.clear();
		min.push_back( WeightLiteral(a, 1) );
		builder.addRule(min);
		newMin = builder.buildAndAttach(solver);
		CPPUNIT_ASSERT(countMinLits() == 1);
		CPPUNIT_ASSERT(newMin->shared()->sum()[0] == 1 && newMin->shared()->sum()[1] == 0);
	}
	
	void testOrder() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(a, 1) );
		bMin.push_back( WeightLiteral(b, 1) );
		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver);
		
		solver.assume(b);
		CPPUNIT_ASSERT_EQUAL(true, solver.propagate());
		solver.assume(~a);
		CPPUNIT_ASSERT_EQUAL(true, solver.propagate());
		CPPUNIT_ASSERT(newMin->sum(0) == 0 && newMin->sum(1) == 1);
		solver.undoUntil(newMin->setModel(solver));
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.isFalse(a));
		CPPUNIT_ASSERT(solver.isFalse(b));
		CPPUNIT_ASSERT(solver.decisionLevel() == 0);
	}

	void testSkipLevel() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(c, 2) );
		aMin.push_back( WeightLiteral(d, 1) );
		aMin.push_back( WeightLiteral(e, 2) );
		
		bMin.push_back( WeightLiteral(a, 1) );
		bMin.push_back( WeightLiteral(b, 1) );

		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver);
				
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(~d) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());
		solver.force(~e, 0); solver.propagate();
		CPPUNIT_ASSERT_EQUAL(uint32(3), newMin->setModel(solver));
		solver.backtrack();
		solver.force(e, 0);
		CPPUNIT_ASSERT_EQUAL(true, newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.decisionLevel() == 2 && solver.backtrackLevel() == 2);
		CPPUNIT_ASSERT(solver.isFalse(c) && solver.isFalse(e));
		solver.backtrack();
	} 

	void testReassertAfterBacktrack() {
		WeightLitVec aMin;
		aMin.push_back( WeightLiteral(x, 1) );
		aMin.push_back( WeightLiteral(y, 1) );
		newMin = MinimizeBuilder().addRule(aMin).buildAndAttach(solver);
		// disable backjumping
		solver.sharedContext_unsafe()->setProject(a.var(), true);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(~x) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(y) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(uint32(2), newMin->setModel(solver));
		solver.undoUntil(1);
		solver.setBacktrackLevel(1);
		CPPUNIT_ASSERT_EQUAL(true, newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.decisionLevel() == 1 && solver.isTrue(~x));
		solver.backtrack();
		CPPUNIT_ASSERT(solver.decisionLevel() == 0 && solver.isTrue(~x));
	}

	void testConflict() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(c, 2) );
		aMin.push_back( WeightLiteral(d, 1) );
		aMin.push_back( WeightLiteral(e, 2) );
		
		bMin.push_back( WeightLiteral(a, 1) );
		bMin.push_back( WeightLiteral(b, 1) );

		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver);
				
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(~d) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());
		solver.force(~e, 0); solver.propagate();
		CPPUNIT_ASSERT_EQUAL(uint32(3), newMin->setModel(solver));
		solver.undoUntil(0);
		CPPUNIT_ASSERT_EQUAL(true, newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		solver.force(c, 0);
		solver.force(d, 0);
		CPPUNIT_ASSERT_EQUAL(false, solver.propagate());
		const LitVec& cfl = solver.conflict();
		CPPUNIT_ASSERT(cfl.size() == 3);
		CPPUNIT_ASSERT(std::find(cfl.begin(), cfl.end(), a) != cfl.end());
		CPPUNIT_ASSERT(std::find(cfl.begin(), cfl.end(), c) != cfl.end());
		CPPUNIT_ASSERT(std::find(cfl.begin(), cfl.end(), d) != cfl.end());
	} 

	void testOptimize() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		bMin.push_back( WeightLiteral(c, 1) );
		bMin.push_back( WeightLiteral(d, 1) );
		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(1u, newMin->setModel(solver));
		solver.undoUntil(0);
		CPPUNIT_ASSERT_EQUAL(true, newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(d) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~a));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~b));
		CPPUNIT_ASSERT_EQUAL(value_free, solver.value(c.var()));
	}

	void testEnumerate() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		bMin.push_back( WeightLiteral(c, 1) );
		bMin.push_back( WeightLiteral(d, 1) );
		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver, MinimizeMode_t::enumerate);
		
		MinimizeConstraint::SumVec vec;
		vec.push_back(1);
		vec.push_back(1);
		CPPUNIT_ASSERT_EQUAL(true, setOptimum(solver, vec, false));
		CPPUNIT_ASSERT_EQUAL(true, solver.propagate());
		
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());

		CPPUNIT_ASSERT_EQUAL(1u, newMin->setModel(solver));
		solver.undoUntil(0);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(d) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT(solver.isTrue(~c));
		CPPUNIT_ASSERT(solver.isTrue(~a));
	}

	void testComputeImplicationLevel() {
		WeightLitVec aMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		aMin.push_back( WeightLiteral(c, 1) );
		aMin.push_back( WeightLiteral(d, 2) );
		newMin = MinimizeBuilder()
			.addRule(aMin)
			.buildAndAttach(solver, MinimizeMode_t::optimize);
		
		solver.assume(a) && solver.propagate();
		solver.force(b,0)&& solver.propagate();
		solver.assume(c) && solver.propagate();
		solver.force(~d,0) && solver.propagate();
		CPPUNIT_ASSERT_EQUAL(1u, newMin->setModel(solver));
		solver.undoUntil(1u);
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.isFalse(d));
		LitVec r1, r2;
		solver.reason(~d, r1);
		solver.undoUntil(0);
		solver.assume(a) && solver.propagate();
		solver.reason(~d, r2);
		CPPUNIT_ASSERT(r2.size() <= r1.size() && r2.size() == 1);
		CPPUNIT_ASSERT(r1[0] == r2[0]);
		CPPUNIT_ASSERT(r1.size() == 1 || b == r1[1]);
		CPPUNIT_ASSERT_MESSAGE("TODO: REASON CORRECT BUT NOT MINIMAL!", r1.size() == r2.size());
	}

	void testSetModelMayBacktrackMultiLevels() {
		WeightLitVec aMin;
		aMin.push_back( WeightLiteral(a, 1) );
		newMin = MinimizeBuilder().addRule(aMin).buildAndAttach(solver);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(0u, newMin->setModel(solver));
	}

	void testPriorityBug() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		aMin.push_back( WeightLiteral(c, 1) );
		bMin.push_back( WeightLiteral(d, 1) );
		bMin.push_back( WeightLiteral(e, 1) );
		bMin.push_back( WeightLiteral(f, 1) );
		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver);
		// disbale backjumping
		solver.sharedContext_unsafe()->setProject(a.var(), true);
		solver.sharedContext_unsafe()->setProject(e.var(), true);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(e) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(f) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(2u, newMin->setModel(solver));
		solver.backtrack();
		CPPUNIT_ASSERT_EQUAL(true, newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.decisionLevel() == 2);
		solver.backtrack();
		CPPUNIT_ASSERT_EQUAL(true, solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(d) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~b));
		LitVec r;
		solver.reason(~b, r);
		CPPUNIT_ASSERT(LitVec::size_type(1) == r.size());
		CPPUNIT_ASSERT(a == r[0]);
	}

	void testStrengthenImplication() {
		WeightLitVec aMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 2) );
		aMin.push_back( WeightLiteral(c, 1) );
		newMin = MinimizeBuilder().addRule(aMin).buildAndAttach(solver);
		CPPUNIT_ASSERT(setOptimum(solver, MinimizeConstraint::SumVec(1, 2), false));
		solver.assume(a) && solver.propagate();
		solver.setBacktrackLevel(1);
		solver.sharedContext_unsafe()->setProject(a.var(), true);
		CPPUNIT_ASSERT(solver.isTrue(~b));
		LitVec r;
		solver.reason(~b, r);
		CPPUNIT_ASSERT(r.size() == 1 && r[0] == a);
		solver.assume(x) && solver.propagate();
		solver.assume(y) && solver.propagate();
		solver.assume(c) && solver.propagate();
		solver.assume(e) && solver.propagate();
		CPPUNIT_ASSERT(newMin->setModel(solver) == 3);
		solver.undoUntil(3);
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.decisionLevel() == 1 && solver.isTrue(~b));
		r.clear();
		solver.reason(~b, r);
		CPPUNIT_ASSERT(r.empty() || (r.size() == 1 && r[0] == posLit(0)));
	}

	void testRootLevelMadness() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 2) );
		aMin.push_back( WeightLiteral(c, 1) );
		bMin.push_back( WeightLiteral(d, 1) );
		bMin.push_back( WeightLiteral(e, 2) );
		bMin.push_back( WeightLiteral(f, 1) );
		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver);
		solver.assume(a) && solver.propagate();
		solver.assume(c) && solver.propagate();
		solver.pushRootLevel(2);
		MinimizeConstraint::SumVec opt(newMin->numRules());
		opt[0] = 2;
		opt[1] = 3;
		setOptimum(solver, opt, false);
		LitVec r;
		CPPUNIT_ASSERT(solver.isFalse(b));
		solver.reason(~b, r);
		CPPUNIT_ASSERT(r.size() == 1 && r[0] == a);
		solver.clearAssumptions();
		solver.assume(d) && solver.propagate();
		solver.assume(e) && solver.propagate();
		solver.assume(f) && solver.propagate();
		solver.pushRootLevel(3);
		opt[0] = 2;
		opt[1] = 2;
		setOptimum(solver, opt, false);
		CPPUNIT_ASSERT(solver.isFalse(b));
		r.clear();
		solver.reason(~b, r);
		CPPUNIT_ASSERT(r.size() == 2 && r[0] == d && r[1] == e);
	}

	void testIntegrateOptimum() {
		WeightLitVec aMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		aMin.push_back( WeightLiteral(c, 1) );
		aMin.push_back( WeightLiteral(d, 1) );
		data   = MinimizeBuilder().addRule(aMin).build(solver);
		newMin = createMin(solver, data);
		solver.assume(a) && solver.propagate();
		solver.assume(e) && solver.propagate();
		solver.assume(b) && solver.propagate();
		solver.assume(f) && solver.propagate();
		solver.assume(c) && solver.propagate();
		
		SharedMinimizeData::SumVec opt(data->numRules());
		opt[0] = 2;
		CPPUNIT_ASSERT(setOptimum(solver, opt, true));
		CPPUNIT_ASSERT(solver.decisionLevel() == 1 && solver.queueSize() == 3);
		newMin->destroy(&solver, true);
		newMin = 0;
	}

	void testIntegrateOptimumConflict() {
		WeightLitVec aMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		aMin.push_back( WeightLiteral(c, 1) );
		aMin.push_back( WeightLiteral(d, 1) );
		data = MinimizeBuilder().addRule(aMin).build(solver);
		SharedMinimizeData::SumVec opt(data->numRules());
		newMin = createMin(solver, data);
		solver.assume(a) && solver.propagate();
		solver.assume(e) && solver.propagate();
		solver.assume(b) && solver.propagate();
		solver.assume(f) && solver.propagate();
		solver.assume(c) && solver.propagate();
		solver.sharedContext_unsafe()->setProject(a.var(), true);
		solver.sharedContext_unsafe()->setProject(b.var(), true);
		solver.setBacktrackLevel(3);
		opt[0] = 2;
		CPPUNIT_ASSERT(!setOptimum(solver, opt, true));
		CPPUNIT_ASSERT(solver.hasConflict());
		CPPUNIT_ASSERT(solver.resolveConflict() && solver.propagate());
		CPPUNIT_ASSERT(newMin->integrateNext(solver) == true);
		CPPUNIT_ASSERT(solver.decisionLevel() == 1 && solver.queueSize() == 3);
		solver.propagate();
		opt[0] = 0;
		CPPUNIT_ASSERT(!setOptimum(solver, opt, true));
		CPPUNIT_ASSERT(solver.hasConflict());
		CPPUNIT_ASSERT(solver.clearAssumptions());
		CPPUNIT_ASSERT(newMin->integrateNext(solver) == false && solver.hasConflict());
		CPPUNIT_ASSERT(!solver.resolveConflict());
		newMin->destroy(&solver, true);
		newMin = 0;
	}

	void testReasonBug() {
		WeightLitVec aMin, bMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		bMin.push_back( WeightLiteral(d, 2) );
		bMin.push_back( WeightLiteral(e, 1) );
		bMin.push_back( WeightLiteral(f, 3) );
		
		newMin = MinimizeBuilder()
			.addRule(aMin)
			.addRule(bMin)
			.buildAndAttach(solver);
		
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(d) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(2u, newMin->setModel(solver));
		solver.backtrack();
		CPPUNIT_ASSERT_EQUAL(true, newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(e) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~f));
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());
		solver.backtrack();
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~f));
		LitVec r;
		solver.reason(~f, r);
		CPPUNIT_ASSERT(std::find(r.begin(), r.end(), e) == r.end());
	}

	void testSmartBacktrack() {
		WeightLitVec aMin;
		aMin.push_back( WeightLiteral(a, 1) );
		aMin.push_back( WeightLiteral(b, 1) );
		aMin.push_back( WeightLiteral(c, 1) );
		newMin = MinimizeBuilder().addRule(aMin).buildAndAttach(solver);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(~c) && solver.propagate());
		
		solver.undoUntil(newMin->setModel(solver));
		CPPUNIT_ASSERT_EQUAL(true, newMin->propagateNewOptimum(solver));
		
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~b));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~c));
	}

	void testBacktrackToTrue() {
		WeightLitVec min1, min2;
		min1.push_back( WeightLiteral(a, 1) );
		min2.push_back( WeightLiteral(b, 1) );
		newMin = MinimizeBuilder()
			.addRule(min1)
			.addRule(min2)
			.buildAndAttach(solver);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(~a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.force(b, 0) && solver.propagate());
			
		CPPUNIT_ASSERT(newMin->setModel(solver) == 0);
		solver.backtrack();
		CPPUNIT_ASSERT_EQUAL(false, newMin->propagateNewOptimum(solver));
	}

	void testMultiAssignment() {
		WeightLitVec min1, min2;
		min1.push_back( WeightLiteral(a, 1) );
		min1.push_back( WeightLiteral(b, 1) );
		min1.push_back( WeightLiteral(c, 1) );
		min1.push_back( WeightLiteral(d, 1) );
		min1.push_back( WeightLiteral(e, 1) );

		min2.push_back( WeightLiteral(f, 1) );
		
		newMin = MinimizeBuilder()
			.addRule(min1)
			.addRule(min2)
			.buildAndAttach(solver);
		MinimizeConstraint::SumVec opt(newMin->numRules());
		opt[0] = 3;
		opt[1] = 0;
		CPPUNIT_ASSERT_EQUAL(true, setOptimum(solver, opt, false));
	
		solver.assume(f);
		solver.force(a, 0);
		solver.force(b, 0);
		solver.force(c, 0);
		
		CPPUNIT_ASSERT_EQUAL(false, solver.propagate());
	}
	
	void testBugBacktrackFromFalse() {
		WeightLitVec min1, min2;
		min1.push_back( WeightLiteral(a, 1) );
		min1.push_back( WeightLiteral(b, 1) );
		min1.push_back( WeightLiteral(c, 1) );
		min2.push_back( WeightLiteral(d, 1) );
		min2.push_back( WeightLiteral(e, 1) );
		min2.push_back( WeightLiteral(f, 1) );
		
		newMin = MinimizeBuilder()
			.addRule(min1)
			.addRule(min2)
			.buildAndAttach(solver);
		
		solver.sharedContext_unsafe()->setProject(x.var(), true);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(x) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.force(~c,0) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(y) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.force(d,0) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.force(e,0) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.force(~f,0) && solver.propagate());
		
		solver.undoUntil(newMin->setModel(solver));
		CPPUNIT_ASSERT(3 == solver.decisionLevel());
		solver.setBacktrackLevel(3);
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT_EQUAL(true, solver.force(f,0) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~d));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~e));
		
		uint32 dl = newMin->setModel(solver);
		CPPUNIT_ASSERT(2 == dl);
		solver.backtrack();
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~x));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~f));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~d));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~e));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(~c));
	}
	
	void testBugBacktrackToTrue() {
		WeightLitVec min1, min2;
		min1.push_back( WeightLiteral(a, 1) );
		min1.push_back( WeightLiteral(b, 1) );
		min1.push_back( WeightLiteral(~b, 2) );
		min2.push_back( WeightLiteral(a, 1) );
		min2.push_back( WeightLiteral(b, 1) );
		min2.push_back( WeightLiteral(c, 1) );
		
		newMin = MinimizeBuilder()
			.addRule(min1)
			.addRule(min2)
			.buildAndAttach(solver);
		
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());

		solver.undoUntil(newMin->setModel(solver));
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver) && 1 == solver.decisionLevel());
		CPPUNIT_ASSERT(solver.propagate());
		
		uint32 dl = newMin->setModel(solver);
		CPPUNIT_ASSERT(dl == 0);
		solver.undoUntil(dl);
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.isTrue(~a));
		CPPUNIT_ASSERT(solver.value(b.var()) == value_free);
	}

	void testWeightNullBug() {
		WeightLitVec min1;
		min1.push_back( WeightLiteral(a, 1) );
		min1.push_back( WeightLiteral(b, 0) );
		newMin = MinimizeBuilder().addRule(min1).buildAndAttach(solver);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.force(~c,0) && solver.propagate());
		solver.undoUntil(newMin->setModel(solver));
		newMin->propagateNewOptimum(solver);
		CPPUNIT_ASSERT(0u == solver.decisionLevel() && solver.isFalse(a));
	}

	void testAdjust() {
		WeightLitVec min1;
		min1.push_back( WeightLiteral(a, 1) );
		min1.push_back( WeightLiteral(b, 1) );
		newMin = MinimizeBuilder().addRule(min1, -2).buildAndAttach(solver);
		
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		uint32 DL = newMin->setModel(solver);
		CPPUNIT_ASSERT(DL < solver.decisionLevel());
		solver.undoUntil(DL);
		CPPUNIT_ASSERT(0 == newMin->shared()->optimum()->opt[0]);
		
		solver.clearAssumptions();
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(~a) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(~b) && solver.propagate());
		DL = newMin->setModel(solver);
		CPPUNIT_ASSERT(DL == UINT32_MAX);
		CPPUNIT_ASSERT(-2 == newMin->shared()->optimum()->opt[0]);
	}

	void testAdjustFact() {
		WeightLitVec min1;
		min1.push_back( WeightLiteral(a, 2) );
		min1.push_back( WeightLiteral(b, 1) );
		min1.push_back( WeightLiteral(c, 1) );
		min1.push_back( WeightLiteral(d, 1) );
		data = MinimizeBuilder().addRule(min1, -2).build(solver);
		solver.addUnary(a, Constraint_t::static_constraint);
		solver.propagate();
		newMin = createMin(solver, data);
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(b) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(c) && solver.propagate());
		CPPUNIT_ASSERT_EQUAL(true, solver.assume(d) && solver.propagate());
		solver.undoUntil(newMin->setModel(solver));
		newMin->propagateNewOptimum(solver);
		CPPUNIT_ASSERT(2 == solver.decisionLevel());
	}

	void testAssumption() {
		WeightLitVec min1;
		min1.push_back( WeightLiteral(a, 1) );
		min1.push_back( WeightLiteral(b, 1) );
		min1.push_back( WeightLiteral(c, 1) );
		Literal minAssume = d;
		data   = MinimizeBuilder().addRule(min1).build(solver, minAssume);
		newMin = createMin(solver, data);
		solver.assume(minAssume);
		solver.pushRootLevel(1);
		solver.propagate();
		
		setOptimum(solver, SharedMinimizeData::SumVec(1, 0), false);
		CPPUNIT_ASSERT(solver.isFalse(a) && solver.reason(~a).constraint() == newMin);
		CPPUNIT_ASSERT(solver.isFalse(b) && solver.reason(~b).constraint() == newMin);
		CPPUNIT_ASSERT(solver.isFalse(c) && solver.reason(~c).constraint() == newMin);

		LitVec r;
		solver.reason(~a, r);
		CPPUNIT_ASSERT(r.size() == 1 && r[0] == minAssume);

		solver.clearAssumptions();
		newMin->propagateNewOptimum(solver);
		CPPUNIT_ASSERT(solver.numAssignedVars() == 0);
	}

	void testHierarchicalSetModel() {
		WeightLitVec min;
		min.push_back( WeightLiteral(a, 1) );
		min.push_back( WeightLiteral(b, 1) );
		min.push_back( WeightLiteral(c, 1) );
		MinimizeBuilder builder;
		builder.addRule(min);
		min.clear();
		min.push_back( WeightLiteral(d, 1) );
		min.push_back( WeightLiteral(e, 1) );
		min.push_back( WeightLiteral(f, 1) );
		builder.addRule(min);
		
		data   = builder.build(solver);
		newMin = createMin(solver, data);
		solver.assume(a); solver.propagate();
		solver.assume(b); solver.propagate();
		solver.assume(c); solver.propagate();
		solver.assume(d); solver.propagate();
		solver.assume(e); solver.propagate();
		solver.assume(f); solver.propagate();
		data->setMode(MinimizeMode_t::optimize, true);
		CPPUNIT_ASSERT(newMin->setModel(solver) == 2);
		solver.undoUntil(2);
		newMin->propagateNewOptimum(solver);
		CPPUNIT_ASSERT(solver.isFalse(c));
		CPPUNIT_ASSERT(solver.numAssignedVars() == 3);
	}

	void testHierarchical() {
		MinimizeBuilder builder;
		WeightLitVec min;
		min.push_back( WeightLiteral(a, 1) );
		builder.addRule(min);
		min.clear();
		min.push_back( WeightLiteral(~b, 1) );
		builder.addRule(min);
		
		solver.addBinary(~a, b, Constraint_t::static_constraint);
		solver.addBinary(a, ~b, Constraint_t::static_constraint);

		data   = builder.build(solver);
		newMin = createMin(solver, data);

		data->setMode(MinimizeMode_t::optimize, 1);

		ctx.endInit();
		solver.assume(a);
		solver.propagate();
		uint32 x = newMin->setModel(solver);
		CPPUNIT_ASSERT(x == 0);
		solver.backtrack();
		CPPUNIT_ASSERT(newMin->propagateNewOptimum(solver));
		CPPUNIT_ASSERT(solver.propagate() == true);
		x = newMin->setModel(solver);
		CPPUNIT_ASSERT(x == UINT32_MAX);
	}
private:
	uint32 countMinLits() const {
		uint32 lits = 0;
		const WeightLiteral* it = newMin->shared()->lits;
		for (; !isSentinel(it->first); ++it, ++lits) { ; }
		return lits;
	}
	bool setOptimum(Solver& s, const SharedMinimizeData::SumVec& vec, bool less) {
		SharedMinimizeData* data = const_cast<SharedMinimizeData*>(newMin->shared());
		data->setOptimum(&vec[0]);
		if (less) {
			return newMin->integrateNext(solver);	
		}
		else {
			newMin->restoreOptimum();
			return newMin->propagateNewOptimum(solver);
		}
	}
	MinimizeConstraint* createMin(Solver& s, SharedMinimizeData* data) {
		return MinimizeBuilder::attach(s, data);
	}
	Solver solver;
	SharedContext ctx;
	MinimizeConstraint* newMin;
	SharedMinimizeData* data;
	Literal a, b, c, d, e, f, x, y;
};
CPPUNIT_TEST_SUITE_REGISTRATION(MinimizeTest);
} } 
