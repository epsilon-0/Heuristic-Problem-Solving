


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
$Log: lk.w,v $
Revision 1.251  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.250  1998/06/19 16:39:17  neto
Check that the upper bound is given when computing held karp lower bounds.
Of course, I could always compute it on the fly....

Revision 1.249  1998/05/29 21:01:10  neto
Off by a factor of 100 in calculation of percentage for Held Karp.

Revision 1.248  1998/05/23 18:23:32  neto
Doh.  Was discarding the held karp bound. Fixed. I hope

Revision 1.247  1998/05/23 18:09:57  neto
Needed casts around length t stuff in held karp bounds.

Revision 1.246  1998/05/23 17:31:25  neto
This now compiles to .o.
(The cleanup function needs access to do weighted perfect matching.
But it doesn't handle held karp only...)

Revision 1.245  1998/05/23 16:22:53  neto
Added proper setup of held-karp lower bound.
Added options for upper bound.  Change -b to -l, a lower bound.
Added options for held karp computations.

Revision 1.244  1998/05/21 15:46:08  neto
New interface to match run

Revision 1.243  1998/04/10 15:13:31  neto
Made safe for non-E2 instances

Revision 1.242  1998/02/21 04:05:19  neto
Added support for Iterated LK (for TSP).
Also fixed some output stuff for matching.

Revision 1.241  1998/01/23  21:04:55  neto
Now it compiles well with match module.
Fixed some printing minor errors.

Revision 1.240  1997/12/20 20:44:12  neto
Changed variable "start tour" to "construction algorithm".
It's more descriptive and more accurate.

Revision 1.239  1997/12/20 20:31:25  neto
Import the matching header.
Fix raw lengths if CEIL 2D.
Export comparison functions for double and length t.

Revision 1.238  1997/12/20 18:38:16  neto
Added first draft of support for doing minimum weighted perfect matchings.

Revision 1.237  1997/12/19  20:46:37  neto
Fixed the calls to decluster mst and preprocess: I was passing the
instance to the wrong procedure.

Revision 1.236  1997/12/13 21:31:04  neto
Ooops, I put it in the wrong place!

Revision 1.235  1997/12/13 21:28:15  neto
decluster mst now takes the tsp instance argument instead of relying on
a global variable.

Revision 1.234  1997/12/13 16:47:54  neto
Updated to new interface with error module.
Made all module names upper case.

Revision 1.233  1997/12/05  21:42:32  neto
It's Moore's curve, dodo.  :)

Revision 1.232  1997/11/14  22:53:44  neto
Output starting tour if verbose is high and postscript is on.

Revision 1.231  1997/10/18  18:09:11  neto
Convert to new protocol for nearest neighbours.

Revision 1.230  1997/10/18 14:47:50  neto
Now we use E2 supports() for more intelligent construction or non-construction
of 2-d trees.

Revision 1.229  1997/10/17  21:48:15  neto
Changed coord\_2d structure.

Revision 1.228  1997/10/17  21:01:11  neto
Added begin data structures mark.

Revision 1.227  1997/09/27 18:06:21  neto
Fixed RCS log behaviour.

Revision 1.226  1997/09/12  21:30:04  neto
Code wasn't included! This caused seg faults.  (This is a CWEB scripto-level
bug.  oops).

Revision 1.225  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.224  1997/08/15  16:59:29  neto
Print the MST to PostScript as well.

Revision 1.223  1997/08/15  16:19:19  neto
Added -m (--mst-edge-lengths-only) to print the edge lengths and quit

Revision 1.222  1997/08/14  20:19:46  neto
Added symbol BUILD DECLUSTER STRUCTURES to internal conditional compilation.

Revision 1.221  1997/06/19  19:41:34  neto
Be a little more friendly on initial tour length.

Revision 1.220  1997/06/17  21:45:20  neto
Put declustering configuration info in the version banner.

Revision 1.219  1997/06/17  21:32:47  neto
Must include declevel.h

Revision 1.218  1997/06/17  20:28:42  neto
Added support for milestones.
Made declustering stuff conditional.

Revision 1.217  1997/06/16  20:45:00  neto
I need to remember the mst space.

Revision 1.216  1997/06/16  20:24:52  neto
A first cut at doing declustering.

Revision 1.215  1997/06/16  17:35:12  neto
Cleaned up output (again).

Revision 1.214  1997/06/16  17:20:52  neto
Split the validation and print section.

Revision 1.213  1997/06/16  16:38:10  neto
I removed an extraneous print line (Edit bug).

Revision 1.212  1997/06/16  16:33:44  neto
Print no decimal points when no-round option is *not* used.
(i.e. the right thing)

Revision 1.211  1997/06/16  16:07:26  neto
Print length in double format when verbose < 10.

Revision 1.210  1997/06/13  22:12:45  neto
Fixed a spelling mistake.

Revision 1.209  1997/06/13  21:59:58  neto
Refine verbose levels for some output.

Revision 1.208  1997/06/13  21:49:29  neto
Make 5 the default verbose.
Some things that were printed at verbose level 2 now pushed up to 10.

Revision 1.207  1997/06/13  21:39:08  neto
Fixed comments.
Prettied up some TeX stuff.
Terminate columns of numbers in printing tour.
Make sure tour is printed if given -t option, no matter what verbose
setting is.

Revision 1.206  1997/06/13  21:16:06  neto
Fixed comment about main.
put starting braces of functions in column 1.
Updated a section name to reflect reality (report results in only
one place).

Revision 1.205  1997/06/13  21:01:59  neto
Fixed a variable name

Revision 1.204  1997/06/13  20:59:29  neto
Make verbose==1 output only the length of the tour.
Make verbose==2 the default, and it's quite quiet.

Revision 1.203  1997/06/13  20:32:09  neto
Don't print starting incumbent len if verbose==0

Revision 1.202  1997/06/13  20:28:08  neto
Removed flushes of stdout after resource mark calls.
Made checking kd tree quieter if verbose==0

Revision 1.201  1997/06/13  20:16:23  neto
Sorted, minor editing on help text.
Made it really quiet when verbose==0.

Revision 1.200  1997/06/13  19:49:27  neto
Made it a little quiter.

Revision 1.199  1997/06/13  18:44:11  neto
Fixed up the parens matching hack (for editors).

Revision 1.198  1997/06/13  18:17:30  neto
It's not Neto's curve, it's Moore's curve.
I've moved the origin to 6 o'clock instead of at the origin.  This
may help cache behaviour.
(Because the 0/1 boundary is at the edge of the square instead of
right in the middle.).

Revision 1.197  1997/05/16  21:15:06  neto
Now I don't need special behaviour for Linux regarding getpagesize.

Revision 1.196  1997/05/16  21:13:33  neto
Now I don't need special behaviour for Linux regarding gethostname.

Revision 1.195  1997/05/16  20:37:20  neto
Put in some support from configure.

Revision 1.194  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.193  1997/05/16  18:09:40  neto
Include <config.h> and lkconfig.h

Revision 1.192  1997/02/11  16:08:50  neto
Fixed parsing of start tour.

Revision 1.191  1997/02/10  19:32:36  neto
Added a grestore to close out postscript .

Revision 1.190  97/01/27  16:43:48  neto
Made lk cleanup prototype and definition match in storage class modifier.

Revision 1.189  97/01/27  16:41:02  neto
Better output of intermediate PostScript.

Revision 1.188  1997/01/21  22:30:17  david
Fixed an errorif call.

Revision 1.187  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.186  1997/01/21  17:48:24  david
Output the tour to the PostScript output stream, if open.

Revision 1.184  1997/01/21  17:23:46  david
Fixed printing out of start tour option, w.r.t. canonical.

Revision 1.183  1997/01/21  16:33:44  david
Added canonical back again.
Fixed error messages about sorting options.

Revision 1.182  1997/01/21  16:22:34  david
Make printing of SFC results optional.

Revision 1.180  1997/01/21  16:10:23  david
Fixed ordering and normalization in SFC comparison function.

Revision 1.179  1997/01/21  15:37:41  david
Fixed the rewrite rule and the comparison rule for SFC when a and
b compare as different.

Revision 1.177  1997/01/21  00:18:10  david
Fail if --maxdepth option given without proper compilation flag.

Revision 1.176  1997/01/20  23:49:31  david
Changed max\_probe\_depth to max\_generic\_flips

Revision 1.175  1997/01/20  19:50:46  david
Fixed setting probe depth.

Revision 1.174  1997/01/20  19:45:56  david
Fixed limit.h to limits.h

Revision 1.173  1997/01/20  19:44:31  david
Added a maxdepth option.

Revision 1.172  1997/01/17  22:11:41  neto
Modifying sfc comparison function.  Still buggy.
Need to use both bits at the same time (x and y) and use table
lookup.
Added printing of labels to the postscript debugging output.

Revision 1.170  1997/01/17  19:43:19  neto
MAXHOSTNAMELEN not defined under Solaris.

Revision 1.169  1997/01/16  22:19:02  neto
Print the wall clock time afterward too.

Revision 1.168  97/01/16  14:20:22  neto
Added space filling curve code.

Revision 1.167  96/12/16  16:56:30  neto
Now it passes gcc with lots of warnings turned on.

Revision 1.166  96/12/13  15:14:03  neto
Fixed a parameter mistake in printing.

Revision 1.165  96/12/13  15:08:50  neto
Fixed typo on variable name.

Revision 1.164  96/12/13  14:49:28  neto
Added raw length computation.

Revision 1.163  96/12/12  14:01:35  neto
Fixed a CWEB typo.

Revision 1.162  96/12/12  14:01:09  neto
Print the current time, too.

Revision 1.161  96/12/05  16:13:54  neto
Free the lengths array.

Revision 1.160  96/12/05  16:00:59  neto
Fixed printf.

Revision 1.159  96/12/05  15:57:08  neto
Fixed prototype for double\_cmp, and made it a module subroutine so that
it would be defined before used.

Revision 1.158  96/12/05  15:55:57  neto
Add the lengths in smallest-to-largest order.   This is the best
numerically-wise.

Revision 1.157  96/12/05  15:35:46  neto
Seem to have fixed the validation routine.

Revision 1.156  96/12/05  15:29:19  neto
Dumb dumb dubm.  +=

Revision 1.155  96/12/05  15:27:51  neto
Need more casts.
.l

Revision 1.154  96/12/05  15:25:37  neto
Need to cast the cost function to double.

Revision 1.153  96/12/05  15:00:38  neto
Changed validation to use compute both a length\_t validation variable
and a double-valued validation variable.  For now, use the double-valued
one to do the check.

Revision 1.152  96/12/05  14:54:59  neto
Added name and comment to output.

Revision 1.151  96/12/05  14:41:05  neto
Added option --noround

Revision 1.150  96/11/08  15:49:55  neto
Added some length\_t\_pcast in places.

Revision 1.149  96/09/19  15:41:47  neto
Added string.h to header list.
Removed assert.h

Revision 1.148  96/09/18  17:16:52  neto
Better name for upper limit on resource marks: last\_resource\_mark.
Also, report a summary from the very beginning to the very end.

Revision 1.147  96/09/18  16:42:38  neto
Fixed calling problem with resource\_report.  Duh.

Revision 1.146  96/09/18  16:39:49  neto
Be a little more intelligent about reporting resource statistics.

Revision 1.145  96/09/18  16:22:10  neto
Added a resource mark at the very beginning of the run, to capture
memory usage of the read routine.

