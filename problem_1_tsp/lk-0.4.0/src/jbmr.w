


\noindent Copyright \copyright 1994, 1995, 1996, 1997, 1998 David Neto
\smallskip

\noindent 
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
\smallskip

\noindent 
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
\smallskip

\noindent   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA  02111-1307, USA.
\smallskip

\noindent   
   You may contact David Neto via email at {\tt netod@@acm.org}, or with
   greater latency at
\smallskip
\noindent{\obeylines
     Department of Computer Science
     University of Toronto
     10 King's College Rd.
     Toronto, Ontario
     M5S 3G4
     Canada
}
\medskip


\noindent\hbox{}\hrule\hbox{}\penalty-1000
\vskip0.5cm\relax



@i webdefs.w
@i types.w

{\obeylines
$Log: jbmr.w,v $
Revision 1.192  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.191  1998/05/23 16:49:20  neto
Change bound value to lower bound value, etc.

Revision 1.190  1998/05/09 22:51:39  neto
Give two decimal points in milestones.

Revision 1.189  1998/02/27 21:40:36  neto
Lowered verbose level of end of LK step.
Fixed CWEB syntax of printing double bridge edge section.

Revision 1.188  1998/02/27 19:43:14  neto
Made printing for iterated Lin-Kernighan respect verbose rules.

Revision 1.187  1998/02/26 21:37:37  neto
Fixed an old bug!  Wasn't checking tabu condition in generic search for
the new edge to be removed being the new edge being proposed to be added.
Fixed a bug in reverting code: must use tour flip arb instead of just
tour flip.
Fixed a conceptual bug: the change log must also encode the scheme id
used in that improvement, and the reverting must undo those scheme changes.
Removed some debugging output.
Implement the double-bridge mutation in three flips instead of four.

This seems to work.  Now I'll remove some of the debugging output.

Revision 1.186  1998/02/21 04:04:36  neto
Added most of the support for Iterated Lin-Kernighan.

Revision 1.185  1998/01/24  20:47:43  neto
Fixed comment on CAREFUL OP

Revision 1.184  1997/11/07  22:35:57  neto
Added verbose message to say when we hit the max depth.
Adjusted verbose values so less is printed at 50.

Revision 1.183  1997/11/06  22:47:54  neto
I wasn't marking cities dirty for 4-changes or lambda-changes!
Ouch.

Revision 1.182  1997/10/18 18:08:13  neto
Convert to new neighbour list protocol.

Revision 1.181  1997/10/17  21:50:10  neto
Show Start and end milestones, and times for preprocessing as well.

Revision 1.180  1997/09/27 18:06:21  neto
Fixed RCS log behaviour.

Revision 1.179  1997/09/12  21:52:46  neto
Don't cause a seg fault in my verbose output: I was calling decluster d
even when I hadn't built the data structures!

Revision 1.178  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.177  1997/07/02  20:48:23  neto
Add online printing of length of broken t1 and t2 edge, and some online
depth printing.

Revision 1.176  1997/07/02  17:51:20  neto
Satisfy GCC's dataflow analysis w.r.t. this time.

Revision 1.175  1997/06/20  21:48:17  neto
Better comment about CAREFUL OP
rename num decluster reject to num reject by decluster, for uniformity.
Implement declustering in test surrounding major part of
  Update best gain and compose a list of eligible moves.

Revision 1.174  1997/06/20  20:55:28  neto
Formatting improvements.

Revision 1.173  1997/06/20  20:44:35  neto
Cleared up some clutter by using a macro for careful comparisons
with best gain.

Revision 1.172  1997/06/20  19:34:02  neto
Fixed typo in section name
Fixed a BIG MISTAKE:  compute cluster distance between t1 and t2ip2
*no* between t2ip1 and t2ip2.  Duh!

Revision 1.171  1997/06/20  18:59:04  neto
Added some stats gathering (num reject by cum 1, num reject before build e)
Check for cum gain > best gain *before* entering Update
best gain and compose an eligible list of moves.
This might save a *lot* of time because we may avoid searching
an entire nn list.

Revision 1.170  1997/06/20  18:32:26  neto
A better comment about building e list.
Commented out the code bloating PREV NEXT loop.
Made cluster rejection announcement at much lower verbose level, though
context is lost.
Count number of rejections due to declustering.

Revision 1.169  1997/06/18  16:43:47  neto
Milestones every 10th of a percent from 10 percent down through zero.

Revision 1.168  1997/06/17  20:28:57  neto
Added support for milestones.

Revision 1.167  1997/06/17  14:49:32  neto
Fixed a TeX error.

Revision 1.166  1997/06/17  14:47:12  neto
Fixed an unterminated hash if

Revision 1.165  1997/06/17  14:45:14  neto
Better formatting in eligibility test.
Added cluster compensation to the greedy test (Go deeper)

Revision 1.164  1997/06/16  21:22:16  neto
More debug verbose info.

Revision 1.163  1997/06/16  21:14:23  neto
Decluster test should use the best gain with slop.

Revision 1.162  1997/06/16  21:01:11  neto
At verbose 501, print every cluster distance.

Revision 1.161  1997/06/16  20:38:58  neto
JBMR ALLOW VERBOSE is always defined.  Now decide on zero/non-zero status
instead.

Revision 1.160  1997/06/16  20:26:58  neto
Added include decluster.h

Revision 1.159  1997/06/16  20:19:20  neto
Fixed a syntax error.

Revision 1.158  1997/06/16  20:05:14  neto
Need to include declevel.h to see whether to use declustering.

Revision 1.157  1997/06/16  20:04:05  neto
First cut at integrating decluster test.  Doesn't actually reject
just yet.  It just collects data.

Revision 1.156  1997/06/16  19:15:32  neto
Make unrolling the prev next loop conditional at compile time.

Revision 1.155  1997/06/16  18:34:20  neto
Make the code compact by putting both alternatives for t2ip2 into
the body of a loop.

Revision 1.154  1997/06/16  17:36:52  neto
Fixed a TeX bug.

Revision 1.153  1997/06/16  16:57:14  neto
Don't need debugging output for SPLIT GAIN VAR anymore.

Revision 1.152  1997/06/16  16:45:51  neto
Reversed the sense of REQUEST SPLIT GAIN VAR to REQUIRE SPLIT GAIN VAR
That way the default (safe) setting happens with fewer variables set.

Revision 1.151  1997/06/13  20:59:16  neto
Made it quieter

Revision 1.150  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.149  1997/05/16  18:09:40  neto
Include <config.h> and lkconfig.h

Revision 1.148  1997/04/23  21:28:07  neto
Added elapsed time since last phase change to verbose reporting.

Revision 1.147  1997/04/23  20:44:56  neto
In verbose mode, report elapsed time since start of LK phase when
an improvement has been found.

Revision 1.146  1997/02/07  16:52:23  neto
Made every use of emphpar end with a paragraph break.

Revision 1.145  1997/01/21  22:46:47  david
Clarified conditional compilation and fixed a bug.

Revision 1.144  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.143  1997/01/21  19:34:36  david
Clarified use of JBMR REQUEST SPLIT GAIN VAR

Revision 1.142  1997/01/21  19:15:27  david
Fixed setting of SPLIT GAIN VAR

Revision 1.140  1997/01/21  00:22:47  david
Removed offending pritnf

Revision 1.139  1997/01/21  00:21:53  david
Report both probe and move depths.

Revision 1.137  1997/01/21  00:06:57  david
Added tracking of probe depths.

Revision 1.136  1997/01/20  23:49:53  david
Changed max\_probe\_depth to max\_generic\_flips

Revision 1.135  1997/01/20  23:47:01  david
Fixed the limiting of probe depth.

Revision 1.134  1997/01/20  19:32:54  david
Optionally limit the probe depth.

Revision 1.133  97/01/16  13:35:17  neto
Get rid of a warning about old\_t when compiling with TABU LINEAR.

Revision 1.132  96/12/23  13:07:03  neto
New variable best gain with slop.  Saves many additions.

Revision 1.131  96/12/20  17:05:13  neto
Fixed typesetting woes by simplifiyng preprocessor stuff. (moved a brace.
).

Revision 1.130  96/12/20  17:02:54  neto
Fixed TeX typos and a spelling mistake.

Revision 1.129  96/12/20  16:57:56  neto
Fixed a tex bug.

Revision 1.128  96/12/20  16:41:53  neto
Fixed typo in section name (init bookkeeping vars)

Revision 1.127  96/12/20  16:32:43  neto
First attempt at incorporating instance\_epsilon

Revision 1.126  96/12/20  13:40:39  neto
Put the unified gain variables back in.  Make it optional.

Revision 1.125  96/12/19  12:12:07  neto
Fixed a CWEB typo in the rcs log.

Revision 1.124  96/12/17  14:50:05  neto
Now it compiles when debugging output is turned on.
Also, fixed a CWEB style infelicity.

Revision 1.123  96/12/16  17:02:55  neto
Fixed a typo.
Forgot the comparison function for eligible moves; it now handles
the split representation.

Revision 1.122  96/12/16  16:38:37  neto
First attempt at separating cum\_gain into positive and negative parts.

Revision 1.121  96/08/19  18:22:01  neto
Fixed uninitialized variables.  
generic flips made being uninitialized was a *bug*!

Revision 1.120  96/08/16  16:29:59  neto
Made it pass all warning flags when "allow verbose" is on.
Added "watch this city"

Revision 1.119  96/08/16  13:04:45  neto
Added fixincludes.

Revision 1.118  96/08/16  12:40:42  neto
Converted putchar to printf.   Otherwise, I'd never get a prototype
for SunOS's \_flusbuf.

Revision 1.117  96/08/15  14:35:51  neto
Fixed a const-related warning.

Revision 1.116  96/08/15  14:18:47  neto
Make it pass more gcc warning flags.

Revision 1.115  96/08/15  13:20:57  neto
Make it pass -Wall

Revision 1.114  96/08/14  13:35:52  neto
Use sort instead of qsort.

Revision 1.113  96/08/07  15:33:50  neto
Added reasons why pointer-difference tie-breaking would break code
in several places.

Revision 1.112  96/08/07  15:18:44  neto
Make qsort optionally preserve the order of equals.

Revision 1.111  96/07/29  17:09:07  neto
Fixed to compile.

Revision 1.110  96/07/29  16:19:50  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

Revision 1.109  96/07/25  13:30:36  neto
Changed ALLOW\_VERBOSE to JBMR\_ALLOW\_VERBOSE

Revision 1.108  1996/07/05  18:18:46  david
Fixed log. Duh.

Revision 1.107  96/06/28  12:18:42  neto
Moved some TeX definitions to webdefs.w

Revision 1.106  96/06/24  16:18:01  neto
Fixed comment that CWEB was interpreting.

Revision 1.105  96/06/20  16:11:58  neto
Use a more math-like typeset name for t2ip1 and t2ip2

Revision 1.104  96/06/19  14:12:31  neto
Finished adding splay TABU stuff.  It's all-or-nothing, though.
It could use some experimental work to determine the right cut-off.
Also, try the LEDA dictoinaries.

Revision 1.103  96/06/04  12:41:58  neto
More TABU stuff.

Revision 1.102  96/06/03  15:36:34  neto
More tabu stuff.

Revision 1.101  96/05/31  17:07:05  neto
Added some measurements regarding tabu check in the generic phase of
the search.
Began to parameterize the code regarding tabu check.

Revision 1.100  96/05/29  11:13:12  neto
This version works.  
Needs improvement:
	command-line switches
	faster tabu check
	allow Papadimitriou tabu rule
	faster preprocessing
	different candidate lists

Revision 1.47  96/05/28  11:52:53  neto
Added a fflush

Revision 1.46  96/05/24  17:44:11  neto
Added probe statistics.

Revision 1.45  96/05/23  14:49:36  neto
Added fflushes everywhere, and a hook to examine a particular city
in detail.
This version does the full LK now.  It hasn't crashed yet.

Revision 1.43  96/05/23  11:46:44  neto
Fixed up the showing of the t array.

Revision 1.42  96/05/22  17:22:09  neto
Removed a redundant test for |best\_scheme\_id| == 13.
Added |length\_t\_pcast| where necessary.  (Ooops!)

Revision 1.40  96/05/22  16:34:08  neto
Fixed announcement of generic rollback.

Revision 1.39  96/05/22  15:49:08  neto
Added a forgotten \#endif

Revision 1.37  96/05/22  15:39:12  neto
Make debugging output rely on value of |verbose|, and only compiled in
if |ALLOW\_VERBOSE| is defined.

Revision 1.36  96/05/22  14:36:46  neto
Runon comment!!!
Terminated properly now.

Revision 1.34  96/05/22  13:38:10  neto
During backtracking, we must clean up our scheme even though best\_gain>0
because that may be due to some other scheme.
Also, add some debugging output for generic flips.

Revision 1.33  96/05/21  13:55:57  neto
Refine the case 1.2 legality test for t6.
Added some Case marker comments.

Revision 1.32  96/05/21  13:30:11  neto
Fixed the inorder query in the reverse direction.

Revision 1.30  96/05/21  12:24:30  neto
Fixed log comments.
All initial 3-changes are checked for feasibilty before we commit to
adding them.
For 4-changes, we perform the feasibility checks that are possible
with cities 1-6 before picking 7.
Added legality checks for 4-changes.
Gave intuitive-style "proofs" as to why the performed checks are necessary
and sufficient.

Revision 1.29  96/05/16  15:42:54  neto
Fixed stupidity with scheme 2 dating back to analysis time.

Revision 1.28  96/05/16  15:31:15  neto
Added missing initial flip to scheme 2 (transcribing problem).

Revision 1.27  96/05/16  15:25:20  neto
Enforce |7!=3| in scheme 2.

Revision 1.26  96/05/16  15:10:02  neto
Fixed one place where |base\_scheme[6]| wasn't properly being set.

Revision 1.25  96/05/16  15:01:20  neto
Made |base\_scheme| an array. Does this work?

Revision 1.24  96/05/16  13:40:09  neto
Optimized scheme 3 feasibility check (now legality checks are finished sooner.)
Defensive switches: add default clause to every switch.
(Caught a bug: need to restore old values of |base\_scheme| for later
backtracking.)

Revision 1.23  96/05/16  12:58:26  neto
Comment about scheme 11.

Revision 1.22  96/05/16  12:47:18  neto
Fixed scheme 10.

Revision 1.21  96/05/16  12:36:15  neto
Fixed scheme 9, including an errant last move in the sequence of lflips.

Revision 1.20  96/05/16  12:03:39  neto
Fixed scheme 6.

Revision 1.19  96/05/16  11:55:45  neto
Fixed scheme 1 (see notes)

Revision 1.18  96/05/15  14:55:21  neto
Made |a| the last city in |tour\_inorder(a,b,c,d)|.  This is how
I use it.

Revision 1.17  96/05/15  14:28:10  neto
Fixed a missing indirection error on constraints for |t[7]|.

Revision 1.16  96/05/15  14:00:11  neto
Print the tour when neighbour conditions not met.

Revision 1.15  96/05/15  13:54:06  neto
Even more debugging output.

Revision 1.14  96/05/15  13:17:34  neto
More debugging output.

Revision 1.13  96/05/14  17:49:26  neto
Added debugging output.
Somehow I'm not undoing an unsuccessful scheme.

Revision 1.12  96/05/14  17:20:56  neto
ID to Id

Revision 1.11  96/05/14  17:20:11  neto
Replaced RCS Header with Id.
}

\def\t#1ip#2{t_{#1i+#2}}
@s t2ip1 TeX
@s t2ip2 TeX
% The following would be cruel...
%\def\twoxi{2i}	 
%@@s two_i TeX

@*Johnson, Bentley, McGeoch, and Rothberg.
This module is my implementation of my understanding of the Johnson,
Bentley, McGeoch and Rothberg description of their implementation of
the Lin-Kernighan algorithm.
I hope that's clear.  If it is, then here's some more trouble:
I haven't got their report (it wasn't available as of February 28, 1996),
so I am going by the description given in Johson and McGeoch's
chapter on local search for the TSP. 

% Format |length_t| as if it were the keyword |int|
@s length_t int

@ This module provides the following interface.

Procedures 
|jbmr_setup| and |jbmr_cleanup| are the usual intialization 
and shutdown routines.

Procedure |jbmr_run| does the actual local search.

@ Procedure |jbmr_run| uses the currently registered oriented tour implementation, which is
accessed through the routines beginning with |tour_|.  It assumes a
starting tour has already been constructed.  

It also uses nearest neighbour lists, already constructed by module
\module{NN}.


@ The outline of this module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Early module headers@>@;
@<Module headers@>@;

@<Module definitions@>@;
@<Module types@>@;
@<Module variables@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *jbmr_rcs_id = "$Id: jbmr.w,v 1.192 1998/07/16 21:58:55 neto Exp neto $";

@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#define __USE_MISC		/* Linux needs this to get the definition of |nrand48| */
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include "fixincludes.h"

@ The exported interface is contained in the \file{jbmr.h} header file,
which has the following form.

