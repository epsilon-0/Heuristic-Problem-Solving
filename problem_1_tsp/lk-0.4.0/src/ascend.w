


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
$Log: ascend.w,v $
Revision 1.28  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.27  1998/05/30 18:51:12  neto
Make it stop after 1500 iterations.  That's just enough, ok?

Revision 1.26  1998/05/23 19:20:17  neto
Implement combination of previous two degree components.  Another
stopping criterion (stop when close enough to upper bound: 0.1 percent)
Clean up output a bit so it is more easily digested by gnuplot

Revision 1.25  1998/05/23 18:10:46  neto
sqrt in the normalizer is definitely the *wrong* thing!
Tightened the t parameter bound to 1e-4

Revision 1.24  1998/05/23 17:50:46  neto
Now it compiles and links into lk.

Revision 1.23  1998/05/23 16:22:11  neto
Added necessary target len.
Added access to best lambda.
Think about adding convex combination of the last two lambdas.

Revision 1.22  1998/05/23 15:22:50  neto
normalizer should be Euclidean distance.

Revision 1.21  1998/05/23 15:13:21  neto
Switch to a fixed distinguished degree 2 node (number n-1).
This seems "more correct".
Also, added much explanatory documentation about Held-Karp lower bounds.
This should be the only new module added to LK.

Revision 1.20  1998/05/22 20:38:10  neto
Fixed a 1-tree length accounting bug.  Oops.
Better comments, and removed pageno.

Revision 1.19  1998/05/22 20:21:21  neto
This might be completely switched over to the simpler non branch and buond
scheme.  Now I'll read the code again...

Revision 1.18  1998/05/22 18:18:53  neto
Removed more stuff not appropriate to pure Held-Karp lower bounds.

Revision 1.17  1998/05/22 17:59:00  neto
Got rid of double-including of headers...
Got rid of bbnode search tree stuff
Use efficient multiple buffering of lambda vectors.

Revision 1.16  1998/05/21 19:29:35  neto
Fixed up standard CWEB thingies and Log stuff.

Revision 1.15  1998/05/21 19:25:34  neto
More restructuring and comments.
Include standard CWEB goodies.
}

@*Held-Karp lower bounds for the TSP.
In {\sl The Traveling Salesman Problem and Minimum Spanning Trees},
Operations Research, {\bf 18}, pp.~1138--1162, 1970, Michael Held and Richard
Karp described a lower bound for the length of the shortest tour for a
given
graph.  
@^Held, Michael@>
@^Karp, Richard@>

A \term{1-tree} for graph $G$ on $n$ vertices is a spanning subgraph of
$G$ that has $n$ edges.  Since all tours of $G$ span $G$ and have as
many edges as $G$ has vertices, then all tours are 1-trees.
So the weight of a minimum weight 1-tree for $G$ is a lower bound
on the length of a shortest tour of $G$.

Minimum 1-trees are easy to compute.  Let us label the vertices of
$G$ with numbers 0 through $n-1$.  We may as well restrict
our attention to 1-trees in which vertex $n-1$ is of degree 2, since
all tours of $G$ also have this property.
Then a minimum 1-tree is just a minimum spanning tree over the subgraph
induced by vertices 0 through $n-2$, together with the two shortest edges
incident upon vertex $n-1$.

@ Now, the lower bounds one gets with this simple minimum 1-tree scheme
are not very good: they underestimate the optimal tour length by about
a third.  What to do?

