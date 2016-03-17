/* declevel.h 
 *
 * Level of declustering support.
 * vi: set tabstop=4 shiftwidth=4:
 * 
 * $Id: declevel.h,v 1.2 1997/07/02 20:51:28 neto Exp neto $
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
 * This file sets the compile-time options for declustering support.
 * I've designed a way to compensate for clustering present in the TSP
 * instance.  It is explained in decluster.w (and in my PhD thesis).
 *
 * Define JBMR_DECLUSTER_IN_ELIGIBILITY_TEST to compensate for clustering
 * when deciding whether an edge is feasible.
 *
 * Define JBMR_DECLUSTER_IN_GREEDY to compensate for clustering when
 * choosing among eligible edges.  If the GREEDY setting is on, then the
 * ELIGIBILITY setting must also be on.
 *
 * Defaults:
	#define JBMR_DECLUSTER_IN_ELIGIBILITY_TEST 1
	#define JBMR_DECLUSTER_IN_GREEDY 1
 */

#if !defined(JBMR_DECLUSTER_IN_GREEDY)
#define JBMR_DECLUSTER_IN_GREEDY 1
#endif

#if !defined(JBMR_DECLUSTER_IN_ELIGIBILITY_TEST)
#define JBMR_DECLUSTER_IN_ELIGIBILITY_TEST 1
#endif


/* Define LK_BUILD_DECLUSTER_STRUCTURES to a non-zero value to always 
 * build the decluster data structures, even if declustering is not used.
 * This is useful for some verbose output, and normally should be disabled.
 *
 * Default:
	#define LK_BUILD_DECLUSTER_STRUCTURES 0
 */
#define LK_BUILD_DECLUSTER_STRUCTURES 0


/* Don't touch the following. */
#if JBMR_DECLUSTER_IN_GREEDY
#undef JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
#define JBMR_DECLUSTER_IN_ELIGIBILITY_TEST 1
#endif
