


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
$Log: array.w,v $
Revision 1.112  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.111  1997/10/25 17:59:30  neto
Fix prolog for TeXing.

Revision 1.110  1997/09/27 18:05:36  neto
Fixed RCS log behaviour.

Revision 1.109  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.108  1997/05/16  14:29:45  neto
Make ARRAY DEBUG settable from lkconfig.h
Include config.h and lkconfig.h

Revision 1.107  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.106  96/12/16  14:12:58  neto
Make this clean w.r.t. rcsdiff.

Revision 1.105  1996/09/12  14:07:34  neto
REmoved duplicate consts.

Revision 1.104  96/09/11  16:38:42  neto
Strengthened the array\_set prototype.

Revision 1.103  96/07/29  17:09:50  neto
Fixed to compile.

Revision 1.102  96/07/29  16:19:13  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*An array-based implementation of the oriented tour ADT.
This module implements the oriented tour ADT using arrays.
The queries take constant time, but a worst case
for the flip operation can take up to $n/2$ steps.

@ The oriented tour ADT consists of the following operations
(I will use the names as implemented in this module, \ie, prepended by
the word |array_|.):

|array_next(a)| is a query that returns the city that follows $a$ in the
current tour.

|array_prev(a)| is a query that returns the city that precedes $a$ in the
current tour.  It must be the case that 
|next(prev(a))==prev(next(a))==a|.

|array_between(a,b,c)| is a query that returns true or false.  It answers
the question:  ``In a forward traversal starting at city $a$, do we reach
city $b$ no later than city $c$?''

|array_flip(a,b,c,d)| updates the tour by replacing the edges $(a,b)$ and
$(c,d)$ by the edges $(b,c)$ and $(a,d)$.  It assumes that 
|a==next(b)| and |d==next(c)|.  The orientation of the updated tour
is not specified.

These four operations are the ones defined by Fredman \etal.  In fact, I
have lifted these descriptions from that paper and lightly edited them
for inclusion here.  

For convenience's sake, I also define |array_set(int *t)|, which
sets the current tour to be the same as the array of
integers |t|.  That is, city |i| in the tour is city |t[i]|.
Note that we don't need a ``get'' routine because the tour can be read off
by successively following |next| cities until we wrap to the start
again.

We also define the standard setup and clean procedures: |array_setup(int n)| 
and
|array_cleanup(void)|.  The parameter to the setup procedure is the number
of cities in the instance.

@ The outline of this module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Module definitions@>@;
@<Module variables@>@;
@<Subroutines@>@;
const char *array_rcs_id="$Id: array.w,v 1.112 1998/07/16 21:58:55 neto Exp neto $";

@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

@ The exported interface is contained in the \file{array.h} header file,
which has the following form.

