


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

\def\Txprime{T'}
\def\LCA{\hbox{\it LCA}}

{\obeylines
$Log: decluster.w,v $
Revision 1.59  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.58  1998/06/19 16:23:39  neto
Fixed call to pq create (to pq create size)

Revision 1.57  1998/06/19 15:01:50  neto
Used pq instead of dict for priority queues.

Revision 1.56  1998/05/23 16:37:26  neto
Factor out the plain MST algorithm (MST)
so it can be used with custom cost functions, e.g. by Held-Karp
lower bounding process in module ascend.

Revision 1.55  1997/12/17 20:01:11  neto
Removed const qualifier on tree returned by decluster topology tree.

Revision 1.54  1997/12/17 17:07:13  neto
Changed compile-time DECLUSTER CONSERVE MEMORY to runtime variable
decluster discard topology tree.
Fixed a date from 1998
(duh!) to 1988.

Revision 1.53  1997/12/13 21:30:07  neto
Fixed a copyo.

Revision 1.52  1997/12/13 21:28:15  neto
decluster mst now takes the tsp instance argument instead of relying on
a global variable.

Revision 1.51  1997/12/06 20:06:05  neto
Be a little defensive when freeing the tree.

Revision 1.50  1997/10/18 14:49:49  neto
Now use E2 supports() to know when we can use a kd-tree.

Revision 1.49  1997/10/17  21:47:55  neto
Changed coord2d structure.

Revision 1.48  1997/09/27 18:05:55  neto
Fixed RCS log behaviour.

Revision 1.47  1997/09/05  20:11:31  neto
Change augmenting chain to augmenting cycle.
improve the comments in the introduction a little bit.

Revision 1.46  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.45  1997/06/26  19:26:14  neto
Better documentation about declustering motivation.

Revision 1.44  1997/06/17  13:33:19  neto
Make DECLUSTER DEBUG a zero/non-zero test instead of a defined/undefined
test.

Revision 1.43  1997/06/16  20:08:24  neto
Fixed a TeX bug.

Revision 1.42  1997/06/13  17:59:32  neto
Added support for DECLUSTER CONSERVE MEMORY.  If defined, this
frees T prime after preprocessing.

Revision 1.41  1997/06/13  15:44:49  neto
Comment on the bit trick I just made more safe.

Revision 1.40  1997/06/13  15:16:27  neto
$(t+1)>>1$ is unsafe when $t=2^{31}-1$ because of possible sign extension
on the right shift.
Replace it with $t\XOR(t>>1)$. (Here t is a low bits mask.)  Also, this
might be faster because it replaces an $AC^0$ operation (t+1) with an $NC^0$
operation (exclusive-or).

Revision 1.39  1997/06/12  19:55:19  neto
Made declustertest a little quieter, and nicer for usual verbose==100
output.

Revision 1.38  1997/06/12  19:45:04  neto
Fixed bug in lca: last step was comparing inlabel numbers of xpp, ypp
instead of level numbers.  A transcripting error, pretty much.  :)
The LCA passes the tests on both the simple matrix and Euclidean
instances.
I'll encapsulate the debugging output now.

Revision 1.37  1997/06/12  18:50:21  neto
Testing on one example shows that
inlabel, ascendant, level, parent of head, head, parent entries are
computed correctly.

Revision 1.36  1997/06/11  20:04:49  neto
Fixed a depth-first search bookkeeping bug.

Revision 1.35  1997/06/11  19:37:37  neto
Fixed visibility and ordering of prototypes for print tree.

Revision 1.34  1997/06/11  19:31:44  neto
Refined when and how print tree is called.

Revision 1.33  1997/06/11  19:19:06  neto
Must preprocess the MST!
In preprocessing: component must be valid for n+n-1 entries.
: must make component[w]=NO PARENT.
Added function decluster print tree.

Revision 1.32  1997/06/10  22:06:56  neto
MST stuff now works, including test.
Added code to test LCA.
LCA does not work.  :(

Revision 1.31  1997/06/10  20:51:47  neto
Fixed 2 bugs in plain prim.
Fixed 2 bugs in testing code.
plain prim: mark cities as members of the component.
plain prim: in updating arrays, I set infinity wrong.
testing code: setup needs number of cities, not number of edges in MST.

Revision 1.30  1997/06/10  20:30:24  neto
Finished coding self-test.  Plain prim fails.  It adds self-edges.

Revision 1.29  1997/06/04  22:27:08  neto
Fixed a macro placement.

Revision 1.28  1997/06/04  22:26:04  neto
More code for selftest.

Revision 1.27  1997/06/04  21:37:33  neto
Begin a small test program.

Revision 1.26  1997/06/04  21:06:55  neto
Now it compiles.

Revision 1.25  1997/06/03  22:40:38  neto
Removed a bad trailing comma in pow 2.

Revision 1.24  1997/06/03  22:35:46  neto
Added a comment about whether we should actually store the
cost in the topology tree.

Revision 1.23  1997/06/03  22:32:39  neto
Moved the bit twiddling forward so that it doesn't split the
digestion code.
Completed the cluster distance code.

Revision 1.22  1997/06/03  22:13:02  neto
We don't need index rightmost 1

Revision 1.21  1997/06/03  22:01:17  neto
We don't need halfmasks.

Revision 1.20  1997/06/03  21:58:40  neto
Completed coding xpp and ypp code.
Created a macro for copying high 1 bit down.
Reduced sectional clutter at the end of the web file.

Revision 1.19  1997/06/03  19:00:17  neto
Finish coding parent of head of inlabel chain.

Revision 1.18  1997/06/03  18:54:04  neto
Fixed accesses to edges of T prime.
Use `parent of head of inlabel chain' instead of `head of inlabel chain'.

Revision 1.17  1997/06/03  18:50:14  neto
Added code for finding inlabel of z, the LCA of x and y.

Revision 1.16  1997/06/02  15:50:47  neto
Fixed two bugs.
First, head levels weren't being checked in the initialization phase.
Second, I was missing the lowest high bit in LCA code.

Revision 1.15  1997/05/28  17:31:24  neto
Make make happy so I can make a distribution.

Revision 1.14  1997/05/28  17:28:25  neto
Started on doing LCA queries.

Revision 1.13  1997/05/27  23:57:02  neto
Finished code to create T prime.
Created code to compute level, inlabel, and ascendant numbers.

Revision 1.12  1997/05/23  22:46:52  neto
Missed an at sign...

Revision 1.11  1997/05/23  22:46:14  neto
Fill out null sections so I can pack this up and back it up to school.

Revision 1.10  1997/05/23  22:37:46  neto
Fixed two typos.

Revision 1.9  1997/05/23  22:34:55  neto
Middle of coding up the transformation from MST T to topology tree T'.
I need to think more before I code.  I may have to go to a full-blown
union-find algorithm, but then again, maybe not.

Revision 1.8  1997/05/23  20:35:20  neto
Bridges drawn from the priority queue might no longer be bridges.  Fixed.
Still no compile.

Revision 1.7  1997/05/23  20:12:00  neto
Added accounting for computing the MST length.

Revision 1.6  1997/05/23  19:13:54  neto
New major section: Interface and code preamble.
Include dict.h and kdtree.h

Revision 1.5  1997/05/23  19:08:07  neto
Implemented Prim's algorithm in the geometric case.
Still not compiled.

Revision 1.4  1997/05/23  18:05:06  neto
Edit for readability.
Skip over cities that are in the component (in Prim's algorithm).

Revision 1.3  1997/05/22  19:22:05  neto
Fixed memory accounting.
Fixed fencepost error.

Revision 1.2  1997/05/22  19:13:52  neto
Completed description of declustering idea.
Created the interface
Now writing the MST routine.
Finished coding the general Prim algorithm.
(Perhaps reference Knuth's MILES\_SPAN).

Revision 1.1  1997/05/21  16:57:50  neto
Initial revision

}

%%\def\t#1ip#2{t_{#1i+#2}}
%%at s t2ip1 TeX
%%at s t2ip2 TeX
%%% The following would be cruel...
%%%\def\twoxi{2i}	 
%%%at at s two_i TeX

@*Declustering.
The Lin-Kernighan algorithm can perform quite badly on clustered
instances.  This becomes evident when one compares its performance on
uniform Euclidean instances with its performance on clustered instances
such as instance \instance{dsj1000}.  I described the problem and suggested
a remedy for it in my research proposal, ``Topology and the traveling
salesman problem'', March 17, 1997.

This module implements the function |decluster_d| that computes the cluster
distance between any pair of cities.  
@^cluster distance@>
It is the key ingredient in the ``efficient declustering'' fix
that I propose for Lin-Kernighan.


@ To understand the problem and its solution, we need to review the
Lin-Kernighan heuristic, whose salient points
are as follows.  The heuristic searches
for a cycle in the underlying graph consisting of $2k$ edges 
$e_1, \ldots, e_{2k}$ with
the following
properties:

\itemskip

\li{i}Edge $e_j$ is the pair of cities $(t_j,t_{j+1})$,
except that edge $e_{2k}$ is the pair of cities $(t_{2k},t_1)$.

\itemskip

\li{ii}Odd-numbered edges are in the current tour;
even-numbered edges are not. 
Removing the odd edges from the current tour 
and adding the even edges results in another tour.
The $2k$ edges therefore form an
augmenting cycle in the graph. (CHECK NOMENCLATURE)%Thanks, Derek.

\itemskip

\li{iii}The total weight of the odd edges exceeds the 
total weight of the even edges. That is,
$$ \sum_{j {\rm\ odd}}\cost(e_j)
	-\sum_{j {\rm\ even}}\cost(e_j) > 0.$$

\itemskip



Although many ideas go into making the search both extensive and efficient, 
one of the principal ideas is the \term{cumulative gain criterion}.
% a strengthening(?) of rule iii.
@^cumulative gain criterion@>
The reasoning goes as follows.
Taking any cycle satisfying the above three criteria, we may rotate it
by twos (taking $e'_{j} = e_{j+2}$, and so on) so that we eventually
find a cycle in which all the partial sums of weights are positive:
$$\cost(e_1)>0$$ 
$$\cost(e_1)-\cost(e_2)>0$$ 
$$\cost(e_1)-\cost(e_2)+\cost(e_3)>0$$ 
$$\cost(e_1)-\cost(e_2)+\cost(e_3)-\cost(e_4)>0$$ 
and so on.  In general, for any $1\le s\le 2k$ we have
$$ \sum_{j {\rm\ odd},\, j\le s}\cost(e_j)
	-\sum_{j {\rm\ even},\, {j\le s}}\cost(e_j) > 0.$$
%$$ \sum_{j \le s}(-1)^{j+1}\cost(e_j) >0.$$ %This is yucky.

@  The proof is easy and is obvious once one draws a picture.
Let $b$ be the least partial sum in the original list, and say it occurs
after subtracting cost of edge $e_{2j}$.  Let $a$ be the gain made over
the last $2k-2j$ edges, \ie, the total sum minus $b$.  
%Since the total
%sum is positive, we know $a+b>0$.
Rotate the cycle so that 
$e_{2j}$ appears last in the list of edges, \ie, $e'_{2k}=e_{2j}$ and so on.  
All the partial sums will now
be positive, because the least partial sum appears at the end of the
list (to where $e_{2j}$ has migrated) and is equal to the original total
sum, $a+b$, which we know is positive.


@
Improving cycles $t$ are built incrementally from $t_1$, by first 
removing edge
$e_1=(t_1,t_2)$ to form a Hamiltonian path.
From then on, city $t_1$ anchors the head of the path while we
repeatedly flip the
tail of the path.
Each flip of the tail adds two cities to the sequence of cities $t$ 
(an odd city and an even city), 
and hence adds two edges to the sequence of edges $e$ (an even edge and
an odd edge).  The cumulative
gain criterion is applied only after an odd edge is added.  

Actually,
instead of checking that the cumulative sum is positive, one checks
that the cumulative sum is greater than the gain given by
the best tour improvement seen
so far in this sequence, denoted by |best_gain|.  In symbols, the
actual cumulative gain criterion is:
$$ \sum_{j {\rm\ odd},\, j < 2i}\cost(e_j)
	-\sum_{j {\rm\ even},\, {j\le 2i}}\cost(e_j) > 
\hbox{|best_gain|}.$$


@
The cumulative gain criterion in the usual Lin-Kernighan 
algorithm deliberately ignores the cost
of immediately closing up the Hamiltonian path to form a tour.    
That is, $cost(t_{2i},t_1)$ is
not removed from the cumulative gain because there might be a way to
extend the sequence a bit farther and achieve a closing-up cost 
much lower than 
$cost(t_{2i},t_1)$.
@^cumulative gain criterion@>

But there's a problem with this. If the tail $t_{2i}$ somehow crosses into
a cluster of the graph distant from the cluster containing $t_1$, then
we end up with an overly-optimistic cumulative gain.  This makes the
search go on for much longer than it should. 
We may never gain enough potential to cross the great divide back into
the territory surrounding the anchor city $t_1$.
@^anchor city@>

My declustering idea is to discount the cumulative gain
by the \term{cluster distance} between
$t_{2i}$ and $t_1$.  
Given a path $P$ from $u$ to $v$, the \term{bottleneck cost} of $P$
is the cost of the most expensive edge in $P$.  Then the cluster distance
between $u$ and $v$ is the minimum bottleneck cost over all paths from
$u$ to $v$. We denote this value by $d(u,v)$.
@^cluster distance@>
@^bottleneck cost@>
% See my research proposal for a precise statement of the relationship
% with the possible costs of closing up the tour.  It is not quite
% an upper bound and not quite a lower bound.  But it ought to be
% close enough.

The cumulative gain criterion applied when considering adding
$t_{2i-1}$ and $t_{2i}$ becomes:
$$ \sum_{j {\rm\ odd},\, j < 2i}\cost(e_j)
	-\sum_{j {\rm\ even},\, {j\le 2i}}\cost(e_j) - d(t_{2i},t_1) > 
\hbox{|best_gain|}.$$

@ The rotation trick 
shows that using the original cumulative gain criterion
doesn't eliminate improvements that satisfy the three Lin-Kernighan
criteria given 
above.  That is, applying the cumulative gain criterion can't hurt.

However, the declustering technique ---discounting the cumulative gain
function by the cluster distance between $t_{2i}$ and $t_1$--- definitely
{\it can\/} hurt.
That is, it might eliminate valid improvement sequences.  (INSERT MORE
DETAILS. Also, see research proposal.)

@ If the underlying cost function is 
postitive-definite and symmetric, then
the cluster distance is positive-definite, symmetric, and
also satisfies the triangle inequality.
In short, 
under
such conditions
$d$ 
is a 
\term{metric}.      
(A function $f$ is \term{positive-definite}  if $f(x,y)\ge0$ with equality if
and only if $x=y$; function $f$ 
satisfies the \term{triangle inequality} if for any 
$x$, $y$, and $z$, we have  $f(x,y)  \le f(x,z)+f(z,y)$.)
@^metric@>
@^positive-definite@>
@^triangle inequality@>


We're quite lucky because $d$ may be computed very efficiently.
In fact with about $O(n \log n)$ preprocessing of the graph, online
queries of $d$ may be processed in constant time!  
This remarkable feat is the job of this module.  

@
Several ingredients are required to make the declustering code run fast.

First, the cluster distance between
vertices $u$ and $v$ in graph $G=(V,E)$ is also equal to the bottleneck
cost along the unique simple path from $u$ to $v$ in a minimum spanning tree
$T=(V,E_T)$ of
$G$. (The proof is left as an exercise.)  

Second, we construct a rooted binary tree 
$T'=(V_{T'},E_{T'})$ from $T$ by making the vertices of $T$ be the leaves
of $T'$, and the edges of $T$ be the internal nodes of $T'$: 
$V_{T'}=V\cup E_T$.
Run Kruskal's minimum 
spanning tree algorithm on $T$.  Each subtree of $T'$ corresponds
to a connected component of $T$ formed during the execution of Kruskal's
algorithm on $T$:  adding edge $(i,j)$ during reconstruction of $T$
corresponds to adding internal node $(i,j)$ to $T'$ with its two children
being the current components containing $i$ and $j$.
%Tree $T'$ captures the topology of the graph under $d$.
Because Kruskal's algorithm adds edges in order of non-decreasing cost,
$T'$ is built bottom-up, with more expensive edges toward the root:
the cost of the edge labeling an internal node $(i,j)$ of $T'$
is as great as the cost of any edge labeling a node in the subtree rooted
at $(i,j)$. 
Finally, the bottleneck cost of the unique path from $u$ to $v$ in $T$ is just
the weight of the edge labeling the least common ancestor of $u$ and
$v$ in $T'$.
@^MST@>
@^LCA@>
@^minimum spanning tree@>
@^Kruskal's algorithm@>
@^cluster distance@>
@^least common ancestor@>

For any rooted tree $R$, 
with $O(n\log n)$ time preprocessing and $O(n)$ extra space,
online least common ancestor (LCA)
queries in $R$ may be answered in constant time 
(INSERT REFERENCE: Schieber1993).  
This technique is applied to tree $T'$ from the previous paragraph.
The LCA algorithm I give here runs in constant time assuming a fixed word
length. 
If machine word size is unrestricted and given as parameter $w$, 
the algorithm given here runs in $O(\log w)$ time.
(The main barrier to asymptotically faster code is 
the problem of writing standard \CEE/ code to find the most significant
1 bit in a word. See \file{http://www.cs.utoronto.ca/\~{}neto/code/\penalty-500first1bit.html}.)


@* Interface and code preamble.  
The outline of this module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Early module headers@>@;
@<Module headers@>@;

@<Global variables@>@;
@<Module definitions@>@;
@<Module types@>@;
@<Module variables@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *decluster_rcs_id = "$Id: decluster.w,v 1.59 1998/07/16 21:58:55 neto Exp neto $";


@ This module provides the following interface.

Procedures 
|decluster_setup| and |decluster_cleanup| are the usual intialization 
and shutdown routines.   They allocate the persistent space for the rest of the
routines.  Procedure |decluster_setup| returns the space into which
a minimum spanning tree can be written.
Procedure |decluster_cleanup_tree| frees that space, given its pointer.  
It is a separate
call because the tree is no longer needed after preprocessing, so
it can be freed early.  In fact, this module throws away its reference
to that storage, so the caller {\it must\/} free it with a
call to |decluster_cleanup_tree|.

Procedure |decluster_mst| builds a minimum spanning tree for the current
graph.  It is passed a pointer to a block of space into which it
should write the tree.  It returns the weight of the tree.

Sometimes we want to compute many minimum spanning trees with our own
modified cost function, and without taking advantage of $k$-d trees.
In that case, use |decluster_mst_custom|, which takes 
an $n$-node tree node array into which it should write the answer, two utility
arrays of length $n$, and the custom cost function.  It returns
the length of the resulting tree.

Procedure |decluster_preprocess| digests a given tree so that least
common ancestor queries can be answered quickly by |decluster_d|.  
It overwrites the tree it is given.  Digestion indeed!

Separating the minimum spanning tree building out into a separate call
allows the user to substitute their own minimum spanning tree.  This is
useful in those cases where special knowledge of the input allows them
to build the tree very quickly.

Function |decluster_d| computes cluster distance $d$ efficiently.  
It uses the data structures built by procedure |decluster_preprocess|.

@ Some parts of the interface supports uses outside just computing cluster
distances.  

Procedure |decluster_topology_tree| returns a pointer to the topology tree
that is preprocessed to answer decluster distance queries.  
It contains much digested information about the structure of the minimum
spanning tree of the instance.

Ordinarily, the topology tree is discarded immediately after preprocessing.
Set variable |decluster_discard_topology_tree| to zero to preserve it
for further use.  In particular, if  |decluster_discard_topology_tree|
is non-zero, 
|decluster_topology_tree| will return |NULL| after |decluster_preprocess|
is called.


Procedure |decluster_print_tree| outputs the structure of an arbitrary
valid |decluster_tree_t|.


@<Exported subroutines@>=
decluster_tree_t *decluster_setup(int n);
void decluster_cleanup_tree(decluster_tree_t *T);
void decluster_cleanup(void);
length_t decluster_mst(tsp_instance_t *tsp_instance,decluster_tree_t *T);
length_t decluster_mst_custom(decluster_tree_t *T,int *from,
			length_t *dist,length_t (*cost)(int,int));
void decluster_preprocess(decluster_tree_t *T);
length_t decluster_d(int u, int v);

decluster_tree_t *decluster_topology_tree(void);
void decluster_print_tree(FILE *out,decluster_tree_t const *t, const char *name);


@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

@ The exported interface is contained in the \file{decluster.h} header file,
which has the following form.

@(decluster.h@>=
extern const char *decluster_rcs_id;
@<Exported types@>@;
@<Exported variables@>@;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "decluster.h"


@ 
Up front, we know we'll need interfaces to
the error checking and memory allocation
modules, the |length_t| type (from 
\module{length}), and the |cost| function and internal
access to the internals of the graph (from \module{read}).

@<Early module headers@>=
#include "error.h"
#include "memory.h"
#include "length.h"
#include "read.h"


@*Setup and cleanup.
Procedure |decluster_setup| just 
allocates the resources required by this module,
and sets up some module-level convenience variables.  It returns space
into which a minimum spanning tree should be written.

@<Subroutines@>=
decluster_tree_t *
decluster_setup(int the_n) 
{
	decluster_tree_t *mst;
	n = the_n;
	@<Allocate space for a spanning tree |mst|@>@;
	@<Other setup code@>@;
	return mst;
}

@ We should declare |n|.
@<Module variables@>=
static int n;	/* The number of cities. */

@ Deallocation is simple (especially with named sections!).
@<Subroutines@>=
void 
decluster_cleanup(void)
{
	@<Other cleanup code@>@;
	n=0;
}

@*Minimum spanning trees.
We'll be manipulating spanning trees throughout this module.  We begin
by defining a spanning tree type.
A spanning tree on $n$ vertices has $n-1$ edges.  Each edge is a pair
of vertices.  
The tree is an array of edges, each with their associated cost.

@<Exported types@>=
typedef struct {
	int city[2];
	length_t cost;
} decluster_edge_t;

typedef struct {
	int n;
	decluster_edge_t *edge; /* An array of $n$ edges */
} decluster_tree_t;

@ Since a tree is just an array of edges, we can allocate it in
one swoop.
@<Allocate space for a spanning tree |mst|@>=
mst = new_of(decluster_tree_t);
mst->n = n-1;
mst->edge = new_arr_of(decluster_edge_t,n-1);


@ Freeing the tree is just as easy.  

@<Subroutines@>=
void 
decluster_cleanup_tree(decluster_tree_t *T)
{
	if (T) { /* Be a little defensive. */
		size_t r = (T->n)*sizeof(decluster_edge_t) + sizeof(decluster_tree_t);
		T->n=0;
		free_mem(T->edge);
		free_mem(T);
		mem_deduct(r);
	}
}

@ 
We can choose among different minimum spanning tree algorithms according
to our knowledge of the underlying structure of the graph.
In
particular, if the graph is embedded in Euclidean space then we can use
Bentley's $k$-d trees for semidynamic point sets, implemented in module
\module{kdtree}, to speed things up
considerably.  Otherwise we say the graph is unstructured and we use
a general minimum spanning tree algorithm.

Our graphs are complete, \ie, there is an edge between each pair of
vertices.  Prim's MST algorithm is efficient for unstructured 
complete graphs because it can be programmed to examine each edge only once.

Prim's algorithm begins with an empty tree $T_0=(V,\{\})$, and designates
a seed vertex $v_0$.  It builds up a single component from $V_0=\{v_0\}$ to
the entire vertex set $V$.
At step $i$ it forms the new version of the component $V_{i+1}$ from 
$V_i$ by adding the shortest edge between a vertex $v\in V_i$ in the current
version of the
component and a vertex $v_{i+1}\in V\setminus V_i$ not in the current
version of the 
component.

Oddly enough, Prim is also good for the Euclidean case because it
builds up a single component from nothing to the entire tree.  We can
filter out many of the edges from consideration by using
the $k$-d tree's ability to hide cities.  We hide cities in the current 
version of the component, \ie, at step $i$ all vertices in $V_i$ are
hidden.
That way nearest neighbour searches will avoid edges that
would
create cycles.


@<Subroutines@>=
length_t 
decluster_mst(tsp_instance_t *tsp_instance,decluster_tree_t *T)
{
	extern int verbose;
	length_t total_len=0;
	errorif(T->n!=n-1,"decluster_mst: passed storage for a tree with %d"@;
		" vertices instead of %d vertices", T->n, n-1);
	if ( E2_supports(tsp_instance) ) {
		@<Build an MST using $k$-d trees@>@;
	} else { /* Use a plain MST algorithm. */
		int *from=new_arr_of(int,n);
		length_t *dist=new_arr_of(length_t,n);
		total_len = 
			decluster_mst_custom(T,from,dist,cost);
		free_mem(from);mem_deduct(n*sizeof(int));
		free_mem(dist);mem_deduct(n*sizeof(length_t));
	}
	return total_len;
}

@ Let's implement a plain MST algorithm, one which uses only the
given |cost| function and the knowledge that all possible edges are
in the graph.
We use a generic version of Prim's algorithm, outlined in the previous
section.

Value |from| is a pointer to an array of |n| integers, 
and |dist| is a pointer to an array of |n| length values.

If vertex |i| is not in the component, then |from[i]| is the
vertex in the component that is closest to |i|, and
|dist[i]==cost(from[i],i)|.  Otherwise, |from[i]=-1|.

Variable |short_len| is the minimum distance between a vertex in
the component and a vertex outside the component.  Variable |short_to|
is the outside vertex closest to the component.

We use city 0 as the seed city.


@<Subroutines@>=
length_t
decluster_mst_custom(
	decluster_tree_t *T,int *from,length_t *dist,length_t (*cost)(int,int))
{
int i, next_edge, short_to, n; /* Override file-scope |n|. */
length_t short_len, total_len = 0;
from[0]=-1;
errorif(T==NULL || T->n<0,"Bug!");
n=T->n+1;
for (i=1,short_len=INFINITY,short_to=-1;i<n;i++) {
	from[i]=0; 
	dist[i]=cost(0,i);
	if ( short_len > dist[i] ) {
		short_len=dist[i];
		short_to=i;
	}
}
for ( next_edge=0; next_edge < n-1; next_edge++ ) {
	@<Add the edge to |short_to|@>@;
	@<Update distance arrays and |short_to|@>@;
}
return total_len;
}


@
@<Add the edge to |short_to|@>=
if (verbose>=1000) printf("decluster_mst_plain: adding edge (%d,%d) "length_t_spec"\n",
	from[short_to],short_to,length_t_pcast(short_len));
T->edge[next_edge].city[0] = short_to;
T->edge[next_edge].city[1] = from[short_to];
T->edge[next_edge].cost = short_len;
total_len += short_len;
from[short_to]=-1;

@ Now that |short_to| has been added to the component, update 
arrays |from| and |dist|.  That is, see if |short_to| is closer to
an outside vertex than any of the other inside vertices.

We'll also be updating |short_to|, so first we copy the value of 
|short_to| to |new_inside_city|.

Scanning through all the cities wastes effort   % half, in fact
because we touch cities
that are in the component.  We could save time by collecting these cities
in one spot.  But that would entail still other bookkeeping.  
Hopefully this simpler version is faster because of its simplicity.

This section completes the general version of  Prim's algorithm.

@<Update distance arrays and |short_to|@>=
{ 
const int new_inside_city=short_to;
short_len=INFINITY;
for (i=1;i<n;i++) {
	length_t d;
	if ( from[i] == -1 ) continue; /* City |i| is already in the component. */
	d=cost(new_inside_city,i);
	if ( d < dist[i] ) {
		dist[i] = d;
		from[i] = new_inside_city;
	}
	if ( dist[i]<short_len ) {
		short_len=dist[i];
		short_to=i;
	}
}
}

@  Now we're ready to implement Prim's algorithm for geometric inputs.
Specifically, we'll use Bentley's $k$-d trees for semidynamic point sets.
Throughout the execution of the algorithm, cities in the component will
be hidden, and cities outside the component will be visible.
This allows us to eliminate the vast majority of edges from consideration.

(It might be nice to measure this.   I suspect that this scheme will work
very well for uniform instances, because the shortest bridge drawn from
the priority queue will probably be consistently short.
The scheme might not work so well for clustered instances.)

We'll keep a priority queue |bridge_pq| of edges that have one endpoint
in the component (recorded in field |city[0]|) 
and the other endpoint outside of the component (recorded in field
|city[1]|).
We'll eventually have an entry for each of $n-1$ vertices, so we
preallocate an array |bridge| of $n$ of them.  (We don't know in advance which
vertex will be the last to enter the component.)

Initially the priority queue contains just the edge from vertex 0 to
its nearest neighbour.  I'm assuming that the $k$-d tree is initialized
to have no cities hidden.  We clean up after ourselves by unhiding all
of them at the end.

@<Build an MST using $k$-d trees@>=
{
decluster_edge_t *bridge=new_arr_of(decluster_edge_t,n);
pq_t *bridge_pq=pq_create_size(edge_cmp,n);
int next_edge; char *is_in_component=new_arr_of_zero(char,n);

errorif(bridge_pq==NULL,"Couldn't allocate a priority queue!");

E2_hide(0);
bridge[0].city[0]=0;
bridge[0].city[1]=E2_nn(0);
bridge[0].cost = cost(0,bridge[0].city[1]);
is_in_component[0]=1;
pq_insert(bridge_pq,&bridge[0]);

for (next_edge=0 ; next_edge < n-1 ; next_edge++ ) {
	int in,out;
	decluster_edge_t *short_bridge;
	while (1) { /* Get a valid bridge. */
		short_bridge = pq_delete_min(bridge_pq);
		in=short_bridge->city[0]; 
			/* The city already in the component, and therefore hidden. */
		out=short_bridge->city[1]; /* The city possibly outside the component. */
		if ( !is_in_component[out] ) break;
		bridge[in].city[1]=E2_nn(in);
		bridge[in].cost=cost(in,bridge[in].city[1]);
		pq_insert(bridge_pq,bridge+in);
	}
	T->edge[next_edge] = *short_bridge;
	total_len += short_bridge->cost;
	E2_hide(out);
	is_in_component[out]=1;

	bridge[in].city[1]=E2_nn(in);
	bridge[in].cost=cost(in,bridge[in].city[1]);
	pq_insert(bridge_pq,bridge+in);
	bridge[out].city[0]=out;
	bridge[out].city[1]=E2_nn(out);
	bridge[out].cost=cost(out,bridge[out].city[1]);
	pq_insert(bridge_pq,bridge+out);
}
pq_destroy(bridge_pq);
free_mem(is_in_component);mem_deduct(n*sizeof(char));
free_mem(bridge);mem_deduct(n*sizeof(decluster_edge_t));
E2_unhide_all();
}

@ We need to import the interfaces to priority queues and to $k$-d trees.
@<Module headers@>=
#include "pq.h"
#include "kdtree.h"

@ One last thing we need is the comparison function |edge_cmp| for edges
so the priority queue can give edges to us in the right order.
Function |edge_cmp| has the same interface as required by the \CEE/
library function |qsort|.  

We force determinacy by comparing pointer values
in case the lengths are the same.   
(I don't think this is necessary in the use in Prim's algorithm above,
but it can't hurt.)

@<Edge comparison function@>=
static int
edge_cmp(const void *a, const void *b) 
{
    length_t len_diff = ((const decluster_edge_t *)a)->cost 
						- ((const decluster_edge_t *)b)->cost;
    return len_diff < 0 ? -1 : 
		(len_diff>0 ? 
		 1 :
	     ((int)(((const decluster_edge_t *)a)-((const decluster_edge_t*)b))) );
}

@  I also use this function in the test routines, but it is local to
both modules.

@<Module subroutines@>=
@<Edge comparison function@>@;

@
@<Test module subroutines@>=
@<Edge comparison function@>@;



@*Topology trees.
Now, given a minimum spanning tree $T$ such as the one constructed in the
previous sections, we'd like to create the related topology tree $T'$ as
described in the opening sections.
% Relate this to dynamic MST or whatever that SODA'97 paper was about.
% They use similar the term ``topology tree'' as well, but in a different
% sense.
When $T$ has $n$ vertices, $T'$ has $2n-1$ vertices.  Each is an entry
in an array of |decluster_edge_t| nodes.  The |city| array in each node
is aliased to the name |child|, and stores child indices.  ($T'$ is binary.) 
A value of
$-1$ indicates no child.

The first $n$ entries of $T'$ correspond to the vertices of the original
graph.  They have zero cost and no children.   

% We may want to do an `at s T_prime TeX'

The \LCA\ queries don't actually need |T_prime|, so we can throw
it away if need be.  We defend against a memory leak in case 
we reallocate for a different size.
@^memory leak@>


@d child city
@d NO_CHILD (-1)


@<Allocate and pre-initialize |T_prime|@>=
if ( T_prime==NULL || T_prime->n!=n+n-1 ) {
	int i;
	@<Clean up |T_prime|@> /* Defend against a memory leak. */
	T_prime =  new_of(decluster_tree_t);
	T_prime->n = n+n-1;
	T_prime->edge = new_arr_of(decluster_edge_t,n+n-1);
	for(i=0;i<n;i++) {
		T_prime->edge[i].child[0]=NO_CHILD;
		T_prime->edge[i].child[1]=NO_CHILD;
		T_prime->edge[i].cost=0;
	}
}

@
@<Other setup code@>=
@<Allocate and pre-initialize |T_prime|@>@;

@
@<Clean up |T_prime|@>=
if ( T_prime ) {
	const int n = T_prime->n;
	free_mem(T_prime->edge);mem_deduct(n*sizeof(decluster_edge_t));
	free_mem(T_prime);mem_deduct(sizeof(decluster_tree_t));
	T_prime=NULL;
}

@
@<Other cleanup code@>=
@<Clean up |T_prime|@>@;

@ We must define |T_prime|.
@<Module variables@>=
static decluster_tree_t *T_prime=NULL;

@ The first $n$ entries of |T_prime| are filled out at memory allocation
time.  We then copy $T$ into the last $n-1$ positions of |T_prime|
in increasing order while making the appropriate links.

Tree |T_prime| is digested into an array of four integers: |level|,
|inlabel|, |ascendant|, and head.

In the normal case we throw away |T_prime| after preprocessing because
it isn't needed for \LCA\ queries.
In this case we may have to reallocate |T_prime| here.


@<Subroutines@>=
void
decluster_preprocess(decluster_tree_t *T) 
{
	errorif(T->n!=n-1,"decluster_preprocess: MST size %d should be %d",T->n, n-1);
	if ( T_prime==NULL ) @<Allocate and pre-initialize |T_prime|@>@;
	@<Fill the last $n-1$ entries of |T_prime| with data from $T$@>@;
	print_tree(T_prime,"T_prime");
	@<Copy |cost| fields from |T_prime|@>@;
	@<Compute |level| numbers@>@;
	@<Compute |inlabel| numbers@>@;
	@<Compute |ascendant| numbers@>@;
	@<Compute |parent_of_head| numbers@>@;
	@<Verbose: print the preprocessing data@>@;
	if ( decluster_discard_topology_tree ) {
		@<Clean up |T_prime|@>@;
	}
}

@ First off, in most cases we want to save space by throwing away
topology tree |T_prime| once we're through processing it.
But sometimes we want to keep it around.  We make it optional through the
globally visible variable |decluster_discard_topology_tree|.

@<Global variables@>=
int decluster_discard_topology_tree=1;

@
@<Exported variables@>=
extern int decluster_discard_topology_tree;



@ We add each edge of $T$ in ascending order.  
Essentially
we simulate Kruskal's algorithm, but with the knowledge that every
edge ends up in the output.   Tree |T_prime| in some sense records
the history of the Kruskal algorithm computation.

Array |component| stores
the evolving component structure of the topology tree.    
Entry |component[i]| points to the root of the component containing
vertex |i|.  Entries may go out of date by the addition of new edges, 
but they can always be updated by following links up the tree.
A value of |NO_PARENT| indicates that a vertex is a root.


@d NO_PARENT (-2)

@<Fill the last $n-1$ entries of |T_prime| with data from $T$@>=
{ int r, w,i, *component=new_arr_of(int,n+n); 
	/* |r| is a read cursor, |w| is a write cursor */
for (i=0;i<n;i++) component[i]=NO_PARENT;
sort(T->edge,(size_t)(n-1),sizeof(decluster_edge_t),edge_cmp);
print_tree(T,"T");
for (r=0,w=n;r<n-1;r++,w++) {
	T_prime->edge[w] = T->edge[r];
	@<Link |T_prime->edge[w]| with its two children and update |component|@>@;
}
free_mem(component);mem_deduct((n+n)*sizeof(int));
}

@ We need to import the sorting routine from module \module{lk}.  The
user has the option of changing it.
@<Module headers@>=
#include "lk.h"

@  Does an amortized argument prove that the following runs in linear time
over the entire sequence?
It is similar to the classic path compression solution to the 
merge/find problem that is a standard component in implementations of
Kruskal's algorithm.  That has worst-case time that is almost
linear, $O(n \alpha(n))$.  But I'm confused as to whether it does less or
more work.  I'll have to think about it more. 
(Some thoughts: Cf. combining tree in asyncrhonous PRAM (Nishimura);
linear time heapify.)

We save some buffer space and some time because we already know where
the nodes will all be pointing to.  They'll point to the vertex labeled
with the edge we're adding, namely |T_prime->edge[w]|.


@<Link |T_prime->edge[w]| with its two children and update |component|@>=
{ int i, here, parent;
component[w]=NO_PARENT;
for ( i=0; i<2 ; i++ ) {
	here=T_prime->edge[w].city[i];
	while ((parent=component[here])!=NO_PARENT) {
		component[here]=w;
		here=parent;
	}
	component[here]=w;
	T_prime->edge[w].child[i]=here; /* |child[i]| is aliased to |city[i]| */
}
}

@*Bit twiddling. 
The least common ancestor code below 
requires some fast bit manipulation.

In several places we need to copy the top 1 bit of a word
down through all the lower bits.  We can do this very quickly without
any branch instructions.

@<Module definitions@>=
#if SIZEOF_INT==8
# define copy_1_down(X) @t}\3{-5@>\
	(((X) |= (X)>>1), @t}\3{-5@>\
	 ((X) |= (X)>>2), @t}\3{-5@>\
	 ((X) |= (X)>>4), @t}\3{-5@>\
	 ((X) |= (X)>>8), @t}\3{-5@>\
	 ((X) |= (X)>>16), @t}\3{-5@>\
	 ((X) |= (X)>>32) )
#else /* |!SIZEOF_INT==8|.  Then hopefully integers are at most 4 bytes wide. */
# define copy_1_down(X) @t}\3{-5@>\
	(((X) |= (X)>>1), @t}\3{-5@>\
	 ((X) |= (X)>>2), @t}\3{-5@>\
	 ((X) |= (X)>>4), @t}\3{-5@>\
	 ((X) |= (X)>>8), @t}\3{-5@>\
	 ((X) |= (X)>>16) )
#endif


@
Array |pow_2| stores powers of two.

@<Module variables@>=

static const int pow_2[]={@t}\3{-5@>
	0x1,
	0x2,
	0x4,
	0x8,@t}\3{-5@>
	0x10,
	0x20,
	0x40,
	0x80,@t}\3{-5@>
	0x100,
	0x200,
	0x400,
	0x800,@t}\3{-5@>
	0x1000,
	0x2000,
	0x4000,
	0x8000,@t}\3{-5@>
	0x10000,
	0x20000,
	0x40000,
	0x80000,@t}\3{-5@>
	0x100000,
	0x200000,
	0x400000,
	0x800000,@t}\3{-5@>
	0x1000000,
	0x2000000,
	0x4000000,
	0x8000000,@t}\3{-5@>
	0x10000000,
	0x20000000,
	0x40000000,
	0x80000000@t}\3{-5@>
#if SIZEOF_INT==8
	,
	0x100000000,
	0x200000000,
	0x400000000,
	0x800000000,@t}\3{-5@>
	0x1000000000,
	0x2000000000,
	0x4000000000,
	0x8000000000,@t}\3{-5@>
	0x10000000000,
	0x20000000000,
	0x40000000000,
	0x80000000000,@t}\3{-5@>
	0x100000000000,
	0x200000000000,
	0x400000000000,
	0x800000000000,@t}\3{-5@>
	0x1000000000000,
	0x2000000000000,
	0x4000000000000,
	0x8000000000000,@t}\3{-5@>
	0x10000000000000,
	0x20000000000000,
	0x40000000000000,
	0x80000000000000,@t}\3{-5@>
	0x100000000000000,
	0x200000000000000,
	0x400000000000000,
	0x800000000000000,@t}\3{-5@>
	0x1000000000000000,
	0x2000000000000000,
	0x4000000000000000,
	0x8000000000000000
#endif
};


@ It will be useful to find logarithms of small numbers quickly.

@<Module variables@>=
static const int floor_log_2_small[16]= {
	/* dummy */@+0, @#
	0, @#
	1, 1, @#
	2, 2, 2, 2, @#
	3, 3, 3, 3,	3, 3, 3, 3};


@
The first bit manipulation
routine I'll define is |floor_log_2(x)|, which computes 
$\lfloor \log_2 (x) \rfloor$, as you might imagine.  Here I assume
that the argument $x$ is a positive integer.  

We use a binary search on the bits to find the highest 1 bit.
Let the \term{grey width} be the number of bits 
of $x$ that might be set to 1, counting from the least significant bit.
Initially, the grey width of $x$ is the word size.  Each
iteration cuts grey width by half.  When $x$ is known to be small,
we just use table lookup.
@^grey width@>
@^binary search@>

The loop is unrolled as the body of a |switch| statement; we depend
on each case falling through to the next.  
Unrolling loops is as old as the sun (Sun?), 
but unrolling a binary search in this way is pretty neat.
I first saw this ``unrolling a binary search'' trick in Knuth's book  
{\sl Literate Programming}.  It is also reminscent of ``Duff's device'';
see the \CEE/ Language FAQ, found on {\tt comp.lang.c}.

The table lookup at the end saves a couple of
possible branches at the cost of a possible cache miss.  
Is it worth it?  
%That trick is inspired by the well-known meta-transformation
%of $O(\log n)$ parallel algorithms with $n$ processors into an $O(\log n)$
%algorithm on $n/\log n$ processors.


% log log n / log log log n ?

As for all the shifting, the shifting in the |if| conditions are constant
expressions and so will be precomputed by the compiler.  The shifts
of variable |x| are by powers of two, and so benefit from fast barrel
shifters in modern processors.
@^barrel shifters@>

@<Module subroutines@>=
#if SIZEOF_INT>8
#error "The bit twiddling handles integers of at most 64 bits."
#endif
static inline int
floor_log_2(unsigned int x) 
{
	int ans=0;

#if SIZEOF_UNSIGNED_INT==8
	if ( x & (0xffffffff<<32) ) ans += 32, x>>=32;
#endif
	if ( x & (0xffff<<16) ) ans += 16, x>>=16;
	if ( x & (0xff<<8) ) ans += 8, x>>=8;
	if ( x & (0xf<<4) ) ans += 4, x>>=4;
	ans += floor_log_2_small[x];
	return ans;
}


@ We will be masking out portions of words.

Macro |lo_mask| lets us keep only the bottom bits of a word:
|w&lo_mask(i)| is the bottom $i$ bits of $w$.

Macro |hi_mask| lets us discard the bottom bits of a word:  
|w & hi_mask(i)| is all but the bottom $i$ bits of $w$.

% Although the code in this module is not entirely independent of
% word-width, we parameterize some of it by defining the macro
% |word_width| to be the number of bits in a machine word.


% at d word_width (sizeof(unsigned int)*8)
% at d all_ones ((unsigned int)(-1)) /* Assume two's complement arithmetic? */
@d lo_mask(X) (pow_2[(X)]-1)
@d hi_mask(X) (~lo_mask(i))

@*Least common ancestors.
Now we're ready to get to the meat of the module: least common ancestors.
In a rooted tree, vertex $u$ is an \term{ancestor} of vertex $v$ if $u$ appears
on the path from $u$ to the root;  we also say that $v$ is a
\term{descendant} of
$u$.  Equivalently, $u$ is an ancestor of $v$ if $v$ appears in the subtree
rooted at $u$.
Note that each node is its own
ancestor and its own descendant.  

Any two vertices in a rooted tree have a non-empty set of common
ancestors; in fact, the root is an ancestor of every node.  The 
\term{least common ancestor} 
of $u$ and $v$, denoted by $\LCA(u,v)$, is that ancestor
of both $u$ and $v$ which is a descendant of all the ancestors
of common to both $u$ and $v$.  In other words, $\LCA(u,v)$ is the root
of the smallest subtree in which both $u$ and $v$ appear.
@^ancestor@>
@^descendant@>
@^least common ancestor@>

@ Now that we've fixed our nomenclature, let's think about algorithms to
compute least common ancestors.  A simple algorithm to find $\LCA(u,v)$
would be to write down the list of vertices on 
the paths from both $u$ and $v$ to the root and to find their convergence
point.  In the worst case this would take time proportional to the depth
of the tree, which could be very bad.  

One might envision a scheme where we could digest the
tree into a corresponding balanced tree and run the simple algorithm
on the balanced tree.  But this would still run in logarithmic time.

It turns out that the predigestion idea can be worked into a scheme so
that the \LCA\ queries can be answered in constant time. (``Constant time''
assumes a fixed word size.  Some people might complain about this.
For machine words with $w$ bits, the $\LCA$ query algorithm presented
here runs in $O(\log w)$ time.)  The first known algorithm to achieve
constant-time queries is presented in 
D.~Harel and R.~E.~Tarjan, ``Fast algorithms for finding nearest common
ancestors.  {\sl SIAM Journal on Computing}, {\bf 13}(2):338--355, May
1984.  Here I use a simpler algorithm, a serial version of a parallel
algorithm: see B.~Schieber and U.~Vishkin ``On finding lowest common
ancestors: simplification and parallelization.  {\sl SIAM Journal on
Computing}, {\bf 17}(6):1253--1262, December 1988, and also Chapter 6,
``Parallel Lowest Common Ancestor Computation'' in the book
{\sl The Synthesis of Parallel Algorithms}, (INSERT PUBLISHER), 1993,
edited by J.~Reif.  I've used this later paper as the basis for this
implementation.

@ The tree is digested into three integer arrays indexed by vertex number:
|level|, |inlabel|, and |ascendant|.  We attempt to 
reduce cache misses when
processing \LCA\ queries by grouping 
these values for each vertex in a single structure, |digest_t|.

I also include a |cost| field in the digest structure because I
throw |T_prime| away when not debugging.

See also the |head| numbers below.
@^head numbers@>
@^level numbers@>
@^inlabel numbers@>
@^ascendant numbers@>


@<Module types@>=
typedef struct {
	int level, inlabel, ascendant;
	length_t cost;
} digest_t;

@
@<Module variables@>=
static digest_t *digest;

@  The first |n| correspond to vertices of the original graph,
and therefore have zero cost.  We initialize those fields at allocation
time instead of processing time because they are a function of
|n| only.

@<Other setup code@>=
digest = new_arr_of(digest_t,n+n-1);
{
int i;
for (i=0;i<n;i++) {
	digest[i].cost=0;
}
}

@
@<Other cleanup code@>=
free_mem(digest);
mem_deduct((n+n-1)*sizeof(digest_t));

@
@<Copy |cost| fields from |T_prime|@>=
{
int i;
for(i=n;i<n+n-1;i++) digest[i].cost=T_prime->edge[i].cost;
}

@ Entry |digest[i].level| is just the depth of vertex |i|.   
We compute all of level numbers in linear time with a breadth first search.
The search begins at the root of the tree, |T_prime->edge[n+n-2]|.

Array |queue| serves as a last-in first-out queue.  It is indexed by 
a read cursor |r| and a write cursor |w|.

@<Compute |level| numbers@>= 
{ int *queue = new_arr_of(int,n+n-1), r, w, i, ch;
digest[n+n-2].level=0;
queue[0]=n+n-2;
for ( r=0, w=1; r < w ; r++ ) {
	const int here = queue[r], cur_level = digest[here].level+1;
	for(i=0;i<2;i++) if ( (ch=T_prime->edge[here].child[i]) != NO_CHILD ) {
		digest[ch].level=cur_level;
		queue[w++]=ch;
	}
}
free_mem(queue);mem_deduct((n+n-1)*sizeof(int));
}


@ The inlabel number of a vertex is a function of its preorder number
and the size of subtree rooted there.    These are stored in arrays
|preorder| and |size|, naturally.  
Value |preorder[i]| is one more than the number of vertices visited before
vertex |i| in a preorder traversal of the tree.
Value |size[i]| is the number of vertices in the subtree rooted at |i|.


@<Compute |inlabel| numbers@>=
{
int *preorder=new_arr_of(int,n+n-1), *size=new_arr_of(int,n+n-1);
int preorder_number=0;
#define DFS_INLABEL
@<Do a depth-first search of |T_prime|@>@;
#undef DFS_INLABEL

free_mem(preorder);free_mem(size);
mem_deduct(2*(n+n-1)*sizeof(int));
}


@
Both |preorder| and |size| statistics 
 are computed via a depth-first search of the tree.
I'll separate the bookkeeping from the real action by using subsections.
This way I can use the same \CWEB/ bookkeeping code twice.

Array |in| stores the roots of the subtrees we're currently exploring.
It behaves as a stack.  Entry |cur_child[i]| tells
us  which 
child (0 or 1) of vertex |in[i]| is currently 
being explored.

We know the graph is acyclic, so we don't need to mark nodes.
Also, the graph is a binary tree.

We begin at the root, vertex |n+n-2|.

@<Do a depth-first search of |T_prime|@>=
{
int *in=new_arr_of(int,n+n-1), *cur_child=new_arr_of(int,n+n-1);
int top, here, next_child;

top=0;
in[top]=n+n-2;
cur_child[top]=-1;

while(top>=0) {
	here=in[top];
	switch(cur_child[top]) {
	case -1: /* Visit myself, then fall through. */
		@<Visit |here| the first time@>@;
	case 0: /* Visit the children. */
		next_child=T_prime->edge[here].child[++cur_child[top]];
		if ( next_child != NO_CHILD ) {
			/* Push that child on the stack. */
			in[++top] = next_child;
			cur_child[top] = -1;
		}
		break;
	default:
		@<Visit |here| the last time@>@;
		/* $\ldots$ and pop the stack. */
		top--;
	}
}
free_mem(in);free_mem(cur_child);
mem_deduct(2*(n+n-1)*sizeof(int));
}

@ For |inlabel| numbers, we need to update the preorder number as we
enter a node.

@<Visit |here| the first time@>=
#if defined(DFS_INLABEL)
preorder[here] = ++preorder_number; 
#endif 

@ For |inlabel| numbers, we need to update the |size| array as we leave
a node.

I'll define |inlabel[here]| but not explain its use.  
The preorder numbers of all the nodes in the subtree of |T_prime| rooted
at |here| range from |preorder[here]| through
|preorder[here]+size[here]-1|.  In fact, together they form precisely
that interval, no more and no less.
Value |inlabel[here]| is the value in that interval having most trailing
0 bits when expressed in binary.

Collectively the |inlabel| fields form  an injective mapping from
the |N := n+n-1| vertices of |T_prime| into a complete binary tree $B$ 
of depth $\lfloor \log_2 N\rfloor +1$.

See below for how |inlabel|s are used.

With care I can elide the taking of logarithms, as I've done below 
in the \LCA\ computation.  Maybe later.  Or maybe never, since
this is just an initialization phase, so timing is not so critical.

@<Visit |here| the last time@>=
#if defined(DFS_INLABEL)
{ const int child0=T_prime->edge[here].child[0],
			child1=T_prime->edge[here].child[1];
size[here] = 1 + (child0==NO_CHILD?0:size[child0])
			   + (child1==NO_CHILD?0:size[child1]);
}
{
const unsigned int last=preorder[here]+size[here]-1, 
	i=floor_log_2((preorder[here]-1)^last);
	digest[here].inlabel=hi_mask(i)&last; /* All but the bottom $i$ bits of |last|. */
}
#endif

@ The |ascendant| numbers may also be computed during a depth-first search.
Again, see Schieber.  The |inlabel| numbers must be computed first.

@<Compute |ascendant| numbers@>=
#define DFS_ASCENDANT
@<Do a depth-first search of |T_prime|@>@;
#undef DFS_ASCENDANT

@ Assuming |x| is positive, value |(x^(x-1))&x| is the rightmost 1 bit
of |x|, but isolated.


@<Visit |here| the first time@>=
#if defined(DFS_ASCENDANT)
if (top==0) { /* The root. */
	digest[here].ascendant=digest[here].inlabel;
} else {
	const int p=in[top-1], ap=digest[p].ascendant, ip=digest[p].inlabel; /* Parent data. */
	if ( digest[here].inlabel==ip ) digest[here].ascendant=ap;
	else {
		const int ih=digest[here].inlabel;
		digest[here].ascendant=ap+((ih^(ih-1))&ih);
	}
}
#endif

@
Schieber also prescribes that we compute a |head| table 
telling us the head of each inlabel chain. That is |head[i]| is
the shallowest vertex in |T_prime| with inlabel |i|.

We only ever want to know the |parent| of a head, so instead
I compute  a 
|parent_of_head| with the following defining equation:
$$\hbox{|parent_of_head[inlabel_w]==parent(head[inlabel_w])|}.$$
This saves an indirection.

All the |parent_of_head|
fields can be defined in four easy passes
over the array.  

But we do need the |head| array during initialization.
It is indexed by inlabel number, so it ranges from 1 through |n+n|.
We also compute a |parent| array, indexed by vertex (in |T_prime|).

@<Compute |parent_of_head| numbers@>=
{
int i, j, *head=new_arr_of(int,n+n), *parent=new_arr_of(int,n+n-1);
for (i=0;i<n+n;i++) head[i]=-1; /* Empty each bin. */
for (i=0;i<n+n-1;i++) { /* Compute heads of inlabel chains */
	const int ii=digest[i].inlabel, hii=head[ii];
	if ( hii==-1 || digest[i].level < digest[hii].level ) head[ii]=i;
}
for (i=0;i<n+n-1;i++) parent[i]=NO_PARENT,parent_of_head[i]=NO_PARENT; 
	/* Make parents null. */
for (i=0;i<n+n-1;i++)  /* Compute parents. */
	for ( j=0;j<2;j++) {
		const int child=T_prime->edge[i].child[j];
		if (child!=NO_CHILD) parent[child]=i;
	}
for (i=0;i<n+n-1;i++) /* Record parents of heads of chains. */
	parent_of_head[digest[i].inlabel] = parent[head[digest[i].inlabel]];
@<Verbose: print |parent|@>@;
@<Verbose: print |head|@>@;

free_mem(head);mem_deduct((n+n)*sizeof(int));
free_mem(parent);mem_deduct((n+n-1)*sizeof(int));
}

@ We need to define |parent_of_head|.
@<Module variables@>=
int *parent_of_head;

@ It must be allocated$\ldots$
@<Other setup code@>=
parent_of_head=new_arr_of(int,n+n);

@ $\ldots$ and freed.
@<Other cleanup code@>=
free_mem(parent_of_head);mem_deduct((n+n)*sizeof(int));


@*Least common ancestor queries.
We're now ready to process least common ancestor queries.

@<Module subroutines@>=
static inline int
decluster_lca(int x, int y)
{
	const digest_t xd=digest[x], yd=digest[y];
	if ( xd.inlabel == yd.inlabel ) return (xd.level<= yd.level)?x:y;
	else { /* The \LCA\ is neither |x| nor |y|. */
		const int xil = xd.inlabel, yil=yd.inlabel;
		int b, inlabel_z, common, jmask, xpp, ypp;
		@<Set |b| to the \LCA\ of $C_x$ and $C_y$ in the complete tree $B$@>@;
		@<Find |inlabel_z|, |common|, and |jmask|@>@;
		@<Find |xpp| and |ypp|@>@;
		return (digest[xpp].level <= digest[ypp].level) ? xpp : ypp;
	}
}


@ 
The digestion of |T_prime| decomposes it into (contiguous) chains of vertices.
Chain $C_u$ is the chain containing vertex $u$ of |T_prime|.
The inlabel numbers form an injective mapping from these chains of
|T_prime| into  a complete binary tree |B|.  
Tree $B$ is not explicitly stored, it's existence is implicit in the inlabel
numbers.  Futhermore, |inlabel[u]| is the ordinal position of the
vertex $C_u$ of $B$ in an in-order traversal of $B$, counting from 1.
@^inlabel numbers@>
@^in-order traversal@>
@^tree $B$@>

Finding least common ancestors in binary trees is easy, given in-order
numbers.  

For clarity,  Schieber describes
things in terms of logarithms, but in the interest of speed
I implemented the computation without logarithms.

The expression of a 1 followed by many zeroes, namely,
|t^(t>>1)|, used to be |(t+1)>>1|.  The old code is unsafe when |t| 
is the largest positive |int|, \eg, $2^{31}-1$, because adding 1 to
this value makes a large negative number.  Then the right shift might
extend the sign down and preserve the negative sign bit.  

The new
\def\AC{{\it AC}}%
\def\NC{{\it NC}}%
code may even be faster because it replaces an $\AC^0$ operation (addition)
and an $\NC^0$ operation (a single bit shift)
with
$NC^0$ operations (exclusive-or, logical and, and
a single bit shift).  On today's machines, who knows?


%$(t+1)>>1$ is unsafe when $t=2^{31}-1$ because of possible sign extension
%on the right shift.
%Replace it with $t\XOR(t>>1)$. (Here t is a low bits mask.)  Also, this
%might be faster because it replaces an $AC^0$ operation (t+1) with an $NC^0$
%operation (exclusive-or).

% at d rightmost_1(x) ((x^(x-1))&x)

@d min(A,B) ((A)<(B)?(A):(B))
@d max(A,B) ((A)>(B)?(A):(B))

@<Set |b| to the \LCA\ of $C_x$ and $C_y$ in the complete tree $B$@>=
{
const unsigned int xfuzz = xil^(xil-1), yfuzz = yil^(yil-1);
const unsigned int lomask=max(xfuzz,yfuzz)>>1;
int hi_diff = (xil^yil)&(~lomask);
if ( hi_diff ) { /* Neither ancestor nor descendant. */
	int t=hi_diff;  
	copy_1_down(t); 
		/* Sort of ``sign extend'' the top 1 bit of |t| down through the
lower bits. */
	b=(~t)&xil; /* Keep only the top few bits common to both |xil| and |yil|. */
	b|=t^(t>>1); /* But append a 1 followed by many zeros. */
} else { /* One is an ancestor of the other. */
	b=(xfuzz>=yfuzz)?xil:yil;
}
@<Verbose: print |b|@>@;
}

@ Let $z=\LCA(x,y)$. This section computes |inlabel_z|$:=$|inlabel[z]| 
without directly
computing |z| itself.  We use the ascendant numbers and some bit masking.
Again Schieber describes things in terms of logarithms, but I have elided
the logarithms.

In declarative form, 
|inlabel[z]|$:=$|inlabel[x]&~lo_mask(j)|
where |j=index_rightmost_1(u)|,
|u=common&~lo_mask(i)|, |common=ascendant[x]&ascendant[y]|,
and 
|i=index_rightmost_1(b)|.

Value |jmask| is |j| low-order 1 bits.

@<Find |inlabel_z|, |common|, and |jmask|@>=
{ const int imask=(b^(b-1))>>1; /* Mask of bits corresponding to low 0's in $b$. */
const int u = (common=xd.ascendant & yd.ascendant) & ~imask;
jmask = (u^(u-1))>>1; /* Mask of bits corresponding to low 0's in
$u$. */
inlabel_z = (xd.inlabel & ~jmask)|(jmask+1); /* |yd.inlabel| would also do. */
@<Verbose: print |inlabel_z|, |common|, and |jmask|@>@;
}




@ Vertex |xpp| is either |x| itself or is the parent of the head
of the inlabel chain at |inlabel_w_x|. Value |inlabel_w_x| is
all but the bottom |k+1| bits of |inlabel[x]|, followed by a 1 and
|k| zeroes.

Vertex |ypp| is similar.

@<Find |xpp| and |ypp|@>=
if (xd.inlabel==inlabel_z) xpp=x;
else {
	int inlabel_w_x;
	int kmask=xd.ascendant & jmask;
	copy_1_down(kmask);
	inlabel_w_x =(~kmask)&xil; /* Keep only the top few bits of |inlabel[x]|. */
	inlabel_w_x |=kmask^(kmask>>1); /* But append a 1 followed by many zeros. */
	xpp=parent_of_head[inlabel_w_x];
	@<Verbose: print |inlabel_w_x|, |xpp|@>@;
}
if (yd.inlabel==inlabel_z) ypp=y;
else {
	int inlabel_w_y;
	int kmask=yd.ascendant & jmask;
	copy_1_down(kmask);
	inlabel_w_y =(~kmask)&yil; /* Keep only the top few bits of |inlabel[y]|. */
	inlabel_w_y |=kmask^(kmask>>1); /* But append a 1 followed by many zeros. */
	ypp=parent_of_head[inlabel_w_y];
	@<Verbose: print |inlabel_w_y|, |ypp|@>@;
}


@ Given the least common ancestor function, computing the cluster distance
|d| is very easy.

We might consider reducing memory requirements by computing the
cost on the fly instead of storing it in the topology tree |T_prime|.
@<Subroutines@>=
length_t 
decluster_d(int u, int v)
{
	return digest[decluster_lca(u,v)].cost;
}

@*Extras.
Here are the extra support routines. That is, these routines are
not required for supporting decluster distance queries.

@ We may need to see what |T_prime| looks like.
The caller can safely change its contents if want to, because we've
already preprocessed it.

@<Subroutines@>=
decluster_tree_t *
decluster_topology_tree(void)
{
	return T_prime;
}

@ It is be useful to be able to output a tree.
@<Subroutines@>=
void
decluster_print_tree(FILE *out,decluster_tree_t const *t, const char *name) 
{
	if ( t )  {
		int n=t->n, i;
		const char *print_name = name ? name : "";
		errorif(t==NULL,"decluster_print_tree: given a NULL tree\n");
		errorif(n<0,"decluster_print_tree: tree %s size %d < 0\n",print_name, n);
		fprintf(out,"%s->n==%d\n",print_name,t->n);
		for (i=0;i<n;i++) {
			fprintf(out," %d (%d,%d) "length_t_spec"\n",
				i,
				t->edge[i].city[0], t->edge[i].city[1],
				length_t_pcast(t->edge[i].cost));
		}
	} else {
		fprintf(out,"Tree %s is NULL\n",name);
		fprintf(out,"For more data, make sure variable decluster_discard_topology_tree is zero)\n");
	}
}

@*Testing.
Since I don't claim to understand the least common ancestor code
completely, let's test it.

@(declustertest.c@>=
#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "length.h"
#include "memory.h"
#include "resource.h"
#include "dsort.h"
#include "read.h"
#include "kdtree.h"
#include "decluster.h"

tsp_instance_t *tsp_instance;
void(*sort)(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));
int verbose=100;
int noround=0;

@<Test module definitions@>@;
@<Test module variables@>@;
@<Test module subroutines@>@;


int
main(int argc, char **argv)
{
	length_t len;
	decluster_tree_t *mst;
	tsp_instance=new_of(tsp_instance_t);
	sort=dsort;
	mem_usage_reset();
	resource_setup(100);
	@<Test on a simple cost matrix@>@;
	@<Test case clean up@>@;
	@<Test on a Euclidean instance@>@;
	@<Test case clean up@>@;
	free_mem(tsp_instance);
	return 0; /* All ok. */
}

@ Here's a simple cost matrix.  It is equivalent to a Euclidean instance
with six points on a line.
@<Test module subroutines@>=
static length_t simple_mat_cost(const int i, const int j);
static length_t
simple_mat_cost(const int i, const int j)
{
	extern int verbose;
	static length_t cost_matrix[6][6]={@t}\3{-5@>
		{0,10,60,71,91,121}, /* distance from 0 */
		{10,0,50,61,81,111}, /* distance from 1 */
		{60,50,0,11,31,61}, /* distance from 2 */
		{71,61,11,0,20,50}, /* distance from 3 */
		{91,81,31,20,0,30}, /* distance from 4 */
		{121,111,61,50,30,0} /* distance from 5 */
	};
	errorif(i<0||i>5,"simple_mat_cost: i==%d out of range 0..6\n",i);
	errorif(j<0||j>5,"simple_mat_cost: j==%d out of range 0..6\n",j);
	if (verbose>=1000) printf("   simple_mat_cost(%d,%d)="length_t_spec"\n",
			i,j,cost_matrix[i][j]);
	return cost_matrix[i][j];
}

@ Here is the  minimum spanning tree we expect. It is unique up to
edge reordering.

@<Test module variables@>=
static decluster_edge_t simple_mat_MST_edges[]= {
	{{0,1},10},
	{{2,3},11},
	{{3,4},20},
	{{4,5},30},
	{{1,2},50} 
};
static int simple_mat_n= 1+sizeof(simple_mat_MST_edges)/sizeof(decluster_edge_t);


@
@<Module definitions@>=
#if DECLUSTER_DEBUG
#define print_tree(A,B) decluster_print_tree(stdout,A,B)
#else
#define print_tree(A,B)
#endif


@
@<Test module definitions@>=
#if DECLUSTER_DEBUG
#define print_tree decluster_print_tree
#else
#define print_tree(A,B)
#endif

@ Since the minimum spanning trees I use  are unique only up to reordering,
it is convenient to have a canonicalizing function.



@<Test module subroutines@>=
#define  swap(type,A,B) {type tmp; tmp=(A); (A)=(B);(B)=tmp;}
/* Messes up if |A| or |B| is the name |tmp|, or if either causes side
 effects. */

static void 
canonicalize(decluster_tree_t *t)
{
	int n=t->n, i;
	extern int verbose;
	errorif(t==NULL,"canonicalize: given a NULL tree\n");
	errorif(n<0,"canonicalize: tree size %d < 0\n",n);
	if ( verbose>=1000) print_tree(t,"pre-canon");
	dsort(t->edge,(size_t)n,sizeof(decluster_edge_t),edge_cmp);
	for (i=0;i<n;i++) {
		if ( t->edge[i].city[0] > t->edge[i].city[1] )
			swap(int,t->edge[i].city[0],t->edge[i].city[1]);
	}
	if ( verbose>=1000) print_tree(t,"post-canon");
}



@
@<Test module subroutines@>=
#define max(A,B) ((A)>(B)?(A):(B))
static void
compare_trees(decluster_tree_t *a, decluster_tree_t *b) 
{
	int i, n, ok=1;
	if ( verbose>=200) printf("a->n==%d\n",a->n);
	if ( verbose>=200) printf("b->n==%d\n",b->n);
	if(a->n!=b->n)ok=0,printf("compare_trees: trees differ in size %d vs. %d\n",
		a->n,b->n);
	n=a->n;
	if (ok)
	for (i=0;i<n;i++) {
		decluster_edge_t ea=a->edge[i], eb=b->edge[i];
		if(ea.city[0]!=eb.city[0]) ok=0,printf("compare_trees: "
			"a->edge[%d].city[0]==%d != b->edge[%d].city[0]==%d\n",
			 i,ea.city[0], i,eb.city[0]);
		if(ea.city[1]!=eb.city[1])ok=0,printf("compare_trees: "
			"a->edge[%d].city[1]==%d != b->edge[%d].city[1]==%d\n",
			 i,ea.city[1], i,eb.city[1]);
		if(ea.cost != eb.cost)ok=0, printf("compare_trees: "
			"a->edge[%d].cost=="length_t_spec" != b->edge[%d].cost=="length_t_spec"\n",
			i,length_t_pcast(ea.cost),i,length_t_pcast(eb.cost));
	}
	if (!ok) {
		int n=max(a->n,b->n);
		printf("a->n==%d\tb->n==%d\n",a->n,b->n);
		for (i=0;i<n;i++) {
			decluster_edge_t ea=a->edge[i], eb=b->edge[i];
			printf(" %d",i);
			if ( i<a->n ) printf(" a(%d,%d) "length_t_spec,
					ea.city[0],ea.city[1], ea.cost);
			else printf("\t");
			if ( i<b->n ) printf(" b(%d,%d) "length_t_spec,
					eb.city[0],eb.city[1], eb.cost);
			printf("\n");
		}
		errorif(1,"Trees are different");
	}
}


@ Variable |cost| is owned by the \module{READ} module.
@<Test on a simple cost matrix@>=
{
	decluster_tree_t simple_mat_MST;
	simple_mat_MST.n = simple_mat_n-1;
	simple_mat_MST.edge = simple_mat_MST_edges;
	printf("Testing simple matrix");
	tsp_instance->name=dup_string("dtsm");
	tsp_instance->comment=dup_string("decluster test simple matrix");
	tsp_instance->n = simple_mat_MST.n+1;
	tsp_instance->edge_weight_type=EXPLICIT;
	tsp_instance->edge_weight_format=FULL_MATRIX;
	tsp_instance->edge_weights=NULL; /* We supply our own cost function. */
	tsp_instance->short_edge_weights=NULL; 
	tsp_instance->coord=NULL; 
	tsp_instance->xmin=0;
	tsp_instance->xmax=0;
	tsp_instance->ymin=0;
	tsp_instance->ymax=0;
	mst=decluster_setup(simple_mat_n);
	printf(".");
	errorif(mst==NULL,"declustertest: Got null tree from decluster_setup\n");
	cost = simple_mat_cost;
	len=decluster_mst(tsp_instance,mst);
	printf(".");
	canonicalize(&simple_mat_MST);
	printf(".");
	canonicalize(mst);
	printf(".");
	compare_trees(&simple_mat_MST,mst);
	printf(".");
	decluster_preprocess(mst);
	printf(".");
	decluster_cleanup_tree(mst);
	printf(".");
	printf("mst works");
}

@ Now let's test the LCA's exhaustively.

@<Test module variables@>=
static length_t simple_mat_lca_len[6][6]={
	/* Row 0 */@+ {0, 10, 50, 50, 50, 50},
	/* Row 1 */@+ {10, 0, 50, 50, 50, 50},
	/* Row 2 */@+ {50, 50, 0, 11, 20, 30},
	/* Row 3 */@+ {50, 50, 11, 0, 20, 30},
	/* Row 4 */@+ {50, 50, 20, 20, 0, 30},
	/* Row 5 */@+ {50, 50, 30, 30, 30, 0}
};


@
@<Test on a simple cost matrix@>=
{
	int n=simple_mat_n;
	print_tree(decluster_topology_tree(),"simple mat T_prime");
#define lca_table simple_mat_lca_len
	@<Test |lca_table|@>@;
#undef lca_table
	printf("lca works");
}

@
@<Test |lca_table|@>=
{
	int i, j,k;
	for (k=0;k<2;k++) {/* Twice, for good measure. */
		printf("\n<");
		for (i=0;i<n;i++) {
			printf(":");
			for (j=0;j<n;j++) {
				const length_t d=decluster_d(i,j);
				printf(".");
				if (verbose >=500) printf("\n\t%d %d "length_t_spec,i,j,length_t_pcast(d));
				if (d!=lca_table[i][j]) {
					printf(
					"decluster_d(%d,%d) "
					"computed wrong: expected "length_t_spec
					" got "length_t_spec,
					i,j,
					length_t_pcast(lca_table[i][j]),
					length_t_pcast(d));
					errorif(1,"LCA bug");
				}
			}
		}
		printf(">");
	}
}

@
@<Test on a Euclidean instance@>=
{
	decluster_tree_t euc_MST;
	euc_MST.n= euc_n-1;
	euc_MST.edge= euc_MST_edges;
	printf("Testing simple Euclidean");
	tsp_instance->name=dup_string("dtse");
	tsp_instance->comment=dup_string("decluster test simple Euclidean");
	tsp_instance->n = euc_MST.n+1;
	tsp_instance->edge_weight_type=EUC_2D;
	tsp_instance->edge_weight_format=NONE;
	tsp_instance->edge_weights=NULL; 
	tsp_instance->short_edge_weights=NULL; 
	tsp_instance->coord=euc_coord;
	tsp_instance->xmin=0;
	tsp_instance->xmax=0;
	tsp_instance->ymin=0;
	tsp_instance->ymax=121;
	E2_create(tsp_instance);
	printf(".");
	mst=decluster_setup(euc_n);
	printf(".");
	errorif(mst==NULL,"declustertest: Got null tree from decluster_setup\n");
	switch_to(tsp_instance);
	len=decluster_mst(tsp_instance,mst);
	printf(".");
	canonicalize(&euc_MST);
	printf(".");
	canonicalize(mst);
	printf(".");
	compare_trees(&euc_MST,mst);
	printf(".");
	decluster_preprocess(mst);
	printf(".");
	decluster_cleanup_tree(mst);
	printf(".");
	E2_destroy();
	printf(".");
	printf("mst works");
}

@ Here is the  minimum spanning tree we expect. It is unique up to
edge reordering.

@<Test module variables@>=
static coord_2d euc_coord[]=
	{ {{0,0}}, {{0,10}}, {{0,85}}, {{0,96}}, {{0,116}}, {{0,146}} };
static decluster_edge_t euc_MST_edges[]= {
	{{0,1},10},
	{{2,3},11},
	{{3,4},20},
	{{4,5},30},
	{{1,2},75} 
};
static int euc_n= 1+sizeof(euc_MST_edges)/sizeof(decluster_edge_t);

@ Now test \LCA\ for the Euclidean instance.
@<Test module variables@>=
static length_t euc_lca_len[6][6]={@t}\3{-5@>
	/* Row 0 */@+ {0, 10, 75, 75, 75, 75},@t}\3{-5@>
	/* Row 1 */@+ {10, 0, 75, 75, 75, 75},@t}\3{-5@>
	/* Row 2 */@+ {75, 75, 0, 11, 20, 30},@t}\3{-5@>
	/* Row 3 */@+ {75, 75, 11, 0, 20, 30},@t}\3{-5@>
	/* Row 4 */@+ {75, 75, 20, 20, 0, 30},@t}\3{-5@>
	/* Row 5 */@+ {75, 75, 30, 30, 30, 0}
};


@
@<Test on a Euclidean instance@>=
{
	int n=euc_n;
	print_tree(decluster_topology_tree(),"Euc T_prime");
#define lca_table euc_lca_len
	@<Test |lca_table|@>@;
#undef lca_table
	printf("lca works");
}



@
@<Test case clean up@>=
decluster_cleanup();
printf(".\n");


@* Verbose output.
@<Verbose: print the preprocessing data@>=
#if DECLUSTER_DEBUG
{
	int i;
	printf("digest:   %12s %12s %12s %s\n", 
		"level","inlabel","ascendant","cost");
	for (i=0;i<n+n-1;i++) {
		printf("%9d %12d %12d %12d "length_t_spec"\n",
			i,digest[i].level,digest[i].inlabel,digest[i].ascendant,
			length_t_pcast(digest[i].cost));
	}
	printf("parent_of_head: (indexed by inlabel number)\n");
	for (i=1;i<n+n;i++) {
		printf(" %5d   %12d\n",i,parent_of_head[i]);
	}
}
#endif

@
@<Verbose: print |parent|@>=
#if DECLUSTER_DEBUG
{
	int i;
	printf("parent list:\n");
	for (i=0;i<n+n-1;i++) 
		printf(" %5d   %12d\n", i,parent[i]);
}
#endif

@
@<Verbose: print |head|@>=
#if DECLUSTER_DEBUG
{
	int i;
	printf("head list:\n");
	for (i=1;i<n+n;i++) 
		printf(" %5d   %12d\n", i,head[i]);
}
#endif

@
@<Module variables@>=
#if DECLUSTER_DEBUG
static char pp[]="          "; /* Print prefix. */
#endif

@
@<Verbose: print |b|@>=
#if DECLUSTER_DEBUG
if (verbose>=2000) {
printf("\n%s x=%d {lev=%d, inl=%d, asc=%d}\n",pp,
	x,xd.level,xd.inlabel,xd.ascendant);
printf("%s y=%d {lev=%d, inl=%d, asc=%d}\n",pp,
	y,yd.level,yd.inlabel,yd.ascendant);
printf("%s b=%d\n",pp,b);
}
#endif

@
@<Verbose: print |inlabel_z|, |common|, and |jmask|@>=
#if DECLUSTER_DEBUG
if (verbose>=2000) {
printf("%s inlabel_z=%d, common=%d, jmask=%d\n",pp,inlabel_z,common,jmask);
}
#endif


@
@<Verbose: print |inlabel_w_x|, |xpp|@>=
#if DECLUSTER_DEBUG
if (verbose>=2000) {
printf("%s inlabel_w_x=%d, xpp=%d\n",pp,inlabel_w_x,xpp);
}
#endif

@
@<Verbose: print |inlabel_w_y|, |ypp|@>=
#if DECLUSTER_DEBUG
if (verbose>=2000) {
printf("%s inlabel_w_y=%d, ypp=%d\n",pp,inlabel_w_y,ypp);
}
#endif

@*Index.