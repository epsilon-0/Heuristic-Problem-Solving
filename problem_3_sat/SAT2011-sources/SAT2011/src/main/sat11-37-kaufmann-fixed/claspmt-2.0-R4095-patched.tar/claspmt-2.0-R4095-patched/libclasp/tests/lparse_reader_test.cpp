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
#include <sstream>
#include <clasp/reader.h>
#include <clasp/program_builder.h>
#include <clasp/solver.h>
namespace Clasp { namespace Test {


class LparseReaderTest : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(LparseReaderTest);
	CPPUNIT_TEST(testEmptyProgram);
	CPPUNIT_TEST(testSingleFact);
	CPPUNIT_TEST(testComputeStatementAssumptions);
	CPPUNIT_TEST(testTransformSimpleConstraintRule);
	CPPUNIT_TEST(testTransformSimpleWeightRule);
	CPPUNIT_TEST(testTransformSimpleChoiceRule);

	CPPUNIT_TEST(testSimpleConstraintRule);
	CPPUNIT_TEST(testSimpleWeightRule);
	CPPUNIT_TEST(testSimpleChoiceRule);

	CPPUNIT_TEST(testDimacs);
	CPPUNIT_TEST(testDimacsDontAddTaut);
	CPPUNIT_TEST(testDimacsDontAddDupLit);
	CPPUNIT_TEST(testDimacsBadVars);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() {
		api.startProgram(ctx, 0);
	}
	void testEmptyProgram() {
		std::stringstream empty("0\n0\nB+\n0\nB-\n0\n1\n");
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(empty, api));
		empty.clear();
		std::stringstream out;
		api.endProgram(solver);
		api.writeProgram(out);
		CPPUNIT_ASSERT_EQUAL(empty.str(), out.str());
	}
	
