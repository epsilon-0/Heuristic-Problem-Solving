


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
$Log: kdtree.w,v $
Revision 1.159  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.158  1998/02/13 21:16:55  neto
Made prototypes and function declarations match w.r.t. const.
,

Revision 1.157  1997/10/25 21:44:06  neto
Finished coding quadrant stuff (I think). Must compile and test.

Revision 1.156  1997/10/25 19:49:11  neto
Compact the code.

Revision 1.155  1997/10/18 15:23:37  neto
I had missed a swapint conversion.  Now it compiles.

Revision 1.154  1997/10/18 14:40:25  neto
Added E2 supports()

Revision 1.153  1997/10/18 14:31:05  neto
Made all floats into doubles.
Checked for CEIL 2D compliance, and added comments in key places.
Minor editing.

Revision 1.152  1997/10/17  21:48:51  neto
Removed CUTDIMEN and THISDIMEN kludge by recasting the coord 2d structure
as an array instead of two named fields.

Revision 1.151  1997/10/17  20:47:35  neto
Move short fields to end of E2 node struct.

Revision 1.150  1997/09/27 18:06:44  neto
Fixed RCS log behaviour.

Revision 1.149  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.148  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.147  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.146  1997/01/21  17:42:14  david
Make showing of partitioning optional.

Revision 1.145  1997/01/17  21:15:44  neto
Fixed a printing leak.

Revision 1.144  96/12/13  15:08:17  neto
Mention hypot

Revision 1.143  96/12/02  15:26:06  neto
Added copyright notice.

Revision 1.142  96/11/11  16:36:44  neto
fixed a spelling mistake.

Revision 1.141  96/09/03  15:14:03  neto
Macro for ML programming language name.

Revision 1.140  96/08/16  13:04:53  neto
Added fixincludes.

Revision 1.139  96/08/16  12:42:26  neto
Converted putchar to printf.  Otherwise, I'd never get a prototype
for SunOS' \_flusbuf.

Revision 1.138  96/08/15  14:20:27  neto
Fixed the prototype for E2\_rnn

Revision 1.137  96/08/15  12:54:30  neto
Make it pass -Wall

Revision 1.136  96/07/30  17:15:34  neto
Fixed editing bug with respect to recurse if not hidden in E2\_rnn.

Revision 1.135  96/07/30  13:03:33  neto
Fixed to compile.

Revision 1.134  96/07/30  12:59:52  neto
Added KD\_BUILD\_SMALLEST\_SEGMENT\_FIRST

Revision 1.133  96/07/29  17:08:56  neto
Fixed to compile.

Revision 1.132  96/07/29  16:19:56  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

Revision 1.131  96/07/26  16:19:54  neto
Report experiments with hidden bit.

Revision 1.130  96/07/26  15:41:44  neto
Added KD\_NO\_HIDDEN\_RNN\_TEST

Revision 1.129  96/07/26  13:44:55  neto
Added compile-time-option KD\_NO\_HIDDEN\_BIT

Revision 1.128  96/07/26  13:21:36  neto
Recurse in rnn ony if not hidden.

Revision 1.127  96/07/26  12:45:03  neto
Don't be preachy about recursing on largest last.

Revision 1.126  96/07/25  14:02:54  neto
Fixed some minor editing of english.
Replaced INFINITY by a computed (floating point!) upper bound.
Isolated debugging output and made it subject to verbose value and
compile-time choices.

Revision 1.125  96/07/25  12:09:27  neto
More info to catch dsj1000 bug.

Revision 1.124  96/07/24  15:57:27  neto
Removed 117 debugging output.
Made bbox checkig optional.

Revision 1.123  96/07/24  15:48:46  neto
Fixed the bbox bug.  I wasn't updating the boboounding box
on the b and c elemnts that were swapped.

Revision 1.122  96/07/24  13:51:38  neto
More debugging outupt for failure kcase on lin318

Revision 1.121  1996/07/15  22:28:48  david
Simplified the code a bit.
It fails on lin318.tsp

Revision 1.120  1996/07/15  21:18:21  david
Bounding box every 1/kd\_bucket\_skip fraction, not 1-that fraction.
Big bug removed: bounding box initialization during Dutch National Flag
problem is now fixed.  (Had max's at infinity instead of effectively
negative infinity.)
Factored the nn search in a bucket.  The general case now is free
from checking that it doesn't return the seed.  It should be faster.
Added PostScript debugging output to draw the buckets.

Revision 1.119  1996/07/15  18:33:24  david
Fixed a name of a section.
Fixed bucket search for nearer neighbour.

Revision 1.118  1996/07/15  16:00:08  david
Compiles now.  I had to add |f.i.| to many of the field names.
I also had to add $E2\_nn\_dist$ back in for the bounding box test.

Revision 1.117  1996/07/15  15:23:55  david
Give up on FRNN, ball searching for now.
We don't need them for Greedy / MF heuristic.

Revision 1.116  1996/07/05  21:02:33  david
Continued a bit on fixed radius nearest neighbours.
Added more about stack overflow.  Referenced Peyton Jones' Implementing
Functional Languages.

Revision 1.115  1996/07/05  20:34:02  david
I forgot to mention the move to using only squared distances in
nearest neighbour search.

Revision 1.114  1996/07/05  20:31:31  david
Changed $E2\_tree$ to $E2\_root$.
Implemented $unhide\_all$ and $hide\_all$.
Got started on comments about fixed radius nearest neighbour.

Revision 1.113  1996/07/05  17:13:32  david
Added some index references to people.
changed is\_internal to is\_bucket.
Worked on nearest neighbours computation.

Revision 1.112  1996/07/04  20:07:38  david
Clarify comments in first part of the document.
Make the recursive building more CWEB-like.
Finished the hiding/unhiding part, but I haven't tried compiling it.

Revision 1.111  96/06/28  14:00:54  neto
Added comments about persistence.
Fixed too-long-line for cweave.
Worked on hiding/unhiding
Added to nn.

Revision 1.110  96/06/28  12:58:29  neto
Ensure theat recursing won't break the stack.
Start work on nearest neighbour query.

Revision 1.109  96/06/26  12:15:42  neto
Made coord a static variable.

Revision 1.108  96/06/26  12:08:19  neto
Be careful with macro parameters.  Parenthesize them.

Revision 1.107  96/06/26  12:05:44  neto
This file was added after I went to 100 and above.

Revision 1.6  96/06/26  12:02:28  neto
Fixed my in-file log.  (I edited, saved, and committed the revision,
but didn't reload before the next commit...)

Revision 1.5  96/06/26  11:38:41  neto
Removed some printing clutter.

Revision 1.4  96/06/26  11:35:41  neto
Most importantly, I fixed the construction bug.  The code that was
moving equal elements to the middle did not handle the left end properly.
It was 0-based instead of being based at the real lower end: lo.

I added comments about what to do with an empty bucket, and why.

I added better paranoid checking diagnostics.

Revision 1.3  96/06/25  17:10:15  neto
Added missing break.
Fixed a swap.  Duh.
More precise output.

Revision 1.2  96/06/25  16:41:37  neto
Fixed typo in med3 computation.
Added better debugging output for paranoid.
Fails paranoid check on lin105.tsp

Revision 1.1  96/06/24  17:16:26  neto
Initial revision

}

@s near void
@s far int

@*$k$-dimensional search structures.
Many geometrical algorithms can be made to run faster in practice if we
use a $k$-dimensional search structure.  Bentley (INSERT REFERENCE) has
@^Bentley, Jon Louis@>
shown this to be true of many algorithms related to the TSP.  

Bentley (INSERT REFERENCE) uses a $k$-d search tree over 
\term{semi-dynamic point sets}@^semi-dynamic point sets@>:
these are sets of points where all the points are known in advance,
and individual points may be hidden and unhidden from the queries.  

Bentley actually describes the hiding and unhiding as \term{deletion} and 
\term{undeletion}.
But as the points still remain in the structure and may be recovered, I
prefer the concept of hiding; it seems a more accurate description of
what is going on.  This is related in some ways to the notion of
persistency.
In general, we say a data structure is \term{(fully) persistent}
@^persistence, full@>
if we can completely recover the visible part of any of 
its old states; we say it is 
\term{partially persistent} if we may query any of its old states, but
@^persistence, partial@>
may update only its latest state.  Persistency 
is a hot topic in data structures, and has led to some interesting
and intuitive new algorithms (INSERT REFERENCE).
@^Tarjan, Robert Endre@>
@^Sleator@>

This module implements $k$-d trees for semi-dynamic point sets.

Actually, only one tree at a time is supported by this module.  
This is all I need (so far)
in the TSP application.  This scheme is also simpler to implement,
and it saves a lot of
parameter passing time (or indirection time) as compared with fully 
object-oriented code.  Besides, the code that Bentley describes
for his experiments in (INSERT REFERENCE) only supports one tree at a time.
%Some of his parameters and maybe even conclusions might change if he
%wrote fully object-oriented code.
%%%% Is that true?  Check C++ meaning for |static| storage class specifier
%%%% for a class member.

The outline of this module is as follows:

@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Early module headers@>@;
@<Module headers@>@;

@<Early module type definitions@>@;
@<Module type definitions@>@;
@<Module variables@>@;
@<Global variables@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *kdtree_rcs_id = "$Id: kdtree.w,v 1.159 1998/07/16 21:58:55 neto Exp neto $";

@ The exported interface is contained in the \file{kdtree.h} header file,
which has the following form.

