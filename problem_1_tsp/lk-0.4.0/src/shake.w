


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

@s domain_t int
@s decluster_edge_t int
@s benchmark_t int
@s prng_kind_t int

@f pi TeX

\def\9#1{{\sl #1}}
{\obeylines
$Log: shake.w,v $
Revision 1.7  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.6  1998/02/13 19:42:22  neto
Document kludges in index.

Revision 1.5  1997/12/17 22:52:48  neto
Rotate around the city on the small end rather than the city on the large
end.  Also, verbose output and debug output are the same in this module.

Revision 1.4  1997/12/17 22:24:20  neto
Fixed an index transformation bug. I wasn't subtracting n when going
from T prime to mst.

Revision 1.3  1997/12/17 21:29:25  neto
Reduce effect of deviation factor by half.
Kludgy check for matchup between mst and T prime.

Revision 1.2  1997/12/17 20:47:49  neto
Fixed CWEB Error causing size to not be initialized.
Fixed off-by-one error counting down the largest elements of T prime
Added seed parameter to comment of output TSPLIB instance.

Revision 1.1  1997/12/17 20:03:22  neto
Initial revision

}

@*SHAKE.
This program perturbs the coordinates in a TSPLIB instance by ``shaking'' 
its minimum spanning tree (MST).
It is useful for confirming that the difficulties the Lin-Kernighan
has with particular clustered instances are not just a fluke.

@ The outline of this program is as follows.
@c

const char *prog_name = "shake";
const char *shake_rcs_id = "$Id: shake.w,v 1.7 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Global variables@>@;
@<Module variables@>@;
@<Module subroutines@>@;


int main(int argc, char **argv) 
{
	@<Basic initialization@>@;
	@<Process the command line@>@;
	@<Read the instance@>@;
	@<Allocate data structures@>@;
	@<Preprocess the instance@>@;
	@<Shake the tree@>@;
	@<Write the instance@>@;
	@<Clean up the data structures@>@;
	return 0;
}

@ There are a few command line parameters.  
They are processed only if the \CEE/ library has the |getopt| function.

Option \type{-h} provides help, then exits successfully.


Option \type{-s} takes a mandatory integer paramter used as the random
number seed.  Actually, we use three independent random number streams, 
but each is initialized with a seed generated deterministically from the
command-line specified seed.  The default seed is, of course, $1969$.

Option \type{-R} takes a mandatory string parameter naming a random
number generator algorithm.  Currently, the algorithms are 
\type{gb\_\,flip}, the generator provided with the Stanford GraphBase,
and \type{nrand48}, the 48-bit linear congruential generator provided
by most variants of Unix.  If the given name does not match either, 
\type{gb\_\,flip}
is substituted.
@^Unix@>
@:Stanford GraphBase@>

Option \type{-b} takes a mandatory natural number parameter 
$num_to_shake$ 
indicating the number of branches to shake.  The $num_to_shake$ longest
branches in the minimum spanning tree should be shaken.
The default value is 20.

Option \type{-d} takes a mandatory numeric parameter $d$.  
The angle to by which to rotate a branch is normally distributed with
mean 0 and standard deviation of $d\cdot\pi/32$.
The default for $d$ is 1.

@<Process the command line@>=
seed = 1969L;
generator_kind = PRNG_DEFAULT;
num_to_shake = 20;
deviation_factor = 1.0;
#if HAVE_GETOPT
while(1) {
	extern char *optarg;
	extern int getopt(int,char*const*,const char*);
	const int opt = getopt(argc,argv,"s:hR:d:b:");
	if (opt==EOF) break;
	switch(opt) {
	case 's': seed = atol(optarg); @+ break;
	case 'h': usage(argv);@+  exit(0); @+ break;
	case 'R': generator_kind = prng_kind_from_name(optarg);@+  break;
	case 'b': num_to_shake = atol(optarg);@+ break;
	case 'd': deviation_factor = atof(optarg);@+  break;
	case ':': errorif(1,"Some option is missing an argument");@+  break;
	case '?': usage(argv);@+  errorif(1,"Unrecognized option");@+  break;
	default: errorif(1,"getopt returned character 0%o",opt);
	}
}
errorif(num_to_shake<0,"-b requires a non-negative argument, but given %d", num_to_shake);
#endif /* |HAVE_GETOPT| */

@ We need to declare the command line parameters.
@<Module variables@>=
static long seed;
static prng_kind_t generator_kind;
static double deviation_factor;
static int num_to_shake;

