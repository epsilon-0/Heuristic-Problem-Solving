


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
$Log: match.w,v $
Revision 1.13  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.12  1998/05/18 20:33:18  neto
Added Iterated part of Iterated Lin-Kernighan.
Oddly enough, it seems that iterated lk for matching doesn't find
any better tours than ordinary lk.  I used a sequential 4-change
as the mutator, but that doesn't seem rich enough, although
*occasionally* it takes a number of tries to get back to the previous
optimal.

Revision 1.11  1998/02/13 19:34:03  neto
Removed the extraneous output.

Revision 1.10  1998/02/07  22:22:49  neto
Fixed 2 bugs:
1.  Edito: accidentally zeroing out en[two i] at start of every generic
part of search.  Ouch.
2.  Was not checking cum gain test on only t2ip1.  That's important.
3.  Had the cum pos and cum neg reversed in setting them.
This appears to work well.  Now I need to remove (or verbosize) some
debugging output.

Revision 1.9  1998/02/06  22:47:32  neto
virtual pointers should never be 0, which is NULL.

Revision 1.8  1998/02/06  21:34:51  neto
Added lots of debugging output (again!)
Fixed two bugs:
1.  Wasn't doing the bookkeeping for filling in e rows correctly.
2.  Was using the *least* attractive move first.  (Now *there*'s an idea)
Fixed that by reversing the sense of the eligible comparison function.

Revision 1.7  1998/02/06  16:39:57  neto
Much more debugging output.
Fixed bug: wasn't quitting search early enough in backtracking depths.
Fixed bug: wasn't checking (t2i,t2ip1) against (t2ip1,t2ip2) in tabu check.

Revision 1.6  1998/01/31  20:34:05  neto
First bug was: I wasn't priming the ei and en on the we back out of the
non-backtracking portion of the search.
Still crashes trying to implement an improvement of 883 in fullgrid1024

Revision 1.5  1998/01/31  20:05:40  neto
Finished coding.  now debugging.  Having problems with mates not being right.

Revision 1.4  1998/01/23  23:31:56  neto
Beginning to code match run

Revision 1.3  1998/01/23  21:04:25  neto
Matchings on n points only have n/2 lengths.  That was the cause of the
validation bug.

Revision 1.2  1998/01/23  20:41:00  neto
It compiles and runs now.  The optimization routine is a no-op.
The validation routine fails.  Doh!

Revision 1.1  1997/12/20 22:24:16  neto
Initial revision

}

\def\t#1ip#2{t_{#1i+#2}}
@s t2ip1 TeX
@s t2ip2 TeX
@s eligible_t int
% The following would be cruel...
%\def\twoxi{2i}	 
%@@s two_i TeX

@*Minimum Weight Perfect Matchings.
It would be nice if declustering worked for more than just Lin-Kernighan
on the Traveling Salesman Problem (TSP).
So I'm going to try it for minimum weighted perfect
matchings.

A \term{matching} on a graph $G=(V,E)$ is a set of edges $M$ 
contained in $E$ with the property that for all vertices $v\in V$,
at most one edge $e\in M$ is incident upon $v$.
A \term{perfect matching} for $G$ is a matching $M'$ for $G$ in which
for all 
vertices $v \in V$, there is exactly one edge in $M'$ incident upon $v$.
Now, this is only possible when the number of vertices is even;
furthermore the number of edges in a perfect matching is half the number
of vertices of the underlying graph.
@^matching@>
@^perfect matching@>
@^weighted matching@>