@(jbmr.h@>=
extern const char *jbmr_rcs_id;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "prng.h"
#include "jbmr.h"


@ 
Up front, we know we'll need interfaces to
the error checking and memory allocation
modules, the |length_t| type (from 
\module{length}), the |cost| function (from \module{read}), and
the nearest 
neighbour lists |nn_list| (from \module{nn}).  We also want the
|incumbent_len| variable (from \module{lk}), which we will be modifying.

@<Early module headers@>=
#include "error.h"
#include "memory.h"
#include "length.h"
#include "read.h"
#include "nn.h"
#include "lk.h"


@*Setup and cleanup.
Procedure |jbmr_setup| just allocates the resources required by this module,
and sets up some module-level convenience variables.

@<Subroutines@>=
void
jbmr_setup(int the_n) {
	n = the_n;
	@<Other setup code@>@;
}

@
@<Exported subroutines@>=
void jbmr_setup(int the_n);

@ We should declare |n|.
@<Module variables@>=
static int n;	/* The number of cities. */

@ Deallocation is simple (especially with named sections!).
@<Subroutines@>=
void 
jbmr_cleanup(void)
{
	n=0;
	@<Other cleanup code@>@;
}

@
@<Exported subroutines@>=
void jbmr_cleanup(void);

@
We'll maintain a set of ``dirty'' cities, \ie, those cities 
whose edges have been modified since the last time they were declared
locally optimal.  

Bentley invented this notion (as near as I can tell)
in the paper ``Fast algorithms for the geometric TSP'' (check title).
However, he implemented this using the concept of a ``don't-look'' bit.
Johnson, Bentley, McGeoch, and Rothberg adopt this notion,
with the same name.

Notice the ``don't look'' bit 
is in the reverse sense in which I'm thinking about this
problem.  That is, Bentley's bit is {\it off} when there is work to
be done.  I prefer to think of it in the positive terms.  That is,
there is an entry in the dictionary for every city for which there
is work to be done.  This is inspired by the notion of 
page table ``dirty'' bits
from operating systems work.


@ We'll use a dictionary for this structure.  
We know that at some points in the
execution, for instance at the beginning, every city will be ``dirty''.
So we dispense with dynamic allocation for every transaction with the 
dictionary.  Instead, we'll just allocate an entire array at once.

@<Other setup code@>=
dirty_work = new_arr_of(int,n);
{ int i;
	for (i=0;i<n;i++) dirty_work[i] = i;
}

@ We must declare this array.
@<Module variables@>=
static int *dirty_work;

@ Cleaning up this portion is just deallocation. 
@<Other cleanup code@>=
free_mem(dirty_work);

@ We'll also need to maintain a set of added edges.  JBMR never delete
an added edge.  In particular, this leads to the guarantee that we'll
never explore more than |n| moves for a particular improvement sequence.

Papadimitriou's variation (INSERT REFERENCE) 
dispenses with the added edges list and
instead never inserts a previously deleted edge.  This extends the
possible depth to roughly all |n(n-1)/2| (undirected) edges.  
This 
version of the Lin-Kernighan algorithm is the basis of a PLS-complete
problem.  I would like to implement this variation at some point in the
future.  The machinery is in place now.

I'll use  a dictionary to maintain the set of added edges.  We'll
allocate these as we need them, as this will likely be a small list.
So we don't allocate anything for this purpose on a module-level basis.

An alternative way of doing this is to forget messing around with 
the whole dictionary and to just compare with pairs of entries in the |t| array.
This not only saves space, but it may be faster in the common case, that is,
when the search is shallow.


@*The Lin-Kernighan algorithm.
Ok.  Here's the big enchilada.

This is a local search routine.  It makes improvements until it can find
no more.  There are possible improvements to be made as long as there
are dirty cities.

We also implement the Iterated Lin-Kernighan scheme of Johnson
(INSERT REFERENCE) which was inspired by Martin-Otto-Felten's use of
chained local optimization.

@<Subroutines@>=
void 
jbmr_run (const int iterations, prng_t *random_stream) 
{
	@<|jbmr_run| variables@>@;
	dict_t *dirty_set;
	int *dirty, iteration;

	@<One-shot initialize@>@;
	@<Allocate |jbmr_run| sets and arrays@>@;
	@<Create the dirty set@>@;
	@<Make all cities dirty@>@;
	@<Show initial milestone@>@;

	for ( iteration=0; iteration < iterations ; iteration++ ) {
		@<Per-iteration initialization@>@;
		while ( (dirty = (int *)dict_delete_any(dirty_set,NULL)) != NULL ) {
			@<Search for an improving sequence starting at |*dirty|@>@;
		}
		@<Verbose: report end of LK step@>@;
		@<Revert to the previous solution if it was better@>@;
		@<If doing another iteration, perturb with a double-bridge@>@;
	}
	@<Verbose: report termination of LK phase@>@;
	@<Show final milestone@>@;
	@<Deallocate |jbmr_run| sets and arrays@>@;
	@<Verbose: print statistics@>@;
}

@
@<Exported subroutines@>=
void jbmr_run(const int iterations,prng_t*random_stream);

@ We need the dictionary interface.   
And the dictionary itself needs the pool-oriented
memory allocator interface.
@<Module headers@>=
#include "pool.h"
#include "dict.h"

@ We need to specify a comparison function and a printing function for cities.
@<Create the dirty set@>=
dirty_set = dict_create(cmp_int,prn_int);

@ These are easily defined.

In other places I have augmented comparison functions to use the pointer
difference as a tie-breaker.  It turns out that |cmp_int| is only
used in conjunction with |dirty_set|, which in turn is defined over
the elements of |dirty_work|, which is just the identity function.  So
tie-breaking is meaningless here: the values are equal if and only if
the pointers are equal.
@<Module subroutines@>=
static int
cmp_int(const void *a, const void *b) {
    return (*(const int *)a)-(*(const int *)b);
}

static void 
prn_int(void *a) {
    printf("%lx=int %d",(unsigned long)a,*(int *)a);
}


@ To make all cities dirty, we just insert every city into |dirty_set|.

@d mark_dirty(CITY) (dict_insert(dirty_set,dirty_work+(CITY)))

@<Make all cities dirty@>=
{ int i;
dict_delete_all(dirty_set,NULL);
for (i=0;i<n;i++) {
	mark_dirty(i);
}
}

@ We must also dispose of the dictionary.  We don't need a freeing action 
because the |dirty_work| array is deallocated in the |jbmr_cleanup| routine.

@<Deallocate |jbmr_run| sets and arrays@>=
dict_destroy(dirty_set,NULL);


@ We'll need an array to remember the sequence of cities in the LK change.
I follow the notation introduced by Lin and Kernighan and use a 1-based
array named |t|.

For example, |t[1]| is the anchor to the Hamiltonian path, and |(t[1],t[2])|
is the first edge removed, and  |(t[2],t[3])| is the first edge added.
In general, edge |(t[2i-1],t[2i])| is the $i$'th edge removed, and
|(t[2i],t[2i+1])| is the $i$'th edge added.  
Edge 
|(t[2i],t[1])| is always a ``phantom'' edge, \ie, it is the edge which 
completes the Hamiltonian path to a Hamiltonian cycle, but is never drawn
in the descriptions of the LK algorithm.

This array 1-based and is treated as a growable array.
The array itself is |t|; the number of entries allocated to it is 
|t_max_alloc|.



@<|jbmr_run| variables@>=
int *t, t_max_alloc;

@ 
The common case is for the 
|t| array to be
small. The average number of entries is roughly at most 
$14=8+6$ --- see the chapter
by Johnson and McGeoch.  Allocating 128 entries is a good compromise 
between saving on reallocations and saving space.

@<Allocate |jbmr_run| sets and arrays@>=
t_max_alloc = 128;
t = new_arr_of(int,t_max_alloc);

@
@<Deallocate |jbmr_run| sets and arrays@>=
free_mem(t);

@ We need a code fragment that will grow the array when necessary.

Doubling the size of the array each time we grow it 
requires at most constant amortized work per cell used. 

Under some  circumstances (known at compile-time),
we must notify others that we have moved the array.  
In particular, we must
update the nodes in the tabu splay tree.

@<Make sure |t[two_i+2]| is valid@>=
if ( two_i+3 >= t_max_alloc ) {
#if defined(TABU_SPLAY)
	int *old_t = t;
#endif
	do {
		t_max_alloc *= 2;	
	} while ( two_i+3 >= t_max_alloc );
	t = (int *)mem_realloc(t,sizeof(int)*t_max_alloc);
	@<|t| has moved from |old_t| to |t|@>@;
}


@ An extra tour query.  In my analysis, I found it useful to create the
following oriented tour query: |tour_inorder(a,b,c,d)| assumes that
|(a,b)| is an edge in the current tour, and answers the question ``in
a traversal of the tour beginning at |a| and going in the direction of
|b|, do we reach |c| no later than |d|? (We always count |a| as last.)''.

@<Module subroutines@>=
static int tour_inorder(int a, int b, int c, int d);
static int
tour_inorder(int a, int b, int c, int d) {
	if ( tour_next(a) == b ) return tour_between(b,c,d);
	else if ( tour_prev(a) == b ) return tour_between(d,c,b);
	else {
		@<Debug: print the tour@>@;
		errorif(1,"Bad tour_inorder(%d,%d,%d,%d)\n"); 
		return -1;	/* Satisfy {\tt gcc -Wall}. */
	}
}

@ We will need to record the cumulative improvement in the {\it Hamiltonian
path\/} following 
this sequence of moves.  This is recorded in the variable |cum_gain|.

Positive values mean net gains.

We'll also record, in |best_gain|, the gain made by the best {\it tour\/}
along this sequence (or along any two-city offshoot of this sequence).  
Note that |best_gain| and |cum_gain| are
not directly comparable because |cum_gain| doesn't include the cost of the
closing edge, \ie, the edge that joins the two ends of the Hamiltonian path.


%We use |possible_gain| as a working variable to compute the
%gain to be had by terminating the search now.
% |length_t possible_gain|;

@ Some experiments that I run use a floating point type for |length_t|.
Unfortunately, sometimes these experiments don't terminate, especially
as problem sizes become larger, \eg, random Euclidean inputs with
$10^5$ or more cities.   (This happened the week of December 11, 1996.)

Some of the smaller runs that do manage to terminate end with 
a badly underestimated tour length; I check the computed ``incumbent'' length 
in |incumbent_len| against a freshly computed tour length.  This effect
increases with the problem size.

After
a little bit of thought, my best guess is that I run into the problem of
\term{catastrophic cancellation}.  
@^catastrophic cancellation@>
@^precision@>
@^numerical analysis@>
@^floating point@>
That is, when we compute the difference
between two nearly-equal numbers, most of the precision is lost. 
In our case, we are alternately adding and then subtracting edge costs
from the variable |cum_gain|.  We may even end up getting the wrong
sign in the end.  This, of course, easily leads to non-termination.

So, I split |cum_gain| into a positive part and a negative part,
|cum_gain_pos| and |cum_gain_neg|.  These three numbers are  are related
by the following equation:
$$
\hbox{|cum_gain|} = \hbox{|cum_gain_pos|} - \hbox{|cum_gain_neg|}.
$$
Actually, this allows a degree of freedom, and I constrain it somewhat
by stipulating
that both |cum_gain_pos| and |cum_gain_neg| should be non-negative numbers.
This is just like the construction of the set of integers as a set
of equivalence classes of pairs of natural numbers.  

In the present situation,
edge costs that increase the cumulative
gain (lengths of removed edges) are added to |cum_gain_pos|, and  edge costs
that decrease the cumulative
gain (lengths of added edges) are added to |cum_gain_neg|.  
I assume here that the |cost| function is non-negative.  In fact, it will
usually be positive-definite.

@ On the other hand, I split these gain variables before I implemented the
idea of an \term{instance epsilon} (see below), which might alleviate the
same problem.  
@^instance epsilon@>
@^epsilon, instance@>
When the length type is inexact, the default is to split the gain variable
into positive and negative parts because that is safest.  
But this default may be overridden at compile time by defining the
symbol
|JBMR_REQUIRE_JOINED_GAIN_VAR|, say in file \file{lkconfig.h}.  
This symbol has no effect when the length type is exact.

Compile-time constant |LENGTH_TYPE_IS_EXACT|, provided by module
\module{LENGTH}
is non-zero when |length_t| is a type in which computations
are exact, \eg\ |length_t| is an integer or rational type.  
It is zero
when  there might be a loss of precision, \eg\ when |length_t| is
either |float| or |double|.

@<Module definitions@>=
#if LENGTH_TYPE_IS_EXACT || defined(JBMR_REQUIRE_JOINED_GAIN_VAR)
#define SPLIT_GAIN_VAR 0
#else
#define SPLIT_GAIN_VAR 1
#endif

@ Now we can define the positive and negative cumulative gain variables.
@<|jbmr_run| variables@>=
#if SPLIT_GAIN_VAR
length_t cum_gain_pos, cum_gain_neg;
#endif

@ Variable |best_gain| is always assigned the current value of the gain,
minus an edge cost.  So there is no need to break it up into positive
and negative parts.

@<|jbmr_run| variables@>=
length_t best_gain;

@ Now, when using an integer type for |length_t|, we don't want to
overflow the representation.  So summing the alternating series in
a single variable is in fact decidedly {\it better\/} than splitting
it up.  So we need to retain the integer manipulations of |cum_gain|
and related variables anyway.  

We use the compile-time constant |SPLIT_GAIN_VAR| to distinguish the
two cases.

@<|jbmr_run| variables@>=
#if !SPLIT_GAIN_VAR
length_t cum_gain;
#endif

@
The variables |best_two_i|, |best_exit_a|, and 
|best_exit_b| are defined by the following invariant:
{\medskip\leftskip=0.75in\rightskip=0.75in\noindent
The gain recorded in |best_gain| is put into effect 
by the changes encoded in |t[1]| through |t[best_two_i]|, followed
by the two cities |best_exit_a|, |best_exit_b|.\medskip}


The Lin-Kernighan algorithm includes many special cases for the initial 
2/3/4-change, and this affects the moves required for the exit.  If 
the best tour is found amongst these first few moves, then we must know
which sequence of moves to perform to get this best gain.  The identity
of this scheme is remembered in |best_scheme_id|, which takes on
values between 0 and 12, inclusive, for the initial 2/3/4-changes, and
13 for a generic change beyond that.  
See below
for a detailed discussion and encoding of these schemes.  It takes on the
value |-1| if it hasn't been defined yet.  

The value of |best_two_i| is always even.    
We maintain the invariant that  |best_scheme_id<0 == (best_gain == 0)|.
@<|jbmr_run| variables@>=
int best_two_i, best_exit_a, best_exit_b, best_scheme_id;


@ I'll also use a boolean variable |more_backtracking| to signal when we should
keep on looking.  This variable will be non-zero when we should continue
looking for starting sequences for the
tabu search, and false otherwise.  In particular, its value is 
the negation of the boolean value of the phrase ``an improving move has
been implemented''.
This variable is used to escape from
various loops in this search.  

Now, |more_backtracking| will almost be synonymous with |best_gain==0|.  
However,
there is one place where they mean something different.  If the initial
segment of the |t| list is an improving (valid) 2-change, then |best_gain>0|
will hold, but we still want to look deeper, at least three levels deep.

So, you ask, why not postpone the setting of  |best_gain| until we enter
the non-backtracking portion of the tabu search?  The problem with this
is that, in case the 2-change is the best improvement we can make, we
don't end up pruning the search as much as we ought to.  That is, all
of the search, including the backtracking search for the initial 3-opt, ought
to be pruned by the 1-tree condition: |best_gain < cum_gain|, which 
is the same as |best_gain + cum_gain_neg < cum_gain_pos|.

This is why we need a seperate boolean variable.

In fact, an improving initial 2-change is not the only situtation where we
need to keep searching in spite of having an improvement already in hand.
{\it Lookahead\/} (see below) also requires us to have this kind of escape.

@<|jbmr_run| variables@>=
int more_backtracking;

@ We will need a few bookkeeping variables.  

The integer |two_i| will be
an index in to the |t| array that points to the active endpoint, \ie, the
city at the end of the Hamiltonian path that is opposite to t[1], the anchor.
To put it another way, |(t[1],t[two_i])| is the phantom edge.

%The eight-entry (though 1-based) array |nn| is a set of read
%cursors into nearest neighbour lists.
%This is used to enumerate candidate neighbours.
% |int nn[9];|

@<|jbmr_run| variables@>=
int two_i;

@*Constraints on the search. 
See my notes of March 7 and April 22 
for an explanation of the case analysis involved
in cycling through all the possible 3-changes (and sometimes 4-changes).

There are four kinds of constraints on the cities that we choose:
\emphpar{%
1.~The LK condition says that the cumulative 1-tree gain must be
greater than the improvement represented by the best tour gain discovered
so far.
In terms of our program variables, this is expressed by |cum_gain > best_gain|,
\ie, |cum_gain_pos > best_gain + cum_gain_neg|.
This is
the main stopping criterion, and it is checked both as we generate the
initial 2/3/4-change, and as we generate the cities on the
deep $\lambda$-change.  I will also call these ``deep'' changes 
{\sl generic}.
}

\emphpar{%
2.~The JBMR tabu edge condition says 
``never delete an added edge''.  This condition
will be checked as we generate both the initial 2/3/4-change 
and the deep portion of the $\lambda$-change.
}

\emphpar{%
3.~The specified edge changes must be feasible.  
That is, there must
always be a legal sequence of flips to get from the current tour to the
tour specified by the changes.  This is where the handling
of the initial 2/3/4-change differs from the rest of the $\lambda$-change.
}

\emphpar{%
The starting 2/3/4-change is checked for feasibility only after the entire
2/3/4-change is specified.  This is because the entire sequence of
flips required to effect the
change depends on the placement of even the last city in the sequence.
For example, see how the flips that implement cases 2.2.2.1.1 and 2.2.2.1.2
differ even in their first filp, even though only the position of the
last city changes between the two cases.  
}

\emphpar{%
Beyond the 2/3/4-change, \ie, the regular ``deep'' $\lambda$-changes
are checked as they are generated, just like for the other two conditions.
}

\emphpar{%
4.~I have added a ``stupid check'': during backtracking, never add the
most recently deleted edge.
This way we avoid covering the same ground twice while generating the
initial  2/3/4-change.  It also quickly eliminates some illegal choices,
specifically, in schemes 1, 8, and 11.
% THINK ABOUT THIS MORE CAREFULLY IN THE t[7] case, because we may want
%  to end up with  a different sequence ending?
%  Well, scheme 11 shows that it is useful at the t[7] level.
}

@*Table-driven flips.
Now, if you look at the case analysis of April 22, you will see that there
is no discernable pattern to the flips required to effect the changes
in the initial 2/3/4-change.  Because of this, I use a table-driven 
approach to encoding these flips.  Instead of using in-line code implementing
the case analysis, I'm just going to encode my handiwork.

Encoding my handiwork in a table is simpler, smaller, and maybe even faster.
(It might be faster because the branches are easier to predict, either by
the compiler, or by the processor.)

@ I should mention that there are in fact many possible ways to effect the
required 2/3/4-change.  I am only recording one.  If it is infeasible, then
this 2/3/4-change is declared infeasible.  Note that this is a conservative
approximation, and that it is conceivable that an alternative implementation
of the same 2/3/4-change might be feasible.  

However, I have chosen not to look for alternative implementations for
the following reasons.  

First, this search may take up too much time, and
is not likely to be of much benefit.  A change is infeasible because it
repeats at least one city, and perhaps repeats many.  If we fail once, then
we are making changes in a tight corner, and it is likely that many alternative
flip sequences encoding that change 
will also fail.  Why go through the bother of enumerating
all these alternatives when a simpler change can probably effect just
as good a gain?

Second, it was difficult enough to find the effecting sequences of flips
in the first place.  In fact, in my March analysis I didn't even see
that the 2/3/4-change required special handling (\ie, different from
the deeper changes in the $\lambda$-change).  Writing a program to 
enumerate all possible flips implementing a given 2/3/4-change would be a 
task comparable to writing a program enumerating 
all the possible solutions to the Rubik's
cube.  I don't want to do that.

@  Here is the encoding of the flips required to effect the various
cases.

Array
|scheme[s]| holds the sequence of indices into the |t| array that implement
scheme |s|.  This sequence is read from left to right in groups of four.
A group of indices $a,b,c,d$ means apply |tour_flip(t[a],t[b],t[c],t[d])|.

The last entry of scheme |s| is in |scheme_max[s]-1|.
Array |scheme_num_cities| records the number of cities involved in each of
the schemes, \ie, the largest index into |t|.

The translation between case numbers (from my April 22 notes) and scheme
numbers is given in the comments.

@<Module variables@>=
static int scheme[14][16] =@+{@;
{
1,2,5,6,
4,3,2,5 },
/* Scheme 0, case 1.1.1 */

{
1,2,6,5,
2,6,4,3,
1,5,4,6 },
/* Scheme 1, case 1.1.2 */ 

{
5,6,3,4,
1,2,6,3,
6,2,8,7,
1,3,2,8 },
/* Scheme 2, case 1.2.1 */ 

{
5,6,3,4,
8,7,6,3,
1,2,3,8 },
/* Scheme 3, case 1.2.2 */ 

{
1,2,3,4 },
/* Scheme 4, case 2 */ 

{
1,2,3,4,
1,4,6,5,
6,4,8,7,
1,5,4,8 },
/* Scheme 5, case 2.1.1.1 */ 

{
1,2,3,4,
6,5,8,7,
1,4,5,8 },
/* Scheme 6, case 2.1.1.2 */ 

{
1,2,3,4,
1,4,5,6 },
/* Scheme 7, case 2.1.2 */ 

{
1,2,5,6,
5,2,3,4 },
/* Scheme 8, case 2.2.1 */ 

{
6,5,8,7,
4,3,8,5,
1,2,3,8 },
/* Scheme 9, case 2.2.2.1.1 */ 

{
1,2,8,7,
1,7,6,5,
1,5,2,8,
4,3,2,5 },
/* Scheme 10, case 2.2.2.1.2 */ 

{
6,5,4,3,
6,3,8,7,
1,2,3,8 },
/* Scheme 11, case 2.2.2.2.1 */ 

{
6,5,8,7,
1,2,5,8,
5,2,3,4 },
/* Scheme 12, case 2.2.2.2.2 */ 

{-1}	/* Scheme 13, a generic change, so this entry is unused apply */
}@+;

static int scheme_max[14] = { 8,12,16,12,4,16,12,8,8,12,16,12,12,0 };
static int scheme_num_cities[14] = { 6,6,8,8,4,8,8,6,6,8,8,8,8,0 };

@ We also need a scheme selection variable |scheme_id|.
It is declared local to the |jbmr_run| procedure, because it should not
be shared with other threads.

We determine the final value of |scheme_id| by performing the case
analysis as in my notes, all the while keeping |scheme_id| at value |-1|.  
During this determination, we use an 
array |base_scheme| indexed in the same way as |t|.
The value of |base_scheme[k]| is as 
tight a lower bound on the
final value of |scheme_id| as we can manage given the selections made
up to and including city |t[k]|.  Since schemes involve at most eight
cities, the values of index $k$ are bounded from above by 8.

When the analysis is finished, 
we set |scheme_id| and implement the changes required
for that scheme.  We maintain the invariant that |scheme_id == -1| if and
only if no intial 2/3/4-change has been implemented.

@<|jbmr_run| variables@>=
int scheme_id, base_scheme[9];


@*Performing the search.
At the very least, this code assumes that we have allocated at least
nine (8+1) entries in the |t| array.

We examine both neighbours of |t[1]| as possibilities for |t[2]|.  
Because it may lead to a better initial gain, we first try the farther
tour neighbour of |t[1]|.  This is a greedy criterion; Lin and Kernighan
use this kind of criterion to prefer one neighbour of |t[7]| over the other.

@<Search for an improving sequence starting at |*dirty|@>=
{
	int t1_n[2], t1_i;
	length_t t1_l[2];
	@<Verbose: announce start of search at |*dirty|@>@;
	t[1] = *dirty;
	t1_n[0] = tour_prev(t[1]);
	t1_n[1] = tour_next(t[1]);
	t1_l[0] = cost(t1_n[0],t[1]);
	t1_l[1] = cost(t1_n[1],t[1]);
#if JBMR_FARTHER_T1_FIRST
	if ( t1_l[0] < t1_l[1] ) {
		int tmp;@+
		length_t tmp_l;
		tmp = t1_n[0];@+t1_n[0] = t1_n[1];@+t1_n[1] = tmp;
		tmp_l = t1_l[0];@+t1_l[0]=t1_l[1];@+t1_l[1]=tmp_l;
	}
#endif

	@<Initialize the bookkeeping variables@>@;
	put_city(1);
	for ( t1_i = 0 ; t1_i < 2 && more_backtracking; t1_i++ ) {
		t[2] = t1_n[t1_i];
		@<Verbose: new |(t1,t2)|@>@;
#if !SPLIT_GAIN_VAR
		cum_gain = t1_l[t1_i];
#else
		cum_gain_pos = t1_l[t1_i];
		cum_gain_neg = 0;
#endif
		put_city(2);
		@<Search from |t[2]|@>@;
	}
	if ( best_gain > 0 ) {
		incumbent_len -= best_gain;
		@<Verbose: announce improvement by |best_gain|@>@;
		@<Check milestone@>@;
		@<Set the |instance_epsilon| slop value@>@;
	}
}

@  We initialize the cumulative gain components |cum_gain_pos| and
|cum_gain_neg| so that GCC's dataflow analysis doesn't complain when
the debugging code is allowed.

@<Initialize the bookkeeping variables@>=
#if !SPLIT_GAIN_VAR
cum_gain = 0;
#else
cum_gain_pos = cum_gain_neg = 0;
#endif
best_gain = 0; best_two_i = 0; best_exit_a = best_exit_b = -1;
more_backtracking = 1; scheme_id = best_scheme_id = -1;

@*Searching at level 0.  
As you may have guessed already (for instance from the presence of the
variable |more_backtracking|), the Lin-Kernighan algorithms performs some
backtracking.  Now, it's an odd beast in that it neither performs arbitrary
depth backtracking---for instance as every branch and bound algorithm does---
nor does it perform zero backtracking, as most pure greedy algorithms do.
If it chose either of these strategies, then our code 
would be simplified because of the regularity of these search paradigms.

Instead Lin-Kernighan is a hybrid, performing backtracking on the 
first few levels, and
probing in a purely greedy manner at deeper levels.
Fortunately, ``first few'' really means
``is bounded by a constant''.  So it will be convenient for us to build
and iterate through 
a fixed amount of state using ordinary nested loops.

Just to make things more interesting, 
the combinatorics of $k$-changes forces
each level of the search to have its own oddities, so each must be coded
differently in places.
Yet much of the code has the same overall structure, and we would like
to reflect that single architecture by using a single collection of 
named sections.  

Now, sit down, because I'm about to tell you how I managed to reconcile
these conflicting coding design goals.  Believe me, you won't like it.

Here it is.  
Most of the code is in a single collection of named sections.   The
top level of these is replicated once for each of the four levels of 
backtracking.  However, the oddities of each are separated out via
conditional compilation using the macro |BL|, which stands for {\sl
backtracking level}, and takes on one of the values 0, 1, 2, or 3.  

Actually, this code isn't nearly as ugly as it used to be.  

@
The search from |t[2]| is a prototype for the search from any city
in an even-numbered position in |t|.    They all share the same style:
first generate the list of all eligible moves from this point, and then
iterate through them.

INSERT MATERIAL ABOUT DECLUSTERING.

@<Search from |t[2]|@>=
two_i = 2;
@<Verbose: update |probe_depth|@>@;
#define BL 0
{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
const length_t cluster_dist=decluster_d(t[1],t[2]);
#else
const length_t cluster_dist=0;
#endif
@<Update |best_gain| and compose a list of eligible moves@>@;
}
@<Sort |e[BL]|@>@;
#undef BL
@<Backtrack at level 0@>@;

@ We employ lookahead as described in section 2B of the original LK
paper.  
It is also adopted by JBMR.  

This lookahead criterion states that we must choose the next two cities
so that
$$\cost(t[2i],t[2i+1]) - \cost(t[2i+1],t[2i+2])$$
is minimized.  That is, we go to the shortest succeeding Hamiltonian Path.

If we are in an initial special case, then we may be doing backtracking.
So we need to create a list
of such candidate moves; it will be convenient to sort them according to
the above criterion.

In such an array, each move's entry records the proposed choices for
|t[2i+1]| and |t[2i+2]|, 
the scheme ID (if applicable), and the net gain as expressed in 
|gain_pos| and |gain_neg|, the positive and negative parts of the gain.

@<Module types@>=
typedef struct {
	length_t gain_for_comparison;
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY 
	length_t cluster_dist;
#endif
#if !SPLIT_GAIN_VAR
	length_t gain;
#else /* |SPLIT_GAIN_VAR| */
	length_t gain_pos, gain_neg;
#endif /* |SPLIT_GAIN_VAR| */
	int t2ip1, t2ip2, scheme_id;
} eligible_t;

@ Each of the four possible search levels --- 
for searches at |two_i| being equal to
2,
4, 6, or higher --- has its own array of candidates.
These are stored in
the |e| array, in positions 0, 1, 2, and 3, respectively.  
% Only the first entry on the deepest level is used, because there is no
% backtracking at the deepest level.

@<|jbmr_run| variables@>=
eligible_t *(e[4]);

@ Each entry must contain space for
least twice |nn_max_bound| entries because for each choice of |t[2i+1]|, there
are up to two choices for |t[2i+2]|.

@<Allocate |jbmr_run| sets and arrays@>=
e[0] = new_arr_of(eligible_t,nn_max_bound*2);
e[1] = new_arr_of(eligible_t,nn_max_bound*2);
e[2] = new_arr_of(eligible_t,nn_max_bound*2);
e[3] = new_arr_of(eligible_t,nn_max_bound*2);

@
@<Deallocate |jbmr_run| sets and arrays@>=
free_mem(e[0]);
free_mem(e[1]);
free_mem(e[2]);
free_mem(e[3]);

@ Now, we may have varying numbers of eligible sequences at each of the levels.
In particular, we may have fewer than |nn_max_bound| valid entries in the 
0, 1, or 2
entries 
of |e|.  Array |en| holds
these counts, and is indexed in the same way as |e|.

@<|jbmr_run| variables@>=
int en[4];

@ During the actual backtracking search, we also need to know where amongst
the |e| array we are right now.  So we need four cursors, one for each
backtracking level.  These are stored in the integer array |ec|.  

At any point in the search, only entries |ec[0]| through |ec[BL]| are valid.
Furthermore, if |ec[i]| is valid, then |0<=ec[i]<en[i]|.

@<|jbmr_run| variables@>=
int ec[4];


@
Some of my experiments with |length_t==double| did not terminate. 
This happened even
after I split the gain variables (|cum_gain|, |cum_1|, and |cum_2|) into 
positive and negative parts in order to avoid catastrophic cancellation.
Examining a particular run, I noticed that this program eventually
got itself into
an endless loop, bouncing back and forth between 
two 3-changes every 25 tries at a new |t[1]|.  I think each of these
3-changes cancelled the other, but very small rounding errors in the 
caused the program to think that each was an improving 3-change.  Clearly,
the program was wrong about one of them.

My proposed fix is to use a positive slop value, |instance_epsilon|, and prune
any sequence of moves with a smaller cumulative gain than this.
Now, I call this value |instance_epsilon| to distinguish it from the 
machine epsilon, |LENGTH_MACHINE_EPSILON|. (|LENGTH_MACHINE_EPSILON| is
is the smallest number that can be added to 1 so that the result
is distinguishable from 1.)  

Actually, we prune any sequence of moves with a cumulative gain less
than the current best tour gain plus the instance epsilon.  Since we're
always testing against |best_gain+instance_epsilon|, I define a new
variable |best_gain_with_slop| that is just this sum.   This saves
us a floating point addition every time we test against this value.

%We initialize |instance_epsilon| so that GCC's dataflow analysis will 
%be silenced on this point.  We use a value of 1, which if kept, would
%result in no
@<|jbmr_run| variables@>=
#if !(LENGTH_TYPE_IS_EXACT)
length_t instance_epsilon=incumbent_len * LENGTH_MACHINE_EPSILON;
length_t best_gain_with_slop;
#endif

@ We must initialize |best_gain_with_slop| at the same time that we
intialize the bookkeeping variables.

@<Initialize the bookkeeping variables@>=
#if !(LENGTH_TYPE_IS_EXACT)
best_gain_with_slop = instance_epsilon;
#endif



@
However, 
|instance_epsilon| and |LENGTH_MACHINE_EPSILON| are related.  
Since we eventually subtract each tour gain from the incumbent length,
we require that the tour gain be large enough so that this subtraction
makes a difference.  (Excuse the pun.)  
@^pun@>
So the minimum value of |instance_epsilon| is 
$$\hbox{|instance_epsilon|} = 
\hbox{|incumbent_len|} \times \hbox{|LENGTH_MACHINE_EPSILON|}.$$
This gets set upon entry to |jbmr_run| and whenever we commit to
a net tour length reduction.

@<Set the |instance_epsilon| slop value@>=
#if !(LENGTH_TYPE_IS_EXACT)
instance_epsilon = incumbent_len * LENGTH_MACHINE_EPSILON;
#endif

@ The code looks really awful when we have two quasi-independent
dimensions of parameterization: exact vs.~inexact, and split vs.~joined.
The |CAREFUL_OP(LHS,OP,RHS)| takes out some of the visual clutter.   
It implements numerical comparison |OP| on left-hand side |LHS| and
right-hand side |RHS|.  The twist is that the |LHS| is a variable 
that might be split into positive and negative parts.  We try to avoid
catastrophic cancellation by adding negative parts to the right hand side.
The right hand side must end in a variable to which we may add
|_with_slop|.  Right now the only variable with that ending
is |best_gain_with_slop|.

The double hash |##| is the ANSI C token pasting
operator.  So, for example, if the length type is |double|, an inexact
type, and |SPLIT_GAIN_VAR| is true, then 
$$\hbox{|@[CAREFUL_OP(cum_gain,<,best_gain)@]|}$$ translates into
$$\hbox{|((cum_gain_pos)<(best_gain_with_slop)+(cum_gain_neg))|.}$$

@<Module definitions@>=
#if LENGTH_TYPE_IS_EXACT
#define CAREFUL_OP(LHS,OP,RHS) ((LHS) OP (RHS))
#elif SPLIT_GAIN_VAR
#define CAREFUL_OP(LHS,OP,RHS) ((LHS##_pos) OP ((RHS##_with_slop)+(LHS##_neg)))
#else
#define CAREFUL_OP(LHS,OP,RHS) ((LHS) OP (RHS##_with_slop))
#endif




@  We use a few bookkeeping variables when we update |best_gain| and compose 
an eligible list.

The neighbour list for city |i| is computed by |nn_list(i,&nn_bound)|.
Such a list an array
of |nn_bound| city numbers,
sorted in ascending order of
distance from city |i|;
|nn_bound| is bounded above by |nn_max_bound|.

Cities |t2ip1| and |t2ip2| are the candidates for |t[two_i+1]| and 
|t[two_i+2]|, respectively.  Lengths |cum_1| and |cum_2|
are the cumulative gains when we append |t2ip1| and |t2ip2| to the |t| list,
respectively.
When |length_t| is an inexact type, these are represented by their positive
and negative parts |cum_1_pos| and |cum_1_neg|, and 
|cum_2_pos| and |cum_2_neg|, respectively.  

City |t2ip1| is chosen from the nearest neighbour list of |t[two_i]|.
Since nearest neighbour lists are sorted, we stop as soon as 
the cumulative gain dips below the current best improvement.
For each choice of |t2ip1|, we may have up to two choices for |t2ip2| --- 
the tour neighbours of |t2ip1|.   

Updating |best_gain| and composing the eligible list of moves is heavily
dependent upon the case analysis.  

If declustering is not in effect, then |cluster_dist| is always zero.
Otherwise, it is the cluster distance between |t[1]| and |t[two_i]|.

@<Update |best_gain| and compose a list of eligible moves@>=
en[BL]=ec[BL]=0;@;
if ( @[CAREFUL_OP(cum_gain,>,cluster_dist+best_gain)@] ) {
int i, t2ip1, t2ip2, enbl, *neighbour_list, nn_bound; 
#if SPLIT_GAIN_VAR
	length_t cum_1_pos, cum_1_neg, cum_2_pos, cum_2_neg;
#else
	length_t cum_1, cum_2;
#endif
	@<Verbose: show current position@>@;


#if SPLIT_GAIN_VAR
	cum_1_pos = cum_gain_pos;
#endif

	neighbour_list = nn_list(t[two_i],&nn_bound);
	for ( i=0, enbl=0; i<nn_bound ; i++ ) {
		t2ip1 = neighbour_list[i];
#if SPLIT_GAIN_VAR
		cum_1_neg = cum_gain_neg + cost(t[two_i],t2ip1);
#else
		cum_1 = cum_gain - cost(t[two_i],t2ip1);
#endif

        if ( @[ CAREFUL_OP(cum_1,<=,best_gain) @] ) {
			@<Verbose: show terminating |cum_1|@>@;
			num_reject_by_cum_1++;
			break;
		}

		@<Fill |e[BL][enbl]| for valid |t2ip2|'s and maybe update |best_gain|@>@;
	}
	en[BL] = enbl;
} else {
	num_reject_pre_e_build++;
}

@ Variables |num_reject_by_cum_1| and |num_reject_pre_e_build| are purely
instrumentation.
@<|jbmr_run| variables@>=
int num_reject_by_cum_1, num_reject_pre_e_build;

@
@<One-shot initialize@>=
num_reject_by_cum_1=num_reject_pre_e_build=0;


@ On the first level, |t[4]| may be either neighbour of |t[3]|.  We don't
care which we pick first because they will be sorted by the greedy
lookahead criterion anyway.

I've factored out the code that does the updating.

@<Fill |e[BL][enbl]| for valid |t2ip2|'s and maybe update |best_gain|@>=
#if BL==0
	@<Try both neighbours of |t2ip1|@>@;
#endif

@ One at a time, we set |t2ip1| to each of the two neighbour current
neighbours of |t2ip1|.

Array |tour_neighbour| just lets us call either of |tour_prev| or
|tour_next|, depending on an integer parameter.  Since both those
latter functions are really just function pointers anyway, the overhead
of calling it through an array reference should be negligible.
Besides, this loop makes the code much more compact.  More compact code
should improve performance because it increases the effectiveness of 
the instruction cache.

Then again, it might be faster to unroll the loop.  
% It is unrolled if the symbol |JBMR_UNROLL_PREV_NEXT_LOOP| is defined.
If you so desire, substitute the following code for this section:

|t2ip2=tour_prev(t2ip1);|\par
|@<Update |best_gain| and |e[BL]| if not tabu@>@;|\par
|t2ip2=tour_next(t2ip1);|\par
|@<Update |best_gain| and |e[BL]| if not tabu@>@;|

But I warn you, this leads to very large \CEE/ files, and therefore
long compilation times.

@<Try both neighbours of |t2ip1|@>=
#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{	int which_neighbour; 
for (which_neighbour=0;which_neighbour<2;which_neighbour++) {
	t2ip2=(tour_neighbour[which_neighbour])(t2ip1);
	@<Update |best_gain| and |e[BL]| if not tabu@>@;
}
}
#endif

