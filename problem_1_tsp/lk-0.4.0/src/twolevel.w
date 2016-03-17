


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
$Log: twolevel.w,v $
Revision 1.145  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.144  1997/09/27 18:04:13  neto
Fixed RCS log behaviour.

Revision 1.143  1997/08/15  20:19:30  neto
Added Index major section.

Revision 1.142  1997/05/16  20:37:46  neto
Change FIX INCLUDES to OS HAS BROKEN HEADERS.

Revision 1.141  1997/05/16  18:13:25  neto
Include <config.h> and "lkconfig.h"

Revision 1.140  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.139  1996/10/29  17:27:11  neto
add copyright notice.

Revision 1.138  96/09/19  15:41:07  neto
Removed useless const qualifiers.  Remember C passes arguments by value,
so integers are safe.

Revision 1.137  96/09/19  15:33:25  neto
Removed conflict with definition of |abs| in stdlib.h for IRIX.

Revision 1.136  96/09/18  11:40:32  neto
There is no em in CWEB, only it.
This module appears to work now.

Revision 1.135  96/09/17  14:16:34  neto
Fixed a conflict with the definition of prev and a structure in
stdio under AIX.

Revision 1.134  96/09/17  14:03:43  neto
Fixed the self-consistency check.  The group sequence numbers were assumed
to start at 0.  They can start anywhere and wrap around to 0.
Also, made using\_two\_representations conditionally compiled.

Revision 1.133  96/09/17  12:53:38  neto
Made debugging output conditional.

Revision 1.132  96/09/17  12:39:31  neto
Fixed bug 10.
Sequence numbers were screwed up on split right when current segment
was reversed but right segment was not.  

Revision 1.131  96/09/17  12:09:55  neto
Fixed the descriptions on sequence numbers for splitting left and right.
Still buggy.

Revision 1.130  96/09/17  11:55:58  neto
Fixed Bug 9.
9a: head/tail wasn't being set properly when current seg was reversed.
9a: seq numbers not set properly under same condition.

Revision 1.129  96/09/17  11:17:21  neto
Fixed bug 8a, 8b.
8a: split segment while that segment is reversed fouled up the inbound
sibling poitner.
8b: split segment while reversed set the sequence numbers rwrogng.

Revision 1.128  96/09/16  17:11:21  neto
Quashed bug 7, failure at flip number 159.
The inbound pointer addresses depend on the orientation of the ac segment.

Revision 1.127  96/09/13  17:21:39  neto
Quashed bugs 5 and 6.
5: off-by-one in splitting left and right.
6: implicit rebalancing for case 1; It was splitting right, but not
fixing the city sibling pointers, both inbound and outbound.
Now it fails on lin105 at flip number 159.

Revision 1.126  96/09/13  15:40:55  neto
Was splitting one-off, for case 3.  Ooops.

Revision 1.125  96/09/13  15:35:54  neto
Split right now updates sequence numbers properly.  I've made
split left symmetric and I hope it works.
Still fails on lin105.

Revision 1.124  96/09/13  13:06:24  neto
More debugging output.
Reach case 2 when psa=psb=0, psc=psd=1.  Mabye need to enforce 4 or more
groups?

Revision 1.123  96/09/13  12:13:11  neto
Added updating of sequence numbers in Case 1.  Oops.

Revision 1.122  96/09/13  11:54:30  neto
More checks of the twolevel data structure.

Revision 1.121  96/09/12  16:46:05  neto
More debugging output. Somewhere, sequence numbers aren't properly being
maintained.

Revision 1.120  96/09/12  15:45:50  neto
Ensure that modulus returns non-negative result in the important places.

Revision 1.119  96/09/12  15:38:02  neto
Fixed debugging stuff a bit.

Revision 1.118  96/09/12  14:18:09  neto
Finished the redundancy code to check two-level trees.
It compiles too, and catches an error in lin105.

Revision 1.117  96/09/11  17:18:51  neto
Started adding debugging code.

Revision 1.116  96/09/10  16:51:35  neto
Fixed problem in creating the data structure.  We need to compute a 
new group size internally.

Revision 1.115  96/09/10  15:57:58  neto
Now it compiles.  (Two minor errors regarding the normalization macro.)

Revision 1.114  96/09/10  15:55:03  neto
Fixed the parent renumbering.
It TeXs to my satisfaction.  We'll see if it compiles.

Revision 1.113  96/09/09  17:06:05  neto
Fixed some of the problem with interening in parents.
Need to fix the parent sequence number updating.

Revision 1.112  96/09/06  16:03:10  neto
Fixed problem in flipping, case 1. 
We might have had portion b-d contained in a-c.
Still a problem in parents.  See research notes.
Also, need to add a comment about avoiding a performance bug in
choosing shorter sequence of parents.

Revision 1.111  96/09/05  16:05:43  neto
Now it compiles cleanly.
Fixed precedence problems, vestiges of the ``city'' field, accessing
wrong link array, variables declared twice, suggested parentheses, etc.

Revision 1.110  96/09/05  15:37:22  neto
Finished coding flipping.

Revision 1.109  96/09/05  14:15:41  neto
Fixed outbound sibling pointers in city list reversal.

Revision 1.108  96/09/05  12:53:55  neto
Check for case 1 after split c-d.

Revision 1.107  96/09/04  17:14:23  neto
Finished coding Case 3 of flipping.

Revision 1.106  96/09/03  17:06:17  neto
Finished coding case 1 in flip.

Revision 1.105  96/09/03  15:45:52  neto
Made city numbers implicit, as per first paragraph of p. 444 of
Fredman et al.

Revision 1.104  1996/08/30  21:28:38  david
More of flip.

Revision 1.103  1996/08/30  20:38:17  david
Use plain sequence numbers and still protect against wraparound.

Revision 1.102  1996/08/30  20:28:16  david
Lots and lots and lots of coding.

Revision 1.101  1996/08/23  20:55:43  david
Initial revision.

}

@*A two-level tree implementation of the oriented tour ADT.
This module implements the oriented tour ADT using two-level trees.
These were introduced by M.~L.~Fredman, D.~S.~Johnson, L.~A.~McGeoch,
and G.~Ostheimer in {\sl Data Structures for Traveling Salesmen}, 
Journal of Algorithms, {\bf 18}, 432--479 (1995), (and
an earlier conference paper).  
@^Fredman, M.~L.@>
@^Johnson, D.~S.@>
@^McGeoch, L.~A.@>
@^Ostheimer, G.@>

That paper introduces three new data structures for the oriented tour
ADT: splay trees, two-level trees, and segment trees.  These three
are compared with the traditional array-based representation.  
Some broad conclusions are drawn:
below a thousand cities, arrays are the fastest; 
between a thousand  and a million cities, two-level
trees are best; above a million, splay trees appear to win out.

This module implements the oriented tour ADT in terms of two-level trees.
Just like the \module{ARRAY} module, only one tour is supported at a
time, although it shouldn't be too hard to make this code purely 
object-oriented.

@ Fredman \etal.~define an oriented tour abstract data type supporting
three queries and one update operation.  The most common and effective
local search algorithms for the traveling salesman problem ---2-opt, 3-opt, 
and Lin-Kernighan--- may all be implemented in terms of this abstraction.
@^oriented tour ADT@>

The oriented tour ADT consists of the following operations
(I will use the names as implemented in this module, \ie, prepended by
the word |twolevel_|.):

|twolevel_next(a)| is a query that returns the city that follows $a$ in the
current tour.

|twolevel_prev(a)| is a query that returns the city that precedes $a$ in the
current tour.  It must be the case that 
|next(prev(a))==prev(next(a))==a|.

|twolevel_between(a,b,c)| is a query that returns true or false.  It answers
the question:  ``In a forward traversal starting at city $a$, do we reach
city $b$ no later than city $c$?''

|twolevel_flip(a,b,c,d)| updates the tour by replacing the edges $(a,b)$ and
$(c,d)$ by the edges $(b,c)$ and $(a,d)$.  It assumes that 
|a==next(b)| and |d==next(c)|.  The orientation of the updated tour
is not specified.

These four operations are the ones defined by Fredman \etal.  In fact, I
have lifted these descriptions from that paper and lightly edited them
for inclusion here.  

For convenience's sake, I also define |twolevel_set(int *t)|, which
sets the current tour to be the same as the array of
integers |t|.  That is, city |i| in the tour is city |t[i]|.
Note that we don't need a ``get'' routine because the tour can be read off
by successively following |next| cities until we wrap to the start
again.

We also define the standard setup and clean procedures: 
|twolevel_setup(int n, int seg_start_size)|
and
|twolevel_cleanup(void)|.  The parameters to the setup procedure is the number
of cities in the instance and the starting segment size (see below).

@ The outline of this module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Module type definitions@>@;
@<Module variables@>@;
@<Module prototypes@>@;
@<Subroutines@>@;
const char *twolevel_rcs_id="$Id: twolevel.w,v 1.145 1998/07/16 21:58:55 neto Exp neto $";

@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

@ The exported interface is contained in the \file{twolevel.h} header file,
which has the following form.

