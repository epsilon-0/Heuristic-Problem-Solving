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
#include "common.h"
#include <clasp/heuristics.h>
#include <clasp/lookahead.h>
#include <clasp/program_builder.h>
#include <clasp/clause.h>
#include <clasp/solver.h>
namespace Clasp { namespace Test {

class DecisionHeuristicTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DecisionHeuristicTest);
	CPPUNIT_TEST(testTrivial);
	CPPUNIT_TEST(testBodyLookahead);
	CPPUNIT_TEST(testAtomLookahead);
	CPPUNIT_TEST(testLookaheadBugNoSimplify);
	CPPUNIT_TEST(testLookaheadBugDepsNotCleared);
	CPPUNIT_TEST(testLookaheadBugNoDeps);

	CPPUNIT_TEST(testBerkmin);
	CPPUNIT_TEST(testVmtf);
	CPPUNIT_TEST(testVsids);
	CPPUNIT_TEST(testResurrect);
	CPPUNIT_TEST_SUITE_END();
public:
	void testTrivial() {
		Solver s;
		SharedContext ctx;
		s.strategies().heuristic.reset(new UnitHeuristic(Lookahead::hybrid_lookahead));
		ctx.startAddConstraints(s);
		CPPUNIT_ASSERT_EQUAL(true, ctx.endInit(1));
	}
	void testBodyLookahead() {
		Solver s1, s2, s3;
		SharedContext ctx;
		DecisionHeuristic* lookBody   = new UnitHeuristic(Lookahead::body_lookahead);
		DecisionHeuristic* lookAtom   = new UnitHeuristic(Lookahead::atom_lookahead);
		DecisionHeuristic* lookHybrid = new UnitHeuristic(Lookahead::hybrid_lookahead);
		s1.strategies().heuristic.reset(lookBody);
		s2.strategies().heuristic.reset(lookAtom);
		s3.strategies().heuristic.reset(lookHybrid);
		ProgramBuilder api;
		api.startProgram(ctx, 0, ProgramBuilder::EqOptions().disable())
			.setAtomName(1, "x").setAtomName(2, "a1").setAtomName(3, "a2").setAtomName(4, "a3")
			.setAtomName(5, "b1").setAtomName(6, "b2").setAtomName(7, "b3")
			.startRule().addHead(1).addToBody(1, false).endRule()
			.startRule().addHead(1).addToBody(2, false).addToBody(5, false).endRule()
			.startRule().addHead(2).addToBody(5, false).endRule()
			.startRule().addHead(5).addToBody(2, false).endRule()
			.startRule().addHead(1).addToBody(3, false).addToBody(6, false).endRule()
			.startRule().addHead(3).addToBody(6, false).endRule()
			.startRule().addHead(6).addToBody(3, false).endRule()
			.startRule().addHead(1).addToBody(4, false).addToBody(7, false).endRule()
			.startRule().addHead(4).addToBody(7, false).endRule()
			.startRule().addHead(7).addToBody(4, false).endRule()
		;
		SharedContext ctx2(ctx, SharedContext::init_share_symbols);
		SharedContext ctx3(ctx, SharedContext::init_share_symbols);
		CPPUNIT_ASSERT_EQUAL(false, api.endProgram(s1) && ctx.endInit(1));
		CPPUNIT_ASSERT_EQUAL(true, api.cloneProgram(ctx2, s2) && ctx2.endInit(1));
		CPPUNIT_ASSERT_EQUAL(false, api.cloneProgram(ctx3, s3) && ctx3.endInit(1));
	}
	void testAtomLookahead() {
		Solver s1, s2, s3;
		SharedContext ctx;
		DecisionHeuristic* lookBody   = new UnitHeuristic(Lookahead::body_lookahead);
		DecisionHeuristic* lookAtom   = new UnitHeuristic(Lookahead::atom_lookahead);
		DecisionHeuristic* lookHybrid = new UnitHeuristic(Lookahead::hybrid_lookahead);
		s1.strategies().heuristic.reset(lookBody);
		s2.strategies().heuristic.reset(lookAtom);
		s3.strategies().heuristic.reset(lookHybrid);
		ProgramBuilder api;
		api.startProgram(ctx, 0, ProgramBuilder::EqOptions().disable())
			.setAtomName(1, "x").setAtomName(2, "c1").setAtomName(3, "c2").setAtomName(4, "c3")
			.setAtomName(5, "a1").setAtomName(6, "a2").setAtomName(7, "a3")
			.setAtomName(8, "b1").setAtomName(9, "b2").setAtomName(10, "b3")
			.startRule().addHead(1).addToBody(2, true).addToBody(3, true).addToBody(4, true).addToBody(1, false).endRule()
			.startRule().addHead(2).addToBody(5, false).endRule()
			.startRule().addHead(2).addToBody(8, false).endRule()
			.startRule().addHead(5).addToBody(8, false).endRule()
			.startRule().addHead(8).addToBody(5, false).endRule()
			.startRule().addHead(3).addToBody(6, false).endRule()
			.startRule().addHead(3).addToBody(9, false).endRule()
			.startRule().addHead(6).addToBody(9, false).endRule()
			.startRule().addHead(9).addToBody(6, false).endRule()
			.startRule().addHead(4).addToBody(7, false).endRule()
			.startRule().addHead(4).addToBody(10, false).endRule()
			.startRule().addHead(7).addToBody(10, false).endRule()
			.startRule().addHead(10).addToBody(7, false).endRule()
		;
		SharedContext ctx2(ctx, SharedContext::init_share_symbols);
		SharedContext ctx3(ctx, SharedContext::init_share_symbols);
		CPPUNIT_ASSERT_EQUAL(true, api.endProgram(s1) && ctx.endInit(1));
		CPPUNIT_ASSERT_EQUAL(false, api.cloneProgram(ctx2, s2) && ctx2.endInit(1));
		CPPUNIT_ASSERT_EQUAL(false, api.cloneProgram(ctx3, s3) && ctx3.endInit(1));
	}

