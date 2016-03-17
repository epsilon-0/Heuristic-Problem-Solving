


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
$Log: tspgen.w,v $
Revision 1.27  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.26  1998/02/19 18:12:46  neto
Removed const from prototype to make it match with the functino definition.

Revision 1.25  1997/12/17 16:22:08  neto
Fix the very long usage printing lines so they typeset better.

Revision 1.24  1997/12/06 19:54:55  neto
Fixed POSIX SOURCE defintion thingie.  Also, fixincludes is definitely
in the same directory.

Revision 1.23  1997/12/06 15:46:38  neto
Fixed to compile on Linux (and hopefully still on Solaris). It seems *I*
have to declare optarg...

Revision 1.22  1997/12/01  15:33:57  neto
No wonder the program was ignoring its random number seed: it hadn't
been processing the command line until *after* the generators were
initialized!

Revision 1.21  1997/11/27  19:11:58  neto
Rail exp to 1 when necessary
Attempt at clean fix of getopt and friends config.

Revision 1.20  1997/11/20 19:22:40  neto
Better comments.  Also, I fixed the sense of t in mediating alpha and beta.
(Comments do wonders for correctness.)
Also, the usage message now describes -j briefly.

Revision 1.19  1997/11/20 18:16:31  neto
If join length bias is 1, then make sure we don't loop enlessly.
Alas, the curse of intervals closed on the right...
Also, don't rotate c unless it's the last component.

Revision 1.18  1997/11/20 16:52:43  neto
Better presentation: cleaned up verbose output in Graham scan, and
added options info to COMMENT field of the output.

Revision 1.17  1997/11/20 16:15:55  neto
Fixed an ooops.

Revision 1.16  1997/11/20 16:15:08  neto
Added hull join point length bias.  It compiles but is untested.

Revision 1.15  1997/11/20 14:28:09  neto
Added better option handling, including packing factor from the command linee,
and help.
The hull-vertex picking code and matching code is better checked.

Revision 1.14  1997/11/14  22:54:05  neto
I know why must sort edges smallest to largest: to preserve the MST lengths.
(e.g. (0,0) (5,0), (0,1) (5,1))
We use a prev bias to try to generate more compact clones.

Revision 1.13  1997/10/11 17:50:28  neto
It seems we must sort the lengths into ascending order. Why? I don't know.
Now default is debugging off.

Revision 1.12  1997/10/11 17:18:55  neto
Added more consistency checks.

Revision 1.11  1997/10/11 15:07:23  neto
This mostly works, but it gets a few edge lengths wrong.

Revision 1.10  1997/09/27 19:24:28  neto
Made the TSPLIB output more conformant.

Revision 1.9  1997/09/27 18:01:42  neto
Fixed Graham scan in case of merging two singletons.

Revision 1.8  1997/09/27 17:29:26  neto
Finished coding. It now compiles and links.

Revision 1.7  1997/09/25  20:35:16  neto
Implemented Graham Scan, but need to implement left turn test.

Revision 1.6  1997/09/22  20:34:19  neto
Added sorting of convex hull points.
About to do Graham Scan.

Revision 1.5  1997/08/22  21:55:35  neto
A tiny bit more coding, and style improvement.

Revision 1.4  1997/08/22  21:51:26  neto
Fixed a section naming typo.

Revision 1.3  1997/08/22  21:50:31  neto
Now coding the convex hull algorithm.

Revision 1.2  1997/08/22  15:56:50  neto
Upon code review, fixed choosing of random components.
Made style more CWEB-like.
Changed name of geo transform to rigid motion.
About to tackle joining components.

Revision 1.1  1997/08/21  20:36:15  neto
Initial revision

}

\def\Rotate{\hbox{Rotate}}
\def\Translate{\hbox{Translate}}

@s theta TeX   
@s alpha TeX   
@s beta TeX   
@s pi TeX

@*TSPGEN.
This program generates a TSP instances.  The input is $n$ followed by
$n$ positive numbers interpreted as lengths.  
The generated instance has a
minimum spanning tree (MST) whose set of edge lengths is the same as the input
set of lengths.

@ I have a hunch that the set of TSP instances generated in this way from the
same input data are reasonable clones of each other in the eyes of 
the Lin-Kernighan heuristic.  That is, Lin-Kernighan has consistent execution
behaviour over such clones.

Furthermore, I have a hunch that projecting a given TSP instance down
to its set of MST edge lengths and then generating 
new TSP instances from that
set is a reasonable way to generate clones of the original instance.

@ Michael Hutton's PhD thesis, 
\book{Characterization and Parameterized Generation of
$\ldots$}(FIX THIS REFERENCE), 1997, describes this paradigm of characterizing
and cloning data, but in the context of logic circuits and VLSI design.

@ The outline of this program is as follows.
@c

const char *prog_name = "tspgen";
const char *tspgen_rcs_id = "$Id: tspgen.w,v 1.27 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
@<System headers@>@;
@<Module headers@>@;
@<Early type definitions@>@;
@<Type definitions@>@;

#if !defined(DEBUG)
#define DEBUG 0
#endif

@<Module variables@>@;
@<Module subroutines@>@;


int main(int argc, char **argv) 
{
	@<|main| variables@>@;
	@<Process the command line@>@;
	@<Initialize the random number generators@>@;
	@<Read the edge lengths@>@;
	@<Sort the lengths into ascending order@>@;
	@<Allocate and initialize the data structures@>@;
	@<Generate a clone@>@;
	@<Print the clone@>@;
	@<Clean up the data structures@>@;
	return 0;
}

@ There are a few command line parameters.  

Option \type{-h} provides help, then exits successfully.

Option \type{-s} takes a mandatory integer paramter used as the random
number seed.  Actually, we use three independent random number streams, 
but each is initialized with a seed generated deterministically from the
command-line specified seed.  The default seed is, of course, $-42$.