	void testSingleFact() {
		std::stringstream prg("1 1 0 0 \n0\n1 a\n0\nB+\n0\nB-\n0\n1\n");
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		api.endProgram(solver);
		CPPUNIT_ASSERT_EQUAL(0u, solver.numVars());
		CPPUNIT_ASSERT_EQUAL('a', ctx.symTab()[1].name[0]);
	}
	void testComputeStatementAssumptions() {
		std::stringstream prg;
		prg << "1 1 1 1 2 \n"	// d:-not c.
			  << "1 2 1 1 3 \n"	// c:-not a.
				<< "1 3 1 1 4 \n"	// a:-not b.
				<< "1 4 1 1 3 \n"	// b:-not a.
				<< "0\n1 d\n2 c\n3 a\n4 b\n"
				<< "0\nB+\n0\nB-\n2\n0\n1\n";	// B-: c
		
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		api.endProgram(solver) && ctx.endInit(1);
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(ctx.symTab()[3].lit));
		CPPUNIT_ASSERT_EQUAL(true, solver.isTrue(ctx.symTab()[1].lit));
		CPPUNIT_ASSERT_EQUAL(true, solver.isFalse(ctx.symTab()[2].lit));
		CPPUNIT_ASSERT_EQUAL(true, solver.isFalse(ctx.symTab()[4].lit));
	}

	
	void testTransformSimpleConstraintRule() {
		std::stringstream prg;
		prg << "2 1 3 1 2 3 2 4 \n"// a :- 2 {not c, b, d}
			  << "1 2 1 1 3 \n"			// b :- not c.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "1 4 1 1 3 \n"			// d :- not c.
				<< "0\n1 a\n2 b\n3 c\n4 d\n"
				<< "0\nB+\n0\nB-\n0\n1\n";

		std::stringstream exp, out;
		api.setExtendedRuleMode(ProgramBuilder::mode_transform_weight);
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		CPPUNIT_ASSERT_EQUAL(true, api.endProgram(solver));
		CPPUNIT_ASSERT(ctx.symTab()[2].lit == ctx.symTab()[1].lit);
		CPPUNIT_ASSERT(ctx.symTab()[4].lit == ctx.symTab()[1].lit);

		
		exp << "1 1 1 1 3 \n"			// a :- not c.
				<< "1 3 1 1 1 \n"			// c :- not b.
				<< "1 2 1 0 1 \n"			// b :- a.
				<< "1 4 1 0 1 \n"			// d :- a.
				<< "0\n1 a\n2 b\n3 c\n4 d\n0\n"
				<< "B+\n0\nB-\n0\n1\n"
		;
		api.writeProgram(out);
		CPPUNIT_ASSERT_EQUAL(exp.str(), out.str());
	}

	void testTransformSimpleWeightRule() {
		std::stringstream prg;
		prg << "5 1 2 3 1 3 2 4 2 1 3\n"// a :- 2 [b=1, not c=2, d=3]
			  << "1 2 1 1 3 \n"			// b :- not c.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "1 4 1 1 3 \n"			// d :- not c.
				<< "0\n1 a\n2 b\n3 c\n4 d\n"
				<< "0\nB+\n0\nB-\n0\n1\n";
		api.setExtendedRuleMode(ProgramBuilder::mode_transform_weight);
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		CPPUNIT_ASSERT_EQUAL(true, api.endProgram(solver));
		CPPUNIT_ASSERT_EQUAL(1u, solver.numVars());
		
		std::stringstream exp, out;
		exp << "1 1 1 1 3 \n"			// a :- not c.
				<< "1 3 1 1 1 \n"			// c :- not a.
				<< "1 2 1 0 1 \n"			// b :- a.
				<< "1 4 1 0 1 \n"			// d :- a.
				<< "0\n1 a\n2 b\n3 c\n4 d\n0\n"
				<< "B+\n0\nB-\n0\n1\n"
		;
		api.writeProgram(out);
		CPPUNIT_ASSERT_EQUAL(exp.str(), out.str());		
	}

	void testTransformSimpleChoiceRule() {
		std::stringstream prg;
		prg << "3 3 1 2 3 2 1 3 2 \n"// {a,b,c} :- b, not c.
			  << "1 2 1 1 1 \n"			// b :- not a.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "0\n1 a\n2 b\n3 c\n"
				<< "0\nB+\n0\nB-\n0\n1\n";
		api.setExtendedRuleMode(ProgramBuilder::mode_transform_choice);
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		CPPUNIT_ASSERT_EQUAL(true, api.endProgram(solver));
		std::stringstream exp, out;
		exp << "1 2 0 0 \n"			// b.
				<< "1 4 1 0 2 \n"		// _a :- b
				<< "0\n2 b\n0\n"
				<< "B+\n2\n0\nB-\n0\n1\n"
		;
		api.writeProgram(out);
		CPPUNIT_ASSERT_EQUAL(exp.str(), out.str());		
	}

	void testSimpleConstraintRule() {
		std::stringstream prg;
		prg << "2 1 3 0 2 3 2 4 \n"// a :- 2 {c, b, d}
			  << "1 2 1 1 3 \n"			// b :- not c.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "1 4 1 1 3 \n"			// d :- not c.
				<< "0\n1 a\n2 b\n3 c\n4 d\n"
				<< "0\nB+\n0\nB-\n0\n1\n";

		std::stringstream exp, out;
		api.setExtendedRuleMode(ProgramBuilder::mode_transform_choice);
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		CPPUNIT_ASSERT_EQUAL(true, api.endProgram(solver));
		CPPUNIT_ASSERT_EQUAL(2u, solver.numVars());
		
		exp << "5 1 2 2 0 3 2 1 2 \n"// a :- 2 [c = 1, b = 2]
				<< "1 2 1 1 3 \n"			// b :- not c.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "1 4 1 0 2 \n"			// d :- b.
				<< "0\n1 a\n2 b\n3 c\n4 d\n0\n"
				<< "B+\n0\nB-\n0\n1\n"
		;
		api.writeProgram(out);
		CPPUNIT_ASSERT_EQUAL(exp.str(), out.str());
	}

	void testSimpleWeightRule() {
		std::stringstream prg;
		prg << "5 1 2 3 0 3 2 4 2 1 3\n"// a :- 2 [c = 2, b = 1, d = 3], but (d = 3 -> d = 2)
			  << "1 2 1 1 3 \n"			// b :- not c.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "1 4 1 1 3 \n"			// d :- not c.
				<< "0\n1 a\n2 b\n3 c\n4 d\n"
				<< "0\nB+\n0\nB-\n0\n1\n";

		std::stringstream exp, out;
		api.setExtendedRuleMode(ProgramBuilder::mode_transform_choice);
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		CPPUNIT_ASSERT_EQUAL(true, api.endProgram(solver));
		CPPUNIT_ASSERT_EQUAL(2u, solver.numVars());
		
		exp << "5 1 2 2 0 3 2 2 3 \n"// a :- 2 [c = 2, b = 3]
				<< "1 2 1 1 3 \n"			// b :- not c.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "1 4 1 0 2 \n"			// d :- b.
				<< "0\n1 a\n2 b\n3 c\n4 d\n0\n"
				<< "B+\n0\nB-\n0\n1\n"
		;
		api.writeProgram(out);
		CPPUNIT_ASSERT_EQUAL(exp.str(), out.str());
	}

	void testSimpleChoiceRule() {
		std::stringstream prg;
		prg << "3 3 1 2 3 2 1 3 2 \n"// {a,b,c} :- b, not c.
			  << "1 2 1 1 1 \n"			// b :- not a.
				<< "1 3 1 1 2 \n"			// c :- not b.
				<< "0\n1 a\n2 b\n3 c\n"
				<< "0\nB+\n0\nB-\n0\n1\n";
		
		api.setExtendedRuleMode(ProgramBuilder::mode_transform_weight);
		CPPUNIT_ASSERT_EQUAL(true, parseLparse(prg, api));
		CPPUNIT_ASSERT_EQUAL(true, api.endProgram(solver));
		std::stringstream exp, out;
		prg.clear();
		prg.seekg(0);
		exp << "1 2 0 0 \n"// b.
			  << "0\n2 b\n"
				<< "0\n"
				<< "B+\n2\n0\nB-\n1\n0\n1\n";
		api.writeProgram(out);
		CPPUNIT_ASSERT_EQUAL(exp.str(), out.str());		
	}

	void testDimacs() {
		std::stringstream prg;
		prg << "c simple test case\n"
				<< "p cnf 4 3\n"
			  << "1 2 0\n"
				<< "3 4 0\n"
				<< "-1 -2 -3 -4 0\n";
		CPPUNIT_ASSERT(parseDimacs(prg, ctx, solver, false));
		CPPUNIT_ASSERT(solver.numVars() == 4);
		CPPUNIT_ASSERT(ctx.numConstraints() == 3);
		CPPUNIT_ASSERT(solver.numLearntConstraints() == 0);
	}

	void testDimacsDontAddTaut() {
		std::stringstream prg;
		prg << "c simple test case\n"
				<< "p cnf 4 4\n"
			  << "1 2 0\n"
				<< "3 4 0\n"
				<< "-1 -2 -3 -4 0\n"
				<< "1 -2 -3 2 0\n";
		CPPUNIT_ASSERT(parseDimacs(prg, ctx, solver, false));
		CPPUNIT_ASSERT(solver.numVars() == 4);
		CPPUNIT_ASSERT(ctx.numConstraints() == 3);
		CPPUNIT_ASSERT(solver.numLearntConstraints() == 0);
	}

	void testDimacsDontAddDupLit() {
		std::stringstream prg;
		prg << "c simple test case\n"
				<< "p cnf 2 4\n"
			  << "1 2 2 1 0\n"
				<< "1 2 1 2 0\n"
				<< "-1 -2 -1 0\n"
				<< "-2 -1 -2 0\n";
		CPPUNIT_ASSERT(parseDimacs(prg, ctx, solver, false));
		CPPUNIT_ASSERT(solver.numVars() == 2);
		CPPUNIT_ASSERT(ctx.numConstraints() == 4);
		CPPUNIT_ASSERT(solver.sharedContext()->numBinary() == 4);
	}

	void testDimacsBadVars() {
		std::stringstream prg;
		prg << "p cnf 2 1\n"
			  << "3 4 0\n";
		CPPUNIT_ASSERT_THROW(parseDimacs(prg, ctx, solver, false), ReadError);
	}
private:
	Solver solver;
	SharedContext ctx;
	ProgramBuilder api;
};

CPPUNIT_TEST_SUITE_REGISTRATION(LparseReaderTest);
} } 