Held and Karp describe how to use Lagrange multipliers in this setting.
(Go back to your vector calculus text to recall what Lagrange multipliers
are in general.  I'll describe them in the particular here.)
Instead of computing minimum 1-trees with the basic distance function 
\cost, compute minimum 1-trees with cost function
$\cost_\lambda(i,j) = 
\cost(i,j)+\lambda_i+\lambda_j$, where $\lambda$ is an arbitrary
$n$-dimensional vector over the reals.

How does that help us?  For a given graph, let 
$L(\lambda)$ be the length of a shortest
1-tree using cost function $\cost_\lambda$ and let $T(\lambda)$ be the length
of a shortest tour using the same cost function $\cost_\lambda$.
Then for any real vector $\lambda$, we have 
from before that $$L(\lambda) \le T(\lambda).$$
Now, since
each tour is a 1-tree in which each vertex is of degree 2,  we have
$$T(0)=T(\lambda)-2\sum_i\lambda_i.$$ Note that $T(0)$ is just the
length of a shortest tour with the original cost function.
Substituting for $T(\lambda)$ in the first equation, we get the 
inequality
$$L(\lambda) - 2\sum_i\lambda_i \le T(0).$$

The
Lagrange multipliers have given us
an extra $n$ degrees of freedom.
The task then becomes finding a $\lambda$ that makes this inequality
as tight as possible.
Held and Karp proved that the objective function is convex over the
space of possible values for $\lambda$, and prove convergence for
an iterative ascent algorithm with certain parameters.

The Held-Karp lower bound for the TSP is the
1-tree lower bound with optimal Lagrange multitpliers.
Held-Karp lower bounds are {\it very\/} tight, often getting
within 0.5\% of the length of a shortest tour for the graph.

@ In a a second paper, {\sl The Traveling Salesman Problem and Minimum Spanning
Trees II}, Mathematical Programming, {\bf 1}, pp.~6--25, 1971, Held and
Karp described a subgradient optimization method for optimizing the
lower bound.  That is the algorithm implemented here.
@^Held, Michael@>
@^Karp, Richard@>


@*Subgradient optimization.
Held and Karp described a convenient and effective
method for approximating the Held-Karp
lower bound to the TSP.  
The algorithm is to refine the $\lambda$ vector iteratively.
Each iteration consists of the following steps:
compute a 1-tree with the durrent $\lambda$ vector, then update 
$\lambda_i$ if vertex $i$ in the 1-tree is not of degree 2.
If the degree of vertex $i$ is 1, then decrease $\lambda_i$.  If the
degree of vertex $i$ is greater than 2, then increase $\lambda_i$.
@^Held, Michael@>
@^Karp, Richard@>

This update rule has the effect of making well-connected vertices less
attractive next time around, and under-connected vertices more attractive.
One can think of this as ``warping'' the local space around each vertex.
Rather cool, actually.
@^cool@>
@^warping local space@>

@
This iterative algorithm belongs to the class of optimization algorithms
known as \term{subgradient optimization}.  Held and Karp prove that
the optimization space explored here is well-behaved (convex). 
As a consequence, with parameters in the right range, this iterative
procedure is guaranteed to converge.  (As long as the floating point
arithmetic holds out, anyway$\ldots$)

Of course, we need practicality too.  All lower bounds computed
by this procedure are valid, and are thus valid approximations
to \term{the} Held-Karp lower bound.  We'll live with taking
the
best lower bound we find here and declaring it as ``good enough''.

@ The outline of this module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Module variables@>@;
@<Early module subroutines@>@;
@<Module subroutines@>@;
@<Subroutines@>@;

@ We need some standard stuff.
@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

@ We need lots of stuff from other header files included with LK.
@<Module headers@>=
#include "error.h"
#include "length.h"
#include "read.h"	/* For |cost| and |tsp_instance_t|. */
#include "lk.h"
#include "memory.h"
#include "decluster.h"

@ The exported interface is contained in the {\tt ascend.h} header file,
which has the following form.

@(ascend.h@>=
#if !defined(_ASCEND_H_)
#define _ASCEND_H_
@<Exported subroutines@>@;
#endif


@ For consistency, we include our own header.
@<Module headers@>=
#include "ascend.h"

@ The setup routine allocates space for the best setting of the $\lambda$
vector. It also initializes |n|, a local copy of the number of vertices
in the instance.

In case anyone asks for the Lagrange multipliers we used to find
a particular lower bound, we'd better be able to tell them.
That's what |best_lambda| is all about.

To save on scans, we use double-buffering for the $\lambda$ vector,
storing both a |read_lambda| vector and a |write_lambda| vector.


@<Subroutines@>=
void
ascend_setup(int the_n)
{
	n = the_n;
	best_lambda = new_arr_of(double,n);
	read_lambda = new_arr_of(double,n);
	write_lambda = new_arr_of(double,n);
	@<Other allocations@>@;
	total_iter = -1;
}

@ The cleanup routine undoes the effect of the setup routine.

@<Subroutines@>=
void
ascend_cleanup(void)
{
	free_mem(best_lambda);
	free_mem(read_lambda);
	free_mem(write_lambda);
	mem_deduct(sizeof(double)*3*n);
	@<Other deallocations@>@;
	n = 0;
	total_iter = -1;
}

@ We give the outside world read-only access to |best_lambda|.
@<Subroutines@>=
double * const
ascend_best_lambda(void)
{
	return best_lambda;
}

@ These routines need to be announced to the world.
@<Exported subroutines@>=
void ascend_setup(int the_n);
void ascend_cleanup(void);
double * const ascend_best_lambda(void);

@ We need to declare the local state.
@<Module variables@>=
static int n=0;
static int total_iter = -1;
static double *best_lambda=NULL, *read_lambda=NULL, *write_lambda=NULL;

@ We also record the degree of each vertex in the 1-tree.
Value |degree_less_2[i]| is two less than the degree of vertex $i$.

We also record the previous iteration's degree vector as
|degree_less_2_old|.

@<Other allocations@>=
degree_less_2 = new_arr_of(int,n);
degree_less_2_old = new_arr_of(int,n);

@
@<Other deallocations@>=
free_mem(degree_less_2); mem_deduct(sizeof(int)*n);
free_mem(degree_less_2_old); mem_deduct(sizeof(int)*n);

@
@<Module variables@>=
static int *degree_less_2=NULL;
static int *degree_less_2_old=NULL;


@ The \term{normalizer} of a 1-tree is a measure of how far off the
1-tree is from being a tour.  It is zero when the 1-tree is a tour,
and grows the farther (degree-wise) the 1-tree is from a tour.

In fact, it is the square of the Euclidean distance between the |degree_less_2| 
vector
and the origin. We're trying to drive the |degree_less_2| vector
to the origin.

@<Module subroutines@>=
static double normalizer(int n, int *degree_less_2);
static double 
normalizer(int n, int *degree_less_2)
{
	int i;
	double l;
	for (l=0.0,i=0;i<n;i++) {
		l += degree_less_2[i]*degree_less_2[i];
	}
	return l;
}

@ Given a step size factor $t$, procedure |update_lambda|
updates $\lambda$ to make each
vertex either more or less attractive next time around, depending
on whether that vertex is currently over-connected or under-connected.

We implement the double-buffering here too: read from |read_lambda|,
write to |write_lambda|.

@<Module subroutines@>=
static void update_lambda(int n, double t, int *degree_less_2, int
*degree_less_2_old, double
	*read_lambda, double *write_lambda);
static void
update_lambda(int n, double t, int *degree_less_2, int *degree_less_2_old,
	double *read_lambda, double *write_lambda)
{
	int i;
	const double recent_share=0.75;  /* Between 0 and 1, nearer 1. */
	const double ta = t*recent_share, tb = t*(1.0-recent_share);
	for ( i=0 ; i<n ; i++ ) {
		write_lambda[i] = read_lambda[i] 
			+ ta * degree_less_2[i] + tb * degree_less_2_old[i];
	}
}

@ Once we've used |degree_less_2| for updating, we rotate it with
|degree_less_2_old|.

@<Rotate the degree vectors@>=
{
	int *t = degree_less_2; 
	degree_less_2 = degree_less_2_old; 
	degree_less_2_old = t; 
}

@ Here we come to the core of  this module: procedure |ascend_alpha_beta|.
It performs the subgradient ascension, modifying the $\lambda$ vector as we go.

Value |upper_bound_len| is the value of an upper bound on the tour length.
It is used as a parameter in the step size.

Its return value is the length of the best lower bound discovered.

It takes three arguments.  The first is |n|, the number of vertices
in the graph.  The second and third are parameters controlling the
convergence of the ascent.  The update rule used is
$\lambda^{(k+1)}_i = \lambda^{(k)}_i + \alpha\cdot\beta^k\cdot {\rm
deg}(i)/\rho$, where $\rho$ is a scaling factor.
That is, the step size 
begins with a multiplier of $\alpha$ and
decays each iteration by a factor of $\beta$.

@<Subroutines@>=
length_t
ascend_alpha_beta(const int n, double upper_bound_len, double alpha, double beta)
{
	extern int verbose;
	int i, best_iter, iter=-1, new_is_best;
	double t, norm, best_lower_bound=0.0, onetree_len;
	errorif(LENGTH_TYPE_IS_INTEGRAL,
		"Held-Karp lower bound computations require length_t to be a "
		"floating point type.  Sorry, but you have to recompile.");
	errorif(n<3,"ascend: n=%d < 3\n",n);
	errorif(beta>=1.0,"ascend: beta=%f > 1\n",beta);
	errorif(beta<=0,"ascend: beta=%f <= 0\n",beta);
	
	for (i=0;i<n;i++) degree_less_2_old[i]=read_lambda[i]=0.0;
	best_lower_bound = 0.0;
	while (1) {
		total_iter++, iter++;
		@<Compute a new |onetree| and its length |onetree_len|@>@;
		@<Compute |degree_less_2| from |onetree|@>@;
		new_is_best = ( onetree_len > best_lower_bound );
		norm = normalizer(n, degree_less_2);

		@<Update |best_lower_bound|@>@;
		@<|break| if we're close enough to |upper_bound_len|@>@;
		@<|break| if we found a tour@>@;
		@<|break| if we've run too many iterations@>@;

		t = alpha * (upper_bound_len - onetree_len)/norm;
		@<Verbose: print new 1-tree weight@>@;
		@<|break| if $t$ is too small@>@;
		@<|break| if the best 1-tree length is old@>@;

		update_lambda( n, t, degree_less_2, degree_less_2_old, read_lambda, write_lambda );
		alpha *= beta;	/* See Held Karp, 1971, Lemma 3 */
		@<Verbose: show 1-tree and flush@>@;
		@<Permute the $\lambda$ vectors@>@;
		@<Rotate the degree vectors@>@;
	}
	return best_lower_bound;
}

@ The step size parameters can either be dictated by theory as given
by Held and Karp, or by practice, as given by Held and Karp or any
other researcher who has implemented this algorithm$\ldots$.

As I come back to this code after about 3 years, I'll leave this pretty
much well alone.  Except I will say that a larger $\alpha$ produces 
larger steps, and often overshooting if you have a bad upper bounding
length.  The scaler $\beta$ should be less than 1; the closer it is to 1, the
slower the convergence, and the slower the run.

Apparently, it is wise to have different rules depending on whether you
already have a good upper bound on the length of the optimal tour.

Here are some good defaults for a slow but accurate ascent.  Call
|ascend| instead of |ascend_alpha_beta| in order to get these values.

@<Subroutines@>=
length_t 
ascend(const int n, double upper_bound_len)
{
	return ascend_alpha_beta(n,upper_bound_len,1.5,0.995);
}

@
@<Exported subroutines@>=
length_t ascend(const int n, double upper_bound_len);
length_t ascend_alpha_beta(const int n, double upper_bound_len, double alpha, double beta);

@ We need an array of $n$ edges to hold the 1-tree.
@<Other allocations@>=
onetree=new_arr_of(decluster_edge_t,n);

@
@<Other deallocations@>=
free_mem(onetree); mem_deduct(n*sizeof(decluster_edge_t));

@
@<Module variables@>=
static decluster_edge_t *onetree=NULL;

@  The 1-tree length we compute must be discounted by $2\cdot\sum \lambda_i$ in
order for it to be comparable to tour lengths.

@<Compute a new |onetree| and its length |onetree_len|@>=
{
const double len = compute_onetree(onetree);
double lambda_2 = 0.0;
int i;
for (lambda_2 = 0.0, i=0; i<n; i++) lambda_2 += 2*read_lambda[i];
onetree_len = len - lambda_2;
}



@ If by some miracle we find a tour, then we stop right away and return
that result. But since we don't trust floating point numbers, we 
recompute the tour length first.

@<|break| if we found a tour@>=
if ( norm == 0.0 ) {
	@<Verbose: found a tour@>@;
	for ( onetree_len = 0.0, i=0;i<n;i++)
		onetree_len += onetree[i].cost;
	best_lower_bound = onetree_len; /* just in case imprecision screwed up |best_lower_bound|*/
	@<Verbose: show tour graphically@>@;
	break;
}

@ If we get within a specified percentage, say 0.1\% of the upper bound,
then let's declare victory.


@ In Held-Karp lower bounds, don't activate this code either$\ldots$
@<|break| if the best 1-tree length is old@>=
#if 0
if ( is_random_dist_matrix ) {
	if ( iter > 1000 &&  iter - best_iter > 5 && iter - best_iter < 8 ) {
		if ( verbose >= 75 ) 
			printf("#  Ascend: stopping criteria met:  best is old\n");
		break;
	}
} else {
	if ( iter > 1000 &&  iter - best_iter > 5 ) {
		if ( verbose >= 75 ) 
			printf("#  Ascend: stopping criteria met:  best is old\n");
		break;
	}
}
#endif



@ I want the Held-Karp lower bounds to be as good as possible, so we
don't want to activate this code.
@<|break| if we've run too many iterations@>=
if ( iter > 1500 ) {
	if ( verbose >= 75 )
		printf("#  Ascend: Iterations exceeded 1500\n");
	break;
}


@
@<|break| if $t$ is too small@>=
if ( t < 1e-2 ) {
	if ( verbose >= 75 )
		printf("#  Ascend: stopping criteria met: t < 0.01 \n");
	break;
}

@  We also remember when the best iteration happened so we can later
tell if has been a long time ago.

@<Update |best_lower_bound|@>=
if ( new_is_best ) {
	best_lower_bound = onetree_len;
	best_iter = iter;
}

@ Within a tenth of a percent is close enough for me!

@<|break| if we're close enough to |upper_bound_len|@>=
if ( new_is_best ) {
	double err = (upper_bound_len - onetree_len)/upper_bound_len;
	if ( err < 0.001 ) { 
		if ( verbose >= 75 )
			printf("#  Ascend: stopping criteria met: %.2f%% away from upper\n",err*100);
		break;
	}
}

@
The update scheme for the $\lambda$ vector is as follows, 
with $B$ representing |best_lambda|,
$R$ representing |read_lambda| (the $\lambda$ vector used to construct the
current 1-tree) and $W$ representing |write_lambda|, the new $\lambda$
used for the next round.  If we get a new best value, then 
we preserve |best_lambda| with the assignment
$(B,R,W) := (B,W,R)$.  If we don't get a new best value, then
we save |read_lambda| in |best_lambda| with the assignment
$(B,R,W) := (R,W,B)$.   In both cases, the |write_lambda| gets moved to
|read_lambda| for the next round.

@<Permute the $\lambda$ vectors@>=
{
double *b=best_lambda, *r=read_lambda, *w=write_lambda;
if ( new_is_best ) {
	best_lambda=b;
	read_lambda=w;
	write_lambda=r;
} else {
	best_lambda=r;
	read_lambda=w;
	write_lambda=b;
}
}


@*Computing 1-trees.
A 1-tree on a graph with $n$ vertices is a spanning subgraph with $n$
edges. (Note that a 1-tree is not a tree.)
All tours are 1-trees, so the heaviest tour is at least as heavy
as the shortest 1-tree.

We will compute minimum 1-trees by computing an $n-2$ edge minimum spanning
tree 
over the subgraph induced by the first $n-1$ vertices, then add the
two shortest edges to the last vertex, the vertex labeled $n-1$.

@ Now, module \module{DECLUSTER} already has machinery for computing
minimum spanning trees.   Let's take advantage of it here.

For one thing, that means we have to use the data structures defined
there.  In particular, we require |onetree| to be an array of
$n$ edges, each stored as a |decluster_edge_t| value.

We also require the Lagrange multiplier $\lambda$ vector
to be stored in |read_lambda|.

We return the length of the 1-tree under the given cost function.
We don't discount by $\sum_i \lambda_i$ like one should before comparing
to a tour length.

@<Module subroutines@>=
static length_t compute_onetree(decluster_edge_t *onetree);
static length_t
compute_onetree(decluster_edge_t *onetree)
{
	length_t len;
	@<Compute a MST over the first $n-1$ vertices@>@;
	@<Now add the two shortest edges from vertex $n-1$@>@;
	return len;
}

@ Note that although |onetree| points to an array of $n$ edges, we only
tell the MST routine about the first $n-2$ of them.

@<Compute a MST over the first $n-1$ vertices@>=
{
decluster_tree_t T;
T.n = n-2;
T.edge = onetree;
len = decluster_mst_custom(&T,work_from,work_dist,custom_cost);
}

@ The custom MST routine requires two length $n-1$ buffers: one of |int|
values
and another of |double| values.    We prefer to do the allocation only
once, not every time we compute a MST.
@<Other allocations@>=
work_from = new_arr_of(int,n-1);
work_dist = new_arr_of(double,n-1);

@
@<Other deallocations@>=
free_mem(work_from);
free_mem(work_dist);
mem_deduct((n-1)*(sizeof(int)+sizeof(double)));

@
@<Module variables@>=
static int *work_from=NULL;
static double *work_dist=NULL;


@ The custom cost function is just the ordinary cost function,  but
with Lagrange multipliers.

@<Early module subroutines@>=
static length_t
custom_cost(int i, int j)
{ 
	return cost(i,j)+read_lambda[i]+read_lambda[j];
}


@ To add the two shortest edges we first need to find them.
Array |short_to| holds the two cities to which vertex $n-1$ is closest,
with the closest in position 0.  Array |short_dist| holds the distances
to those cities.

@<Now add the two shortest edges from vertex $n-1$@>=
{ const int v=n-1;
int i, short_to[2];
length_t short_dist[2]={INFINITY,INFINITY};
for (i=0;i<v;i++) {
	const length_t di=custom_cost(v,i);
	if ( di < short_dist[0] ) {
		short_to[1]=short_to[0];
		short_dist[1]=short_dist[0];
		short_to[0]=i;
		short_dist[0]=di;
	} else if ( di < short_dist[1] ) {
		short_to[1]=i;
		short_dist[1]=di;
	}
}
onetree[n-2].city[0]=v;
onetree[n-2].city[1]=short_to[0];
onetree[n-2].cost=short_dist[0];
onetree[n-1].city[0]=v;
onetree[n-1].city[1]=short_to[1];
onetree[n-1].cost=short_dist[1];
len += short_dist[0] + short_dist[1];
}

@ Computing degrees is pretty simple, requiring one pass over the |onetree|
array.

@<Compute |degree_less_2| from |onetree|@>=
{ int i;
for (i=0;i<n;i++) degree_less_2[i]=-2;
for (i=0;i<n-1;i++) {
	degree_less_2[onetree[i].city[0]]++;
	degree_less_2[onetree[i].city[1]]++;
}
}


@*Verbose.
@<Verbose: print new 1-tree weight@>=
if ( verbose >= 100  ) {
	printf("%d %f # 1-tree weight iter = %d L(l) t == %f alpha = %f\n",
		total_iter,onetree_len,iter, t,alpha);
	fflush(stdout);
}

@
@<Verbose: show 1-tree and flush@>=
#if 0
if ( total_iter==0 && verbose >=100)
	show_onetree( debug_ps, "First 1-tree, lambda==0 vector", n, NULL, edge);
else if ( verbose >= 500 )
	show_onetree( debug_ps, NULL, n, NULL, edge);

if (verbose) fflush(stdout);
#endif


@
@<Verbose: found a tour@>=
#if 0
if ( verbose >= 50 )
	printf("#  Ascend: Page %% total_iter %d Found a tour of length %f\n", 
		total_iter, (float)(onetree_len));
#endif


@
@<Verbose: show tour graphically@>=
#if 0
if ( verbose >= 100 ) {
	char s[100];
	sprintf(s,"Tour length %f",(float)onetree_len);
	show_onetree( debug_ps, s, n, NULL, edge);
}
#endif

@*Index.
@^easter eggs@>
