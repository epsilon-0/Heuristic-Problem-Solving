


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

@*Uniform random Euclidean TSP instances.
This program generates uniform random Euclidean TSP instances in the
TSPLIB format (INSERT REFERENCE).    These kinds of instances are used
by Johnson \etal\ (INSERT REFERENCE) 
to study the behaviour of TSP heuristics on large inputs.

The points are drawn pseudo-randomly and uniformly from
the square $[0,10000)\times[0,10000)$.    
I use the pseudo-random number generator Knuth implemented for the Stanford
GraphBase.  Its generator provides 31 bits at a time.  We treat these bits
as a random fraction in the interval $[0,1)$ and multiply them by the
scaling factor of 10000 to get the value of a coordinate.  
Now, $2^<13 < 10^5 < 2^14$, 
so about 14 bits are shifted
to the left of the decimal point.  So there are about useful 17 bits
to the right of the decimal point.  To make sure we output them all, we 
print the coordinates with eight decimal places.  This prints
at least 24 bits of the fraction, and ought to be read in faithfully 
by a good floating point number reading routine.


@d SIZE (10000)
@d TWO_TO_THE_31 ((double)((unsigned long) 0x80000000))

@c
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include "fixincludes.h"

#include "gb_flip.h"
#define SIZE (10000)
int main(int argc, char**argv) {
	int i,n;
	long s;
	if ( argc != 4 ) {
		fprintf(stderr,"Usage: %s <seed> <n> <name>\n",argv[0]); exit(1);
	}
	s=atol(argv[1]);
	n=atoi(argv[2]);
	gb_init_rand(s);
	printf("NAME: %s\n",argv[3]);
	printf("TYPE: TSP\n");
	printf("COMMENT: Automatically generated with seed %ld by unifd\n",s);
	printf("DIMENSION: %d\n",n);
	printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
	printf("NODE_COORD_SECTION\n");
	for (i=0;i<n;i++) {
		double x,y;
		x=( (SIZE*((double)gb_next_rand())) )/TWO_TO_THE_31;
		y=( (SIZE*((double)gb_next_rand())) )/TWO_TO_THE_31;
		printf("%7d %14.8f %14.8f\n",i+1,x,y);
	}
	printf("EOF\n");
	return 0;
}
