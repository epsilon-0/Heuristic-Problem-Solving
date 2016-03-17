/* lkconfig.h 
 *
 * Compile-time options for the program LK.  
 *
 * vi: set tabstop=4 shiftwidth=4:
 * 
 * $Id: lkconfig.h,v 1.11 1998/05/18 21:02:06 neto Exp neto $
 * 
 *    Copyright (C) 1996, 1997 David Neto
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 * 
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 *    USA.
 * 
 * 
 * This file sets the compile-time options for the program LK.  Behaviour
 * or availability of certain parts of the program LK are enabled or
 * modified here by defining C preprocessor symbols.  The defaults are
 * given in comments.
 * 
 * Warning!  This file is *not* generated by a web file.  It is a plain .h
 * header file so that the user who doesn't have ctangle installed (tsk,
 * tsk!) has the ability to change the configuration options for the
 * program LK.  That said, I've tried to make this file as self-documenting
 * as possible without the power of CWEB or TeX.
 * 
 * Some of the options from this file depend on definitions in config.h,
 * the package-wide configuration header file.  That file is generated
 * automatically at configuration time, and knows a lot about the target
 * system.  So files that include this header file should include
 * <config.h> first.  (See the Autoconf manual for why it one should use
 * angle brackets (#include <config.h>) instead of ordinary quotes
 * (#include "config.h").)
 * 
 * Generally speaking, the first ``word'' in a symbol name corresponds to
 * the source file that it affects.  For example, ERROR_NO_CHECK controls
 * the behaviour of part of the error module in file error.w.  Sometimes
 * the name is abbreviated, e.g. KD_CHECK_VERBOSE controls behaviour of the
 * k-dimensional trees defined in kdtree.w.
 * 
 *
 * This file is divided into sections, most important first.  They are:
 *  Options to control algorithmic parameters.
 *  Options to control precision and accuracy.
 *  Options that may have an impact on performance, but not on correctness.
 *  Options to control the amount of memory used.
 *  Options to select options for repeatability -- good for experiments.
 *  Options to control in some way the amount of output generated.
 *  Options to control how much checking is done.
 * 
 * 
 */


/***************************************************************************
 * These options control algorithmic parameters.
 **************************************************************************/

/* We need to select which tabu rules are in effect.  Exactly one of
 * TABU_JBMR or TABU_Papadimitriou must be selected.  
 * 
 * TABU_JBMR selects the rule ``Never delete an added edge''.
 * TABU_Papadimitriou selects the rule ``Never add a deleted edge''.
 *
 * Papadimitriou's rule enables LK to solve a PLS-complete problem, but as
 * of 1997 had not yet been studied experimentally.
 *
 * Lin and Kernighan devised and used both rules, but did not name them
 * this way.  This naming scheme is my own mnemonic.
 *
 * Default:
	#define TABU_JBMR
	#undef TABU_Papadimitriou
 */

#define TABU_JBMR
#undef TABU_Papadimitriou


/* Most of the time you want to limit the probe depth of the variable-depth 
 * search.  Use command line option --maxdepth <n> to do so.  The option
 * can only be used if JBMR_LIMIT_PROBE_DEPTH is defined.  There may be
 * an insignificant performance loss if it is defined, because there is a 
 * depth check at each step deeper in the search.  
 *
 * Default:
	#define JBMR_LIMIT_PROBE_DEPTH
 */

#define JBMR_LIMIT_PROBE_DEPTH


/* Lin and Kernighan examine the farther tour neighbour of t[7] first.
 * This switch determines whether we consider the farther neighbour of t[1]
 * first.  If the value of JBMR_FARTHER_T1_FIRST is zero, then we try
 * the tour neighbours in arbitrary order.
 * 
 * A quick experiment on dsj1000 showed that (with declustering turned on),
 * it's better to turn this on:  turned off, total run time is 395 sec,
 * tour length is 19190163 (or 2.8% above optimal); turn on, total run time
 * is 91 sec, tour length is 18870278 (or 1.1% above optimal).
 *
 * Default:
	#define JBMR_FARTHER_T1_FIRST 1
 */

#if !defined(JBMR_FARTHER_T1_FIRST)
#define JBMR_FARTHER_T1_FIRST 1
#endif



/***************************************************************************
 * These options control precision and accuracy.
 **************************************************************************/

/* We need to define a C data type for lengths.  Only one of the following
 * should be active at a time.  See length.w for more information.  
 *
 * Type long long is not pure ANSI; it is supported by GCC and by the IRIX
 * native C compiler.  At package configuration time, symbol
 * SIZEOF_LONG_LONG is set to zero if type long long is unsupported; it is
 * set to the number of bytes in long long otherwise, usually 8.  So we
 * can allow it conditionally as follows:
 * 
 * Example:
	#if SIZEOF_LONG_LONG
	#define LENGTH_LONG_LONG
	#end
 * 
 * Default: 
	#define LENGTH_DOUBLE 
	#undef  LENGTH_FLOAT
	#undef  LENGTH_INT
	#undef  LENGTH_LONG_LONG
 */

