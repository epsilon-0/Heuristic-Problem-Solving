


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
$Log: nn.w,v $
Revision 1.129  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.128  1998/04/16 15:40:03  neto
Need to include dsort.h to get the select range prototype.

Revision 1.127  1998/04/11 14:34:09  neto
Duh.  select is a Unix system call.  Renamed my select to select\_range

Revision 1.126  1998/04/10 21:20:23  neto
Checked that this module is safe for use by TSPs with arbitrary cost
functions.  It is.
Also, made the non-Euclidean case more efficient by using the select
function from module DSORT.  That's a lazy sorting function that only
does enough to select the appropriate subrange.

Revision 1.125  1997/10/28  21:23:19  neto
It now runs ok with nn.  It was reallocating improperly and not
initializing work next

Revision 1.124  1997/10/28  20:41:08  neto
Now it compiles.
and links.

Revision 1.123  1997/10/28  20:27:50  neto
Removed FINISH signal to finish coding.
Removed old balanced quadrant material.
Added maintenance of nn max bound, that jbmr requires.

Revision 1.122  1997/10/25 17:43:34  neto
Done coding the quadrants.
Will remove old stuff.

Revision 1.121  1997/10/18 20:39:43  neto
Restructuring so that we really do use multiple criteria.
Also, change to a single list structure with variable sublists.

Revision 1.120  1997/10/18 17:26:28  neto
Added support for CEIL 2D.

Revision 1.119  1997/10/17  21:27:34  neto
Convert coord2d to x[0] and x[1].
Fixed an apparent initialization bug in quadrant search.

Revision 1.118  1997/09/27 18:06:21  neto
Fixed RCS log behaviour.

Revision 1.117  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.116  1997/05/16  21:16:24  neto
Got rid of an unused variable and scope.

Revision 1.115  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.114  1997/05/16  18:09:40  neto
Include <config.h> and lkconfig.h

Revision 1.113  1997/02/11  15:58:26  neto
Reduced the number of calls to malloc.  This is also a bit
smarter about compacting the memory used when list\_len < max\_bound.
Luk pointed out the problem with malloc to me.

Revision 1.112  1997/01/22  15:18:31  david
Simplified wording. Fixed a wordo.

Revision 1.111  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.110  96/12/02  15:31:37  neto
Add copyright notice.

Revision 1.109  1996/08/23  16:36:44  david
Changed "Module types" to "Module type definitions" for consistency
with other modules.

Revision 1.108  96/08/15  14:13:21  neto
Fixed usage to match prototype of sort()

Revision 1.107  96/08/15  13:32:02  neto
Must export nn\_build

Revision 1.106  96/08/14  13:36:08  neto
Use sort instead of qsort.

Revision 1.105  96/08/07  15:20:35  neto
Make qsort optionally perserve the order of equals

Revision 1.104  96/07/29  17:10:35  neto
Added an RCS id, and it compiles.

}

@*Nearest neighbour lists.
This module constructs the nearest neighbour lists that are used by
efficient implementations of the Lin-Kernighan algorithm.  
For a discussion of this feature, see the chapter by Johnson and McGeoch.
In the next few paragraphs I will describe the ideas contained in that
discussion.

The LK algorithm often looks for a nearest neighbour tour to switch an
edge to.  For efficiency's sake, it would like to examine the neighbours
of a given city in increasing distance order from that city.  The most
natural structure for this is an array of neighbours of that city,
sorted by distance.  Then the LK algorithm searches sequentially from
the beginning of the array looking for candidates.

@ The above scheme takes quadratic space, which is not practical for
very large instances.  So we compromise, storing only the first $k$
nearest neighbours.  Once the near neighbour search exhausts this
list, we just give up.   This also saves us time: we don't waste time
searching in unlikely places.

@ This truncated scheme works well on randomly distributed instances --- 
whether those with random edge lengths, or those which consist of
cities placed randomly in a Euclidean space.  However, on more structured
geometric instances, such as those taken from TSPLIB, we get better results
if we reflect some of that structure in the neighbour lists.