@ But we do need to declare array |tour_neighbour|.
It is an array of two pointers to functions that take an integer
and return an integer. Got that?
@<|jbmr_run| variables@>=
#if !defined(JBMR_UNROLL_PREV_NEXT_LOOP)
int (*tour_neighbour[2])(int);
#endif

@ The ordering is arbitrary.
@<One-shot initialize@>=
#if !defined(JBMR_UNROLL_PREV_NEXT_LOOP)
tour_neighbour[0]=tour_prev;
tour_neighbour[1]=tour_next;
#endif

@ 
The JBMR tabu rule is ``never delete an added edge''.  On the first level,
this amounts to |t[4]!=t[2]|, and we check that here.

@<Update |best_gain| and |e[BL]| if not tabu@>=
#if BL==0
if ( t[2] != t2ip2 ) {
	@<Update |best_gain| and |e[BL]|.@>@;
}
#endif

@  This bit of code records the move in the |e| array.

Once we reach here, we know that the proposed move is passes the 1-tree and
tabu tests, and is not known to be infeasible.  So it is an eligible move,
and it gets recorded in |e|.

@<Update |best_gain| and |e[BL]|.@>=
{ 
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist=decluster_d(t[1],t2ip2);
@<Verbose: cluster distance@>@;
#endif

#if !SPLIT_GAIN_VAR
	cum_2 = cum_1 + cost(t2ip1,t2ip2);
#else /* |SPLIT_GAIN_VAR| */
	cum_2_pos = cum_1_pos + cost(t2ip1,t2ip2);
	cum_2_neg = cum_1_neg;
#endif /* |SPLIT_GAIN_VAR| */

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST 
if ( @[ CAREFUL_OP(cum_2,<,cluster_dist+best_gain) @] ) {
	@<Verbose: declustering rejects candidate pair@>@;
} else 
#endif

{
@<Update |best_gain| and set scheme@>@;
e[BL][enbl].t2ip1 = t2ip1;
e[BL][enbl].t2ip2 = t2ip2;

#if !SPLIT_GAIN_VAR
	e[BL][enbl].gain_for_comparison = e[BL][enbl].gain = cum_2;
#else
	e[BL][enbl].gain_for_comparison = cum_2_pos-cum_2_neg;
	e[BL][enbl].gain_pos = cum_2_pos;
	e[BL][enbl].gain_neg = cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
#	if BL<3
		e[BL][enbl].gain_for_comparison -= cluster_dist;
#	else
		e[BL][enbl].cluster_dist = cluster_dist;
#	endif
#endif

@<Verbose: output candidate pair@>@;
enbl++;
}
}

