



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

\def\mybr{\hbox{}\hfill\hbox{}\penalty-10000\relax}
\def\myverb#1{\noindent{\tt\obeyspaces\relax #1}}

% Started coding: Fri Feb  7 11:13:57 EST 1997
%from the sier.w skeleton I had already created.
{\obeylines
$Log: ifs.w,v $
Revision 1.19  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.18  1997/09/27 18:06:44  neto
Fixed RCS log behaviour.

 Revision 1.17  1997/08/15  20:18:25  neto
 Added Index major section.

 Revision 1.16  1997/05/16  20:41:22  neto
 Include <config.h>

 Revision 1.15  1997/02/19  17:50:35  neto
 Fixed the min to max for bound on number of throwaway steps.

 Revision 1.14  1997/02/18  20:05:53  neto
 Checked the section 3.8.2 of Barnsley.  I was right.

 Revision 1.13  1997/02/18  19:16:16  neto
 Added second tropical fish --- with more concentration.

 Revision 1.12  1997/02/10  21:53:01  neto
 Small formatting improvements.

 Revision 1.11  1997/02/10  21:22:29  neto
 Use psfig instead of psbox.
 psbox trashes the TOC somehow.  psfig does not.

 Revision 1.10  1997/02/10  21:01:16  neto
 Improved index entry for Barnsley.

 Revision 1.9  1997/02/10  20:57:06  neto
 Light editing, and added tropical fish.

 Revision 1.8  1997/02/07  23:45:40  neto
 Added a couple of figures.
 Formatting is still stinky.

 Revision 1.4  1997/02/07  22:25:39  neto
 Finished initial coding.  Need to compile and read for English.

 Revision 1.3  1997/02/07  20:44:03  neto
 More typeing.\

 Revision 1.2  1997/02/07  19:33:49  neto
 More writing and editing.

 Revision 1.1  1997/02/07  18:43:15  neto
 Initial revision

}

@*Introduction.
This program generates geometric 
traveling salesman problem (TSP) data based on 
Iterated Function Systems (IFS).
See the development in Michael F.~Barnsley's {\sl Fractals Everywhere}, 
@^Barnsley, Michael Fitzgerald@>
Academic
Press, 1988, or in Kenneth Falconer's 
{\sl Fractal Geometry: Mathematical Foundations and Applications}, John Wiley
and Sons, 1990.
@^Falconer, Kenneth@>