@(twolevel.h@>=
extern const char *twolevel_rcs_id;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "twolevel.h"

@*Two-level trees.
A two-level tree on $n$ cities is much like a B+tree of degree $\sqrt{n}$.
That is, the tour is stored as a linked list of cities.  
They are clustered into 
into $\sqrt{n}$ segments of $\sqrt{n}$ cities each.
Each segment is represented at the root level by a
parent node. The roughly $\sqrt{n}$ parent
nodes are themselves organized in a doubly linked list.

To facilitate ordering comparisons, the parent nodes are given consecutive
sequence numbers, and city nodes are given consecutive sequence numbers
within the context of their own segment.

To facilitate quick reversals of large portions of the tour, each 
parent node has an associated reversal bit, indicating whether the cities
in the associated segment should are traversed from left to right or from
right to left.

When the parent's reversal bit is off, succesive cities in the tour
are found by following |next| pointers, encountering increasing
sequence numbers within a segment. 
When the parent's reversal bit is on, succesive cities in the tour
are found by following |prev| pointers, encountering decreasing
sequence numbers within a segment. 

@ The diagram of a two-level tree that 
Fredman \etal.\ provide include an explicitly stored city number in
the city nodes.  However, they say ---at the top of page 444--- that
the city nodes are stored in an array and that therefore looking up
the city node from the city number can be done in constant time.  
I take this to mean that they also save space by not explicitly 
storing the city number in the city node.  This should also speed things
up by making more effective use of the cache and the communication
bandwidth between
levels of the memory hierarchy.

@ Here are the type definitions for a parent node, |parent_node_t|,
and for a city node, |city_node_t|.  Parents point to the head and tail
of their associated, segments.  Each city node points to its parent.

In both kinds of nodes, sibling pointers are held in the |link| array;
macros |next| and |prev| are just a shorthand for the next and previous
siblings, respectively.  Similarly, |head| and |tail| are abbreviations
for access into the |city_link| array.

(Here's a gotcha under AIX.  I used to use \CWEB/'s @@d facility to
make these preprocessor definitions.  But that puts the definitions
at the start of the \CEE/ file, before the includes.  But the |prev|
macro conflicts with a \file{stdio.h} structure definition.  So I make
these definitions after the standard includes.  There is still a possibility
that a macro, \eg\ |putchar|, 
might want to use the |prev| field in the \file{stdio} 
structure.  However, until I come across this problem, I'll stick to the
current solution.  I suppose I could use a |union| type to alias 
|prev| to |link[LINK_PREV]|, but that would make everything far uglier.)
@^system dependencies@>

@<Module type definitions@>=

#define LINK_PREV 0
#define LINK_NEXT 1
#define prev link[LINK_PREV]
#define next link[LINK_NEXT]
#define CITY_LINK_HEAD 0
#define CITY_LINK_TAIL 1
#define head city_link[CITY_LINK_HEAD]
#define tail city_link[CITY_LINK_TAIL]

typedef struct parent_node_s {
	int seq;	/* Sequence number.  Fredman \etal.\ call this |ID| */
	int reverse;	/* Either 0 (forward), or 1 (reverse) */
	struct parent_node_s *link[2];
	struct city_node_s *city_link[2];
} parent_node_t;

typedef struct city_node_s {
	struct parent_node_s *parent;
	int seq;	/* Sequence number.  Fredman \etal.\ call this |ID| */
	struct city_node_s *link[2];
} city_node_t;

@ The city nodes and parent nodes will reside in statically allocated
arrays.  These are |city_node| and |parent_node|, respectively.

%% We'll also need a mapping  from city numbers to city nodes.  This is done
%% by the array |city_to_node|.  

@<Module variables@>=
static parent_node_t *parent_node=NULL;
static city_node_t *city_node=NULL;


@ These variables get allocated in the setup routine.  We will be adding
to this code later, so we separate it out in a new named section.

@<Subroutines@>=
void
twolevel_setup(const int num_vertices, const int start_seg_size) {
	@<Set up the two-level data structure@>@;
}

@ We also need a symmetrical tear down routine.
@<Subroutines@>=
void 
twolevel_cleanup(void) {
	@<Clean up the two-level data structure@>@;
}

@ We must export these routines.
@<Exported subroutines@>=
void twolevel_setup(const int num_vertices, const int start_seg_size);
void twolevel_cleanup(void);

@  We allocate these arrays using the |new_arr_of| macro from the 
\module{MEMORY} module.
@<Set up the two-level data structure@>=
city_node = new_arr_of(city_node_t,num_vertices);

@ We need the interface to the \module{MEMORY} module.    We'll also later do
sanity checks using the macros from the \module{ERROR} module.

@<Module headers@>=
#include "error.h"
#include "memory.h"

@ We use the |free_mem| macro to deallocate these arrays.
@<Clean up the two-level data structure@>=
free_mem(city_node);


@ There are at least two possible descriptions of the two-level
tree data structure.
To derive good
worst-case time bounds, segment sizes are kept between $\sqrt{n}/2$ and
$2\sqrt{n}$ cities via explicit balancing.   
Under these conditions, the queries take constant time, and the |flip|
update takes $O(\sqrt{n})$ time.

However, the balancing required to achieve that worst-case time
for flips can be quite time consuming.  
For practical purposes, Fredman \etal.~describe a variant
where each segment starts out with roughly |groupsize| elements.
Furthermore, explicit balancing is dispensed with in favour 
of implicit balancing with lower overhead .

In the practical variant, queries remain constant time, but 
flips may degenerate to linear time.  However, Fredman \etal.~cite
the conventional wisdom that data structures stay balanced in practice,
so they expect this bad behaviour to be rare.

We'll see later what implicit balancing entails, but for now we
declare the |groupsize| variable.

It will also be convenient to know the number of groups, |num_groups|.

@<Module variables@>=
static int groupsize, num_groups;

@ I'll leave the setting of |groupsize| to the main module; it's passed
as a parameter to the setup routine.  However, Fredman \etal.'s experiments
were run with |groupsize==100| on instances of $10^3$ to $10^5$ cities,
and |groupsize==200| on instances of $10^6$ cities.  For these million-city
instances, this larger group size made each |flip| 27\% faster on average;
performance was stable up to a group size of 800.

Given an initial segment size of |groupsize|, there should be
$\lfloor$|num_vertices/ groupsize|$\rfloor$ parent nodes.  

@<Set up the two-level data structure@>=
groupsize = start_seg_size;
num_groups = num_vertices/groupsize;
parent_node = new_arr_of(parent_node_t,num_groups);


@ While we're at it, let's  write down how we 
deallocate the |parent_node| array.
@<Clean up the two-level data structure@>=
free_mem(parent_node);

@ It will also be convenient to remember the number of cities; we'll
store it in the variable |n|.
@<Module variables@>=
static int n=0;

@ We set it at setup time. 
@<Set up the two-level data structure@>=
n = num_vertices;

@ For defensiveness' sake, we'll put a garbage value into it at cleanup time.
@<Clean up the two-level data structure@>=
n = 0;

@*Initializing the two-level tree.
The procedure |twolevel_set(int *t)| takes a tour represented
as an array of $n$ integers
and changes the two-level tree to
match it.  It balances the segment lengths as best as it can.

@ We have a choice to make here.  We must decide how to map
cities to city nodes; this might have consequences on how 
well the cache will perform over the duration of the local optimization
phase of the program.
Our choices are as follows.
We can store the data for city $i$
in the $i$'th city node;
or, we could store the data for the city that appears in position $i$ of the
tour
in the $i$'th city node.

Storing the data for city $i$ in the $i$'th node carries any locality
properties of the initial city ordering over to this module.
For instance, if we preprocess the data using a space-filling curve to try 
to achieve better locality, then this first scheme carries that mapping into
the manipulations of the two-level tree.  In this way, this scheme
supports the efforts of that data rearrangement.

On the other hand, storing the data in the order that it appears in 
the tour might achieve better locality initially.  However, starting
tours such as the Greedy/Multiple Fragment tours have some very large
defects.  These defects both increase the tour size, but more importantly
for our current
discussion,  also likely decrease locality for the duration of the 
local optimization phase.

For this reason, I've chosen to map the data for city $i$ onto element
$i$ of the |city_node| array.

% Another point is that sequence numbers for cities are initialized to
%be balanced around zero.  That is, they range roughly over the
%interval from $-k$ to $k$, where $k$ is half the number of cities
%in the group.  This is done in the hope that sequence numbers will 
%not go near the overflow values of |INT_MAX| or |INT_MIN|, where
%we'd be in danger of making integer comparisons go wrong.
%
%Hang on: as long as indices are consecutive, we don't have to
%worry about integer comparisons going wrong anyway!  Unless, of course,
%there are more than |UINT_MAX| cities in each segment --- that's $2^{32}-1$
%on a 32-bit machine.  But we're only targeting for up to a million cities, so
%it shouldn't become a problem.

On another front, it turns out that \CEE/ doesn't guarantee that remainders
will be non-negative when the dividend is negative.  
But the pointer arithmetic for initializing sibling pointers
relies on this property.
So we must use
|(group-1+num_groups)%num_groups| in place of the plainer
|(group-1)%num_groups| in place of the plainer.  Similarly,
|(i-1+n)%n| replaces
|(i-1)%n|.

@<Subroutines@>=
void
twolevel_set(int const *tour) {
	int i, j, group, num_big_groups = n % num_groups, base_group_size = n/num_groups;
	for ( i=0, group=0; i<n; group++ ) {
		const int this_group_size = base_group_size + (group<num_big_groups);
		parent_node[group].head = city_node+tour[i];
		parent_node[group].tail = city_node+tour[i+this_group_size-1];
		parent_node[group].reverse = 0;
		parent_node[group].seq = group;
		parent_node[group].prev = parent_node + ((group-1+num_groups) % num_groups);
		parent_node[group].next = parent_node + ((group+1) % num_groups);
		for ( j=0; j<this_group_size ; j++, i++ ) {
			city_node[tour[i]].parent = parent_node+group;
			city_node[tour[i]].seq = j;
			city_node[tour[i]].prev = city_node+tour[(i-1+n)%n];
			city_node[tour[i]].next = city_node+tour[(i+1)%n];
		}
	}
	errorif( i != n || group != num_groups, "Bug in my 'rithmetic");
}

@ We must export this routine.
@<Exported subroutines@>=
void twolevel_set(int const *tour);


@*Variations in the data structure.  
There are few other potential variations on the data structure.  I hope
to implement a few of them, to study their tradeoffs.

@ First, Fredman \etal.~maintian links between cities at the ends of 
segments.  An alternative is to keep distinct linked lists, one 
per segment.  That is, don't link ends of segments together at the
city node level.

This variation is  designed to  make |flip|s faster.  However, 
|prev| and |next| queries might be slower because they would have
to check for a |NULL| pointer.  The |between| query ought to be unaffected.

@ Second, we might choose to never move a city from its node.  We would
change pointers instead.  When this is done, we don't have to explicitly
store the city number in each city node.  This should make things faster
because the cache will be able to store a larger portion of the
city node array.

I have to think about whether this change involves extra pointer 
manipulation.  I ought to measure the difference from the standard 
data structure.

@ Third, perhaps we can borrow use some approximate counting techniques
such as are found in good implementations of the 
$<INSERT,DELETE,RANK>$ ADT.  See Dietz (INSERT REFERENCE).

@ Fourth, perhaps we can soften the requirement for consecutive
numberings within segments and at the root level.  (Q: Is this
even done at all in the 
`practical' variation?)  Instead of wholesale renumbering, just
take an average of neighbours when inserting a node between two others.
Then ``rebalance'' when we run out of precision.  In the common case,
rebalancing ought to be rare.


@*Queries.
We'll define the |prev| and |next| queries first.  The  |between| query
will follow later.

The only interesting thing about the |prev| and |next| queries is that
we must decide which link to follow by examining the parent's 
reversal bit.  We take advantage of the fact that the reversal bit
is either 0 or 1 by exclusive-or'ing it with an index into the
city node's link array.  This straightens the code path: the decision is
made 
via arithemtic and indexing, not by branching in the code.  That should
save time on heavily pipelined architectures.
@^pipelined architectures@>
In fact, this trick, er, {\it technique}, 
is the main motivation for declaring the link
pointers as an array.
@^trick@>
@^technique@>

Both queries take constant time.

@<Subroutines@>=
int
twolevel_next(int a) {
	const city_node_t *ca = city_node+a;
	return (ca->link[ LINK_NEXT ^ ca->parent->reverse ])-city_node;
}

int
twolevel_prev(int a) {
	const city_node_t *ca = city_node+a;
	return (ca->link[ LINK_PREV ^ ca->parent->reverse ])-city_node;
}

@ We must export these routines.
@<Exported subroutines@>=
int twolevel_next(int a);
int twolevel_prev(int a);

@ Query |between(a,b,c)| asks: ``In a forward traversal starting at $a$,
do we reach $b$ no later than $c$?''

The |between| query is drudgery in comparison with queries |prev|
and |next|.  It is a case analysis
on the cities' intra-segment number, 
parent numbers, and parent reversal
bits.
Fredman \etal.~(page 444) describe this query quite well, and I take
this description mostly from them.

If all three cities have distinct parents, then we need only compare
their parents' sequence numbers.

If all three cities are in the same segment, then we need only 
compare their intra-segment sequence numbers.  The actual comparison in
this case depends on the common parent's reversal bit.

If exactly two of the cities have the same parent, then the answer
depends only on their intra-segment sequence numbers and their common
parent's reversal bit.
The placement of the third city is irrelevent: it is outside the
segment.

In some of the conditional expressions in the following,
I use bitwise operators $\mid$ and |&|
in place of short-circuiting
operators |||| and |&&|.    
Specifically, I do this when both operands of the logical operators
are comparsions.  I expect that the extra time performing a possibly redundant 
integer comparison is worth the savings on 
pipelined architectures in not having to always take
a branch.
This trick also relies on \CEE/'s semantics
of providing consistent values of 0 and 1 for boolean expressions
evaluating to false and true values, respectively.
@^pipelined architectures@>
@^trick@>
@^technique@>

I also use bitwise exclusive-or, |^|, but there is no short-circuiting
logical exclusive-or operator in \CEE/;
exclusive-or must always evaluate both its arguments anyway.

We're also careful to use as sequence numbers the offsets from 
the beginning of the segment instead of the bare intra-segment sequence number.
This protects us in case some sequence of flips has forced the sequence
numbers to migrate and wrap around at one of the ends of the
integer range, |INT_MIN|$\ldots$|INT_MAX|.

This query takes constant time.

@<Subroutines@>=
int
twolevel_between(int a, int b, int c) {
	const city_node_t *ca = city_node+a, *cb= city_node+b, *cc = city_node+c;
	const parent_node_t *pa = ca->parent, *pb = cb->parent, *pc = cc->parent;
	const int sa=ca->seq-pa->head->seq, sb=cb->seq-pb->head->seq, sc=cc->seq-pc->head->seq;

	if ( pa == pb ) 
		if ( pa == pc) 	/* All in the same segment */
			if ( pa->reverse )
				 return (sa>=sb? ((sb>=sc)|(sc>sa)) : ((sb>=sc) & (sc>sa)));
			else return (sa<=sb? ((sb<=sc)|(sc<sa)) : ((sb<=sc) & (sc<sa)));
		else 	/* |a|, |b| in same, |c| elswhere */
		return (sa==sb) | (pa->reverse ^ (sa<sb));
	else 
		if ( pa==pc )	/* |a|, |c| in same, |b| elswhere */
			return (sa!=sc) & (pa->reverse ^ (sa>sc));
		else 
			if (pb==pc) /* |b|, |c| in same, |a| elswhere */
				return (sb==sc) | ((pb->reverse) ^ (sb<sc));
			else {/* All in different; much like all in the same, but use parent numbers. */
				const int psa=pa->seq, psb=pb->seq, psc=pc->seq;
				return (psa<=psb? ((psb<=psc)|(psc<psa)) : ((psb<=psc) & (psc<psa)));
			}
}

@ We export this function.
@<Exported subroutines@>=
int twolevel_between(int a, int b, int c);


@*Flipping.
Flipping is the most difficult operation, as it changes the data structure,
and must update pointers, reversal bits, and sequence numbers.

With explicit balancing, one can make a flip take $O(\sqrt{n})$ time;
Fredman \etal.~describe how.
However, I've implemented the practical variant they describe. First,
it uses
implicit balancing instead of explicit balancing.
Second, 
when 
the portion of the tour to be flipped
is no more than $3/4\times groupsize$ and lies entirely within one segment,
that segment is split and reversed using its parent's reversal bit.
This practical variant incurs a lower overhead, but its performance
may degenerate to $\Omega(n)$ time in the worst case.  One hopes that
this occurs only vary rarely.

@ 
An important observation is that we can flip either the $b-d$ portion 
of the tour
or the $a-c$ portion.  We have this freedom because the tour may be 
arbitrarily oriented after
the flip.  
This simplifies the code somewhat.

Flipping a tour segment splits into three cases.  

The first case occurs if 
either the $b-d$ portion or the $a-c$ portion
lies entirely within one city list segment.

The second case occurs when both the $a-c$ and the $b-c$ parts are made
up only of entire segments.  That is, no segment contains both 
$a$ and $d$ nor both $c$ and $b$.

The third case covers the rest of the possibilities.  Fortunately, 
we may always rearrange things so that the second case applies.

(I used to define |SWAP| and |abs| globally using \CWEB/'s {\tt @@d}
construct, but that interferes with the IRIX 5.3 definition of |abs|
in \file{stdlib.h}.  So I moved these definitions to after that inclusion.)
@^system dependencies@>
@^IRIX@>

@<Subroutines@>=
#define SWAP(x,y,t)  ((t)=(x),(x)=(y),(y)=(t))
#define abs(x) ((x)<0?-(x):(x))
void
twolevel_flip(int a, int b, int c, int d) {
	city_node_t *ca = city_node+a, *cb= city_node+b, 
		*cc = city_node+c,*cd = city_node+d, *tcn;
	int psa=ca->parent->seq, psb=cb->parent->seq, 
		psc=cc->parent->seq, psd=cd->parent->seq, ti;
#if defined(TWOLEVEL_FLIP_CHECK_PRECONDITION)
	errorif( a != twolevel_next(b), "a != twolevel_next(b)" );
	errorif( d != twolevel_next(c), "d != twolevel_next(c)" );
#endif 

	@<Handle case 1 of flipping, if it applies@>@;
	if (psa==psb) {		/* Arrange for case 2 to apply, part 1. */
		@<Split the $a-b$ segment@>@;
	}
	if (psc==psd) {		/* Arrange for case 2 to apply, part 2. */
		@<Split the $c-d$ segment@>@;
	}
	@<Flip a sequence of segments@>@;
}

@ We export this routine.
@<Exported subroutines@>=
void twolevel_flip(int a, int b, int c, int d);

@ As I've said, 
the first case occurs if 
either the $b-d$ portion or the $a-c$ portion
lies entirely within one city list segment.

Note that both portions can't both be in single segments unless there
are at most two segments; that's a degenerate case.  I had given some
thought to adding code to flip the shorter portion until I realized
this fact.  So, following Bentley and McIlroy's advice (INSERT REFERENCE), 
I'm keeping
the code simple.

This code gets used in three places, as we'll see.  So I've split it off
and made it a separate section.

@<Handle case 1 of flipping, if it applies@>=
@<Verbose: handle case 1@>@;
if ( psb==psd ) {	/* Case 1, but rename so that $a-c$ lies in one segment. */
	SWAP(ca,cb,tcn); @+ SWAP(cc,cd,tcn);
	SWAP(psa,psb,ti);@+  SWAP(psc,psd,ti);
	/* |a|, |b|, |c|, |d| are not used again. */
}
if ( psa==psc ) {	/* Case 1, really do it. */
	@<Flip: |ca| and |cc| are in the same segment@>@;
	return;
}

@ Let's start with the first case,
\ie, when both $a$ and $c$ lie in the same data structure segment.
This means one of two things.  Either the $a-c$ portion lies entirely within
this segment, or the $b-d$ portion lies within this segment and is
sandwiched by cities $a$ and $c$.

First we rename variables so that the list of cities from
|ca| to |cc| lies entirely within one segment and contains no part
of the |cb| to |cd| portion of the tour.
Then we flip the segment.


%Now, it may be the case that the $b-d$ segment lies entirely within this
%segment, and is sandwiched by cities |ca| and |cc|.  It would then be 
%wrong to flip the sequence of cities from |ca| through |cc| within this
%segment: that would have the effect of reversing the $b-d$ segment, {\it and\/}
%swapping cities $a$ and $c$.  So we must check for this condition and
%move |u| and |v| one city `inward' if it is the case.  Note that it is
%sufficient to check that |u->next| ...

@<Flip: |ca| and |cc| are in the same segment@>=
@<Rename so that the |a-c| portion lies entirely in one segment@>@;
@<Flip: |ca| to |cc| lies entirely within one segment@>@;

@  
We rename variables so that variables
|ca| and |cc| point to the portion of the tour 
lying entirely within this segment.
This condition is convenient to check if we first rename variables so that
|ca| is to the left of |cc|.

Of course, if |ca==cc|, then the |ca| to |cc| portion of the tour is just
one city long, so there is no work to do.  We don't check for this condition
because we think it will be common. Rather, we do it so that checking
for the containment of the |cb| to |cd| portion easy: it becomes the
simple test |ca->next == cb|.

It turns out that we won't be needing the identities of cities |b| or |d|
any longer.  So the pair of assignments |ca=cb,cc=cd| is safe in place of a 
set of full |SWAP|s.  

If these assignments {\it are\/} performed, then
|ca| still lies on or to the left of |cc|.  


@<Rename so that the |a-c| portion lies entirely in one segment@>=
if ( ca == cc ) return;	/* Rerversing a length-1 list is trivial */
if ( ca->seq > cc->seq ) SWAP(ca,cc,tcn),SWAP(cb,cd,tcn);	/* Make $a$ come before $c$ */
if ( ca->next == cb ) ca=cb,cc=cd;	/* Make $a-c$ lie entirely in this segment */

@ Now we can get down to the business of 
flipping the $a-c$ portion of the tour.
If it is long enough, then
it makes sense to implictly rebalance:
split the ends off and turn
on its parent's reversal bit.
Otherwise, we physically move the cities.


@<Flip: |ca| to |cc| lies entirely within one segment@>=
if ( abs(ca->seq-cc->seq) > implicit_balance_threshhold ) {
	@<Split the ends off and flip the parent's reversal bit@>@;
} else {
	@<Reverse the list from |ca| to |cc|@>@;
}

@ The variable |implicit_balance_threshhold| is set when we set up
the data structure.  It is given the value of $3/4\times groupsize$,
as prescribed by Fredman \etal.

@<Set up the two-level data structure@>=
implicit_balance_threshhold = (3 * groupsize)/4;

@ It is local to this module.
@<Module variables@>=
static int implicit_balance_threshhold;



@ Lets do the simpler part: moving links around to flip a tour segment.

First we reverse the sequence  numbers, then we reverse the list by
permuting pointers.

There will be several places where we'll need to reverse a sequence of
cities.  That code is generalized by using variables |u|  and |v| to
denote the first and last cities to be reversed; city |u| occurs on or to
the left of |v|.  We already assume that |ca| occurs on or to the
left of |cc|.

We reverse a segment by swapping each city's |next| and |prev| pointers.
This way, what was a city's predecessor is now its successor, and
vice versa.  We must ensure that
pointers from outside the reversed segment get 
updated to point to the appropriate
end cities.  The outbound sibling pointers inside the segment are fixed by
the |SWAP(u->prev,v->next)| code: remember they will be swapped appropriately
when all the sibling links are swapped.




@<Reverse the list from |ca| to |cc|@>=
{ city_node_t *u = ca, *v = cc;
@<Reverse the city sequence numbers from |u| to |v|@>@;
@<Make external pointers point to the other of |u|, |v|@>@;
SWAP(u->prev,v->next,tcn);		/* Fix outbound sibling pointers */
@<Swap links from |u| to |v|@>@;
}

@ Now, |u| and |v| have been chosen so that |v| may be found by following
zero or more |next| pointers from |u| without leaving this segment.
Also, sequence numbers increase as we follow |next| pointers.
This allows us
to just overwrite the sequence numbers; we don't need to do any swapping.

@<Reverse the city sequence numbers from |u| to |v|@>=
{	city_node_t *i=u, *done=v->next;
	int s;
	for ( s=v->seq,i=u; i!=done ; i=i->next,s-- ){
		i->seq=s;
	}
}

@ Now that we've updated sequence numbers, we can update pointers.
The pointers that might need updating are |head| and |tail| pointers,
and |prev| and |next| pointers.

The code for updating the |prev| and |next| pointers is just 
a parallel assignment.  Unfortunately, parallel
assignment is awkward in \CEE/; parallel bindings are easy in \ML/.
@^ML@>
We need parallel assignment because we might be in the degenerate case
where we are flipping the entire tour except for one node.   In that case,
we shouldn't change its |next| pointer from |ca|, say, to |cc|, {\it and
then back again.}  Think about it.

Similarly, there might only be one node in the segment; it would be
both the head and the tail.  But then updating it twice doesn't pose
any problems, for then |ca==cc|!.  So we don't need a parallel assignment
in fixing the head and tail pointers.

Recall that we assume that |u| and |v| are in the same segment, 
and therefore have the same parent.  Furthermore, |u| comes on or before
|v|. 

@<Make external pointers point to the other of |u|, |v|@>=
{ parent_node_t *p = u->parent;
const int upn_to_v = u->prev->next == u, upp_to_v = u->prev->prev == u,
vnp_to_u = v->next->prev == v, vnn_to_u = v->next->next == v;
if ( upn_to_v ) u->prev->next = v;
if ( upp_to_v ) u->prev->prev = v;
if ( vnp_to_u ) v->next->prev = u; 
if ( vnn_to_u ) v->next->next = u;
if ( p->head == ca ) p->head=cc;	/* Now fix |head| and |tail| */
else if ( p->head== cc ) p->head=ca;
if ( p->tail == ca ) p->tail=cc;
else if ( p->tail== cc ) p->tail=ca;
}


@ This code requires that sequence numbers increase as we follow |next| 
pointers.  It assumes that |u| occurs at the same point or to the left of |v|.

%%I've used fresh variables |i| and |j| because I want to be as hygienic 
%%as possible:
%%don't destroy values unnecessarily.  A good optimizing compiler will
%% reuse the registers anyway.

@<Swap links from |u| to |v|@>=
{
	city_node_t *i=u, *done = v->next;
	for ( i=u; i != done; i=i->prev ) {	/* Yes, |prev|: it's the old |next| pointer. */
		SWAP(i->next,i->prev,tcn);
	}
}

@ Let's do the other part: implict rebalancing. This involves
splitting the ends off the $a-c$ segment, merging those ends
with their neighbours, swapping the inbound sibling pointers, and
then flipping their parent's reversal bit.

We've already arranged things so that 
that |ca|'s sequence number is
no greater than |cc|'s sequence number, \ie, that we can find |cc| by
following zero or more |next| pointers starting at node |ca| without
leaving the segment.


@<Split the ends off and flip the parent's reversal bit@>=
@<Split off the end to the left of |ca|@>@;
@<Split off the end to the right of |cc|@>@;
@<Fix sibling pointers to and from |ca| and |cc|@>@;
ca->parent->reverse ^= 1;
@<Verbose: implicit rebalance done@>@;


@ The part of the segment to the left of |ca| is split off and merged
with the segment to its left (left according to the |prev| link of the
head of this segment).  
We must be careful for a few reasons.

First, there
are four possible combined settings for the reversal bits of this
segment and the segment to the left.  

Second, we must set the city |prev| and |next| links so that they
are correct {\it after\/} the parent's reversal bit is flipped.

@<Split off the end to the left of |ca|@>=
@<Verbose: split off the end to the left of |ca| begin@>@;
{ 	parent_node_t *p = ca->parent;
	city_node_t *lc=p->head; 		/* City at left end of split off segment. */
	city_node_t *rc=ca->prev;		/* City at right end of split off segment */
	city_node_t *llc=lc->prev;		/* New sibling of |lc|: ``left of |lc|'' */
	parent_node_t *lp=llc->parent;	/* Parent of the segment to be merged into */
	int lpr = lp->reverse, pr=p->reverse;
	errorif(lp==p,"Bug");
	if ( lc != ca ) {	/* There is work to do. */
		@<Split left: set the end city links@>@;
		@<Split left: set the per-city data in the split off segment@>@;
	}
}
@<Verbose: split off the end to the left of |ca| end@>@;

@ This section updates any pointers to the end cities of the split off
portion of the segment.  It helps to look at the input and output
pointer ``flows'' to/from this split off portion.  This way we can
hopefully avoid missing updating a pointer.

The pointers coming {\it into\/} this split off portion of the segment are as
follows:
there is one sibling pointer pointing to the left end of the
list, |llc->link[lpr^LINK_NEXT]|; there is one sibling pointer pointing to the
right end of the list, |ca->prev|; finally there is a head pointer from
the old parent, |p->head|, and a head/tail pointer from the
new parent, |lp->city_link[pr^lpr^CITY_LINK_TAIL]|.  
Interestingly, the sibling pointers need to be changed depending on the
context in which this code is used, so we won't change them here.

The pointers coming {\it out of\/} this split off portion of the segment are as
follows:
there is one sibling pointer pointing from the left end of the
list, |lc->prev|; there is one sibling pointer pointing from the
right end of the list, |rc->next|; finally there are parent pointers 
at each node in the list.
All these outgoing pointers will be handled as part of the per-city changes.

@<Split left: set the end city links@>=
p->head = ca;
lp->city_link[(pr==lpr)?CITY_LINK_TAIL:CITY_LINK_HEAD] = rc;


@ Each city node in the split off segment must be updated in the
following ways.

First, we must set the sequence numbers so they are consecutive 
with those in the segment to the left.    We use two variables
to set them: |seq_num| begins as the sequence number that city |lc|
should be set to; |seq_inc| is the increment in sequence numbers that
should take effect in traversing the list from |lc| through to |rc|.

There are two cases to consider.  
If the two segments have the same orientation, then 
we're appending the |lc| to |rc| list to the right end of the segment
to the left.
So
|lc|'s new sequence number should be |llc->seq+1| and they should increase,
\ie\ |seq_inc| should be 1.
Otherwise, the segments have different orientations: |llc| is the
head of its and we'll be moving the |lc| to |rc| list
to the left of |llc|.  In this case, |lc|'s new sequence number should
be |llc->seq-1| and they should decrease, \ie\ |seq_num| should be -1.

Second, if the orientations of the old and the new segments are different,
then we must reverse the links of the moved portion of the linked list.

I've combined these functions into one segment because the
traversal code changes according whether we change the sense
of |prev| and |next|.  In particular, |link[succ_link]| traverses the
list from |u| to |v|, which is left to right in the original list.

@<Split left: set the per-city data in the split off segment@>=
{ 
city_node_t *i, *u=lc, *v=rc;
int succ_link, seq_inc, seq_num;
if ( lpr==pr ) {	/* Move to right end. */
	succ_link=LINK_NEXT;
	seq_inc = 1;
	seq_num = llc->seq + 1;
} else {	/* Move to left end. */
	succ_link = LINK_PREV;
	seq_inc = -1;
	seq_num = llc->seq - 1;
	@<Swap links from |u| to |v|@>@;
}
for ( i=lc;i!=rc;i=i->link[succ_link], seq_num+= seq_inc ) {	/* Set parent pointers and
sequence numbers */
	i->parent = lp;
	i->seq = seq_num;
}
i->parent = lp;
i->seq = seq_num;
}

@ Splitting off the right end is analogous to splitting off the left end,
but with a slight twist.
First, we make the following exchanges:
|next|$\leftrightarrow$|prev|;
|head|$\leftrightarrow$|tail|; 
|l|$\leftrightarrow$|r|, in variable names;
and |cc|$\leftrightarrow$|ca|.  The twist comes when setting sequence numbers;
its explained below.

Here's righthand version of the top-level section.  

@<Split off the end to the right of |cc|@>=
@<Verbose: split off the end to the right of |cc| begin@>@;
{ 	parent_node_t *p = cc->parent;
	city_node_t *rc=p->tail; 		/* City at right end of split off segment */
	city_node_t *lc=cc->next;		/* City at left end of split off segment */
	city_node_t *rrc=rc->next;		/* New sibling of |rc|: ``right of |rc|'' */
	parent_node_t *rp=rrc->parent;	/* Parent of the segment to be merged into */
	int rpr = rp->reverse, pr=p->reverse;
	errorif(rp==p,"Bug");
	if ( rc != cc ) {	/* There is work to do. */
		@<Split right: set the end city links@>@;
		@<Split right: set the per-city data in the split off segment@>@;
	}
}
@<Verbose: split off the end to the right of |cc| end@>@;

@ Setting the end city links on the right is analogous to setting them
on the left.
@<Split right: set the end city links@>=
p->tail = cc;
rp->city_link[(pr==rpr)?CITY_LINK_HEAD:CITY_LINK_TAIL] = lc;

@ Setting the per-city data on the right hand side is also analogous.  

As in splitting a segment to the left, |seq_num| 
is again the new sequence number of |lc|
and |seq_inc| is the increment on sequence numbers as we travel from
|lc| to |rc|.  

The twist in setting the sequence numbers that I mentioned earlier 
is as follows.  When the orientations of the two segments are the
same, then we're moving the |lc| to |rc| list to the {\it left\/}
end of the new segment, and so |lc| must start out as |rrc->seq-1|
minus the length of the |lc| to |rc| segment; the increment should
again be 1.  When the orientations are different, we'll be adding
to the right end of the new segment, with |rc| at the beginning and
|lc| becoming the new tail.  In this case, 
|lc|'s new sequence number should be |rrc->seq| plus the length
of the |lc| to |rc| list, and |seq_inc| should be -1.

@<Split right: set the per-city data in the split off segment@>=
{ 
city_node_t *i, *u=lc, *v=rc;
int succ_link, seq_inc, seq_num;
if ( rpr==pr ) {	/* Move to left end. */
	succ_link=LINK_NEXT;
	seq_inc = 1;
	seq_num = rrc->seq + u->seq-v->seq - 1;
} else {	/* Move to right end. */
	succ_link = LINK_PREV;
	seq_inc = -1;
	seq_num = rrc->seq + v->seq-u->seq + 1;
	@<Swap links from |u| to |v|@>@;
}
for ( i=lc;i!=rc;i=i->link[succ_link], seq_num+= seq_inc ) {	
	/* Set parent pointers and sequence numbers */
	i->parent = rp;
	i->seq = seq_num;
}
i->parent = rp;
i->seq = seq_num;
}


@ We're reversing a single segment and must therefore swap the two inbound
sibling pointers and the two outbound pointers.  

In more detail, there are four pointers to change.
The sibling 
pointer that used to point to |cc| should
now point to |ca|, and vice versa.  
The code is only tricky because we
must handle all combinations of reversal bits of the two bordering segments.
Then, |ca->prev| and |cc->next| should be swapped; these are the outbound
sibling pointers.

This section completes the code
to handle the first case in flipping.

@<Fix sibling pointers to and from |ca| and |cc|@>=
{
	city_node_t *l=ca->prev, *r = cc->next;
	parent_node_t *lp= l->parent, *rp = r->parent;
	const int ac_rev=ca->parent->reverse;
	city_node_t **inbound_l = &l->link[LINK_NEXT^lp->reverse^ac_rev],
		**inbound_r = &r->link[LINK_PREV^rp->reverse^ac_rev];
	errorif(*inbound_l != ca,
		"Inbound left %d != ca %d", 
		*inbound_l - city_node, ca-city_node);
	errorif(*inbound_r != cc,
		"Inbound right %d != cc %d", 
		*inbound_r - city_node, cc-city_node);
	SWAP(*inbound_l,*inbound_r,tcn);
	SWAP(ca->prev,cc->next,tcn);
}

@ Now we can move on to handling the third case for flipping:
either $a$ and $b$ are in the same segment, or $c$ and $d$ are.
We handle this case by reducing it to the second case.  That is,
we split segments so that $a$ and $b$ are in different segments,
and $d$ and $c$ are in different segments.

@ Let's tackle splitting the $a-b$ segment first.
Thankfully, we can reuse much of the code we've just written for implicit
balancing in case 1.  In particular, we've got code to split off the 
portion of a segment to the left of the pointer |ca|, and code
to split off code to the right of pointer |cc|.

That splitting code takes time proportional to the length of list that is
split off.  So we prefer to split off the shorter portion of the segment.

@<Split the $a-b$ segment@>=
@<Verbose: split the $a-b$ segment@>@;
{ city_node_t *l, *r; parent_node_t *p = ca->parent; /* Same as |cb->parent| */
if ( ca->seq < cb->seq ) l=ca, r=cb;
else l=cb, r=ca;
if ( l->seq - p->head->seq < p->tail->seq - r->seq ) {
	city_node_t *ca=r;	/* No relation to the previous |ca| */
	@<Split off the end to the left of |ca|@>@;
} else {
	city_node_t *cc=l;	/* No relation to the previous |cc| */
	@<Split off the end to the right of |cc|@>@;
}
}
@<Renew the parent sequence numbers@>@;

@ We've moved one of $a$ or $b$.  We need to update its parent sequence number.
It's simpler (and probably faster) to just update both than to figure
out (or remember) which one was moved.

Cities |c| and |d| might have been moved with the $a-b$ split.  We renew
their parent sequence numbers just in case.

The nice symmetry of this code allows us to use it after we split
the segment containing $c$ and $d$.

@<Renew the parent sequence numbers@>=
psa=ca->parent->seq; 
psb=cb->parent->seq;
psc=cc->parent->seq; 
psd=cd->parent->seq;

@ Our aim so far in this third case is to arrange things so that case 2 applies,
\ie, so that both $a-c$ and $b-d$ are each a contiguous sequence of complete 
segments.  However once we've split the $a-b$ segment, the {\it first\/}
case might apply. That is, either $a-c$ or $b-d$ might lie entirely within
one segment.  
If this is the case, then we update the data structure as in
case 1.  Fortunately, \CWEB/ lets us do this quite naturally by reusing
that section.  Recall that if case 1 does apply, then that code
performs its own |return| to complete this procedure execution.

@<Split the $a-b$ segment@>=
@<Handle case 1 of flipping, if it applies@>@;

@ Now lets split the $c-d$ segment.  This is analogous to splitting the
$a-b$ segment.

@<Split the $c-d$ segment@>=
@<Verbose: split the $c-d$ segment@>@;
{ city_node_t *l, *r; parent_node_t *p = cc->parent;  /* Same as |cd->parent| */
if ( cc->seq < cd->seq ) l=cc, r=cd;
else l=cd, r=cc;
if ( l->seq - p->head->seq < p->tail->seq - r->seq ) {
	city_node_t *ca=r;	/* No relation to the previous |ca| */
	@<Split off the end to the left of |ca|@>@;
} else {
	city_node_t *cc=l;	/* No relation to the previous |cc| */
	@<Split off the end to the right of |cc|@>@;
}
}
@<Renew the parent sequence numbers@>@;

@ Just as in the $a-b$ case, $c$ may have been moved into $a$'s segment,
or $d$ may have been moved into $b$'s segment.   If either has occurred,
then we're back to case 1.  So again, we check for case 1 and handle it
if it occurs.

@<Split the $c-d$ segment@>=
@<Handle case 1 of flipping, if it applies@>@;

@ Now we're ready to handle case 2: each of the $a-c$ and the $b-d$ portions
of the tour consists of a contiguous sequence of complete segments.

As with flipping a sequence of city nodes, we first rename cities so that
the portion to be flipped is delimited by the parents of cities |a| and |c|.

@<Flip a sequence of segments@>=
@<Verbose: flip a sequence of segments@>@;
errorif((psa==psb||psc==psd),"psa %d==psb %d or psc %d == psd %d",psa,psb,psc,psd);
@<Rename so that |psa| through |psc| is shorter than |psb| through |psd|@>@;
@<Flip the sequence of segments from $a$ to $c$@>@;

@
We prefer to flip the shorter of the two sequences of segments.  
However, we must know how the sequences are laid out before we
know which is shorter.  Schematically, the parents of the cities $a$, $b$,
$c$, and $d$ may be laid out in forward order, $abdc$, in reverse, $cdba$,
or in any of the three rotational variants of each of these:
$bdca$, $dcab$, $cabd$, or $dbac$, $bacd$, $acdb$.  We'd rather not 
expand the code unnecessarily by writing eight different versions, so
we'll rename cities so that the sequence of parents from |a| through |c|
is to be reversed.

The first step of this renaming task is to identify which  of the above
eight orderings hold.  There are two tricks to doing this easily.
First, we filter out trivial flips, \ie~where
one of the portions consists of a single parent.  
We want the predecessor and successor
of the parent of an end city (one of $a$, $b$, $c$, or $d$) to be 
in the other portion.  
Second, we must know the number of groups, |numgroups|; this makes identifying
successors and predecessors easy by using modular arithmetic.

We will make use of |normp| and |normm|, a pair of 
a fast but restricted  macros for the remainder modulo |num_groups|.
Macro |normp| normalizes numbers from $[0,2\hbox{|num_groups|}-1]$ down
to $[0,\hbox{|num_groups|}-1]$; it is used when adding two numbers (remember
$p$ for `plus').
Macro |normm| normalizes numbers from 
$[-\hbox{|num_groups|},\hbox{|num_groups|}-1]$ down
to $[0,\hbox{|num_groups|}-1]$; it is used when subtracting 
two numbers (remember
$m$ for `minus').

@d normp(X) ((X)<num_groups ? (X) : (X)-num_groups)	
@d normm(X) ((X)<0 ? (X)+num_groups : (X))
@<Rename so that |psa| through |psc| is shorter than |psb| through |psd|@>=
if ( psb==psd ) {
	SWAP(a,b,ti), @+ SWAP(c,d,ti),@+
	SWAP(ca,cb,tcn), @+ SWAP(cc,cd,tcn),@+
	SWAP(psa,psb,ti), @+ SWAP(psc,psd,ti);
} else if ( psa!=psc ) {	/* Nontrivial sequence of parents. Determine the shorter of the two. */
	if ( normp(psa+1)==psb ) { /* Forward order */
		const int dmb = psd-psb, amc=psa-psc;
		if ( normm(dmb) < normm(amc) )
			SWAP(a,b,ti), @+ SWAP(c,d,ti),@+
			SWAP(ca,cb,tcn), @+ SWAP(cc,cd,tcn),@+
			SWAP(psa,psb,ti), @+ SWAP(psc,psd,ti);
	} else { /* Reverse order */
		const int bmd = psb-psd, cma=psc-psa;
		if ( normm(bmd) < normm(cma) )
			SWAP(a,b,ti), @+ SWAP(c,d,ti),@+
			SWAP(ca,cb,tcn), @+ SWAP(cc,cd,tcn),@+
			SWAP(psa,psb,ti), @+ SWAP(psc,psd,ti);
	}
}

@ It is convenient to know which parent comes first.  We'll write |u| and
|v| for the lefthand and righthand parents of |ca| and |cb|, respectively.

There are two kinds of tasks to perform.  The first involves
changing pointers at the boundary.  The second involves making changes
at each of the parent nodes in the reversed sequence.



@<Flip the sequence of segments from $a$ to $c$@>=
{
parent_node_t *u, *v;
if ( normp(psa+1)==psb ) u=cc->parent, v=ca->parent;
else u=ca->parent, v=cc->parent;
@<Fix inbound and outbound sibling pointers@>@;
@<Fix per-parent data in the reversal from |u| to |v|@>@;
}


@ It is convenient to do the end-pointer manipulation first, 
while we have a good conceptual 
handle on where pointers point.  

We must fix outbound and inbound city sibling pointers at the boundaries,
and outbound and inbound parent sibling pointers at the boundaries.

This code looks hairy, but only because to fix
the city siblings, 
we have to handle all possible cases of reversal bits.  Also,
we need some double indirection in order to swap properly.

@<Fix inbound and outbound sibling pointers@>=
{
parent_node_t *tpn;
int ur, vr;
city_node_t **u_outbound, **v_outbound, **u_inbound, **v_inbound, *u_first, *v_last;
ur=u->reverse;
vr=v->reverse;
u_first = u->city_link[ur^CITY_LINK_HEAD];
v_last  = v->city_link[vr^CITY_LINK_TAIL];
u_outbound = u_first->link + (ur^LINK_PREV);
v_outbound = v_last ->link + (vr^LINK_NEXT);
u_inbound = (*u_outbound)->link + 
	((*u_outbound)->link[LINK_NEXT] == u_first? LINK_NEXT:LINK_PREV);
v_inbound = (*v_outbound)->link + 
	((*v_outbound)->link[LINK_NEXT] == v_last ? LINK_NEXT:LINK_PREV);
	
SWAP(*u_inbound,*v_inbound,tcn);	/* Fix inbound city sibling pointers */
SWAP(*u_outbound,*v_outbound,tcn);	/* Fix outbound city sibling pointers */
u->prev->next = v;	/* Fix inbound parent sibling pointers */
v->next->prev = u;
SWAP(u->prev,v->next,tpn); 	/* Fix outbound parent sibling pointers */
}

@
This section updates the per-node data on the reversed sequence of parents.

The first job is to fix the parent sibling pointers.  This code is similar
to the code to reverse a sequence of city links a single segment, namely
swap the sibling link pointers: make a former successor into a predecessor
and vice versa.  The outbound parent sibling pointers have already been taken
care of.

The second and third jobs are to update the parent sequence numbers and to
flip the reversal bits.  

Updating sequence numbers is interesting only
because we must do all arithmetic modulo |num_groups|.  In the future,
we might take the extra care
so that we would never overflow the number representation, but this
would only be possible (on a 32-bit or better machine) 
if we had about two {\it billion\/} groups or more.  Instead, I've
opted for the go for simpler and hopefully faster code.

On the other hand, if you end up fixing this problem, beware that you must
be very careful.  For instance, it is not good enough to leave the
code as it is, changing |int|s to |unsigned int|s, because the definition
of |upvn| in effect becomes 
$$upvn = (\hbox{|u->seq + v->seq|}\ \mod\ m)\ \mod\ \hbox{|num_groups|}$$
which is {\it not\/}
in general equal to 
$$(\hbox{|u->seq + v->seq|}\ \mod\ \hbox{|num_groups|})\ \mod\ m.$$
For example, $(4\ \mod\ 3)\ \mod\ 2 = 1 \not=0=(4 \ \mod\ 2)\ \mod 3$.
Here I've taken $m$ to be 1 greater than the maximum value of an unsigned
integer, \eg\ $m=2^{32}$ on a 32-bit machine.


@<Fix per-parent data in the reversal from |u| to |v|@>=
{
	const int upv = u->seq+v->seq, upvn = normp(upv);	
	parent_node_t *i, *done=v->next, *tpn;
	errorif(upv<u->seq || upv<v->seq, 
		"We've overflowed the integer representation");
	for ( i=u; i != done; i=i->prev ) {	/* Yes, |prev|: it's the old |next| pointer. */
		const int new_seq = upvn - i->seq;
		i->seq = normm(new_seq);
		i->reverse ^= 1;
		SWAP(i->next,i->prev,tpn);
	}
}

@*Debugging.
I'm not perfect.  This module didn't work the first time it compiled.
The following routines were created to help me debug the above routines.

Externally, they duplicate the interface using different names.  Internally,
they perform the queries and updates on both the array-based implementation
and the two-level-tree-based implementation, and check
the answers by comparing them.

Here's the interface.

@<Exported subroutines@>=
#if defined(TWOLEVEL_DEBUG)
void twolevel_debug_setup(const int num_vertices, const int start_seg_size);
void twolevel_debug_cleanup(void);
void twolevel_debug_set(int const *tour);
int twolevel_debug_next(int a);
int twolevel_debug_prev(int a);
int twolevel_debug_between(int a, int b, int c);
void twolevel_debug_flip(int a, int b, int c, int d);
#endif


@ The main wrinkle in this debuggging code is that the 
|flip| operation of the ADT does not specify the orientation
of the resulting tour.    So we must remember and adjust for the
possibly different orientations of tours under both implementations.  
Variable |reverse| is non-zero when the orientations differ.  

We will
take the two-level tree as the base implementation and adjust calls
to the array implementation.  That is, the answers to the queries
will always be the answers given by the two-level tree; the answers
from the array queries will be adjusted before comparing.  I've made
this choice because I want to process exactly the same sequence of operations
as when the bare two-level tree implementation is used.  I want to
minimize the entropy during debugging.
@^entropy@>


@<Module variables@>=
#if defined(TWOLEVEL_DEBUG)
static int reverse;
#endif

@ The setup, cleanup and tour-setting routines call the appropriate
routines in both modules, then set the reversal variables as appropriate.

@<Subroutines@>=
#if defined(TWOLEVEL_DEBUG)
void 
twolevel_debug_setup(const int num_vertices, const int start_seg_size) {
	array_setup(num_vertices);
	twolevel_setup(num_vertices,start_seg_size);
	using_two_representations=1;
}

void 
twolevel_debug_cleanup(void) {
	twolevel_cleanup();
	array_cleanup();
	using_two_representations=0;
}

void 
twolevel_debug_set(int const *tour) {
	if ( verbose >= 100) { printf("set\n"); }
	array_set(tour);
	twolevel_set(tour);
	reverse = array_next(0) != twolevel_next(0);
	if ( verbose >=200) 
		printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
				twolevel_next(0));
	check_tours_match();
}
#endif

@ We need the interface to the \module{ARRAY} module.
@<Module headers@>=
#if defined(TWOLEVEL_DEBUG)
#include "array.h"
#endif

@ 
@<Module variables@>=
#if defined(TWOLEVEL_DEBUG)
static int using_two_representations;
#endif

@ Here's a linear-time check on the tours.  
We check most of the internal 
consistency of the data structures, but not 
any of the |between| queries.  Checking all the possible |between|
queries would take cubic time!

I also check sequence numbers; they weren't being properly maintained.

@<Subroutines@>=
#if defined(TWOLEVEL_DEBUG)
static int
check_self_consistency(void)
{	int i, c,cnt, an_error=0, cnpt, gs,s,tail_s,lgs,ls, ng=0, ph,pt;
	const int first_city=
		parent_node[0].city_link[CITY_LINK_HEAD^parent_node[0].reverse]
		-city_node;
	parent_node_t *p;
	if (verbose >= 150)
		printf("Checking twolevel tour consistency, reverse==%d\n",reverse);
	tail_s = ls = city_node[twolevel_prev(first_city)].seq;
	lgs = parent_node[0].seq-1;
	for ( i=0, c=first_city; i<n && !an_error ; i++, c=cnt ) {
		if ( c == first_city && i > 0) {an_error=1;printf("Not a tour\n");}
		cnt = twolevel_next(c);
		cnpt = twolevel_prev(cnt);
		if ( cnpt != c ) {
			an_error=1;
			printf("twolevel next/prev inconsistent pos %d city %d next: %d, nextprev: %d\n",
				i,c,cnt,cnpt);
		}
		p = city_node[c].parent;
		if ( lgs != (gs=p->seq) ) { /* New segment. */
			ng++;	/* Number of groups encountered */
			if ( gs != ((lgs+1)%num_groups) ) {
				an_error=1;
				printf("Parent sequence numbers %d to %d not consecutive\n",
					lgs,gs);
			}
			lgs=gs;
			if ( tail_s != ls ) {
				an_error=1;
				printf("Seq of last city in segment %d doesn't seq of \"tail\"%d\n",
					ls,tail_s);
			}
			tail_s = p->city_link[CITY_LINK_TAIL ^ p->reverse]->seq;
			ls = city_node[c].seq;
			if ( c != (ph=p->city_link[CITY_LINK_HEAD ^ p->reverse]-city_node) ) {
				an_error=1;
				printf("First city in segment %d isn't \"head\"%d\n",
					c,ph);
			}
			{const cp=twolevel_prev(c);
			const parent_node_t *pp = city_node[cp].parent;
			if ( cp != (pt=pp->city_link[CITY_LINK_TAIL^pp->reverse]-city_node) ) {
				an_error=1;
				printf("Last city %d in previous segment isn't \"tail\" %d; step %d\n",
					cp,pt,i);
			}
			}
		} else {
			const int s_should_be = ls + (p->reverse?-1:1);
			s = city_node[c].seq;
			if ( s != s_should_be ) {
				an_error=1;
				printf("Sequence number %d of %d should be %d\n",
					s,c,s_should_be);
			}
			ls = s;
		}
	}
	if ( ng != num_groups ) {
		an_error=1;
		printf("Only counted %d groups; should be %d groups\n",
			ng,num_groups);
	}
	if ( c!=first_city ) {
		an_error=1;
		printf("Not a tour: didn't loop back from %d to itself\n",
			first_city);
	}
	if ( an_error ) print_two_tours();
	errorif(an_error,"Incorrect state for two-level trees.");
	return 1;
}

static int
check_tours_match(void)
{	int i, c,cna, cnt, an_error=0;
	const int first_city=
		parent_node[0].city_link[CITY_LINK_HEAD^parent_node[0].reverse]
		-city_node;
	check_self_consistency();
	if ( verbose >= 150 ) printf("Checking tours match\n");
	for ( i=0, c=first_city; i<n && !an_error ; i++, c=cnt ) {
		if ( c == first_city && i > 0) {an_error=1;printf("Not a tour\n");}
		cna = reverse ? array_prev(c) : array_next(c);
		cnt = twolevel_next(c);
		if(cna!=cnt) {
			an_error=1;
			printf("next's don't match: position %d city %d array: %d, twolevel: %d\n",
				i,c,cna,cnt);
		} 
	}
	if ( c!=first_city ) {
		an_error=1;
		printf("Not a tour: didn't loop back from %d to itself\n",
			first_city);
	}
	if ( an_error ) print_two_tours();
	errorif(an_error,"Tours don't match.");
	return 1;
}
#endif

@
@<System headers@>=
#include <stdio.h>
#if defined(OS_HAS_BROKEN_HEADERS)
#include "fixincludes.h"
#endif


@
@<Subroutines@>=
#if defined(TWOLEVEL_DEBUG)
static int 
print_two_tours(void) {
	int i, ca, ct, amore=1, tmore=1, 
	first_city=parent_node[0].city_link[CITY_LINK_HEAD^parent_node[0].reverse]
				-city_node;
	char a[100],t[100];
	for ( i=0, ca=ct=first_city; i<n ; i++ ) {
		if ( i==0 ) printf("Tour: Array Two-level\n");
		sprintf(a,"%d",ca);
		sprintf(t,"%d",ct);
		printf("\t%4d %7s %7s", i, amore ? a : " ", tmore?t:" ");
		if ( tmore ) {
			printf("\tseq=%3d p=%p g=%2d %s h=%4d t=%4d", 
				city_node[ct].seq,
				city_node[ct].parent,
				city_node[ct].parent->seq,
				city_node[ct].parent->reverse? "r": " ",
				city_node[ct].parent->head-city_node,
				city_node[ct].parent->tail-city_node);
		}
		printf("\n");
		ca = reverse ? array_prev(ca) : array_next(ca);
		ct = twolevel_next(ct);
		amore &= ca != first_city;
		tmore &= ct != first_city;
	}
	return 1;	/* Non-zero, for use in |errorif|. */
}
#endif

@ The |next| and |prev| queries have already been foreshadowed by the
check of the entire tour.  Specifically, we use |reverse| to select
whether to call the other of |next|, |prev| on the array implementation.

@<Subroutines@>=
#if defined(TWOLEVEL_DEBUG)
int 
twolevel_debug_next(int a) {
	const int tn = twolevel_next(a);
	const int an = reverse ? array_prev(a) : array_next(a);
	const int tnp = twolevel_prev(tn);
	if ( verbose >= 125 ) printf("next(%d)\n",a);
	errorif(tn!=an && check_tours_match(),
		"next: twolevel_next(%d)=%d, array_%s(%d)=%d",
		a,tn,reverse?"prev":"next",an);
	errorif( tnp != a && check_tours_match(), 
		"next(%d)=%d, prev(%d)=%d",a,tn,tn,tnp);
	return tn;
}

int
twolevel_debug_prev(int a) {
	const int tp = twolevel_prev(a);
	const int ap = reverse ? array_next(a) : array_prev(a);
	const int tpn = twolevel_next(tp);
	if ( verbose >= 125 ) printf("prev(%d)\n",a);
	errorif(tp!=ap && check_tours_match(),
		"next: twolevel_next(%d)=%d, array_%s(%d)=%d",
		a,tp,reverse?"next":"prev",ap);
	errorif( tpn != a && check_tours_match(), 
		"prev(%d)=%d, next(%d)=%d",a,tp,tp,tpn);
	return tp;
}
#endif

@ The |between| query is interesting because reversing the orientation
is reversing the arguments.  Doodle for a while to see why.
There's
modular arithmetic in there somewhere.
This technique is also used in the module \module{JBMR} to define 
|tour_inorder|.

@<Subroutines@>=
#if defined(TWOLEVEL_DEBUG)
int 
twolevel_debug_between(int a, int b, int c) {
	const int ab = reverse ? array_between(c,b,a) : array_between(a,b,c);
	const int tb = twolevel_between(a,b,c);
	if ( verbose >= 125 ) printf("between(%d,%d,%d)\n",a,b,c);
	errorif(ab!=tb && check_tours_match() && print_two_tours(),
		"between(%d,%d,%d) don't match: twolevel=%d array=%d",
		a,b,c,tb,ab);
	return tb;
}
#endif

@ 
Orientation doesn't actually matter in |flip|, except that
the ADT definition requires that |a==next(b)| and |d==next(c)|.  
We propagate that condition.

We must also reset |reverse|.

@<Subroutines@>=
#if defined(TWOLEVEL_DEBUG)
void 
twolevel_debug_flip(int a, int b, int c, int d) {
	if (verbose >= 110) printf("flip(%d,%d,%d,%d) %d\n",a,b,c,d,++count_flips);
	twolevel_flip(a,b,c,d);
	if ( reverse ) array_flip(b,a,d,c);
	else array_flip(a,b,c,d);
	reverse = array_next(0) != twolevel_next(0);
	if ( verbose >= 200 ) 
		printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
				twolevel_next(0));
	check_tours_match();
	{ int an_error=0;
	const int an = twolevel_next(a), ap = twolevel_prev(a);
	const int bn = twolevel_next(b), bp = twolevel_prev(b);
	const int cn = twolevel_next(c), cp = twolevel_prev(c);
	const int dn = twolevel_next(d), dp = twolevel_prev(d);
	if ( an==d ) {
		if ( dp != a ) an_error=1,printf("dp!=a\n");
		if ( bn != c ) an_error=1,printf("bn!=c\n");
		if ( cp != b ) an_error=1,printf("cp!=b\n");
	} else if ( ap==d ) {
		if ( dn != a ) an_error=1,printf("dn!=a\n");
		if ( bp != c ) an_error=1,printf("bp!=c\n");
		if ( cn != b ) an_error=1,printf("cn!=b\n");
	}
	if ( an_error ) {
		print_two_tours();
		errorif(1,"Bug");
	}
	}
}
#endif