@ We need the interface to the decluserting  module.
@<Module headers@>=
#include "decluster.h"
#include "declevel.h"

@  This section of code performs two jobs for us:  sets the scheme, and 
perhaps update |best_gain|.

The scheme is determined by checking the ordering of the cities around
the tour.  This is all we need to do, indeed all we {\it can\/} do
at this point to discriminate between the possible
schemes.

Now, candidates for |t[3]| and |t[4]| can complete a legal 2-change
if and only if
|tour_inorder(t[1],t[2],t[4],t[3])| holds
and the move is feasible.    The ordering condition is the first thing this
section checks.

As far as feasibility goes, 
we already know that |t[2]!=t[3]| by the 1-tree condition, and that
|t[1]!=t[2]| and |t[3]!=t[4]| because each are respective tour neighbours.
So we need only check that |t[1]!=t[4]| holds.

@<Update |best_gain| and set scheme@>=
#if BL==0
	if ( tour_inorder(t[1],t[2],t2ip2,t2ip1) ) {
		e[BL][enbl].scheme_id = 4;
		if ( t[1] != t[4] ) {
			@<Set |best_gain| if this move is better@>@;
		}
	} else {
		e[BL][enbl].scheme_id = 0;	/* Record for deeper levels. */
	}
#endif



@ Here's where we finally (maybe) set |best_gain| and associated variables.

We need to compute the cost of closing up the Hamiltionian path to make
a Hamiltonian tour. There is only one way to do this: add in the phantom
edge from |t2ip2| to |t[1]|.

We've separated this code out because we will use it again and again.

@<Set |best_gain| if this move is better@>=
{const length_t cost_phantom = cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR 
   const length_t cum_exit_now = cum_2 - cost_phantom;
#endif

   if (
#if LENGTH_TYPE_IS_EXACT
	   cum_exit_now > best_gain
#elif SPLIT_GAIN_VAR
	   cum_2_pos  > best_gain_with_slop + cum_2_neg + cost_phantom
#else
	   cum_exit_now > best_gain_with_slop
#endif
      )
{

#if SPLIT_GAIN_VAR
	best_gain = cum_2_pos - cum_2_neg - cost_phantom;
#else
	best_gain = cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
	best_gain_with_slop = best_gain + instance_epsilon;
#endif

	best_two_i = two_i;
	best_exit_a = t2ip1;
	best_exit_b = t2ip2;
	best_scheme_id = e[BL][enbl].scheme_id;
	@<Verbose: output new |best_gain|@>@;
}
}

@ Now that we've constructed the lookahead array, we need to 
sort it in non-decreasing order of the |gain| entry.

Now, if only the rest of the code were this easy.  :)

We use the sorting routine pointed to by |sort|; it must have
the same signature as the |qsort| standard library function.  
Module \module{LK} sets the |sort| pointer.

@<Sort |e[BL]|@>=
sort(e[BL],(size_t)en[BL],sizeof(eligible_t),cmp_eligible);

@ The comparison function returns an integer less than, equal to, or greater
than 0, if the gain of the
first input is respectively {\it greater\/} than, equal to or {\it less\/}
than the gain
of the second input.

Sometimes we want to make the comparision function a little more 
stringent, for example to ensuring repeatability in case of a randomized
sorting function.
We use a compile time constant |QSORT_DETERMINATE| to force 
the Quicksort method to be a stable sort by
breaking all ties between distinct entries.

@<Module subroutines@>=
static int
cmp_eligible(const void *a, const void *b) 
{
	length_t diff =   ((const eligible_t *)a)->gain_for_comparison
					- ((const eligible_t *)b)->gain_for_comparison;
	return diff > 0 ? -1 : (diff < 0 ? 1 : 

#if defined(QSORT_DETERMINATE)
			(int)(((eligible_t *)a)-((eligible_t *)b))
#else
											0 
#endif
											);
}

@ We've now completed the construction of the eligible move list 
at the first level.
We're ready to implement backtracking.

We use specially named sections for each level of backtracking for
two reasons.  First, the code really looks different at each level,
so we may as well call it by a different name.
Second, 
we will be nesting all the code for the deeper search
within this code.  However, CWEB doesn't allow cyclic code webs.

Of course, I wouldn't have to nest the code if I allowed myself either
luxury of recursion or |goto|s.  I don't use recursion because I don't want
to pass all that local state around, nor pass it through an indirect reference
because that costs too much; I haven't made the local state
global because I want to port this routine to a multi-threaded environment.
I don't use |goto|s because they are {\sl considered harmful} INSERT
REFERENCE, though
not fatal INSERT REFERENCE.

@ Here's the backtracking code at the first level.

The interesting bit here is the delay of implementing the 2-change until after
all its possible successors have been examined.


At all the levels below this one, there is an early exit mechanism.
Specifically,
if we find an improving sequence of moves, we keep following that path
for as long as possible.  Once we hit the end of this path in the search,
we implement the best improvement that we've found, and terminate the
search.  The mechanism for the early exit is the presence of the
|more_backtracking| variable in the test of our loop. 

I'll defer the description of how to unroll changes until later, because
I haven't even shown you how to implement those changes in the first place!

% Now, an interesting thing happens with the eligible move list.  It may be
% the case that early on, |best_gain| is rather small, so some poor opening
% moves get placed on list.  Later, however, |best_gain| may be improved, and
% therefore becomes a more selective filter for membership on the eligible
% moves list.
% 
% Stop the presses.  I don't care about this because the |best_gain| move
% is moved up to the start of the list.  When we process that best_gain
% move, we perform an early exit from the loop and therefore never process
% a succeeding eligible move.  So we don't need a second |best_gain|
% filter inside this loop.
% 
% 

@<Backtrack at level 0@>=
for (ec[0] = 0; more_backtracking && ec[0] < en[0] ; ec[0]++ ) {
	eligible_t *this_move = &e[0][ec[0]];
	t[3] = this_move->t2ip1;
	t[4] = this_move->t2ip2;
#if !SPLIT_GAIN_VAR
	cum_gain = this_move->gain;
#else
	cum_gain_pos = this_move->gain_pos;
	cum_gain_neg = this_move->gain_neg;
#endif
	two_i = 4;
	@<Verbose: update |probe_depth|@>@;
#define BL 1
{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
	const length_t cluster_dist=this_move->cluster_dist;
#else
	const length_t cluster_dist=0;
#endif
	@<Update |best_gain| and compose a list of eligible moves@>@;
}
	@<Sort |e[BL]|@>@;
#undef BL
	@<Backtrack at level 1@>@;
	@<If necessary, implement an improving 2-change@>@;
}

@ Scheme 4 is a 2-change.  To implement such a change, we must first
unroll any
previous changes.
Then we fix up the end of the |t| array, implement the changes, and mark
the involved cities as dirty.

@<If necessary, implement an improving 2-change@>=
if ( best_scheme_id == 4 ) {
	@<Unroll all the changes@>@;
	t[3] = best_exit_a; t[4] = best_exit_b;
	scheme_id = 4;
	@<Implement |scheme_id|@>@;
	@<Mark changed cities as dirty@>@;
	@<Verbose: report improving 2-change@>@;
	more_backtracking = 0; 
}

@ The cities which have had their edges changed by a tour improvement
should be marked dirty.


@<Mark changed cities as dirty@>=
{ int i;
	for ( i=1; i<=best_two_i ; i++ ) {
		mark_dirty(t[i]);
	}
	mark_dirty(best_exit_a);
	mark_dirty(best_exit_b);
}

@ My implementation of Iterated Lin-Kernighan (see below) requires 
that we keep list of differences be kept between the end-tour of the previous 
iteration of LK and the end-tour of the current iteration.
The differences are just the sequences of improving $\lambda$-changes.

Each $\lambda$-change is encoded as the values of
|t[1]| through |t[best_two_i]| followed by |best_exit_a|, |best_exit_b|,
|scheme_id|, and finally the value |best_two_i+3|.
Now, the length goes {\it after\/} the array because we will be using
the log in reverse.

Of course, if there is nothing to revert to, then we shouldn't record 
the |t| array.  That is, only record the diffs when |iteration > 0|.


@^Iterated Lin-Kernighan@>

@d write_log(a) (change_log[change_log_next++] = a)