@ We've used the interface to the pseudo-random number generator
abstraction
layer, and to the error checking code.  We need their definitions.
@<Module headers@>=
#include "prng.h"
#include "error.h"

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
"Shake a TSPLIB instance.\n"@;
"\nCopyright (C) 1997 David M. Neto\n");@;
printf(
"%s comes with NO WARRANTY, to the extent permitted by law.\n", prog_name);@;
printf(
"You may redistribute and/or modify copies of %s under the terms of the\n"@;
"GNU General Public License, version 2 or any later version.\n"@;
"For more information about these matters, see the file named COPYING.\n",
prog_name);@;
printf(
"\n"
"Usage: %s [options]\n",argv[0]);
printf(
" -b <num>     : Shake the <num> longest branches in some MST of the instance\n"@|
"                Default <num> is 20\n"@|
" -d <f>       : Signed shake angle is normally distributed with mean\n"@|
"                0 and standard deviation <f>*pi/32\n"@|
"                Default <f> is 1\n"@|
" -h           : Output this help and quit\n"@|
" -R <gen-alg> : Use the named random number genarator.\n"@|
"                <gen-alg> is one of:");
{int i; for (i=0;i<PRNG_NUM_KINDS;i++) { 
	printf(" %s",prng_name_from_kind(i)); 
}
}
printf("\n"@|
" -s <seed>    : Use integer <seed> as the random number seed\n"@|
);
}

@ 
We've used some standard I/O.  Let's get the usual goodies.

@<System headers@>=
#define _POSIX_C_SOURCE 2   /* GNU headers need this to define a |getopt| prototype. */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

@
We've also used the nearly-universal |getopt| function for processing
command line options.  If its prototype isn't in \file{unistd.h} then
we get one from \file{fixincludes.h} and hope for the best.

@<Module headers@>=
#if HAVE_GETOPT
#define FIXINCLUDES_NEED_GETOPT
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_GETOPT
#endif /* |HAVE_GETOPT| */


@ Module \module{READ} has a reading routine that does the right thing.
The first argument is the file stream from which to read the instance.
The second argument is the file stream, if any, on which to put 
debugging output in PostScript.
@^PostScript@>

@<Read the instance@>=
tsp_instance = read_tsp_file(stdin,NULL);
n = tsp_instance->n;
errorif(num_to_shake>n-1,
	"There are only %d nodes, so I can't shake %d branches",n,num_to_shake);

@
@<Module variables@>=
static tsp_instance_t *tsp_instance;
static int n;

@
@<Module headers@>=
#include "length.h"
#include "read.h"

@ The \module{READ} module needs to know in advance whether to round 
distances.  We may want to eventually let the user decide.

This only affects the building of the minimum spanning tree by way
of affecting the |cost| function.  The transformed coordinates are
always computed to full precision.

@<Global variables@>=
int noround=1;

@ 
We shake branches of the minimum spanning tree, so
we need to build the tree.  It just so happens that the declustering
module already knows how to build minimum spanning trees.

@<Preprocess the instance@>=
E2_create(tsp_instance);
mst = decluster_setup(n);
mst_len = decluster_mst(tsp_instance,mst);
@<Debug: check the MST@>@;
errorif( n != 1 + mst->n, "Wrong number of edges in MST: %d instead of %d",
	mst->n, n-1);

@ The $k$-d tree routines need the |verbose| variable.

Also, the minimum spanning tree algorithm needs a sorting function
compatible with |qsort|.  Function |dsort| implements Bentley and McIlroy's
version of |qsort|.

@<Global variables@>=
int verbose=100;
void (*sort)(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));

@
@<Module headers@>=
#include "dsort.h"

@
@<Basic initialization@>=
sort = dsort;

@
@<Module variables@>=
static decluster_tree_t *mst=NULL;
static double mst_len;

@
@<Clean up the data structures@>=
E2_destroy();
decluster_cleanup_tree(mst);
decluster_cleanup();

@
@<Module headers@>=
#include "pool.h"
#include "kdtree.h"
#include "decluster.h"


@ Now, the declustering routines also help us out by building a
\term{topology tree}. The topology tree $T'$ is a binary tree whose
internal nodes are all the nodes of the minimum spanning tree $T$,
and whose leaves are all the vertices of minimum spanning tree.
The MST edge $e$ at each internal node of $T'$ is at least as heavy as any
MST edge in the subtree of $T'$ rooted at $e$.

In fact, the way |decluster_preprocess| builds it, the topology tree's
edges are listed in increasing weight. 