Option \type{-j} takes a floating point parameter used as the 
\term{join length bias}.  When gluing components together, we can join
them at whatever hull points we like.  If the join length bias is negative,
then we join them at a randomly chosen hull point.  
However, experiments show that this leads to very sparse fractal-like
structures.   
(I'm out of practice at this, but my eyeball estimate is that the Hausdorff
dimension is quite low: about 1.05.)  
If we always join hulls at a point adjoining the longest edge on the hull,
then the resulting instance has a much tighter structure.  
We'd like some flexibility on this choice, and the join length bias gives
us that flexibility.  If the bias is negative, then each hull join point is
chosen randomly.  Otherwise, the bias should be between 0 and 1,
representing a fraction used to choose from a sorted list of the hull edge
lengths: a bias of 0 means always pick the shortest edge on each hull,
a bias of 1 means always pick the longest edge.  
The default bias is 1, so that the default is to
try to create the tightest instance possible.
This parameter is used
in conjunction with the packing factor.

Option \type{-p} takes a floating point parameter used as the 
\term{packing factor}.  Once each hull point and its associated edge of
interest is chosen, we can choose from a range of angles at which to 
rotate the component before joining.  This has some effect over how
tightly the points in the instance are packed.  The packing factor must
be non-negative.  Smaller factors bias the angles toward looser packing,
and higher factors bias the angles toward tighter packing.

@<Process the command line@>=
seed = -42L;
packing_factor = 100; /* Something large, for tightest packing. */
join_length_bias = 1; /* By default, join at largest edge in hull. */
while(1) {
	extern char *optarg; /* Defined by the \CEE/ library. */
	const int opt = getopt(argc,argv,"s:p:j:h");
	if (opt==EOF) break;
	switch(opt) {
	case 's': seed = atol(optarg); break;
	case 'p': 
		packing_factor = atof(optarg);
		errorif(packing_factor<0,
		"Packing factor should be non-negative, but given %f",packing_factor);
		break;
	case 'j': 
		join_length_bias = atof(optarg);
		errorif(join_length_bias>1,
		"Join length bias should be no more than 1, but given %f",
			join_length_bias);
		break;
	case 'h': usage(argv); exit(0); break;
	case ':': errorif(1,"some option is missing an argument"); break;
	case '?': usage(argv); errorif(1,"Unrecognized option"); break;
	default: errorif(1,"getopt returned character 0%o",opt);
	}
}

@
|VERSION_STRING| is defined in file \file{<config.h>} but is set in
\file{configure.in}.

@<Module subroutines@>=
void usage(char **argv);
void 
usage(char **argv)
{
printf("%s (LK %s)\n", prog_name, VERSION_STRING);
printf(
"Generate TSPLIB instances from minimum spanning tree edge lengths\n"@;
"\nCopyright (C) 1997 David M. Neto\n");@;
printf(
"LK comes with NO WARRANTY, to the extent permitted by law.\n");@;
printf(
"You may redistribute and/or modify copies of LK under the terms of the\n"@;
"GNU General Public License, version 2 or any later version.\n"@;
"For more information about these matters, see the file named COPYING.\n");@;
printf(
"\n"@|
"Usage: %s [options]\n"@|
" -h                      : Output this help and quit\n"@|
" -j <join-length-bias>   : Bias choice of hull point based on associated\n"@|
"                           hull edge length.\n"@|
"                             negative means random vertex\n"@|
"                             0 to 1: use this as a fractional ordinal in\n"@|
"                               sorted hull edge lengths (read the source!)\n"@|
" -p <packing-factor>     : Non-negative <packing-factor> is a hint on how\n"@|
"                           tight to try to make the instance:\n"@|
"                             0 means try hard to stretch it loose,\n"@|
"                             large values means try to pack it tight\n"@|
" -s <seed>               : Use integer <seed> as the random number seed\n",@|
argv[0]);
}

@ We've used the nearly-universal |getopt| function for processing
command line options.  It is usually in \file{unistd.h}.  If
it isn't, then we get it from \file{fixincludes.h}.

@<System headers@>=
#define _POSIX_C_SOURCE 2   /* GNU headers need this to define a |getopt| prototype. */
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

@
@<Module headers@>=
#define FIXINCLUDES_NEED_GETOPT
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_GETOPT

@  The two parameters are a random number seed and a packing factor.