@
@<Module prototypes@>=
#if defined(TWOLEVEL_DEBUG)
static int check_tours_match(void);
static int check_self_consistency(void);
static int print_two_tours(void);
#endif

@
@<Verbose: handle case 1@>=
#if defined(TWOLEVEL_DEBUG)
if ( print_at_flips != -1 && print_at_flips <= count_flips ) {
	if ( verbose >=200 ) printf(" Handle case 1\n");
	if ( using_two_representations ) {
		check_tours_match();
		print_two_tours();
	}
}
#endif

@
@<Verbose: split the $a-b$ segment@>=
#if defined(TWOLEVEL_DEBUG)
if ( print_at_flips != -1 && print_at_flips <= count_flips ) {
	if ( verbose >= 200 ) 
		printf(" Split the a-b segment, a=%d b=%d c=%d d=%d\n",a,b,c,d);
	if ( using_two_representations ) {
		check_tours_match();
		print_two_tours();
	}
}
#endif

@
@<Verbose: split the $c-d$ segment@>=
#if defined(TWOLEVEL_DEBUG)
if ( print_at_flips != -1 && print_at_flips <= count_flips ) {
	if ( verbose >= 200 )
	printf(" Split the c-d segment, a=%d b=%d c=%d d=%d\n",a,b,c,d);
	if ( using_two_representations ) {
		check_tours_match();
		print_two_tours();
	}
}
#endif

