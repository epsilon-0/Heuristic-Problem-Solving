


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
$Log: read.w,v $
Revision 1.135  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.134  1998/05/08 22:23:57  neto
Better comment.
Also, added writing abilities for matrix forms.

Revision 1.133  1997/12/13 20:05:45  neto
Ok, so I got the name of write... wrong

Revision 1.132  1997/12/13 20:03:05  neto
Added first (compiling) draft of write tsp instance

Revision 1.131  1997/12/13 17:25:18  neto
Stripped the newlines off the error messages.

Revision 1.130  1997/10/18 15:16:19  neto
More readability (matchword).
Hopefully fix garbage output on error (move keyword[0]=0).
Added support for CEIL 2D

Revision 1.129  1997/10/17  21:47:44  neto
Fixed to compile.

Revision 1.128  1997/10/17  21:00:25  neto
Made coordinates indexed by number, not name, i.e. x[0] and x[1] instead
of x and y.  This reduces the code size in kdtree by removing
the CUTDIMEN kludge.

Revision 1.127  1997/09/27 18:04:39  neto
Fixed RCS log behaviour

Revision 1.126  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.125  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.124  1997/05/16  18:09:40  neto
Include <config.h> and lkconfig.h

Revision 1.123  1997/02/10  19:25:03  neto
Limit the size of the PostScript arrays.

Revision 1.122  1997/02/10  19:16:26  neto
Fixed printf spec.

Revision 1.121  1997/02/10  19:13:51  neto
Changed debugging PostScript output so that we don't depend on
large (>8191 element) arrays.

Revision 1.120  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.119  96/12/20  14:02:47  neto
Make EOF optional. 

Revision 1.118  96/12/13  17:11:23  neto
Make hypot optional.

Revision 1.117  96/12/13  14:44:43  neto
Used hypot instead of sqrt.
Also, added cost\_from\_euc2d\_raw.

Revision 1.116  96/12/05  14:43:16  neto
Added support for no rounding.

Revision 1.115  96/09/12  15:25:37  neto
Empty input doesn't print a garbage keyword now.

Revision 1.114  96/08/16  13:05:01  neto
Added fixincludes.

Revision 1.113  96/08/15  14:01:29  neto
Make it pass all flags, except for error problem.

Revision 1.112  96/08/15  12:34:25  neto
Make it pass -Wall

Revision 1.111  96/07/29  17:07:58  neto
Fixed to compile.

Revision 1.110  96/07/29  16:24:28  neto
oops.  TeX again.

Revision 1.109  96/07/29  16:22:58  neto
TeX barfed on the Log.

Revision 1.108  96/07/29  16:20:09  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*Reading TSPLIB files.
The {\sc READ\_ME} included with {\sc TSPLIB} describes the file format.
We restrict our attention to the case where the arc lengths are given
in matrix form, or are assumed to be the Euclidean lengths in two dimensions.

Here is the outline of this module.

@c
#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "fixincludes.h"
@<Other includes@>@;

#include "read.h"@;

@<Global variables@>@;
@<Module definitions@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *read_rcs_id="$Id: read.w,v 1.135 1998/07/16 21:58:55 neto Exp neto $";


@ The header file for this module is also included into this module.
It provides type definitions and declarations of publicly accessible
variables and subroutines.