@<Mark changed cities as dirty@>=
if ( iteration > 0 ) {
const int more_log = 4+best_two_i;
@<Make sure |change_log| has space for |more_log| more integers@>@;
{ int j;
	for ( j=1;j<=best_two_i; j++) {
		write_log(t[j]);
	}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


@
@<Make sure |change_log| has space for |more_log| more integers@>=
if ( more_log >= change_log_max_alloc ) {
	do {
		change_log_max_alloc *= 2;	
	} while ( more_log >= change_log_max_alloc );
	change_log = (int *)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

@ Initially |change_log| is given 10000 entries.

@<Allocate |jbmr_run| sets and arrays@>=
change_log_max_alloc=10000;
change_log = new_arr_of(int,change_log_max_alloc);

@ We also need to clean it up.
@<Deallocate |jbmr_run| sets and arrays@>=
free_mem(change_log);


@ We need to declare |change_log|, |change_log_next|, and
|change_log_max_alloc|.

@<|jbmr_run| variables@>=
int *change_log=NULL, change_log_max_alloc, change_log_next=0;


@*Searching at level 1.  
Now we are ready to tackle the second level: picking |t[5]| and |t[6]|.

It would be dumb to allow |t[3]==t[5]|.  Why?  Because then |(t[4],t[5])|
would be just adding the edge |(t[3],t[4])| that we just removed!  
So we eliminate
this possibility at the outset.  

This kind of condition will always apply
from now on, \ie, at all deeper levels of the search.
Note that we didn't have this wrinkle to contend with at
the first backtracking level because requiring that |t[3]!=t[1]| holds 
is already covered
by the 1-tree condition.  Yet, the 1-tree condition doesn't eliminate this
check from this and lower levels because we may have a lot of 
gain credits already
``in the bank''.

From this point on, the feasibility conditions will be much more complicated. 
To simplify matters, we accumulate all the orientation knowledge we can right
at the start.  We do this so we don't ask any ``stupid'' questions later,
\ie, we never ask the same question twice. 

%(An algorithm that never asks stupid questions is called {\sl parsimonious}.
%This concept was invented by INSERT REFERENCE, and is discussed by Knuth
%in section 15 of his short book {\sl Axioms and Hulls}.  It's a nice idea,
%and I'm applying it here for the sake of efficiency, and perhaps efficacy.  
%I'm hoping that keeping 
%the interaction with the abstract tour data type to a minimum will both
%speed things up, and as a long shot, improve the chances that we'll have 
%less contention once this program is ported to a parallel setting.)

@<Fill |e[BL][enbl]| for valid |t2ip2|'s and maybe update |best_gain|@>=
#if BL==1
if ( t2ip1 != t[3] ) {
	switch( e[0][ec[0]].scheme_id ) {
	case 0: base_scheme[5] = tour_inorder(t[1],t[2],t2ip1,t[3]) ? 0 : 2; break;
	case 4: base_scheme[5] = tour_inorder(t[1],t[2],t2ip1,t[4]) ? 5 : 8; break;
	default: errorif(1,"Non exhaustive switch: %d",e[0][ec[0]].scheme_id);
	}
	@<Verbose: show |base_scheme[5]|@>@;
	@<Try both neighbours of |t2ip1|@>@;
}
#endif


@ Here we must check the tabu condition: that |(t[5],t[6])| hasn't previously
been added.
That is, the move is tabu if
|(t[5] == t[4] && t[6] == t[5]) || (t[5] == t[5] && t[6] == t[4])
||(t[5] == t[2] && t[6] == t[3]) || (t[5] == t[3] && t[6] == t[2])|.
However, note that |t[5]==t[5]| is redundant.  Furthermore,
the test |(t[5] == t[4] && t[6] == t[5])| always fails because 
|t[5]| is always chosen to be different from |t[4]|; we want to add the
edge |(t[5],t[4])|, and hence |t[5]| appeared on the nearest neigbours list
of |t[4]|.
So we can skip that disjunct altogther.
The final tabu condition becomes:
 | (t[6] == t[4]) ||(t[5] == t[2] && t[6] == t[3]) || (t[5] == t[3] && 
t[6] == t[2])|.

%Here's a question about C compilers. I've stated the tabu condition in
%the positive sense.  That is, disallow conditions encapsulated in the
%formula $F$.  Then I use it as |!F|.  Now, C uses short-circuiting semantics
%for its logical boolean operators |||| and |&&|.  That means that the operands
%are evaluated left to right, and as soon as the final value is known, then
%evaluation terminates.  For example, this allows 
%the following test to always proceed
%without a divide by zero error:
%|x==0 || y==4/x|.
%Now, is the C compiler forced (say, by the ANSI standard) to 
%push the negation down so that the short-circuiting
%semantics of the embedded operators are always exposed?   I think so$\ldots$
%See sections 7.5.4 and 7.7 in Harbison and Steele's 
%\book{C: A Reference Manual}.

Once we have eliminated tabu moves, we start refining our knowledge of the
scheme.  This knowledge is used later on.

The legal values of |base_scheme[5]| upon entry are 0, 2, 5, and 8.

A base scheme of 0 at this point ends up either as scheme 0 or as scheme 1,
both of which are 3-changes.  Schemes 7 and 8, both of which are recognized
at this stage, are also 3-changes.
Before we commit to adding these to the list of
eligible moves, we must pass them through both a legaility and
the feasibility filter.  To save on variables, I only use a single
variable |is_illegal| to catch both cases.

For 4-changes, we also perform the legality and feasibility checks which
involve only cities |t[1]| through |t[6]|.

%Now, the |switch| statement looks funny because all the |tour_inorder| calls
%are the same.  But each branch of the switch performs different sanity checks,
%and records the results in |is_illegal|.  These aren't tabu restrictions,
%but just ensure that we won't try something illegal later on.

@<Update |best_gain| and |e[BL]| if not tabu@>=
#if BL==1
if ( !( /* Never delete an added edge. */
	(t2ip2 == t[4]) 
	||(t2ip1 == t[2] && t2ip2 == t[3]) 
	||(t2ip1 == t[3] && t2ip2 == t[2]) )) {
	int is_illegal = 0;
	switch( base_scheme[5] ) {
	case 0: /* 1234.  We know edge |{3,4}| is not the same as |{1,2}|
			because |1234| and |3!=1| by the 1-tree condition. */
		if ( tour_inorder(t[1],t[2],t2ip2,t2ip1) ) {	/* |1265| */
			base_scheme[6] = 0;	/* Case 1.1.1 */
			/* Edge |{6,5}| is not edge |{3,4}| because 1234 and 1253 and
			1265.  It is not edge |{1,2}| because |6!=5| and 1253 and 1234,
			so edge |{3,4}| intervenes between 5 and 1.  But feasibility
			check needs to be done.  */
			is_illegal = t[2] == t2ip1 || t[1] == t2ip2;
		} else {
			base_scheme[6] = 1;	/* Case 1.1.2 */
			/* |{5,6}!={1,2}| because |!1265| ensures that |5!=1| and |6!=2|,
			and edge |{3,4}| intervenes between 6 and 1.
			|{5,6}!={3,4}| because 1234 and |!1265|, so 1234 and 1256, and
			|5!=3| by the stupid check. However, 
			feasibility needs to be checked. */
			is_illegal = t[2] == t2ip2 || t[1] == t2ip1 || t[4] == t2ip2 
				|| t[1] == t2ip2;
		}
		break;
	case 2: 
		base_scheme[6] = 2;	/* Case 1.2 */
		is_illegal = tour_inorder(t[3],t[4],t2ip1,t2ip2); 
		/* Suppose it isn't illegal by the above test.  We want to
			make sure that |{6,5}!={3,4}| and |{6,5}!={1,2}| hold.
				We know |(1,2)|, |(3,4)|, and |(6,5)| are all oriented
			in the same way.  So |(6,5)!=(3,4)| because |5!=4| by construction.
			Also, |(6,5) != (1,2)| because |5!=2| since |!1253| is known.
			So legality holds as far as we can tell, without us doing any
				more work. */
		break;
	case 5: /* We know |!1234&&1254| */
		if ( tour_inorder(t[1],t[2],t2ip2,t2ip1) ) { /* 1265 */
			base_scheme[6] = 5;	/* Case 2.1.1 */
			/* Schemes 9 through 12 are 4-changes, so the
				checks involving cities 7 and 8 are deferred.  However
				we must disallow |{6,5}=={1,2}| and |{6,5}!={4,3}|.
				Let's do the second one first: |{6,5}!={4,3}| follows
				from |!1234| and |1254| and |1265| since 6 is nested before
				5 which is before 6.
				Now |{6,5}!={1,2}| follows because first, |{3,4}| intervenes
				between 5 and 1, so |5!=1|, and second, |6!=1| because
				1265 and |{3,4}| intervenes between 1 and 5, so it must
				also intervene between 1 and 6.  So legality---as far
				as we can tell---follows. */
		} else { /* |!1265| */
			base_scheme[6] = 7; /* Case 2.1.2 */
			/* Legality:  |{5,6}!={4,3}| because |!1234| implies |1243|, 
			and |!1265| implies 1256, but |5!=4| by construction.
			|{5,6}!={1,2}| may occur here, but only if |6==1|; we check that
			here in feasibility.  Feasibility pairs: 14, 16. */
			is_illegal = t2ip2 == t[1] || t[1]==t[4];
		}
		break;
	case 8: /* We know |!1234&&!1254| */
		if ( tour_inorder(t[4],t[3],t2ip2,t2ip1) ) { /* 4365 */
			base_scheme[6] = 8; /* Case 2.2.1 */
			/* Legality: 
			Knowing 4365 tells us that either |(4,3)| and |(6,5)|
			are oriented the same way, or |(6==4)| and |5==3|.
			The second case is not possible because it is eliminated by
			the stupid check; in particular, |{6,5}!={4,3}|.  	
			We must only worry about |{6,5}={1,2}|.  Now, |!1234| implies
			that 1243 and |4!=1| and |(1,2)| is oriented in the same way
			as (4,3), which in turn is oriented in the same way as
			(6,5).  But |!1254| tells us that 5 lies between 3 and 1,
			so 6 must lie between 3 and 5, and therefore 6 cannot be
			2 because 4 intervenes between 3 and 2.  So |{6,5}!={1,2}|
			and legality follows. 
			*/
		} else {	/* |!1234&&!1254&&!4365| */
			base_scheme[6] = 9; /* Case 2.2.2 */
			/* Schemes 9 through 12 are 4-changes, so the
				checks involving cities 7 and 8 are deferred.  However
				we must disallow |{6,5}=={1,2}| and |{6,5}!={4,3}|.
				First, |5!=3| by the stupid check, and |5!=4| by construction,	
				so |{6,5}!={4,3}|.
				Second, |!4365| implies |(5,6)| is oriented as |(4,3)|, which
				itself is oriented as |(1,2)| because |!1234| holds.
				So to ensure legality, as far as we can tell, we must
				enforce |(5,6)!=(1,2)| as a pair.
				*/
			is_illegal = t2ip2 == t[2];
		}
		break;
	default: errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
	}
	if ( !is_illegal ) {
		@<Verbose: show |base_scheme[6]|@>@;
		@<Update |best_gain| and |e[BL]|.@>@;
	}
}
#endif /* BL==1 */

@ This section handles only eligible moves for backtracking level 1.  

Its first job is to set |e[BL][enbl].scheme_id|, which should take on the
value in |base_scheme[6]|.

Its second job is to update |best_gain| and associated variables when 
this move
is a legal tour-completing move.  To determine this, we
must check feasibility.  See my notes of May 8, 1996 for the
detailed analysis.  However, one can generate the constraints as follows. 

We need to make sure that every flip, say of the form |tour_flip(a,b,c,d)|,
is legal.

The first criterion is that edges |(a,b)| and |(d,c)| are oriented 
in the same way.
However, we don't need to check that here because the scheme analysis 
has already taken care of this.

The second criterion is that |a!=b|, |c!=d|, |b!=c|, and |d!=a|, which we
check here.

Now, we can eliminate some of these tests by the following observations.
City |2k| is
always distinct from city |2k+1| because the latter is found on the nearest
neighbour list of the former.  Also, |2k+1| is always distinct from |2k+2|
because the latter is a tour neighbour of the former.  We've just proven
that |t[k]!=t[k+1]| for all $k$.  This eliminates a good fraction of the
potential tests.

For completeness, here is a listing, for each scheme, 
of all the pairs that need to be
tested for inequality:
\emphpar{%
Scheme 0: 25,16\hfil\break
Scheme 1: 26,15,46,16\hfil\break
Scheme 2: 13,26,36,28,18\hfil\break
Scheme 3: 36,38,18\hfil\break
Scheme 4: 14\hfil\break
Scheme 5: 14,46,15,48\hfil\break
Scheme 6: 14,58,18\hfil\break
Scheme 7: 14,16\hfil\break
Scheme 8: 52,16\hfil\break
Scheme 9: 58,38,13,28\hfil\break
Scheme 10: 17,15,28,25,18\hfil\break
Scheme 11: 18,36,38\hfil\break
Scheme 12: 58,25,18
}

We have already used the Scheme 4 conditions at backtracking level 0.

As a reminder, upon entering this code, the value of |base_scheme[6]| is
restricted to one of 0, 1, 2, 5, 7, 8, or 9.  
This section of code will only test those schemes that don't involve
cities |t[7]| and |t[8]| (and which aren't scheme 4).  That list is:
schemes 0, 1, 7, and 8.  A simple test is to index into 
|scheme_num_cities| and make sure it is 6.


@<Update |best_gain| and set scheme@>=
#if BL==1
if ( scheme_num_cities[e[BL][enbl].scheme_id = base_scheme[6]]==6 ) {
	@<Set |best_gain| if this move is better@>@;
}
#endif

@ Now we're ready for the backtracking code for level 1.

The interesting aspect this time around is that we may have finished
defining an initial 3-change, in which case we should implement it and
move on to the general case.  Otherwise, we're building an initial 4-change,
and we just move to the next level.

@<Backtrack at level 1@>=
for (ec[1] = 0; more_backtracking && ec[1] < en[1] ; ec[1]++ ) {
	eligible_t *this_move = &e[1][ec[1]];
	t[5] = this_move->t2ip1;
	t[6] = this_move->t2ip2;
#if !SPLIT_GAIN_VAR
	cum_gain = this_move->gain;
#else
	cum_gain_pos = this_move->gain_pos;
	cum_gain_neg = this_move->gain_neg;
#endif
	two_i = 6;
	@<Verbose: update |probe_depth|@>@;
	if ( scheme_num_cities[this_move->scheme_id] == 6 ) {
		scheme_id = this_move->scheme_id;
		@<Implement |scheme_id|@>@;
		@<Perform the greedy search@>@;
		@<If necessary, implement an improving 3-change or clean up@>@;
	} else {
#define BL 2
			{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
			const length_t cluster_dist=this_move->cluster_dist;
#else
			const length_t cluster_dist=0;
#endif
			@<Update |best_gain| and compose a list of eligible moves@>@;
			}
		@<Sort |e[BL]|@>@;
#undef BL
		@<Backtrack at level 2@>@;
	}
}


@
As with improving 2-changes, we check to see if we must implement an
improving 3-change at this level after a deeper search.  

Note the special
handling of the case where the best 3-change is a prefix of the deeper
search that we're dropping out of.  I do this to reduce the interaction with
the tour abstract data type in the hopes that this will reduce contention
in the parallel setting.

Once a positive tour gain has been discovered, we do exactly one
deep search before implementing the sequence of moves leading to the
best gain discovered so far. This implies that at this point, 
cities |t[1]| through
|t[4]| are common between the best gain sequence and the current changes.
So to ensure that the best sequence is a 
prefix of the latest deep search, we need only check that |best_exit_a| and
|best_exit_b| equal |t[5]| and |t[6]|, respectively.

@<If necessary, implement an improving 3-change or clean up@>=
if ( more_backtracking ) {
	if ( best_gain > 0 && scheme_num_cities[best_scheme_id] == 6 ) {
		if ( best_exit_a == t[5] && best_exit_b == t[6] ) {
			@<Unroll all the generic changes.@>@;
		} else {
			@<Unroll all the changes@>@;
			t[5] = best_exit_a; t[6] = best_exit_b;
			scheme_id = best_scheme_id;
			@<Implement |scheme_id|@>@;
		}
		@<Mark changed cities as dirty@>@;
		@<Verbose: report improving 3-change@>@;
		more_backtracking = 0;
	} else {
		@<Unroll all the changes@>@;
	}
}

@ This code will be used in a couple of places, so it's generalized.
The |scheme| table encodes all the hard work I did to figure out the 
appropriate moves.  So we end up with just a simple loop.

@<Implement |scheme_id|@>=
{@+int i, n=scheme_max[scheme_id], *s = &scheme[scheme_id][0];
@<Verbose: announce implement scheme@>@;
	for (i=0 ; i<n ; i+= 4) {
		tour_flip_arb(t[s[i]],t[s[i+1]],t[s[i+2]],t[s[i+3]]);
	}
}

@ The generic tour flipping routine |tour_flip(a,b,c,d)| requires that certain
orientation conditions hold, namely 
|a == tour_next(b)| and |d==tour_next(c)|.  This isn't always convenient.
So I've defined the following procedure to allow either that
condition or the condition 
|a == tour_prev(b)| and |d==tour_prev(c)|.

@<Module subroutines@>=
static void tour_flip_arb(int a, int b, int c, int d);
static void
tour_flip_arb(int a, int b, int c, int d) {
	@<Verbose: announce |tour_flip_arb(a,b,c,d)|@>@;
	if ( b==d || a==c) return; /* This is a no-op. */
	if ( a == tour_next(b) && d == tour_next(c) ) {
		tour_flip(a,b,c,d);
		@<Verbose: flip case a@>@;
	} else if ( a == tour_prev(b) && d == tour_prev(c) ) {
		tour_flip(b,a,d,c);
		@<Verbose: flip case b@>@;
	} else {
		printf("\nNeighbour conditions not met\n");
		@<Debug: print the tour@>@;
		printf("\t(%d) %d (%d)",tour_prev(a),a,tour_next(a));
		printf("\t(%d) %d (%d)",tour_prev(b),b,tour_next(b));
		printf("\t(%d) %d (%d)",tour_prev(c),c,tour_next(c));
		printf("\t(%d) %d (%d)",tour_prev(d),d,tour_next(d));
		printf("\n");
		errorif(1,"Neighbour conditions not met.");
	}
}

@*Searching at level 2.
While we're in the groove of taking care of all these special cases, let's
finish up the 4-changes.

The legal 4-changes have an interesting special structure.  
It turns out that there the choice of segment that |t[7]| is allowed
to belong to depends on the first six cities.
The required conditions are as follows:
\emphpar{%
Base scheme 2: |tour_inorder(t[1],t[2],t[7],t[3])|\hfil\break
Base scheme 5: |tour_inorder(t[6],t[5],t[7],t[4])|\hfil\break
Base scheme 9: |tour_inorder(t[1],t[2],t[7],t[5])|
}

However, as usual, the first thing we do is the ``stupid'' check, \ie, make
sure we don't double back on ourselves.

In all cases, |t[8]| may be either neighbour of |t[7]|, subject to 
tabu and 1-tree conditions, of course.

@<Fill |e[BL][enbl]| for valid |t2ip2|'s and maybe update |best_gain|@>=
#if BL==2
if ( t2ip1 != t[5] ) {
	int i1, i2, i4;
	switch( base_scheme[7] = e[1][ec[1]].scheme_id ) {
	case 2: i1=1; i2=2; i4=3; break;
	case 5: i1=6, i2=5, i4=4; break;
	case 9: i1=1, i2=2, i4=5; break;
	default: errorif(1,"Got to 4-change in base scheme %d", base_scheme[7]); 
		i1=i2=i4=-1;	/* Satisfy GCC's dataflow warnings. */
		break;
	}
	if ( tour_inorder(t[i1],t[i2],t2ip1,t[i4]) ) {
		@<Try both neighbours of |t2ip1|@>@;
	}
}
#endif


@ Here we must check the tabu condition: that |(t[7],t[8])| hasn't previously
been added.
That is, the move is tabu if
\emphpar{%
|(t[7] == t[6] && t[8] == t[7]) || (t[7] == t[7] && t[8] == t[6])|\hfil\break
|||(t[7] == t[4] && t[8] == t[5]) || (t[7] == t[5] && t[8] == t[4])|\hfil\break
|||(t[7] == t[2] && t[8] == t[3]) || (t[7] == t[3] && t[8] == t[2])|.}

As before, 
|t[7]==t[7]| is redundant, and
the test |(t[7] == t[6] && t[8] == t[7])| always fails because 
|t[7]| is always chosen to be different from |t[6]|.
So we can skip that disjunct altogther.

The final tabu condition becomes
\emphpar{%
|(t[8] == t[6])|\hfil\break
|||(t[7] == t[4] && t[8] == t[5]) || (t[7] == t[5] && t[8] == t[4])|\hfil\break
|||(t[7] == t[2] && t[8] == t[3]) || (t[7] == t[3] && t[8] == t[2])|.}

Once we have eliminated tabu moves, we start refining our knowledge of the
scheme.  This knowledge is used when we actually implement the specified
4-change.  This is the deepest level of backtracking, so it will also
be the last level of refinement of the scheme.  That is, our scheme
determinations here are final.

If there was a problem involving only cities |t[1]| through |t[6]|, 
then we've already dealt with them earlier.  The only checking done
involves either |t[7]| or |t[8]| or both.

To see that these tests are unambiguous and complete, one has to do 
a bit of work.  That is, not all the details are shown here.  The best
way to derive these constraints is to doodle with small circles with labelled
vertices, and make some deductions.  That's what are in my notes.


But before you go off and do all that tricky and tedious work, you should
know that 
the guiding principle is that |(t[7],t[8])| must never be on of the
previously removed edges.

%Scheme 9 requires |8!=1|, but this is part of the feasibility check, so
%we don't have to waste time here to do it.  We
%make that the first pair to be tested in the feasibility entry for scheme 9.
%
% Actually, this is moot because 8!=1  scheme 9 only occurs when 1287,
% and this is incompatible with (1,2)==(8,7).

@<Update |best_gain| and |e[BL]| if not tabu@>=
#if BL==2
if ( !( 
	(t2ip2 == t[6]) 
	||(t2ip1 == t[4] && t2ip2 == t[5]) 
	||(t2ip1 == t[5] && t2ip2 == t[4]) 
	||(t2ip1 == t[2] && t2ip2 == t[3]) 
	||(t2ip1 == t[3] && t2ip2 == t[2]) )) {
	int infeasible_4_change, is_illegal = 0;
	switch( base_scheme[7] ) {
	case 2: 
		if ( tour_inorder(t[1],t[2],t2ip1,t2ip2) ) {
			base_scheme[8] = 2;	/* Case 1.2.1 */
			is_illegal = t2ip2 == t[4] || t2ip2 == t[1];
		} else {
			base_scheme[8] = 3; 
			/* Ok here because we know 1273, and |8!=1| because that would be
				included in the 1278 case, \ie, scheme 2. */
		}
		break;
	case 5: 
		if ( tour_inorder(t[1],t[2],t2ip2,t2ip1) ) {
			base_scheme[8] = 5;
			/* We know |7!=5| by stupid check, and |6574| by construction;
			together, this means |8!=6|.  Now, |1287|, so |8!=3|. */
		} else {
			base_scheme[8] = 6; 
			is_illegal = t2ip2 == t[3];
			/* |6574| by construction, so |7!=2|; together with |!1287&&1265|,
			means |8!=6|.  The only danger lies in |(7,8)==(4,3)|. */
		}
		break;
	case 9:	/* |!1234&&!1254&&!4365| */
		if ( tour_inorder(t[1],t[2],t2ip1,t[4]) ) {	/* |1274| */
			if ( tour_inorder(t[1],t[2],t2ip2,t2ip1) ) { /* |1287| */
				base_scheme[8] = 9;
				/* First, |!1234| implies |4!=1|; together with |1274| and 
					|1287| implies |8!=1|. 
					Second, |!1234| implies |4!=1&&3!=2|; together with
					|1274| and |1287|, this shows |8!=3|.  So both
					possibilities are eliminated. */
			} else {	/* |!1287|, so |1278 && 2!=8 && 8!=7 && 7!=1| */
				base_scheme[8] = 10; 
				is_illegal = t2ip2 == t[3];
				/* |7==4| possible, so need to exclude |8==3|.
				We can tell that |8!=1| because 8 is at most 3, but 
				then edge |(5,6)| intervenes before we get to 1. */
			}
		} else {	/* |!1274| */
				/* Knowing |1275| by construction, and |!1274|, and the
				fact that |1| is shielded from |7| by |6|, and |2| is 
				shielded from |7| by |4|, we can conlude that |7| is 
				restricted to the 3--5 segment.   */
			if ( tour_inorder(t[1],t[2],t2ip1,t2ip2) ) {
				base_scheme[8] = 11;
				is_illegal = t2ip2 == t[6];
				/* Because |7| is restricted to the 3--5 segment, and |1278|,
				|8==6| is the only danger. */
			} else {
				base_scheme[8] = 12;
				is_illegal = t2ip2 == t[4];
				/* Because |7| is restricted to the 3--5 segment, and |1278|,
				|8==4| is the only danger. */
			}
		}
		break;
	default: errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
	}
	if ( !is_illegal ) {
		@<Define |infeasible_4_change|@>@;
		if ( !infeasible_4_change ) {
			@<Update |best_gain| and |e[BL]|.@>@;
		}
	}
}
#endif

@ The possible values of |base_scheme[8]| coming into this section
are precisely those that involve cities |t[7]| and |t[8]|, namely 2, 3, 5, 6,
9, 10, 11, and 12.

@<Define |infeasible_4_change|@>=
{@+ int i, *sc, sn;
t[7] = t2ip1;
t[8] = t2ip2;
infeasible_4_change = 0;
sc = &scheme_feas_check[base_scheme[8]][0];
sn = scheme_feas_n[base_scheme[8]];
for ( i=0; i<sn ; i+=2 ) {
	if ( t[sc[i]] == t[sc[i+1]] ) { infeasible_4_change = 1; break; }
}
}

@ But we need to fill in the tables that the above code uses.  Refer  to
the table listed earlier.  These should always be kept in synch with
the |scheme| array.

@<Module variables@>=
static int scheme_feas_check[14][10] = {
{-1},	/* Scheme 0; not used */
{-1},	/* Scheme 1; not used */
{1,3,3,6,2,6,1,8,2,8},	/* Scheme 2 */
{3,8,1,8,3,6},	/* Scheme 3 */
{-1},	/* Scheme 4; not used */
{1,4,4,6,1,5,4,8},	/* Scheme 5 */
{1,4,5,8,1,8},	/* Scheme 6 */
{-1},	/* Scheme 7; not used */
{-1},	/* Scheme 8; not used */
{1,8,3,8,5,8},	/* Scheme 9 */
{1,7,1,5,2,8,2,5,1,8},	/* Scheme 10 */
{1,8,3,6,3,8},	/* Scheme 11 */
{5,8,2,5,1,8},	/* Scheme 12 */
{-1}	/* Scheme 13; not used */
};

static int scheme_feas_n[14] = {0,0,10,6,0,8,6,0,0,6,10,6,6,0};

@ By the time we get here, {\it every\/} 4-change completes 
the Hamiltonian cycle as if by magic.  Actually, it's really 
by design and hard work.

@<Update |best_gain| and set scheme@>=
#if BL==2
	e[BL][enbl].scheme_id = base_scheme[8];
	@<Set |best_gain| if this move is better@>@;
#endif

@ Now we're ready for the backtracking code for level 2, which is a 
loop over the possible candidates as before.

When we get here, every combination of six cities at the start of the
|t| array, together with |t2ip1| and |t2ip2| forms a legal 4-change.  
However, they haven't yet been implemented, though they have been
checked for 
feasibility.  
So we implement the 4-change, 
and then perform the greedy portion of the search.

@<Backtrack at level 2@>=
for (ec[2] = 0; more_backtracking && ec[2] < en[2] ; ec[2]++ ) {
	eligible_t *this_move = &e[2][ec[2]];
	t[7] = this_move->t2ip1;
	t[8] = this_move->t2ip2;
#if !SPLIT_GAIN_VAR
	cum_gain = this_move->gain;
#else
	cum_gain_pos = this_move->gain_pos;
	cum_gain_neg = this_move->gain_neg;
#endif
	two_i = 8;
	@<Verbose: update |probe_depth|@>@;
	scheme_id = this_move->scheme_id;
	@<Implement |scheme_id|@>@;
	@<Perform the greedy search@>@;
	@<If necessary, implement an improving 4-change or clean up@>@;
}

@
As with improving 2-changes and 3-changes, we  check 
to see if we must implement an
improving 4-change at this level after a deeper search.  

Again we handle the special case of the best changes being a prefix
of the greedy search we just dropped out of.
Analogously, we need examine the values of only |t[7]| and |t[8]| to
check for this special case.

@<If necessary, implement an improving 4-change or clean up@>=
if ( more_backtracking ) {
	if ( best_gain > 0 && scheme_num_cities[best_scheme_id] == 8 ) {
		if ( best_exit_a == t[7] && best_exit_b == t[8] ) {
			@<Unroll all the generic changes.@>@;
		} else {
			@<Unroll all the changes@>@;
			t[7] = best_exit_a; t[8] = best_exit_b;
			scheme_id = best_scheme_id;
			@<Implement |scheme_id|@>@;
		}
		@<Mark changed cities as dirty@>@;
		@<Verbose: report improving 4-change@>@;
		more_backtracking = 0;
	} else {
		@<Unroll all the changes@>@;
	}
}

@*Greedy search.
Here's the inner loop of Lin-Kernighan, but without all that backtracking
baggage.  It repeatedly takes the move that has the best cumulative gain,
all the while updating and recording the best tour gain.

To keep our code and data
separate from the other backtracking levels, we define |BL| to be 3, the
next available number.   The scratch space in |e[BL]| and |en[BL]| is reused
during each iteration.

Once we reach here, the 2/3/4-change has been implemented.
So the
flips performed here are all of a regular form involving only |t[1]|,
|t[2i]|, |t[2i+1]|, and |t[2i+2]|.

@<Perform the greedy search@>=
{@+int go_deeper;
last_special_two_i = two_i;
generic_flips_made = 0; 
@<Prime the tabu structure@>@;
@<Verbose: announce start of generic search@>@;
for ( go_deeper = 1; go_deeper ; ) {
	@<Possibly limit the depth of the search@>@;
	@<Verbose: update |probe_depth|@>@;
	@<Make sure |t[two_i+2]| is valid@>@;
#define BL 3
	{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
	const length_t cluster_dist=decluster_d(t[1],t[two_i]);
#else
	const length_t cluster_dist=0;
#endif
	@<Update |best_gain| and compose a list of eligible moves@>@;
	}
#undef BL
	if ( en[3] > 0 ) {
		@<Go deeper@>@;
	} else {
		@<End the generic search@>@;
		go_deeper = 0;
	}
}
@<Empty the tabu structure@>@;
}

@ Some researchers have suggested speeding up the algorithm by
arbitrarily limiting the depth of the search.  I believe this
is unnatural, but I've implemented this hook.  

@<Possibly limit the depth of the search@>=
#if defined(JBMR_LIMIT_PROBE_DEPTH)
if ( generic_flips_made >= max_generic_flips ) {
	@<Verbose: hit the max generic flips@>@;
	@<End the generic search@>@;
	go_deeper=0; 
	break;
}
#endif

@ In several places I'll need to know the boundary between the special
changes required for the initial 2/3/4-change, and the general changes
of the greedy search.  Variable |last_special_two_i| records the position
of this boundary.

We also need to know when generic flips have been made.  
This knowledge is used when
we attempt to unroll them.  It's no additional work 
to {\it count} the number of generic moves, so this is what we do.
This is an interesting statistic in itself.

Variable |generic_flips_made| counts the number of generic flips made.
It is reset to zero on every entry to the generic search, and incremented
from then on.  It is also used to guard the code that unrolls the generic
flips.  However, we might not begin a generic search before we test whether
there is anything to unroll.  So we must initialize it when we declare it.

Each use of variable |last_special_two_i| is either nested 
within the greedy search
or is guarded by a test on variable |generic_flips_made|.  
So strictly speaking,
we don't need to initialize |last_special_two_i|.  
But the data flow analysis of GCC will
complain about this.  To keep it quiet, we initialize it anyway, but to
a ridiculously large number.

@<|jbmr_run| variables@>=
int last_special_two_i;
int generic_flips_made;

@
@<Per-iteration initialization@>=
last_special_two_i=INT_MAX;
generic_flips_made=0;




@  We pick |t[2i+2]| so that it is always possible to complete the
path to a cycle with this move.

@<Fill |e[BL][enbl]| for valid |t2ip2|'s and maybe update |best_gain|@>=
#if BL==3
	if ( t[two_i] == tour_prev(t[1]) ) t2ip2 = tour_next(t2ip1);
	else t2ip2 = tour_prev(t2ip1);
	@<Update |best_gain| and |e[BL]| if not tabu@>@;
#endif


@ This  first implementation 
 uses a loop to check the tabu condition.  This is a linear search 
through the |t| array.  Because we perform this for every pair of cities
appended to |t|, this results in quadratic behaviour overall.
We might consider doing something smarter,
like using a good dictionary implementation.  Now {\it there's\/} an idea!

On average, I expect this search to be small, because the 
number of cities involved in an average $\lambda$-change is something on
the order of 12 to 16.  (Johnson and McGeoch say that the average depth of a
$\lambda$-change is around 3 edges beyond the initial backtracking stages,
which themselves involve anywhere between at most 6 and 8 cities.  However,
Their inputs are mostly Euclidean inputs where the 
points are randomly chosen from a uniform distribution
over the unit square.)
However, both Lin and Kernighan, and JBMR report
initially having up to around a quarter of all the cities involved in 
the early stages.

Ok.  I've gone away and done some measurements.  The following numbers
are for instance \type{brd14051},
using the 20 nearest neighbours as candidates, and counting only those generic
searches which got at least one level deep.  The unit of depth is a single
city in the |t| list.
With an arbitrary insertion starting tour, there were 103627 non-trivial
generic probes,
minimum depth was 6, maximum was 4264, average was 30.0, and a standard 
deviation
of 56.2.  From a random starting tour, the numbers were
102875 non-trivial generic probe sequences, 
minimum 6 depth, maximum 13032 (surprise!), 
average 34.2, and standard deviation of 76.8.

I was surprised by how deep these probes were.
So the quadratic behaviour for large $N$ is actually a Very Bad Thing.   
So I {\it
will} end up using the dictionary after all.  But wait until my prototype
is finished.

On reflection, the big difference is that the average {\it search\/} might go
much deeper than the average committed {\it change}.  That's an important
difference, with important consequences for parallelization.  In particular,
the probing may disturb a much larger portion of the tour data structure 
(whatever that might be) than the changes we commit.

@ Of course, first we'll check the feasibility.

@<Update |best_gain| and |e[BL]| if not tabu@>=
#if BL==3
if ( t2ip2 != t[1] && t2ip2 != t[two_i] ) {	/* Feasibility check. */
	int is_tabu=0;
	@<Set |is_tabu| appropriately@>@;
	if ( !is_tabu ) {
		@<Update |best_gain| and |e[BL]|.@>@;
	}
}
#endif


@ This time around, the ``scheme'' system doesn't really apply.  
We'll mark that with a scheme number of 13.

@<Update |best_gain| and set scheme@>=
#if BL==3
e[BL][enbl].scheme_id = 13;
@<Set |best_gain| if this move is better@>@;
#endif

@ Now that we've composed a list of possible moves, we implement the one
that has the greatest cumulative gain.  

In all previous cases, we've
presorted the |e[BL]| array.  But we haven't done that here because we just
want to use the best move.  So we begin by doing a linear search for
the best move.  (A simple adversary argument shows that this
is optimal in the number of comparisons, to within one comparison.)

Once we've found our candidate, we implement its change.
@<Go deeper@>=
{ int i, best_i=-1; 
#if !SPLIT_GAIN_VAR
	length_t best_len=0;
#else
	length_t best_len_pos=0, best_len_neg=0;
#endif
@<Verbose: go deeper@>@;
	for ( i=0; i<en[3] ; i++ ) {
		if (
#if JBMR_DECLUSTER_IN_GREEDY
			e[3][i].cluster_dist +
#endif
#if !SPLIT_GAIN_VAR
			best_len < e[3][i].gain
#else
			best_len_pos + e[3][i].gain_neg < best_len_neg + e[3][i].gain_pos
#endif
           )
		{
			best_i = i;
#if !SPLIT_GAIN_VAR
			best_len = e[3][i].gain;
#else
			best_len_pos = e[3][i].gain_pos;	
			best_len_neg = e[3][i].gain_neg;	
#endif
		}
	}
	errorif(best_i==-1,"Shouldn't be going deeper.");
#if !SPLIT_GAIN_VAR
	cum_gain = best_len;
#else
	cum_gain_pos = best_len_pos;
	cum_gain_neg = best_len_neg;
#endif
	t[two_i+1] = e[3][best_i].t2ip1;
	t[two_i+2] = e[3][best_i].t2ip2;
	tour_flip_arb(t[1],t[two_i],t[two_i+1],t[two_i+2]);
	@<Add to the tabu structure@>@;
	two_i += 2;
	generic_flips_made++; 
	@<Verbose: announce generic flip made@>@;
}

@ This code handles the end of the generic search.  There are two cases
to consider.

In the first case, no improvement has been found along any point in the
search.  We should then unroll all the changes.

In the second case, we have found an improvement.  If this improvement
is generic, then we roll back to it.  Otherwise the improvement is an
initial 2/3/4-change, and it is handled after we exit from this generic
section.

@<End the generic search@>=
if ( best_gain == 0 ) {
	@<Unroll all the changes@>@;
} else if ( best_scheme_id == 13 ) {
	@<Revert to the best generic gain@>@;
}

@ If there is an improving move that ended generically, then this
code 
backs up (if necessary) and implements it.

@<Revert to the best generic gain@>=
{
	int low_j, best_is_prefix;
	errorif( best_gain <= 0, "Bad best_scheme_id == 13");
	best_is_prefix = t[best_two_i+1] == best_exit_a 
		&& t[best_two_i+2] == best_exit_b;
	low_j = best_two_i + (best_is_prefix ? 2 : 0);
	@<Unroll all the generic changes down to |low_j|@>@;
	if ( !best_is_prefix ) {
		tour_flip_arb(t[1],t[best_two_i],best_exit_a,best_exit_b);
	}
	@<Mark changed cities as dirty@>@;
	@<Verbose: report improving $\lambda$-change@>@;
	more_backtracking = 0;
}

@ There are a couple of odds and ends left.  The first is unrolling the
generic changes down to |low_j|.   Each unrolling flip has a nice symmetry
with the flip that implemented it.

@<Unroll all the generic changes down to |low_j|@>=
{@+ int j;
	errorif( low_j < last_special_two_i, "Generic broken! caught at unrolling time");
	for ( j=two_i ; j>low_j ; j-=2 ) {
		@<Verbose: generic rollback at |j|@>@;
		tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
	}
	generic_flips_made = (low_j - last_special_two_i) / 2;
	@<Verbose: announce generic flips remain after rollback@>@;
}

@ If generic changes have been made, then unrolling them 
just applies the previous section 
with |low_j == last_special_two_i|.  

@<Unroll all the generic changes.@>=
if ( generic_flips_made ) {
	int low_j = last_special_two_i;
	@<Unroll all the generic changes down to |low_j|@>@;
}

@ Unrolling all the changes is just unrolling the generic changes followed
by unrolling the scheme changes.

@<Unroll all the changes@>=
@<Unroll all the generic changes.@>@;
@<Unroll the scheme changes@>@;

@ The last piece is just unrolling the initial 2/3/4-change.  
We must use the |scheme[scheme_id]| array from right to left.  It's the
shoes and socks principle from group theory.

We have unrolling to do ony when a scheme has been implemented, \ie, 
when |scheme_id > -1|.  We must remember to mark these changes as undone,
by resetting |scheme_id| to |-1|.

@<Unroll the scheme changes@>=
if ( scheme_id >= 0 ) {
	int j, *s = scheme[scheme_id];
	@<Verbose: unroll scheme |scheme_id|@>@;
	for ( j=scheme_max[scheme_id]-4;j>=0;j-=4) {
		tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
	}
	scheme_id = -1;
	@<Verbose: report failure@>@;
}

@*Tabu rules.
In order to prevent the search from endlessly cycling, Lin and Kernighan
defined two tabu rules regarding edges:
\centrepar{Never delete an added edge.}
and
\centrepar{Never add a deleted edge.}
In fact, these rules guarantee that the generic portion of the search
will be at  most $n$ levels deep.

JBMR keep only the first condition, so I call it the JBMR tabu rule.
Using only this rule, the search is still at most only $n$ levels deep.


Meanwhile, in {\sl The complexity of the Lin-Kernighan heuristic for the
traveling salesman problem}, SIAM Journal on Computing, {\bf 21} 3, June 1992,
460--465, 
Papadimitriou proved that a 
simplification of the Lin-Kernighan
algorithm that used only the second tabu rule
solves a problem that is PLS-complete.  (For an introduction to 
PLS-completeness,
see the paper {\sl How easy is local search?} by Johnson,
Papadimitriou, and Yannakakis, JCSS, {\bf 37}, 1988, 79--100.)
Until at least November 1995 (source: Johnson and McGeoch, November 20, 1995 
INSERT BETTER REFERENCE),
there had been no reported experience using
this tabu rule only.    
I have come to call the second tabu rule the Papadimitriou tabu rule.  

Note that using the second tabu rule 
only allows us to go much deeper: up to $n(n-1)/2$
levels instead of only $n$.  But the price is PLS-completeness.  Is the price
worth paying?  Nobody knows---yet.  On the one hand, it appears to be
much less restrictive because one is allowed to go much deeper.  On the
other hand, the rule may be much faster to check.  Why?  Well, lookahead
forces us to check the JBMR rule for every candidate |t2ip2|  for each
choice of |t2ip1|, typically 10 checks or more per choice of |t2ip1|.  
Meanwhile,
the Papadimitriou rule may be checked as soon as a candidate for |t2ip1| is 
known, resulting in one edge to be checked per choice of |t2ip1|.  
%We'll see.

@ When considering data structures for this problem, it might help to  know
the context in which it will be used.  

In this  program, the usage pattern is as follows:\br
\def\q{\hbox{}\hskip3em\relax}
\noindent create table\br
repeat $\{$\br
\q repeat $\{$\br
\q\q repeat find\br
\q\q insert\br
\q$\}$\br
\q make empty\br
$\}$

Also, I expect that most of the find operations will result in a miss.
	

@  We can check the tabu condition in time that is linear in the
number of moves made so far.  There is no additional space overhead,
and the multiplicative constant is small.

The JBMR rule is ``Never delete an added edge''.  Added edges are of the
form $(t_{2k},t_{2k+1})$.

Papadimitriou's tabu rule is ``Never add a deleted edge''.   
How do I implement
that?  Hmmm.  I need to do that one step {\it earlier}, \ie\ as soon as 
|t2ip1| is chosen.

@<Set |is_tabu| appropriately@>=
#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for ( i=2, is_tabu = 0; i < two_i ; i+= 2 ) {
	if ( (t2ip1 == t[i] && t2ip2 == t[i+1]) 
		|| (t2ip1 == t[i+1] && t2ip2 == t[i]) ) {
		is_tabu = 1;
		break;
	}
}
}
#elif defined(TABU_Papadimitriou)
{ errorif(1,"TABU_Papadimitriou is not implemented yet"); }
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif /* |TABU_LINEAR| */

@ The linear check needs no setup or teardown.
@<Prime the tabu structure@>=

@
@<Add to the tabu structure@>=

@
@<Empty the tabu structure@>=

@ Another alternative for the tabu structure is a dictionary.  In this
case, we will be using a splay tree.  Splay trees have nice working
set properties (see Sleator and Tarjan), and worst case amortized
times of $O(\log n)$ per operation.  Besides, the code's already written.

We might consider implementing
a hash table instead.  On average, hash tables are supposedly faster.
But they are an implementation headache because we don't know the
size of the dictionary in advance, and so we would have to grow the hash
table as it filled up, reallocating space, and rehashing everything.  Ugh.

I will consider using the dictionaries supplied with LEDA, the Library of
Efficient Data Structures and Algorithms,
{\tt http://www.mpi-sb.mpg.de/LEDA/leda.html}.  But then I 
must use C++, and I don't know the allocation properties of LEDA.
In particular, I'm worried about its (lack of?) concurrency control.

@ The dictionary must be created first.  We will 
reuse the same dictionary for every generic probe.

@<|jbmr_run| variables@>=
#if defined(TABU_SPLAY)
dict_t *tabu = dict_create(cmp_pair,NULL);
#endif

@ The comparison function implements lexicographic ordering.

The tricky part is that 
 edge $(p,q)$ must be considered the same as edge $(q,p)$.  We enforce
this by making the first coordinate at least as large as the second coordinate.

For correctness, I should not break ties by doing a pointer comparison as
I have optionally done in other places.  That would break this code because
I want to be able to find an edge in the dictionary without knowing where
it is stored.  After all, that's the whole point of the splay tabu structure.

@<Module subroutines@>=
#if defined(TABU_SPLAY)
static int cmp_pair(const void *a, const void *b);
static int 
cmp_pair(const void *a, const void *b) {
	int a1 =  *((const int *)a), a2 = *(((const int *)a)+1);
	int b1 =  *((const int *)b), b2 = *(((const int *)b)+1);
	if ( a1 < a2 ) { int t = a1; a1 = a2; a2 = t; }
	if ( b1 < b2 ) { int t = b1; b1 = b2; b2 = t; }
    return a1==b1 ? a2-b2 : a1-b1;
}
#endif


@ The proposed edge to be deleted is |(t2ip1,t2ip2)|.  We'll save some
branches in the comparison function if we order this edge appropriately
here.

@<Set |is_tabu| appropriately@>=
#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{ int edge[2];
	if ( t2ip1 < t2ip2 ) {edge[0] = t2ip2; edge[1] = t2ip1;}
	else {edge[0] = t2ip1; edge[1] = t2ip2;}
	is_tabu = dict_find(tabu,edge) != NULL;
}
#endif

@ This section initializes the tabu structure with the edges added in the
backtracking stage, \ie\ the scheme changes.  We only use the |t| array
here and ignore the implementation we actually used to get to this point.
This is faster (because there are fewer added edges in the |t| array
than in the scheme implementation sequence), simpler, and less skewed
toward the particular implementations of schemes that we have chosen.

The added edges are |(t[2],t[3])|, |(t[4],t[5])|, \etc.

@<Prime the tabu structure@>=
#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{
	int i;
	for ( i=2; i<two_i ; i+= 2 ) dict_insert(tabu,t+i);
}
#endif

@
@<Add to the tabu structure@>=
#if defined(TABU_SPLAY) && defined(TABU_JBMR)
	dict_insert(tabu,t+two_i);
#endif

@  Emptying the splay tree is the same job in both the JBMR and Papadimitriou
cases.  We don't want to do anything at the nodes, so we pass |NULL| as the
procedure.

@<Empty the tabu structure@>=
#if defined(TABU_SPLAY)
	dict_delete_all(tabu,NULL);
#endif

@ The only thorn in the side of things is that if we ever move the 
|t| array during reallocation, then we must move each of the pointers in
the tree.   We do this by subtracting the value |old_t| and adding the value
|t| to each dictionary entry payload pointer, but only after
it has been 
cast from |void *| to |int *|.

We use a special dictionary operation for this job, |dict_update_all|.
One of its parameters is a pointer to a procedure to update the 
contents of the dictionary entry in place.  But this updating
procedure must know how to modify the pointer, in this case it must know
the values of |t| and |old_t|, which are local to this |jbmr_run| and should
not be shared with other threads.  But the |\CEE| language does not
allow nested function definitions.  What are we to do?

It has been said that there isn't much in computer science that can't be
solved by another level of indirection.  The solution here is to
pass not only a pointer to the procedure, but a pointer to data that
should be passed to that procedure.  (It's simpler once you read the
code, honest.)  Another way of thinking about this is that we pass
the environment that should be passed to that procedure.  Implementors
of functional
programming languages will recognize this as a thunk with its environment.
Everything old is new again.  The best ideas are stolen, I mean, reused.

So this determines the interface to the |dict_update_all| procedure. 
Heck, I wrote the dictionary module, so I have complete freedom to add
this to its interface.  And yes, I was lazy and only added this procedure
only after I needed here.

@<|t| has moved from |old_t| to |t|@>=
#if defined(TABU_SPLAY)
{	int *env[2];	
	env[0] = old_t;
	env[1] = t;
	dict_update_all(tabu,move_t,env);
}
#endif

@ Here's the procedure that actually does the moving.  Its first parameter
is the environment that it needs; its second parameter is a pointer to
the integer pointer (disguising as a |void| pointer) that it must change.

Now that I've written it, all I can say is, ``Egads!''.  
@<Module subroutines@>=
#if defined(TABU_SPLAY)
static void move_t(void *env,void **p);
static void
move_t(void *env,void **p) {
	int *old_t = ((int **)env)[0], *t = ((int **)env)[1];
	*p = (void *)( t + ((int *)(*p) - old_t));
}
#endif


@  Whenever we make an improvement, we check to see if we've passed
a milestone in terms of percentage above a lower bound.
Of course, this is conditional a upon the user specifying a lower bound
on the command line.  The value of the lower bound is stored in 
|lower_bound_value|, and its name is stored in |lower_bound_name|.

@<Check milestone@>=
#if JBMR_MAX_VERBOSE >= 25
if ( lower_bound_name && verbose >= 25 ) {
	double this_time=0;
	if ( incumbent_len <= milestone_value ) this_time=resource_user_tick();
	while ( incumbent_len <= milestone_value && milestone < num_milestones ) {
		printf("Milestone: %4.2f%% above %s after %.2f (+ %.2f) sec\n",
			milestone_percentage[milestone]*100, 
			lower_bound_name,
			this_time,
			this_time==milestone_time ? 0 : this_time-milestone_time );
		milestone_time=this_time;
		milestone++; 
		if ( milestone < num_milestones ) 
			milestone_value = lower_bound_value*(1+milestone_percentage[milestone]);
	}
	fflush(stdout);
}
#endif

@ 
@<|jbmr_run| variables@>=
const double milestone_percentage[] = 
{ .10,
.099, .098, .097, .096, .095, .094, .093, .092, .091, .090,
.089, .088, .087, .086, .085, .084, .083, .082, .081, .080,
.079, .078, .077, .076, .075, .074, .073, .072, .071, .070,
.069, .068, .067, .066, .065, .064, .063, .062, .061, .060,
.059, .058, .057, .056, .055, .054, .053, .052, .051, .050,
.049, .048, .047, .046, .045, .044, .043, .042, .041, .040,
.039, .038, .037, .036, .035, .034, .033, .032, .031, .030,
.029, .028, .027, .026, .025, .024, .023, .022, .021, .020,
.019, .018, .017, .016, .015, .014, .013, .012, .011, .010,
.009, .008, .007, .006, .005, .004, .003, .002, .001, .000 };
int milestone;
length_t milestone_value; 
const int num_milestones=sizeof(milestone_percentage)/sizeof(double);
double milestone_time;

@
@<One-shot initialize@>=
milestone=0;
milestone_value = lower_bound_value*(1+milestone_percentage[milestone]);
milestone_time=0.0;

@
@<Module headers@>=
#include "resource.h"


@ We show where we started from, percentage-wise.
@<Show initial milestone@>=
#if JBMR_MAX_VERBOSE >= 25
if ( lower_bound_name && verbose >= 25 && lower_bound_value > 1e-5 ) {
	printf("Initial milestone: %.1f%% above %s\n",
		100*(incumbent_len-lower_bound_value)/lower_bound_value, lower_bound_name );
	fflush(stdout);
}
#endif

@ We also show where we end up.
@<Show final milestone@>=
#if JBMR_MAX_VERBOSE >= 25
if ( lower_bound_name && verbose >= 25 && lower_bound_value > 1e-5 ) {
	printf("Final milestone: %.2f%% above %s\n",
		100*(incumbent_len-lower_bound_value)/lower_bound_value, lower_bound_name );
	fflush(stdout);
}
#endif


@*Debugging output.  
This is the debugging output I needed to remove all the bugs  
I removed.  And I sincerely hope that no bugs remain.

To reduce the size of the object code, set |JBMR_MAX_VERBOSE| to a smaller
number.   That compile-time definition controls how much of the debugging
output can be generated.

The \type{-v} or \type{--verbose} command-line options allow the user
to set variable |verbose| and therefore the amount of output generated,
subject to the limits placed by |JBMR_MAX_VERBOSE|.

@
@<Verbose: announce improvement by |best_gain|@>=
#if JBMR_MAX_VERBOSE >= 50
if ( verbose >= 50 ) {
	static double last_time=0.0;
	const double this_time=resource_user_tick();
	printf("=== improve by " length_t_spec " to "length_t_spec,
		length_t_pcast(best_gain),length_t_pcast(incumbent_len));
	printf("  after %.3f (+ %.3f) sec\n", this_time,this_time-last_time);
	last_time=this_time;
	fflush(stdout);
}
#endif


@
@<Verbose: report termination of LK phase@>=
#if JBMR_MAX_VERBOSE >= 20
if ( verbose >= 20 ) {
	const double lk_time = resource_user_tick();
	const double ds_time = resource_user_tick_from(begin_data_structures_mark);
	printf("LK phase ended with incumbent_len == " length_t_spec 
		" after %.3f sec for LK and %.3f sec for ds+LK\n", 
		length_t_pcast(incumbent_len), lk_time, ds_time);
	fflush(stdout);
}
#endif

@
@<Verbose: announce start of search at |*dirty|@>=
#if JBMR_MAX_VERBOSE >= 100
if ( verbose >= 100 ) {
	printf("Search for an improvement starting at city %d\n",*dirty);
	fflush(stdout);
#if defined(JBMR_WATCH_THIS_CITY)
	if ( *dirty ==  JBMR_WATCH_THIS_CITY ) { 
		old_verbose = verbose;
		old_verbose_is_set = 1; 
		verbose = 2000;
	} else if ( old_verbose_is_set ) {
		verbose = old_verbose; 
		old_verbose_is_set = 0;
	}
#endif
}
#endif

@
@<Module variables@>=
#if JBMR_MAX_VERBOSE >= 100 && defined(JBMR_WATCH_THIS_CITY)
static int old_verbose, old_verbose_is_set=0;
#endif


@
@<Verbose: announce generic flip made@>=
#if JBMR_MAX_VERBOSE >= 150
if ( verbose >= 150 ) {
	printf("Generic flips made: %d\n", generic_flips_made);
	fflush(stdout);
}
#endif

@
@<Verbose: announce generic flips remain after rollback@>=
#if JBMR_MAX_VERBOSE >= 150
if ( verbose >= 150 ) {
	printf("Generic flips remain after rollback: %d\n", generic_flips_made);
	fflush(stdout);
}
#endif


@
@<Verbose: announce start of generic search@>=
#if JBMR_MAX_VERBOSE >= 175
if ( verbose >= 175 ) {
	printf("Start generic search\n");
	fflush(stdout);
}
#endif


@
@<Verbose: output new |best_gain|@>=
#if JBMR_MAX_VERBOSE >= 200
if ( verbose >= 200 ) {
	@<Verbose: indent@>@;
	printf("best_gain = "length_t_spec" %d %d s%d\n",
		length_t_pcast(best_gain), best_exit_a, best_exit_b,best_scheme_id);
	fflush(stdout);
}
#endif

@
@<Verbose: announce implement scheme@>=
#if JBMR_MAX_VERBOSE >= 300
if ( verbose >= 300 ) {
	printf("Implement scheme %d\n",scheme_id);
	@<Verbose: show |t|@>@;
	fflush(stdout);
}
#endif

@
@<Verbose: unroll scheme |scheme_id|@>=
#if JBMR_MAX_VERBOSE >= 300
if ( verbose >= 300 ) {
	printf("Unrolling the scheme %d changes\n",scheme_id);
	@<Verbose: show |t|@>@;
	fflush(stdout);
}
#endif

@  Show |t| and its associated cumulative and tour gains.
@<Verbose: show |t|@>=
#if JBMR_MAX_VERBOSE >= 300
if ( verbose >= 300 ) {
	int i;
	length_t c=0, b=0;
	printf("t: ");
	for ( i=1;i<=two_i;i++) {
		if ( i%2 ) { /* is odd */
			if ( i>1 ) c -= cost(t[i],t[i-1]);
		} else { /* is even */
			c += cost(t[i],t[i-1]);
		}
		printf("%d ",t[i]);
	}
	b = c - cost(t[1],t[two_i]);
	printf(length_t_spec" ",length_t_pcast(c));
	printf(length_t_spec"\n",length_t_pcast(b));
	fflush(stdout);
}
#endif



@
@<Verbose: announce |tour_flip_arb(a,b,c,d)|@>=
#if JBMR_MAX_VERBOSE >= 350
if ( verbose >= 350 ) {
	printf("tour_flip_arb(%d,%d,%d,%d)",a,b,c,d);
	fflush(stdout);
}
#endif

@
@<Verbose: generic rollback at |j|@>=
#if JBMR_MAX_VERBOSE >= 350
if ( verbose >= 350 ) {
	printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
	fflush(stdout);
}
#endif

@
@<Verbose: flip case a@>=
#if JBMR_MAX_VERBOSE >= 350
if ( verbose >= 350 ) {
	printf(" case a\n");
	fflush(stdout);
}
#endif

@
@<Verbose: flip case b@>=
#if JBMR_MAX_VERBOSE >= 350
if ( verbose >= 350 ) {
	printf(" case b\n");
	fflush(stdout);
}
#endif

@ Here, |t[two_i]| is the last thing added.
@<Verbose: show current position@>=
#if JBMR_MAX_VERBOSE >= 400
if ( verbose >= 400 ) {
	@<Verbose: indent@>@;
	printf("%d %d "length_t_spec" "length_t_spec" s%d\n", t[two_i-1], t[two_i],
#if !SPLIT_GAIN_VAR
		length_t_pcast(cum_gain), 
#else
		length_t_pcast(cum_gain_pos-cum_gain_neg), 
#endif
		length_t_pcast(best_gain), scheme_id );
	fflush(stdout);
}
#endif



@
@<Module subroutines@>=
#if JBMR_MAX_VERBOSE >= 300
#if !SPLIT_GAIN_VAR
#define put_city(X) \
if ( verbose >= 300 ) { \
	int i;\
	length_t cg = cum_gain, bg = best_gain; \
	for ( i=0;i<(X);i++) {printf(" ");}\
	printf("t%d == %d p=%d n=%d",(X),t[(X)],tour_prev(t[(X)]),tour_next(t[(X)]));\
	if (X>1) { \
		int c = cost(t[(X)-1],t[X]); \
		printf(" c(t%d,t%d)=%d",(X)-1,(X),c); \
		c = cost(t[(X)],t[1]); \ 
		printf(" c(t%d,t1)=%d",(X),c); \
	} \
	printf("\tcg "length_t_spec" bg "length_t_spec"\n",length_t_pcast(cg),\
		length_t_pcast(bg)); \
	fflush(stdout); \
}
#else
#define put_city(X) \
if ( verbose >= 300 ) { \
	int i;\
	length_t cg = cum_gain_pos-cum_gain_neg, bg = best_gain; \
	for ( i=0;i<(X);i++) {printf(" ");}\
	printf("t%d == %d p=%d n=%d",(X),t[(X)],tour_prev(t[(X)]),tour_next(t[(X)]));\
	if (X>1) { \
		int c = cost(t[(X)-1],t[X]); \
		printf(" c(t%d,t%d)=%d",(X)-1,(X),c); \
		c = cost(t[(X)],t[1]); \ 
		printf(" c(t%d,t1)=%d",(X),c); \
	} \
	printf("\tcg "length_t_spec" bg "length_t_spec"\n",length_t_pcast(cg),\
		length_t_pcast(bg)); \
	fflush(stdout); \
}
	
#endif
#else
#define put_city(X)
#endif

@
@<Verbose: output candidate pair@>=
#if JBMR_MAX_VERBOSE >= 500
if ( verbose >= 500 ) {
	@<Verbose: indent@>@;
#if !SPLIT_GAIN_VAR
	printf("%d: %d %d "length_t_spec" s%d\n",
		enbl,t2ip1,t2ip2,
		length_t_pcast(cum_2),
#else
	printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
		enbl,t2ip1,t2ip2,
		length_t_pcast(cum_2_pos),
		length_t_pcast(cum_2_neg),
		length_t_pcast(cum_2_pos-cum_2_neg),
#endif
		e[BL][enbl].scheme_id);
	fflush(stdout);
}
#endif

@
@<Verbose: cluster distance@>=
#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if ( verbose >= 501 ) {
	@<Verbose: indent@>@;
	printf(" v---- next clust_dist==%f\n", (double)cluster_dist);
}
#endif

@
@<Verbose: declustering rejects candidate pair@>=
#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if ( verbose >= 500 ) {
	@<Verbose: indent@>@;
	printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
		enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
		length_t_pcast(cum_2),
#else
		length_t_pcast(cum_2_pos-cum_2_neg),
#endif
		e[BL][enbl].scheme_id,
		num_reject_by_decluster,
		(double)cluster_dist);
	fflush(stdout);
}
#endif
#endif