#define LENGTH_DOUBLE
#undef LENGTH_FLOAT
#undef LENGTH_INT
#undef LENGTH_LONG_LONG


/* Should we use the math library's hypot function instead of open-coding
 * the Euclidean distance function?  Numerical analysts might argue for
 * using hypot, but it turned out to be much slower.   
 *
 * The many cost functions are defined in the READ module, read.w.
 *
 * Default: 
	#undef COST_USE_HYPOT 
 */

#undef COST_USE_HYPOT


/* JBMR_REQUIRE_JOINED_GAIN_VAR   
 *
 * If an inexact type is specified for length then by default the LK
 * optimization phase computes cumulative gains in a split variable: a
 * positive part and a negative part.  This default is the safe slower than
 * using a single cumulative gain variable.
 *
 * To force a unified variable, define the symbol
 * JBMR_REQUIRE_JOINED_GAIN_VAR.  Turn this option on if you trust summing
 * an alternating series with floating point numbers.  :)
 * (Hint: you shouldn't!)
 * 
 * However, I do use machine epsilon intelligently in cutting off the
 * search, so these alternating sums might not be such a big issue.
 *
 * Default:
	#undef JBMR_REQUIRE_JOINED_GAIN_VAR
 */

#undef JBMR_REQUIRE_JOINED_GAIN_VAR


/***************************************************************************
 * These options may have an impact on performance, but not on correctness.
 **************************************************************************/

/* We must determine what data structure to use for the tabu check.
 * Exactly one of TABU_LINEAR or TABU_SPLAY must be defined.
 *
 * TABU_LINEAR uses an unordered array; each check takes time linear in the
 * number of items in the array.  This is best for probes up to a depth of
 * about 50.  See also JBMR_LIMIT_PROBE_DEPTH.
 *
 * TABU_SPLAY uses a splay tree; each check takes (amortized) time
 * logarithmic in the number of items in the array, but has greater
 * overhead for smaller dictionaries.  This is best for deeper probes.
 *
 * I plan to implement an automatic switch from linear to splay when the
 * probe gets deep enough.
 *
 * Default:
	#undef TABU_LINEAR
	#define TABU_SPLAY
 */

#define TABU_LINEAR
#undef TABU_SPLAY


/* Define KD_BUILD_SMALLEST_SEGMENT_FIRST to make the k-d tree building
 * routine build the segment with the fewest number of cities first.
 * This may or may not prevent stack overflow.  (In fact, I think a
 * seriously smart compiler is needed for this trick to prevent stack
 * overflow.
 * 
 * Default:
	#undef KD_BUILD_SMALLEST_SEGMENT_FIRST
 */

#undef KD_BUILD_SMALLEST_SEGMENT_FIRST


/* Define KD_NO_HIDDEN_BIT to remove all support for hidden bits in nodes
 * of k-d trees.  After running some experiments, it appears that the
 * reduction in bookkeeping (time and space) is more than offset by useless
 * node searches.  So the default is to not define this symbol.
 *
 * Default:
	#undef KD_NO_HIDDENT_BIT
 */

#undef KD_NO_HIDDENT_BIT


/* Define KD_NO_HIDDEN_RNN_TEST to turn off the testing the hidden bit
 * before recursing in E2_rnn.  This is less drastic than removing hidden
 * bits altogether (see KD_NO_HIDDEN_BIT), but it still doesn't save time.
 *
 * Default:
	#undef KD_NO_HIDDEN_RNN_TEST 
 */

#undef KD_NO_HIDDEN_RNN_TEST 


/***************************************************************************
 * These options select options for repeatability -- good for experiments.
 **************************************************************************/

/* Define QSORT_DETERMINATE to make sorting stable, i.e. so that we
 * preserve the order of objects that compare as equal.  Also consider
 * command-line option -S dsort (which substitutes Bentley and McIlroy's
 * deterministic sorting routine in place of the qsort routine from the
 * system's C library.
 *
 * Turn this option on only if you want to ensure repeatable results, both
 * across runs and across systems.  For repeatable results across systems,
 * you must also use -S dsort.
 *
 * Default:
	#undef QSORT_DETERMINATE
 */
#undef QSORT_DETERMINATE


/* Define CITY_ORDER_INVARIANT to ensure that computations do not depend
 * on the initial ordering of the cities.  This is for repeatability.
 * This does not work yet.  (Faith Fich's suggestion of looking at
 * statistical behaviour under input randomization may be good enough.)
 *
 * Default:
	#undef CITY_ORDER_INVARIANT
 */

#undef CITY_ORDER_INVARIANT


/***************************************************************************
 * These options control in some way the amount of output generated.
 **************************************************************************/

