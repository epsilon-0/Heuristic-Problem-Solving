


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
@s benchmark_t int
@s prng_kind_t int

\def\9#1{{\sl #1}}
{\obeylines
$Log: jitter.w,v $
Revision 1.8  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.7  1997/12/17 20:48:59  neto
Added seed to the comment of output TSPLIB instance.

Revision 1.6  1997/12/17 16:39:33  neto
In usage, added output of defaults for -d and -a.

Revision 1.5  1997/12/13 22:24:38  neto
This appears to work.
:)

Revision 1.4  1997/12/13 19:43:04  neto
First draft finished.

Revision 1.3  1997/12/12  18:26:09  neto
Command line parameters are now parsed.  I just give up my hands
w.r.t. getting gcc -ansi to compile cleanly without it getting in a huff
about getopt being undeclared.  I dunno.

Revision 1.2  1997/12/06 21:01:24  neto
Defined the commandline parameters.  Now I need to code them up.

Revision 1.1  1997/12/04  22:16:41  neto
Initial revision

}

@*JITTER.
This program adds jitter to the coordinates in a TSPLIB instance of the
traveling salesman problem.
It is useful for confirming that the difficulties the Lin-Kernighan
has with particular clustered instances are not just a fluke.

@ The outline of this program is as follows.
@c

const char *prog_name = "jitter";
const char *jitter_rcs_id = "$Id: jitter.w,v 1.8 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;
@<Type definitions@>@;

@<Global variables@>@;
@<Module variables@>@;
@<Module subroutines@>@;