Now suppose each edge $e$ has an associated cost, say |cost(e)|.
Then we may make the convention that the weight of a set $E'$ of edges
is the sum of the weights of its members, \ie, $\cost(E')=
\sum_{e \in E'} \cost(e)$.
Then 
we may ask for 
a minimum-weight perfect matching.
There are polynomial time algorithms for finding optimal answers,
but here we implement a heuristic that should find good answers quickly.

We will only be considering undirected graphs, and therefore assume
that the cost function is symmetric.

@ Why weighted perfect matchings?

First, the Lin-Kernighan algorithm retains its spirit when translated from
the TSP to this setting.  The same cumulative gain criterion can be used.
I believe it has the same flaw and the same fix.

Second, the TSP is an NP-hard problem.  Its solution space is therefore
quite treacherous.  Weighted perfect matching is polytime-solvable.
In fact, 
algorithms that backtrack in to find augmenting paths
always find optimal solutions in $O(n^3)$ time or better.
In particular, this fixed search strategy shows that the solution space
is well-behaved.  So it would be nice to show that declustering might
help a Lin-Kernighan style heuristic in these well-behaved spaces as
well as in the spaces defined by NP-hard problems.

Third, as a practical matter, one would not want to run a cubic algorithm
on an instance of size 100000.  Just as with NP-hard problems, one might
prefer a good solution in a short time rather than an optimal solution
in a very long time.

Fourth, weighted perfect matchings have very local structure.  
This removes most of the tedium of coding the Lin-Kernighan heuristic.
At least, I hope it does.  We don't need the complicated case structure
of Lin-Kernighan in the context of the TSP.

@ If you are new to the Lin-Kernighan algorithm, I suggest you read
their paper first.  If you can't make heads or tails out of that, 
read Johnson and McGeoch's chapter in {\sl Local Search in Combinatorial
Optimization}, 1997.
If that too fails and you still want to understand the heuristic,
read this module before reading the \module{JBMR} module.

@ The outline of this module is as follows.

@c
#include <config.h>
#include "declevel.h"
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;@#

@<Module definitions@>@;
@<Type definitions@>@;
@<Module variables@>@;
@<Module subroutines@>@;
@<Subroutines@>@;

@* Data structures.
A matching on $n$ vertices is a set of $n/2$ edges, \ie, a pairing
of each vertex with a mate.  An array can easily handle the task.
Entry |mate[i]| is the vertex matched to vertex |i|.  
If $(u,v)$ is in the matching, then |mate[u]=v| and |mate[v]=u|.

Module-level variable |n| records the number of vertices in the graph.

@<Module variables@>=
static int *mate=NULL;
static int n=0;

@
Convenience macro |make_mates(u,v)| makes mates of |u| and |v|.

The common case for changing mates is to swap the mates of two pairs
of vertices, \ie, a 2-change.  That is implemented by convenience
procedure |swap_mates|.

@d make_mates(u,v) ((mate[(u)]=(v)),(mate[(v)]=(u)))
@d dump_core(x) ((verbose % 2) ? *(int *)0=(x) : (s_x=(x)) )

@d swap_mates(a,b,c,d) {
s_a = a;
s_b = b;
s_c = c;
s_d = d;
	if(a<0 || a>= n) dump_core(41);
	if(b<0 || b>= n) dump_core(42);
	if(c<0 || c>= n) dump_core(43);
	if(d<0 || d>= n) dump_core(44);
	if((mate[a]!=b && mate[b]!=a) || (mate[c]!=d && mate[d]!=c)) dump_core(45);
	errorif((mate[a]!=b && mate[b]!=a) || (mate[c]!=d && mate[d]!=c), 
		"swap_mates(%d,%d,%d,%d) aren't pairwise mates",a,b,c,d);
	make_mates(a,d);
	make_mates(b,c);
}

@ 
@<Module subroutines@>=
static int s_a,s_b,s_c,s_d,s_x;
static void (*prev_cleanup_fn)(void);
static 
void
dump_ds(void) 
{
int i;
printf("dumping core: %d\n",s_x);
printf("possibly swapping (%d,%d,%d,%d)\n",s_a,s_b,s_c,s_d);
for (i=0;i<n;i++) {
	printf("  mate[%d] = %d\n",i,mate[i]);
}
if (prev_cleanup_fn) prev_cleanup_fn();
}

@
@<Allocate and initialize...@>=
prev_cleanup_fn = error_precleanup_stats;
error_precleanup_stats = dump_ds;


@ Allocating the mate structure is pretty easy.
@<Subroutines@>=
void
match_setup(int the_n) 
{
errorif(the_n%2,
	"Perfect matchings require an even number of vertices; given %d\n",the_n);
n = the_n;
mate = new_arr_of(int,n);
mate[0]=-1;	/* Mark as uninitialized. */
@<Other setup code@>@;
}


@ Deallocating it is just as easy.
@<Subroutines@>=
void
match_cleanup(void) 
{
if ( mate ) { free_mem(mate); mem_deduct(n*sizeof(int)); }
@<Other cleanup code@>@;
n=0;
}

@ We export the declarations of these routines via
header file \file{match.h}.

@(match.h@>=
#include "prng.h"
@<Exported subroutines@>@;

@
@<Exported subroutines@>=
void match_setup(int n);
void match_cleanup(void);

@ We've used the memory and error handling routines.  We need their
declarations.  
While we're at it, lets get the definition of the |length_t| type.
The |cost| function is exported by the \module{READ} module. (Go figure.)
For consistency's sake, let's also import our own interface.

@<Module headers@>=
#include "error.h"
#include "memory.h"
#include "length.h"
#include "read.h"
#include "match.h"

@* Preliminaries.

Now that I've got the basic data structure foremost in my mind, let me
describe some of the simpler routines we've promised to the rest of the
world.

@*1 Output.
The first routine outputs the matching to as text to an open file stream,
one edge per line.
There are two tricks. 
First, we ensure that each edge appears only once in the output.
Second, we remap the vertex numbers back to the original naming scheme.

@d city_name(I) (1+(original_city_num ? original_city_num[I] : I))

@<Subroutines@>=
void
match_show(FILE *out)
{
	length_t weight = 0;
	int i;
	errorif(mate==NULL || mate[0]==-1,
			"Tried to print a matching before it is initialized");
	fprintf(out,"Perfect matching:\n");
	for ( i=0; i<n ; i++) {
		const int i_mate = mate[i];
		if ( i_mate > i ) {
			fprintf(out,"%d %d\n",city_name(i),city_name(i_mate));
			weight += cost(i,i_mate);
		}
	}
	fprintf(out,"Length: "length_t_spec"\n",length_t_pcast(weight));
}


@ We've used the standard input and output facilities, and the definition
of 
|NULL|.  
Let's get their declarations and definitions.

@<System headers@>=
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

@ 
The next routine outputs the matching in PostScript form.
Fortunately, the PostScript prolog has removed much of the complexity
that we might have faced.

@<Subroutines@>=
void
match_ps_out(FILE *ps_out,const char *name)
{
	length_t weight=0;
	int i;
	errorif(mate==NULL || mate[0]==-1,
			"Tried to print a matching before it is initialized");
	fprintf(ps_out,"%%Here's a weighted perfect matching\n");
	for ( i=0; i<n ; i++) {
		const int i_mate = mate[i];
		if ( i_mate > i ) { /* Write a pair exactly once. */
			weight += cost(i,i_mate);
			fprintf(ps_out,"%f x %f y %f x %f y rawedge\n",
				tsp_instance->coord[i].x[0],
				tsp_instance->coord[i].x[1],
				tsp_instance->coord[i_mate].x[0],
				tsp_instance->coord[i_mate].x[1]);
		}
	}

	fprintf(ps_out,"(%s matching, weight "length_t_spec") title\n",
		name, length_t_pcast(weight));
	fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
	fprintf(ps_out,"showpage\n");fflush(ps_out);
}

@
@<Exported subroutines@>=
void match_show(FILE *out);
void match_ps_out(FILE *ps_out,const char *name);

@*1 Validation.
Validating a matching involves checking the integrity of the data
structure and checking the arithmetic.

If the length type is a floating point type,
we may have lost precision along the way.
We add up the weights
several different ways to see if that has happened.

@<Subroutines@>=
void
match_validate(length_t *validate_len,double *double_validate_len,
double *ordered_double_len,double *raw_len)
{
	length_t my_validate_len=0;
	double my_double_validate_len=0, my_ordered_double_len=0, my_raw_len=0;
	double *length=new_arr_of(double,n/2);
	double *raw_length=new_arr_of(double,n/2);
	double *length_t_length=new_arr_of(length_t,n/2);

	int i, w;
	errorif(mate==NULL || mate[0]==-1,
			"Tried to validate a matching before it is initialized");

	@<Validate the data structure@>@;

	for ( i=0, w=0; i<n ; i++) {
		const int i_mate = mate[i];
		if ( i_mate > i ) { /* Examine a pair exactly once. */
			length_t_length[w] = cost(i,i_mate);
			length[w] = (double)length_t_length[w];
			my_double_validate_len += length[w];
			switch ( tsp_instance->edge_weight_type ) {
			case EUC_2D:
			case CEIL_2D:
				raw_length[w] = cost_from_euc2d_raw(i,i_mate);
				break;
			default: raw_length[w] = length[w];
			}
			w++;
		}
	}
	@<Add the lengths in a numerically nice way@>@;
	free_mem(length);
	free_mem(raw_length);
	free_mem(length_t_length);
	*validate_len = my_validate_len;
	*double_validate_len = my_double_validate_len;
	*ordered_double_len =  my_ordered_double_len;
	*raw_len=my_raw_len;
}
@
@<Exported subroutines@>=
void
match_validate(length_t *validate_len,double *double_validate_len,
double *ordered_double_len,double *raw_len);


@
@<Validate the data structure@>=
{
int i, *visited=new_arr_of_zero(int,n);
for ( i=0;i<n;i++) {
	const int i_mate = mate[i];
	errorif(i_mate < 0 || i_mate >= n,
			"Mate of %d is %d, out of range\n",i_mate);
	visited[i]++; 
	visited[i_mate]++;
}
for ( i=0;i<n;i++ ) {
	errorif(visited[i] != 2,"Vertex %d visited %d times, not 2 times",i,visited[i]);
}

free_mem(visited);
}


@ Assuming all the numbers are non-negative, it is  usually better
to add them up from smallest magnitude to largest magnitude.
If you want more detail, ask a numerical analyst.

@<Add the lengths in a numerically nice way@>=
sort(length,(unsigned)n/2,sizeof(double),lk_double_cmp);
sort(raw_length,(unsigned)n/2,sizeof(double),lk_double_cmp);
sort(length_t_length,(unsigned)n/2,sizeof(length_t),lk_length_t_cmp);
my_validate_len = 0;
my_ordered_double_len = my_raw_len=0.0;
for (i=0;i<n/2;i++) {
	my_validate_len += length_t_length[i];
	my_ordered_double_len += length[i];
	my_raw_len += raw_length[i];
}

@ We've used the function pointer |sort| and the comparison functions 
|lk_double_cmp| and |lk_length_t_cmp|. All three are defined by 
module \module{LK}.
@<Module headers@>=
#include "lk.h"


@*1 Construction.
Local optimzation algorithms require a starting point.  
Procedure
|match_construct| builds a perfect matching.
Since the \module{CONSTRUCT} already has much machinery in place,
and the mate data structure is so trivial, 
I offload the construction duty to the |construct_matching| in that module.
Cute, huh?

The routine returns the total weight of the matching.


@<Subroutines@>=
length_t 
match_construct(int alg,long alg_param) 
{
	errorif(mate==NULL,
			"Tried to construct a matching before space is allocated");
	return construct_matching(n,mate,alg,alg_param);
}

@
@<Exported subroutines@>=
length_t match_construct(int alg,long alg_param);


@ We need the interface of module \module{CONSTRUCT}.
@<Module headers@>=
#include "construct.h"

@* Lin-Kernighan for weighted matching.
This routine implements the Lin-Kernighan idea for minimum weight perfect 
matching.  It is a local search routine that repeatedly tries to find
improvements known as $k$-changes.  A $k$ change is the removal of $k$
edges and the addition of $k$ edges.

The $k$-changes sought by Lin-Kernighan are of a special nature.
The edges involved the $k$-change form an even-length cycle, where deleted
edges alternate with added edges.
We label the vertices involved in the $k$-change
$t[1]$ through $t[2k]$, where $(t[1],t[2])$ is the first edge removed from the
current matching, and $(t[2],t[3])$ is the first edge added to the matching.
Lin and Kernighan called such a structure a \term{sequential $k$-change}
because one may construct it incrementally from $t[1]$ on upward.

@ It will be convenient to represent |t| as an array.  
In this implementation of Lin-Kernighan, the list will never grow beyond
entry |t[n]|, so we allocate |n+1| cells for |t|, labelled 0 through |n|.

@<Module variables@>=
int *t;

@
@<Other setup code@>=
t = new_arr_of(int,n+1);

@
@<Other cleanup code@>=
if(t){free_mem(t);mem_deduct(sizeof(int)*(n+1));}

@
We keep track of how far the |t| list has been filled in with 
the variable |two_i|.  This is in keeping with the notation originally
used
by  Lin and Kernighan in the description of their algorithm, and
is a symbolic spelling-out  of $2i$.
More precisely, the current |t| list is recorded in 
cells |t[1]| through |t[two_i]|.  (As the name implies, |two_i| is always
even.)

@<|match_run| variables@>=
int two_i;


@ An improving sequential $k$-change is one in which the deleted edges outweigh
the added edges.
Lin and Kernighan observed that without loss of generality, one 
may restrict the search to those in which the \term{cumulative gain criterion}
applies, \ie, in any prefix of the $t$ array, the deleted edges outweigh 
the added edges.

We define the \term{cumulative gain} to be the total weight of the deleted
edges minus the total weight of the deleted edges.
If the |length_t| length type is an exact representation, then the 
cumulative gain is stored directly in the variable |cum_gain|,
\ie $$\hbox{|cum_gain|}= 
\sum_{1 \le s < 2i, s {\rm\ odd}}
\cost(t[s],t[s+1])%
-
\sum_{1 \le s < 2i, s {\rm\ even}} 
\cost(t[s],t[s+1])%
.$$
The first sum is the weight of the deleted edges;
the second sum is the weight of the added edges.

Unfortunately, we sometimes have to deal with inexact representations
for numbers, \eg,
types |float| or |double|.  In those cases it turns out that it is better
to store the positive and negative parts separately.  
Variable |cum_gain_pos|
records the weight of the deleted edges, and |cum_gain_neg| 
records the weight of the added edges.


@<|match_run| variables@>=
#if SPLIT_GAIN_VAR
length_t cum_gain_pos, cum_gain_neg;
#else
length_t cum_gain;
#endif


@ We split the gain variable if the length type is inexact.  That knowledge
is exported from the \module{LENGTH} module.

@<Module definitions@>=
#define SPLIT_GAIN_VAR (!(LENGTH_TYPE_IS_EXACT))



@ In keeping with the theme of being careful about numerics, let's define
a generic comparison macro that adjusts to both the exact and inexact cases.
Macro |CAREFUL_CMP(LHS,OP,RHS)| compares the left hand side |LHS| with
the right hand side |RHS| using arithmetic operator |OP| and evaluates
to a boolean value.

We use ANSI C's token pasting operator |##| to automagically transform 
the variable names in the left and right-hand sides appropriately.   This
forces all uses of the macro to use variable names only for the two sides
of the comparison.

Furthermore, we'll be using the concept of an \term{instance epsilon} to
protect against other numerical nasties.   If we're using exact
representations, then the value of the right-hand side should just a
variable name.  If we're using inexact representations, then the same
value with a slop factor should be in an identically named variable with
a suffix of |_with_slop|.
@^numerical nasties@>

So, for example, if the length type is |double|, an inexact
type, then |SPLIT_GAIN_VAR| is true and
$$\hbox{|@[CAREFUL_OP(cum_gain,<,best_gain)@]|}$$ translates into
$$\hbox{|((cum_gain_pos)<(best_gain_with_slop+cum_gain_neg))|.}$$


@<Module definitions@>=
#if !SPLIT_GAIN_VAR
#define CAREFUL_OP(LHS,OP,RHS) ((LHS) OP (RHS))
#else
#define CAREFUL_OP(LHS,OP,RHS) ((LHS##_pos) OP (RHS##_with_slop + LHS##_neg))
#endif

@ While building the |t| list, we keep track of the best improvement found so
far in the search, if any.  The best improvement is the one with the greatest
gain.  We record the value of the best gain in the variable |best_gain|.

Now, the best gain in the matching might be at any point in the search, so
we must record the position in the |t| array where it happened.  
Variables |best_two_i|, |best_exit_a|, and
|best_exit_b| are defined by the following invariant:
{\medskip\leftskip=0.75in\rightskip=0.75in\noindent
The gain recorded in |best_gain| is put into effect
by the changes encoded in |t[1]| through |t[best_two_i]|, followed
by the two cities |best_exit_a|, |best_exit_b|.\medskip}

In particular, |best_two_i| is even and bounded above by |two_i|.
If no improvement has been found, then |best_two_i| is zero.
This is more reliable than testing the length |best_gain| against zero,
again because of numerical nasties.
@^numerical nasties@>

Note that |best_exit_a| and |best_exit_b| are not necessarily the same
as |t[best_two_i+1]| and
|t[best_two_i+2]|.  That is, the search may have explored a path different
from the one in which the best improvement was discovered.  But it is always
the case that the best improvement is at most a single pair away from
the path explored.

@<|match_run| variables@>=
length_t best_gain;
int best_two_i, best_exit_a, best_exit_b;

@
@<Initialize per-search bookkeeping variables@>=
best_gain = 0;
best_two_i = 0;
best_exit_a = best_exit_b = INT_MAX;  /* Wacked-out value. */

@
@<System headers@>=
#include <limits.h>

@ In making the length comparisons, we also record the value of the best
gain with a little extra slop.  That is, variable |best_gain_with_slop|
is the value of 
$\hbox{|best_gain|} + \varepsilon \times \hbox{|incumbent_len|}$ 
where $\varepsilon$
is something close to machine epsilon and |incumbent_len| is the weight
of the current best perfect matching.  
I store the current value of
$\varepsilon \times \hbox{|incumbent_len|}$ in variable |instance_epsilon|.

@<|match_run| variables@>=
#if !LENGTH_TYPE_IS_EXACT
length_t best_gain_with_slop;
length_t instance_epsilon;
#endif

@ We'll be reseting the instance epsilon every time we find an improvement,
so separate that initialization out into its own section.

@<Set the instance epsilon slop value@>=
#if !LENGTH_TYPE_IS_EXACT
instance_epsilon = incumbent_len * LENGTH_MACHINE_EPSILON;
#endif

@
@<Allocate...@>=
@<Set the instance epsilon slop value@>@;

@
@<Initialize per-search bookkeeping variables@>=
#if SPLIT_GAIN_VAR
best_gain_with_slop = instance_epsilon;
#endif



@*1 Backtracking.
Successful application of the Lin-Kernighan variable-depth idea demands
that we backtrack when no improvement is found.  For example, if a search
beginning with a particular quadruple $(t[1],t[2],t[3],t[4])$ yeilds no
improvement, then we substitute some other pair 
in place of $t[3]$ and $t[4]$ and try again.  
@^backtracking@>

The best implementations of Lin-Kernighan for the TSP backtrack over all
possibilities up to $t[6]$ and occasionally over some possibilities for 
up to $t[8]$.  But the constraints of maintaining a tour, or something
close to a tour, makes the case analysis quite involved and error-prone.
That difficulty translates into the code, where the depth of backtracking
is usually hardcoded.

In the case of perfect matchings, the changes are localized enough that 
the case analysis is obviated: all the cases are regular.  So we can afford
to encode the backtracking in a generic way, and allow the caller to
specify the depth of the backtracking.  The parameter |backtracking_levels|
records an integer specifying which is the last position in the |t| 
at which to perform backtracking.  Specifically, we backtrack over all
possibilities for $t[2j+1]$ whenever $1 \le j \le \hbox{|backtracking_levels|}$.
Note that a value of zero for |backtracking_levels| specifies that no
backtracking should be done at all.

@*1 Basic moves.
A sequential $k$-change is built by appending pairs of vertices to the 
|t| array.  The current end of the |t| 
list is indicated by the value of variable |two_i|, which is always even
and at least 2.  That is, edges 
$(t[1],t[2]), (t[3],t[4]), \ldots, 
(t[2i-1],t[2i])$ are deleted edges, and
$(t[2],t[3]), (t[4],t[5]), \ldots, 
(t[2i-2],t[2i-1])$ are added edges.

Given a candidate for |t[2i+1]|, |t[2i+2]| is determined; in fact 
|t[2i+2]| is always the current mate of
|t[2i+1]|.  
The cumulative gain criterion says we 
can add the pair of |t[2i+1]| and |t[2i+2]| to the |t| list
if the current cumulative gain plus 
|-cost(t[2i],t[2i+1]) + cost(t[2i+1],t[2i+2])| is positive.


@*1 Greedy choice.
Given a list of candiates for |t[2i+1]| (and their mates), Lin-Kernighan
prioritizes them according to which gives the greatest gain (or least
reduction) in the cumulative gain.  To make prioritization convenient,
we storing the pairs with their auxiliary information
in an array and sorting them before choosing to explore any of them.

Type |eligible_t| records the candidate pair of vertices
in fields |t2ip1| and |t2ip2|.  
The cumulative gain resulting from the choice of using |t2ip1| and |t2ip2|
as $t[2i+1]$ and $t[2i+2]$ is recorded in field |gain| (or
the pair |gain_pos|, |gain_neg| if the gain variables are split).

In |gain_1| (or |gain_1_pos| and |gain_1_neg|), we 
record the gain after adding only |t2ip1| to the list.

Field |cluster_distance| is the cluster distance between |t[1]| and |t2ip2|.
It is only used when the declustering feature is turned on.

To compare eligible moves, it is convenient to boil the gain down into one 
field the value of the gain, regardless of whether the gain variables are
split.  That field is |gain_for_comparison|.

(Note that module \module{JBMR} has its own version of type |eligible_t|,
which has the extra complication of recording the case analysis scheme
required by that eligible move.    We don't need that here because the
perfect matching cases are all uniform.)

@d USE_DECLUSTER (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
)

@<Type definitions@>=
typedef struct {
	length_t gain_for_comparison;
	length_t cluster_distance;
#if SPLIT_GAIN_VAR
	length_t gain_1_pos, gain_1_neg;
	length_t gain_pos, gain_neg;
#else
	length_t gain_1;
	length_t gain;
#endif
	int t2ip1, t2ip2;
	int two_i;
} eligible_t;

@ To save time, we preallocate all the 
eligible move cells in the two-dimensional
array |e|.  Entry |e[l][j]| is the $j$'th eligible move from $t[l]$
\ie, it encodes a move choosing $t[l+1]$ and $t[l+2]$.
Beware that |l| tracks the value of |two_i| and hence will only ever
be even and positive.

Given a choice for |t[2i]|, the candidates for |t[2i+1]| are taken
from a list of those vertices close to |t[2i]|.  The candidate lists
are precomputed by routines in module \module{NN}.  Here we need to
know the maximum length of any candidate list, because that is an upper
bound on the width of the backtracking at any one level.
That value is recorded in the variable |nn_max_bound| exported by that
module.

Now, some of the moves might not meet the cumulative gain criterion.
So we might not always fill the |e[b]| row.  Value |en[l]| records
the number of eligible moves in row |e[l]|.  Furthermore, value |ei[l]|
records where in row |e[l]| we are currently searching.  In particular,
|0 \le ei[l] < en[l]| for all $2 \le l < 2\times\hbox{|backtracking_levels|}$.

@<|match_run| variables@>=
eligible_t **e;
int *en, *ei;

@
@<Module headers@>=
#include "nn.h"

@
@<Allocate and initialize |match_run| structures@>=
{int l;
e  = new_arr_of(eligible_t*,1+2*backtracking_levels);
en = new_arr_of(int,1+2*backtracking_levels);
ei = new_arr_of(int,1+2*backtracking_levels);
for (l=2;l<=2*backtracking_levels;l+=2)
	e[l]=new_arr_of(eligible_t,nn_max_bound);
}
		
@
@<Clean up |match_run| structures@>=
{int l;
for (l=2;l<=2*backtracking_levels;l+=2) {
	free_mem(e[l]);
	mem_deduct(sizeof(eligible_t)*nn_max_bound);
}
free_mem(e);mem_deduct(sizeof(eligible_t*)*(1+2*backtracking_levels));
free_mem(en);mem_deduct(sizeof(int)*(1+2*backtracking_levels));
free_mem(ei);mem_deduct(sizeof(int)*(1+2*backtracking_levels));
}



@ Here's the outline of the Lin-Kernighan optimization routine for
perfect matchings.

We implement Iterated Lin-Kernighan.  The number of times to iterate
is passed in as a parameter, $iterations$.

Initially, all vertices are marked as dirty.
If no improvement is discovered with a search starting at
$t[1]$, then $t[1]$ is marked as clean.
If an improvement is found, then all the affected nodes are marked as dirty.

@<Subroutines@>=
void match_run(const int backtracking_levels,const int iterations, 
prng_t *random_stream)
{
	int iteration;
	@<|match_run| variables@>@;
	dict_t *dirty_set=dict_create(cmp_virtual_char,prn_virtual_char);
	char *dirty_pointer;
	@<Make all vertices dirty@>@;

	@<Allocate and initialize |match_run| structures@>@;
	for ( iteration=0; iteration < iterations ; iteration++ ) {
		while( (dirty_pointer = dict_delete_any(dirty_set,NULL))!=NULL ) {
			t[1] = dirty_pointer-VIRTUAL_BASE;
			t[2] = mate[t[1]];
			two_i=2;
			@<Initialize per-search bookkeeping variables@>@;
			@<Search from |t[two_i]|@>@;
			if ( best_two_i ) { @<Clean up the improvement and record it@>@; }
		}
		@<Verbose: report end of LK step@>@;
		@<Revert to the previous solution if it was better@>@;
		@<If doing another iteration, perturb by a 4-change@>@;
	}
	@<Verbose: report termination of LK phase@>@;
	@<Clean up |match_run| structures@>@;
}

@
@<Exported subroutines@>=
void match_run(const int backtracking_levels,const int iterations, 
prng_t *random_stream);

@
@<Module headers@>=
#include "dict.h"
#include "prng.h"

@ The initial cumulative gain is just the weight of the deleted edge.
@<Initialize per-search bookkeeping variables@>=
#if SPLIT_GAIN_VAR
cum_gain_pos = cost(t[1],t[2]);
cum_gain_neg = 0;
#else
cum_gain = cost(t[1],t[2]);
#endif

@ Instead of allocating a whole bunch of memory for the dirty set, I'll
just use a virtual pointer.  That is, the pointer stored in the
dictionary stores all the necessary information in its value, 
and it doesn't actually
point to anything.  This is safe because the pointer is never dereferenced.

In this case, the virtual pointers are just character offsets from byte 42.
@^virtual pointer@>

The comparison function just subtracts the pointer values.  The semantics
of \CEE/ take care of the scaling.

The printing function prints the offset.

@d VIRTUAL_BASE ((char *)42)

@<Module subroutines@>=
static int cmp_virtual_char(const void *a, const void *b);
static int 
cmp_virtual_char(const void *a, const void *b) 
{
	return (const char *)a - (const char *)b;
}

static void prn_virtual_char(void *a);
static void 
prn_virtual_char(void *a) 
{
	printf("%d",(const char *)a-VIRTUAL_BASE);
}

@ To mark all the vertices as dirty, we just insert a representative
virtual pointer into the dictionary for each vertex.

@<Make all vertices dirty@>=
{
	int i;
	for (i=0;i<n;i++) {
		dict_insert(dirty_set,VIRTUAL_BASE + i);
	}
}

@ Any city involved in an improving $k$-change is marked as dirty.
@<Make the |t[1]| through |t[best_two_i]| and |best_exit_a| and |best_exit_b| dirty@>=
{int i;
for ( i=1;i<=best_two_i ; i++ ) {
	dict_insert(dirty_set,VIRTUAL_BASE+t[i]);
}
dict_insert(dirty_set,VIRTUAL_BASE+best_exit_a);
dict_insert(dirty_set,VIRTUAL_BASE+best_exit_b);
}

@ In searching from |t[two_i]|, the first thing we need to know is if we
should be going deeper at this point.   A few things can terminate the
search: first, there are no eligible moves, second, ther

@ There are two cases when searching from |t[two_i]|.
If we're still in backtracking territory, then we fill a row of the eligible
moves array |e|, and then pick the best path, saving the others in case the
current path doesn't pan out.
Otherwise, we just pick the best path.

Variable |keep_going| is true if we should keep searching, namely
if we haven't found an improvement and if we haven't exhausted the
backtracking possibilities.

Let us define the convention that before row $j$ of |e| has been
filled in, we have |ei[j]==-2| and |en[j]==-1|.  This sentinel-like
convention simplifies the row-filling code a bit.

@<Search from |t[two_i]|@>=
@<Verbose: start new search@>@;
ei[two_i] = -2;  /* Prime the row-filling. */
en[two_i] = -1;
{keep_going=1;
while ( keep_going ) {
	if ( two_i <= 2*backtracking_levels ) {
		if ( ei[two_i] == -2 ) { 
			@<Fill in row |two_i| of |e|@> 
		}
		if ( ei[two_i] < en[two_i] ) {
			const eligible_t *e_entry = e[two_i]+ei[two_i];
			@<Verbose: backtracking deeper@>@;
			ei[two_i]++;
			@<Go deeper via |e_entry|@>@;
		} else if ( best_two_i ) { keep_going = 0; }
		else { @<Back up one move@>@; }
	} else {
		@<Verbose: generic deeper@>@;
		@<Go deeper via best among pairs from |t[two_i]|, if possible@>@;
	}
}
}

@
@<|match_run| variables@>=
int keep_going;

@ Here's where we determine which 2-changes are candidates for searching.
That is, we record in |e[two_i]| the list of candidates for $t[2i+1]$ and
$t[2i+2]$.  In the perfect matching problem, 
all choices for $t[2i+1]$ are feasible (subject to tabu constraints), and 
$t[2i+2]$ is always the 
current mate
of $t[2i+1]$.   

@<Fill in row |two_i| of |e|@>=
{ int j, num_candidates, *candidates;
candidates = nn_list(t[two_i],&num_candidates);
for ( en[two_i]=j=0; j<num_candidates; j++ ) {
	const int t2ip1 = candidates[j], t2ip2 = mate[t2ip1];
	eligible_t *e_entry = &e[two_i][en[two_i]];
	@<|continue| if |t2ip1| and |t2ip2| are tabu@>@;
	@<Fill in |*e_entry|@>@;
	@<|continue| if |e_entry| fails the cumulative gain test@>@;
@<Verbose: accept |e_entry| as candidate@>@;
	@<See if |e_entry| makes the best matching so far@>@;
	en[two_i]++;
}
@<Sort row |two_i| of |e|@>@;
ei[two_i]=0;
}

@ Let's also prime the {\it next\/} row for filling.
@<Fill in row |two_i| of |e|@>=
if ( two_i < 2*backtracking_levels ) {
	ei[two_i+2]=-2;
	en[two_i+2]=-1; 
}


@ To prevent endless cycling, Lin and Kernighan used two rules:
$$\hbox{Never delete an added edge}$$
and
$$\hbox{Never add a deleted edge.}$$

In their recent experiments,
Johnson, Bentley, McGeoch, and Rothberg keep the first rule and
discard the second;
the first rule alone is sufficient to limit the
search to a depth of roughly $n$ steps.  

In Papadimitriou's proof of the PLS-completeness of Lin-Kernighan for
the TSP, he discards the first rule and keeps the second; the second
rule alone is sufficient to limit the search to a depth of $O(n^2)$ steps.
I know of no implementations of Lin-Kernighan for the TSP that use only
the second rule.

I call the first rule the JBMR tabu rule, and I call the the second rule
the Papadimitriou rule.

For consistency with the \module{JBMR} module, I implement the JBMR rule.
In the perfect matching case it would be easy to implement the Papadimitriou
rule instead (or as well).  

In more concrete terms, the JBMR rule says that see that 
edge $(t2ip1,t2ip2)$ does not appear as $(t[2k],t[2k+1])$ anywhere on
the current list, nor as the proposed new edge
$(t[two_i],t2ip1)$.  All these edges are taken
to be undirected.  

Since the overwhelming majority of searches are shallow, I use a linear
time low-overhead tabu check instead of a more elaborate logarithmic time
check.  

Now that I've written the code, I see that a targeted |continue| (as in Java),
or even Scheme-style continuations would be really handy here.

@<|continue| if |t2ip1| and |t2ip2| are tabu@>=
{
int j, tabu=0;
if ( t2ip2 == t[two_i] ) { @<Verbose: tabu@>@; continue; }
for ( j=2; j<two_i; j+=2 )  {
	if ((t2ip1 == t[j] && t2ip2 ==t[j+1]) 
		|| (t2ip1 == t[j+1] && t2ip2 ==t[j])) {tabu = 1; break;}
}
if (tabu) { @<Verbose: tabu@>@; continue; }
}


@  The cluster distance is used both in the cumulative gain criterion
and in the prioritization of possible moves from |t[two_i]|. So we record
it along with the other gain statistics.

@<Fill in |*e_entry|@>=
{
	const length_t this_neg = cost(t[two_i],t2ip1),
		this_pos = cost(t2ip1,t2ip2), this_net=this_pos-this_neg;

	e_entry->t2ip1 = t2ip1;
	e_entry->t2ip2 = t2ip2;
#if SPLIT_GAIN_VAR
	e_entry->gain_1_neg = cum_gain_neg + this_neg;
	e_entry->gain_1_pos = cum_gain_pos;
	e_entry->gain_neg = cum_gain_neg + this_neg;
	e_entry->gain_pos = cum_gain_pos + this_pos;
#else
	e_entry->gain_1 = cum_gain - this_neg;
	e_entry->gain = cum_gain + this_net;
#endif
#if USE_DECLUSTER
	e_entry->cluster_distance = decluster_d(t[1],t2ip2);
	e_entry->gain_for_comparison = this_net-e_entry->cluster_distance;
#else
	e_entry->gain_for_comparison = this_net;
#endif
	e_entry->two_i=two_i;
}

@ We need a declaration of |decluster_d|.
@<Module headers@>=
#include "decluster.h"

@ The new cumulative gain must be positive in order for |e_entry| to
be accepted.  The only wrinkle here is the conditionally compiled 
discounting of 
the cluster distance.

@<|continue| if |e_entry| fails the cumulative gain test@>=
{
const length_t cluster_dist=(USE_DECLUSTER ? e_entry->cluster_distance : 0);
if ( @[CAREFUL_OP(e_entry->gain,<=,cluster_dist + best_gain)@] 
   ||@[CAREFUL_OP(e_entry->gain_1,<=,best_gain)@] ) { 
	@<Verbose: fail cumulative gain test@>@;
	continue; 
}
}


@ Now we consider |e_entry| as a termination of the search.
We calculate the cost of matching up the loose ends |t[1]| and |t2ip2|.
If it makes the best perfect matching so far, then we update |best_gain|
and its associated variables.

Note that updating |best_gain| on the fly narrows the search, even
within the same row of |e|, by strengthening
the cumulative gain test.

Even though we have found an improvement, we continue searching because
there might be an even better one down the road.

@<See if |e_entry| makes the best matching so far@>=
{ 
#if SPLIT_GAIN_VAR
const length_t possible_best_gain_pos = e_entry->gain_pos,
possible_best_gain_neg = e_entry->gain_neg + cost(t[1],e_entry->t2ip2);
#else
const length_t possible_best_gain = e_entry->gain - cost(t[1],e_entry->t2ip2);
#endif

if ( @[CAREFUL_OP(possible_best_gain,>,best_gain)@] ) { /* We have a winner! */
	best_two_i = two_i;
	best_exit_a = t2ip1;
	best_exit_b = t2ip2;
#if SPLIT_GAIN_VAR
	best_gain = possible_best_gain_pos - possible_best_gain_neg;
#else
	best_gain = possible_best_gain;
#endif
#if !LENGTH_TYPE_IS_EXACT
	best_gain_with_slop = best_gain + instance_epsilon;
#endif
	@<Verbose: announce details of improvement@>
}
}

@ We examine first those 
moves effecting the greatest increase (or least decrease)
in the cumulative gain.

@<Sort row |two_i| of |e|@>=
sort(e[two_i],(size_t)en[two_i],sizeof(eligible_t),cmp_eligible);

@ The comparison function just uses the |gain_for_comparison| entries
of the structures, which were constructed just for this purpose.
But the greatest gain should come first, so the result of the sign
test is used in the opposite way to usual.

@<Module subroutines@>=
static int cmp_eligible(const void *a, const void *b);
static int 
cmp_eligible(const void *a, const void *b) 
{
	const eligible_t *ea = (const eligible_t *)a;
	const eligible_t *eb = (const eligible_t *)b;
	length_t diff = ea->gain_for_comparison - eb->gain_for_comparison;
	return diff < 0 ? 1 : (diff > 0 ? -1 : 0);
}

@ Ok, now that most of the bookkeeping is done, we're ready to see how
it goes into action.  
Our job here is to put into action the move defined by |e_entry|.
We append the pair |t2ip1| and |t2ip2|, swap the ends of two edges in
the matching, 
update the
cumulative gain variable, and incremente |two_i|.

@<Go deeper via |e_entry|@>=
@<Verbose: accept |e_entry| as doing move@>@;
#if SPLIT_GAIN_VAR
cum_gain_pos = e_entry->gain_pos;
cum_gain_neg = e_entry->gain_neg;
#else
cum_gain = e_entry->gain;
#endif
if (e_entry->two_i != two_i ) dump_core(96);

t[two_i+1] = e_entry->t2ip1;
t[two_i+2] = e_entry->t2ip2;
swap_mates(t[1],t[two_i],t[two_i+1],t[two_i+2]);
two_i += 2;
@<Verbose: do one move@>@;
@<Verbose: show |t| after move@>@;

@  To back up, we must undo the mating changes that were done when
going down that search path.

@<Back up one move@>=
if ( two_i > 2 ) {
	if ( two_i <= 2*backtracking_levels ) {
		ei[two_i]=-2; /* Prime the row-filling. */
		en[two_i]=-1; 
	}
	two_i -= 2;
	@<Verbose: undo one move@>@;
	swap_mates(t[1],t[two_i+2],t[two_i+1],t[two_i]);
	@<Verbose: show |t| after move@>@;
} else keep_going = 0;  /* We've reached the end of backtracking. */



@ Sometimes Lin-Kernighan gets caught and goes way too deep.  The user
can excercise a command-line option to limit the depth of the search.
That bound is encapsulated in
|max_two_i|.

If we haven't hit the depth limit, then we put into effect the
move with the best cumulative gain, if it passes all the eligibility
tests.  But there might not be any eligible moves.  
If there were eligible moves, then we set |none_eligible| to zero.

@<Go deeper via best among pairs from |t[two_i]|, if possible@>=
{ int none_eligible=1;
if ( two_i <= max_two_i ) {
	@<Go deeper via best among pairs from |t[two_i]|, if eligible@>@;
} 
if ( none_eligible ) {
	if ( best_two_i == 0 )
		while ( two_i > 2*backtracking_levels ) { @<Back up one move@> }
	else { keep_going = 0; }
}
}

@ The maximum search depth has two components: the depth of the backtracking
and the depth of the post-backtracking search.

@<|match_run| variables@>=
const int max_two_i = 
(max_generic_flips == INT_MAX ? INT_MAX : 2*(backtracking_levels + max_generic_flips));

@ When we get beyond the backtracking depth, we implement a pure greedy
search.  It is simpler than in the backtracking phase because we don't need
to precompute or remember the possible moves.  We just follow the move
with the greatest cumulative gain (or least cumulative loss).
Again, when declustering is used, it figures in the greedy choice.

Fortunately, we get to reuse much of the bookkeeping code from the backtracking
phase.  I love CWEB.

@<Go deeper via best among pairs from |t[two_i]|, if eligible@>=
{ 
eligible_t best_move;
int j, num_candidates, *candidates=nn_list(t[two_i],&num_candidates);
for ( j=0; j<num_candidates; j++ ) {
	const int t2ip1 = candidates[j], t2ip2 = mate[t2ip1];
	eligible_t trial_move, *e_entry = &trial_move;  /* A hack. */
	@<|continue| if |t2ip1| and |t2ip2| are tabu@>@;
	@<Fill in |*e_entry|@>@;
	@<|continue| if |e_entry| fails the cumulative gain test@>@;
	@<See if |e_entry| makes the best matching so far@>@;
@<Verbose: accept |e_entry| as candidate@>@;
	if ( none_eligible || best_move.gain_for_comparison < trial_move.gain_for_comparison ) {
		none_eligible = 0;
		best_move = trial_move;
@<Verbose: accept |e_entry| as best move@>@;
	}
}
if ( !none_eligible ) { eligible_t *e_entry=  &best_move;
			@<Go deeper via |e_entry|@>@;
}
}

@ There are two reasons for we stopping the search from |t[2]|.
First, we've exhausted the possibilities without finding an improvement.
In that case, we've already undone all the moves, and we've nothing left
to do.

Second, we have found an improvement to the perfect matching.  
That's what this section is about.  It unwinds the changes from the search
down to the level where the best improvement was discovered, and implements
the last offshoot in that improvement.  (Actually, we might be undoing
the offshoot and then reimplementing the offshoot again, but 
checking whether that has happened is more difficult than just redoing
the work, especially because the mate data structure is so trivial.)
Finally, we update the bookkeeping variables.

@<Clean up the improvement and record it@>=
while ( best_two_i < two_i ) { @<Back up one move@> }
@<Verbose: show improvement change@>@;
swap_mates(t[1],t[best_two_i],best_exit_a,best_exit_b);
@<Log the changes recorded in |t[1],\ldots,t[best_two_i],best_exit_a,best_exit_b|@>@;
@<Make the |t[1]| through |t[best_two_i]| and |best_exit_a| and |best_exit_b| dirty@>@;
@<Verbose: show |t| after improvement@>@;
incumbent_len -= best_gain;
@<Verbose: announce improvement@>@;
@<Set the instance epsilon slop value@>@;

@*Iterated Lin-Kernighan.
In order to be able to revert to a previous solution, we either record
the previous solution in its entirety or just the differences between
solutions.  I choose to record just the differences.

The log is an array of integers, formatted as follows.  The log
contains an encoding of all the $\lambda$-changes applied during this iteration,
in order from first $\lambda$-change to last $\lambda$-change.  Each $\lambda$-change
is encoded as the values $t[1]$ through $t[best_two_i]$, followed by
|best_exit_a|, |best_exit_b|, and then finally |2+best_two_i|.  We need
this last value so we can find the boundary of the record of
this $\lambda$-change while
unrolling the changes.

But we only record those differences if there is something to revert
back to, \ie, only if this is not the first iteration.


@d write_log(A) (change_log[change_log_next++]=(A))

@<Log the changes recorded in |t[1],\ldots,t[best_two_i],best_exit_a,best_exit_b|@>=
if (iteration > 0 ) {
	const int more_log = 3+best_two_i;
	@<Make sure |change_log| has space for |more_log| more integers@>@;
	{ int j;
		for ( j=1;j<=best_two_i; j++) {
			write_log(t[j]);
		}
	}
	write_log(best_exit_a);
	write_log(best_exit_b);
	write_log(2+best_two_i);
}

@
@<Make sure |change_log| has space for |more_log| more integers@>=
if ( more_log >= change_log_max_alloc ) {
    do {
        change_log_max_alloc *= 2;
    } while ( more_log >= change_log_max_alloc );
    change_log = (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

@ Initially |change_log| is given 10000 entries.

@<Allocate and initialize |match_run| structures@>=
change_log_max_alloc=10000;
change_log = new_arr_of(int,change_log_max_alloc);

@ We also need to clean it up.
@<Clean up |match_run| structures@>=
free_mem(change_log);mem_deduct(sizeof(int)*change_log_max_alloc);


@ We need to declare |change_log|, |change_log_next|, and
|change_log_max_alloc|.

@<|match_run| variables@>=
int *change_log=NULL, change_log_max_alloc, change_log_next=0;

@ 
Sometimes the tour we find after the perturbation is worse than
we we started with.  So we need to be able to revert to what we started
with.
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
    incumbent_len = previous_incumbent_len;
}
change_log_next = 0;

@
@<|match_run| variables@>=
length_t previous_incumbent_len=0;


@ The length of the $\lambda$-change is written in
|change_log[change_log_next-1]|, and the $t$ array itself precedes that
value.  We don't change |change_log_next| here.

The matching case is much simpler than the TSP case because there are no
special schemes to unwind.  All changes are generic.

Now, perfect matchings are rather simple beasts.  We can circumvent
most of the |swap_mates| machinery by observing that we can set
the mates directly.  We should match |best_exit_a| with |best_exit_b|,
and what was |t[1]| with what was |t[2]|, and  in general
what was |t[2i+1]| with |t[2i+2]|.

@<Undo a $\lambda$-change@>=
{ 
const int t1_pos = change_log_next - change_log[change_log_next-1] - 1;
int j;
for (j=change_log_next-3; j>=t1_pos;j-=2) {
	const int a=change_log[j], b=change_log[j+1];
	make_mates(a,b);
}
errorif(j!=t1_pos-2,"Fencepost Bug!");
}


@ Iterated LK for the TSP uses a double-bridge as a mutation because it
is a simple mutation that isn't implementable by a sequential $k$-change.

Now, all changes to a perfect matching can be encoded as collections of
sequential $k$-changes.  
There is no natural global
orientation differentiating a double-bridge from a 4-change.

Just to make things a little more interesting, 
the 4-changes implemented here are of the variety that aren't the
composition of two 2-changes.

@<If doing another iteration, perturb by a 4-change@>=
if ( iteration+1 < iterations ) {
	int m[8],i;
	
	@<Write four distinct matches in |m|@>@;
	make_mates(m[0],m[7]);
	make_mates(m[1],m[2]);
	make_mates(m[3],m[4]);
	make_mates(m[5],m[6]);
	for (i=0;i<8;i++) write_log(m[i]);
	write_log(8);

	/* Record the change in weight. */
	previous_incumbent_len = incumbent_len;
	incumbent_len +=
cost(m[1],m[2])+cost(m[3],m[4])+cost(m[5],m[6])+cost(m[7],m[0])@|
-cost(m[0],m[1])-cost(m[2],m[3])-cost(m[4],m[5])-cost(m[6],m[7]);@;
	
	/* Make these cities dirty. */
	for (i=0;i<8;i++) dict_insert(dirty_set,VIRTUAL_BASE+m[i]);
}

@
The random process can only go wrong if we pick the same match twice.
Note that matches are ``undirected''.

@<Write four distinct matches in |m|@>=
{
int count=0, still_clashing;

do {
	int j;
	errorif(count++>=10000,"Ummm, 4-change matching mutation didn't terminate after 10000 tries!\n");
	for ( j=0;j<8;j+=2 ) {
		m[j]=prng_unif_int(random_stream,n);
		m[j+1]=mate[m[j]];
	}
	still_clashing=0; /* Now check for clashes. */
	for ( j=0;j<8;j+=2 ) {
		int k;
		for (k=j+2;k<8;k++) {
			if ( m[j]==m[k] ) {
				still_clashing=1;
				break;
			}
		}
	}
} while ( still_clashing );
}





@*Verbose.

@<Verbose: undo one move@>=
if ( verbose > 125 ) {
	int i;
printf("\n");
	for ( i=0;i<two_i; i++ ) putchar(' ');
	printf("-");
	fflush(stdout);
}

@
@<Verbose: do one move@>=
if ( verbose > 125 ) {
	int i;
printf("\n");
	for ( i=0;i<two_i; i++ ) putchar(' ');
	printf("+");
	fflush(stdout);
}


@
@<Verbose: announce details of improvement@>=
if (verbose >= 125 ) {
	printf(" verbose %d ===two_i %d best_two_i %d best_exit_a %d best_exit_b %d\n",
		verbose,
		two_i, best_two_i, best_exit_a, best_exit_b );
	fflush(stdout);
}

@
@<Verbose: announce improvement@>=
if (verbose >= 100 ) {
	printf("=== improve by "length_t_spec" to "length_t_spec"\n",
		length_t_pcast(best_gain), length_t_pcast(incumbent_len));
	fflush(stdout);
}

@
@<Verbose: show |t| after move@>=
if (verbose >= 150 ) {
	int i;
	printf("t:");
	for (i=1;i<=two_i;i++) printf(" %d",t[i]);
	printf("\n");
	fflush(stdout);
}

@
@<Verbose: show |t| after improvement@>=
if (verbose >= 110 ) {
	int i;
	printf("T:");
	for (i=1;i<=best_two_i;i++) printf(" %d",t[i]);
printf(" %d",best_exit_a);
printf(" %d",best_exit_b);
	printf("\n");
	fflush(stdout);
}

@
@<Verbose: show improvement change@>=
if (verbose >= 110 ) {
	int i, m= (two_i<best_two_i?two_i:best_two_i);
	printf("two_i %d best_two_i %d best_exit_a %d best_exit_b %d\n",
			two_i, best_two_i, best_exit_a, best_exit_b );
	
	printf("B:");
	for (i=1;i<=m;i++) printf(" %d",t[i]);
	printf("\n");
	fflush(stdout);
}
@
@<Verbose: tabu@>=
if (verbose >= 500 ) {
	printf("X");
	fflush(stdout);
}
@
@<Verbose: fail cumulative gain test@>=
if (verbose >= 500 ) {
	printf("<");
	fflush(stdout);
}

@
@<Verbose: accept |e_entry| as candidate@>=
show_entry_with_string_at_verbose(e_entry,"accept",500);

@
@<Verbose: accept |e_entry| as best move@>=
show_entry_with_string_at_verbose(e_entry,"best move",500);


@
@<Verbose: accept |e_entry| as doing move@>=
show_entry_with_string_at_verbose(e_entry,"doing move",500);

@
@<Module subroutines@>=
static void
show_entry_with_string_at_verbose(const eligible_t *e_entry, const char *str, int the_verbose)  
{
if (verbose >= the_verbose ) {
	printf("\n%s: %p two_i %d  t2ip1 = %d  t2ip2 = %d "length_t_spec" -> "length_t_spec,
			str,
			e_entry,
			e_entry->two_i,
			e_entry->t2ip1,
			e_entry->t2ip2,
#if SPLIT_GAIN_VAR
			length_t_pcast(e_entry->gain_pos-e_entry->gain_neg),
#else
			length_t_pcast(e_entry->gain),
#endif
			length_t_pcast(e_entry->gain_for_comparison)
);
	fflush(stdout);
}
}

@
@<Verbose: start new search@>=
if ( verbose >= 105 ) {
printf("*");
}

@
@<Verbose: backtracking deeper@>=
if ( verbose >= 109 ) {
printf("g");
}

@
@<Verbose: generic deeper@>=
if ( verbose >= 109 ) {
printf("G");
}

@
@<Verbose: announce reverting to previous@>=
#if JBMR_MAX_VERBOSE >= 57
if (verbose>=57) {
printf("Reverting to previous\n");
}
#endif

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
@<Verbose: report termination of LK phase@>=
#if JBMR_MAX_VERBOSE >= 20
if ( verbose >= 20 ) {
    const double lk_time = resource_user_tick();
    const double ds_time =
resource_user_tick_from(begin_data_structures_mark);
    printf("LK phase ended with incumbent_len == " length_t_spec
        " after %.3f sec for LK and %.3f sec for ds+LK\n",
        length_t_pcast(incumbent_len), lk_time, ds_time);
    fflush(stdout);
}
#endif

@ We need the interface to the resource measurement routines.
@<Module headers@>=
#include "resource.h"


@*Index.