@
@<|jbmr_run| variables@>=
int num_reject_by_decluster;


@
@<One-shot initialize@>=
num_reject_by_decluster=0;

@
@<Verbose: show terminating |cum_1|@>=
#if JBMR_MAX_VERBOSE >= 500
if ( verbose >= 500 ) {
	@<Verbose: indent@>@;
#if !SPLIT_GAIN_VAR
	printf("Terminating |cum_1| "length_t_spec"\n", length_t_pcast(cum_1));
#else
	printf("Terminating |cum_1| "length_t_spec" "
		"(== "length_t_spec" - " length_t_spec")\n",
		length_t_pcast(cum_1_pos-cum_1_neg),
		length_t_pcast(cum_1_pos),
		length_t_pcast(cum_1_neg) );
#endif
	fflush(stdout);
}
#endif

@ Show the candidate list.
@<Verbose: go deeper@>=
#if JBMR_MAX_VERBOSE >= 500
if ( verbose >= 500 ) {
	int i; 
	@<Verbose: indent@>@; printf("go deeper candidates begin\n");
	for ( i=0; i<en[3] ; i++ ) {
#if !SPLIT_GAIN_VAR
		@<Verbose: indent@> printf("%d %d "length_t_spec" s%d\n", 
			e[3][i].t2ip1, 
			e[3][i].t2ip2, 
			length_t_pcast(e[3][i].gain),
			e[3][i].scheme_id );
#else
		@<Verbose: indent@> printf("%d %d "length_t_spec" (=="length_t_spec"-"
			length_t_spec") s%d\n", 
			e[3][i].t2ip1, 
			e[3][i].t2ip2, 
			length_t_pcast(e[3][i].gain_pos-e[3][i].gain_neg), 
			length_t_pcast(e[3][i].gain_pos), 
			length_t_pcast(e[3][i].gain_neg), 
			e[3][i].scheme_id );
#endif
	}
	@<Verbose: indent@>@; printf("go deeper candidates end\n");
	fflush(stdout);
}
#endif

