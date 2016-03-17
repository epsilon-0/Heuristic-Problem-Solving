


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
$Log: construct.w,v $
Revision 1.132  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.131  1998/06/19 14:55:53  neto
Use binary heap priority queue in place of heavier weight dictionaries.

Revision 1.130  1998/04/16 16:02:03  neto
webbug fixed:  the code for initializing nn work array came after its
first use.  Doh.

Revision 1.129  1998/04/16 15:23:20  neto
Now it ctangles and compiles with no warnings.  (But you ask, does it work?)

Revision 1.128  1998/04/11 17:39:52  neto
Possibly finished coding the non-Euclidean changes.
But company is coming, and I must go.

Revision 1.127  1998/04/11 17:24:40  neto
Added much queue handling for the non-Euclidean case, including refreshing
the list, maintaining the unsaturated cities, and the farthest in queue
array.

Revision 1.126  1998/04/11 15:43:28  neto
Convert nn link to nn link pool because non-Euclidean case is better
with multiple possible neighbours in the queue.  Still converting
to allow non-Euclidean.

Revision 1.125  1998/01/23  20:09:22  neto
The mate structure doesn't need to be initialized before it is initialized!

Revision 1.124  1998/01/23  19:30:56  neto
Fixed to compile.  Also match construct is now more appropriately
construct matching.

Revision 1.123  1997/12/20 22:33:02  neto
Fixed another preprocessor booboo.

Revision 1.122  1997/12/20 22:29:52  neto
Fixed preprocessor booboo.

Revision 1.121  1997/12/20 22:23:59  neto
First crack at greedy matching heuristic.

Revision 1.120  1997/09/27 18:05:36  neto
Fixed RCS log behaviour.

Revision 1.119  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.118  1997/06/17  21:23:52  neto
Added two index entries.

Revision 1.117  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.116  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.115  1997/01/21  16:43:37  david
Added canonical tour back in.

Revision 1.114  96/12/02  15:27:15  neto
Added copyright notice.

Revision 1.113  96/08/20  11:34:39  neto
tx, ty might have been used uninitialized if n<2.  Added an n<3 guard
and assignments of dummy values to tx, ty.

Revision 1.112  96/08/16  13:04:35  neto
Added fixincludes.

Revision 1.111  96/08/15  14:42:25  neto
Fixed a const-related warning.

Revision 1.110  96/08/15  14:20:08  neto
Mmore prototypes.

Revision 1.109  96/08/15  13:00:11  neto
Make it pass -Wall

Revision 1.108  96/08/02  16:28:00  neto
Make sure different edges with equal lengths are both inserted.
(Fix the comparison function).
If we add an edge from x and x isn't saturated, then we should insert
a new edge from x into the priority queue.

Revision 1.107  96/08/02  14:38:10  neto
Now it compiles.  But greedy does not work.  It exhausts the priority
queue.

Revision 1.106  96/08/02  14:10:35  neto
Made heur\_param a long.

Revision 1.105  96/08/02  13:59:38  neto
Finished coding greedy.  Must now compile and check.

Revision 1.104  96/08/01  16:26:02  neto
More on Greedy.

Revision 1.103  96/08/01  14:25:29  neto
Random tour in this module.
Don't use upper.w
Edited description of Greedy.

Revision 1.102  96/07/29  17:09:55  neto
Fixed to compile.

Revision 1.101  96/07/29  16:19:42  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*Constructing a starting tour.
Lin-Kernighan is a local search procedure; it repeatedly looks to improve
a given tour.  It needs a starting tour to work on;  this module
builds one.

The outline of this module is as follows:

@c 
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;
@<Module type definitions@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *construct_rcs_id = "$Id: construct.w,v 1.132 1998/07/16 21:58:55 neto Exp neto $";

@ The exported interface to is contained in the \file{construct.h} header
file.  It has the following form.