So, we have vertices 0 through $n-1$ of $T'$ being the vertices of the
original graph.  We'll ignore those.   Then vertices $n$ through $2n-1$
of $T'$ being the edges of the MST, in non-decreasing weight order.
Rather convenient for us, yes?


@<Preprocess the instance@>=
decluster_discard_topology_tree = 0;
decluster_preprocess(mst);
T_prime = decluster_topology_tree();
errorif(T_prime->n != 2*n-1,"Topology tree is the wrong size: %d instead of %d",
T_prime->n, 2*n-1);

@
@<Module variables@>=
decluster_tree_t * T_prime;

@ When shaking a branch, we move the nodes on the side of the
branch that has fewer nodes.  So we need to know how many TSP vertices are in
each subtree.  This is recorded in array |size|, and it runs parallel
to |T_prime|.

Now, we know the ancestors in |T_prime|
always follow their descendants.  We take advantage of this by building
|size| bottom-up.

@d child city		/* This identity holds internally to |T_prime| */

@<Preprocess the instance@>=
{int i, size_T_prime=2*n-1;
size = new_arr_of(int,size_T_prime);
for (i=0;i<n;i++) size[i]=1;
for (i=n;i<size_T_prime;i++)
	size[i]=size[T_prime->edge[i].child[0]]+size[T_prime->edge[i].child[1]];
}

@
@<Clean up the data structures@>=
free_mem(size); mem_deduct((2*n-1)*sizeof(int));

@
@<Module variables@>=
int *size=NULL;

@ We need declarations of the memory management functions and macros.
@<Module headers@>=
#include "memory.h"

@ We shake the heaviest |num_to_shake| branches of the MST.  They are
all bunched up at the end of |T_prime|.

@^Knuth, Donald Ervin@>
@:Art of Computer Programming, The@>

@d pi (3.1415926535897932384626433832795028841972) /* See Knuth's TAOCP, volume 1. */

@<Shake the tree@>=
{int i;
const double stddev = deviation_factor*pi/32.0;
const double mean = 0.0;
prng_t *shake_prng = prng_new(generator_kind,seed);
int *fringe=new_arr_of(int,n), fringe_size;

for (i=0;i<num_to_shake;i++) {
	const double angle = prng_normal(shake_prng,mean,stddev);
	const decluster_edge_t *branch = T_prime->edge + ((2*n-1)-1 - i);
	const int smaller_end = 
		( size[branch->child[0]] < size[branch->child[1]] ) ? 0 : 1;
	@<Debug: output (outdated?) MST edge info@>@;

	@<Write the leaves of the smaller end into |fringe|@>@;
	@<Rotate the fringe vertices by |angle| around the smaller end@>@;
}
free_mem(fringe);mem_deduct(sizeof(int)*n);
prng_free(shake_prng);
}

@ We use breadth-first search to scan the smaller subtree.
Breadth-first search is fast, easy to code, and doesn't blow up the
stack.

Array |pending| holds the indices into |T_prime| of the nodes that
are not yet processed in the breadth-first search.

@<Write the leaves of the smaller end into |fringe|@>=
{
int r, w;	/* Read and write cursors. */
fringe_size = 0;
pending[0]=branch->child[smaller_end];
for (r=0,w=1; r<w; r++) {
	if ( pending[r] < n ) fringe[fringe_size++] = pending[r];
	else {
		pending[w++] = T_prime->edge[pending[r]].child[0];
		pending[w++] = T_prime->edge[pending[r]].child[1];
	}
}
errorif(w>n,"Bug: fringe breadth first search overran array. %d>%d",w,n);
}
errorif(fringe_size > n/2,"Bug: fringe too big.\n");

@
@<Allocate data structures@>=
pending = new_arr_of(int,n);

@
@<Clean up the data structures@>=
free_mem(pending); mem_deduct(n*sizeof(int));

@
@<Module variables@>=
static int *pending;


@ Here's a kludgy part.  It turns out that the |child| array inside
an edge is overloaded onto the |city| array.  So to retrieve the
city number, we have to go back into the MST array.  This is very fragile:
it depends on internal behaviour of the declustering module's processing.
@^kludge@>

The rotations themselves are routine, as long as you remember that 
the origin of the rotation is the city on the smaller end of
the shaking branch.  So we need to translate both before and after
the rotation.