Revision 1.144  96/09/17  14:28:52  neto
More feedback about shutdown sequence.  It seems to take a while.

Revision 1.143  96/09/17  14:07:18  neto
Added conditional compilation if structure around a use of 
a twolevel debugging name.

Revision 1.142  96/09/12  14:15:07  neto
Fixed an unterminated preprocessor else.

Revision 1.141  96/09/12  14:08:10  neto
Removed duplicate const in prototype.

Revision 1.140  96/09/12  14:05:44  neto
Added twolevel debugging routines.

Revision 1.139  96/09/11  16:37:48  neto
Strengthened tour\_set prototype.

Revision 1.138  96/09/10  16:21:26  neto
Added handling of two-level representation.

Revision 1.137  96/08/23  17:24:32  david
Removed the period from the etal macro

Revision 1.136  1996/08/23  15:40:41  david
Fixed for linux.  Unistd declares gethostname and getpagesize only
if \_\_USE\_BSD is defined.  So I doit manually.

Revision 1.135  96/08/20  11:30:40  neto
Added unistd.h for gethostname

Revision 1.134  96/08/16  16:59:37  neto
Report the fixincludes rcs id only if we actually compiled it in.

Revision 1.133  96/08/16  16:56:43  neto
Was including fixincludes twice erroneously.

Revision 1.132  96/08/16  16:49:58  neto
Added fixincludes to the rcs list

Revision 1.131  96/08/16  13:36:01  neto
only need gethostname

Revision 1.130  96/08/16  13:32:04  neto
Fixed the semantics of fwrite.

Revision 1.129  96/08/16  13:04:58  neto
Added fixincludes.

Revision 1.128  96/08/16  12:42:06  neto
Converted putchar to printf.  Otherwise, I'd never get a prototype
for SunOS' \_flusbuf.

Revision 1.127  96/08/15  14:45:51  neto
Enable  definition of length\_rcs\_id

Revision 1.126  96/08/15  13:29:00  neto
Make it pass -Wall

Revision 1.125  96/08/15  12:36:18  neto
No longer use the "upper" module.

Revision 1.124  96/08/14  15:16:42  neto
Fixed printing of command line.

Revision 1.123  96/08/14  14:45:14  neto
Really fixed it this time.

Revision 1.122  96/08/14  14:41:38  neto
Fixed cast of qsort.

Revision 1.121  96/08/14  14:37:27  neto
Fix the declaration of sort to match ANSI (use void instead of char).

Revision 1.120  96/08/14  13:48:56  neto
Add an option to specify sorting procedure.

Revision 1.119  96/08/02  14:38:42  neto
Update documentation and printing of command line to reflect new
construct implementation.
.\

Revision 1.118  96/08/02  14:10:52  neto
Update command line switches to match what construct offers.
Updated the construct() call.

Revision 1.117  96/07/30  16:29:32  neto
Flush stdout after each call to resource\_mark

Revision 1.116  96/07/29  17:08:19  neto
Fixed to compile

Revision 1.115  96/07/29  16:20:02  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*The Lin-Kernighan program.
This program implements the Lin-Kernighan heuristic for the 
traveling salesman problem (TSP).  

See the famous 1973 paper {\sl 
An effective heuristic algorithm for the traveling salesman
        problem},
Operations Research,
    {\bf 21},
    pp.~498--516,
    1973,
  by Shen Lin and Brian Kernighan
for the first description and motivation of this algorithm.
A more modern source is the chapter by Johnson and McGeoch, 
    {``The traveling salesman problem:
            a case study''},
Chapter 8, 
    pp.~215--310, in
    {\sl Local Search in Combinatorial Optimization},
    {Emile Aarts and Jan Karel Lenstra} editors,
    {John Wiley \& Sons}, 1997,
    {Wiley Interscience series in discrete mathematics
        and optimziation}.
That chapter
describes the Lin-Kernighan  algorithm (LK from now on) in the
context of other local search algorithms for the TSP.  If you plan to implement
LK, you really ought to study that chapter closely.  When it comes becomes
available,
you should also read the implementation report by Johnson, Bentley, McGeoch
and Ostheimer.

(Then again, why not just work from this code base?)

@ The outline of the main module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Early module headers@>@;
@<Module headers@>@;

@<Module variables@>@;
@<Global variables@>@;
@<Static prototypes@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *lk_rcs_id="$Id: lk.w,v 1.251 1998/07/16 21:58:55 neto Exp neto $";


@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#define __USE_MISC		/* Linux needs this to get the definition of |nrand48| */
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#if defined(OS_HAS_BROKEN_HEADERS)
#define FIXINCLUDES_USE_RCS_ID
#define FIXINCLUDES_NEED_GETHOSTNAME
#define FIXINCLUDES_NEED_TIME_STUFF
#include "fixincludes.h"
#undef FIXINCLUDES_USE_RCS_ID
#undef FIXINCLUDES_NEED_GETHOSTNAME
#undef FIXINCLUDES_NEED_TIME_STUFF
#endif

@ The exported interface is contained in the \file{lk.h} header file,
which has the following form.