The packing factor can be any non-negative number.  
Large packing factors
make this program try to pack the TSPLIB instances into as small a
space as is practical, and factors near zero make it try to stretch the
instance out.
Actually, $L_p$ metrics come into play, another reason
for using the letter `p'.
@<Module variables@>=
long seed;
double packing_factor, join_length_bias;

@  The input is a number |ne| followed by |ne| floating point numbers, each
taken to be an edge length.  Each length should be positive.
The name $n$ is reserved for the number of vertices; $n = ne + 1$.

We read the lengths into array |length|. The array is allocated after 
|ne| has been read.

@<Read the edge lengths@>=
@<Clear |errno|@>@;
{int num_read, i;
num_read=scanf(" %d ", &ne);
errorif( num_read != 1, "Couldn't read ne, the number of edge lengths.");
errorif( ne < 1, "ne, the number of edge lengths, is %d but must be positive.",ne);
n = ne + 1; /* Variables |n| and |ne| never change after this. */
length = new_arr_of(double,ne);
for (i=0;i<ne;i++) {
	num_read=scanf(" %lf ", length+i);
	errorif(num_read!=1,"Couldn't read length %d.",i);
	errorif(length[i] <= 0,"Length %d should be positive, but is %f.",i,length[i]); 
		/* Use machine epsilon instead? */
}
}
@<Clear |errno|@>@;


@
@<Clean up the data structures@>=
free_mem(length);

@  
@<Module variables@>=
int ne, n;
double *length=NULL;

@ We need the definitions of |NULL| and other standard things.
@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



@ We also need error handling and memory allocation routines.
@<Module headers@>= 
#include "error.h"
#include "memory.h"

@ It turns out that we need to sort the lengths into ascending order.
Why? (Really, why?)

By the way, |dsort| is just Bentley and McIlroy's |qsort| function.
See module \module{DSORT}.

@<Sort the lengths into ascending order@>=
dsort(length,(size_t)ne,sizeof(double),cmp_double);

@
@<Module headers@>=
#include "dsort.h"

@
@<Module subroutines@>=
static int 
cmp_double( const void *ap, const void *bp ) 
{
	const double a = *(const double *)ap, b = *(const double *) bp;
	if ( a < b ) return -1;
	if ( a > b ) return 1;
	return 0;
}


@*Agglomeration.
We generate a clone by agglomeration.  That is, we mimic Kruskal's 
minimum spanning tree algorithm.  Kruskal's algorithm begins with isolated
vertices and repeatedly adds a next shortest edge that does
not create a cycle.  

However, Kruskal's algorithm projects information away, namely all the
discarded edges.
Our task is to build a coherent structure around the minimal information
we're given.   Furthermore, we are given only the edge lengths, and not
how the edges are connected.

This program generates only two-dimensional Euclidean instances, even
though its input might not have been projected down from a Euclidean instance.
I hope this restriction is not too damaging.

@ The algorithm is as follows.  Begin with isolated vertices, and then
perform the following steps until the list of lengths is exhausted.
Pick two components.
Pick a random vertex on each of their hulls.
Join those hull points by an edge whose length is equal to 
the next length in the sequence.

@s component_t int
@<Generate a clone@>=
for ( nc = n; nc > 1 ; nc-- ) { /* Value |nc| is the number of components. */
	component_t *a, *b;
	const double this_length = length[n-nc]; 	
		/* Ascending array order. */

	@<Set |a| and |b| to a random pair of components@>@;
	@<Choose hull points for |a| and |b|@>@;
	@<Separate |a| and |b| by |this_length| units, making a new component@>@;
}

@ We use multiple random number streams.  
@<Initialize the random number generators@>=
component_prng=gb_prng_new(seed);
hull_prng=gb_prng_new(seed^42);
angle_prng=gb_prng_new(seed^(42*42));
errorif(
component_prng==NULL
|| hull_prng==NULL
|| angle_prng==NULL
, "Couldn't allocate three random number generators");

@
@<|main| variables@>=
gb_prng_t *component_prng, *hull_prng;

@
@<Module variables@>=
gb_prng_t *angle_prng;

@ We need the interface to the Stanford GraphBase random number generator,
and my object-oriented extensions to it.
@<Module headers@>=
#include "gb_flip.h"


@
Of course, there may be many variations on this.  First, one might
want to sort the lengths into increasing order.  This might result in
more compact clones.  This is likely most easily implemented in a 
preprocessor to this program, \eg, a Perl script.
@^Perl@>
@^preprocessing@>

Second, we might want to bias the chosen components
in some way.  For now, components are chosen at random.
Looking at its output, this may have to change.  For example, 
TSPLIB instance \type{pla7397} has two bands of very tightly packed points,
with increasingly sparse points in between.  Choosing components randomly,
the short MST
edges become widely distributed, cluster-wise.  That's an
unfaithful representation of the cluster structure of the instance.
I suppose I shall have to carry more of the MST structure through to
the generated instances.
@^TSPLIB@>
@.pla7397@>

Third, we might want to bias the join points in some way.
Initially they were chosen at random.  Now the user has some control
through the join length bias (option \type{-j}) and the 
packing factor (option \type{-p}).
@^variations on agglomeration@>
@^agglomeration, variations@>

@*Data structures.
Now that we've seen the algorithm, 
we need to define the supporting data structures and their 
operations.

@ We begin with the easiest data structure: 
the collection of connected components.
All |n+ne| componenents are stored
in the |component| array (see below).  The initial |n| singleton
components are in entries 0 through $n-1$ of that array.  
Conglomerations of components are added in sequence in position $n$ and
afterward.  

The only state we need is the number of connected components.
We record that information in variable |nc|.
Then the first available slot is |component[n+n-nc]|.

@d next_component_slot() (component+n+n-nc)

@<Module variables@>=
int nc;

@ All the valid components, \ie, roots of components, 
are in positions $2(n-nc)$ through  $2n - nc - 1$
the initial part of the |component| array.
This makes picking one at random rather easy. 

Once chosen, the random roots are swapped with those in positions
$2(n-nc)$ and $2(n-nc)+1$ so that the roots are in place for
the next round.

@<Set |a| and |b| to a random pair of components@>=
{component_t temp; 
int base = 2*(n-nc), r;
r = base + gb_prng_unif_rand(component_prng,nc);
temp = component[base]; @+component[base] = component[r]; @+component[r] = temp;
r = base + 1 + gb_prng_unif_rand(component_prng,nc-1);
temp = component[base+1]; @+component[base+1] = component[r]; @+component[r] = temp;
a = component+base;
b = component+base+1;
}


@*1 Convex hulls.
To ensure that the resulting TSP instance has the same set of MST edge
lengths, the vertices joined are chosen from the convex hull of the components.
So each component must know its own convex hull.

A convex hull is an ordered set of points.  We will represent each hull by
a circular linked list.  
Since there are up to $n$ points in all the hulls, the linked
lists for all the hulls are just independent threads in an array 
of vertices named |hull_vertex|.

Each entry of |hull_vertex| represents a vertex in its hull list.
A vertex in this context knows its Euclidean coordinates
(stored in fields |x| and |y|)
and its successor and predecessor in the list 
(stored as pointers |next| and |prev| to
other elements of
array |hull_vertex|).  Each vertex is identified by its position in the
array.

@<Type definitions@>=

typedef struct hull_vertex_s {
	double x, y;
	struct hull_vertex_s *next, *prev;
} hull_vertex_t;

@ Allocation of the array of hull vertices is easy.  

@<Allocate and initialize the data structures@>=
hull_vertex = new_arr_of(hull_vertex_t,n);
@<Initialize the hulls to singletons@>@;

@
We begin with |n| trivial hulls.  Initialization is interesting only
because the linked lists are circular, therefore each vertex starts out
pointing to itself.
@<Initialize the hulls to singletons@>=
{ int i;
for (i=0;i<n;i++) {
	hull_vertex[i].x = 0;
	hull_vertex[i].y = 0;
	hull_vertex[i].next = hull_vertex[i].prev = hull_vertex+i;
}
}

@
Deallocation is even easier.
@<Clean up the data structures@>=
free_mem(hull_vertex);

@ We must declare the array.
@<Module variables@>=
hull_vertex_t *hull_vertex;

@ We'll be transforming hulls.  Procedure |hull_then_rotate| geometrically
rotates a hull about the origin.  
Procedure |hull_then_translate| translates it.

@<Module subroutines@>=
static void
hull_then_rotate( hull_vertex_t *h, double theta)
{
	const double ct = cos(theta), st = sin(theta);
	const hull_vertex_t *start = h;
	do {
		const double x = h->x, y = h->y;
		h->x = x * ct - y * st;
		h->y = x * st + y * ct;
		h=h->next;
	} while( h != start );
}

static void
hull_then_translate( hull_vertex_t *h, double x, double y)
{
	const hull_vertex_t *start = h;
	do {
		h->x += x;
		h->y += y;
		h=h->next;
	} while( h != start );
}

@*1 Connected components.
A component must know its points and its hull.    These are stored
separately.  That is, a point in the interior of the component is
stored only once, and a point on the hull is stored once in the point
collection and once in the hull.

@
In addition to being connected by edges, 
components will be geometrically translated and rotated.
In fact, each time a component is joined with another component, one of them
will be translated, both will likely be rotated, and then
their convex hulls merged.  The transformed coordinates of the hull points
must be known in order
to compute the new convex hull, but we don't need to know the exact
coordinates of each interior point until the end of the program
execution
when we write the output.  

So we can save a lot of computational 
effort by updating internal point coordinates lazily.  That is, when
a component is transformed, we store its transformation for later processing;
in contrast, we transform hull coordinates eagerly.  When it comes time
to write the cooridinates, we apply the accumulated transformations
on each point.

@ As components are merged, they form a binary tree.  
Leaves represent individual vertices.  Untransformed vertices are always
at the origin, so there is no need to store them explicitly.

@ A component also needs to know its hull size, the number of vertices in
its hull.

This completes the description of the component structure, modulo
a representation for geometric transformations.

@s rigid_motion_t int
@<Type definitions@>=
typedef struct component_s {
	struct component_s *left, *right;
	hull_vertex_t *hull;
	int hull_size;
	rigid_motion_t transform;
} component_t;

@ The component tree is a binary tree with |n| leaves and |ne| edges. 
(Recall $n=ne+1$.)  So we can allocate all the components at once
in array |component|.

@<Allocate and initialize the data structures@>=
component = new_arr_of(component_t,n+ne);
{int i;
for ( i=0; i<n; i++ ) {
	component[i].hull = hull_vertex + i;
	component[i].hull_size = 1;
	transform_init(&component[i].transform);
}
for ( i=0; i<n+ne; i++ ) component[i].left = component[i].right = NULL;
}

@ As usual, cleaning up is easy.
@<Clean up the data structures@>=
free_mem(component);

@ We need to declare array |component|.
@<Module variables@>=
component_t *component;


@ We use the join length bias to bias the choice of hull points for
both |a| and |b|.

During a single execution of the program, only one branch is chosen
because |join_length_bias| does not change after the command line options
are processed.

@<Choose hull points for |a| and |b|@>=
if ( join_length_bias < 0 ) {
	@<Randomly choose joining hull points for |a| and |b|@>@;
} else {
	@<Choose biased hull points for |a| and |b|@>@;
}

@ We pick a random joining point on a component's hull by 
advancing its |hull| pointer a random number of steps around the circular
list of hull vertices.  Since we'll be scanning the entire list later anyway,
this is only a constant multiple of overhead.

@<Randomly choose joining hull points for |a| and |b|@>=
{ long steps;
for ( steps = gb_prng_unif_rand(hull_prng,a->hull_size); steps ; steps-- ) 
		a->hull = a->hull->next;
for ( steps = gb_prng_unif_rand(hull_prng,b->hull_size); steps ; steps-- ) 
		b->hull = b->hull->next;
}

@  Ok, so it is a bit awkward doing this renaming.
@<Choose biased hull points for |a| and |b|@>=
{component_t *c;
c=a;@<Shift |c->hull| to a biased point@>@;
c=b;@<Shift |c->hull| to a biased point@>@;
}

@ Think of the join length bias as a fraction indexing into the sorted
list of hull lengths.  In fact, that's exactly how |join_length_bias| is
used.    However, we'll get both boundary values 0 and 1 to get the
shortest
and longest edges.

We only need the ordering among lengths, and not their values, so using
squared lengths is sufficient.

Ok, so |hull_sortbox| is a lousy name. So sue me. (No, dont!)


@d sqr(X) ((X)*(X))
@d hull_edge_len(HP) (sqr((HP)->x - (HP)->next->x)+sqr((HP)->y - (HP)->next->y))

@<Shift |c->hull| to a biased point@>=
{ hull_vertex_t *here=c->hull;
int i, index;
for (i=0,here=c->hull;i<c->hull_size;i++,here=here->next) {
	hull_sortbox[i].vertex = here;
	hull_sortbox[i].len = hull_edge_len(here);
}
dsort(hull_sortbox,(size_t)c->hull_size,sizeof(hull_sortbox_t),cmp_hull_sortbox);
index = floor(scale_01(join_length_bias,0,c->hull_size));
if ( index == c->hull_size ) index--; /* Don't get a non-existent vertex. */
c->hull = hull_sortbox[index].vertex;
}

@ We need to allocate the sorting box$\ldots$
@<Allocate and initialize the data structures@>=
hull_sortbox = new_arr_of(hull_sortbox_t,n);

@ $\ldots$ clean it up $\ldots$
@<Clean up the data structures@>=
free_mem(hull_sortbox);

@ $\ldots$ and declare it.
@<Module variables@>=
hull_sortbox_t *hull_sortbox;

@ Each bin in the sorting box has a vertex pointer and a length.
@<Type definitions@>=
typedef struct {
	hull_vertex_t *vertex;
	double len;
} hull_sortbox_t;

@ We also need a sorting function.
@<Module subroutines@>=
static int 
cmp_hull_sortbox( const void *ap, const void *bp ) 
{
	const double 
			al = ((const hull_sortbox_t *)ap)->len, 
			bl = ((const hull_sortbox_t *)bp)->len;
	if ( al < bl ) return -1;
	if ( al > bl ) return 1;
	return 0;
}

@*1 Geometric transformations.
% HA!
We will use only rigid body motions to transform our geometric objects.
Such motions always decompose into rotation by an angle  $\theta$ 
and a translation $v$.  We adopt the convention that the rotation is
always applied before the translation.  
% The following is beautiful, but alas, deprecated.
%% We borrow from computer graphics practice by using homogeneous coordinates.
%% That is, a point with coordinates $(x,y)$ is represented by
%%  $(a\cdot x,a\cdot y,a)$ for any non-zero $a$.
%% A rotation is represented by the matrix:
%% $$
%% \Rotate(\theta) = \left( 
%% 	\matrix{ \cos \theta & - \sin \theta & 0 \cr
%% 	         \sin \theta &  \cos \theta & 0 \cr
%% 	                   0 &            0 & 1 \cr}\right).$$
%% A translation is represented by the matrix:
%% $$
%% \Translate(u,v) = \left( 
%% 	\matrix{           1 &            0 & u \cr
%% 	                   0 &            1 & v \cr
%% 	                   0 &            0 & 1 \cr}\right).$$
%% Translations and rotations may transformation can be conveniently 
% Transforming a point $p$ then becomes multiplying it by $A$ and adding $v$,
% \ie, $p \mapsto A\cdot p + v$.

Recall that points are two-dimensional.

@<Early type definitions@>=
typedef struct {
	double theta;
	double v[2];
} rigid_motion_t;

@ We will need to initialize transformations.
The identity transformation consists of a rotation by angle 0 
and a translation
by $(0,0)$.
@<Module subroutines@>=
static void
transform_init( rigid_motion_t *t )
{
	t->theta = t->v[0] = t->v[1] = 0.0;
}

@ Now we define a few composition operators.  Each takes a transformation
argument |t| and some modifier |m|.  We update |t| to have the effect
of operation |m| after applying its original value.  That is,
$ t' = m \circ t $.  If you like thinking in linear algebra terms, we
multiply the matrix for |t| on the right by the matrix
for |m|, and then assign it to
|t|.

@
Translation is easy because it doesn't affect the rotation.
(Remember that our convention is that the rotation is always performed
before the translation.)
@<Module subroutines@>=
static void 
transform_then_translate( rigid_motion_t *t, double x, double y )
{
	t->v[0] += x;
	t->v[1] += y;
}

@ Rotating by angle $\theta$ is tricky because the translation must also
be rotated.

@<Module subroutines@>=
static void 
transform_then_rotate( rigid_motion_t *t, double theta )
{
	const double ct = cos(theta), st = sin(theta);
	const double x = t->v[0], y = t->v[1];
	t->v[0] = x * ct - y * st;
	t->v[1] = x * st + y * ct;
	t->theta += theta;
}

@ Functions |cos| and |sin| are in the math library.
@<System headers@>=
#include <math.h>


@ Given rotation and translation, applying a full-blown rigid motion is an
easy two-step process.

@<Module subroutines@>=
static void 
transform_then_transform( rigid_motion_t *t, rigid_motion_t *t2 )
/* Apply |t2| to |t| in place. */
{
	rigid_motion_t copy;
	if ( t == t2 ) {@+ copy = *t2; @+ t2 = &copy; @+ } 	/* Fix aliasing. */
	transform_then_rotate(t,t2->theta); /* Rotations come before translations. */
	transform_then_translate(t,t2->v[0],t2->v[1]);
}

@ Now we have all the tools to fully define applying rigid motions to
components as a whole.

@<Module subroutines@>=
static void
component_then_rotate( component_t *c, double theta )
{
	transform_then_rotate(&(c->transform),theta);
	hull_then_rotate(c->hull,theta);
}

static void
component_then_translate( component_t *c, double x, double y )
{
	transform_then_translate(&(c->transform),x,y);
	hull_then_translate(c->hull,x,y);
}


@*Joining components.
This is the hard part.  We're given two connected components |a| and |b|, and
vertices |ah == a->hull| and |bh ==b->hull| on their respective convex hulls.
We're asked to glue |a| and |b| to make new component |c| so that
the minimum distance between points in |a| and points in |b| is exactly
|this_length| units, and points |ah| and |bh| meet that minimum.

The |a| and |b| hulls are always very carefully rotated before joining, 
so there's no point in rotating |c| until it is the last component.
That's until it's the last component, |c| will always join another
component
later, and therefore pass through here again as either |a| or as |b|.

@<Separate |a| and |b| by |this_length| units, making a new component@>=
rotate_hull_with_bias(a,1);
b->hull = b->hull->next;rotate_hull_with_bias(b,0); component_then_rotate(b,pi);
{
component_t *c = next_component_slot();
hull_vertex_t *ah = a->hull, *bh = b->hull;
@<Translate |a| so |ah| is |this_length| units above |bh|@>@;
@<Make new component |c| from subcomponents |a| and |b|@>@;
if ( nc > 2 ) {@<Rotate |c| by a random angle@>@;}
}

@ Let's do an easy part first.
@<Translate |a| so |ah| is |this_length| units above |bh|@>=
component_then_translate(a, bh->x - ah->x, bh->y - ah->y + this_length);
@<Verbose: check that |a| and |b| are really |this_length| units apart@>@;

@ The final rotation is also easy.

@d pi (3.1415926535897932384626433832795028841972) /* See Knuth's TAOCP, volume 1. */
@d two_to_the_31 ((unsigned long)0x80000000) /* See Knuth's Stanford Graphbase. */
@d scale_01(s,a,b) ((a)+((b)-(a))*(s))
@d uniform_sample(g,a,b) scale_01((((double)gb_prng_next_rand(g))/two_to_the_31),(a),(b))
	/* Samples $[a,b)$. */
@d uniform_sample_incl(g,a,b) scale_01(((double)gb_prng_next_rand(g))/(two_to_the_31-1),(a),(b))
	/* Samples $[a,b]$. */

@<Rotate |c| by a random angle@>=
component_then_rotate(c, uniform_sample(angle_prng,-pi,pi));

@ 
Here's where we rotate a component with a bias.
Let's name the component |comp| and its hull point |comph =comp->hull|.
We rotate |comp| so that |comph| is at the bottom, \ie, its |y| coordinate
is the least of any |y| coordinate of points in |comp|.

We have some freedom in picking the angle used to rotate the component.
There are two cases: the forward direction, and the backward direction.
The forward direction is as follows.
At one extreme, angle |alpha| lays the vector from |comph->prev| 
to |comph| at angle
0 (\ie, parallel to the $x$ axis and pointing toward positive infinity).
At the other extreme, angle |beta| 
lays the vector from |comph| to |comph->next| at angle 0.

The backward direction interchanges the roles of |alpha| and |beta|.

Hulls are oriented counter-clockwise.  
That is, following |next| pointers results
takes you around the hull while making left-hand turns.    

Of course, if there's only one point in the hull, then there's nothing to do!
@^counter-clockwise@>
@^hull orientation@>
@^orientation, hull@>

@<Module subroutines@>=
void rotate_hull_with_bias(component_t *comp,int is_foward);
void
rotate_hull_with_bias(component_t *comp,int is_forward) 
{
hull_vertex_t *comph=comp->hull;
if (errno) {perror("main: about to rotate comp");errorif(1,"Oops!");}
if ( comp->hull_size > 1 ) {
	double rot;
	double alpha = - atan2( comph->y - comph->prev->y, comph->x - comph->prev->x);
	double beta = - atan2( comph->next->y - comph->y, comph->next->x - comph->x);
	errorif(errno==EDOM,"Sorry, my call to atan2 had a bad argument.");
	errorif(errno==ERANGE,"Sorry, the answer to my atan2 call was out of range.");
	while ( alpha < beta ) beta -= 2*pi; 
		/* Rectify the principal value of arctan. */
	@<Set |rot| to a biased value between |alpha| and |beta|@>@;

	component_then_rotate(comp, rot);
}
@<Verbose: show component |comp|@>@;
}

@
@<System headers@>=
#include <errno.h>

@
@<Clear |errno|@>=
errno = 0;


@
I used to randomly choose an angle from a uniform distribution over 
$[\alpha,\beta]$, but that seemed to generate very sparse and stringy
instances.

So 
I introduced a positive number |packing_factor|, used to bias the
choice between |alpha| and |beta|.  A factor of 1 specifies a uniform
distribution.  Higher factors specify a tighter packing, and
lower factors specify a looser packing.  But we're still at the mercy
of randomization.  The packing factor is a hint.

In fact, if $y$ is in $[0,1]$, we set $t= y^p$, where $p$ is the
non-negative packing factor.  When $p$ is near zero, $t$ is biased toward
1; when $p$ is large and positive, $t$ is biased toward 0.
So when the packing factor is small the angle is biased toward |alpha|,
and when the packing factor is large the angle is biased toward |beta|.
(That's the forward case. The backward case is opposite.)

Ok, so there's a small trick here.  I want to avoid taking the logarithm
of zero, so I sample from $[0,1)$, and then subtract that from 1, and 
only then take the logarithm.  Still, I should probably check for errors
back from |log|.

@<Set |rot| to a biased value between |alpha| and |beta|@>=
@<Clear |errno|@>@;
{ double y = 1-uniform_sample(angle_prng,0,1), t = exp(packing_factor * log(y));
switch(errno) {
case 0: break;  /* All is ok in floating point land. */
case ERANGE: t=1.0; @<Clear |errno|@>; break; /* Rail it to 1. */
default: perror("main: about to sample alpha beta");errorif(1,"Oops!");
}
errorif(t<0.0 || 1.0<t,"alpha-beta mediation is %f, not in [0,1]", t);
if ( !is_forward ) t = 1-t;
rot = t * alpha + (1-t) * beta;
@<Verbose: report |rot|@>@;
}




@ The new component goes in |c|.  
First, it needs to
know its two subcomponents |a| and |b|.  
Second, its convex hull must be
computed.

Component |c| has already had its transform initialized 
(at the time array |component| was allocated, remember?).

@<Make new component |c| from subcomponents |a| and |b|@>=
c->left = a;
c->right = b;
@<Merge the hulls of |a| and |b| to form the hull of |c|@>@;

@*1 Merging convex hulls.
There are many algorithms for computing the convex hull of a set of points
in the plane.  For a good treatment, see chapters 3 and 
4 in \book{Computational Geometry: An 
Introduction}, Franco P.~Preparata and Michael Ian Shamos, 
Springer-Verlag, Texts and Monographs in Computer Science, 1985.

Things are quite a bit simpler in our case because we are merging
two non-overlapping convex hulls, and we know their relative positions (|b|
lies below |a|).  In particular, our situation is simpler than covered
in section 3.3.5 of \book{Computational Geometry}, where a hull
merge algorithm
is developed.

@ Even so, I'll use one of the simpler algorithms, Graham's scan.

First, we find an extreme point of both sets, |west|. 
Second, we sort the points by polar their angle about |west| with careful 
tie-breaking rules.
Third, we scan them in order, eliminating 
right turns.


@<Merge the hulls of |a| and |b| to form the hull of |c|@>=
@<Copy the hulls of |a| and |b| to |hull_buf|@>@;
@<Make |west| the leftmost point in |hull_buf|@>@;
@<Carefully sort the hull points about |west|@>@;
@<Perform a Graham scan and copy the new hull to |c|@>@;

@ Let's do the easy parts first, shuffling the data about.  It will
be convenient to remember in array |available| the positions that
make up the hulls of |a| and |b|.

@<Copy the hulls of |a| and |b| to |hull_buf|@>=
{ hull_vertex_t *start, *here;
nh=0;
here = start = a->hull; 
do {
	hull_buf[nh].x = here->x;
	hull_buf[nh].y = here->y;
	available[nh] = here - hull_vertex;
	here = here->next;
	nh++;
} while ( here != start );
here = start = b->hull; 
do {
	hull_buf[nh].x = here->x;
	hull_buf[nh].y = here->y;
	available[nh] = here - hull_vertex;
	here = here->next;
	nh++;
} while ( here != start );
}

@ Buffer |hull_buf| may contain up to |n| vertices.
@s point_t int
@<Allocate and initialize the data structures@>=
hull_buf = new_arr_of(point_t,n);
available = new_arr_of(int,n);

@
@<Clean up the data structures@>=
free_mem(hull_buf);
free_mem(available);

@
@<Module variables@>=
point_t *hull_buf=NULL, west;
int *available, nh=0;

@ I could probably use the |point_t| type in |hull_vertex_t|$\ldots$

@<Type definitions@>=
typedef struct { double x, y, angle; } point_t;

@  Not only do we find |west|, but we also move it to the first position 
in the array.
@<Make |west| the leftmost point in |hull_buf|@>=
{ int i;
west = hull_buf[0];
for (i=1;i<nh;i++) 
	if ( hull_buf[i].x < west.x ) {
		west = hull_buf[i]; 
		hull_buf[i] = hull_buf[0]; 
		hull_buf[0] = west;
	}
}

@ To sort the points, we need to assign to each point its
the polar angle about |west|.  
Of course, the angle of |west| about
itself is undefined;  we don't need to find its angle because
it's already in place.

@<Carefully sort the hull points about |west|@>=
{ int i;
for (i=1;i<nh;i++) {
	hull_buf[i].angle = atan2( hull_buf[i].y - west.y, hull_buf[i].x - west.x );
}
qsort(&hull_buf[1],(size_t)nh-1,sizeof(point_t),cmp_point);
}

@ Of course, we need the comparison function for |qsort|.
The main part of the comparison is by angle.  If there's a tie, then
the point closer to |west| is taken as being ``before'' the other one.


@<Module subroutines@>=
#define abs(A) ((A)<0 ? -(A) : (A))
static int 
cmp_point( const void *ap, const void *bp ) 
{@/
	const point_t a = *(const point_t *)ap, b = *(const point_t *) bp;
	if ( a.angle < b.angle ) return -1;
	if ( a.angle > b.angle ) return 1;
	if ( a.x < b.x ) return -1; /* Point |a| is closer to |west| than |b| is. */
	if ( a.x > b.x ) return 1;
	if ( abs(a.y-west.y) < abs(b.y-west.y) ) return -1;
	if ( abs(a.y-west.y) > abs(b.y-west.y) ) return 1;
	return 0;
}

@ A Graham scan works as follows.  We perform a single sweep of the points
in increasing polar coordinates, with ties broken as above.
During the sweep we maintain a stack of points that we propose to be
on the convex hull.  When considering a new point $w$, we push it
onto the stack and ask ``Is $u$ to
$v$ to $w$ a left hand turn?'', where $v$ is immediately below $w$ on the
stack, and
and $u$ is immediately below $v$.  If so, then we continue with the
next point.  If not, we remove $v$ and repeat the test.

As for starting and ending conditions, point |west| is an extremum, so
it must appear on the hull.  
The only tricky part is that we may have to reject several points near
the end of the |hull_buf| list because they may be the apex of a right
turn ending in |west|.  That explains the shenanigans with trying
to put |west| on the list twice.

Array |stack| is an indirection array.  That is, |stack[i]| is
the index into |hull_buf| of item |i| on the stack, with higher
indices being closer to the top of the stack (thank goodness).


@<Perform a Graham scan and copy the new hull to |c|@>=
{
int i;
int top=-1;  /* The index of the latest addition to the stack. */
@<Verbose: beginning of Graham scan@>@;
for (i=0;i<=nh;i++) {
	stack[++top] = (i<nh)?i:0;
	@<Verbose: try to add new point@>@;
	while ( top >= 2 && stack[top-2] != stack[top]
			@| && !left_turn( hull_buf[stack[top-2]],
								hull_buf[stack[top-1]],
								hull_buf[stack[top]]) ) { /* Remove $v$. */
		@<Verbose: remove a point@>@;
		stack[top-1] = stack[top];
		top--;
	}
}
@<Verbose: end of Graham scan@>@;
@<Copy the new hull to |c|@>@;
}

@
@<|main| variables@>=
int *stack;

@ We must make space for the second copy of |west|.
@<Allocate and initialize the data structures@>=
stack = new_arr_of(int,n+1);

@
@<Clean up the data structures@>=
free_mem(stack);


@ Copying the new hull over the old ones is tricky for two reasons.
First, we must be careful to not copy |west| twice.

Second and more importantly, we may write over only those hull vertices
that were part of |a| and |b|.  We've already planned ahead and
recorded in array |available| the list of
positions in |hull_vertex| used by |a| and |b|.

@<Copy the new hull to |c|@>=
for ( i=0; i<top; i++ ) {
	hull_vertex_t *here = &hull_vertex[available[i]];
	here->x = hull_buf[stack[i]].x;
	here->y = hull_buf[stack[i]].y;
	here->prev = &hull_vertex[available[(i-1+top)%top]];
	here->next = &hull_vertex[available[(i+1)%top]];
}
c->hull = &hull_vertex[available[0]];
c->hull_size = top;

@ We need to implement the left-turn test.  This is well known.
See equation (3.4) of Preparata and Shamos, or 
the |ccw| test (counterclockwise) function in 
program GB\_PLANE of Knuth's Stanford GraphBase.  
The angle $uvw$ is a left turn if and only if 
$$\det \left(\matrix{ 
u_x & u_y & 1 \cr
v_x & v_y & 1 \cr
w_x & w_y & 1 \cr}\right) > 0.$$
This 3x3 determinant is equal to the 2x2 determinant
$$\det \left(\matrix{ 
u_x - w_x& u_y-w_y \cr
v_x - w_x& v_y-w_y \cr
}\right),$$
which saves us several multiplications.

Numerical analysts beware!

@<Module subroutines@>=
static int 
left_turn( point_t u, point_t v, point_t w) 
{
	const double 
			ad = (u.x-w.x)*(v.y-w.y), 
			bc = (u.y-w.y)*(v.x-w.x);
	return ad > bc;
}


@*Writing the output.
We're almost done.  
The component tree is built, but the subcomponents need
to be transformed.  

The convex hulls are now useless.  In fact, the pointers from the
subcomponents into |hull_vertex| are meaningless.   Before we
transform the coordinates, we must each of these hull pointers to something
minimal but harmless.  Recall that transforming a component 
eagerly transforms the hull.

@<Print the clone@>=
@<Initialize the hulls to singletons@>@;
printf("NAME: egen%d\n",n);
printf(
	"COMMENT: generated from MST edge lengths, (LK %s) %s -s %ld -j %f -p %f\n",
	VERSION_STRING,prog_name,seed,join_length_bias,packing_factor);
printf("TYPE: TSP\n");
printf("DIMENSION: %d\n",n);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");
errorif(nc!=1,"Must be only one component, but nc==%d.",nc);
{ int city_num=1;
write_component(stdout,next_component_slot()-1,&city_num);
errorif(city_num-1!=n,"Wrote %d cities instead of %d.",city_num,n);
}
printf("EOF\n");

@  We use a recursive procedure to write the component.
@<Module subroutines@>=
static void
write_component(FILE *file,component_t *c, int *city_num)
{
	if ( c->left ) {
		transform_then_transform(&(c->left->transform), &(c->transform));
		write_component(file,c->left,city_num);
	}
	if ( c->left == NULL && c->right == NULL ) {
		printf("%10d %.15f %.15f\n",
			*city_num,
			c->transform.v[0],c->transform.v[1]);
		*city_num += 1;
	}
	if ( c->right ) {
		transform_then_transform(&(c->right->transform), &(c->transform));
		write_component(file,c->right,city_num);
	}
}

@*Verbose.
I used the following during debugging.
@<Verbose: show component |comp|@>=
#if DEBUG >= 100
{ int i; hull_vertex_t *here;
printf("Hull size %d, bottom point listed first.\n", a->hull_size);
for ( i=0, here=comp->hull; i < comp->hull_size ; i++, here=here->next ) {
	printf("\t%10.5f  %10.5f\n",here->x, here->y);
}
errorif(here != comp->hull, "hull_size wrong");
}
#endif

@
@<Verbose: check that |a| and |b| are really |this_length| units apart@>=
#if DEBUG >= 100
{
	hull_vertex_t *here, *ahere, *bhere;
	const double d=euc2hull(ah,bh);
	int fail=0;
	here = ah;
	
	/* Check that no point of |b| is closer to |ah| than |bh| is */
	for ( here=bh->next; here != bh ; here = here->next ) {
		const double hd = euc2hull(ah,here);
		if ( d > hd ) fail=1,fprintf(stderr,"d = %f > hd = %f\n", d, hd);
		fprintf(stderr,"a");
	}
	/* Check that no point of |a| is closer to |bh| than |ah| is */
	for ( here=ah->next; here != ah ; here = here->next ) {
		const double hd = euc2hull(bh,here);
		if ( d > hd ) fail=1,fprintf(stderr,"d = %f > hd = %f\n", d, hd);
		fprintf(stderr,"b");
	}

	/* Check all $m \cdot n$ possibilities */
	ahere = ah;
	do {
		bhere = bh;
		do {
			const double hd = euc2hull(ahere,bhere);
			if ( (ahere != ah || bhere != bh) && d > hd ) 
				fail=1,fprintf(stderr,"full d = %f > hd = %f\n", d, hd);
			bhere = bhere->next;
			fprintf(stderr,"c");
		} while (bhere != bh);
		ahere = ahere->next;
	} while (ahere != ah);

	
	/* Check that |ah| and |bh| really are |this_length| units apart. */
	if ( d < this_length - 1e-6 ) 
		fail=1,fprintf(stderr,"d = %f < %f = this_length\n", d, this_length);
	if ( d > this_length + 1e-6 ) 
		fail=1,fprintf(stderr,"d = %f > %f = this_length\n", d, this_length);
	fprintf(stderr,"\n");
	errorif(fail,"distances mucked up!");
}
#endif

@
@<Module subroutines@>=
#if DEBUG >= 100
static double
euc2hull(hull_vertex_t *ah, hull_vertex_t *bh) 
{
	const double dx = ah->x - bh->x, dy = ah->y - bh->y;
	return sqrt(dx*dx + dy*dy);
}
#endif


@
@<Verbose: report |rot|@>=
#if DEBUG >= 200
{ double frac = (rot-beta)/(alpha-beta);
fprintf(stderr," angle %10.5f%% alpha and %10.5f%% beta %s\n", 
	100*frac, 100*(1-frac), (is_forward?"forward":"reverse"));
errorif(frac < 0.0 || 1.0 < frac,"Frac %f out of [0,1]",frac );
}
#endif

@
@<Verbose: beginning of Graham scan@>=
#if DEBUG >= 100
	printf("Graham scan: nh==%d\n",nh);fflush(stdout);
#endif

@
@<Verbose: try to add new point@>=
#if DEBUG >= 100
	printf(" push   %d, top==%d\n",stack[top], top);fflush(stdout);
#endif


@
@<Verbose: remove a point@>=
#if DEBUG>=100
		printf(" remove %d, top==%d\n",stack[top-1], top-1);fflush(stdout);
#endif

@
@<Verbose: end of Graham scan@>=
#if DEBUG >=100
printf("Done Graham scan: top==%d\n",top);fflush(stdout);
#endif

@*Index.