@(construct.h@>=
#if !defined(_CONSTRUCT_H_)
#define _CONSTRUCT_H_
@<Headers we need to define our own interface@>@;
extern const char *construct_rcs_id;@;
@<Exported constants@>@;
@<Exported subroutines@>@;
#endif

@ To ensure consistency between the implementation and the interface,
we include our own header.
@<Module headers@>=
#include "construct.h"

@ The |construct| procedure does all the work.  Given 
the number of
cities 
$n$, 
and the globally-visible distance function |cost|, it builds
a tour and writes it into the preallocated buffer space that |tour| points
to.

The caller chooses from among several construction heuristics via the
|heuristic| parameter.  Some of these heuristics use the integer-valued
parameter |heur_param|.

@<Subroutines@>=
length_t
construct(const int n, int *tour, const int heuristic, const long heur_param) {
	switch(heuristic) {
	@<Heuristic alternatives@>@;
	}
	errorif(1,"Unknown heuristic: %d",heuristic);
	return (length_t)0;	/* Satisfy GCC's {\tt -Wall} option. */
}

@
@<Exported subroutines@>=
length_t
construct(const int n, int *tour, const int heuristic, const long heur_param);

@ We need the interface to the \module{LENGTH} module which 
defines the |length_t| type.
@<Headers we need to define our own interface@>=
#include "length.h"

@ We also need the interface to the \module{ERROR} module, which defines
the error-checking convenience functions.  
@<Module headers@>=
#include "error.h"

@ For a warmup, let's implement the canoncial tour, \ie~ordering 0, 1, 2, \etc.
This us usually only good if the points have already been sorted according
to some space-filling curve.

@<Heuristic alternatives@>=
case CONSTRUCT_CANONICAL: {
	int i; length_t len;
	for (i=0;i<n;i++)tour[i]=i;

	len = cost(tour[0],tour[n-1]);
	for (i=1;i<n;i++) len += cost(tour[i-1],tour[i]);
	return len;
	break;	/* Redundant, I know$\ldots$ */
}

@ We need to export the constant |CONSTRUCT_CANONICAL|.
@<Exported constants@>=
#define CONSTRUCT_CANONICAL 0




@ That was too easy.  
Let's implement a random tour heuristic.  Random tours
are usually very bad, but can be computed very quickly.

We use |heur_param| as the random number generator's seed.

@<Heuristic alternatives@>=
case CONSTRUCT_RANDOM: {
	int i; length_t len;

	for (i=0; i< n;i++) {
		tour[i] = i;
	}

	gb_init_rand(heur_param);
	for (i=0; i<n;i++) {
		const int next = gb_unif_rand(n-i);
		const int t = tour[next];@+
		tour[next] = tour[n-1-i];@+
		tour[n-1-i] = t;
	}

	len = cost(tour[0],tour[n-1]);
	for (i=1;i<n;i++) len += cost(tour[i-1],tour[i]);

	return len;
	break;	/* Redundant, I know$\ldots$ */
}


@ We need to export the constant |CONSTRUCT_RANDOM|.
@<Exported constants@>=
#define CONSTRUCT_RANDOM 1


@ And we must import the interface to the random number generator.  We've
used the generator from Knuth's Stanford GraphBase.
@^Stanford GraphBase@>
@^Knuth, Donald Ervin@>

The |cost| function is provided by the \module{READ} module.

@<Module headers@>=
#include "gb_flip.h"
#include "read.h"


@*The Greedy heuristic.
Johnson \etal (INSERT REFERENCE), suggest using the Greedy 
heuristic to construct the
starting tour for Lin-Kernighan.   
Bentley (INSERT REFERENCE), calls it the Multiple Fragment heuristic, and
describes a fast algorithm for it on geometric inputs.

``Greedy'' has a few advantages over other
heuristics.  First, it is quickly computed, especially on geometric inputs.
Second, most of the edges it ends up using are very short, so the local
optimization phase doesn't have to fix up too much.  Third, the tours it
constructs have a few very large defects; the Lin-Kernighan cumulative
gain heuristic takes advantage of this to find very good tours.

%For now, I'll just use the best of the upper bounding heuristics that I
%used for the branch and bound procedure.  See the \module{upper} module.

@ The greedy heuristic may be described as follows.  Begin with an
empty set of edges $T$.  Examine the edges in smallest to largest order.
If the edge in hand doesn't create a cycle in $T$ and doesn't create a vertex 
of
degree three in $T$, then that edge is added to $T$.  
Once $T$ has $n-1$ edges, join
the two ends of $T$ to make it a Hamiltonian cycle.  (The  first $n-1$ edges 
of $T$ form a Hamiltonian path.)

Notice the similarity to Kruskal's algorithm for constructing a minimum
@^Kruskal's algorithm@>
@^minimum spanning tree@>
spanning tree.  The main difference is that we never allow a vertex to
become of degree three, \ie, we never let our set of paths ``branch''.
Another way to put this is as follows. Let us say that a vertex is
\term{saturated} if it is of degree two.
@^saturated vertex@>
Then the Greedy heuristic is just
Kruskal's algorithm with the
proviso that no edge with a saturated endpoint is ever added,
together with
the addition of an $n$'th edge to complete the tour.

@ If implemented directly, the description just given for the Greedy heuristic
would be quite inefficient.
The implementation in this module 
follows Bentley's.

Bentley's innovations are threefold.  First,
he sorts and selects the edges lazily, using a priority queue containing
the shortest edge from each unsaturated vertex.   
Second, he uses $k$-dimensional trees to perform nearest neighbour queries
(where one is allowed to hide vertices).  See module \module{KDTREE} for
an implementation of this data structure.  Third, he uses an efficient
data structure to determine when an edge would create a subcycle.

Unfortunately, not all instances have the benefit of geometry, so we
have to add some cleverness in searching for next-nearest neighbours.
In the non-Euclidean case, this amounts to maintaining
extra bookkeeping about 
which cities remain unsaturated, and buffering multiple nearest neighbours
in the queue to save on repeated exhaustive searches of neigbours of a
single city.

Finally, much of this code for the TSP can be shared with the weighted
perfect matching code.  When there is a difference, the TSP-specific code is
delimited with |DO_TOUR|, and the matching code with |DO_MATCHING|.


@<Heuristic alternatives@>=
case CONSTRUCT_GREEDY: {
	length_t len=0;
	const int E2_case = E2_supports(tsp_instance);
#define DO_TOUR
	@<Declare the data structures for Greedy@>@;
	@<Build the data structures for Greedy.@>@;
	@<Build the Greedy tour@>@;
	@<Destroy the data structures for Greedy@>@;
#undef DO_TOUR
	return len;
break;
}

@ We need to export the constant |CONSTRUCT_GREEDY|.
@<Exported constants@>=
#define CONSTRUCT_GREEDY 2

@ The first data structure we'll need is a priority queue of edges.  We'll
record at most one edge per  vertex in the graph.  It will be convenient
to store the edges in an array indexed by city number.  Each entry records
the name of the other end of the edge, together with the length of that
edge.

I've put the length entry first because we will access it much more often
than the city entry.  This happens because the length entry is the
key in the priority queue.  The comparison function |cmp_pq_edge| 
defined below 
accesses the length entry through a pointer; if that field comes first,
then the offset from the pointer will be zero.  I assume that the \CEE/ 
compiler will be smart enough to elide the pointer arithmetic, making
the program that little bit faster.

@<Module type definitions@>=
typedef struct {
	length_t len;
	int this_end;
	int other_end;
} pq_edge_t;

@ In the Euclidean case, we keep in the queue at most one 
neighbour for each city.  An array is convenient for that, and
that is how Bentley defines it.
He says  ``|nn_link[i]| contains
the index of the nearest neighbour to $i$ that (when originally computed) is
not in the same fragment that contains |i| (though subsequent operations might
invalidate that condition).  These links are the edges that are eventually 
inserted into the tour.''  That is, he city from which the edge is
emanating is implicitly defined by pointer arithmetic.

In the non-Euclidean case, we cache multiple neighbours at a time,
so the array structure doesn't work well for us.  To keep the code
simpler, we use a dynamically allocated pooled of edges instead of just
an array.  This pool is called |nn_link_pool|.

The entries of |nn_link_pool| serve as the domain over which
the priority queue |edge_pq| is defined.
We will use the priority queue routines from module \module{PQ}.

@<Declare the data structures for Greedy@>=
pool_t *nn_link_pool = pool_create(sizeof(pq_edge_t),n);
pq_t *pq_edge = pq_create_size(cmp_pq_edge,n);

@ We need to do a bit of error checking.
@<Build the data structures for Greedy.@>=
errorif(pq_edge==NULL,"Couldn't create the priority queue!");
pq_set_print_func(pq_edge,nn_link_prn);

@ Deallocation is easy.
@<Destroy the data structures for Greedy@>=
pool_destroy(nn_link_pool);
pq_destroy(pq_edge);

@ We need the interface to both the memory allocation routines, the
priority queue routines, and to the pool manager.

@<Module headers@>=
#include "memory.h"
#include "pq.h"
#include "pool.h"

@ We also need the definition of |NULL|, which is in one of the following
header files.  Also, the |free_mem| macro needs the declaration of |free|
from \file{stdlib.h}.
@<System headers@>=
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "fixincludes.h"

@ We've had to provide a comparison function for the priority queue routines.
The comparison function has the same interface as the one provided to
the |qsort| standard library function.  This one in particular compares
edge lengths.  We want our priority queue to return the shortest edge
first, so smaller edge lengths compare smaller.

Our function returns an |int|, and we don't know exactly what |length_t| really
is,  so we need to be a bit careful about how we translate the difference
between the lengths into a sign value.  Using an intermediate value should
be safe.  Note that both lengths should be non-negative, so their difference
should be smaller in magnitude than the greater of the two lengths, and
therefore within range of the |length_t| data type.
@^overflow@>

When the lengths compare equal, we must break the tie.  Otherwise we'd never
be able to insert two edges of the same length: the priority queue requires
unique keys.  We break ties by returning the difference in the pointers.

@<Module subroutines@>=
static int
cmp_pq_edge(const void *a, const void *b) {
	length_t len_diff = ((const pq_edge_t *)a)->len - ((const pq_edge_t *)b)->len;
	return len_diff < 0 ? -1 : (len_diff >0 ? 1 : 
		(int)(((const pq_edge_t *)a)-((const pq_edge_t*)b)) );
}

@ The priority queue is initialized by filling in each city's entry
in the |nn_link_pool| collection, 
and then inserting that entry into the priority queue.
The entry for a city contains the that city's nearest neighbour and the
length to that neighbour.

We assume that the all the cities in the $k$-d search structure are
visible.

In the non-Euclidean case, we do a bulk search of 
I'll have to modify this for the case when the 
@^unfinished code@>

@<Build the data structures for Greedy.@>=
if ( E2_case ) {
	int i;
	for (i=0;i<n;i++) {
		pq_edge_t *e = pool_alloc(nn_link_pool);
		e->this_end = i;
		e->other_end = E2_nn(i);
		e->len = cost(i,e->other_end);
		pq_insert(pq_edge,e);
		@<Other initializations for city |i|@>@;
	}
} else {
	@<Build the data structures for Greedy, non-Euclidean case@>@;
}

@  We need the interface to $k$-d trees and the declaration of |tsp_instance|.
@<Module headers@>=
#include "lk.h"
#include "kdtree.h"

@ In the non-Euclidean case, we can have multiple neighbours in the queue
for each city.  When those are exhausted, we get a fresh batch.  We
need a way of knowing when they are exhausted. For that we use an array
with entry
|farthest_in_queue[i]| being the city at the other end of the heaviest
edge in the queue and which had been added for city |i|.

@<Declare the data structures for Greedy@>=
int *farthest_in_queue=NULL;

@
@<Build the data structures for Greedy, non-Euclidean case@>=
farthest_in_queue = new_arr_of(int,n);

@
@<Destroy the data structures for Greedy@>=
if ( !E2_case ) { free_mem(farthest_in_queue); mem_deduct(sizeof(int)*n); }


@ Furthermore, the non-Euclidean case needs an anolog to the ``hidden''
cities.  It is in fact more convenient to keep track of which cities
remain unsaturated.  Values |unsaturated[0]| through
|unsaturated[num_unsaturated-1]| are the cities which remain, well,
unsaturated.  We also support efficient updates to this array by
maintaining
an inverse mapping of the unsaturated cities: if city |i| 
is unsaturated, then |unsaturated[inv_unsaturated[i]]==i|.

@<Declare the data structures for Greedy@>=
int *unsaturated=NULL, num_unsaturated=0, *inv_unsaturated=NULL;

@
@<Build the data structures for Greedy, non-Euclidean case@>=
unsaturated = new_arr_of(int,n);
inv_unsaturated = new_arr_of(int,n);
num_unsaturated=n;
{ int i;
	for (i=0;i<n;i++) inv_unsaturated[i]=unsaturated[i]=i;
}

@
@<Destroy the data structures for Greedy@>=
if ( !E2_case ) { 
free_mem(unsaturated); mem_deduct(sizeof(int)*n); 
free_mem(inv_unsaturated); mem_deduct(sizeof(int)*n); 
}

@ Here's how to make a city unsaturated.
Once we verify that it really was unsaturated to begin with, 
all we have to do is copy down the last unsaturated city down over its
entry in the |unsaturated| array.

Note that because the values in |inv_unsaturated| are  always non-negative,
we don't have to check for underflow of |num_unsaturated|.
@<Mark city |c| as saturated@>=
{ const int inv= inv_unsaturated[c];
	if (inv<num_unsaturated && unsaturated[inv]==c) 
		unsaturated[inv]=unsaturated[--num_unsaturated];
}

@ Initializing the priority queue in the non-Euclidean case is done
city by city.  The initialization for each city is rather complicated,
and we shall reuse it, so we break it off into a separate section.

@<Build the data structures for Greedy, non-Euclidean case@>=
{
int i;
nn_work = new_arr_of(pq_edge_t,n);
for (i=0;i<n;i++) {
	const int x=i, not_me = -1;
	@<Get fresh neighbours for |x|, excepting |not_me|@>@;
	@<Other initializations for city |i|@>@;
}
}

@  In the non-Euclidean case we don't know anything about the structure
of the distance matrix.  We have to scan all unsaturated cities for
possible neighbours.  However, for a large fraction of cities, we'll
be scanning their rows multiple times.  To save on these scans, 
we insert multiple entries into the queue for every scan we perform.

Of course, there is a tension between the space required to store the
queue, how quickly we can find those nearest neighbours, and how many
of them end up wasted (by the time we draw an edge from the queue,
the other end may have become saturated).

We choose to put in up to |max_per_city_nn_cache| neighbours at a time
for each city.  We may make this a user paramter.  The default
value is 30, which is a complete guess.

In scanning the list of unsaturated cities, we 
skip over |x| itself and |not_me|.
(The |not_me| is used in the tour algorithm.   Trust me.)

We use the |select_range| procedure from module \module{DSORT}, which
requires the entries to be in an array.  We'll use |nn_work|, defined
below.

@d max_per_city_nn_cache 30
@d max(X,Y) ((X)<(Y)?(Y):(X))
@d min(X,Y) ((X)>(Y)?(Y):(X))

@<Get fresh neighbours for |x|, excepting |not_me|@>=
{
	int i,num_chosen, farthest_city;
	size_t w;
	length_t farthest_len;
	for (i=w=0;i<num_unsaturated;i++) {
		const int c=unsaturated[i];
		if ( c==x || c==not_me ) continue;
		nn_work[w].this_end=x;
		nn_work[w].other_end=c;
		nn_work[w].len=cost(x,c);
		w++;
	}
	num_chosen=min(w,max_per_city_nn_cache);
	errorif(num_chosen==0,"Bug!");
	(void)select_range(nn_work,w,sizeof(pq_edge_t),cmp_pq_edge,
		0,num_chosen,0 /* Don't sort. */);
	farthest_len = nn_work[i].len;
	farthest_city = nn_work[i].other_end;
	for ( i=0;i<num_chosen; i++) {
		pq_edge_t *e=pool_alloc(nn_link_pool);
		*e = nn_work[i];
		pq_insert(pq_edge,e);
		if ( farthest_len < e->len ) { 
			farthest_city = e->other_end;
			farthest_len = e->len; 
		}
	}
	farthest_in_queue[x]=farthest_city;
}

@
@<Module headers@>=
#include "dsort.h"


@ We must declare the set |nn_work|.
@<Declare the data structures for Greedy@>=
pq_edge_t *nn_work=NULL;


@
@<Destroy the data structures for Greedy@>=
if ( !E2_case ) { free_mem(nn_work); mem_deduct(sizeof(pq_edge_t)*n); }


@ We need a place to record the tour as its being built up.  We use
an array |adj| indexed by city number.  Entry |adj[i]| records the set of
cities adjacent to |i| in the tour so far.    Because at any time
there are either zero, one or two cities adjacent to a given city, it
is sufficient for each entry to have a |count| field and a two-entry
array |city| of neighbours.

@<Module type definitions@>=
typedef struct {
	int count;	/* 0, 1, or 2 */
	int city[2];
} adj_entry_t;

@ We allocate the |adj| when we declare it.

@<Declare the data structures for Greedy@>=
#if defined(DO_TOUR)
adj_entry_t *adj = new_arr_of(adj_entry_t,n);
#endif

@ Deallocation is easy.
@<Destroy the data structures for Greedy@>=
#if defined(DO_TOUR)
free_mem(adj);
#endif

@ Each vertex begins with no neighbours.
@<Other initializations for city |i|@>=
#if defined(DO_TOUR)
adj[i].count = 0;
#endif

@ 
While
building the tour, we maintain a set of framgents.
Each fragment is
a (non-branching) path.  In general, each path has two tails, and these
are the cities to which we add links.  We avoid creating subcycles by
avoiding joining one endpoint of a fragment to its other end.  
It is therefore convenient to maintain an array, |tail|. When
city |i| is still a tail, entry |tail[i]|
records the index of the city at the other end of the fragment containing
|i|.

@<Declare the data structures for Greedy@>=
#if defined(DO_TOUR)
int *tail=new_arr_of(int,n);
#endif

@
@<Destroy the data structures for Greedy@>=
#if defined(DO_TOUR)
free_mem(tail);mem_deduct(sizeof(int)*n);
#endif

@ Each city begins in a fragment by itself.
@<Other initializations for city |i|@>=
#if defined(DO_TOUR)
tail[i] = i;
#endif

@ Now we're ready for the main part of the Greedy heuristic, which builds
the Hamiltonian path.

Initially, each city is alone in its own fragment.  
We repeatedly take the cheapest remaining
valid link and add it to the tour.  Most of the code here is just
the bookkeeping involved in adding the chosen edge.

Once $n-1$ edges have been added, we connect the two remaining tails.
By sheer luck, these tails are stored in |tx| and |ty|.

@<Build the Greedy tour@>=
{@+ int i, x, y, tx, ty;
errorif(n<3,"Only %d cities.  Can't build a tour.",n);
tx=ty=-1;	/* Satisfy GCC's dataflow analysis. */
for ( i=0;i<n-1;i++ ) {
	pq_edge_t *e;
	@<Find a shortest valid edge $e=(x,y)$@>@;
	adj[x].city[adj[x].count++] = y;
	adj[y].city[adj[y].count++] = x;
	if ( adj[y].count == 2) { if (E2_case) E2_hide(y); else {const int c=y;
@<Mark city |c| as saturated@>}}
	if ( adj[x].count == 2) { if (E2_case) E2_hide(x); else {const int c=x;
@<Mark city |c| as saturated@>}}
	else { @<Insert a new link for |x|@> }
	tx = tail[x];
	ty = tail[y];
	tail[tx]=ty;
	tail[ty]=tx;
}
adj[tx].city[adj[tx].count++] = ty; /* Complete the Hamiltonian cycle */
adj[ty].city[adj[ty].count++] = tx;
if (E2_case) E2_unhide_all();
len += cost(tx,ty);
}

@ Here's where we pick a shortest remaining valid edge.
It is eligible if both ends are
not yet saturated (\ie, if both ends have degree less than two), and
if the two ends belong to different fragments (\ie, are not the two
tails of the
same fragment).
	
First we find the shortest remaining edge, $(x,y)$.  If it satisfies both 
of the above criteria, then we break out of the loop, and pass it on.
Otherwise, it is a stale link, \ie, edges added since its insertion
into the priority queue have made it obsolete.  In that case, we must
find a new valid link and insert it into the priority queue.

@<Find a shortest valid edge $e=(x,y)$@>=
while (1) {
	e = pq_delete_min(pq_edge);
	errorif(e==NULL,"Exhausted the priority queue of links.");
	x = e->this_end; y=e->other_end;
	if ( adj[x].count == 2 ) { /* |x| is saturated */
		continue; 
	}
	if ( adj[y].count <2 && y!=tail[x] )  break;	/* We found a valid edge */
	@<Insert a new link for |x|@>@;
}
len += e->len;

@ This section finds a new candidate link for city |x|.

In the non-Euclidean case, we might have many other neighbours of |x| 
already
in the queue.  So we only refresh if we have just used up the furthest
one that was in the queue.

In the Euclidean case, 
we must first hide the
city at the other end of its fragment.

@<Insert a new link for |x|@>=
if ( E2_case ) {
	E2_hide(tail[x]);
	e->other_end = E2_nn(x);
	e->len = cost(x,e->other_end);
	E2_unhide(tail[x]);
	pq_insert(pq_edge,e);
} else {
	pool_free(nn_link_pool,e);
	if ( farthest_in_queue[x] == y ) {
		const int not_me = tail[x];
		@<Get fresh neighbours for |x|, excepting |not_me|@>@;
	}
}

@ Once the tour is built in |adj|, we write it in simpler form to |tour|.
This is a simple matter of following indices around. 

@<Build the Greedy tour@>=
{@+ int i=0, prev=-1, here=0;
	do {
		tour[i++]=here;
		if ( adj[here].city[0] != prev ) {@+prev=here;@+here=adj[here].city[0];@+}
		else {@+prev=here;@+here=adj[here].city[1];@+}
	} while( here != 0 );
	errorif(i!=n,"Not a tour.");
}


@
@<Module subroutines@>=
static void nn_link_prn(void *p);
void
nn_link_prn(void *p) {
	pq_edge_t *np=(pq_edge_t*)p;
	printf(" %d,%d ",np->this_end,np->other_end);
}

@* Weighted perfect matchings.

Procedure |construct_matching| builds a weighted perfect matching.
It is analogous to procedure |construct|.

The first parameter is the number of vertices in the graph.

The second parameter is a buffer in which to write the matching.
After we're through, edge $(u,v)$ is in the matching if and only if
|mate[u]=v| and |mate[v]=u|.

The third parameter specifies which algorithm should be used to construct
the matching, as with procedure |construct|.

The fourth parameter can be specified on the command line
and may be used (or ignored) by the algorithm for whatever purpose
the algorithm desires.

The routine returns the weight of the constructed perfect matching.

@<Subroutines@>=
length_t 
construct_matching(int n, int *mate, int alg,long alg_param) 
{
	int i;
	length_t weight=0;
	errorif(n%2,
		"Perfect matchings need an even number of vertices; given %d", n);
	errorif(mate==NULL,
			"Tried to construct a matching before space is allocated");
	switch(alg) {
	@<Matching cases@>@;
	default:
		errorif(1,"Unrecognized matching construction algorithm %d",alg);
	}
	return weight;
}

@ 
@<Exported subroutines@>=
length_t construct_matching(int n, int *mate, int alg,long alg_param);


@ The first algorithm is rather trivial.  It just pairs each vertex
with its positional neighbour.

Now, this might seem like an awful matching.  But the user has the
option of pre-sorting the points so that they are in the order
determined by Moore's space-filling curve (a variant of Hilbert's curve).
In that case, this canonical perfect matching  
might be an excellent starting point.