The TSP data is output in the TSPLIB format.  For a description of this simple
data exchange format,
consult the online TSPLIB world wide web home pages at
{\tt http://www.iwr.uni-heidelberg.de:80/iwr/}\penalty-500
{\tt comopt/soft/TSPLIB95/TSPLIB.html}.
A description of an older version of the data set and format
specification is contained in Gerhard Reinelt,
``{TSPLIB} --- A Traveling Salesman Problem Library'',
{\sl ORSA Journal on Computing}, {\bf 3} (4), 1991, pp.~376--384.

@ Heuristics, by their  very
nature, are often poorly understood.  Their asymptotic behaviour
may be very bad in the worst case but very good in practice.  
For example, although the 
Lin-Kernighan heuristic for the traveling salesman problem (TSP) 
has very bad worst case inputs, they are not encountered
in practice.   

Another example is the simplex method for solving
linear programs. There is  an infinite family of inputs that force
the simplex method 
to take an exponential number of steps.  However, despite the
availability of guaranteed-polytime methods for solving linear programs,
the simplex method is
often the method of choice because {\it in  practice\/} bad inputs for simplex 
are rarely encountered.

To understand why this kind of behaviour occurs, especially with heuristics,
we need empirical studies.    
Experiments complement the usual
``worst case'' and ``average case'' analyses, and help to fill out our
knowledge in the ``in practice''  domain.

@ Generating varied data is fundamental to empirical studies of 
algorithms in general 
and of heuristics in particular.
It is important to use data from real applications, if available.  After
all, we'd like to solve real problems.  
But in anticipation of new (or proprietary) applications, we should also 
use artificially generated data from a wide variety of distributions.
Arguments about techniques or algorithms are more convincing when
derived from experience with many classes of data.

%%%inspire more confidence in the performance of heuristics, such
%%%as the Lin-Kernighan heuristic, or in proposed modifications to heuristics,
%%%such as my declustering transformation based on minimum spanning
%%%trees. (What a {\it terrible\/} name!)


With this computer program, I hope to generate a class of interesting TSP 
data based on iterated function systems.  
Iterated function systems can be used to generate point sets with
rich structure at many levels.  These point sets are popularly known
as ``fractals''.  In the introduction to {\sl Fractal Geometry}, Falconer
gives the following fuzzy description of a fractal:
@^Falconer, Kenneth@>

\medskip
\hrule
\emphpar When we refer to a set $F$ as a fractal, therefore, we will typically
have the following in mind.

\itempar{\emphitem{i}$F$ has a fine structure, 
\ie, detail on arbitrarily small scales.}
\itemskip
\itempar{\emphitem{ii}$F$ is too irregular to be described in 
traditional geometrical language.}
\itemskip
\itempar{\emphitem{iii}Often $F$ has some 
form of self-similarity, perhaps approximate or statistical.}\itemskip
\itempar{\emphitem{iv}Usually, 
the `fractal dimension' of $F$ (defined in some way)
is greater than its topological dimension.}\itemskip
\itempar{\emphitem{v}In most cases of 
interest $F$ is defined in a very simple way, 
perhaps recursively.}
\smallskip
\hrule
\medskip

For my present purposes, 
irregularity, item \emphitemnum{ii}, is useful because real life data often 
have
peculiar structure.
Self-similarity and simple characterization, items \emphitemnum{iii} 
and \emphitemnum{v}, 
are useful because they often allow programs that generate fractal data to
be short and efficient.
Item \emphitemnum{iv} is less important because the TSP is 
defined over finite data sets ---we will sample a finite number of
points from each fractal--- so (fractal) dimensionality does not come into
play.  

Similarly, because we take only finite samples, detail on arbitrarily
small scales, item \emphitemnum{i}, is less important.  
However, we must also be aware that this is a characteristic of fractal
data, although it might not appear with smaller point set samples.
% balls into bins... how often do we repeat a sequence?
In particular, detail on extremely small scales might lead to numerical
problems.  I've already encountered numerical nastiness with million-city
{\it uniform\/} geometric  TSP instances, and the problem is potentially
much worse with fractally generated data.   More importantly perhaps
is that real-life data for certain applications 
might not have detail on such a fine scale.  
The
peculiar behaviour emphasized by fractal data sets should be discounted
in these contexts.   Alternatively, one might post-process this fractal
data to get rid of the finer detail.

@ This is a literate C program created with the help of the CWEB system.
The program is broken up into named sections, with automatically generated
numbers and cross-references.  Each section is elaborated in this text at a 
time appropriate for a person to understand what is going on. We are not
at the mercy of the compiler.

The outline of the program is as follows:

@c
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
@<Other includes@>@;
@#
@<Type definitions@>@;

int main(int argc, char**argv) {
	@<|main| variables@>@;
	@<Process the command-line arguments@>@;
	@<Read in the iterated function system@>@;
	@<Output the preamble@>@;
	@<Generate the data@>@;
	return 0;
}

@  There are three mandatory command line parameters.  

The first parameter is a
seed for the pseudo-random number generator.  
It may be varied so that different data sets may be generated
from the same IFS.
I use the random number generator presented by Donald Knuth in
@^Knuth, Donald Ervin@>
{\sl The Stanford GraphBase}.  This generator is portable, fast, and freely
available.
The seed is a |long| integer stored in the variable |seed| and
is used to initialize 
the random number generator with the call |gb_init_rand(seed)|.

The second parameter is |n|, the number of data points to be generated.   
We vary the data set size drawn from a given IFS
to study
the scaling properties of our algorithms.

The third parameter is an instance name.

@<Process the command-line arguments@>=
long seed;
int n;
char *name;
if ( argc != 4 ) {
	fprintf(stderr,
		"Usage: %s <seed> <n> <name>\n",argv[0]);
	exit(1);
}
seed=atol(argv[1]);
n=atoi(argv[2]);
if ( n < 10 ) {
	fprintf(stderr,"Need at least 10 cities; only %d specified.\n",n);
	exit(2);
}
name=argv[3];
gb_init_rand(seed);

@ We need the interface to the random number generator.
@<Other includes@>=
#include "gb_flip.h"	

@ We generate data in the TSPLIB format.  This simple format allows us
to name the instance and provide a comment.  In this case, the comment
consists of the name of this program and its parameters.

Because this program generates two-dimensional Euclidean data, 
the cost function type is fixed as |EUC_2D|.  A TSP-solving program 
is free to ignore this declaration and use
any cost function on the coordinate space.  However, such 
usage should
always be reported as nonstandard, so that we don't compare
apples to oranges.

@<Output the preamble@>=
printf("NAME: %s\n",name);
printf("TYPE: TSP\n");
printf("COMMENT: %s %s %s %s\n",argv[0],argv[1],argv[2],argv[3]);
printf("DIMENSION: %d\n",n);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");

@ It will be helpful to have a data type describing points.  Since
we are working in two dimensions, a |point_t| is a vector of two floating
point numbers.  Since we may want to move to more dimensions later,
we parameterize everything with a compile-time constant |DIMENSIONS|.

@d DIMENSIONS 2
@<Type definitions@>=
typedef double point_t[DIMENSIONS];

@*Iterated functions systems.
An iterated function system is a (finite) collection of contractive maps.
This program deals only with the subclass of IFS over affine maps.
This subclass is still rich enough to encompass a wide range of 
fractals (see Barnsley).
@^Barnsley, Michael Fitzgerald@>

An affine map $(A,v)$ is a linear map, represented by a matrix $A$, 
together with
an offset vector $v$.  
Its action on a vector $u$ is $u \mapsto Au + v$.
An affine map $(A,v)$ is \term{contractive\/} if it shrinks volumes, or
equivalently, if $\size{\det(A)}<1$.


Let's define |affine_t| to be an affine transformation type.  It consists
of the array part |A| and  the vector part |v|.

@<Type definitions@>=
typedef struct { double A[DIMENSIONS][DIMENSIONS], v[DIMENSIONS];} affine_t;

@
The IFS is specified on the standard input stream as a number |n_ifs|
followed by |n_ifs| affine maps.  We use |n_ifs| in allocating arrays
and in counting loops.  

The algorithm to sample from the fractal requires that
a weight be associated with each map.  
The weights are stored
in the array |weight|.
These are normalized and then
used to flip a biased coin, as we'll see.   
To implement biased coin-flipping, we use a second array, |cum_norm_weight|.
Entry |cum_norm_weight[i]| is the sum of the normalized weights of maps
0 through $i$.

Array  |map| stores the affine maps.  

@<|main| variables@>=
int n_ifs;
double *weight, *cum_norm_weight;
affine_t *map;

@ We're now ready see how to read in the data.  Once we know how many
maps to expect, we allocate the arrays.    
Then we read each map and associated weight.

Each map is specified by the matrix part $A$ in row-major order 
(\ie, the column number changes
faster than the row number), followed by the vector part $v$, followed
by the map's  weight.  

The input is in freeform format, meaning whitespace may be use liberally.


@<Read in the iterated function system@>=
if ( 1!=scanf(" %d",&n_ifs))
	{fprintf(stderr,"IFS does not specify n_ifs, number of maps\n");exit(3);}
if ( n_ifs < 1)
	{fprintf(stderr,"Need a positive number of maps: n_ifs=%d\n",n_ifs);exit(4);}
weight=malloc(sizeof(double)*n_ifs);
cum_norm_weight=malloc(sizeof(double)*n_ifs);
map=malloc(sizeof(affine_t)*n_ifs);
if (weight==NULL||cum_norm_weight==NULL||map==NULL) 
	{fprintf(stderr,"Couldn't allocate arrays\n");exit(5);}
{ int i,j,k;
for (i=0;i<n_ifs;i++) {  /* Read map $i$. */
	for ( j=0; j<DIMENSIONS; j++) /* Read array part $A$. */
		for ( k=0; k<DIMENSIONS; k++)
			if ( 1!=scanf(" %lf",&map[i].A[j][k]) )
				{fprintf(stderr,"Couldn't read map %d array entry (%d,%d)\n",i,j,k);
				exit(6);}
	for ( j=0; j<DIMENSIONS; j++) /* Read vector part $v$. */
		if ( 1!=scanf(" %lf",&map[i].v[j]) )
			{fprintf(stderr,"Couldn't read map %d vector entry (%d)\n",i,j);
			exit(7);}
	if ( 1!=scanf(" %lf",&weight[i]) )
		{fprintf(stderr,"Couldn't read map %d weight\n",i);
		exit(8);}
}
}

@ To generate the data, we play the ``Chaos Game'' on the IFS.  
This notion is fully 
developed in Barnsley's book;  he provides BASIC code for this
@^Barnsley, Michael Fitzgerald@>
in section 3.8.2.  

The implementation is quite simple.  
We start anywhere on the plane
and repeatedly apply a map at random, chosen according to their relative
weightings.  Wherever we land, we plot a point.  To get rid of the noise
introduced by the our arbitrary starting location, we skip plotting
the first few points.
The points very quickly converge to the strange attractor for the system, 
if one exists.

% density, etc.

Point |u| is the current location in space.  We start it at the origin.

@<Generate the data@>=
@<Set up the biased coin@>@;
{int i; point_t u;
for (i=0;i<DIMENSIONS;i++) u[i]=0.0;
@<Prime the chaos game@>@;
@<Play the chaos game, with output@>@;
printf("EOF\n");
}

@ Flipping a biased coin requires that we be able to invert the
cumulative probability distribution.  But first we'll have to 
find the cumulative probability distribution.  We compute that here,
and store it in |cum_norm_weight|.

I expect that number of maps will be small ---fewer than 20--- 
so it will be fine to do
a linear scan of |cum_norm_weight| to invert the cumulative distribution 
function.
@^assumptions@>

@<Set up the biased coin@>=
{int i; double total_weight=0.0, sum_weight=0.0;
for (i=0;i<n_ifs;i++)
	total_weight += weight[i];
if ( total_weight < 1e-10 )
	{fprintf(stderr,"Total weight %f is too small (less than 1e-10)\n",total_weight); exit(9);}
for (i=0;i<n_ifs;i++) {
	sum_weight+=weight[i];
	cum_norm_weight[i] = sum_weight/total_weight;
}
}

@ To flip the biased coin, we generate a number in the uniform distribution
over $[0,1)$, and then invert the cumulative distribution.

The pseudo-random number generator provided by the Stanford GraphBase
@^Stanford GraphBase@>
in its raw form only provides integers in the range $0$ through $2^{31}-1$.
We normalize it to a floating point number in the range $[0,1)$ by dividing
by $2^{31}$, being careful about automatic type conversions.


If the number of maps is large, this linear  scan ought to be converted to
a binary search.

@d two_to_the_31 ((double)0x80000000)

@<Set |next_map| to the next biased coin flip@>=
{
const double fair_toss=gb_next_rand()/two_to_the_31;
int i;
for (i=0;i<n_ifs && cum_norm_weight[i] < fair_toss ;i++)
	;	/* Empty body */
if ( i==n_ifs ) i--; /* Just in case |fair_toss==1.0|.  Impossible? */
next_map=i;
}



@  
We take 2000 steps to flush out the noise caused by starting at the origin.
The number of steps we should really take is something like
$${m \over  {- \log_2 \max_i\! \size{\det(A_i)}}},$$
where $m$ is the number of bits of mantissa in type |double|; 
$m=53$ on all machines implemtenting arithmetic to the IEEE-754 floating
point standard.
@^IEEE-754 floating point standard@>
Two thousand
should be safe for now, though maybe I should compute this bound.

It might also be a good idea to check that every affine map in the IFS
is actually contractive.  We could give a warning if this isn't the case.
Maybe in the future.

@<Prime the chaos game@>=
{int i;
for (i=0;i<2000;i++) {
	@<Take a step@>@;
}
}

@ To take a step, we flip the biased coin, and move |u| accordingly.
We need a temporary variable |u_prime| so we don't prematurely
stomp on the components of |u|.
@<Take a step@>=
{int d,i; point_t u_prime;
@<Set |next_map| to the next biased coin flip@>@;
for (d=0;d<DIMENSIONS;d++) {
	u_prime[d]=map[next_map].v[d];
	for (i=0;i<DIMENSIONS;i++)
		u_prime[d]+=map[next_map].A[d][i] * u[i];
}
for (d=0;d<DIMENSIONS;d++) u[d]=u_prime[d];
}

@ We need to declare |next_map|.
@<|main| variables@>=
int next_map;

@  Now we get to the meat of the matter.  Fortunately, the code
to play the chaos game with output is already written, save for the
bookkeeping.

We output each point with lots of unwarranted precision.  But
this data is intended for computer's eyes only, so it doesn't really
matter.

@<Play the chaos game, with output@>=
{int i,d;
for (i=0;i<n;i++) {
	@<Take a step@>@;
	printf("%7d",i+1);	/* City numbers are 1-based in TSPLIB. */
	for (d=0;d<DIMENSIONS;d++)
		printf(" %25f",u[d]);
	printf("\n");
}
}

@ There is one small system-dependent annoyance to take care of.
The include files for some operating systems don't define full
prototypes  for some important functions like |fprintf|.  Versions
of SunOS and IRIX have this problem.  These kinds of problems are fixed in
the file \file{fixincludes.h}, defined elsewhere.
@^system dependencies@>

@<Other includes@>=
#include "fixincludes.h"


@*Sample input and output.
So what kind of data does this program produce?  Let's look at some examples.

@ The fern is probably the most famous IFS.  It consists of only four maps,
yet is remarkably beautiful.  
Its specification, taken from Barnsley's book, looks like this:\mybr
@^Barnsley, Michael Fitzgerald@>
\myverb{4\mybr
 0     0     0    0.16 0 0    0.01\mybr
 0.85  0.04 -0.04 0.85 0 1.6  0.85\mybr
 0.2  -0.26  0.23 0.22 0 1.6  0.07\mybr
-0.15  0.28  0.26 0.24 0 0.44 0.07}

This is the output with seed 42 and 10000 samples:
\medskip
\input psfig.sty
\centerline{\psfig{figure=fern.eps}}\par


@ Here are some systems I cobbled together in just a few minutes' fiddling
with this generator program.

The first one has two major clouds and sweeping radiating lines.
This is its input file:\mybr
\myverb{5\mybr
 0.95  0.05  0.05  1.05  0.02   0.001 0.5\mybr
-0.50 -0.20  0.10 -0.80 -0.20  -0.05 0.2\mybr
 0.38 -0.02  0.13  0.24  0.015 -0.05 0.1126\mybr
 0.01  0.05  0.03  0.05  0.015 -0.06 0.001\mybr
 0.1  0 0 1.5  -0.01 0 0.05}

Here are the first 3000 points generated using seed 42.
\medskip
\centerline{\psfig{figure=nicecloud.eps}}\par

This second one reminds me of a pair of tropical fish swimming from left
to right.  This is its data:\mybr
\myverb{9\mybr
0.000 -.3333 1 0  -0.3333 0 1\mybr
0.000 -.3333 1 0  0.3333 0 1\mybr
0.2  0 0 0.2 0 0 .5\mybr
0.15  .2 -.2 0.15 0 0 1\mybr
0.3333  0 0 0.7 -0.3333 0 1\mybr
-0.2  0.2 0 0.3333 0.7 0 1\mybr
0.6  0 0 0.3333 -0.5 .4 1\mybr
0.3333  0 0 0.3333 0.3333 .3333 1\mybr
0.25  0 0.1 0.3333 -0.25 -.4333 1}


\vbox{Here is its output: 10000 points with seed 42.
\medskip
\centerline{\psfig{figure=tropicalfish.eps}}\par}

By increasing the relative weight of the third map from $0.5$ to 10, we
emphasize the clustering of the eye and its related spots.
This is the new data:\mybr
\myverb{9\mybr
0.000 -.3333 1 0  -0.3333 0 1\mybr
0.000 -.3333 1 0  0.3333 0 1\mybr
0.2  0 0 0.2 0 0 10\mybr
0.15  .2 -.2 0.15 0 0 1\mybr
0.3333  0 0 0.7 -0.3333 0 1\mybr
-0.2  0.2 0 0.3333 0.7 0 1\mybr
0.6  0 0 0.3333 -0.5 .4 1\mybr
0.3333  0 0 0.3333 0.3333 .3333 1\mybr
0.25  0 0.1 0.3333 -0.25 -.4333 1}

\vbox{Here is its output: 10000 points with seed 42.
\medskip
\centerline{\psfig{figure=tropicalfisheye.eps}}\par}


@*Index.