@
@<Verbose: show |base_scheme[5]|@>=
#if JBMR_MAX_VERBOSE >= 1000
if ( verbose >= 1000 ) {
	@<Verbose: indent@>@; printf("base_scheme5 == %d\n",base_scheme[5]);
	fflush(stdout);
}
#endif

@
@<Verbose: show |base_scheme[6]|@>=
#if JBMR_MAX_VERBOSE >= 1000
if ( verbose >= 1000 ) {
	@<Verbose: indent@>@; printf("base_scheme6 == %d\n",base_scheme[6]);
	fflush(stdout);
}
#endif


@ This one's only used by other verbose output sections.
@<Verbose: indent@>=
#if JBMR_MAX_VERBOSE
{ int i; for (i=0;i<two_i;i++) printf(" "); }
#endif

@ This is printed as debugging output when something fails.
@<Debug: print the tour@>=
{ int i, c,cn;
	printf("Tour: 0");
	for ( i=0, c=0; i<n ; i++ ) {
		errorif( c == 0 && i > 0, "Not a tour");
		cn = tour_next(c);
		printf(" %d",cn);
		c = cn;
		if ( i%20 == 19 ) printf("\n");
	}
	printf("\n");
	fflush(stdout);
	errorif( c != 0, "Not a tour");
}