int main(int argc, char **argv) 
{
	@<Basic initialization@>@;
	@<Process the command line@>@;
	@<Read the instance@>@;
	@<Preprocess the instance@>@;
	@<Add jitter to the instance@>@;
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
command-line specified seed.  The default seed is, of course, $42$.

Option \type{-R} takes a mandatory string parameter naming a random
number generator algorithm.  Currently, the algorithms are 
\type{gb\_\,flip}, the generator provided with the Stanford GraphBase,
and \type{nrand48}, the 48-bit linear congruential generator provided
by most variants of Unix.  If the given name does not match either, 
\type{gb\_\,flip}
is substituted.
@^Unix@>
@:Stanford GraphBase@>

Option \type{-g} indicates that the amount of jitter at a node should be
based on the lengths of all edges in the minimum spanning tree.
The letter `g' indicates `global'.

Option \type{-l} indicates that the amount of jitter at a node should be
based on the lengths of minimum spanning tree edges incident upon that
node.  This option is the opposite of option \type{-g}.
Option \type{-l} is the default.
The letter `l' indicates `local'.

Given the set of edge lengths on which to base the amount of jitter,
options \type{-m}, \type{-a}, and \type{-M} indicate whether to choose the
minimum, average (mean), or maximum of that set of lengths as the benchmark
length (for that node, if it's a local set).  The default is to 
use the average.

Option \type{-d} takes a mandatory numeric parameter $d$.  
Given a benchmark length $l$ for a node $u$, we move $u$ 
in random direction by a distance drawn from a normal distribution
with mean of 0 and a standard deviation of $l \cdot d$.
It is harmless if the argument happens is negative; in that case the
deviation goes in the opposite direction, which is undetectable from
a statistical standpoint.
The default for $d$ is 1/8.

@<Process the command line@>=
seed = 42L;
generator_kind = PRNG_DEFAULT;
domain = DOMAIN_GLOBAL;
benchmark_kind = BENCHMARK_AVG;
deviation_factor = 1.0/8;
#if HAVE_GETOPT
while(1) {
	extern char *optarg;
	extern int getopt(int,char*const*,const char*);
	const int opt = getopt(argc,argv,"s:hR:glmaMd:");
	if (opt==EOF) break;
	switch(opt) {
	case 's': seed = atol(optarg); @+ break;
	case 'h': usage(argv);@+  exit(0); @+ break;
	case 'R': generator_kind = prng_kind_from_name(optarg);@+  break;
	case 'g': domain = DOMAIN_GLOBAL;@+  break;
	case 'l': domain = DOMAIN_LOCAL;@+  break;
	case 'm': benchmark_kind = BENCHMARK_MIN;@+  break;
	case 'a': benchmark_kind = BENCHMARK_AVG;@+  break;
	case 'M': benchmark_kind = BENCHMARK_MAX;@+  break;
	case 'd': deviation_factor = atof(optarg);@+  break;
	case ':': errorif(1,"Some option is missing an argument");@+  break;
	case '?': usage(argv);@+  errorif(1,"Unrecognized option");@+  break;
	default: errorif(1,"getopt returned character 0%o",opt);
	}
}
#endif /* |HAVE_GETOPT| */

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
"Add jitter to TSPLIB instances.\n"@;
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
" -h           : Output this help and quit\n"@|
" -R <gen-alg> : Use the named random number genarator.\n"@|
"                <gen-alg> is one of:");
{int i; for (i=0;i<PRNG_NUM_KINDS;i++) { 
	printf(" %s",prng_name_from_kind(i)); 
}
}
printf("\n"@|
" -s <seed>    : Use integer <seed> as the random number seed\n"@|
" -g           : Make all edges in minimum spanning tree the\n"@|
"                domain edges for each node\n"@|
" -l           : Make all edges incident upon node u in a minimum\n"@|
"                spanning tree for the graph be domain edges for u\n"@|
"                (not well defined, I know)\n"@|
"                -l is the default\n"@|
" -m           : <benchmark-len> is minimum of domain edge lengths\n"@|
" -a           : <benchmark-len> is average (mean) of domain edge lengths.\n"@|
"                This is the default.\n"@|
" -M           : <benchmark-len> is maximum of domain edge lengths\n"@|
" -d <f>       : Signed jitter distance is normally distributed with mean\n"@|
"                0 and standard deviation <f>*<benchmark-len>\n"@|
"                Default <f> is 0.125\n"@|
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

@ We need to declare the command line parameters.
@<Module variables@>=
static long seed;
static prng_kind_t generator_kind;
static domain_t domain;
static benchmark_t benchmark_kind;
static double deviation_factor;

@
@<Type definitions@>=
typedef enum { BENCHMARK_MIN, BENCHMARK_AVG, BENCHMARK_MAX } benchmark_t;
typedef enum { DOMAIN_LOCAL, DOMAIN_GLOBAL} domain_t;

@ Module \module{READ} has a reading routine that does the right thing.
The first argument is the file stream from which to read the instance.
The second argument is the file stream, if any, on which to put 
debugging output in PostScript.
@^PostScript@>

@<Read the instance@>=
tsp_instance = read_tsp_file(stdin,NULL);
n = tsp_instance->n;

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

@<Global variables@>=
int noround=1;

@ 
Benchmark distances are always related to the minimum spanning tree, so
we need to build the tree.  It just so happens that the declustering
module already knows how to build minimum spanning trees.

If the domain is global, we can precompute the benchmark distance once.

@<Preprocess the instance@>=
E2_create(tsp_instance);
mst = decluster_setup(n);
mst_len = decluster_mst(tsp_instance,mst);
@<Verbose: check the MST@>@;
errorif( n != 1 + mst->n, "Wrong number of edges in MST: %d instead of %d",
	mst->n, n-1);
switch( domain ) {
case DOMAIN_GLOBAL:
	@<Compute the global benchmark length@>@; @+ break;
case DOMAIN_LOCAL:
	@<Find the neighbourhoods@>@;
	@<Compute the local benchmark lengths@>@;
	break;
default: errorif(1,"Bug!");
}

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
#include "length.h"
#include "decluster.h"


@ The global benchmark length is either the minimum, mean, or maximum
of all the lengths in the MST.

@d min(X,Y) ((X)<(Y) ? (X) : (Y))
@d max(X,Y) ((X)>(Y) ? (X) : (Y))

@<Compute the global benchmark length@>=
switch( benchmark_kind ) {
case BENCHMARK_AVG: global_benchmark_len = mst_len / mst->n;
	break;
case BENCHMARK_MIN:
	{ int i; 
		global_benchmark_len = mst->edge[0].cost;
		for (i=1;i<mst->n;i++) {
			global_benchmark_len = min(global_benchmark_len,mst->edge[i].cost); 
		}
	}
	break;
case BENCHMARK_MAX:
	{ int i; 
		global_benchmark_len = mst->edge[0].cost;
		for (i=1;i<mst->n;i++) {
			global_benchmark_len = max(global_benchmark_len,mst->edge[i].cost); 
		}
	}
	break;
default: errorif(1,"Bug!");
}

@
@<Module variables@>=
static double global_benchmark_len = -1.0;	/* This will be overwritten. */


@  The MST is presented as an array of edges. We need to construct local
neighbourhoods for each node.  
Since the tree might be quite irregular, we weave together all the
neighbour hood lists together in a single array.
Entry |nbhd[i]| is the head of the linked list of names of cities
that are neighbours of city |i|.

Since there are |n-1| edges, there
are |2n-1| endpoints to store in neighbourhood lists.  

@<Find the neighbourhoods@>=
{ int i, next_nbhd_link;
nbhd = new_arr_of(nbhd_link_t *,n);
nbhd_link = new_arr_of(nbhd_link_t,2*mst->n);
for (i=0; i < n ; i++) nbhd[i] = NULL;
next_nbhd_link = 0;

for (i=0; i < n; i++) {
	const int u = mst->edge[i].city[0];
	const int v = mst->edge[i].city[1];
	nbhd_link[next_nbhd_link].next = nbhd[u];
	nbhd_link[next_nbhd_link+1].next = nbhd[v];
	nbhd[u] = &nbhd_link[next_nbhd_link];
	nbhd[v] = &nbhd_link[next_nbhd_link+1];
	next_nbhd_link += 2;
	nbhd[u]->neighbour = v;
	nbhd[v]->neighbour = u;
}
errorif(next_nbhd_link != 2*mst->n,"Bug!");
}

@
@<Clean up the data structures@>=
free_mem(nbhd);
free_mem(nbhd_link);

@
@<Module headers@>=
#include "memory.h"

@
@<Module variables@>=
static nbhd_link_t *nbhd_link, **nbhd=NULL;

@
@<Type definitions@>=
typedef struct nbhd_link_s {
	int neighbour;
	struct nbhd_link_s *next;
} nbhd_link_t;

@ We store the local benchmark lengths in array |local_benchmark_len|.

This code is not as scary at it looks.  It's just three list traversals,
with an easy reduction function on each.

@<Compute the local benchmark lengths@>=
local_benchmark_len = new_arr_of(double,n);
{int i;
nbhd_link_t *nb;
switch(benchmark_kind) {
case BENCHMARK_AVG:
	for(i=0;i<n;i++) {
		double sum=0.0; int count=0;
		for(nb=nbhd[i];nb;nb=nb->next) {sum+=cost(i,nb->neighbour);count++;}
		local_benchmark_len[i]=sum/count;/* Each city has at least one neighbour. */
	}
	break;
case BENCHMARK_MIN:
	for(i=0;i<n;i++) {	/* Each city has at least one neighbour. */
		double len=cost(i,nbhd[i]->neighbour);
		for(nb=nbhd[i];nb;nb=nb->next) {len=min(len,cost(i,nb->neighbour));}
		local_benchmark_len[i]=len;
	}
	break;
case BENCHMARK_MAX:
	for(i=0;i<n;i++) {	/* Each city has at least one neighbour. */
		double len=cost(i,nbhd[i]->neighbour);
		for(nb=nbhd[i];nb;nb=nb->next) {len=max(len,cost(i,nb->neighbour));}
		local_benchmark_len[i]=len;
	}
	break;
}
}

@
@<Module variables@>=
static double *local_benchmark_len=NULL;

@
@<Clean up the data structures@>=
free_mem(local_benchmark_len);










@
We've precomputed the benchmark distances, so adding jitter just entails
sampling normal distributions and scaling them right.
Since all the benchmark distances are stored, we can modify the coordinates
in place.

It would be very easy to extend this to more dimensions.

@<Add jitter to the instance@>=
@<Initialize the random number generator@>@;
{ int i;
for (i=0;i<n;i++) {
	const double len = (domain==DOMAIN_LOCAL?local_benchmark_len[i]:global_benchmark_len);
	const double stddev=len*deviation_factor;
	const double dx = prng_normal(jitter_prng,0.0,stddev);
	const double dy = prng_normal(jitter_prng,0.0,stddev);
	tsp_instance->coord[i].x[0]+=dx;
	tsp_instance->coord[i].x[1]+=dy;
}
}

@ 
@<Initialize the random number generator@>=
jitter_prng = prng_new(generator_kind,seed);

@
@<Module variables@>=
static prng_t *jitter_prng;

@ When writing out the instance again, we keep the same edge-weight
type, even though this might not jibe well with the fact we didn't use
rounded distances.

However, we do the command line parameters to the comment.

The |write_tsp_file| belongs to module \module{READ}.

@<Write the instance@>=
{ 
char *old_comment= tsp_instance->comment;
char *new_comment = new_arr_of(char,200+strlen(old_comment));
sprintf(new_comment,"%s | %s -R %s -s %ld %s %s -d %g",
old_comment,
prog_name,
prng_name_from_kind((int)generator_kind),
seed,
(domain==DOMAIN_LOCAL?"-l":"-g"),
(benchmark_kind==BENCHMARK_MIN?"-m":
 (benchmark_kind==BENCHMARK_AVG?"-a":
  (benchmark_kind==BENCHMARK_MAX?"-m":
   (errorif(1,"Bug!"),"unknown")
  )
 )
),
deviation_factor);
free_mem(old_comment);
tsp_instance->comment = new_comment;
write_tsp_file(tsp_instance,stdout);
}

@*Verbose output.
@<Verbose: check the MST@>=
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

@*Index.