/* Define LK_SHOW_AFTER_SFC to output the cities graphically (in
 * PostScript) after sorting them according to Moore's version of Hilbert's
 * space-filling curve.  The output is generated only if the -p
 * (--postscript) command-line option is used to request PostScript output.
 *
 * Default:
	#undef LK_SHOW_AFTER_SFC
 */

#undef LK_SHOW_AFTER_SFC


/* Define KD_SHOW_KDTREE to output the partitioning used for the k-d tree.
 * The output is made graphically in PostScript, and only if the -p
 * (--postscript) option is used.
 *
 * Default:
	#undef KD_SHOW_KDTREE
 */

#undef KD_SHOW_KDTREE


/* Define KD_ALLOW_VERBOSE to turn on debugging output for module KDTREE,
 *  subject to the verbose command line option.
 * 
 * Default:
	#undef KD_ALLOW_VERBOSE
 */

#undef KD_ALLOW_VERBOSE


/* Define JBMR_REPORT_DEPTHS to show how deep tabu probing goes, and how
 * deep actually improving moves go.  These are platform-independent
 * statistics of work done by the tabu search algorithm. This is not
 * affected by the value of JBMR_MAX_VERBOSE.
 *
 * Default:
	#define JBMR_REPORT_DEPTHS 0
 */

#if !defined(JBMR_REPORT_DEPTHS)
#define JBMR_REPORT_DEPTHS 1
#endif


/* Define JBMR_MAX_VERBOSE to determine how much verbose output code gets
 * compiled into the LK optimization code for the TSP (i.e. in module JBMR).
 * The level of detail actually output depends on this value and the values
 * given to the -v or --verbose command-line options.  
 *
 * If undefined, then there is no runtime overhead due to verbose output 
 * code, i.e., checks against variable |verbose| are not even compiled into 
 * the code.
 *
 * Default:
	#define JBMR_MAX_VERBOSE 45
 */

#if !defined(JBMR_MAX_VERBOSE)
#define JBMR_MAX_VERBOSE 45
#endif


/* If JBMR_MAX_VERBOSE is greater than zero, we can turn on very verbose
 * output for a specific city by setting symbol JBMR_WATCH_THIS_CITY
 * to the numeric value of the city to watch.
 *
 * Example:
	#define JBMR_WATCH_THIS_CITY (999)
 * This turns on very verbose output when t[1]=999.
 * 
 * Default:
	#undef JBMR_WATCH_THIS_CITY
 */

#undef JBMR_WATCH_THIS_CITY


/***************************************************************************
 * These options control how much checking is done.
 **************************************************************************/

/* Define ERROR_NO_CHECK to turn off assertion checking.
 *
 * Default: 
	#undef ERROR_NO_CHECK
 */

#undef ERROR_NO_CHECK


/* Define LK_CHECK_KDTREE to make module LK check that all nn computations
 * are correct.  On $n$-city instances, this does $O(n^2)$ work.
 * 
 * Default:
	#undef LK_CHECK_KDTREE
 */
#undef LK_CHECK_KDTREE


/* Define KD_CHECK_PARTITIONING to make the k-d tree building routine
 * check that it has partitioned the cities correctly.
 *
 * Default:
	#undef KD_CHECK_PARTITIONING
 */

#undef KD_CHECK_PARTITIONING


/* Define KD_CHECK_BBOX to make the k-d tree building routine check that
 * it computes its bounding boxes correctly.
 *
 * Default:
	#undef KD_CHECK_BBOX
 */

#undef KD_CHECK_BBOX


/* The value of ARRAY_DEBUG controls how much checking is done by the
 * array-based tour representation.  A value of 0 does no checking.  A
 * non-zero value checks input conditions for flips.  A value greater than
 * 1000 forces a time-consuming ($O(n)$) consistency check after each flip.
 *
 * Default:
	#define ARRAY_DEBUG 0
 */

#define ARRAY_DEBUG 0


/* Define TWOLEVEL_FLIP_CHECK_PRECONDITION to force the tour representation
 * based on two-level tree to check the input precondition for flips.  This
 * is analogous to ARRAY_DEBUG being non-zero.  Sorry for the naming
 * inconsistency.
 *
 * Default:
	#undef TWOLEVEL_FLIP_CHECK_PRECONDITION
 */

#undef TWOLEVEL_FLIP_CHECK_PRECONDITION


/* Define TWOLEVEL_DEBUG to force both two-level trees and arrays to be
 * used to represent tours, and ensuring that they are consistent with
 * each other.
 *
 * Default:
	#undef TWOLEVEL_DEBUG
 */

#undef TWOLEVEL_DEBUG


/* Define DECLUSTER_DEBUG to a non-zero value to allow program
 * declustertest (part of decluster.w) to examine and test data structures
 * internal to the decluster module.
 *
 * Default:
	#defined DECLUSTER_DEBUG 0
 */

#if !defined(DECLUSTER_DEBUG)
#define DECLUSTER_DEBUG 0
#endif