@(read.h@>=
extern const char *read_rcs_id;
@<Type definitions@>@;
@<Exported variables@>@;
@<Exported subroutines@>@;


@ These routines deal with only one problem at a time.  
We keep a pointer to the current problem in the variable |p|.
This is convenient to the users of these routines because that means
they don't have to pass an extra pointer on every function call.
This is also more efficient because we expect the edge cost function
to be evaluated thousands and maybe millions of times.

@<Global variables@>=
static tsp_instance_t *p;

@ We provide a mechanism to switch contexts.  
The user supplies the
problem that becomes the new context, and receives the current
context.

@<Subroutines@>=
tsp_instance_t *
switch_to(tsp_instance_t *new_problem) 
{
	tsp_instance_t *old_problem;
	old_problem = p;
	p = new_problem;
	@<Set the |cost| function according to the current context@>@;
	return old_problem;
}

@ The switching routine is made publicly available.
@<Exported subroutines@>=
tsp_instance_t *
switch_to(tsp_instance_t *new_problem);

@ The routine that actually does the reading is passed the file name
and fills the current context.  If a previous context exists, then
it should be saved with a call such as |saved_problem = switch_to(NULL)|, 
or it should be freed.


@<Subroutines@>=
tsp_instance_t *
read_tsp_file(FILE *in, FILE *debug)
{
	p=new_of(tsp_instance_t);
	@<Set the problem defaults@>@;
	@<Read in the problem@>@;
	@<Debugging output@>@;
	return p;
}

@ We've used an allocation macro, so we should include the header file
where it is defined.  We also need to know the error checking interface.
@<Other includes@>=
#include "memory.h"
#include "error.h"

@ We make the reading routine publicly available.
@<Exported subroutines@>=
tsp_instance_t * read_tsp_file(FILE *in, FILE *out);


@ The |tsp_instance_t| type contains fields that identify and 
specify the problem.

The |name| field is the name given by the TSPLIB maintainers to this problem.
It is useful as a basename for the file, though we don't enforce such
usage.  

The |comment| field is the one-line comment attached to this graph.

The |n| field is the number of cities in the problem.  


@<Type definitions@>=
@<Early type definitions@>@;
typedef struct {
	char *name;
	char *comment;
	int n;
	@<Other |tsp_instance_t| fields@>@;
} tsp_instance_t;

@ We specify defaults for these fields so that if there is a problem
reading the file, we can detect it later on.

@<Set the problem defaults@>=
p->name = NULL;
p->comment = NULL;
p->n = 0;

@ The different parts of the input file are introduced by various keywords.
So we read a keyword, and then do the appropriate thing.

@d matchword(STR) (0==strncmp(keyword,STR,strlen(STR)))
	
@<Read in the problem@>=
{
#define MAX_KEYWORD_LEN (25)
#define MAX_LINE_LEN (200)
char keyword[MAX_KEYWORD_LEN], rest_of_line[MAX_LINE_LEN];
int more_input = 1, lineno=0;
while( more_input) {
	char *colon; int r;
	keyword[0]=0;
	r = fscanf(in," %s ", keyword); 
	if ( r==EOF )@+ {@+more_input=0;@+break;@+}
	errorif( r != 1, "%d: Couldn't read the word following \"%s\". (r==%d)",
			 lineno+1,keyword,r);
	if ( NULL!=(colon = strchr(keyword,':')) ) *colon = '\0';
	if ( matchword("EOF") ) {
		more_input = 0;
	}@+ else if ( matchword("NAME") ) {
		@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
		p->name = dup_string(rest_of_line);@;
	}@+ else if ( matchword("COMMENT") ) {
		@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
		p->comment = dup_string(rest_of_line);@;
	}@+ else if ( matchword("TYPE") ) {
		@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
		errorif(strcmp(rest_of_line,"TSP"),"Can't read TSPLIB files of type %s.",rest_of_line);@;
	}@+ else if ( matchword("DIMENSION") ) {
		@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
		p->n = atoi(rest_of_line);
	}@+ else if ( matchword("DISPLAY_DATA_TYPE") ) {
		@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
		/* Do nothing. */
	}@+ else if ( matchword("EDGE_WEIGHT_TYPE") ) {
		@<Parse the edge weight type@>@;
	}@+ else if ( matchword("EDGE_WEIGHT_FORMAT") ) {
		@<Parse the edge weight format@>@;
	}@+ else if ( matchword("EDGE_WEIGHT_SECTION") ) {
		@<Parse the edge weights@>@;
	}@+ else if ( matchword("NODE_COORD_SECTION") ) {
		@<Parse the node coordinates@>@;
	}@+ else if ( matchword("DISPLAY_DATA_SECTION") ) {
		@<Parse the display data@>@;
	}@+ else if ( matchword("SEED") ) {
		@<Generate random edge lengths using the given seed@>@;
	}@+ else {
		@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
		errorif(1,"%d: Don't know what the keyword %s is!",lineno,keyword);
	}
}
@<Set the |cost| function according to the current context@>@;
}

@ We need to include the interface definition for the string handling
functions.
@<Other includes@>=
#include <string.h>

@
We make sure that the colon is actually there, and that the line
lengths aren't violated.

Also, erase trailing whitespace.

@<Get the rest of the line into |rest_of_line|, but skip the colon@>=
{ 
int l; char *rcp;
if ( colon == NULL ) {
	int r=fscanf(in," : ");
	errorif( r != 0, "%d: Missed the colon.", lineno);
}
rcp = fgets(rest_of_line,MAX_LINE_LEN,in);
errorif( NULL == rcp,
	@|"%d: Couldn't read after the colon; truncated file?", lineno);@;
l = strlen(rest_of_line)-1;@;
if ( l>=0 && rest_of_line[l] == '\n' ) { rest_of_line[l--]='\0'; lineno++;}
while ( l >= 0 && isspace(rest_of_line[l]) ) rest_of_line[l--] = '\0';@;
if ( feof(in) )@+more_input = 0;
}

@ We need to include the character classifiction macros.
@<Other includes@>=
#include <ctype.h>

@ The |RANDOM_EDGES| edge weight type is an extension to the TSPLIB format.  
It specifies that the edge lengths should be random and uniformly
distributed between 1 and 1000.  The keyword |SEED| must be used
to specify a seed value and to generate the edge lengths.

@<Parse the edge weight type@>=
@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
if ( 0==strcmp(rest_of_line,"EUC_2D") ) {
	p->edge_weight_type = EUC_2D;
}@+else if ( 0==strcmp(rest_of_line,"CEIL_2D") ) {
	p->edge_weight_type = CEIL_2D;
}@+else if ( 0==strcmp(rest_of_line,"EXPLICIT") ) {
	p->edge_weight_type = EXPLICIT;
}@+else if ( 0==strcmp(rest_of_line,"RANDOM_EDGES") ) {
	p->edge_weight_type = RANDOM_EDGES;
}@+else {
	errorif(1,"%d: Apology: Unknown edge weight type \"%s\".",lineno,rest_of_line);
}

@ @<Early type definitions@>=
typedef enum { EUC_2D, CEIL_2D, EXPLICIT, RANDOM_EDGES } edge_weight_type_t;

@ @<Other |tsp_instance_t| fields@>=
edge_weight_type_t edge_weight_type;

@ @<Set the problem defaults@>=
p->edge_weight_type = EUC_2D;

@ @<Other includes@>=
#include "gb_flip.h"




@ @<Parse the edge weight format@>=
@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
if ( 0==strcmp(rest_of_line,"LOWER_DIAG_ROW") ) {
	p->edge_weight_format = LOWER_DIAG_ROW;
}@+else if ( 0==strcmp(rest_of_line,"FULL_MATRIX") ) {
	p->edge_weight_format = FULL_MATRIX;
}@+else if ( 0==strcmp(rest_of_line,"UPPER_ROW") ) {
	p->edge_weight_format = UPPER_ROW;
}@+else {
	errorif(1,"%d: Unknown edge weight format \"%s\".",lineno,rest_of_line);
}

@ @<Early type definitions@>=
typedef enum { NONE, LOWER_DIAG_ROW, FULL_MATRIX, UPPER_ROW } 
	edge_weight_format_t;

@ @<Other |tsp_instance_t| fields@>=
edge_weight_format_t edge_weight_format;

@ @<Set the problem defaults@>=
p->edge_weight_format = NONE;


@*Explicit edge weights.
We parse the edge weights according to the format they are given.  The
file format guarantees that we know this information before this section
arrives.

@<Parse the edge weights@>=
switch( p->edge_weight_format ) {
long int long_dummy;
case LOWER_DIAG_ROW :
	{ 
		int row, col;
		p->edge_weights = new_arr_of(length_t*,p->n);
			/* Allocate the space for the edge weights. */
		for ( row = 0 ; row < p->n ; row++ ) {
			p->edge_weights[row] = new_arr_of(length_t,p->n);
		}
		for ( row = 0 ; row < p->n ; row++ ) { /* Now actually read the weights. */
			for ( col = 0 ; col <= row ; col++ ) {
				int r= fscanf(in," %ld ", &long_dummy);
				errorif( 1 != r,
					"Couldn't convert an edge weight: %d to %d.",row+1,col+1);
				p->edge_weights[col][row] = p->edge_weights[row][col] = long_dummy;
			}
		}
	}
	break;
case FULL_MATRIX :
	{
		int row, col;
		p->edge_weights = new_arr_of(length_t*,p->n);
			/* Allocate the space for the edge weights. */
		for ( row = 0 ; row < p->n ; row++ ) {
			p->edge_weights[row] = new_arr_of(length_t,p->n);
		}
		for ( row = 0 ; row < p->n ; row++ ) { /* Now actually read the weights. */
			for ( col = 0 ; col < p->n ; col++ ) {
				int r= fscanf(in," %ld ", &long_dummy);
				errorif( 1 != r,
					"Couldn't convert an edge weight: %d to %d.",row+1,col+1);
				p->edge_weights[row][col] = long_dummy;
			}
		}
		for ( row = 0; row < p->n ; row++ ) {
			for ( col = 0; col < row ; col++ ) {
				errorif(p->edge_weights[row][col] != p->edge_weights[col][row],
					"Asymmetric FULL_MATRIX:  (%d,%d) does not match (%d,%d)",
					row,col,col,row);
			}
		}
	}
	break;
case UPPER_ROW:
	{ 
		int row, col;
		p->edge_weights = new_arr_of(length_t*,p->n);
			/* Allocate the space for the edge weights. */
		for ( row = 0 ; row < p->n ; row++ ) {
			p->edge_weights[row] = new_arr_of(length_t,p->n);
			p->edge_weights[row][row] = 0;
		}
		for ( row = 0 ; row < p->n ; row++ ) { 
			/* Now actually read the weights. */
			for ( col = row+1 ; col < p->n ; col++ ) {
				int r= fscanf(in," %ld ", &long_dummy);
				errorif( 1 != r,
					"Couldn't convert an edge weight: %d to %d.",row+1,col+1);
				p->edge_weights[col][row] = p->edge_weights[row][col] = long_dummy;
			}
		}
	}
	break;
default: break;
}

@ We need the |length_t| type.
@<Other includes@>=
#include "length.h"

@ @<Other |tsp_instance_t| fields@>=
length_t **edge_weights;

@ @<Set the problem defaults@>=
p->edge_weights = NULL;


@*Implicit edge weights.
In this case, the weights of the edges are not given explicitly in
the file, and we don't store them either.  Instead, each weight can
be computed from other data given in the file, usually coordinates
of the vertices of the problem.  

Currently the only implicit edge weight scheme we support is the
two-dimensional Euclidean distance.  
Unsupported schemes include
the geographical distances.

Beware of off-by-one errors in input and output:
the input format counts from 1; we count from 0.

For the purposes of graphical output, we also keep track of the bounding
box of the cities.

@d min(X,Y) ((X)>(Y)?(Y):(X))
@d max(X,Y) ((X)<(Y)?(Y):(X))

@<Parse the node coordinates@>=
{ 	

	int i,j;
	p->coord = new_arr_of(coord_2d,p->n);	/* Allocate the space for the coordinates. */
	for ( i=0; i<p->n; i++ ) {
		fscanf(in," %d ",&j);
		fscanf(in," %lf %lf ",&p->coord[j-1].x[0],&p->coord[j-1].x[1]);
		p->xmin = min(p->xmin,p->coord[j-1].x[0]);
		p->ymin = min(p->ymin,p->coord[j-1].x[1]);
		p->xmax = max(p->xmax,p->coord[j-1].x[0]);
		p->ymax = max(p->ymax,p->coord[j-1].x[1]);
		lineno++;
	}
}

@ Index |0| refers to the $x$ coordinate,
and index |1| refers to the $y$ coordinate.

I use an array because code that indexes can be made shorter than
code that uses different names.  Also, it generalizes more easily
to higher dimensions.  As a bonus, a good compiler ought to emit identical
anyway.

@<Early type definitions@>=
typedef struct { double x[2]; } coord_2d;

@ @<Other |tsp_instance_t| fields@>=
coord_2d *coord;
double xmin, xmax, ymin, ymax;

@ I've used the limits on integer values for the minimum and maximum
coordinate values.  It would be nice to use |double|-valued constants,
but I can't seem to find them under SunOS.  (Header {\tt math.h} has
|HUGE_VAL|, but that appears to be an infinity; it breaks on the KSR.)
In any case, these integer values should be good enough.