@(lk.h@>=
extern const char *lk_rcs_id;
@<Exported type definitions@>@;
@<Exported definitions@>@;
@<Exported variables@>@;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we import our own interface.

@<Module headers@>=
#include "lk.h"


@*The main module.
The program parses the command line, reads an instance,
builds support data structures, constructs a starting tour,
optimized that tour with Lin-Kernighan, then prints the results.

If the system supports resource measurement, then resource usage
is reported over the phases of execution.

@<Subroutines@>=
int
main(int argc, char **argv) 
{
	@<|main| variables@>@#
	@<Do basic initialization@>@;
	@<Parse the command line@>@;
	@<Print a banner@>@;
	@<Read the TSP instance@>@;
	@<Possibly produce only a Held-Karp lower bound@>@;
	@<Possibly reorder the cities@>@;
	@<Allocate the space for this instance@>@;
	@<Build the data structures@>@;
	if ( do_weighted_perfect_matching ) {
		@<Construct a starting matching@>@;
	} else {
		@<Construct a starting tour@>@;
	}
	@<Run the Lin-Kernighan algorithm@>@;
	@<Stop the timers and print interval times@>@;
	@<Validate and print the result@>@;
	@<Free the allocated space@>@;
	return 0;
}


@*Command-line options.
We'll be experimenting with this program, so we need to put in lots of
control knobs, better known as command-line options.  

This program follows the
GNU conventions.  Each option has both a short name consisting of a 
minus sign followed by a single letter, and a long name, 
consisting of two minus
signs  followed by a string of alphanumeric characters.  Parameters to
an option follow whitespace after the option name.  Options are terminated
by `{\tt --}', thus allowing filename parameters to the program to
begin with a leading dash while not being in conflict with command-line
option names or their parameters.

In this program, parameters are processed from left to right, so later
options may override earlier options.

Option \type{-h} or \type{--help} prints out help for command-line 
options, and then quits the program.

Option \type{--version} makes LK print out version information
and then exit successfully.


Option \type{-v} or \type{--verbose} turns on the ``verbose'' mode of 
output.  It has an optional numeric argument, where 0 means no verbose
reporting, and higher values lead to more verbiage.  If no number
is provided, then a default value of 100 is used.  If this option is not
used at all, then a default value of |DEFAULT_VERBOSE| is used.

Option \type{-P} or \type{--postscript} has a mandatory filename argument.
Debugging PostScript output is placed in that file.

Option \type{-q} or \type{--quiet} is synonymous with \type{--verbose 0}.

Option \type{-i} or \type{--iterate} tells us that Lin-Kernighan should
be iterated in the sense of Johnson'90.  An optional numeric
parameter specifies the number of iterations. 
If no numeric parameter is given, a value of 20 is used.  
This is not yet implemented.

Option \type{-r} or \type{--representation} has a mandatory string argument
specifying which oriented tour representation we should use.  
Allowable arguments are \type{array} (the default), 
\type{splay}, 
\type{two-level}, 
\type{tld}, 
and \type{segment}.   
Only \type{array} and \type{two-level} are supported for now.
Suboption \type{splay} has an optional numeric argument that must be either
0, 1, 2, or 3, corresponding to each of the four levels of faithfullness
to the splaying discipline (lower numbers mean less splaying).  See
Fredman \etal.~for the details on this.
Option \type{tld} is ``two-level-debug''; it checks the two-level tree
implementation against the array implementation; the program must have
been compiled
with symbol |TWOLEVEL_DEBUG| defined.


Option \type{-c} or \type{--candidate} has a mandatory expression 
as a parameter.  For each city $i$ in the tour, the expresion specifies
a predicate that defines which other cities may appear on $i$'s candidate list.
The basic predicates are as follows: \type{nn $k$} is satisfied by the $k$
nearest neighbours of city $i$; \type{nq $k$} is satisfied by the $k$
nearest neighbours of $i$ in each quadrant surrounding $i$;
\type{del $d$} is satisfied by any city that is at most $d$ steps away 
from city $i$ in the Delauney triangulation of all the cities.
(The last two options are only applicable to two-dimensional Euclidean 
instances.)  Basic predicates may be combined by the keyword \type{or}.
Delauney triangulation is not yet supported.

Option \type{-s} or \type{--start} has a mandatory string argument specifying
what the starting tour should be.  Allowable arguments are 
\type{random} (random tour),
\type{canonical} (tour $1,2,3,\ldots,n$),
\type{greedy} (greedy, or multi-fragment heuristic---the default)
%\type{ai} (arbitrary insertion), 
%and \type{best} (best of the above---the default).
Suboption \type{random} takes an optional long integer seed.
If the points are to be sorted by a spacefilling curve, 
by specifying option \type{--sfc}, then the canonical tour is the cities
in space-filling curve order.

Option \type{-S} or \type{--sort} has a mandatory string argument specifying
what the sorting procedure should be.  Allowable arguments are
\type{qsort} (the system C library's implementation of Quicksort),
or
\type{dsort} (a determinstic sorting function---Bentley and McIlroy's 
implementation of Quicksort, see INSERT REFERENCE).
It so happens that some system library's implementations of |qsort|
are not deterministic; running times of this program have varied
by up to a factor of 2 because of it, and they sometimes return different
length tours.  Using \type{-S dsort} ensures consistent results.

Option \type{-p} or \type{--print} tells us to print the LK-optimal
tour (or matching)
when
we're done.  The default is to not print the tour (matching), because I'm
usually
interested in the far less bulky output of only run times and tour lengths.

Option \type{-M} or \type{--mst-edge-lengths-only} tells us to 
compute the minimum spanning tree, output the set of edge lengths
in the tree, and then exit.  In particular, a tour is not computed
when this option is used.  This option is useful for cloning an input.
See the program \file{tspgen}.  For post-processing, this option is
probably most useful with the \type{--quiet} so that human-oriented
noise is removed.

Option \type{--no-round} tells us to avoid rounding computed distances.  
The TSPLIB file format specifies that instances of type |EUC_2D| use
rounded distances, \ie, 
$$\hbox{\it cost}(u,v) = \left\lfloor 0.5 + \sqrt{(u_x-v_x)^2+(u_y-v_y)^2} 
\right\rfloor.$$
However, David Johnson's runs on Euclidean inputs do not do any rounding
(I had a pleasant conversation with him at FOCS'96 in Burlington, Vermont).
Using this option allows us to override the TSPLIB definition and just use
the ordinary Euclidean metric:
$$\hbox{\it cost}(u,v) = \sqrt{(u_x-v_x)^2+(u_y-v_y)^2}.$$
This is useful only when the |length_t| type is either an exact type or 
a floating point type.

Option \type{--sfc} asks us to reorder the cities according to my
space-filling curve.  This only makes sense for geometric instances,
and is currently only implemented for 2-dimensional Euclidean instances.
This uses extra memory to remember the mapping.
However, I expect this to use the cache hierarchy more effectively.
This is a research hypothesis.

Option \type{--maxdepth} takes an optional integer argument, $d$.
It asks us to limit the probe depth to at most $d$ generic flips, \ie\
$d$ flips deep in the greedy portion of the search for an improving
sequential $\lambda$-change.
Some researchers speed up their implementations of Lin-Kernighan
by specifiying that probes should stop at 50 or 100 flips.
I believe
this is unnatural.   
Instead I think limiting the depth due to the
inherent topology of the instance is preferable.
This is a research hypothesis.
If this option is not specified, then no limit is put on the probing depth.
If \type{--maxdepth} is specified without giving a value for $d$, then
a default of $d=50$ is used.

Option \type{-l} or \type{--lower-bound}
takes two mandatory arguments, a string and a number.
The number is taken as a lower bound on the tour length, useful for
keeping track of milestones.  The string is a name for the bound
given by the user.  In verbose output the milestones are labelled with
the name of the bound. 
For example, the user might indicate a known optimal tour length by
specifying \type{-l optimal 14379}. 
(Optimal tours for \type{lin105} have
length 14379.) 
Then the output might say something like: 
\type{2.5\% above optimal after 1.5 user seconds}.
Simliarly, \type{-l Held-Karp 702.3} might be used to get messages like
\type{2.5\% above Held-Karp after 5.5 user seconds}.
If a bound is specified, milestones are printed when the verbose level 
is 25 or more.

Option \type{-u} or \type{--upper-bound}
is similar to \type{-l}, 
taking two mandatory arguments, a string and a number.
The number is taken as an upper bound on the tour length,
and the name is taken as its description, \eg, \type{optimal}, or
\type{best-known}.  This option is required when option \type{--held-karp}
is specified.

Option \type{--held-karp} specifies that we should compute the
Held-Karp lower bound on the tour length, and then exit.
See module \module{ASCEND} for a description of the Held-Karp lower bound.

Option \type{--held-karp-lambda} specifies that we should compute
the Held-Karp lower bound on tour length and print out a representation
of the Lagrange multipliers with which we achieve that bound.

Option \type{-m} or \type{--matching} tells us to tackle the Minimum
Weighted Perfect Matching problem rather than the Traveling Salesman
Problem.  It affects several of the other options: the tour representation
is irrelevant; the start kind (\type{canonical}, \type{greedy},
\type{random}) specifies algorithms constructing weighted
perfect matchings that correspond to similar algorithms for
constructing tours.



Option \type{-} specifies that the TSPLIB input will be found on the standard
input stream.  

Anything that remains on the command line after options are processed will
be treated as a filename from which our TSPLIB input is taken.  It is an
error to specify more than one file (standard input counts as a file).
If no files are specified, then the standard input is used.

@ We scan the command line arguments from left to right.

@<Parse the command line@>=
@<Set the option defaults@>@;
{ int r, filecount=0, postscript_filecount=0, more_options = 1;
	filename = NULL;
	for (r=1;r<argc;r++) {
		if ( more_options && argv[r][0] == '-' && argv[r][1]!=0 ) {
			@<Parse this option@>@;
			@<Flag illegal option@>@;
		} else {
			if ( filecount ) {
				@<Print the command line; split at |r|@>@;
				fprintf(stderr,"Only one input file allowed\n");
				exit(1);
			}
			if ( !(more_options && strcmp(argv[r],"-")==0) ) 
				filename = argv[r];
				/* |else| case means use |stdin| */
			filecount++;
		}
	}
}
@<Check option prerequisites@>@;


@
@<Module variables@>=
static char *filename;
static int mst_edge_lengths_only;
static int do_weighted_perfect_matching;
static int held_karp_only;
static int held_karp_lambda_only;

@
@d DEFAULT_VERBOSE 5
@<Set the option defaults@>=
	verbose = DEFAULT_VERBOSE;
	iterations = 1;
	should_show_tour = 0;
	should_show_version = 0;
	mst_edge_lengths_only = 0;
	held_karp_only = 0;
	held_karp_lambda_only = 0;
	do_weighted_perfect_matching = 0;
	representation = REP_ARRAY;
	candidate_expr = CAND_NN;
	cand_nn_k = 20;
	cand_nq_k = 5;
	cand_del_d = 3;
	construction_algorithm = CONSTRUCT_GREEDY;
	start_heuristic_param = 42L;
	PostScript_filename = NULL;
	lower_bound_name = NULL;
	lower_bound_value=1.0; /* Dummy. */
	upper_bound_name = NULL;
	upper_bound_value=0.0; /* Dummy. */
	sort = (void (*)(void *, size_t, size_t, int(*)(const void*,const void*)))qsort;
	noround = 0;
	
@
@<Global variables@>=
int verbose, iterations, should_show_tour, should_show_version;
int representation, construction_algorithm;
long start_heuristic_param;
int candidate_expr, cand_nn_k, cand_nq_k, cand_del_d;
char *PostScript_filename, *lower_bound_name, *upper_bound_name;
void (*sort)(void *a, size_t n, size_t es, int(*cmp)(const void *,const void*));
int noround;
double upper_bound_value, lower_bound_value;

@
@<Exported variables@>=
extern int verbose, iterations, should_show_tour, should_show_version;
extern int representation, construction_algorithm;
extern long start_heuristic_param;
extern int candidate_expr, cand_nn_k, cand_nq_k, cand_del_d;
extern char *PostScript_filename, *lower_bound_name, *upper_bound_name;
extern void (*sort)(void *a, size_t n, size_t es, int(*cmp)(const void *,const void*));
extern int noround;
extern double lower_bound_value, upper_bound_value;

@
@<Exported definitions@>=
#define REP_ARRAY		1	/* Tour representations */
#define REP_TWO_LEVEL	2
#define REP_SPLAY_0		3
#define REP_SPLAY_1		4
#define REP_SPLAY_2		5
#define REP_SPLAY_3		6
#define REP_TWO_LEVEL_DEBUG		7
@#

#define CAND_NN			1	/* Candidate predicate types --- they may be ||||'d */
#define CAND_NQ			2
#define CAND_DEL		4
@#


@  The \type{--help} option is the easiest one.
@<Parse this option@>=
if ( strcmp(argv[r],"-h")==0 || strcmp(argv[r],"--help")==0 ) {
	printf("Usage: %s [options] [filename]\n",argv[0]);
	printf(" -                          TSPLIB input on stdin\n");
	printf(" --                         End options\n");
	printf(" -l --lower-bound <name> <length> \n"
           "                            Give lower bound, enable milestones\n");
	printf(" -c --candidate <p>         Specify candidate cities\n");
	printf("      <p> ::= <bp> | <bp> or <p>\n");
	printf("      <bp> ::= nn <k> | nq <k> | del <d>\n");
	printf("                            (nq, del are unimplemented)\n");
	printf("    --held-karp             Compute approx Held-Karp TSP lower bound,\n");
	printf("                            then exit successfully.  Requires -u\n");
	printf("    --held-karp-lambda      Compute approx Held-Karp TSP lower bound,\n");
	printf("                            print the best Lagrange multipliers found,\n");
	printf("                            then exit successfully.  Requires -u\n");
	printf(" -h --help                  Give this help, then exit\n");
	printf(" -i --iterate [n]           Iterated LK n times (default is 1, n default is 20)\n");
	printf("                            (unimplemented)\n");
	printf(" -m --matching              Find cheap weighted perfect matchings\n"@| 
		   "                            rather than short tours\n");
	printf(" -M --mst-edge-lengths-only Print the edge lengths in a minimum spanning tree\n");
	printf("                            and then exit successfully\n");
	printf("    --maxdepth [d]          Limit probe depth to d cities\n");
	printf("    --no-round              Don't round distance computations\n");
	printf(" -p --print                 Print the LK-optimal tour or matching\n");
	printf(" -P --postscript <file>     Generate PostScript output and write to <file>\n");
	printf(" -q --quiet                 Same as --verbose 0\n");
	printf(" -r --representation <rep>  Specify tour representation (default is array)\n");
	printf("      <rep> ::= array | two-level | tld (two-level-debug)| splay\n");
	printf("                            (This has no effect if finding a matching)\n");
	printf(" -s --start <kind>          Specify staring tour (matching) algorithm"@|
           "                            Greedy is default.\n");
	printf("      <kind> ::= canonical | greedy | random [seed]\n");
	printf("    --sfc                   Reorder cities by Moore's space filling curve\n");
	printf(" -S --sort <kind>           Specify sorting procedure (default is qsort)\n");
	printf("      <kind> ::= qsort (from system library) | dsort (Bentley&McIlroy qsort)\n");
	printf(" -u --upper-bound <name> <length> \n"
           "                            Give upper bound, required for Held-Karp\n");
	printf(" -v --verbose [n]           Set verbose level (default is 5, n default is 100)\n");
	printf("    --version               Print LK version number, then exit successfully\n");
	exit(0);
}

@ If the user tells us the options are finished, then we shouldn't process more
options...  (Sort of obvious, huh?).

@<Parse this option@>=
if ( strcmp(argv[r],"--")==0 ) {
	more_options = 0;
	continue;
}

@ Here we find out whether we should turn off rounding of Euclidean distance
computations.
@<Parse this option@>=
if ( strcmp(argv[r],"--no-round")==0 ) {
	noround = 1;
	continue;
}

@ Here we find out whether we must print the tour in addition to
printing its length.
@<Parse this option@>=
if ( strcmp(argv[r],"-p")==0 || strcmp(argv[r],"--print")==0 ) {
	should_show_tour = 1;
	continue;
}

@ Here we find out whether we should only print the minimum spanning
tree edge lengths (and not compute a tour).
@<Parse this option@>=
if ( strcmp(argv[r],"-M")==0 || strcmp(argv[r],"--mst-edge-lengths-only")==0 ) {
	mst_edge_lengths_only = 1;
	continue;
}

@ Here we find out whether we should only compute a Held-Karp lower
bound for the TSP.
@<Parse this option@>=
if ( strcmp(argv[r],"--held-karp")==0 ) {
	held_karp_only = 1;
	continue;
}

@ Here we find out whether we should only compute a Held-Karp lower
bound for the TSP and print the Lagrange multipliers used.
@<Parse this option@>=
if ( strcmp(argv[r],"--held-karp-lambda")==0 ) {
	held_karp_lambda_only = 1;
	continue;
}

@ Here we find out whether we should try to find a cheap weighted perfect
matching rather than a short tour.  
If we are to find a matching, then the tour representation is irrelevant,
because there is no tour.

@<Parse this option@>=
if ( strcmp(argv[r],"-m")==0 || strcmp(argv[r],"--matching")==0 ) {
	do_weighted_perfect_matching = 1;
	continue;
}



@ Here we find out whether we should print version information.
@<Parse this option@>=
if ( strcmp(argv[r],"--version")==0 ) {
	should_show_version = 1;
	@<Print a version banner@>@;
	exit(0);
	continue;
}


@ Here we find out whether we should reorder the cities according to
my spacefilling curve.  I suspect this improves the performance in
a non-uniform memory architecture (NUMA) machine.  I have my reasons.
@^non-uniform memory architecture@>
@^NUMA@>

@<Parse this option@>=
if ( strcmp(argv[r],"--sfc")==0 ) {
	should_sfc_reorder = 1;
	continue;
}

@
@<Set the option defaults@>=
should_sfc_reorder = 0;

@
@<Global variables@>=
int should_sfc_reorder;


@ The quiet option sets the verbose variable.
@<Parse this option@>=
if ( strcmp(argv[r],"-q")==0 || strcmp(argv[r],"--quiet")==0 ) {
	verbose = 0;
	continue;
}

@ The verbose option has an optional numerical argument.  We must check for
its presence.
@<Parse this option@>=
if ( strcmp(argv[r],"-v")==0 || strcmp(argv[r],"--verbose")==0 ) {
	verbose = 100;
	if ( r+1<argc && is_number(argv[r+1]) ) verbose = atoi(argv[++r]);
	continue;
}

@ But we need to create the predicate |is_number|.  We allow an optional
single
unary minus.  We are paranoid about |NULL| parameters.

@<Module subroutines@>=
static int
is_number(char *p) 
{
	if ( p == NULL ) return 0;	/* Be paranoid. */
	if ( *p == '-' ) p++;		/* Skip over a single unary minus. */
	if ( *p == 0 ) return 0;	/* Need at least one digit. */
	for (;*p;p++) {
		if (!isdigit(*p)) return 0;
	}
	return 1;
}

@	We've just used the |isdigit| macro which is defined in \file{ctype.h}.
@<System headers@>=
#include <ctype.h>

@ While we're doing optional numerical arguments, 
let's do the \type{--iterate} switch as well.
@<Parse this option@>=
if ( strcmp(argv[r],"-i")==0 || strcmp(argv[r],"--iterate")==0 ) {
	iterations = 20;
	if ( r+1<argc && is_number(argv[r+1]) ) iterations = atoi(argv[++r]);
	continue;
}

@ The maximum probe depth option has an optional numerical argument, which
goes into |max_generic_flips|.  
We must check this option's presence, as in the verbose option.

@<Parse this option@>=
if ( strcmp(argv[r],"--maxdepth")==0 ) {
#if !defined(JBMR_LIMIT_PROBE_DEPTH)
	errorif(1,
		"Option --maxdepth requires JBMR_LIMIT_PROBE_DEPTH compilation flag.\n");
#endif
	max_generic_flips = 50;
	if ( r+1<argc && is_number(argv[r+1]) ) max_generic_flips = atoi(argv[++r]);
	continue;
}

@
@<Global variables@>=
int max_generic_flips;

@
@<Exported variables@>=
extern int max_generic_flips;

@ The default maximum probe depth should really be $\infty$ but |INT_MAX|,
the maximum representable signed integer should suffice.
@<Set the option defaults@>=
max_generic_flips=INT_MAX;

@  We need the definition of |INT_MAX|
@<System headers@>=
#include <limits.h>

@ Lets tackle the starting tour option.  This has a mandatory string
argument chosen from a fixed list.  Argument string \type{random} has
an optional numeric parameter.
@<Parse this option@>=
if ( strcmp(argv[r],"-s")==0 || strcmp(argv[r],"--start")==0 ) {
	if ( r+1>=argc ) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr, "Need one of {canonical,greedy,random [seed]}\n");
		exit(1);
	}
	r++;

	if ( strcmp(argv[r],"greedy")==0 ) construction_algorithm = CONSTRUCT_GREEDY;
	else if ( strcmp(argv[r],"canonical")==0 ) construction_algorithm = CONSTRUCT_CANONICAL;
	else if ( strcmp(argv[r],"random")==0 ) {
		construction_algorithm = CONSTRUCT_RANDOM;
		if ( r+1<argc && is_number(argv[r+1]) ) start_heuristic_param = atol(argv[++r]);
	} else {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr, "Need one of {canonical,greedy,random [seed],best}\n");
		exit(1);
	}
	continue;
}

@ Next comes the sort procedure option.  It also has a mandatory string
argument chosen from a fixed list.
@<Parse this option@>=
if ( strcmp(argv[r],"-S")==0 || strcmp(argv[r],"--sort")==0 ) {
	if ( r+1>=argc ) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr, "Need one of {dsort,qsort}\n");
		exit(1);
	}
	r++;

	if ( strcmp(argv[r],"qsort")==0 ) 
		sort = (void (*)(void *, size_t, size_t,int(*)(const void*,const void*)))qsort;
	else if ( strcmp(argv[r],"dsort")==0 ) sort = dsort;
	else {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr, "Need one of {dsort,qsort}\n");
		exit(1);
	}
	continue;
}

@ We need to import the interface to |dsort|.
@<Module headers@>=
#include "dsort.h"

@ The \type{--representation} switch also has a mandatory string
argument chosen from a fixed list.

@<Parse this option@>=
if ( strcmp(argv[r],"-r")==0 || strcmp(argv[r],"--representation")==0 ) {
	if ( r+1>=argc ) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr, "Need one of {array,splay [level],two-level,tld}\n");
		exit(1);
	}
	r++;
	if ( strcmp(argv[r],"array")==0 ) {
		representation = REP_ARRAY;
	} else if ( strcmp(argv[r],"two-level")==0 ) {
		representation = REP_TWO_LEVEL;
	} else if ( strcmp(argv[r],"tld")==0 ) {
		representation = REP_TWO_LEVEL_DEBUG;
	} else if ( strcmp(argv[r],"splay")==0 ) {
		int level=0;
		if ( r+1<argc && is_number(argv[r+1]) ) level = atoi(argv[++r]);
		if ( level<0 || level>3 ) {
			@<Print the command line; split at |r|@>@;
			fprintf(stderr,"Splay level must be 0, 1, 2, or 3\n");
			exit(1);
		}
		representation = REP_SPLAY_0 + level;
	} else {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr, "Need one of {array,splay [level],two-level,tld}\n");
		exit(1);
	}
	continue;
}

@ The PostScript option  needs a filename.
@<Parse this option@>=
if ( strcmp(argv[r],"-P")==0 || strcmp(argv[r],"--postscript")==0 ) {
	if (r+1>=argc) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr,"Need a file name\n");
		exit(1);
	}
	r++;
	if ( postscript_filecount ) {
		fprintf(stderr,
			"Warning: %s already specified as PostScript output file; "
			"%s overrides\n", 
			PostScript_filename, argv[r]);
	}
	postscript_filecount++;
	PostScript_filename = argv[r];
	continue;
}

@ The lower bound option needs a name and a floating-point number.
In most UNIX shells, names with spaces can be specified if quoted.

@<Parse this option@>=
if ( strcmp(argv[r],"-l")==0 || strcmp(argv[r],"--lower-bound")==0 ) {
	if (r+1>=argc) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr,"Need a lower bound name\n");
		exit(1);
	}
	if (r+2>=argc) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr,"Need a lower bound on length\n");
		exit(1);
	}
	r++;
	lower_bound_name=dup_string(argv[r]);
	r++;
	lower_bound_value=atof(argv[r]);
	continue;
}

@ The upper bound option is very much like the lower bound option.

@<Parse this option@>=
if ( strcmp(argv[r],"-u")==0 || strcmp(argv[r],"--upper-bound")==0 ) {
	if (r+1>=argc) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr,"Need an upper bound name\n");
		exit(1);
	}
	if (r+2>=argc) {
		@<Print the command line; split at |r|@>@;
		fprintf(stderr,"Need an upper bound on length\n");
		exit(1);
	}
	r++;
	upper_bound_name=dup_string(argv[r]);
	r++;
	upper_bound_value=atof(argv[r]);
	continue;
}

@ The upper bounding option is required when computing Held-Karp lower bounds.
@<Check option prerequisites@>=
errorif( (held_karp_only || held_karp_lambda_only) && upper_bound_name == NULL,
	"Held-Karp lower bounding requires an upper bound\n");


@ Now we get to the most involved option: the candidate list predicate 
expression.  Fortunately, it's at worst just the disjunction of a number of
basic predicates.

@<Parse this option@>=
if ( strcmp(argv[r],"-c")==0 || strcmp(argv[r],"--candidate")==0 ) {
	int numeric_param;
	candidate_expr = cand_nn_k = cand_nq_k = cand_del_d = 0;
	r++;
	do {
		if ( r>=argc ||
				(strcmp(argv[r],"nn")!=0 && strcmp(argv[r],"nq")!=0 &&
				strcmp(argv[r],"del")!=0) 
		   ) {
			@<Print the command line; split at |r|@>@;
			fprintf(stderr,"Need one of {nn,nq,del}\n");
			exit(1);
		}
		if ( r+1>=argc || !is_number(argv[r+1]) ) {
			r++;
			@<Print the command line; split at |r|@>@;
			fprintf(stderr,"Need a numeric parameter\n");
			exit(1);
		} else numeric_param = atoi(argv[r+1]);
		if ( strcmp(argv[r],"nn")==0 ) {
			candidate_expr |= CAND_NN;
			if ( cand_nn_k < numeric_param ) cand_nn_k = numeric_param;
		} else if ( strcmp(argv[r],"nq")==0 ) {
			candidate_expr |= CAND_NQ;
			if ( cand_nq_k < numeric_param ) cand_nq_k = numeric_param;
		} else if ( strcmp(argv[r],"del")==0 ) {
			candidate_expr |= CAND_DEL;
			if ( cand_del_d < numeric_param ) cand_del_d = numeric_param;
		} else {
			@<Print the command line; split at |r|@>@;
			fprintf(stderr,"Need one of {nn,nq,del}\n");
			exit(1);
		}
		r++;
	} while( r+1<argc && strcmp(argv[r+1],"or")==0 && (r+=2) );
	continue;
}

@ If there's an option we don't understand, then we tell the user about
it and skip over it.  Note that the code for each legal option performs
a |continue| to get to the next argument, so if we get here, then we've
seen a non-empty string with a leading `\type-'.

@<Flag illegal option@>=
@<Print the command line; split at |r|@>@;
fprintf(stderr,"Skipping unrecognized option %s\n",argv[r]);

@ Here we print out the command line, from  the
beginning of the candidate expression onward, but split it right
after the last token read.  This idea is stolen from Knuth's 
\TeX.  We do the splitting in this way so the user can see where
the program got confused (or found an error, rather).

Variable |se| marks the start of the expression.  Did you catch its definition
above?

To be able to properly show the split, we count the characters coming before
the split.

@<Print the command line; split at |r|@>=
{	int chars_before_split = 0, i;
	for ( i=0;i<=r && i<argc;i++ ) {
		fprintf(stderr,"%s ",argv[i]);
		chars_before_split += strlen(argv[i]) + 1;
	}
	fputc('\n',stderr);
	for ( i=0;i<chars_before_split;i++) {fputc(' ',stderr);}
	for ( i=r+1 ; i<argc ; i++ ) {
		fprintf(stderr,"%s ",argv[i]);
	}
	fputc('\n',stderr);
}

@ Once the command line has been successfully parsed, we print a banner.  
It consists of a few lines of text identifying the program name, version
numbers, and information on how the program was compiled and run.

While measuring and testing this program, it is important to know
the version of the module being used.  I use the revision control system
known as RCS.  The following string variable is updated automatically
each time this module is checked into the system.
@^RCS@>
@^revision control system@>

@<Print a banner@>=
if ( verbose>=10 ) {
	extern const char *compile_compile, *compile_link; /* Compiler options */
	@<Print a version banner@>@;
	if ( verbose >= 10 ) @<Print a copyright notice@>@;
	if ( verbose >= 100 ) {
		printf("%s\n",compile_compile);
		printf("%s\n",compile_link);
		printf("%s\n",array_rcs_id);
		printf("%s\n",construct_rcs_id);
		printf("%s\n",dict_rcs_id);
		printf("%s\n",dsort_rcs_id);
		printf("%s\n",error_rcs_id);
#if defined(OS_HAS_BROKEN_HEADERS)
		printf("%s\n",fixincludes_rcs_id);
#endif
		printf("%s\n",jbmr_rcs_id);
		printf("%s\n",kdtree_rcs_id);
		printf("%s\n",length_rcs_id);
		printf("%s\n",lk_rcs_id);
		printf("%s\n",memory_rcs_id);
		printf("%s\n",nn_rcs_id);
		printf("%s\n",pool_rcs_id);
		printf("%s\n",read_rcs_id);
		printf("%s\n",resource_rcs_id);
	}
	printf("Command line equivalent: ");@+@<Print an equivalent command line@>@;
	printf("Start time: ");@+@<Print the current time@>@;
}

@ String |VERSION_STRING| appears in \file{$<$config.h$>$} and is set
in file \file{configure.in}.  
%This version banner conforms to the GNU coding standards.

If declustering is implemented, then a short string is appended to
the version number.  The letter \type{d} indicates declustering,
letter \type{e} indicates clustering used for eligibility testing,
and  \type{g} indicates clustering used for greedy selection.
Note that \type{g} implies \type{e}.

@<Print a version banner@>=
printf("LK %s",VERSION_STRING);
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST 
	printf("de");
#	if JBMR_DECLUSTER_IN_GREEDY
		printf("g");
#	endif
#endif
printf("\n");

@ LK is free software.  This is a GNU-compliant copyright notice. 
@<Print a copyright notice@>=
printf(@;
"LK approximately solves the traveling salesman problem.\n"@;
"\nCopyright (C) 1997 David M. Neto\n"@;
"LK comes with NO WARRANTY, to the extent permitted by law.\n"@;
"You may redistribute and/or modify copies of LK under the terms of the\n"@;
"GNU General Public License, version 2 or any later version.\n"@;
"For more information about these matters, see the file named COPYING.\n"@;
/* Maybe insert major author names, i.e. me. */
);

@ A few of the version number strings are in modules we haven't seen yet.
Let's include them now.
@<Module headers@>=
#include "pool.h"
#include "dict.h"
#include "kdtree.h"


@ If verbose mode is on at all, we print out a complete
and unambiguous command line equivalent to the one we got.  That is,
we fill in the important details if they were skipped.

@<Print an equivalent command line@>=
if ( verbose>=10 ) {
	printf("%s ",argv[0]);
	if ( verbose != DEFAULT_VERBOSE ) printf("-v %d ",verbose);
	if ( should_show_version ) printf("--version "); /* But it exits by now! */
	if ( do_weighted_perfect_matching ) printf("-m ");
	if ( mst_edge_lengths_only ) printf("-M ");
	if ( held_karp_only ) printf("--held-karp ");
	if ( held_karp_lambda_only ) printf("--held-karp-lambda ");
	if ( should_show_tour ) printf("-p ");
	if ( noround ) printf("--no-round ");
	if ( NULL != PostScript_filename ) printf("-P %s ",PostScript_filename);
	if ( iterations != 1 ) printf("-i %d ",iterations);@#
	switch(construction_algorithm) {
	case CONSTRUCT_CANONICAL: printf("-s canonical "); break;
	case CONSTRUCT_GREEDY: printf("-s greedy "); break;
	case CONSTRUCT_RANDOM: printf("-s random %ld ",start_heuristic_param);break;
	default: errorif(1,"Bad construction_algorithm == %d\n",construction_algorithm);
	}
	@#
	if ( sort == dsort ) printf("-S dsort ");
	@#
	printf("-c ");
	if ( candidate_expr & CAND_NN ) 
		printf("nn %d %s",cand_nn_k, 
			candidate_expr & (CAND_NQ|CAND_DEL) ? "or ": "");
	if ( candidate_expr & CAND_NQ ) 
		printf("nq %d %s",cand_nq_k, 
			candidate_expr & CAND_DEL ? "or ": "");
	if ( candidate_expr & CAND_DEL ) 
		printf("del %d ",cand_del_d);
	@#
	switch(representation) {
	case REP_ARRAY: printf("-r array "); break;
	case REP_TWO_LEVEL: printf("-r two-level "); break;
	case REP_TWO_LEVEL_DEBUG: printf("-r tld "); break;
	case REP_SPLAY_0: printf("-r splay 0 "); break;
	case REP_SPLAY_1: printf("-r splay 1 "); break;
	case REP_SPLAY_2: printf("-r splay 2 "); break;
	case REP_SPLAY_3: printf("-r splay 3 "); break;
	default: errorif(1,"Bad representation == %d\n",representation);
	}
	@#
	if ( should_sfc_reorder ) printf("--sfc ");
	@#
	if ( max_generic_flips != INT_MAX ) printf("--maxdepth %d ", max_generic_flips);
	@#
	if ( lower_bound_name != NULL ) printf("-l %s %f ", lower_bound_name, lower_bound_value);
	if ( upper_bound_name != NULL ) printf("-u %s %f ", upper_bound_name, upper_bound_value);
	@#
	if ( filename ) {
		if ( filename[0]=='-' ) printf("-- %s",filename);
		else printf("%s",filename);
	} else printf("-");
	printf("\n");
}

@  It might also help the user to tell them when a particular run started.
The following code prints the current date and time in human-readable form.
I hope it uses only ANSI-standard library facilities.
@^system dependencies@>

@<Print the current time@>=
{ 
#if HAVE_TIME_H && HAVE_TIME && HAVE_CTIME
  time_t now = time(NULL);
  printf("%s",ctime(&now));
  fflush(stdout);
#endif
}

@ This time code requires the \file{time.h} interface.
@<System headers@>=
#if HAVE_TIME_H
#include <time.h>
#endif

@*Initialization.

Now we read the instance into a structure that is read-only for the rest
of the program.  That is, after this initialization, this structure is not
changed for the remainder of the execution of the program.  This may have
significant consequences for a parallel implementation of this program.

For convenience, we have a module-level variable |n| which is an alias
for |tsp_instance->n|.

The procedure |read_tsp_file| reads the instance and provides us
with generalized |cost| and |pseudo_cost| functions.  (The |pseudo_cost|
function is only guaranteed to be monotonic in the |cost| function,
although it may be faster.  See the \module{READ} module for more
information.)

@<Read the TSP instance@>=
last_resource_mark = resource_mark("Reading the instance");
if ( filename ) {
	TSPLIB_in = fopen(filename,"r");
	errorif( TSPLIB_in==NULL, "Couldn't open \"%s\" for reading",filename);
} else TSPLIB_in = stdin;
if ( PostScript_filename ) {
	FILE *prolog;
	char buf[8192];
	size_t countin, countout;
	ps_out = fopen(PostScript_filename,"w");
	errorif( ps_out==NULL, "Couldn't open \"%s\" for writing",filename);
	prolog = fopen("prolog.ps","r");
	errorif( prolog==NULL,"Couldn't open prolog.ps for reading");
	while ( (countin=fread(buf,1,8192,prolog)) > 0 ) {
		char *p=buf;
		while ( (countout=fwrite(p,1,countin,ps_out)) < countin ) {
			countin-=countout; p+= countout;
		}
	}
	fclose(prolog);
} else ps_out = NULL;
tsp_instance = read_tsp_file( TSPLIB_in, ps_out );
n = tsp_instance->n;

@ We need to declare that module-level variable |n| and the file handles.
@<Module variables@>=
static int n;
static FILE *TSPLIB_in, *ps_out;

@ The interface for the reading routine is defined in the \file{read.h}.
We also need the |length_t| type.
@<Early module headers@>=
#define LENGTH_USE_RCS_ID
#include "length.h"
#undef LENGTH_USE_RCS_ID
#include "read.h"

@ We need to declare the |tsp_instance| variable.  

@<Global variables@>=
tsp_instance_t *tsp_instance;

@ @<Exported variables@>=
extern tsp_instance_t *tsp_instance;

@*Held-Karp lower bounds for the TSP.
Sometimes all we want to do is produce the Held-Karp lower bound for the
TSP.

Sometimes we want to see the Lagrange multipliers used in the result.

@<Possibly produce only a Held-Karp lower bound@>=
if ( held_karp_only || held_karp_lambda_only ) {
	length_t held_karp_bound; 
	errorif(upper_bound_value<=0,"main: upper bound %d should be positive.",upper_bound_value);
	ascend_setup(n);
	held_karp_bound = ascend(n,upper_bound_value);
	printf("Held-Karp lower bound: "length_t_spec
		" (%.2f%% below upper bound " length_t_spec")\n",
		length_t_pcast(held_karp_bound),
			100.0*((double)(upper_bound_value-held_karp_bound))/upper_bound_value, 
		length_t_pcast(upper_bound_value));
	if ( held_karp_lambda_only ) {
		int i;
		double * const lambda = ascend_best_lambda();
		errorif(lambda==NULL,"No Lagrange multilpier lambda vector!\n");
		printf("Lagrange multipliers:\n");
		for ( i=0; i<n ; i++) {
			printf("%d %f\n",1+i,lambda[i]);
		}
	}
	ascend_cleanup();
	exit(0);
}

@ We need the interface to module \module{ASCEND}.
@<Module headers@>=
#include "ascend.h"

@*Reordering the cities.
I have reason to believe that, for geometric instances at least, 
reordering the cities according to a space-filling curve improves
the performance of the program on machines with
a non-uniform memory architecture (NUMA).
@^non-uniform memory architecture@>
@^NUMA@>

When we do sort the instance, we must remember the original city numbers.
These are stored in the array |original_city_num|.

@<Possibly reorder the cities@>=
if ( should_sfc_reorder ) {
	int i, n=tsp_instance->n;
	coord_2d *new_coord;
	errorif( tsp_instance->coord == NULL, 
		"Space filling curve reordering applies only to geometric instances.\n");
	original_city_num = new_arr_of(int,n);
	for (i=0;i<n ; i++) original_city_num[i] = i;
	sort(original_city_num,(size_t)n,sizeof(int),cmp_sfc_Moore);
	new_coord = new_arr_of(coord_2d,n);
	for (i=0;i<n ; i++) new_coord[i]=tsp_instance->coord[original_city_num[i]];
#if 0
	free_mem(tsp_instance->coord);mem_deduct(n*sizeof(coord_2d));
	tsp_instance->coord = new_coord;
#else
	for (i=0;i<n ; i++) tsp_instance->coord[i]=new_coord[i];
	free_mem(new_coord);mem_deduct(n*sizeof(coord_2d));
#endif
#if defined(LK_SHOW_AFTER_SFC)
	if ( ps_out ) {
		length_t len=cost(0,n-1);int i; for (i=1;i<n;i++,len+=cost(i,i-1));
		fprintf(ps_out,"(SFC(Moore) tour, len "length_t_spec") title\n",
			length_t_pcast(len));
		fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
		for ( i=0;i<n;i++ ) {
			fprintf(ps_out,"%d %f %f sfcs\n",i+1,
				tsp_instance->coord[i].x,tsp_instance->coord[i].y);
			fprintf(ps_out,"(%d) %d label\n",i,i);
			if ( i>0 ) fprintf(ps_out,"%d %d edge\n",i-1,i);
		}
		fprintf(ps_out,"%d %d edge\n",n-1,0);
		fprintf(ps_out,
			"1 1 N { dup xs exch get exch ys exch get circle } for\n");
		fprintf(ps_out,"showpage\n");
		fflush(ps_out);
	}
#endif
}

@ We make the |original_city_num| array globally visible so that any module
can remamp city numbers for output.  It is non-|NULL| if a remapping is
in effect.

@<Global variables@>=
int *original_city_num = NULL;

@
@<Exported variables@>=
extern int *original_city_num;


@
@<Free the allocated space@>=
free_mem(original_city_num);

@ Here is the comparison function that implicitly defines the space filling
curve.  It defined Moore's curve, a cyclic variant of Hilbert's curve.
Bartholdi and Platzman used a different curve in relation to the TSP, 
and even then only to specify a {\it tour\/},
not a city remapping for improving cache performance.

See my notes of September 27, 1996 for the definition of this function.
Actually, that was buggy.  So see my notes of January 20, 1997.
For much more information about space-filling curves, see the book
by Hans Sagan, {\sl Space Filling Curves}. (INSERT MORE COMPLETE
REFERENCE).
@^Moore's curve@>
@^Hilbert's curve@>
@^Bartholdi@>
@^Platzman@>

We must normalize the coordinates to the unit square with bottom-left
corner lies at the origin.
Just to be pedantic, we must take care of the case where all the points
are on an line parallel to one of the axes.  This is the purpose of the
|XNORM| and |YNORM| macros.  We divide by $(1+\epsilon)$ so that we get values in the
interval $[0,1)$.

@d XNORM(V) (tsp_instance->xmax==tsp_instance->xmin ? 0.0 : 
	((V)-tsp_instance->xmin)/(tsp_instance->xmax-tsp_instance->xmin)/(1+10*DBL_EPSILON));
@d YNORM(V) (tsp_instance->ymax==tsp_instance->ymin ? 0.0 :
	((V)-tsp_instance->ymin)/(tsp_instance->ymax-tsp_instance->ymin)/(1+10*DBL_EPSILON));

@d sgn(value) ((value)<0? -1 : ((value)>0? 1: 0))


@<Module subroutines@>=
int cmp_sfc_Moore(const void *voida, const void *voidb);
int
cmp_sfc_Moore(const void *voida, const void *voidb) 
{
	int ai=*(const int *)voida, bi=*(const int *)voidb;
	double a[2],b[2];
	int ax,ay,bx,by,aq,bq,lastq=12;
	int order[13][4] = 
		{{0,3,1,2},{0,1,3,2},{0,3,1,2},{2,3,1,0},
		 {0,3,1,2},{2,3,1,0},{0,1,3,2},{2,1,3,0},
		 {0,1,3,2},{2,3,1,0},{2,1,3,0},{2,1,3,0},{3,2,0,1}};
	int rewrite[13][4] = 
		{{1,3,2,0},{4,1,7,6} ,{8,9, 2, 0},{9,0, 5,10},
		 {1,9,2,0},{9,0,5,11},{2,1, 11,6},{7,10,8,5},
		 {2,1,7,6},{9,4,5,10},{7,10,6, 3},{7,10,6,5},{7,10,2,0}};
	
	a[0]=XNORM(tsp_instance->coord[ai].x[0]);
	b[0]=XNORM(tsp_instance->coord[bi].x[0]);
	a[1]=YNORM(tsp_instance->coord[ai].x[1]);
	b[1]=YNORM(tsp_instance->coord[bi].x[1]);
@q VIM is just amazing.  It doesn't match parens in strings with parens@>
@q outside of strings.  I've still used at q"(" at> here in case you're using@>
@q some sad sack editor that isn't as smart as VIM in this respect. @>
	errorif(a[0]<0 || a[0]>=1,@q"("@>"cmp_sfc_Moore: a[0] out of range [0,1): %f",a[0]);
	errorif(a[1]<0 || a[1]>=1,@q"("@>"cmp_sfc_Moore: a[1] out of range [0,1): %f",a[1]);
	errorif(b[0]<0 || b[0]>=1,@q"("@>"cmp_sfc_Moore: b[0] out of range [0,1): %f",b[0]);
	errorif(b[1]<0 || b[1]>=1,@q"("@>"cmp_sfc_Moore: b[1] out of range [0,1): %f",b[1]);
	while (1) {
		if ( a[0]==b[0] && a[1]==b[1] )@+ return 0;
		ax = a[0] >= 0.5;@+ ay = a[1] >= 0.5;@+ aq = (ax<<1)+ay;
		bx = b[0] >= 0.5;@+ by = b[1] >= 0.5;@+ bq = (bx<<1)+by;
		if ( aq != bq ) return order[lastq][aq]-order[lastq][bq];
		lastq= rewrite[lastq][aq];
		a[0] = (2*a[0])-ax; a[1] = (2*a[1])-ay;
		b[0] = (2*b[0])-bx; b[1] = (2*b[1])-by;
	}
}

@ We needed a definition of machine epsilon, |DBL_EPSILON|.  It is found
in \file{float.h}.
@<System headers@>=
#include <float.h>


@*Timers.
This program has several phases of execution, and we want to measure 
each of these phases in various ways.
In particular, we will be measuring the
time required to build the auxiliary data structures, construct a starting
tour, and the run the Lin-Kernighan algorithm.
We will also measure the space used by these phases.

The \module{RESOURCE} module is a general purpose measurement tool.  We call
it to take
snapshots of the current resource usage.  First we need to allocate space
for those snapshots.  This allocation is part of the basic initialization
of the program.

@<Do basic initialization@>=
mem_usage_reset();	/* Start memory counter at zero. */
resource_setup(50);  /* 50 is magic: it is an upper bound on the 
	number of calls to  |resource_mark| */
error_postcleanup_stats = resource_abnormal_exit_output;

@ We need to know the interface to the resource measurement module.
@<Module headers@>=
#include "resource.h"

@ We also need to declare |last_resource_mark|, which counts
what it says it counts.  We need it in order to properly report the timings
and memory usage statistics.

@<Module variables@>=
static int last_resource_mark;

@*Data structures.
An efficient implementation of the Lin-Kernighan algorithm requires several
data structures.  For a complete treatment, see the chapter by
Johnson and McGeoch, the paper by Fredman, Johnson, McGeoch and Ostheimer,
and the (as-yet unavailable) implementation report by Johnson, Bentley, 
McGeoch and Rothberg.

@*1$K$-d trees.
The first of these data structure is a 2-d tree, for fast proximity
searching.

@<Build the data structures@>=
if ( E2_supports(tsp_instance) ) {
	begin_data_structures_mark =
	last_resource_mark = resource_mark("Build the 2-d tree");
	E2_create(tsp_instance);
	if ( ps_out ) { E2_postscript_show(ps_out); }
	@<Test the $k$-d tree@>@;
} else {
	begin_data_structures_mark 
		= resource_mark("Begin building data structures (but not k-d tree)");
}


@ We sometimes want to know when the data structures started being built.
@<Global variables@>=
int begin_data_structures_mark;

@
@<Exported variables@>=
extern int begin_data_structures_mark;


@*1 Declustering trees.
Declustering needs some preprocessing as well.  

First, we need a minimum
spanning tree for the TSP instance.

@d ALWAYS_BUILD_DECLUSTER_STRUCTURES 
	(LK_BUILD_DECLUSTER_STRUCTURES 
	|| JBMR_DECLUSTER_IN_ELIGIBILITY_TEST 
	|| JBMR_DECLUSTER_IN_GREEDY)

@<Build the data structures@>=
if ( ALWAYS_BUILD_DECLUSTER_STRUCTURES || mst_edge_lengths_only ) {
	last_resource_mark = resource_mark("Build a MST (decluster)");
	mst_len = decluster_mst(tsp_instance,mst);
	if ( mst_edge_lengths_only ) {
		@<Possibly output the MST as PostScript@>@;
		@<Print the MST edge lengths and exit@>@;
	}
}


@ Sometimes we're only interested in the set of edge lengths in a minimum
spanning tree for the instance.  In that case we print them and then 
immediately exit.

The output format is very simple: the number $n-1$ followed by $n-1$
(floating point) lengths.

@<Print the MST edge lengths and exit@>=
{
	int i;
	printf("%d\n",n-1);
	for (i=0;i<n-1;i++) printf("%.15f\n", (double) (mst->edge[i].cost));
	exit(0);
}

@ If PostScript output is desired and the instance is two-dimensional, 
then we should also output the tree as PostScript.
@<Possibly output the MST as PostScript@>=
if (ps_out && tsp_instance->coord) {
	int i;
	fprintf(ps_out,"(MST length "length_t_spec") title\n",
		length_t_pcast(mst_len));
	fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
	for (i=0;i<n-1;i++) {
		const int *city=mst->edge[i].city;
		fprintf(ps_out,"%f %f %f %f ue\n",
			tsp_instance->coord[city[0]].x[0],
			tsp_instance->coord[city[0]].x[1],
			tsp_instance->coord[city[1]].x[0],
			tsp_instance->coord[city[1]].x[1]);
	}
	fprintf(ps_out,"showpage\ngrestore\n%%%%EOF");
	fclose(ps_out); ps_out=NULL;
}


@ For ordinary processing, we have a second preprocessing task related
to declustering.
We digest the minimum spanning tree so that least common ancestor
queries may be answered in constant time.

@<Build the data structures@>=
#if ALWAYS_BUILD_DECLUSTER_STRUCTURES
last_resource_mark = resource_mark("Preprocess the MST (decluster)");
decluster_preprocess(mst);
#endif

@
@<Cleanup code@>=
#if ALWAYS_BUILD_DECLUSTER_STRUCTURES
if ( verbose >=50 ) printf("Cleaning up MST\n");
if ( mst != NULL ) decluster_cleanup_tree(mst);
if ( verbose >=50 ) printf("Cleaning up decluster data strucutres\n");
decluster_cleanup();
#endif

@
@<Allocate the space for this instance@>=
if ( ALWAYS_BUILD_DECLUSTER_STRUCTURES || mst_edge_lengths_only ) {
mst = decluster_setup(n);
}

@ We need to declare the minimum spanning tree variable |mst|.  Eventually
I'll add code that uses the MST to characterize the clusteredness of 
an instance.

@<Global variables@>=
decluster_tree_t *mst;
length_t mst_len;

@ We've used a bunch of stuff from the \module{DECLUSTER} module.
These inclusion directives are mandatory
because I want dependency
information to always be compiled in.  Header file \file{declevel.h}
specifies the amount of declustering that should be implemented.

@<Module headers@>=
#include "declevel.h"
#include "decluster.h"

@*1 Nearest neighbour lists.
Johnson and McGeoch, and Johnson \etal.~demonstrate the performance
benefit of an adjacency structure in an implementation of the Lin-Kernighan
algorithm.  We build it now.

@<Build the data structures@>=
last_resource_mark = resource_mark("Build the adjacency structure");
errorif((candidate_expr & CAND_NN) && (cand_nn_k < 1), 
	"Neighbourhood bound must be positive, but is %d",cand_nn_k);
errorif((candidate_expr & CAND_NQ) && (cand_nq_k < 1), 
	"Neighbourhood quadrant bound must be positive, but is %d",cand_nq_k);
errorif(candidate_expr & CAND_DEL, "Candidate structure %d not supported",candidate_expr);
nn_build(
	(candidate_expr & CAND_NN) ? cand_nn_k : 0,
	(candidate_expr & CAND_NQ) ? cand_nq_k : 0,
	(candidate_expr & CAND_DEL) ? cand_del_d : 0);

@ We need the interface to the nearest neighbours module.
@<Module headers@>=
#include "nn.h"

@ We need to call the cleanup routine.  
For allocation, things are complicated enough in allocation that it's all
done in |nn_build|.

@<Cleanup code@>=
if ( verbose >=50 ) printf("Cleaning up nn structure\n");
nn_cleanup();


@*The oriented tour ADT.
We also need an 
implementation of the tour abstract data type.  
This implementation both
stores and manipulates the current tour.
Fredman \etal.~introduce this ADT, experimented with various 
implementations of the ADT, and provided an amortized lower bound on the time
it requires to performe a worst-case sequence of operations.


@ Throughout this program, cities are identified 
with integers |0,...,tsp_instance->n-1|, inclusive.

@ The oriented tour ADT consists of the following operations:

|tour_next(a)| is a query that returns the city that follows $a$ in the
current tour.

|tour_prev(a)| is a query that returns the city that precedes $a$ in the
current tour.  It must be the case that 
|tour_next(tour_prev(a))==tour_prev(tour_next(a))==a|.

|tour_between(a,b,c)| is a query that returns true or false.  It answers
the question:  ``In a forward traversal starting at city $a$, do we reach
city $b$ no later than city $c$?''

|tour_flip(a,b,c,d)| updates the tour by replacing the edges $(a,b)$ and
$(c,d)$ by the edges $(b,c)$ and $(a,d)$.  It assumes that 
|a==tour_next(b)| and |d==tour_next(c)|.  The orientation of the updated tour
is not specified.

These four operations are the ones defined by Fredman \etal.  In fact, I
have lifted these descriptions from that paper and lightly edited them
for inclusion here.  

For convenience's sake, I also define |tour_set(int *t)|, which
sets the current tour to be the same as the array of
integers |t|.  That is, city |i| in the tour is city |t[i]|.
Note that we don't need a ``get'' routine because the tour can be read off
by successively following |tour_next| cities until we wrap to the start
again.

We also define the standard setup and clean procedures: |tour_setup(int n)| and
|tour_cleanup(void)|.  The parameter to the setup procedure is the number
of cities in the instance.

@
We isolate the implementation of the tour ADT both because it
is good design practice, and because at run time we may want to select from
several of the
possible implementations.

So, each of the operation names given above are actually function pointers
to actual implementations of these operations.

@<Global variables@>=
int (*tour_next)(int) = NULL;
int (*tour_prev)(int) = NULL;
int (*tour_between)(int,int,int) = NULL;
void (*tour_flip)(int,int,int,int) = NULL;
void (*tour_set)(int const *) = NULL;
void (*tour_setup)(int n) = NULL;
void (*tour_cleanup)(void) = NULL;

@
@<Exported variables@>=
extern int (*tour_next)(int);
extern int (*tour_prev)(int);
extern int (*tour_between)(int,int,int);
extern void (*tour_flip)(int,int,int,int);
extern void (*tour_set)(int const *);
extern void (*tour_setup)(int n);
extern void (*tour_cleanup)(void);

@ Currently, only the \type{array}, \type{two-level}, and \type{tld}
representations
are available.

@<Parse the command line@>=
switch(representation) {
case REP_ARRAY:
tour_next = array_next;
tour_prev = array_prev;
tour_between = array_between;
tour_flip = array_flip;
tour_set = array_set;
tour_setup = array_setup;
tour_cleanup = array_cleanup;
break;
case REP_TWO_LEVEL:
tour_next = twolevel_next;
tour_prev = twolevel_prev;
tour_between = twolevel_between;
tour_flip = twolevel_flip;
tour_set = twolevel_set;
tour_setup = NULL;	/* Special instructions below. */
tour_cleanup = twolevel_cleanup;
break;
case REP_TWO_LEVEL_DEBUG:
#if defined(TWOLEVEL_DEBUG)
tour_next = twolevel_debug_next;
tour_prev = twolevel_debug_prev;
tour_between = twolevel_debug_between;
tour_flip = twolevel_debug_flip;
tour_set = twolevel_debug_set;
tour_setup = NULL;	/* Special instructions below. */
tour_cleanup = twolevel_debug_cleanup;
#else
	errorif(1,"Two-level tree debugging (-DTWOLEVEL_DEBUG) wasn't compiled into the program");
#endif
break;
default:
	errorif(1,"Only array, two-level, and tld representations are currently supported");
}

@ But first we need to include the appropriate tour interfaces.
@<Module headers@>=
#include "array.h"
#include "twolevel.h"

@ We must call the |tour_setup| function before any of the other 
tour operations.  It allocates the requisite space for the tour
ADT implementation.

Two-level trees require an extra parameter, namely a group size.
Fredman \etal (INSERT REFERENCE) use a value of 100 for $n$ between
$10^3$ and $10^5$; they use a value of 200 for larger instances.
We'll extend the bottom end of this range by using a value of $n$
up to 50, and then a value of 50 for $n$ up to 1000.

Of course, tour representations are irrelevant when finding a weighted
matching!

@<Allocate the space for this instance@>=
if ( do_weighted_perfect_matching) {
	tour_setup=NULL;
} else { /* Yes, we really need a tour representation. */
switch(representation) {
case REP_TWO_LEVEL:
	{
	const int n=tsp_instance->n;
	twolevel_setup
		(n, n < 50 ? n : (n < 1000 ? 50 : (n > 100000 ? 200 :  100)));
	}
	break;
case REP_TWO_LEVEL_DEBUG:
	{
#if defined(TWOLEVEL_DEBUG)
	const int n=tsp_instance->n;
	twolevel_debug_setup
		(n, n < 50 ? n : (n < 1000 ? 50 : (n > 100000 ? 200 :  100)));
#else
	errorif(1,"Debugging of two-level isn't possible.  Recompile with -DTWOLEVEL_DEBUG");
#endif
	}
	break;
default:
	tour_setup(tsp_instance->n);
}
}


@ When shutting down, we ought to call the cleanup function.
(But remember this might happen very early in the execution.)
@<Cleanup code@>=
if ( !do_weighted_perfect_matching ) {
	if ( verbose >=50 ) printf("Cleaning up tour data structure\n");
	if ( tour_cleanup != NULL ) (*tour_cleanup)();
}

@ All local search algorithms for the TSP need a starting tour.
The procedure |construct| builds one for us, given |n| and some space
in which to write its results.

@<Construct a starting tour@>=
last_resource_mark = resource_mark("Construct starting tour");
tour = new_arr_of(int,n);
incumbent_len = construct(n,tour,construction_algorithm,start_heuristic_param);
if (verbose>=10) printf("Initial tour length: "length_t_spec"\n",length_t_pcast(incumbent_len));
@<Possibly output the starting tour as PostScript@>@;

@ If PostScript output is desired and the instance is two-dimensional, 
then we should also output the tree as PostScript.
@<Possibly output the starting tour as PostScript@>=
if (ps_out && tsp_instance->coord && verbose >= 50 && 
!do_weighted_perfect_matching ) {
	int i;
	const char *tour_name;
	switch( construction_algorithm ) {
	case CONSTRUCT_CANONICAL: tour_name="Canonical"; break;
	case CONSTRUCT_GREEDY: tour_name="Greedy"; break;
	case CONSTRUCT_RANDOM: tour_name="Random"; break;
	default: errorif(1,"Unkown start tour parameter %d\n",construction_algorithm);
		tour_name=""; /* Satisfy GCC's dataflow analysis. */
	}
	fprintf(ps_out,"(%s tour length "length_t_spec") title\n",
		tour_name,
		length_t_pcast(incumbent_len));
	fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
	for (i=0;i<n;i++) {
		const int city=tour[i], next_city=tour[(i+1)%n];
		fprintf(ps_out,"%f %f %f %f ue\n",
			tsp_instance->coord[city].x[0],
			tsp_instance->coord[city].x[1],
			tsp_instance->coord[next_city].x[0],
			tsp_instance->coord[next_city].x[1]);
	}
	fprintf(ps_out,"showpage\n");
}

@ We've used some general purpose memory allocation routines,
which in turn use some error-checking
routines.  Their interfaces are given in the following header files.

@<Early module headers@>=
#include "error.h"
#include "memory.h"

@ We also need the interface to the construction module.
@<Module headers@>=
#include "construct.h"

@ We need to declare the |tour| array.
@<Module variables@>=
static int *tour;

@ And then free it when we're done.
@<Cleanup code@>=
if ( !do_weighted_perfect_matching ) {
	if ( verbose >=50 ) printf("Cleaning initial tour\n");
	free_mem(tour);
}

@ The variable |incumbent_len| is the length of the best tour found and
committed to so far.
@<Global variables@>=
length_t incumbent_len;

@ We make it visible to the outside world.
@<Exported variables@>=
extern length_t incumbent_len;

@ Once we have a starting tour in hand, we initialize the tour ADT
implementation.

@<Construct a starting tour@>=
tour_set(tour);

@*The Lin-Kernighan algorithm.
Lin-Kernighan is a local search algorithm.  I've modeled my implementation
after that of Johnson, Bentley, McGeoch, and Rothberg, as described
in by Johnson and McGeoch in ``Local Search and the Traveling Salesman
Problem'', (INSERT REFERENCE).  The code appears in module \module{JBMR},
named in honour of Johnson \etal.

@<Run the Lin-Kernighan algorithm@>=
last_resource_mark = resource_mark("Lin-Kernighan");
if ( do_weighted_perfect_matching ) {
	match_run(3,iterations,prng_new(PRNG_DEFAULT,1998));
} else { /* Do the TSP. */
	jbmr_run(iterations,prng_new(PRNG_DEFAULT,1998));
}

@ We need the interface to modules \module{JBMR} and \module{PRNG}.

@<Module headers@>=
#include "jbmr.h"

@
@<Early module headers@>=
#include "prng.h"

@ We need to call its setup and cleanup procedures.
@<Allocate the space for this instance@>=
if ( !do_weighted_perfect_matching ) jbmr_setup(n);

@
@<Cleanup code@>=
if ( !do_weighted_perfect_matching ) {
	if ( verbose >=50 ) printf("Cleaning up jbmr structures\n");
	jbmr_cleanup();
}

@* Weighted perfect matchings.
This program also (belatedly) handles finding cheap weighted perfect
matchings.   We use the same TSPLIB inputs as before, except we interpret
them as weighted matching problem instances instead of traveling salesman
problem instances.  

Of course, we need the interface to the \module{MATCH} module.

@<Module headers@>=
#include "match.h"

@ If the instance has an odd number of vertices, then there is no
perfect matching.  

@<Read the TSP instance@>=
if ( do_weighted_perfect_matching ) {
errorif(n % 2,"Must have even number of vertices to have a perfect matching");
}

@ Except for the tour representation and the starting tour, 
all the same data structures are used.  Here are the extra bits we need.

@<Allocate...@>=
if ( do_weighted_perfect_matching ) {
	match_setup(n);
}

@
@<Cleanup code@>=
if ( do_weighted_perfect_matching ) {
	match_cleanup();
}

@
@<Construct a starting matching@>=
last_resource_mark = resource_mark("Construct starting matching");
incumbent_len = match_construct(construction_algorithm,start_heuristic_param);
if (verbose>=10) printf("Initial matching length: "length_t_spec"\n",
		length_t_pcast(incumbent_len));
@<Possibly output the starting matching as PostScript@>@;


@
@<Possibly output the starting matching as PostScript@>=
if (ps_out && tsp_instance->coord) {
	char heuristic_name[200];
	switch(construction_algorithm) {
	case CONSTRUCT_CANONICAL: sprintf(heuristic_name,"Canonical");break;
	case CONSTRUCT_GREEDY: sprintf(heuristic_name,"Greedy");break;
	case CONSTRUCT_RANDOM: sprintf(heuristic_name,"Random %ld",start_heuristic_param);break;
	default: sprintf(heuristic_name,"unknown--Bug!");
	}
	match_ps_out(ps_out,heuristic_name);
}



@ Beyond that, there are some differences in the winding down phase.



@*Winding down.
When the program has finished its work, it gives us the answer it
has computed and reports the performance of the various phases of the
execution.  It then cleans up after itself.

@<Stop the timers and print interval times@>=
last_resource_mark = resource_mark("The end");
if (verbose>=2) {
	int i;
	if ( verbose >=5 )
		for (i=0;i<last_resource_mark;i++) {
			resource_report(stdout,i,i+1);
		}
	if ( last_resource_mark > 0 ) {
		resource_report(stdout,begin_data_structures_mark,last_resource_mark);
	}
	if (verbose>=10) {
		printf("End time: ");@+@<Print the current time@>@;
		mem_report();
	}
	@<Print the machine name@>@;
}


@
@<System headers@>=
#if HAVE_SYS_PARAM_H 
#include <sys/param.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>	/* For |gethostname()| under AIX. */
#endif

@ For some reason, |MAXHOSTNAME| is not defined by the Solaris header
file \file{<sys/param.h>}, although the manual page says it should be.
In that case, we define it ourselves to be 256, which is the current
value advertised on that page.
@<Print the machine name@>=
#if HAVE_GETHOSTNAME
{
#if !defined(MAXHOSTNAMELEN)  
#define MAXHOSTNAMELEN 256    
#endif /*  |!defined(MAXHOSTNAMELEN)| */
char buf[MAXHOSTNAMELEN+1];
gethostname(buf,MAXHOSTNAMELEN);
buf[MAXHOSTNAMELEN]=0;
printf("Machine: %s\n",buf);
}
#endif /* |HAVE_GETHOSTNAME| */


@ We factor out the cleanup code into a the procedure |lk_cleanup| because
it may be called by the error checking routines.

@<Free the allocated space@>=
lk_cleanup();

@ What does |lk_cleanup| do?  It calls the cleanup routines for all the
other modules.

@<Module subroutines@>=
static void lk_cleanup(void) 
{
	@<Cleanup code@>@;
}

@ This procedure needs to be known within this compilation unit only.
@<Static prototypes@>=
static void lk_cleanup(void);

@ The error checking routine needs to know what procedure to call
to clean up.  We use a function pointer variable to do this in order
to keep the error module cleanly separated from the rest of the program.
The variable belongs to the error module, but we set it here.

@<Do basic initialization@>=
error_cleanup = lk_cleanup;

@ After an error condition and subsequent cleanup, we 
want to report the memory statistics.  This might help us detect the
problem.  Again, |error_postcleanup_stats| belongs to the \module{ERROR}
module.

@<Do basic initialization@>=
error_postcleanup_stats = mem_report;

@ We have a separate named section for the cleanup code so it can be added
to as necessary later in this file.  For now we just put in the call to
the cleanup code for the resource manager.

All this  code should be idempotent and should be able to be called before
any calls to the corresponding initialization code.  

@<Cleanup code@>=
resource_cleanup();


@
	@<Exported type definitions@>=
@
	@<Exported variables@>=
@
	@<Exported subroutines@>=

@ We should check to see that |jbmr_run| actually improved the result 
by as much as it says it did.   Of course, floating point computations
lose precision, so we only check to within a certain error tolerance.
For now, that error tolerance is half a unit.  In the future we might
allow the user to specify a tolerance.

We also make sure the tour is actually a tour.

We print the tour if the user's asked for it.  Right now it's just
the word ``Tour:'' followed by lines with up to 10 city numbers.
In the future, consider changing the code to
print it in TSPLIB's tour format, and possibly to a file.

@d my_abs(A) ((A)<0?-(A):(A))
@d within_epsilon(A,B) (my_abs(((A)-(B))) < 0.5)

@<Validate and print the result@>=
if ( do_weighted_perfect_matching ) {
	match_validate(&validate_len,&double_validate_len,&ordered_double_len,&raw_len);
} else {
	int i, c,cn;
	double *lengths = new_arr_of(double,n);
	double *raw_lengths = new_arr_of(double,n);
	double *length_t_lengths = new_arr_of(length_t,n);
	validate_len = 0;
	double_validate_len = ordered_double_len = raw_len=0.0;
	for ( i=0, c=0; i<n ; i++ ) {
		errorif( c == 0 && i > 0, "Not a tour");
		cn = tour_next(c);
		length_t_lengths[i]=cost(c,cn);
		double_validate_len += (double)length_t_lengths[i];
		lengths[i]=(double)length_t_lengths[i];
		if ( tsp_instance->edge_weight_type == EUC_2D ||
		     tsp_instance->edge_weight_type == CEIL_2D ) {
			raw_lengths[i]=cost_from_euc2d_raw(c,cn);
		} else {
			raw_lengths[i]=lengths[i];
		}
		c = cn;
	}
	sort(lengths,(unsigned)n,sizeof(double),lk_double_cmp);
	sort(raw_lengths,(unsigned)n,sizeof(double),lk_double_cmp);
	sort(length_t_lengths,(unsigned)n,sizeof(length_t),lk_length_t_cmp);
	for (i=0;i<n;i++) {
		ordered_double_len += lengths[i];
		raw_len += raw_lengths[i];
		validate_len += length_t_lengths[i];
	}
	free_mem(lengths); 
	free_mem(raw_lengths);
	free_mem(length_t_lengths);
	mem_deduct(n*(sizeof(double)+sizeof(double)+sizeof(length_t)));
	errorif( c != 0, "Not a tour");
}

@
@<Validate and print the result@>=
if (verbose>=2) {
	printf("Instance name: %s\n",tsp_instance->name);
	printf("Instance comment: %s\n",tsp_instance->comment);
}
if ( should_show_tour ) { /* ``Are ya shure?'' */
	if ( do_weighted_perfect_matching ) {
		match_show(stdout);
	} else {
		int i, c;
		printf("Tour:\n");
		for ( i=0, c=0; i<n ; i++, c=tour_next(c) ) {
			printf("%d ",(original_city_num?original_city_num[c]:c)+1);	
				/* Use 1-based convention of TSPLIB, and maybe remap. */
			if ( (i % 10) == 9 || i==n-1 ) printf("\n"); 
		}
	}	
}
if ( verbose >=2 ) printf("Length: ");
if ( verbose ) printf( noround ? "%f\n" : "%.0f\n", (double)validate_len);
if ( verbose >= 10 ) {
	printf( "\tincumbent_len       == " length_t_spec "\n" @|
			"\tvalidate_len        == " length_t_spec "\n" @|
			"\tdouble_validate_len == %f\n" @|
			"\tordered_double_len  == %f\n" @|
			"\traw_len             == %f\n" @|
			"\tdiscrepancy == (incumbent_len-ordered_double_len) == %-10g\n",
			length_t_pcast(incumbent_len),
			length_t_pcast(validate_len),
			double_validate_len, 
			ordered_double_len, 
			raw_len,
			((double)incumbent_len)-ordered_double_len );
}
errorif( !within_epsilon(((double)incumbent_len),ordered_double_len),
	"%s mistaken about improvement", 
	do_weighted_perfect_matching ?  "match_run()" : "jbmr_run()" );

@
@<|main| variables@>=
length_t validate_len;
double double_validate_len, ordered_double_len, raw_len;


@ Now let's print it to the PostScript output, if that stream is open.
@<Validate and print the result@>=
if ( ps_out ) {
	if ( do_weighted_perfect_matching ) {
		match_ps_out(ps_out,(const char *)"LK-opt");
	} else {
		int i, c,cn;
		fprintf(ps_out,"%%Here's the final tour\n");
		fprintf(ps_out,"(LK opt, tour len "length_t_spec") title\n",
			length_t_pcast(incumbent_len));
		fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
		for ( i=0, c=0; i<n ; i++, c=cn ) {
			cn = tour_next(c);
			errorif( c == 0 && i > 0, "Not a tour");
			fprintf(ps_out,"%f x %f y %f x %f y rawedge\n",
				tsp_instance->coord[cn].x[0],
				tsp_instance->coord[cn].x[1],
				tsp_instance->coord[c].x[0],
				tsp_instance->coord[c].x[1]);
		}
		fprintf(ps_out,"showpage\n");fflush(ps_out);
	}
	fprintf(ps_out,"end\ngrestore\n%%EOF\n");fclose(ps_out);
}


@
@<Subroutines@>=
int
lk_double_cmp(const void *a, const void *b)
{
	const double da=*((const double*)a), db=*((const double*)b);
	if (da<db) return -1;
	if (da>db) return +1;
	return 0;
}

int
lk_length_t_cmp(const void *a, const void *b)
{
	const length_t da=*((const length_t*)a), db=*((const length_t*)b);
	if (da<db) return -1;
	if (da>db) return +1;
	return 0;
}

@
@<Exported subroutines@>=
int lk_double_cmp(const void *a, const void *b);
int lk_length_t_cmp(const void *a, const void *b);

@
@<Test the $k$-d tree@>=
#ifdef LK_CHECK_KDTREE
if ( E2_supports(tsp_instance) ) {
int i,c,d,*done=new_arr_of(int,n), last;
	length_t last_dist, next_dist;
for (c=0; c<n;c++) {
	if (verbose) printf("%d ",c); fflush(stdout);
	for (i=0;i<n;i++) {
		done[i]=0;
	}
	done[c]=1;
	last_dist=0;
	last = c;
	for(i=0;i<n-1;i++) {
		d=E2_nn(c);
		if (0<=d && d<n ) {
			next_dist=cost(c,d);
			errorif(last_dist>next_dist,
				"NN for %d out of order: #%d %d cost="length_t_spec", "
				"#%d %d cost="length_t_spec,
				c,i-1,last,length_t_pcast(last_dist),
				i,d,length_t_pcast(next_dist));

			if  (verbose>=500) {
				printf("nn(%d) #%d = %d dist "length_t_spec"\n",c,i,d,length_t_pcast(cost(c,d)));
			}
				
			last_dist=next_dist;
			last=d;
		} else {
			printf("Invalid city %d returned on nn query %d from %d\n",
				d,i,c);
		}
		errorif(done[d],"Shouldn't return %d on nn query at %d",d,c);
		E2_hide(d);
		done[d]=1;
	}
	d = E2_nn(c);
	errorif(d!=-1,"nn(%d) returned %d when all others hidden; should be -1.\n",
			c,d);
	E2_unhide_all();
}
free_mem(done);
if (verbose) printf("\nkd tree passed an integrity test on nearest-neighbour searching\n");
}
#endif



@*Index.