@<Rotate the fringe vertices by |angle| around the smaller end@>=
@<Debug: check that |mst| and |T_prime| match up@>@;
{
int i;
double ct=cos(angle), st=sin(angle);
const int smaller_end_city = 
		mst->edge[branch-T_prime->edge-n].city[smaller_end];  /* Ick! */
const double anchor_x = tsp_instance->coord[smaller_end_city].x[0]; 
const double anchor_y = tsp_instance->coord[smaller_end_city].x[1]; 
@<Debug: show anchor and angle@>@;
for (i=0;i<fringe_size;i++) {
	const int city = fringe[i];
	const double x = tsp_instance->coord[city].x[0] - anchor_x;
	const double y = tsp_instance->coord[city].x[1] - anchor_y;
	@<Debug: show current position of the city@>@;
	tsp_instance->coord[city].x[0] = x*ct - y*st + anchor_x;
	tsp_instance->coord[city].x[1] = x*st + y*ct + anchor_y;
	@<Debug: show new position of the city@>@;
}
}

@ We need the definitions of the |cos| and |sin| functions from the math
library.

@<System headers@>=
#include <math.h>


@ When writing out the instance again, we keep the same edge-weight
type, even though this might not jibe well with the fact we didn't use
rounded distances.

However, we do the command line parameters to the comment.

The |write_tsp_file| belongs to module \module{READ}.

@<Write the instance@>=
{ 
char *old_comment= tsp_instance->comment;
char *new_comment = new_arr_of(char,200+strlen(old_comment));
sprintf(new_comment,"%s | %s -R %s -s %ld -b %d -d %g",
	old_comment,
	prog_name,
	prng_name_from_kind((int)generator_kind),
	seed,
	num_to_shake,
	deviation_factor);
free_mem(old_comment);
tsp_instance->comment = new_comment;
write_tsp_file(tsp_instance,stdout);
}

@*Debugging output.
The following sections are the code I used to debug this program, beyond
segmentation faults and compiler errors.

@ First, I was paranoid about the MST.   It turned out that I was getting
it right.  Phew!

@<Debug: check the MST@>=
#if defined(SHAKE_DEBUG)
if (verbose>=1000) {
	int i;
	double sum;
	decluster_edge_t *edge = mst->edge;
	printf("mst len is %f\n",mst_len);
	printf("mst has %d edges\n",mst->n);
	for (i=0, sum=0.0;i<mst->n;i++) {
		printf(" cost(%d,%d)=%f\n",i,(i+1)%n,cost(i,(i+1)%n));
		printf("   cost(%d,%d)=%f\n",
			edge[i].city[0],
			edge[i].city[1],
			(double)edge[i].cost);
		sum += edge[i].cost;
	}
	printf("mst computed len is %f\n",mst_len);
}
#endif

@ The first bug was discovered by looking at the output.  Some points
moved in absolute position way more than they should have. The
problem turned out to be not subtracting |n| when mapping |T_prime|
index
|branch-T_prime->edge|  into the corresponding minimum spanning tree
edge index in |mst|.

@<Debug: output (outdated?) MST edge info@>=
#if defined(SHAKE_DEBUG)
printf("mst edge (%f,%f) to (%f,%f) length %f\n",
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[smaller_end]].x[0],
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[smaller_end]].x[1],
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[1-smaller_end]].x[0],
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[1-smaller_end]].x[1],
mst->edge[branch-T_prime->edge-n].cost);
#endif

@ This was also used to swat that offset bug.
@<Debug: show anchor and angle@>=
#if defined(SHAKE_DEBUG)
printf(" angle is %f\n",angle);
printf(" anchor at (%f,%f)\n",anchor_x, anchor_y);
#endif

@
@<Debug: show current position of the city@>=
#if defined(SHAKE_DEBUG)
printf("   city at (%f,%f)\n",tsp_instance->coord[city].x[0],
				tsp_instance->coord[city].x[1]);
#endif

@
@<Debug: show new position of the city@>=
#if defined(SHAKE_DEBUG)
printf("   city now at (%f,%f)\n",tsp_instance->coord[city].x[0],
				tsp_instance->coord[city].x[1]);
#endif


@ This is a kludgy way to check the kludge relationship we rely on between
|mst| and |T_prime|.
@^kludge@>
@<Debug: check that |mst| and |T_prime| match up@>=
#if defined(SHAKE_DEBUG)
{int i;
for (i=0;i<n-1;i++) {
	errorif(mst->edge[i].cost != T_prime->edge[i+n].cost,
		"Bug: Icky kludgy part at %d\n",i);
}
}
#endif

@*Index.