@<Set the problem defaults@>=
p->coord = NULL;
p->xmin = p->ymin = INT_MAX;
p->xmax = p->ymax = INT_MIN;

@ @<Other includes@>=
#include <limits.h>

@ Currently we don't do anything with the display coordinates.  
We may want to output PostScript in the future.
@<Parse the display data@>=
{ 	
	int i;
	double dummy;
	for ( i=0; i<p->n; i++ ) {
		fscanf(in," %lf %lf %lf ",&dummy,&dummy,&dummy);
	}
}

@ We use |short|s to store the randomly generated edge lengths because
they fit.  This scheme saves space and time (because of cache effects).
@<Generate random edge lengths using the given seed@>=
@<Get the rest of the line into |rest_of_line|, but skip the colon@>@;
gb_init_rand( atol(rest_of_line) );
{ int i,j;
p->short_edge_weights = new_arr_of(short*,p->n);
for (i=0;i<p->n;i++) {
	p->short_edge_weights[i]  = new_arr_of(short,p->n);
	p->short_edge_weights[i][i] = 0;
}
for (i=0;i<p->n;i++)
	for (j=0;j<i;j++) 
		p->short_edge_weights[i][j] = p->short_edge_weights[j][i] = 
			(short)(1+gb_unif_rand(1000L));
if ( p->n <=10 ) {
	printf("Cost matrix:\n");
	for (i=0;i<p->n;i++) {
		for (j=0;j<p->n;j++) printf(" %4d",p->short_edge_weights[i][j]);
		printf("\n");
	}
}
}