@
@<Verbose: flip a sequence of segments@>=
#if defined(TWOLEVEL_DEBUG)
if ( print_at_flips != -1 && print_at_flips <= count_flips ) {
	if ( verbose >= 125 ) printf(" flip a sequence of segments\n");
	if ( using_two_representations ) {
		check_tours_match();
		print_two_tours();
	}
}
#endif


@
@<Verbose: split off the end to the right of |cc| begin@>=
#if defined(TWOLEVEL_DEBUG)
if ( verbose >= 150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d begin\n",cc-city_node);
if ( using_two_representations ) check_tours_match();
#endif

@
@<Verbose: split off the end to the right of |cc| end@>=
#if defined(TWOLEVEL_DEBUG)
if ( verbose >= 150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d end\n",cc-city_node);
if ( using_two_representations ) check_tours_match();
#endif

@
@<Verbose: split off the end to the left of |ca| begin@>=
#if defined(TWOLEVEL_DEBUG)
if ( verbose >= 150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d begin\n",ca-city_node);
if ( using_two_representations ) check_tours_match();
#endif

@
@<Verbose: split off the end to the left of |ca| end@>=
#if defined(TWOLEVEL_DEBUG)
if ( verbose >= 150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d end\n",ca-city_node);
if ( using_two_representations ) check_tours_match();
#endif

@
@<Verbose: implicit rebalance done@>=
#if defined(TWOLEVEL_DEBUG)
if ( verbose >= 150) printf("\t\t\tImplicit rebalance done\n");

{ 
const int old_reverse = reverse;
if ( using_two_representations ) {
	reverse = array_next(0) != twolevel_next(0);
	if ( verbose >=200)
		printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
				twolevel_next(0));
}
	check_self_consistency();
if ( using_two_representations ) {
	reverse = old_reverse;
}
}
#endif

@
@<Module variables@>=
#if defined(TWOLEVEL_DEBUG)
static int count_flips = -1, print_at_flips=-1;
extern int verbose;
#endif


@*Denoument.  Give performance numbers.

@*Index.