@<Matching cases@>=
case CONSTRUCT_CANONICAL:
	for(i=0;i<n;i+=2) {
		mate[i]=i+1;
		mate[i+1]=i;
		weight += cost(i,i+1);
	}
	break;

@ The second option is a random perfect matching.
It's probably very bad, but at least it's fast.

We use |alg_param| as the random number generator's seed.
(We may want to use different pseudo random number generator algorithms
via the facilities provided by module \module{PRNG}, but I'm not too
worried about using \module{GB\_FLIP} in this case.)


@<Matching cases@>=
case CONSTRUCT_RANDOM:
	{ @;
	int *unmated=new_arr_of(int,n), num_unmated=n, u, v, ui, vi;
	for (i=0;i<n;i++) unmated[i]=i;
    gb_init_rand(alg_param);
	while ( num_unmated > 0 ) {
		ui = gb_unif_rand(num_unmated);
		u = unmated[ui]; unmated[ui]=unmated[--num_unmated];
		vi = gb_unif_rand(num_unmated);
		v = unmated[vi]; unmated[vi]=unmated[--num_unmated];
		mate[u]=v;
		mate[v]=u;
		weight+=cost(u,v);
	}
	free_mem(unmated);mem_deduct(sizeof(int)*n);
	}
	break;

@ The last option is a perfect matching discovered by a greedy algorithm.
Beginning with an empty matching, we repeatedly add the next shortest
edge that is not incident upon any vertex already in the matching.