The main idea is to ensure that there is representation on this list
from the various regions that surround a particular city.  For example,
in a 2-D instance,
we might want to include the ten nearest neighbours from each of the
four surrounding quadrants.  This changes the makeup of the neighbour
list dramatically if the city is on the edge of a cluster.

This module supports both pure and region-oriented nearest neighbour lists
via parameters passed to the construction routine.

@ This module provides the following interface.

Procedures 
|nn_setup| and |nn_cleanup| are the usual intialization and shutdown routines.

Procedure |nn_build| builds the nearest neighbour arrays. 

Procedure |nn_list| returns the nearest neighbour list for a given 
city.

Global variable |nn_max_bound| is the length of the longest neighbour
list.

@ The outline of this module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Early module headers@>@;
@<Module headers@>@;

@<Global variables@>@;
@<Module type definitions@>@;
@<Module variables@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *nn_rcs_id="$Id: nn.w,v 1.129 1998/07/16 21:58:55 neto Exp neto $";

@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

@ The exported interface is contained in the \file{nn.h} header file,
which has the following form.

@(nn.h@>=
extern const char *nn_rcs_id;
@<Exported variables@>@;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "nn.h"

@ Variable |nn_max_bound| is an integer.
@<Global variables@>=
int nn_max_bound;

@
@<Exported variables@>=
extern int nn_max_bound;


@ When making up the nearest neighbour lists, this module needs to associate
a neighbouring city with the distance to that city.
We declare a local type for this purpose.

However, during actual use
we store only the neighbouring cities.  
This saves a lot on space.  For most 32-bit architectures, it saves 2/3 of
the space, because the city number is 4 bytes, and the length is 
usually 8 bytes.  In fact the nearest neighbour lists take up more
space than any other data structure in LK.

@<Module type definitions@>=
typedef struct {
	length_t len;
	int city;
} nn_entry_t;

@ We've used the |length_t| type which is defined in the \file{length.h}
module.

@<Early module headers@>=
#include "length.h"

@ Because there are multiple disjoint criteria for a city to belong
to a neighbour list, the lengths of the lists will vary.  
We save space by not having dummy entries.  

Variable |list|  is an array of integers into which all the lists
of neighbours are stored, one after another.  To mark the list boundaries,
we use array |begin|. 
In particular |begin[i]| is the index into |list|
at which the candidate list for city $i$ begins.  Array |begin| has |n+1|
entries: |begin[n]| points to just past the end of the list for the last 
city.  In other words, the candidate list for city |i| runs from
|list[begin[i]]| through |list[begin[i+1]-1]|, inclusive.

Without going farther, we can already code the |nn_list| function.

@<Subroutines@>=
int *
nn_list(int city, int *list_len)
{
	*list_len = begin[city+1]-begin[city];
	return list+begin[city];
}


@
@<Exported subroutines@>=
int *nn_list(int city, int *list_len);

@ We need to declare the |list| and |begin| arrays.  
It will be convenient to store |n|, the number of cities.

@<Module variables@>=
static int *list, *begin, n;

@ Array |begin| has |n+1| entries. We'll see later how to allocate
the |list| array.

@<Set up the array data structures@>=
begin = new_arr_of(int,n+1);
begin[0]=0;

@ We need the interface to the memory module.  
While we're at it, let's get the error module as well.

@<Module headers@>=
#include "error.h"
#include "memory.h"

@ These arrays should be deallocated when we clean up.
@<Subroutines@>=
void
nn_cleanup(void) {
	@<Clean up the array data structures@>@;
}

@
@<Clean up the array data structures@>=
if ( begin ) { free_mem(begin);mem_deduct(sizeof(int)*(n+1)); }

@ The cleanup procedure must be declared externally.
@<Exported subroutines@>=
void nn_cleanup(void);

@*Building the neighbour lists.
Procedure |nn_build| builds the nearest neighbour arrays.  

There is one parameter for each kind of neighbour we might be
asked to add: an unqualified (pure) near neighbour, a near neighbour
in a particular quadrant, or a city nearby in the Delauney triangulation.
The list of neighbours for each city $i$ should be:
the |num_pure| closest neighbours of $i$; 
the |num_quadrant| closest neighbours of $i$ in each of the four
surrounding quadrants; 
all cities that are at most |num_delauney| steps from $i$ 
in the Delauney triangulation of the instance.  
Of course, the same city may qualify under more than one of these criteria
for a given seed.  Such cities are included only once for that seed city,
\ie, duplicates are removed.

@d max(A,B) ((A)>(B) ? (A) : (B))

@<Subroutines@>=
void
nn_build(int num_pure, int num_quadrant, int num_delauney) 
{
	@<|nn_build| variables@>@;
	int i;
	n = tsp_instance->n;
	@<Check build parameters@>@;
	
	@<Set up the array data structures@>@;
	nn_max_bound = 0;
	for (i=0;i<n;i++) {
		@<|nn_build| iteration variables@>@;
		@<Verbose: about to start building list for |i|@>@;
		@<Build a pure work list for city |i|@>@;
		@<Build a quadrant work list for city |i|@>@;
		@<Build a Delauney work list for city |i|@>@;
		@<Compress the work lists and copy them into |list|@>@;
		nn_max_bound = max(nn_max_bound, begin[i+1]-begin[i]);
	}
	@<Clean up the temporary data structures@>@;
}

@ We export the building subroutine.
@<Exported subroutines@>=
void nn_build(int num_pure, int num_quadrant, int num_delauney);

@ We check for bad build parameters.  This helps us to spot bugs and 
to avoid misleading the user, \eg, if they specified 50 nearest neighbours
but only get 20 because there are only 21 cities.

@<Check build parameters@>=
@<Verbose: show build parameters@>@;
errorif(num_pure<0,
	"Need positive number of nearest neighbours; %d specified",num_pure);
errorif(num_quadrant<0,
	"Need positive number of quadrant neighbours; %d specified",num_quadrant);
errorif(num_delauney<0,
	"Need positive Delauney depth; %d specified",num_delauney);
errorif(num_pure<=0 && num_quadrant<=0 && num_delauney<=0,
	"Must specify some candidates");
errorif(num_pure>= n,
	"%d nearest neighbours specified, but there are only %d cities",num_pure,n);

@ We need to import the instance |tsp_instance| and its type.
@<Early module headers@>=
#include "read.h"
#include "lk.h"


@ We try to reduce the number of reallocations of 
|list| by guessing the average length of each city's neighbour list.
The following expressions are themselves just guesses.


@<Guess the average number of neighbours per city@>=
if ( num_pure )
	guess_avg = num_pure + num_quadrant + num_delauney;
else if ( num_quadrant )
	guess_avg = 4*num_quadrant + num_delauney;
else
	guess_avg = 3*num_delauney*num_delauney;

@ Once we have a guess at the average length of a list, we initially
allocate |n| times that number of entries for |list|.

@<Set up the array data structures@>=
{int guess_avg;
@<Guess the average number of neighbours per city@>@;
list_size = guess_avg * n;
list = new_arr_of(int,list_size);
}

@
@<Clean up the array data structures@>=
if ( list ) { free_mem(begin);mem_deduct(sizeof(int)*list_size); }

@ Variable |list_size| always contains the number of elements allocated
for |list|.

@<Module variables@>=
static int list_size;

@ We will need work space for each of the three passes through the data.
In the worst (and exceedingly rare) case, 
each city will appear three times in the work list.

@<Set up the array data structures@>=
work = new_arr_of(nn_entry_t,3*n);

@ We don't need the |work| array after we build the lists, so we clean it
up early.  
@<Clean up the temporary data structures@>=
free_mem(work);mem_deduct(sizeof(nn_entry_t)*3*n);

@ But we must declare the variable.
@<|nn_build| variables@>=
nn_entry_t *work;

@ The work list will be built by just appending.  Specifically, the 
working copy of the candidate list for a city is stored in  
|work[0]| through |work[work_next-1]|.  

We sort to find duplicates. After sorting, we don't ever use the
lengths again.

Module \module{LK} sets the |sort| function pointer to a suitable sorting
procedure, \eg, the \CEE/ library |qsort| function.

@<Compress the work lists and copy them into |list|@>=
errorif( work_next < 1, "Must have nonempty candidate list"); 
{
int r, w, last_city;
sort(work,(size_t)work_next,sizeof(nn_entry_t),cmp_entry_compress);
for ( r=w=0, last_city=work[r].city-1; r<work_next; r++ ) {
	if ( work[r].city != last_city )
		last_city = work[w++].city = work[r].city;
}
@<Make sure |list| has space for |w| more elements@>@;
for (r=0;r<w;r++) list[begin[i]+r] = work[r].city;
begin[i+1] = begin[i]+w;
}

@ We must declare |work_next|.
@<|nn_build| iteration variables@>=
int work_next=0;


@ We do have to provide a comparison function. 
We promise to the outside world to put nearer
cities first on lists, so that's the first criterion.
Second, we want duplicates to be brought together, so that's the second
criterion.

@<Module subroutines@>=
static int 
cmp_entry_compress(const void *a, const void *b) {
	const length_t ad = ((const nn_entry_t *)a)->len;
	const length_t bd = ((const nn_entry_t *)b)->len;
	if ( ad < bd ) return -1;
	else if ( ad > bd ) return 1;
	else return ((const nn_entry_t *)a)->city - ((const nn_entry_t *)b)->city;
}

@ We use repeated doubling to expand the |list| array to achieve a constant
amortized allocation time per cell.  

It's ok if we end up using horribly 
less than the total allocated space.  It would only end up wasting address
space, which we of course know is infinite.  
There is no performance penalty because we never access the memory we don't
use.  Duh.  Unused memory is never paged in.

@<Make sure |list| has space for |w| more elements@>=
if ( begin[i]+w > list_size ) {
	int new_size = list_size;
	while ( begin[i]+w > new_size ) new_size*=2;
	@<Verbose: resize |list|@>@;
	list = mem_realloc(list,sizeof(int)*new_size);
	list_size = new_size;
}

@*1 Pure lists.
Whenever possible, we use the $k$-d tree to speed things up.

Otherwise, we use a quick and dirty method to calculate
the nearest neighbour list.  For each city, compute the distances to all
the cities, sort, and then pick off the first few entries.
In the future we may want to do smart partitioning, like a truncated
Quicksort, perhaps with randomized pivot sampling.


@<Build a pure work list for city |i|@>=
if ( num_pure ) {
	int start_work = work_next;
	if (E2_supports(tsp_instance)) {
		@<Use the $k$-d tree to find nearest neighbours@>@;
	} else {
		@<Compute all the distances except from $i$@>@;
		@<Move the |num_pure| closest cities to the front@>@;
	}
}

@ The |E2| routines for 2-d trees are in the \module{KDTREE} module.
@<Early module headers@>=
#include "kdtree.h"

@ Let's do the fast way first,
using the $k$-d search structure implemented in \module{KDTREE}.
Here we only use the nearest neighbour search and the hiding and unhiding 
routines.  Given those calls, building the list is rather easy.

@<Use the $k$-d tree to find nearest neighbours@>=
{
	int j, city;
	for (j=0;j<num_pure;j++) {
		city = E2_nn(i);
		if ( city == -1 ) break; /* No such neighbour. */
		work[work_next].city = city;
		work[work_next].len = cost(i,city);
		work_next++;
		E2_hide(city);
	}
	for (j=start_work;j<work_next;j++) E2_unhide(work[j].city);
}

@ Now we're ready to do the brute force method. 
Computing all the distances is easy.

@<Compute all the distances except from $i$@>=
{ int j;
	for (j=0;j<i;j++) {
		work[start_work+j].city = j;
		work[start_work+j].len = cost(i,j);
	}
	for (j=i+1;j<n;j++) {
		work[start_work+j-1].city = j;
		work[start_work+j-1].len = cost(i,j);
	}
}


@  We use the handy-dandy partial sorting selection function |select_range| from
the \module{DSORT} module to
move the closest |num_pure| cities to the front of the array, and sort them
too.

Recall |num_pure <= n-1|, so we won't run off the end of what we've already
written.

@<Move the |num_pure| closest cities to the front@>=
select_range((void *)work,(size_t)n-1,sizeof(nn_entry_t),cmp_entry_compress,
	0,num_pure,0/*Don't sort them */);
work_next += num_pure;

@ 
@<Module headers@>=
#include "dsort.h"


@*1 Quadrant-balanced lists.
Quadrant balanced lists only make sense when the instance lives in a
coordinate system.  Since the only coordinate system we support is
2-dimensional real space, we just use the 2-d trees.  In fact, quadrant
lists may be used precisely when 2-d trees are supported.

@<Check build parameters@>=
errorif(num_quadrant>0 && !E2_supports(tsp_instance),
	"Quadrant lists supported only when 2-d trees supported",num_pure);

@ Quadrant lists are interesting for two reasons.

First, building them efficiently requires special support in the 2-d tree.
That is, we need to be able to find nearest neighbours while masking
out entire quadrants of space surrounding the seed city.

Second, although the user may ask for a certain number of cities from
each quadrant, there may not be that many available there.  In fact, this
is certain to be the case for cities at the ``corners'' of the instance.
The only consequence of running short is that the caller gets back a
shorter list.

@<Build a quadrant work list for city |i|@>=
if ( num_quadrant ) {
	int quadrant;
	@<Find all cities in quadrant 0@>@;
	for ( quadrant = 1; quadrant <= 4; quadrant++ ) {
		@<Find up to |num_quadrant| neighbours in quadrant |quadrant|@>@;
	}
}

@ 
I borrow from and slightly extend ordinary mathematical 
terminology: if city |i| lies
at $(x,y)$, then 
quadrant 0 is point $(x,y)$;
quadrant 1 is all points $(x',y')$ with $x'>x$ and $y'\ge y$;
quadrant 2 is all points $(x',y')$ with $x'\le x$ and $y'>y$;
quadrant 3 is all points $(x',y')$ with $x'<x$ and $y'\le y$;
quadrant 4 is all points $(x',y')$ with $x'\ge x$ and $y'<y$.

I've been careful to define the boudaries of quadrants 1 through 4
to be balanced: those quadrants are pairwise congruent to each other.

Since all five quadrants are disjoint, we don't need to worry about
duplicates.  So we write directly to the |work| array.

The quadrant parameter passed to the |E2_nn_quadrant| 
is a bit mask of all the quadrants in which to search.

@<Find up to |num_quadrant| neighbours in quadrant |quadrant|@>=
{ int j, start_work=work_next;
	for (j=0;j<num_quadrant;j++) {
		const int city = E2_nn_quadrant(i,1<<quadrant);
		if ( city == -1 ) break; /* No such neighbour. */
		work[work_next].city = city;
		work[work_next].len = cost(i,city);
		work_next++;
		E2_hide(city);
	}
	for (j=start_work;j<work_next;j++) E2_unhide(work[j].city);
}

@ 
Now, we would hope to
not have cities with duplicated coordinates.  But they might be there.
Let's get all of them, no matter what |num_quadrant| is.

We cheat a little by temporarily redefining the |num_quadrant| variable.

@<Find all cities in quadrant 0@>=
{ const int num_quadrant = n-1, quadrant=0;
@<Find up to |num_quadrant| neighbours in quadrant |quadrant|@>@;
}


@*2 Delauney lists.
We don't support Delauney lists.  Alas.  For further pointers, see
either Knuth's {\sl The Stanford Graphbase} or 
Preparata and Shamos' {\sl Computational Geometry}.

@
@<Check build parameters@>=
errorif(num_delauney,"Delauney neighbours not supported (yet)");

@
@<Build a Delauney work list for city |i|@>=

@*Verbose.

@<Verbose: resize |list|@>=
if ( verbose >= 750 ) {
	printf("nn: Resize list from %d elements to %d elements; begin[i]=%d, w=%d\n", 
		list_size, new_size, begin[i], w);
	fflush(stdout);
}

@
@<Verbose: show build parameters@>=
if ( verbose >= 500 ) {
printf("nn: build nn %d nq %d del %d\n", num_pure, num_quadrant, num_delauney);
	fflush(stdout);
}

@
@<Verbose: about to start building list for |i|@>=
if ( verbose >= 1250 ) {
	printf("nn: about to build for %d; work_next=%d list_size=%d\n", 
		i, work_next, list_size);
	fflush(stdout);
}

@*Index.