	void testLookaheadBugNoSimplify() {
		DecisionHeuristic* lookAtom = new UnitHeuristic(Lookahead::atom_lookahead);
		Solver s;
		SharedContext ctx;
		s.strategies().heuristic.reset(lookAtom);
		Literal a = posLit(ctx.addVar(Var_t::atom_var));
		Literal b = posLit(ctx.addVar(Var_t::atom_var));
		Literal e = posLit(ctx.addVar(Var_t::atom_var));
		ctx.startAddConstraints(s,10);
		ctx.addBinary(a,  b);
		ctx.endInit(1);
		ctx.addBinary(a, ~b);
		s.assume(e) && s.propagate();
		CPPUNIT_ASSERT(lookAtom->select(s));
		CPPUNIT_ASSERT(s.isTrue(a));	
		CPPUNIT_ASSERT(s.seen(a.var()));
		CPPUNIT_ASSERT(s.decisionLevel() == 1);
	}
	void testLookaheadBugDepsNotCleared() {
		DecisionHeuristic* lookAtom = new UnitHeuristic(Lookahead::atom_lookahead);
		Solver s;
		SharedContext ctx;
		s.strategies().heuristic.reset(lookAtom);
		Literal a = posLit(ctx.addVar(Var_t::atom_var));
		Literal b = posLit(ctx.addVar(Var_t::atom_var));
		Literal c = posLit(ctx.addVar(Var_t::atom_var));
		Literal d = posLit(ctx.addVar(Var_t::atom_var));
		Literal e = posLit(ctx.addVar(Var_t::atom_var));
		Literal f = posLit(ctx.addVar(Var_t::atom_var));
		ctx.startAddConstraints(s);
		ctx.addBinary(a, b);
		ctx.addBinary(b, c);
		ctx.addBinary(c, f);
		ctx.addUnary(e);
		ctx.endInit(1);
		// Assume without using lookahead (e.g. a random choice)
		s.assume(b);
		s.propagate();
		// Deps not cleared
		CPPUNIT_ASSERT(lookAtom->select(s));
		CPPUNIT_ASSERT(s.isFalse(c) || s.isFalse(f));
	}
	void testLookaheadBugNoDeps() {
		DecisionHeuristic* lookAtom = new UnitHeuristic(Lookahead::atom_lookahead);
		Solver s;
		SharedContext ctx;
		s.strategies().heuristic.reset(lookAtom);
		Literal a = posLit(ctx.addVar(Var_t::atom_var));
		Literal b = posLit(ctx.addVar(Var_t::atom_var));
		Literal c = posLit(ctx.addVar(Var_t::atom_var));
		Literal d = posLit(ctx.addVar(Var_t::atom_var));
		Literal e = posLit(ctx.addVar(Var_t::atom_var));
		ctx.startAddConstraints(s);
		ctx.addBinary(a, b);
		ctx.addBinary(b, c);
		ctx.addUnary(e);
		ctx.endInit(1);
		CPPUNIT_ASSERT(lookAtom->select(s));
		CPPUNIT_ASSERT(s.isFalse(b));
		s.undoUntil(0);
		s.simplify();
		CPPUNIT_ASSERT(lookAtom->select(s));
		CPPUNIT_ASSERT(s.isFalse(b));
	}
	void testBerkmin() {
		ClaspBerkmin* berkmin = new ClaspBerkmin();
		Solver s;
		SharedContext ctx;
		s.strategies().heuristic.reset(berkmin);
		Literal a = posLit(ctx.addVar(Var_t::atom_var));
		Literal b = posLit(ctx.addVar(Var_t::atom_var));
		Literal c = posLit(ctx.addVar(Var_t::atom_var));
		Literal d = posLit(ctx.addVar(Var_t::atom_var));
		Literal e = posLit(ctx.addVar(Var_t::atom_var));
		Literal f = posLit(ctx.addVar(Var_t::atom_var));
		Literal g = posLit(ctx.addVar(Var_t::atom_var));
		ctx.startAddConstraints(s);
		ctx.endInit(1);
		s.stats.conflicts = 1;
		LitVec up;
		berkmin->updateReason(s, up, Literal() );
		up.push_back(a);
		berkmin->updateReason( s,up,a );
		up.clear();
		up.push_back(b);
		up.push_back(b);
		berkmin->updateReason( s,up,b );
		up.clear();
		berkmin->updateReason( s,up,e );
		s.assume( ~b );
		s.assume( ~c );
		s.assume( ~d );
		ClauseCreator cc(&s);
		cc.startAsserting(Constraint_t::learnt_conflict, a).add(b).add(c).add(d).end();
		s.undoUntil(0);
		s.assume( ~e );
		s.assume( ~f );
		s.assume( ~g );
		cc.startAsserting(Constraint_t::learnt_loop, d).add(e).add(f).add(g).end();
		s.undoUntil(0);
		CPPUNIT_ASSERT_EQUAL(0u, s.numAssignedVars());
		CPPUNIT_ASSERT_EQUAL(true, berkmin->select(s));
		CPPUNIT_ASSERT_EQUAL(b, s.trail().back());	// from conflict clause
		s.propagate();
		CPPUNIT_ASSERT_EQUAL(true, berkmin->select(s));
		CPPUNIT_ASSERT_EQUAL(e, s.trail().back());	// from loop clause
		s.propagate();
		CPPUNIT_ASSERT_EQUAL(true, berkmin->select(s));
		CPPUNIT_ASSERT_EQUAL(a.var(), s.trail().back().var());	// highest activity
	}
	void testVmtf() {
		ClaspVmtf* vmtf = new ClaspVmtf;
		Solver s;
		SharedContext ctx;
		s.strategies().heuristic.reset(vmtf);
		Literal a = posLit(ctx.addVar(Var_t::atom_var));
		Literal b = posLit(ctx.addVar(Var_t::atom_var));
		ctx.startAddConstraints(s);
		ctx.endInit(1);
		CPPUNIT_ASSERT_EQUAL(true, vmtf->select(s));
		s.propagate();
		CPPUNIT_ASSERT_EQUAL(true, vmtf->select(s));
		s.propagate(); 
		CPPUNIT_ASSERT_EQUAL(false, vmtf->select(s));
	}