It has much the same structure as the greedy algorithm for constructing
a greedy tour.  This time around, we don't need to use the |adj| or |tail|
arrays.  

@<Matching cases@>=
case CONSTRUCT_GREEDY:
	{ 
	const int E2_case = E2_supports(tsp_instance);
#define DO_MATCHING
	@<Declare the data structures for Greedy@>@;
	@<Build the data structures for Greedy.@>@;
	@<Build the Greedy matching@>@;
	@<Destroy the data structures for Greedy@>@;
#undef DO_MATCHING
	}
	break;

@ We use the |mate| array itself to record when a city has been saturated.
We initialize each entry to a negative number, which can never be a city 
label.

@<Other initializations for city |i|@>=
#if defined(DO_MATCHING)
mate[i]=-1;
#endif


@ With the priority queue and the nearest neighbour links all set up, 
the greedy algorithm looks like the following.

In the perfect matching case, a node is saturated if it has even a single
edge incident upon it.  We maintain the invariant that a city is hidden
in the $k$-d tree if and only if it is saturated.

You'll have to agree this is much simpler than the greedy algorithm
for tours.

@<Build the Greedy matching@>=
{
int num_remaining =n/2;@;
while( num_remaining > 0 ) {@/
	int u, v;
	pq_edge_t *next_edge = pq_delete_min(pq_edge);
	errorif ( next_edge==NULL,
		"Priority queue exhausted while we expect 2*%d more", num_remaining);
	u = next_edge->this_end;
	v = next_edge->other_end;
	if (mate[u]>=0) continue; /* Node |u| is already saturated. */
	if (mate[v]>=0) { @<Pick a new potential mate for |u|@> continue;}@;
	mate[u]=v; /* Otherwise, insert |(u,v)| into the matching. */
	mate[v]=u;
	if (E2_case) E2_hide(u); else { const int c=u; @<Mark city |c| as
saturated@>@;}
	if (E2_case) E2_hide(v); else { const int c=v; @<Mark city |c| as
saturated@>@;}
	weight += cost(u,v);
	num_remaining--;
}
}
if (E2_case) E2_unhide_all();

@ Recall that all mated cities are hidden.  Also, the $k$-tree never
says that a city is its own nearest neighbour.

In the non-Euclidean case, we insert new possible mates only if we've
exhausted
the list of neighbours for |u| already in the queue.

@<Pick a new potential mate for |u|@>=
if (E2_case) {
	next_edge->other_end = E2_nn(u);
	next_edge->len = cost(u,next_edge->other_end);
	pq_insert(pq_edge,next_edge);
} else { 
	pool_free(nn_link_pool,next_edge);
	if ( farthest_in_queue[u] == v ) {
		const int x = u, not_me = x;
		@<Get fresh neighbours for |x|, excepting |not_me|@>@;
	}
}

@*Index.