@(kdtree.h@>=
extern const char *kdtree_rcs_id;
@<Exported variables@>@;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "kdtree.h"

@*Interface.  
This section presents the interface to the $k$-d tree as specified by
Bentley. I have altered the names of the procedures to fit within my
naming scheme for modules.  
@^Bentley, Jon Louis@>

Currently this module only supports 2-dimensional point
sets with the Euclidean metric.
The names of the procedures all begin with $E2$ to reflect this fact.

The interface is as follows:

|void E2_create(tsp_instance_t *tsp)| 
creates a tree based on the TSP instance |tsp|.  
The structure is defined
in the \module{READ} module.

|void E2_destroy()| destroys the search tree.

|void E2_hide(int i)| hides point |i| from future queries (until the
next |unhide| operation).

|void E2_unhide(int i)| makes point |i| visible to future queries (until the
next |hide| operation).

|void E2_hide_all(void)| hides all points.  

|void E2_unhide_all(void)| hides all points.

|int E2_nn(int i)| returns the index of an unhidden point that is nearest
to point |i|, but is not |i| itself. If there is none, $-1$ is returned.

|int E2_nn_quadrant(int i, int q)| returns the index of an unhidden point 
in relative quadrant $q$ that is nearest
to point |i|, and is not |i| itself. If there is none, $-1$ is returned.
For example, quadrant 1 relative to point |i| is the set of all points
to the northeast of |i|.

|void E2_frnn(int i, double rad, void (*proc)(int j))| is 
a 
\term{fixed-radius nearest neighbour search}@^fixed-radius nearest neighbour search@>.
It calls |proc| on all points |j| that lie within |rad| units of point |i|.

The following two procedures are used to implement 
\term{sphere of influence}@^sphere of influence@>
computations.

|void E2_set_radius(int i, double r)| sets the radius of the 
active sphere around
point |i| to |r| units.

|void E2_ball_search(int i, void (*proc)(int j))| calls |proc| on every
point |j| in whose active sphere point |i| lies.
% The girl the boy the dog bit hit cried.
Get that?  Let's try it a different way:  this procedure determines which
points |j| have point |i| somewhere within their own (|j|'s) 
active sphere; it calls
|proc| on every such |j|.


@<Exported subroutines@>=
void E2_create(tsp_instance_t *tsp);
void E2_destroy(void);
void E2_hide(int i);
void E2_unhide(int i);
void E2_hide_all(void);
void E2_unhide_all(void);
int E2_nn(int i);
int E2_nn_quadrant(int i, const int q);
void E2_frnn(int i, double rad, void (*proc)(int j));
void E2_set_radius(int i, double r);
void E2_ball_search(int i, void (*proc)(int j));


@ It is also useful to know when a 2-d trees may be used with a particular
TSP instance.
@<Exported subroutines@>=
int E2_supports(tsp_instance_t *tsp);


@  These routines support TSP instances with |EUC_2D| and |CEIL_2D| cost
functions.
@<Subroutines@>=
int 
E2_supports(tsp_instance_t *tsp) 
{
	switch(tsp->edge_weight_type) {
	case EUC_2D:
	case CEIL_2D:
		return 1;
	default:
		return 0;
	}
}


@ We need the interface to the \module{READ} module.  In turn,
it needs the \module{LENGTH} module.
@<Early module headers@>=
#include "length.h"
#include "read.h"

@* $k$-d trees.
A $k$-d search tree is a tree over some set of points in $k$-dimensional
real-space, together with the partitioning properties given in the following
paragraphs.

Each internal node
of the tree is associated with one of the $k$ dimensions, called |cutdimen|,
and also has a real-valued
|cutvalue|.  All points in the subtree rooted at the |lo_child| have their
|cutdimen|-dimension value being no greater than |cutvalue|, and all
points in the subtree rooted at the |hi_child| have their value no less
than |cutvalue|.  

Each external node of the tree, known as a \term{bucket}@^bucket@>, contains all
the points that simultaneously satisfy all 
the constraints in the internal nodes on
the path from the bucket to the root.  
These are stored as indices |lo| and |hi| into |perm|, which itself is
an array holding a permutation of the point names.  The points in
that bucket are |perm[lo]| through |perm[hi-1]|.

There are other embellishments to the data structure, be we are ready to
start defining it now.

The short fields are placed at the end so all the other fields are 
word-aligned.  This may speed things up on some architectures.

@<Module type definitions@>=
typedef struct E2_node_s {
	@<Other common fields@>@;
	union {
		struct {
			int cutdimen;
			double cutvalue;
			struct E2_node_s *lo_child, *hi_child;
			@<Other internal node fields@>@;
		} i;
		struct {
			int lo, hi;
			@<Other external node fields@>@;
		} e;
	} f;
	char is_bucket;
	@<Other common short fields@>@;
} E2_node_t;


@  The permutation array |perm| is visible to everyone because we might make
use of it elsewhere.

For example, I have an idea that we might get better performance if
we reorganize the data according to a space-filling curve.  
This would move together in memory those points which are close together
geographically.  I have some notions on a particular curve to follow,
and have a hunch that it provides an optimal layout, given the kind
of access pattern that Lin-Kernighan exhibits.  This would be a very
nice theorem to prove.  It's ``future work''.

I briefly mentioned this reorganization idea during my Qualifying Oral exam.
But I didn't speculate on optimality$\ldots$

@<Global variables@>=
int *perm;


@ The maximum number of points allowed
in a bucket,
recorded in the variable
|kd_bucket_cutoff|,
is chosen to be a small positive integer.
Bentley found that
a value of 5 works well.  
@^Bentley, Jon Louis@>

Now, a cutoff of 5 works well on Bentley's implementation, which
constitutes a machine (a VAX-8550),
a compiler, and his program, \etc.
Should we use a different value 
on a modern RISC machine with a different
compiler and memory architecture?  
We may want to experiment with this value, which is why
we put it in a variable and not in a compile-time constant.
However, we use a default value of 5.

@<Global variables@>=
int kd_bucket_cutoff=5;

@
@<Exported variables@>=
extern int kd_bucket_cutoff;




@ Now, Bentley showed that bottom-up accesses are much faster in practice
@^Bentley, Jon Louis@>
than top-down searches.
In particular, his implementation performs
an all-nearest-neigbhours computation on
a point-set uniform in a square using
bottom-up accesses in
linear time, \ie, constant amortized time per lookup.  
He presents
some theoretical arguments as to why things should turn out this way.

In addition, Bentley's implementation takes only linear time to 
compute a 
nearest-neighbour tour on such distributions.
Finding such a tour
is more involved than all-nearest-neighbours because, first,
one
hides each point as it acquires a neighbour, and second, at the end of the
computation the unhidden points are likely to be far away both in the
Euclidean metric and in the tree.

In contrast, a top-down search takes at least logarithmic time on average:
one must traverse the path from the root to the bucket containing
the point.  In a tree whose arity is bounded by a constant,
the average depth of an item is at least logarithmic in the number of items.

The upshot is that we put a parent pointer in each node.

@<Other common fields@>=
struct E2_node_s *parent;


@ We need a way to hide entire subtrees at a time.  This is done by
setting the |hidden| field to a true value.
An invariant we must maintain is that if a node is hidden,
then its children (if any) are also hidden.

@<Other common short fields@>=
#if !defined(KD_NO_HIDDEN_BIT)
char hidden;
#endif


@ In a bottom-up search that hopes visit a sub-logarithmic number of nodes, 
we need to know when to stop climbing the tree.  This is done by checking
against a description of the bounding box of that subtree.

For example, if we desire a nearest neighbour to $i$ that we know is
within $r$ units (say, because we already have another neighbour that
is $r$ units away from $i$), then we stop once the ball of radius $r$
centred around point $i$ is fully contained by the bounding box
of the subtree.

Bentley's experiments show that things actually run faster if we only
@^Bentley, Jon Louis@>
occasionally compare to this box.  For speed, he suggests comparing
only at every third level in the tree.   


In terms of defining our data structure, if we compare only occasionally,
then we should store only occasionally as well.   One possible
scheme is at each level store a pointer to the corresponding bounding box;
a missing bounding box would be recorded as a |NULL| pointer.
We can store a $k$-dimensional bounding box in $2k$ words, 
and a pointer is stored in one word.
Assuming that memory allocator space overhead is negligible and that
we store a bounding box for every $s$ nodes (this is 
simpler than analysing every $s$ {\it levels}---why?),
this scheme uses $s+2k$ words where the obvious scheme would use $2sk$.
For the 2-d case and one bounding box every
three nodes, the clever scheme uses 11 words 
(two |NULL| box pointers, one valid box pointer, and one box structure)
for every 24 words 
(three box structures)
in the
original scheme.

This analysis assumes that the coordinate
type and the pointer type take the same amount of space.
Using |double| and ordinary \CEE/ pointers, this is valid 
on most 32-bit architectures.  
(Will Microsoft's |near| and |far| pointers
@^Microsoft@>
disappear by the time you read this?  Probably.)
I think things change on 64-bit architectures and higher, but I'm willing
to sweat the difference.

So let's go with the clever scheme.  In particular, a pointer to
a possible bounding box gets placed in each node.
Question: would I save any space if I placed them only in internal nodes?

@<Other common fields@>=
E2_box_t *bbox;

@ Of course, we need a definition of a 2-d box.
@<Early module type definitions@>=
typedef struct {
	double xmin,xmax,ymin,ymax;
} E2_box_t;

@ The space analysis we've done assumes that the per-box
space
overhead of the memory allocator is negligible.  This isn't the case
if we use the general purpose |malloc| and |free| routines, and
by extension, the |new_of| routine that uses them.  However, we can
make the per-box space overhead as small as we like by using the pool-oriented
allocator of module \module{POOL} and picking a suitably large
minimum block size.

@d new_box() ((E2_box_t *)pool_alloc(box_pool))
@d free_box(P) pool_free(box_pool,(P))


@ Of course, we need the interface to \module{POOL}.
@<Module headers@>=
#include "pool.h"


@ I'll use a global variable to keep track of the number of levels
to skip between bounding boxes.  This allows us to experiment with
different values, for example by setting it via a command-line option.
The default is Bentley's suggestion of every third level.
@^Bentley, Jon Louis@>

@<Global variables@>=
int kd_bbox_skip=3;

@
@<Exported variables@>=
extern int kd_bbox_skip;

@*The opportunity of equal elements.
Bentley experimented with various point-set distributions and discovered
@^Bentley, Jon Louis@>
that his implementation of $k$-d trees behaved pretty much the same way
as on sets where the points were drawn uniformly over the unit square.

When he used a simple partitioning method,
there was one glaring exception to this is rule: the ``spokes'' distribution
forced his program to touch four times as many tree nodes.  
A 2-d spokes distribution has half the points with $x=1/2$
and with $y$ chosen uniformly from $[0,1]$, and the other half of the
points with $y=1/2$ and $x$ chosen uniformly from $[0,1]$; this results
in a large ``plus'' sign: $+$.

In the $k$-d search tree 
paper, Bentley's fix (see section 7) 
was to use a more elaborate partitioning algorithm
based on a theorem of Bentley and Shamos INSERT REFERENCE (and also
described by Preparata and Shamos INSERT REFERENCE) that guarantees
the existence of a good so-called nearest neighbour
cut plane given that the point set obeys
a certain sparseness criterion.  
Given these conditions on the intput, the 
partitioning algorithm takes $O(n \log n)$ time, for fixed $k$.

However, Bentley himself admits that, although better than naive partitioning,
this elaborate partitioning scheme
is not completely robust.  In fact, Papadimitriou and Bentley INSERT REFERENCE
have shown that some inputs have {\it no\/} good nearest neighbour cut planes.


@ I propose a different solution to this problem.  Ironically, 
it is based on observations made by Bentley  and McIlroy in 
@^Bentley, Jon Louis@>
@^McIlroy, M.~Douglas@>
``Engineering a Sort Function'', {\sl Software---Practice and Experience},
Vol 23(11), 1249--1265, November 1993.  There, they describe their
experience of writing a new library implementation of Quicksort.
@^Quicksort@>
(This is an excellent paper.  Go read it.)

Part of their work was to recognize the fact that it often pays
to treat specially those elements that compare equal to the pivot.
In an implementation of Quicksort, if one parititions elements into
three classes---those less than, equal to, and greater than the pivot---then
one often saves many recursive calls if a significant fraction of the
elements compare equal to the pivot.  

In fact, the spokes distribution in the $2$-d partitioning
problem exhibits exactly this
kind of behaviour: in a given dimension, half the points compare equal
to the pivot.  So I propose the same solution for the $k$-d partitioning
problem as Bentley and McIlroy describe for Quicksort:  treat equal
elements specially, by partitioning into three classes.  Bentley
and McIlroy call this \term{fat partitioning}@^fat partitioning@>,
and they observe that task is equivalent to Dijkstra's `Dutch National Flag'
problem.  
@^Dijkstra, Edsger W.@>
We'll hear more of this later when we actually do the partitioning.

To implement this, we add another child to each node.
(Is this a record?  Eight paragraphs for one variable declaration?)
@<Other internal node fields@>=
struct E2_node_s *eq_child;

@ Unfortunately, there is a small fly in the ointment: what if
there are many points with exactly the same coordinates?
@^degenerate inputs@>
If we don't check for this problem, then we will soon come to
a point where we endlessly recurse on
the equal elements---there being no others---trying to break them into 
buckets with no more than
|kd_bucket_cutoff| points each.

The solution is to 
never flatten a dimension twice in the same path from a bucket to the
root.
This implemented by passing a bit mask down the recursion tree.


If there are a large number of points with exactly the same coordinates,
then we get poor performance on the queries.  But gee whiz, what are
we supposed to do?  You deserve what you get if you don't preprocess
the input to remove duplicates.  So there!

@*Creating the tree.
Although we're not quite finished defining the data structure, we
now know enough about it to write most of the code that builds it.
We'll put in placeholders to be filled in later when we introduce the
necessary concepts.

Here's the outline of the creation routine.

@<Subroutines@>=
void
E2_create(tsp_instance_t *tsp) 
{
	errorif(!E2_supports(tsp), "2-d trees may not be used for this instance");
	@<Allocate structures@>@;
	@<Build the tree@>@;
}

@
The first step is to allocate the space for the tree.  In
general, 
the 
buckets have an irregular number of items in them, so we can't 
allocate all the tree nodes in advance: we don't even know how many
we'll use.

So we'll have to settle for creating the pool within which we'll
be allocating the tree nodes.  Let's allocate them in 500-node blocks.

We also need a pool for the bounding boxes.

@d new_node() ((E2_node_t *)(pool_alloc(node_pool)))
@d free_node(P) pool_free(node_pool,(P))

@<Allocate structures@>=
node_pool = pool_create(sizeof(E2_node_t),500);
box_pool = pool_create(sizeof(E2_box_t),500);

@ Of course, we'll need to declare these variables.
@<Module variables@>=
static pool_t *node_pool, *box_pool;

@ We also need to allocate the permutation array.  
We can allocate this one all
in one swoop because it has $n$ entries, where $n$ is the number of cities.

Let's cheat a bit and initialize the array as well.  It starts out with 
the identity permutation.

@<Allocate structures@>=
n = tsp->n;
perm = new_arr_of(int,n);
{int i; for (i=0;i<n;i++) perm[i]=i;}

@
@<Module variables@>=
static int n;

@ We need the interface to the ordinary memory allocator.
@<Module headers@>=
#include "error.h"
#include "memory.h"

@ While we're thinking about memory allocation, let's take care of 
deallocation.  

@<Subroutines@>=
void
E2_destroy(void) {
	pool_destroy(node_pool);
	pool_destroy(box_pool);
	box_pool = node_pool = NULL; /* Let's be defensive. */
	free_mem(perm);
	@<Other deallocation@>@;
}

@ We've used the constant |NULL|, which is written in ordinary
\CEE/ text as \hbox{|NU|}|LL|.  This constant is defined in the 
\file{stddef.h} header file.  While we're including it, let's include
some other standard header files.

@<System headers@>=
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "fixincludes.h"


@
The process of building the tree is much  like executing a Quicksort
routine.  We pick a pivot element, and then partition the points into 
three classes:
points preceding the pivot go in the |lo_child| subtree, 
points matching the pivot go in the |eq_child| subtree, and
points following the pivot go in the |hi_child| subtree.  
Then we recursively build the three subtrees.

However, the $k$-d tree-building problem has the extra complication of
picking the dimension along which we partition, |cutdimen|.  Bentley
@^Bentley, Jon Louis@>
suggests partitioning along the dimension which has maximum spread.
We do that here.  Note that the bookkeeping to determine spreads can
be folded into the parititioning at the previous level.

Because this process is naturally recursive, we use a separate recursive
procedure to do the dirty work.  But we must prime it with the right
arguments.  

It turns out that the range for the entire data set has already been
computed for us in the instance-reading function.  We just access those
values.

The set of values to be partitioned is specified using a closed-on-the-left
and open-on-the-right index range.

@<Build the tree@>=
coord = tsp->coord;
errorif(n<=0,"Need at least one point; instance has %d points",n);
E2_root = E2_build_helper(NULL,0,0,0,n,
	tsp->xmin,tsp->xmax,tsp->ymin,tsp->ymax);

@ We need to declare the tree variable and the coordinate array variable.
The coordinates will be needed for queries later, which is why need to
keep it around on a more permanent basis.
@<Module variables@>=
static E2_node_t *E2_root;
static coord_2d *coord;

@ The helper routine returns the
root of the subtree that it creates.

We are guaranteed to be given a positive number of points to partition,
so there will be at least one bucket created at this level.  So we create
it right away and fill in the common fields.

We increment the level number before testing to see whether to include
a bounding box 
because there is no sense in having a bounding box test at the root.

This invocation creates a bucket if there are few enough elements
(no more than |kd_bucket_cutoff|), or when both dimensions have already
been flattened.  The dimensions which have been flattened are recorded
in the bit vector |flat_dimen|.  Bit 0, with value $2^0=1$ is turned
on when the $x$ dimension is flattened, \ie, when one of our ancestors,
possibly this node, is an |eq_child| of a node whose cutting dimension
is the $x$ dimension.  Similarly, bit 1, with value $2^1=2$ is turned
on if the $y$ dimension is flattened.

@<Module subroutines@>=
static E2_node_t *
E2_build_helper(E2_node_t *parent,int flat_dimens,int level,
	int lo, int hi, 
	double xmin, double xmax, double ymin, double ymax) {
	E2_node_t *node = new_node();
	node->parent = parent;
#if !defined(KD_NO_HIDDEN_BIT)
	node->hidden = lo>=hi;
#endif
	if ( (++level % kd_bbox_skip)==0 ) {
		node->bbox = new_box();
		node->bbox->xmin = xmin;
		node->bbox->xmax = xmax;
		node->bbox->ymin = ymin;
		node->bbox->ymax = ymax;
		@<Paranoid: check bounds@>@;
	} else {
		node->bbox = NULL;
	}
	if ( hi-lo <= kd_bucket_cutoff || flat_dimens == 0x03 ) {
		node->is_bucket = 1;
		node->f.e.lo = lo;
		node->f.e.hi = hi;
		@<Fill other bucket fields@>@;
		@<Make elements point to this bucket@>@;
	} else {
		node->is_bucket = 0;
		@<Create three children@>@;
	}
	return node;
}

@
It is possible for a node have no elements in it.  Such nodes must be buckets,
and have |hi==lo|.   The bounding box of such a bucket should not be trusted.

I could have chosen to avoid creating a node for an empty bucket, in which
case returning |NULL| would be the right answer.  However, I didn't do so
for the following reasons.

First, I didn't think of the possibility of empty buckets
before I wrote the code.  That's an honest answer.

Second, empty buckets are likely to be rare.  (I should measure this.)
So checking for a |NULL| pointer {\it every\/} time I want to visit a node
is likely to take more time overall than visiting an empty bucket.    
We can use the same simple code to cover both cases---empty and non-empty
buckets---it's just the termination test of the |for| loop.   
This shows again the benefit of treating zero as a first-class citizen
among numbers.

@  Bottom-up searching only works if we can instantly jump to 
the right bucket.  We define an array that does this mapping for us.
@<Make elements point to this bucket@>=
{ int i;
for (i=lo;i<hi;i++) E2_point_to_bucket[perm[i]] = node;
}

@ Of course, we need to declare this array.
@<Module variables@>=
static E2_node_t **E2_point_to_bucket;

@ And we must allocate space for it.
@<Allocate structures@>=
E2_point_to_bucket = new_arr_of(E2_node_t *,n);

@ And finally free it.
@<Other deallocation@>=
free_mem(E2_point_to_bucket);

@ The recursive case is much more interesting.  It picks a cutting dimension,
finds a pivot, and then partitions.

If no dimensions have been flattened, then the
cut dimension is the one with the greatest range.
Otherwise, pick the nonflat dimension.

Exercise: Show that I could have replaced the entire |switch| statement
by the statement
|cutdimen = flat_dimens ? (xmax-xmin < ymax-ymin) : (2-flat_dimens);|.
Would it have been worth it?

@<Create three children@>=
{ int cutdimen=0; /* Satisfy GCC's dataflow analysis. */
switch ( flat_dimens ) {
case 0:
	if ( xmax-xmin > ymax-ymin ) cutdimen = 0;
	else cutdimen = 1;
	break;
case 1:
	cutdimen = 1;
	break;
case 2:
	cutdimen = 0;
	break;
case 3:	/* A valid |flat_dimens| value, but not here, so fall through. */@;
default:
	errorif(1,"Invalid flat_dimens: %d", flat_dimens);
}
@<Partition along dimension |cutdimen|@>@;
}

@ Partitioning involves finding a pivot and then splitting the points into
three classes.

@<Partition along dimension |cutdimen|@>=
{ int p;	/* The pivot's index in |perm|. */
int a,b,c,d;	/* Cursors for partitioning. */
double exl,exh,lxl,lxh,gxl,gxh;	/* |x| extremes. */
double eyl,eyh,lyl,lyh,gyl,gyh;	/* |y| extremes. */
@<Find the pivot@>@;
@<Partition around |perm[p]|@>@;
@<Build the subtrees@>@;
}

@
In the Quicksort application, Bentley and McIlroy settled on the following
@^Bentley, Jon Louis@>
algorithm for finding a pivot.  For large inputs, it uses Tukey's `ninther':
the median of the three medians of three.  For smaller inputs, a median
of three is used.  

Now, 
their pivot-picking algorithm
may not be suitable here
because their application differs from ours in the following ways.
First, our cost model differs: we compare coordinates, which is fast,
while their comparison is a function-call away.  
Second, they are doing a pure sort; we too are sorting, but in $k$ dimensions.
Does this change matters?
Third, their machine is a VAX-8550; ours is likely to be a modern RISC machine.
Fourth, theirs is a library function, so side-effecting the random number
generator is a bad thing; we don't care about that: how much better or
slower is randomization? 

However, until someone gives convincing evidence that there are better choices
for the pivot, I will stick to the Bentley and McIlroy solution.
Before you run off and try to find a better solution, here's how
their algorithm stacks up:
to sort $n$ random 30-bit integers, they required $1.094n\lg n-0.74n$
comparisons.  (This is for $n$ ranging over each power of two from 128 to
65536. The function was found by a weighted least-squares regression fit.)

If you're thinking `pick the true median', then your thoughts
have already been anticipated.  In the Quicksort application, finding
the true median, although taking only linear time, is too costly.

@d val(a) (coord[perm[(a)]].x[cutdimen])
@d valx(a) (coord[perm[(a)]].x[0])
@d valy(a) (coord[perm[(a)]].x[1])
@d med3(a,b,c) (val(a)<val(b) ? (val(b)<val(c) ? b : val(a)<val(c) ? (c):(a)) @;
							  : (val(b)>val(c) ? b : val(a)>val(c) ? (c):(a)) )

@<Find the pivot@>=
p = (lo+hi)/2;	/* Small arrays, middle element. */
if ( hi-lo > 7 ) {
	int p1=lo,pn=hi-1;
	if ( hi-lo > 40 ) {	/* Big arrays, pseudomedian of 9. */
		int s = (hi-lo)/8;
		p1 =  med3(p1,p1+s,p1+s+s);
		p =  med3(p-s,p,p+s);
		pn =  med3(pn-s-s,pn-s,pn);
	}
	p = med3(p1,p,pn);	/* Mid-size, median of 3. */
}

@ Partitioning the elements into three classes means more than just finding
which elements belong to which class---it also means moving the elements
so that the members of each class is contiguous.  In addition, we'll
move all the lesser elements to the front, the greater elements to the
back, and the equal elements to the middle.  
This problem is equivalent to Dijkstra's `Dutch National Flag' problem,
@^Dijkstra, Edsger W.@>
after the Dutch flag, which is three horizontal stripes of red, white, and
blue.  (See {\tt http://www.cesi.it/flags/nl.html} for a rendition
of the Dutch National Flag.)

The invariant maintained is: equal, lesser, unknown, greater, equal.
The boundary indices are |lo|, |a|, |b|, |c|, |d|, and |hi-1|.

We're also careful to find the ranges over each set of elements.

@d swapint(J,K)@+ {@+ int t=J;@+ J=K;@+ K=t;@+ }
		/* Assumes |t| is not free in |J| or |K| */

@<Partition around |perm[p]|@>= 
@<Initialize bounds@>@;
a=b=lo; c=d=hi-1; 
{double v = val(p), diff; 
node->f.i.cutdimen = cutdimen;  
node->f.i.cutvalue = v;
for(;;) {
	while( b<=c && (diff=val(b)-v)<=0.0 ) {
		if ( diff==0.0 ) {
			@<Update bounds for equal elements at |b|@>@;
			swapint(perm[a],perm[b]);
			a++;
		} @+ else @+ {@+  
			@<Update bounds for lesser elements@>@+
		}
		b++;
	}
	while( c>=b && (diff=val(c)-v)>=0.0 ) {
		if ( diff==0.0 ) {
			@<Update bounds for equal elements at |c|@>@;
			swapint(perm[d],perm[c]);
			d--;
		} @+ else @+ {@+  
			@<Update bounds for greater elements@>@+
		}
		c--;
	}
	if ( b>c ) break;
	swapint(perm[b],perm[c]);
	@<Update bounds for lesser elements@>@;
	@<Update bounds for greater elements@>@;
	b++; c--;
}
@<Move equals to middle@>@;
}
@<Paranoid: check the partitioning@>@;

@
@<Initialize bounds@>=
exl=lxl=gxl=xmax;	
exh=lxh=gxh=xmin;	
eyl=lyl=gyl=ymax;	
eyh=lyh=gyh=ymin;	

@
@d min(x,y) ((x)<(y)?(x):(y))
@d max(x,y) ((x)>(y)?(x):(y))
@<Update bounds for equal elements at |b|@>=
			exl = min(exl,valx(b));
			exh = max(exh,valx(b));
			eyl = min(eyl,valy(b));
			eyh = max(eyh,valy(b));

@
			@<Update bounds for lesser elements@>=
			lxl = min(lxl,valx(b));
			lxh = max(lxh,valx(b));
			lyl = min(lyl,valy(b));
			lyh = max(lyh,valy(b));

@
			@<Update bounds for equal elements at |c|@>=
			exl = min(exl,valx(c));
			exh = max(exh,valx(c));
			eyl = min(eyl,valy(c));
			eyh = max(eyh,valy(c));

@
			@<Update bounds for greater elements@>=
			gxl = min(gxl,valx(c));
			gxh = max(gxh,valx(c));
			gyl = min(gyl,valy(c));
			gyh = max(gyh,valy(c));

@
@<Move equals to middle@>=
{
int s,l,h;
s=min(a-lo,b-a);	/* Move first set of equals to middle. */
for(l=lo,h=b-s;s;s--) {swapint(perm[l],perm[h]);@+l++;h++;}
s=min(d-c,hi-1-d);	/* Move last set of equals to middle. */
for(l=b,h=hi-s;s;s--) {swapint(perm[l],perm[h]);@+l++;h++;}
}

@ Now that the elements are partitioned, we recurse to build the subtrees.

It is possible to pick a sequence of bad pivots, causing many of the
segments to be large.  This would not only slow things down, but it would
also force us to use a lot of stack space.  

There are two ways to get around this.
First, one might always choose a pivot that guarantees a good partition,
for example the median; medians can be found in linear time (INSERT REFERENCE).
Second, one might always process the smaller segments first and
use tail recursion to process the remaining largest segment.  This guarantees
that at most $\log_2 n$ activation records are present on the stack
@^tail recusion@>
@^stack overflow@>
at any one time.

However, until this problem shows up,  
I will use the simplest solution: blind recursion.
Note that Quicksort itself runs in $O(n\log n)$ time on average.
For example, see C.~A.~R.~Hoare's INSERT REFERENCE, or Robert Sedgewick's
PhD thesis (INSERT REFERENCE), or the perhaps more readily available
Knuth (INSERT REFERENCE), section ??.
@^Hoare, Charles Anthony Richard@>
@^Knuth, Donald Ervin@>
@^Sedgewick, Robert@>

%%%
%%%A common trick in Quicksort implementations is to recurse on the 
%%%smaller-size array segment first.  This leaves the larger segment waiting
%%%in the activation record on the stack.   When the smaller segment is done,
%%%then we sort the larger segment.
%%%This strategy ensures that
%%%there are at most $\log_2 n$ activation records on the stack, protecting
%%%us from stack overflow.
%%%@^stack overflow@>
%%%
%%%Interestingly, many people know this trick, but a significant fraction
%%%of them get it backwards: they recurse on the {\it larger\/} segment
%%%first.  Knuth (CHECK THIS) comments on this phenomenon, and wags his finger
%%%@^Knuth, Donald Ervin@>
%%%appropriately.
%%%
%%%Here, we have three segments on which we recurse.  A moment's thought tells
%%%us 
%%%to recurse on the smallest first, the next smallest second, and the largest
%%%last.  This still guarantees that there are at most $\log_{2} n$ activation
%%%records on the stack: because the smallest segment is at most one third
%%%of the remaining elements, and the middle segment is at most half the
%%%remaining elements.
%%%
%%%We only need the largest segment last in order to guarantee this logarithmic
%%%bound.  Arranging to meet  
%%%this simpler condition isn't much less work: one fewer
%%%integer comparison in the worst case.
%%%I didn't realize this until after I coded the following, which arranges
%%%the
%%%stronger small-medium-large order, so I left it in.
%%%
%%%

@<Build the subtrees@>=
#if defined(KD_BUILD_SMALLEST_SEGMENT_FIRST)
{ int l = b-a, m = hi-(d-c)-lo+b-a, h = d-c;
if ( l <= m ) {
	if ( m <= h ) { @<Build $<$ tree@> @+ @<Build $=$ tree@> @+ 
		@<Build $>$ tree@> }
	else if ( l <= h ) { @<Build $<$ tree@> @+ @<Build $>$ tree@> @+ @<Build $=$ tree@> }
	else { @<Build $>$ tree@> @+ @<Build $<$ tree@> @+ @<Build $=$ tree@> }
} else {
	if ( l <= h ) { @<Build $=$ tree@> @+ @<Build $<$ tree@> @+ @<Build $>$ tree@> }
	else if ( m <= h ) { @<Build $=$ tree@> @+ @<Build $>$ tree@> @+ @<Build $<$ tree@> }
	else { @<Build $>$ tree@> @+ @<Build $=$ tree@> @+ @<Build $<$ tree@> }
}
}
#else
@<Build $<$ tree@>@;
@<Build $=$ tree@>@;
@<Build $>$ tree@>@;
#endif

@ To build the subtree for the smaller elements, we call ourselves 
recursively.  We  pass this node as the parent; we propagate the information
on which dimensions have been flattened, and what level the subtree is at; 
we also pass the array bounds for the segment and the spatial 
bounding box of those
points.

@<Build $<$ tree@>=
node->f.i.lo_child =
	E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

@ @<Build $>$ tree@>=
node->f.i.hi_child =
	E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

@ When we recurse on the equal elements, we additionally 
tell the new invocation
that this dimension has already been flattened.
For $k\in\{0,1\}$, $2^k=k+1$, so we use |cutdimen+1| in place of an 
exponentiation.

@<Build $=$ tree@>=
node->f.i.eq_child = 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


@*Hiding and unhiding.
Part of the meaning of a semidynamic point set is that we may hide and unhide
points at will.  
A point becomes invisible to queries when it is hidden.  It becomes
visible again when it is unhidden.

First we will describe how to hide and unhide single points.
Later we will show how to hide and unhide all the points at once.

@ Inside a bucket, we hide a node by moving it to the end of the bucket, and
decrement the |hi| index.  To recover all the points in a bucket, we
also store a |hi_all| index, which is the value of |hi| when all
the points are visible.

@<Other external node fields@>=
int hi_all;

@  We need to initialize this field during tree creation.
@<Fill other bucket fields@>=
node->f.e.hi_all = hi;

@ In addition to moving the point to the end of its bucket, we need to
ensure the |hidden| fields of our ancestors are properly set.

@<Subroutines@>=
void
E2_hide(int c) {
	int ci;
	E2_node_t *node;
	errorif (c<0 || c>=n,"Invalid city %d to hide",c);
	node = E2_point_to_bucket[c];
	@<Make |perm[ci]==c|@>@;
	@<Hide |ci|@>@;
	@<If necessary, hide |node|'s ancestors@>@;
}


@ Before we can hide city |c|, we must find it in its bucket.  

One option is to maintain an inverse of |perm|.  However, this takes
up linear extra space, and is a hassle to maintain.

The option I've chosen here is to perform a sequential search through the
bucket.  For most buckets this is  fast because, on average, this takes about
|kd_bucket_cutoff/2| steps.  With the default of 5 for |kd_bucket_cutoff|,
this is 2.5 steps.  That's small.  

I said `most buckets' because there is a fly in the ointment.  In fact,
this is the same fly and the same ointment that I mentioned earlier. 
When there are
many points with exactly the same coordinate, then the bucket storing
those points will be rather large.  Again, degenerate inputs lead to
@^degenerate inputs@>
bad running times.  
I've decided to risk this tradeoff because I expect
these inputs to be very rare.
@^tradeoffs@>


@<Make |perm[ci]==c|@>=
{ int hi_all = node->f.e.hi_all;
	for ( ci=node->f.e.lo;ci<hi_all; ci++ ) {
		if ( perm[ci]==c ) break;
	}
	errorif(ci==hi_all,"Point %d not found in its bucket",c);
}

@ For correctness' sake, we must check to see whether the city is already
hidden.   (If the city is already  hidden, then |hi| should not be
decremented.)

Should we complain publicly if the city is already hidden?  
@^public complaining@>
As a matter of defensive programming, the answer---currently---is yes.
The algorithms that use this module shouldn't try to hide a hidden city.
Complaining about it here would probably help me track down a bug.
However, if this code is used in other contexts, then we may want
to eliminate this public complaining.

@<Hide |ci|@>=
{ int t, hi = node->f.e.hi;
if ( ci < hi ) { 
	hi=--node->f.e.hi;
	t=perm[ci];@+perm[ci]=perm[hi];@+perm[hi]=t;
} else {
	fprintf(stderr,"Hiding hidden city %d at perm[%d]\n",c,ci);
}
}
	
@ We've used |fprintf|, and so we need the interface to the standard
I/O library. % While we're at it,
@<System headers@>=
#include <stdio.h>

@ The next task is to set the |hidden| fields in our ancestors properly.
In particular, each node is an ancestor of itself.  
This simplifies the code nicely.

We stop climbing on one of three conditions: when we run 
off the top of the tree, when we hit an ancestor 
that is already hidden, or when not all the nodes in the subtree rooted
at that node are hidden.
To simplify the loop test, we put it at the end of the loop, so it 
only applies to internal nodes.
Remember that each internal node is ternary:
none of its three children are null pointers, |NULL|, though they may be empty.


@<If necessary, hide |node|'s ancestors@>=
#if !defined(KD_NO_HIDDEN_BIT)
if ( node->f.e.lo == node->f.e.hi && !node->hidden ) {
	do {
		node->hidden = 1; 
/* |printf("h");| */
		node=node->parent;
	} while ( node 
			&& !node->hidden 
			&& node->f.i.lo_child->hidden 
			&& node->f.i.eq_child->hidden 
			&& node->f.i.hi_child->hidden );
}
#endif

@ The code for hiding a city is now complete.  It's now time
to turn our attention to unhiding a city.

Luckily for us, we get to reuse some of the code we've just seen, namely
the code that finds $\hbox{|perm|}^{-1}(c)$.  The other sections are easy.

@<Subroutines@>=
void
E2_unhide(int c) {
	int ci;
	E2_node_t *node = E2_point_to_bucket[c];
	@<Make |perm[ci]==c|@>@;
	@<Unhide |ci|@>@;
	@<Unhide |node| and its ancestors@>@;
}


@ As with hiding, we must first check to see if the city is already unhidden.
We complain publicly if this is the case.
@^public complaining@>


@<Unhide |ci|@>=
{ int t, hi = node->f.e.hi;
if ( ci >= hi ) { 
	t=perm[ci];@+perm[ci]=perm[hi];@+perm[hi]=t;
	node->f.e.hi++;
} else {
	fprintf(stderr,"Unhiding unhidden city %d at perm[%d]\n",c,ci);
}
}
	



@
Unhiding ancestors is analogous hiding ancestors, but simpler.
We climb up the tree, setting |hidden| fields to false, and stop when
we either run off the top or reach an ancestor that is already unhidden.

@<Unhide |node| and its ancestors@>=
#if !defined(KD_NO_HIDDEN_BIT)
while ( node && node->hidden ) {
	node->hidden = 0;
	node=node->parent;
}
#endif

@ Now we are ready to see how to hide and unhide all the points in the set.
One option is to call the individual operation on every point in the set.
This works, but has a high overhead.  We can reduce the overhead by 
specially coding
these bulk operations. This is the course I've chosen.

@ We'll start with hiding.  We use a recursive routine to unhide all
the subtrees.  We use a helper routine that hides an entire subtree.

@<Subroutines@>=
void 
E2_hide_all(void) {
#if !defined(KD_NO_HIDDEN_BIT)
	if ( E2_root && !E2_root->hidden ) E2_hide_all_helper(E2_root);
#else
	if ( E2_root ) E2_hide_all_helper(E2_root);
#endif
}

@ The recursive routine sets the |hidden| field, and then splits
into two cases.
Inside a bucket, it moves the live-range index |hi| down to |lo|.
At an internal node, it calls itself recursively.

One might worry about overflowing the runtime stack.  
With a bit of care, we'll only
overflow the stack here if we've already overflowed it in building the 
tree itself.  The `bit of care' is to process the largest segment last.
Unfortunately, we've lost that information, and it's not
easily recoverable. Yikes!  Oh well,
let's recurse blindly.
@^stack overflow@>

An extra optimization is to only recurse down subtrees which are
not currently hidden.

@<Module subroutines@>=
static void 
E2_hide_all_helper(E2_node_t *p) {
#if !defined(KD_NO_HIDDEN_BIT)
	p->hidden = 1;
#endif
	if ( p->is_bucket ) p->f.e.hi = p->f.e.lo;
	else { 
#if !defined(KD_NO_HIDDEN_BIT)
		if(!p->f.i.lo_child->hidden)E2_hide_all_helper(p->f.i.lo_child);
		if(!p->f.i.eq_child->hidden)E2_hide_all_helper(p->f.i.eq_child);
		if(!p->f.i.hi_child->hidden)E2_hide_all_helper(p->f.i.hi_child);
#else
		E2_hide_all_helper(p->f.i.lo_child);
		E2_hide_all_helper(p->f.i.eq_child);
		E2_hide_all_helper(p->f.i.hi_child);
#endif
	}
}

@ Unhiding is very similar to hiding.
The only subtlety is that we have no option but to always recurse:
there may be hidden cities in subtrees whose |hidden| bit is turned off.


@<Subroutines@>=
void 
E2_unhide_all(void) {
	if ( E2_root ) E2_unhide_all_helper(E2_root);
}

@ This time, a bucket's live-range index |hi| gets set to |hi_all|,
the value it has when all its points are unhidden.  At an internal node,
we have no option but to recurse into the children.

@<Module subroutines@>=
static void 
E2_unhide_all_helper(E2_node_t *p) {
	if ( p->is_bucket ) {
		p->f.e.hi = p->f.e.hi_all;
#if !defined(KD_NO_HIDDEN_BIT)
		p->hidden = p->f.e.lo >= p->f.e.hi;
#endif
	} else {
#if !defined(KD_NO_HIDDEN_BIT)
		p->hidden = 0;
#endif
		E2_unhide_all_helper(p->f.i.lo_child);
		E2_unhide_all_helper(p->f.i.eq_child);
		E2_unhide_all_helper(p->f.i.hi_child);
	}
}

@* Nearest neighbours.
Now that we've built the tree, we're ready to describe the first query:
nearest neighbour search.  Given a city $i$, we'd like to find an
unhidden city that is nearest to $i$, excluding $i$ of course.

We proceed in bottom-up fashion, searching from the bucket containing 
$i$ and upward through the ever-larger subtrees that contain that bucket.
The idea is that the nearest neighbour is likely to be found in a part
of the tree that is near $i$'s bucket.  
With a candidate $j$ in hand, we terminate the walk to the root once we can 
prove that the ball of radius $\cost(i,j)$ lies entirely within the current
subtree.  Here, of course, one can use whatever metric is in effect in
the current context to define ``ball''; we aren't restricted to the Euclidean
metric.

I should say up front that most of this code is taken almost verbatim from
Bentley's {\sl $K$-d Trees for Semidynamic Point Sets}, Sixth Annual 
@^Bentley, Jon Louis@>
ACM Symposium on Computational Geometry, Berkeley, CA, June 1990, pp.~187--197.

@ We also need quadrant-based nearest neighbour search. 
Most of the code is the same, so I've folded in the generalizations
required.

I borrow from and slightly extend ordinary mathematical
terminology: if city |i| lies
at $(x,y)$, then
quadrant 0 is point $(x,y)$;
quadrant 1 is all points $(x',y')$ with $x'>x$ and $y'\ge y$;
quadrant 2 is all points $(x',y')$ with $x'\le x$ and $y'>y$;
quadrant 3 is all points $(x',y')$ with $x'<x$ and $y'\le y$;
quadrant 4 is all points $(x',y')$ with $x'\ge x$ and $y'<y$.
This nomenclature is presented in module \module{NN}.

For the sake of generality, the core searching code will be able to handle
any combination of the five quadrants by using bit masks.
For exaple, to specify searching in quadrants 0, 1 and 4, a mask
of |0x13| will is used.

@<Module variables@>=
int quadrant_mask;


@ We use a recursive helper routine to check subtrees.  

To save time passing state around, we define some external state.
The city we're trying to find a neighbour for is |E2_nn_seed|;
the best city found so far is |E2_nn_incumbent|.
Because we're using the Euclidean metric, 
we can take Sproull's advice (see Bentley (INSERT REFERENCE)) and 
@^Bentley, Jon Louis@>
@^Sproull@>
compare squared distances instead of actual distances; this 
saves a square root operation each time we determine an edge cost.  The
squared distance to the incumbent is stored in |E2_nn_dist_sq|.
Occasionally, however, we test against a bounding box whose radius
is the actual distance between the seed and the best neighbour found
so far.  This distance is stored in |E2_nn_dist|.


We will often compute distances to the seed city, so it will also be 
convenient to remember its coordinates.  They are stored in |E2_nn_seed_x|
and |E2_nn_seed_y|.

@<Module variables@>=
static int E2_nn_seed, E2_nn_incumbent;
static double E2_nn_dist, E2_nn_dist_sq, E2_nn_seed_x, E2_nn_seed_y;

@  The recursive routine that checks subtrees is named |E2_rnn|.
It splits naturally into two cases: internal versus external nodes.

@<Module subroutines@>=
static void 
E2_rnn(E2_node_t *p) {
	if ( p->is_bucket ) {
		@<Search this bucket for a nearer neighbour@>@;
	} else {
		@<Search the children for a nearer neighbour@>@;
	}
}


@ Inside a bucket, we perform a sequential search.

@<Search this bucket for a nearer neighbour@>=
{ int i, hi=p->f.e.hi;
for ( i=p->f.e.lo ; i<hi ; i++ ) {
	int pi = perm[i];
	@<Update nearest neighbour if |pi| is nearer@>@;
}
}


@
I avoid rounding in the computation of the actual distance because
I want this code to be applicable to both |EUC_2D| and |CEIL_2D|
cost functions.  Rounding would have implications on the bounding
box test.   We should be careful in this respect, and not rounding
is a conservative choice: it doesn't needlessly throw bits away.
@^rounding@>

If you need further convincing, then observe that both the rounding  
and the ceiling functions are 
monotonic on the real line.  That is, for any real numbers
$\alpha$ and $\beta$,
$\alpha \le \beta$  % \Rightarrow 
implies both
$\lfloor \alpha + 0.5\rfloor
\le \lfloor \beta + 0.5\rfloor$ 
and
$\lceil \alpha \rceil \le
\lceil \beta \rceil$.

I may want to consider using the |hypot| standard math library function 
instead.

The bitmask table encodes the case analysis for determining in which
relative quadrant city |pi| lies.  This way we can precisely prune
points in unwanted relative quadrants.

@d my_sgn(X) ((X)<0?0:((X)>0?2:1)) 
		/* Answer 0 if negative, 1 if zero, and 2 if positive. */

@<Update nearest neighbour if |pi| is nearer@>=
{
	const double 
		diff_x = E2_nn_seed_x-coord[pi].x[0], 
		diff_y = E2_nn_seed_y-coord[pi].x[1];
	const int qmask[3][3]={{0x02,0x02,0x10},{0x04,0x01,0x10},{0x04,0x08,0x08}};
	if ( quadrant_mask & qmask[my_sgn(diff_x)][my_sgn(diff_y)] ) {
		/* City |pi| is in a quadrant we are searching. */
		const double dist_sq = diff_x*diff_x + diff_y*diff_y;
		@<Verbose: |nn| show city being compared@>@;
		if ( dist_sq < E2_nn_dist_sq ) {
			@<Verbose: |nn| new incumbent@>@;
			E2_nn_dist = sqrt(dist_sq);
			E2_nn_dist_sq = dist_sq;
			E2_nn_incumbent = pi;
		}
	}
}

@ We need the interface to |sqrt|.
@<System headers@>=
#include <math.h>


@  As usual, the recursive case is more interesting.  A naive implementation
would just call itself recursively on each of its three children.

However, we use a simple distance criterion to prune the search.
We avoid examining a branch if that branch is on the opposite side of the
cut plane from the seed city and the distance from the seed city to
the cut plane is greater than the distance from the seed city
to the incumbent city.  
%(We use squared distances, as mentioned earlier.)  
This tactic 
works whenever the
metric being used dominates the $L_\infty$ metric, which is the case
for all $L_p$ metrics ($p\ge 1$), and the Euclidean ($L_2$) metric in 
particular.  Note that the |CEIL_2D| metric dominates the Euclidean metric,
and therefore it also dominates the $L_\infty$ metric.

A clever thing that Bentley does is to first search the branch
that is on the same side of
@^Bentley, Jon Louis@>
the cut plane as the seed city.  The idea is that a nearest neighbour is
more likely to be found on the same side as opposed to the opposite side.
In this way we hope to find a strong pruning distance more quickly.
In our case we have separated the cities into three classes instead of
only two, so
we extend this heuristic 
slightly by searching the cut plane itself before the far
side of the cut plane.

When the seed city lies in the cut plane, we search the cut plane first,
and the other branches in some arbitrary order.

@ One might worry about stack overflow in the case that the tree is rather
degenerate.  
@^stack overflow@>
We can avoid it by transforming the recursion into an iteration, but
this either means maintaining our own stack, or more cleverly,
using pointer reversal. 
(Pointer reversal was introduced by H.~Schorr and W.~Waite in their 
@^{Schorr, H{.}}@>
@^{Waite, W{.}}@>
1967 paper ``An efficient machine independent procedure for garbage 
collection'', {\sl Communications of the ACM}, 1967, 
Vol.~10, No.~8, pp.~501--506.  
The technique is useful for more than just garbage collection;
it is also used in graph-reduction model of evaluating functional programs.
For example, see \S11.6.1 in 
{\sl
Implementing Functional
Languages}, edited by Simon L.~Peyton Jones (COMPLETE REFERENCE).)
@^Peyton Jones, Simon L{.}@>
However, both these measures appear a bit drastic for now.  So I'll make the 
code just blindly recurse.

@ When I first coded this section, I forgot to test the hidden bit of the
node we were going to recurse into:  there is no point in recursing into
subtrees that only have hidden cities.
Yet, the times to build a 20 nearest neighbour
structure will still very reasonable, about 15 seconds on {\tt brd14051}
on a 125MHz IBM RS/6000.
@^RS/6000@>
@^brd14051@>

I began to wonder how effective this extra test really is at pruning the 
search.  Does it succeed often enough to warrant checking that byte every
time?  So I performed the following experiment.  

One of the stress tests I've used to discover bugs in my $k$-d tree 
implementation is to compute successive nearest neighbours for each city.
That is, for each city $i$, I had the program compute $i$'s nearest
neighbour, hide that neighbour, and repeat until all the cities were hidden.
The program checked that the distances were non-decreasing.  This is a
significant amount of work, taking time at least quadratic in the number
of cities.

The following table records the number of user seconds required 
by the RS/6000 machine
to both build the $k$-d tree
and perform this computation on various instances.  Three variations
were performed.  The first variation tests the hidden bit before every
recursive call of |E2_rnn_helper|.  The second variation avoids this test,
but still tests the hidden bit on every call to |E2_rnn|.
The last avoids storing the hidden bit at all, and therefore saves on
bookkeeping costs related to the hidden bit, but might unnecessarily
visit extra nodes.

\noindent\hfill\halign{{\tt #\hfil}&\hfil#&\hfil#&\hfil#\cr
&\omit\quad Always test\quad\hfil&\omit\quad Sometimes test\quad\hfil&\quad 
No hidden bit\hfil\quad\cr
\omit\hfil\quad Instance\quad\hfil&\omit\hfil hidden bit\hfil&\omit\hfil 
hidden bit\hfil&\quad\hfil used or stored\hfil\quad\cr
lin105 & 0.3 	&  0.4 &  0.5 \cr
lin318 & 8.3 	& 13.2 & 15.0 \cr
dsj1000 & 317.2 &728.3 &845.8 \cr
}\hfill\hbox{}\penalty-10000
%Experiments July 26, 1996

These results show that the using the hidden bit to its fullest is the
right thing to do,
resulting in up to 100\% better performance than using it only
some of the time, and up to 265\% better performance than not using it
at all.

@ There is one last detail.  
We also use quadrant masks to avoid recursive calls when possible.
That's the source of the expressions with |quadrant_mask|
involving the magic numbers |0x12|, |0x06|, |0x0c|, and |0x18|.
Do the case analysis with a bunch of pictures and you'll see why those
values are right.

@<Search the children for a nearer neighbour@>=
#if !defined(KD_NO_HIDDEN_BIT) && !defined(KD_NO_HIDDEN_RNN_TEST)
#define recurse_if_not_hidden(P) ((P)->hidden || (E2_rnn(P),42))
#else
#define recurse_if_not_hidden(P) (E2_rnn(P),42)
#endif
{
const int cutdimen = p->f.i.cutdimen;
const double seed_coord = cutdimen==0 ? E2_nn_seed_x : E2_nn_seed_y,
diff = seed_coord - p->f.i.cutvalue;
if ( diff < 0 ) { /* |seed < cutvalue | */
	recurse_if_not_hidden(p->f.i.lo_child);
	if ( E2_nn_dist >= -diff && ((cutdimen ? 0x12 : 0x06) & quadrant_mask) ) {
		recurse_if_not_hidden(p->f.i.eq_child);
		recurse_if_not_hidden(p->f.i.hi_child);
	}
} else if ( diff > 0 ) { /* |seed > cutvalue | */
	recurse_if_not_hidden(p->f.i.hi_child);
	if ( E2_nn_dist >= diff && ((cutdimen ? 0x0c : 0x18) & quadrant_mask) ) {
		recurse_if_not_hidden(p->f.i.eq_child);
		recurse_if_not_hidden(p->f.i.lo_child);
	}
} else {
	recurse_if_not_hidden(p->f.i.eq_child);
	recurse_if_not_hidden(p->f.i.lo_child);
	recurse_if_not_hidden(p->f.i.hi_child);
}
}

@ Now that we've built the helper routine to search entire subtrees,
let's write the driver code itself.  Function |E2_nn(int c)| returns
an unhidden city that is nearest to |c|.  
If there are no unhidden neighbours, then it returns $-1$.

We look for a candidate first in |c|'s bucket, and then expand
the search to the subtrees rooted at ever-higher ancestors of that
bucket.  

But first we need to set up the required state for the recursive helper
routine.

Admittedly, the |do {...} while (0)| 
construction is awkward, but it lets us write
the `unfruitful' test code so that it may be reused.  This is the perfect
place for a forward |goto|.  Knuth (INSERT REFERENCE) once argued
@^Knuth, Donald Ervin@>
for the desirability of a well-placed |goto|; this was in response
to Edsger Dijkstra's famous and influential ``Goto considered harmful''
@^Dijkstra, Edsger W.@>
letter to the {\sl Communications of the ACM}.  Of course, all this
awkwardness would go away if we could program in continuation passing
style, as is common in, say, Scheme or \ML/.
@^continuation passing style@>
@^|goto|@>
@^Scheme@>
@^ML@>

@<Subroutines@>=
int E2_nn(int c) { return E2_nn_quadrant(c, 0x1f); }

int 
E2_nn_quadrant(int c, const int mask) 
{
	E2_node_t *node = E2_point_to_bucket[c];
	quadrant_mask = mask;
	E2_nn_seed = c;
	E2_nn_seed_x = coord[c].x[0];
	E2_nn_seed_y = coord[c].x[1];
	E2_nn_incumbent = -1;
	E2_nn_dist = E2_nn_dist_sq = E2_strict_upper_bound;
	@<Search bucket |node| for a nearer neighbour, excluding the seed@>@;
	do {
		@<|break| if further search would be unfruitful@>@;
		@<Search proper ancestors for nearer neighbours@>@;
	} while (0);
	return E2_nn_incumbent;
}


@ The variable |E2_strict_upper_bound| holds a number that is guaranteed
to be larger than the squared length of any edge.   
It is a kind of ``infinity''
@^infinity@>
and is computed as something larger than the square of the length of 
the diagonal of the 
bounding box of all the points.

To ensure strictness, I've both doubled and added one to the square of the
length of the diagonal.  If the diagonal is trivial, say 0 units long, then
adding 1 ensures strictness.  If the diagonal is very large, then just adding
1 alone might not ensure strictness because we only have limited precision:
the 1 might be less than the value of the least significant bit of the mantissa
of the squared length of the diagonal. Multiplying by 2 first gets us out
of that problem.  In very extreme cases, we might overflow the floating point
representation.

@<Build the tree@>=
{double xrange = tsp->xmax-tsp->xmin, yrange = tsp->ymax-tsp->ymin;
E2_strict_upper_bound = 2.0*(xrange*xrange+yrange*yrange)+1.0;
}

@ It is visible only within this module.
@<Module variables@>=
static double E2_strict_upper_bound;

@  In the bucket that contains the seed, we avoid returning the seed itself.
Otherwise, this code works the same as the bucket search we saw earlier.

@<Search bucket |node| for a nearer neighbour, excluding the seed@>=
{
	int i, hi=node->f.e.hi;
	for ( i=node->f.e.lo ; i<hi ; i++ ) {
		int pi = perm[i];
		if ( pi != E2_nn_seed ) {
			@<Update nearest neighbour if |pi| is nearer@>@;
		}
	}
}


@ We prune the search by stopping when we've already
looked at all parts of the tree that intersect a ball with radius
|E2_nn_dist|, centred at the seed city.  Because each partitioning cut
in the tree is along a plane perpendicular to one of the axes, we may
as well use just a bounding box instead.  

Recall that |CEIL_2D| dominates |EUC_2D|, so these tests are safe for
|CEIL_2D| as well.

In the bounding box comparisons, it might be wise to put in a safety factor
of $\varepsilon$, a small positive constant.

@<|break| if further search would be unfruitful@>=
{ E2_box_t *b = node->bbox;
if ( b
	&& (b->xmin <= E2_nn_seed_x-E2_nn_dist)
	&& (b->xmax >= E2_nn_seed_x+E2_nn_dist) @|
	&& (b->ymin <= E2_nn_seed_y-E2_nn_dist)
	&& (b->ymax >= E2_nn_seed_y+E2_nn_dist) ) {
		@<Verbose: |break| from further search@>@;
		break;
	}
}

@ We walk up the tree, exploring ever-larger regions of the tree.
We're careful to not search the same subtree twice:  we avoid calling
|E2_rnn| on |last|, the node we've just come from.  We also don't search
subtrees which contain only hidden points.

As with the bucket search, we search the child that is on the same
side of the cut plane first.

@<Search proper ancestors for nearer neighbours@>=

#if !defined(KD_NO_HIDDEN_BIT)
#define recurse_if_not_last_or_hidden(P) ((P)==last||(E2_rnn(P),42))
#else
#define recurse_if_not_last_or_hidden(P) ((P)==last||(P)->hidden||(E2_rnn(P),42))
#endif

{ E2_node_t *last;
for ( last = node, node=node->parent; node ; last = node, node=node->parent ) {
	E2_node_t *l=node->f.i.lo_child, *e=node->f.i.eq_child, *h=node->f.i.hi_child;
	if ( (node->f.i.cutdimen == 0 && E2_nn_seed_x < node->f.i.cutvalue)
		@| || (node->f.i.cutdimen == 1 && E2_nn_seed_y < node->f.i.cutvalue) ) {
		recurse_if_not_last_or_hidden(l);
		recurse_if_not_last_or_hidden(e);
		recurse_if_not_last_or_hidden(h);
	} else {
		recurse_if_not_last_or_hidden(h);
		recurse_if_not_last_or_hidden(e);
		recurse_if_not_last_or_hidden(l);
	}
	@<|break| if further search would be unfruitful@>@;
}
}
	
	
@*Fixed-radius nearest neighbours.
We've just seen how to search for nearest neighbours.  There we were concerned
with finding a {\it single\/}
unhidden city that is {\it nearest\/} to the seed city.
Fixed-radius nearest neighbour is different in that it is used 
to find {\it all\/}
cities within a {\it given\/} radius.  

@ Now, many cities might fit the bill.
In a language such as Haskell, \ML/, or Scheme, where it is convenient to 
@^Haskell@>
@^ML@>
@^Scheme@>
return arbitrarily sized bags of elements, we  might just return a list, 
and let the caller iterate through them.  However, \CEE/ encourages a 
different style: the procedure that finds the cities also 
iterates through them,
calling a given procedure on each one.  This explains the peculiar
type signature of the fixed radius nearest neighbour routine.

@ On the assumption that the given radius will be small, we mimic the
structure of the ordinary nearest neighbour search, except that we 
{\it don't\/}
update the distance.

As before, we'll use some global state instead of passing parameters around.
Variable |E2_frnn_dist_sq| is the square of the radius.

@<Subroutines@>=
void 
E2_frnn(int c, double rad, void (*proc)(int j)) {
	errorif(1,"Fixed radius nearest neighbour not implemented");
}

void E2_set_radius(int i, double r) {
	errorif(1,"Ball searching not implemented");
}

void E2_ball_search(int i, void (*proc)(int j)) {
	errorif(1,"Ball searching not implemented");
}


@*Paranoia.
@d verb(a) if ( verbose>=(a) )
@<Paranoid: check the partitioning@>=
#ifdef KD_CHECK_PARTITIONING
/* Check the invariant. */
{ int i; double v = node->f.i.cutvalue;
verb(1000)printf("\nDimension %d\n",cutdimen);
for (i=lo;i<hi;i++) {
	if ( i==lo ) verb(1000)printf("Checking lesser: %d %d\n",lo,lo+b-a);
	if ( i==lo+b-a ) verb(1000)printf("Checking equal: %d %d\n",lo+b-a,hi-(d-c));
	if ( i==hi-(d-c) ) verb(1000)printf("Checking greater: %d %d\n",hi-(d-c),hi);
	verb(1000)printf("%d (%.0f,%.0f)\t %.0f %.0f\n",i,valx(i),valy(i),val(i),v); fflush(stdout);
}
for (i=lo;i<lo+b-a;i++) {
	errorif(val(i)>=v,"Not lesser at %d",i);
}
for (i=lo+b-a;i<hi-(d-c);i++) {
	errorif(val(i)!=v,"Not equal at %d",i);
}
for (i=hi-(d-c);i<hi;i++) {
	errorif(val(i)<=v,"Not greater at %d",i);
}
}
#endif

@
@<Module headers@>=
#include "error.h"
#include "memory.h"

@ The following routine outputs PostScript commands to show the divisions
between buckets.

@<Subroutines@>=
extern tsp_instance_t *tsp_instance;

static void
E2_postscript_show_helper(FILE *ps_out, int level, E2_node_t *node, 
	double xmin, double xmax, double ymin, double ymax ) {
	if ( !node->is_bucket ) {
		double cv = node->f.i.cutvalue;
fprintf(ps_out,"%%cutdimen == %d\n",node->f.i.cutdimen);
		switch(node->f.i.cutdimen) {
		case 0:	/* $x$ dimension */
			fprintf(ps_out,"newpath %f x %f y moveto %f x %f y lineto stroke\n",
				cv,ymin, cv,ymax);
@<Debug: indent@> verb(1000)printf("= in x = %f\n",cv);
			E2_postscript_show_helper(ps_out,level+1,node->f.i.eq_child,cv,cv,ymin,ymax);
@<Debug: indent@> verb(1000)printf("< in x < %f\n",cv);
			E2_postscript_show_helper(ps_out,level+1,node->f.i.lo_child,xmin,cv,ymin,ymax);
@<Debug: indent@> verb(1000)printf("> in x > %f\n",cv);
			E2_postscript_show_helper(ps_out,level+1,node->f.i.hi_child,cv,xmax,ymin,ymax);
			break;
		case 1:
			fprintf(ps_out,"newpath %f x %f y moveto %f x %f y lineto stroke\n",
				xmin,cv, xmax,cv);
@<Debug: indent@> verb(1000)printf("= in y = %f\n",cv);
			E2_postscript_show_helper(ps_out,level+1,node->f.i.eq_child,xmin,xmax,cv,cv);
@<Debug: indent@> verb(1000)printf("< in y < %f\n",cv);
			E2_postscript_show_helper(ps_out,level+1,node->f.i.lo_child,xmin,xmax,ymin,cv);
@<Debug: indent@> verb(1000)printf("> in y > %f\n",cv);
			E2_postscript_show_helper(ps_out,level+1,node->f.i.hi_child,xmin,xmax,cv,ymax);
			break;
		}
	} else {
		int i;
		@<Debug: indent@> 
		for (i=node->f.e.lo;i<node->f.e.hi_all;i++) {
			verb(1000)printf("%d ",perm[i]);
		}
		verb(1000)printf("\n");
	}
}

void
E2_postscript_show(FILE*ps_out) {
#if defined(KD_SHOW_KDTREE)
	fprintf(ps_out,"gsave 0 setlinewidth\n");
	E2_postscript_show_helper(ps_out,0,E2_root,
		tsp_instance->xmin, tsp_instance->xmax,tsp_instance->ymin,tsp_instance->ymax);
	fprintf(ps_out,"grestore\n");
	fflush(ps_out);
	fprintf(stderr,"Printed stuff to ps_out\n");
#else
	return;
#endif
}

@
@<Exported subroutines@>=
void E2_postscript_show(FILE *);

@
@<Debug: indent@>=
verb(1000){ int i; for (i=0;i<level;i++) printf(" "); }

@
@<Paranoid: check bounds@>=
#ifdef KD_CHECK_BBOX
verb(1000)printf("lo %d hi %d\n",lo,hi);
if ( lo < hi )
{ double xl,xh,yl,yh; int i;
	xl = xmax; xh = xmin; yl=ymax;yh = ymin;
	for (i=lo;i<hi;i++ ) {
verb(1000)printf("xl %f i %d perm[i] %d %f %f xl\n",xl,i,perm[i], 
		coord[perm[i]].x[0], coord[perm[i]].x[1]);
		xl=min(xl,valx(i));
		yl=min(yl,valy(i));
		xh=max(xh,valx(i));
		yh=max(yh,valy(i));
	}
	errorif( xl != xmin, "xl %f!= xmin %f",xl,xmin);
	errorif( yl != ymin, "yl %f!= ymin %f",yl,ymin);
	errorif( xh != xmax, "xh %f!= xmax %f",xh,xmax);
	errorif( yh != ymax, "yh %f!= ymax %f",yh,ymax);
}
#endif

@
@<Module variables@>=
extern int verbose;

@
@<Verbose: |nn| show city being compared@>=
#if KD_ALLOW_VERBOSE
if ( verbose >= 2000 ) {
	printf("  city %5d (%7.0f,%7.0f) is dist %10.3f\n",
		pi,coord[pi].x[0], coord[pi].x[1], sqrt(dist_sq));
}
#endif


@
@<Verbose: |nn| new incumbent@>=
#if KD_ALLOW_VERBOSE
if ( verbose >= 1000 ) {
	printf("    new champion\n");
}
#endif

@
@<Verbose: |break| from further search@>=
#if KD_ALLOW_VERBOSE
if ( verbose >= 500 ) {
		printf("     rnn break: seed=(%0.0f,%0.0f) dist=%f\n",
			E2_nn_seed_x, E2_nn_seed_y, E2_nn_dist );
		printf("     seedbb=(%0.0f,%0.0f,%0.0f,%0.0f) bb=(%0.0f,%0.0f,%0.0f,%0.0f)\n",
			E2_nn_seed_x-E2_nn_dist,
			E2_nn_seed_y-E2_nn_dist,
			E2_nn_seed_x+E2_nn_dist,
			E2_nn_seed_y+E2_nn_dist,
			b->xmin,
			b->ymin,
			b->xmax,
			b->ymax);
}
#endif


@*Index.