@(array.h@>=
extern const char *array_rcs_id;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "array.h"



@ The storage for the array data structure for this ADT works as follows.   
The $i$'th city of the current tour is stored in position $i$ of array |A|.
To facilitate lookup by city name ---which is an integer between 0 and $n-1$, 
inclusive--- we maintain an inverse |B| of the array |A|.  That is, 
|A[B[i]] == i| for all cities |i| and |B[A[p]] == p| for all array positions p.

We need to declare these arrays.

@<Module variables@>=
static int *A=NULL, *B=NULL;

@ It will be convenient to store both |n|, the number of cities, and, in
variable |nm1|, the value |n-1|.

@<Module variables@>=
static int n, nm1;

@ These variables get allocated in the setup routine.  We will be adding
to this code later, so we separate it out in a new named section.

@<Subroutines@>=
void
array_setup(int num_vertices) {
	@<Set up the array data structure@>@;
}

@
@<Set up the array data structure@>=
n = num_vertices;
nm1 = n-1;
A = new_arr_of(int,n);
B = new_arr_of(int,n);

@ We need the interface to the memory module.  
While we're at it, let's get the error module as well.

@<Module headers@>=
#include "memory.h"

@ These arrays should be deallocated when we clean up.
@<Subroutines@>=
void
array_cleanup(void) {
	@<Clean up the array data structure@>@;
}

@
@<Clean up the array data structure@>=
free_mem(A);
free_mem(B);

@ Both these procedures must be declared externally.
@<Exported subroutines@>=
void array_setup(int num_vertices);
void array_cleanup(void);

@
Queries |array_next(a)| and |array_prev(a)| just return the values 
|A[(B[i]+1)%n]| and 
|A[(B[i]-1)%n]|, respectively.

For efficiency's sake, we factor out the remainder computation.

We'll put in hooks for profiling.

@<Subroutines@>=
int
array_next(int a) {
	int ra;
	@<Profiling for |array_next|@>@;
	ra = B[a];	/* |ra| stands for ``real a''.  Dumb, I know. */
	if ( ra == nm1 ) return A[0];
	else return A[ra+1];
}

int
array_prev(int a) {
	int ra;
	@<Profiling for |array_prev|@>@;
	ra = B[a];
	if ( ra == 0 ) return A[nm1];
	else return A[ra-1];
}

@ We must export these routines.
@<Exported subroutines@>=

int array_next(int a);
int array_prev(int a);

@
Query |array_between(a,b,c)| is basically a comparison of indices, 
but we have to take wraparound into effect.

Note that if |b == c| then we return true.

We'll put in hooks for profiling.

@<Subroutines@>=
int
array_between(int a, int b, int c) {
	int ra, rb, rc;
	ra = B[a];
	rb = B[b];
	rc = B[c];
	@<Profiling for |array_between|@>@;
	if ( rb < ra ) rb+=n;
	if ( rc < ra ) rc+=n;
	return rb <= rc;
}

@ We must export this routine.
@<Exported subroutines@>=
int array_between(int a, int b, int c);

@ Flipping is the most difficult operation.
There are several difficulties.  

First, for efficiency's sake, we prefer to flip the shorter segment.

Second, we must be careful and do the right thing when flipping a segment
that straddles the |n-1,0| boundary.

Third, we must update the |B| array while reversing the segment in the
|A| array.


@<Subroutines@>=
void
array_flip(int a, int b, int c, int d) {
	int ra, rb, rc, rd;
	@<Check flip assumptions@>@;
	@<Make |a,c| the shorter segment@>@;
	@<Profiling for |array_flip|@>@;
	@<Flip |a,c|@>@;
}


@ I have defined a compile time |ARRAY_DEBUG| option to turn on checking of 
the
assumptions for flipping,  that is, that
|a = next(b)| and |d = next(c)|.
(Note that these assumptions may be loosened: an alternative
arrangement is 
|a = prev(b)| and |d = prev(c)|.  See my research notes 
of February 23, 1996.)

@<Check flip assumptions@>=
#if ARRAY_DEBUG
	errorif( a != array_next(b), "a != array_next(b)" );
	errorif( d != array_next(c), "d != array_next(c)" );
#endif /* |ARRAY_DEBUG| */

@ The recommended practice is for |ARRAY_DEBUG| to be set to an integer.  
But all the other compile-time options are based on defined vs. undefined
symbols.  So we are a bit forgiving here.

@<Module definitions@>=
#if !defined(ARRAY_DEBUG)
#define ARRAY_DEBUG 0
#endif

@ We need to import the error checking code.
@<Module headers@>=
#include "error.h"

@
Given the assumption that |a = next(b)| and |d = next(c)|, 
we can either flip |a,c| or |d,b|.  This section arranges these variables
so that |a,c| is the shorter of the two, and the assumptions still hold.

We first need to adjust things so that |a| comes no later than |c|, 
and |d| comes no later than |b|.

@<Make |a,c| the shorter segment@>=
ra = B[a];
rb = B[b];
rc = B[c];
rd = B[d];
if ( rc < ra ) rc += n;
if ( rb < rd ) rb += n;
if ( rc - ra > rb - rd ) { /* Rename the variables */
	int t;
	t = a; a = d; d = t;
	t = b; b = c; c = t;
	t = ra; ra = rd; rd = t;
	t = rb; rb = rc; rc = t;
}

@ In flipping, we need to take care of wraparound, and updating the |B| array.

To reduce the strength of the remainder, I'll use a normalizing macro.
It only works when its argument is between $0$ and $2n-1$, inclusive.

Note that this code assumes that |ra<rc|.
@d norm(x) ((x)<n?(x):(x)-n)

@<Flip |a,c|@>=
{
	int ri,rj,t;
	for ( ri=ra, rj=rc; ri<rj ; ri++, rj-- ) {
		B[A[norm(ri)]] = norm(rj);
		B[A[norm(rj)]] = norm(ri);
		t = A[norm(ri)]; A[norm(ri)] = A[norm(rj)]; A[norm(rj)] = t;
	}
#if ARRAY_DEBUG>1000	/* This is slow */
	for ( i=0; i<n; i++ ) {
		assert( B[A[i]] == i );
		assert( A[B[i]] == i );
	}
#endif
}

@ We must export this routine.
@<Exported subroutines@>=
void array_flip(int a, int b, int c, int d);

@ Setting the initial contents of the array is easy.

I assume that the tour is actually a permutation of the integers $0,\ldots,n-1$.

@<Subroutines@>=
void
array_set(int const *tour) {
	int i;
	for ( i=0;i<n;i++ ) {
		A[i]=tour[i];
		B[A[i]]=i;
	}
}

@ We must export this routine.
@<Exported subroutines@>=
void array_set(int const *tour);

@*Profiling.
Currently, we do no profiling.

@<Profiling for |array_next|@>=
@
@<Profiling for |array_prev|@>=
@
@<Profiling for |array_between|@>=
@
@<Profiling for |array_flip|@>=

@*Index.