@ @<Other |tsp_instance_t| fields@>=
short **short_edge_weights;

@ @<Set the problem defaults@>=
p->short_edge_weights = NULL;

@*Cost functions.
The cost function depends upon the type of the current problem.
The |cost| variable is a function pointer that refers to the appropriate
function, and it is always the case that 
|cost(i,j)| is the cost of the edge from |i| to |j| in the current problem.

We will often only be comparing the lengths of a pair of edges.
In these cases, we can substitute a function which is monotonic
in the real cost function.  
The |pseudo_cost| function should be monotonic in |cost|.
That is,
$${\mit cost}(i,j)\le {\mit cost}(k,l) \iff
{\mit pseudo\_cost}(i,j) \le {\mit pseudo\_cost}(k,l).$$
%$$ |cost(i,j)|\le|cost(k,l)|\iff
%|pseudo_cost(i,j)|\le|pseudo_cost(k,l)|.$$

@<Global variables@> =
length_t (*cost)(const int,const int);
length_t (*pseudo_cost)(const int,const int);

@ We make this variable known to the outside world.
@<Exported variables@>=
extern length_t (*cost)(const int,const int);
extern length_t (*pseudo_cost)(const int,const int);


@ When the edge weights are given explicitly, the cost function is merely
a table lookup.  When the edge lengths are generated randomly, they
save space
@<Module subroutines@>=
length_t cost_from_matrix(const int i,const int j);