@*Tracking probe depths.
@<Module definitions@>=
#if JBMR_MAX_VERBOSE||JBMR_REPORT_DEPTHS
#define TRACK_DEPTHS 1
#else
#define TRACK_DEPTHS 0
#endif

@
@<Verbose: report improving 2-change@>=
#if TRACK_DEPTHS
move_depth = 4;
@<Verbose: report move stats@>@;
#endif

@
@<Verbose: report improving 3-change@>=
#if TRACK_DEPTHS
move_depth = 6;
@<Verbose: report move stats@>@;
#endif

@
@<Verbose: report improving 4-change@>=
#if TRACK_DEPTHS
move_depth = 8;
@<Verbose: report move stats@>@;
#endif

@
@<Verbose: report improving $\lambda$-change@>=
#if TRACK_DEPTHS
move_depth = best_two_i+2;
@<Verbose: report move stats@>@;
#endif

@
@<Verbose: report failure@>=
#if TRACK_DEPTHS
move_depth = 0;
@<Verbose: report move stats@>@;
#endif

@
@<Verbose: update |probe_depth|@>=
#if TRACK_DEPTHS
if ( probe_depth < two_i+2 ) (probe_depth = two_i+2);
#endif


@
@<Initialize the bookkeeping variables@>=
#if TRACK_DEPTHS
probe_depth = move_depth = 0;
#endif

@
@<|jbmr_run| variables@>=
#if TRACK_DEPTHS
int probe_depth, move_depth;
#endif

@
@<Verbose: report move stats@>=
#if JBMR_MAX_VERBOSE >= 125
if ( verbose >= 125 ) {
	printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
	fflush(stdout);
	probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth=probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth = probe_depth = 0;
#endif


@
@<|jbmr_run| variables@>=
#if JBMR_MAX_VERBOSE >= 125
int probes = 0;
#endif

@
@d DEPTHS_BOUND (n+20)
@<Other setup code@>=
#if TRACK_DEPTHS && defined(TABU_JBMR)
p_depths = new_arr_of(int,DEPTHS_BOUND);
m_depths = new_arr_of(int,DEPTHS_BOUND);
{int i; for (i=0;i<DEPTHS_BOUND;i++) p_depths[i]=m_depths[i]=0;}
#endif


@
@<Other cleanup code@>=
#if TRACK_DEPTHS
free_mem(p_depths);
free_mem(m_depths);
#endif

@
@<Module variables@>=
#if TRACK_DEPTHS
static int *p_depths=NULL, *m_depths=NULL;
#endif

@
@<Verbose: report depths@>=
#if TRACK_DEPTHS
{ int i,j;
	for (i=DEPTHS_BOUND-1;p_depths[i]!=0;i--);
	for (j=0;j<=i;j++) {
		if ( p_depths[j] ) printf("p %d citydeep %d\n",j,p_depths[j]);
	}
	for (i=DEPTHS_BOUND-1;m_depths[i]!=0;i--);
	for (j=0;j<=i;j++) {
		if ( m_depths[j] ) printf("m %d citydeep %d\n",j,m_depths[j]);
	}
}
#endif


@
@<Verbose: print statistics@>=
@<Verbose: report depths@>@;
printf("Statistics: num_reject_by_cum_1 %d\n",num_reject_by_cum_1);
printf("Statistics: num_reject_pre_e_build %d\n",num_reject_pre_e_build);
printf("Statistics: num_reject_by_decluster %d\n",num_reject_by_decluster);


@
@<Verbose: new |(t1,t2)|@>=
#if JBMR_MAX_VERBOSE >= 70
if ( verbose>=70 ) {
printf("(t1,t2)= (%d,%d) cost=%f, d=%f p=%d\n",t[1],t[2],(double)cost(t[1],t[2]),
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
	(double)decluster_d(t[1],t[2]) 
#else
	(double)-1 /* Don't cause a seg fault. */
#endif
, last_probe_depth);
}
#endif

@
@<|jbmr_run| variables@>=
#if TRACK_DEPTHS
int last_probe_depth=0;
#endif


@
@<Verbose: hit the max generic flips@>=
#if JBMR_MAX_VERBOSE >= 75
if ( verbose>=75 ) {
	printf(" hit max generic flips: %d >= %d\n",
		generic_flips_made,max_generic_flips);
}
#endif

@*Iterated Lin-Kernighan.
Given a LK-optimal tour, one might try to find a better tour by
perturbing it a little and then running LK on it again.  That's the idea
behind Iterated Lin-Kernighan.

Of course, sometimes the tour we find after the perturbation is worse than
we we started with.  So we need to be able to revert to what we started with.
We use the |change_log|, but in reverse order.

In either case reset the change log index to zero.

@<Revert to the previous solution if it was better@>=
if ( iteration > 0 && change_log_next > 0 && previous_incumbent_len < incumbent_len ) {
	@<Verbose: announce reverting to previous@>@;
	while ( change_log_next > 0 ) {
		@<Undo a $\lambda$-change@>@;
		change_log_next -= change_log[change_log_next-1]+1;
	}
	errorif(change_log_next!=0,"Bug!");
	@<Undo the mutation@>@;
	incumbent_len = previous_incumbent_len;
}
change_log_next = 0;

@ 
@<|jbmr_run| variables@>=
length_t previous_incumbent_len=0;

@ As described earlier, the $lambda$-change is encoded by 
|t[1]| through |t[best_two_i]|, then |best_exit_a|, |best_exit_b|,
|scheme_id|,
and finally |best_two_i+3|.

We need the length value last because we are decoding the $lambda$-change 
it from the end down toward the beginning.  We need the scheme id because
we can't blindly unwind just from the |t| array since some of the
early moves would destroy the tour.

In the following code, |first_pos| is the position where |t[1]| is stored;
|first_generic_pos| is the position of the first city recorded as part
of the generic search, it therefore marks the transition from the 
scheme flips and the generic flips.
In the generic flips, value |j| marks the $c$ city in the 
|tour_flip_arb(a,b,c,d)| move that we're trying to undo (with a 
|tour_flip_arb(a,d,c,b)|.

For undoing the scheme changes, |st| acts just like the |t| array did
when doing the scheme changes, |s| is the scheme change script that we
read backwards, and |si| is the index that runs through the script.

@<Undo a $\lambda$-change@>=
{
const int len=change_log[change_log_next-1], 
		revert_scheme_id = change_log[change_log_next-2],
		first_pos=change_log_next-1-len,
		first_generic_pos=first_pos + scheme_num_cities[revert_scheme_id],
		t1=change_log[first_pos], *st=(&change_log[first_pos])-1;
int j,si,*s=&scheme[revert_scheme_id][0];
@<Verbose: announce undoing a segment of change log@>@;
errorif(first_pos<0,"Bug!");
for ( j=change_log_next-4; j >= first_generic_pos ; j-=2 ) { /* Undo generic changes. */
	tour_flip_arb(t1,change_log[j+1],change_log[j],change_log[j-1]);
}
for (si=scheme_max[revert_scheme_id]-4 ; si>=0 ; si-= 4) { /* Undo the scheme changes. */
	tour_flip_arb(st[s[si]],st[s[si+3]],st[s[si+2]],st[s[si+1]]);
}
}

@ If we are going to go through another round of LK-optimization, we 
store the current tour length in 
|previous_incumbent_len| and then perform a double-bridge perturbation.


@<If doing another iteration, perturb with a double-bridge@>=
if ( iteration < iterations-1 ) {
	int edge[4][2];
	previous_incumbent_len = incumbent_len;
	@<Put four distinct oriented edges into |edge|@>@;
	@<Sort the bridge edges@>@;
	@<Perform the double-bridge mutation using |edge|@>@;
}
@<Verbose: announce new (probably higher) incumbent length@>@;



@
@<Put four distinct oriented edges into |edge|@>=
{
int ok, count=0;
do {
	int i,j;
	errorif(count++>1000,"Ummm, random double-bridge search didn't stop after 1000 tries");
	for (i=0,ok=1;ok && i<4;i++) { 
		edge[i][0]=prng_unif_int(random_stream,(long)n);
		edge[i][1]=tour_next(edge[i][0]);
		for (j=0; ok && j<i ;j++) { /* Check for uniqueness. */
			if ( edge[j][0] == edge[i][0] ) ok=0;
		}
	}
} while(!ok);
}

@
@<Put four distinct oriented edges into |edge|@>=
#if JBMR_MAX_VERBOSE >= 60
if ( verbose >= 60 ) {
int i;
printf("Doing double-bridge: ");
for (i=0;i<4;i++) printf("%d(%d,%d) ",i,edge[i][0],edge[i][1]);
printf("\n");
}
#endif

@ We take |edge[0]| as the reference edge, and sort the other three
manually.  It's bubblesort, folks. (Or rather bubblesort's opposite, rocksort.)

@d swap_bridge(a,b) {int temp=a[0];a[0]=b[0];b[0]=temp;temp=a[1];a[1]=b[1];b[1]=temp;}
@d bridge_less(a,b) (tour_inorder(edge[0][0],edge[0][1],a[0],b[0]))


@<Sort the bridge edges@>=
{int bottom,rock;
for (bottom=3;bottom>1;bottom--) {
	for(rock=1;rock<bottom;rock++) {
		if ( bridge_less(edge[rock],edge[rock+1]) )  {
			swap_bridge(edge[rock],edge[rock+1]);
		}
	}
}
}


@ Only three flips are required to perform
the double-bridge move.  A little pencil and paper shows that the following
sequence works.

@d bridge_t(X) (edge[(X-1)>>1][(X-1)&1])
@d bridge_move(a,b,c,d) (tour_flip_arb(bridge_t(a),bridge_t(b),bridge_t(c),bridge_t(d)))

@<Perform the double-bridge mutation using |edge|@>=
bridge_move(1,2,6,5);
bridge_move(8,7,4,3);
bridge_move(1,5,2,6);

@ Here's a tricky part.  We also have to record the perturbation and undo
it when reverting to the previous iteration's tour.

@d mutate(a) (mutation[mutation_next++]=bridge_t(a))

@<Perform the double-bridge mutation using |edge|@>=
{ int mutation_next=0;
mutate(1);
mutate(2);
mutate(6);
mutate(5);

mutate(8);
mutate(7);
mutate(4);
mutate(3);

mutate(1);
mutate(5);
mutate(2);
mutate(6);
}

@ We also need to reflect the mutation in the incumbent length.

There is some redundancy here that I should probably get rid of.


@<Perform the double-bridge mutation using |edge|@>=
#if JBMR_MAX_VERBOSE >= 60
#define bc(a,b) (<@Verbose: print double bridge edge |(a,b)|@>,
			cost(bridge_t(a),bridge_t(b)))
#else
#define bc(a,b) (cost(bridge_t(a),bridge_t(b)))
#endif

incumbent_len += bc(1,6);
incumbent_len += bc(2,5);
incumbent_len += bc(4,7);
incumbent_len += bc(3,8);
incumbent_len -= bc(1,2);
incumbent_len -= bc(3,4);
incumbent_len -= bc(5,6);
incumbent_len -= bc(7,8);
	
@
@<Verbose: print double bridge edge |(a,b)|@>=
(verbose >= 60 
	? printf("cost(%d,%d)="length_t_spec"\n",
		bridge_t(a),bridge_t(b),length_t_pcast(cost(bridge_t(a),bridge_t(b))))
	: 0
)

@ We also mark as dirty the cities involved in the mutation.
@<Perform the double-bridge mutation using |edge|@>=
{int i;
for (i=1;i<=8;i++)
	mark_dirty(bridge_t(i));
}


@
@<|jbmr_run| variables@>=
int mutation[12];

@ 
@<Undo the mutation@>=
{ int i;
for (i=8;i>=0;i-=4)
	tour_flip_arb(mutation[i],mutation[i+3],mutation[i+2],mutation[i+1]);
}

@
@<Verbose: report end of LK step@>=
#if JBMR_MAX_VERBOSE >= 40
if ( verbose>=40 ) {
	printf("End of LK step %d, incumbent_len = "length_t_spec"\n",
		iteration + 1,
		length_t_pcast(incumbent_len));
}
#endif

@
@<Verbose: announce new (probably higher) incumbent length@>=
#if JBMR_MAX_VERBOSE >= 60
if (verbose>=60){
printf("+++incumbent_len is now "length_t_spec"\n",length_t_pcast(incumbent_len));
}
#endif


@
@<Verbose: announce reverting to previous@>=
#if JBMR_MAX_VERBOSE >= 57
if (verbose>=57) {
printf("Reverting to previous\n");
}
#endif

@
@<Verbose: announce undoing a segment of change log@>=
#if JBMR_MAX_VERBOSE >= 65
if ( verbose >= 65 ) {
printf("  first_pos = %d change_log_next = %d\n",first_pos,change_log_next);
}
#endif

@*Index.