	void testVsids() {
		ClaspVsids* vsids = new ClaspVsids;
		Solver s;
		SharedContext ctx;
		s.strategies().heuristic.reset(vsids);
		Literal a = posLit(ctx.addVar(Var_t::atom_var));
		Literal b = posLit(ctx.addVar(Var_t::atom_var));
		ctx.startAddConstraints(s);
		ctx.endInit(1);
		LitVec up;
		up.push_back(a);
		vsids->updateReason( s,up,a );
		CPPUNIT_ASSERT_EQUAL(true, vsids->select(s));
		CPPUNIT_ASSERT_EQUAL(true, s.trail().back() == ~a && s.propagate());
		CPPUNIT_ASSERT_EQUAL(true, vsids->select(s));
		CPPUNIT_ASSERT_EQUAL(true, s.trail().back() == ~b && s.propagate());
		CPPUNIT_ASSERT_EQUAL(false, vsids->select(s));
	}

	void testResurrect() {
		/*
		typedef std::pair<const char*, DecisionHeuristic*> Heu;
		Heu heus[3] = {
			Heu("Berkmin", new ClaspBerkmin()),
			Heu("Vmtf", new ClaspVmtf()),
			Heu("Vsids", new ClaspVsids())
		};
		for (uint32 i = 0; i != 3; ++i) {
			Solver s;
			SharedContext ctx;
			s.strategies().heuristic.reset(heus[i].second);
			Var v1 = ctx.addVar(Var_t::atom_var);
			Var v2 = ctx.addVar(Var_t::atom_var);
			Var v3 = ctx.addVar(Var_t::atom_var);
			s.startAddConstraints(&ctx);
			s.endInit();
			s.eliminate(v1, true);
			while (s.strategies().heuristic->select(s) && s.propagate()) { ; }
			CPPUNIT_ASSERT(2u == s.stats.choices);
			CPPUNIT_ASSERT_EQUAL_MESSAGE(heus[i].first, 0u, s.numFreeVars());
			s.eliminate(v1, false);
			CPPUNIT_ASSERT_EQUAL(value_free, s.value(v1));
			CPPUNIT_ASSERT_EQUAL_MESSAGE(heus[i].first, true, s.strategies().heuristic->select(s));
			CPPUNIT_ASSERT_MESSAGE(heus[i].first, value_free != s.value(v1));
		}
		*/
		CPPUNIT_FAIL("TODO - Resurrection not yet supported!");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(DecisionHeuristicTest);

} } 