length_t
cost_from_matrix(const int i,const int j)
{
	return (length_t)p->edge_weights[i][j];
}

length_t cost_from_short_matrix(const int i, const int j);

length_t
cost_from_short_matrix(const int i, const int j)
{
	return (length_t)p->short_edge_weights[i][j];
}


@ We use the following cost function when the weight of an edge weights between
two nodes is the two dimensional Euclidean distance between those nodes.

The original incarnation of the TSPLIB documentation used the |aint| 
function in place of the |floor| 
function.  However, |aint| is not in any ANSI~C standard library.  
For non-negative arguments, |aint| and |floor| behave the same way: each
returns
a |double| value representing the greatest integer not more than its |double|
argument.
(I compared the |aint| manual page under SunOS~4.1 dated 15 October 1987
with the description of |floor| in Plauger's {\sl The Standard C Library}.)

The newer documentation uses |nint| which also isn't in the ANSI~C library.
I believe it is the same ``round to the nearest integer'', which I take
to mean |nint(\alpha)=floor(0.5+\alpha)|.



Maybe we should be more intelligent about integer square roots???

@<Module subroutines@>=
length_t cost_from_euc2d(const int i, const int j);
length_t
cost_from_euc2d(const int i, const int j)
{
	coord_2d *coord_array = p->coord;
	double xd = coord_array[i].x[0] - coord_array[j].x[0];
	double yd = coord_array[i].x[1] - coord_array[j].x[1];
	return (length_t) floor(0.5+my_hypot(xd,yd));
}

@ Taking the ceiling instead of just rounding to the nearest integer
is interesting because the Euclidean distance with ceiling is a metric.
In particular, the triangle inequality is preserved under taking ceilings.

@<Module subroutines@>=
length_t cost_from_ceil2d(const int i, const int j);
length_t
cost_from_ceil2d(const int i, const int j)
{
	coord_2d *coord_array = p->coord;
	double xd = coord_array[i].x[0] - coord_array[j].x[0];
	double yd = coord_array[i].x[1] - coord_array[j].x[1];
	return (length_t) ceil(my_hypot(xd,yd));
}

@ I converted over to using the |hypot| function.  But things were running
about 15% slower on an SGI Challenge (150MHz MIPS R4400), 
even using the native C compiler
{\tt cc -xansi}.  The {\tt -xansi} option makes some floating point 
intrinsics inline.  This should be faster, but one should always measure.

So I make the use of |hypot| optional via the |my_hypot| macro.  The
macro definition is changed according to the compile time option
|COST_USE_HYPOT|.

Note that the parameters to this macro should not have side effects.

@<Module definitions@>=
#if defined(COST_USE_HYPOT)
#define my_hypot(A,B) (hypot((A),(B)))
#else
#define my_hypot(A,B) (sqrt((A)*(A)+(B)*(B)))
#endif

@ David Johnson's experiments don't use rounded Euclidean norms.  
If the external variable |noround| is true, then we avoid rounding.

@<Module subroutines@>=
length_t cost_from_euc2d_not_rounded(const int i, const int j);
length_t
cost_from_euc2d_not_rounded(const int i, const int j)
{
	coord_2d *coord_array = p->coord;
	double xd = coord_array[i].x[0] - coord_array[j].x[0];
	double yd = coord_array[i].x[1] - coord_array[j].x[1];
	return (length_t) my_hypot(xd,yd);
}

@
I've had floating point precision problems that I believe are
based on massive cancellation.
So in some experiments I may want to compute the raw distances without
even casting to |length_t|.  This is done by function 
|cost_from_euc2d_raw|.

@<Subroutines@>=
double
cost_from_euc2d_raw(const int i, const int j)
{
	coord_2d *coord_array = p->coord;
	double xd = coord_array[i].x[0] - coord_array[j].x[0];
	double yd = coord_array[i].x[1] - coord_array[j].x[1];
	return my_hypot(xd,yd);
}

@
@<Exported subroutines@>=
double cost_from_euc2d_raw(const int i, const int j);

@ We need to include the interface definition for the numerical
functions
|floor|, |sqrt|, and |hypot|.

@<Other includes@>=
#include <math.h>

@ For comparisons between edges, we can strip off the rounding and
square root computations.  This is about three times faster
on an Intel 486 DX2-66.

@<Module subroutines@>=
length_t pseudo_cost_from_euc2d(const int i, const int j);
length_t
pseudo_cost_from_euc2d(const int i, const int j)
{
	coord_2d *coord_array = p->coord;
	double xd = coord_array[i].x[0] - coord_array[j].x[0];
	double yd = coord_array[i].x[1] - coord_array[j].x[1];
	return (length_t)(xd*xd+yd*yd);	/* Worry about rounding? */
}


@ We choose among the above cost functions based upon the type
of the problem.  In the Euclidean case, we pay attention to the
|noround| variable.

@<Set the |cost| function according to the current context@>=
switch( p->edge_weight_type ) {
case EXPLICIT: 
	cost = cost_from_matrix;
	pseudo_cost = cost_from_matrix; 
	break;
case EUC_2D: 
	{
	extern int noround;	/* Defined by module \module{LK}. */
	cost = noround ? cost_from_euc2d_not_rounded : cost_from_euc2d;
	}
	pseudo_cost = pseudo_cost_from_euc2d; 
	break;
case CEIL_2D: 
	{
	extern int noround;	/* Defined by module \module{LK}. */
	cost = noround ? cost_from_euc2d_not_rounded : cost_from_ceil2d;
	}
	pseudo_cost = pseudo_cost_from_euc2d; 
	break;
case RANDOM_EDGES: 
	errorif(p->short_edge_weights==NULL,"RANDOM_EDGES specified but no SEED given");
	cost = cost_from_short_matrix;
	pseudo_cost = cost_from_short_matrix; 
	break;
}

@*Debugging output routines.

%When debugging output is desired, |verbose>0|.

When we're done reading the file, we output some summary statistics
about its contents to a debugging file.  The file handle is |debug|, passed
in to |read_tsp_file| as a parameter.

@ First we output the number of cities and create 1-based arrays
for the |x| and |y| coordinates.

Unfortunately, the maximum array size on some PostScript implementations
is  quite small.  For example, the default in the Ghostscript implementation
is 8191.  If we have too many cities, then we can't create the arrays.
In these cases, we must take care later on to not use any PostScript routines
that require them.

@<Debugging output@>=
if (debug) {
	fprintf(debug,"/N {%d} def        %% number of nodes\n",p->n);
	if ( p->n < 8191 )
		fprintf(debug,"/xs N 1 add array def\n/ys N 1 add array def\n");
}


@ Then we output the bounding positions.

@<Debugging output@>=
if (debug) {
const double xdiff = ((double) p->xmax) - ((double)p->xmin);
const double ydiff = ((double) p->ymax) - ((double)p->ymin);
const double maxrange = max(xdiff,ydiff);
const double xoffset = xdiff<ydiff ? (maxrange-xdiff)/2 : 0.0;
const double yoffset = ydiff<xdiff ? (maxrange-ydiff)/2 : 0.0;
fprintf(debug,"/xmin {%f} def \n",p->xmin);
fprintf(debug,"/xmax {%f} def \n",p->xmax);
fprintf(debug,"/ymin {%f} def \n",p->ymin);
fprintf(debug,"/ymax {%f} def \n",p->ymax);
fprintf(debug,"/maxrange {%f} def \n", maxrange );
fprintf(debug,"/xoffset  {%f} def \n", xoffset);
fprintf(debug,"/yoffset  {%f} def \n", yoffset);
}

@ And the coordinates themselves.
@<Debugging output@>=
if (debug) {int i;
for (i=0; i<p->n ; i++) {
	fprintf(debug,"%f %f ts\n",p->coord[i].x[0],p->coord[i].x[1]);
}
fflush(debug);
}

@*Writing TSPLIB files.
Given a |tsp_instance_t| object, we'd like to write it out again.

@<Subroutines@>=
void
write_tsp_file(tsp_instance_t *tsp,FILE *out) 
{
if(out) { 
fprintf(out,"NAME: %s\n",tsp->name);
fprintf(out,"TYPE: TSP\n");
if (tsp->comment) {fprintf(out,"COMMENT: %s\n",tsp->comment);}
fprintf(out,"DIMENSION: %d\n",tsp->n);
switch(tsp->edge_weight_type) {
case CEIL_2D: fprintf(out,"EDGE_WEIGHT_TYPE: CEIL_2D\n"); 
	@<Write the coordinates@>@;
	break;
case EUC_2D:  fprintf(out,"EDGE_WEIGHT_TYPE: EUC_2D\n"); 
	@<Write the coordinates@>@;
	break;
case EXPLICIT: fprintf(out,"EDGE_WEIGHT_TYPE: EXPLICIT\n");
	{ int format=tsp->edge_weight_format;
	@<Write the explicit weights in format |format|@>@;
	}
	break;
case RANDOM_EDGES: fprintf(out,"EDGE_WEIGHT_TYPE: EXPLICIT\n");
	{ int format=UPPER_ROW;
	@<Write the explicit weights in format |format|@>@;
	}
	break;
fprintf(out,"EOF\n");
}
}
}

@
@<Exported subroutines@>=
void write_tsp_file(tsp_instance_t *tsp,FILE *out);

@
@<Write the coordinates@>=
fprintf(out,"NODE_COORD_SECTION\n");
{int i;
for (i=0;i<tsp->n;i++) {
fprintf(out,"%d %20g %20g\n",i+1,tsp->coord[i].x[0],tsp->coord[i].x[1]);
}
}


@
@<Write the explicit weights in format |format|@>=
{ int row, col;
	switch (format) {
	case LOWER_DIAG_ROW:
		fprintf(out,"EDGE_WEIGHT_FORMAT: LOWER_DIAG_ROW\n");
		fprintf(out,"EDGE_WEIGHT_SECTION\n");
		for (row=0;row<tsp->n;row++) {
			for (col=0;col<=row;col++) {
				fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
			}
			fprintf(out,"\n");
		}
		break;
	case FULL_MATRIX:
		fprintf(out,"EDGE_WEIGHT_FORMAT: FULL_MATRIX\n");
		fprintf(out,"EDGE_WEIGHT_SECTION:\n");
		for (row=0;row<tsp->n;row++) {
			for (col=0;col<tsp->n;col++) {
				fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
			}
			fprintf(out,"\n");
		}
		break;
	case UPPER_ROW:
		fprintf(out,"EDGE_WEIGHT_FORMAT: UPPER_ROW\n");
		fprintf(out,"EDGE_WEIGHT_SECTION:\n");
		for (row=0;row<tsp->n;row++) {
			for (col=row+1;col<tsp->n;col++) {
				fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
			}
			fprintf(out,"\n");
		}
		break;
	default: break;
	}
}
	

@*Index.
