



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

{\obeylines
$Log: sier.w,v $
Revision 1.10  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.9  1997/09/27 18:04:13  neto
Fixed RCS log behaviour.

 Revision 1.8  1997/08/15  20:18:25  neto
 Added Index major section.

 Revision 1.7  1997/06/11  17:30:50  neto
 M\_PI is not a standard C library definition.  So I define my own PI.

 Revision 1.6  1997/05/16  18:14:55  neto
 Include <config.h>

 Revision 1.5  1997/01/28  22:05:40  neto
 Added proper logging.

}

@*Separated Sieripinski gaskets.
This program generates Euclidean TSP instances with points drawn randomly
uniformly from a ``separated Sierpinsky gasket''.  We play the chaos
game on four points, though I might make this a parameter in the future.


I expect these inputs to be quite hard for an unadorned
Lin-Kernighan heuristic.  I hope to prove the heuristic for
these kinds of clustered inputs.  This is research.

@
We play the chaos game  on four points.  (See Falconer, {\sl The Geometry of Fractal Sets} 
(CHECK THIS) or
Barnsley, {\sl Fractals Everywhere}.)

@ Old comments:

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


@d RADIUS (10000/2)

@c
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fixincludes.h"
#include "gb_flip.h"

int main(int argc, char**argv) {
	@<Process the command-line arguments@>@;
	@<Output a preamble@>@;
	@<Generate the data@>@;
	return 0;
}

@
@<Process the command-line arguments@>=
int cities,corners;
long seed;
double rotation, shrinkfactor;
char *name;
if ( argc != 7 ) {
	fprintf(stderr,
		"Usage: %s <seed> <cities> <corners> <shrinkfactor> <rotation> <name>\n",argv[0]);
	exit(1);
}
seed=atol(argv[1]);
cities=atoi(argv[2]);
if ( cities < 10 ) {
	fprintf(stderr,"Need at least 10 cities; only %d specified.\n",cities);
	exit(2);
}
corners=atoi(argv[3]);
shrinkfactor=atof(argv[4]);
rotation=atof(argv[5]);
name=argv[6];
gb_init_rand(seed);

@
@<Output a preamble@>=
printf("NAME: %s\n",name);
printf("TYPE: TSP\n");
printf("COMMENT: %s %s %s %s %s %s %s\n",
		argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
printf("DIMENSION: %d\n",cities);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");

@
@<Generate the data@>=
{ int i;
typedef double point_t[2];
point_t *corner, here={0.0,0.0};
@<Locate the corners@>@;
@<Prime the chaos game@>@;
@<Play the chaos game, with output@>@;
printf("EOF\n");
}


@ I need the value of $\pi$.  
On Linux, I get |M_PI| from \file{<math.h>}, but that doesn't work
under Solaris.  Upon examining Plauger's book {\sl The Standard C Library},
it appears that |M_PI| is not a required definition from a standard header.
So I just asked Maple for fifty digits of precision and pasted it here.

@d PI (3.1415926535897932384626433832795028841971693993751)
@<Locate the corners@>=

if ( (corner = malloc(sizeof(point_t)*corners)) == NULL ) {
	fprintf(stderr,"Couldn't allocate an array of %d corners\n",corners);
	exit(1);
}
{ const double shift=rotation*PI/180; /* |rotation|$ \times 2\pi / 360 $ */
for ( i=0;i<corners;i++ ) {
	corner[i][0] = RADIUS * cos( PI*2*((double)i)/corners + shift);
	corner[i][1] = RADIUS * sin( PI*2*((double)i)/corners + shift);
}
}

@  We take 500 steps to flush out the noise caused by starting at the origin.
If we ever have floating point numbers with more than 500 bits of mantissa,
then we should lengthen this priming stage.

@<Prime the chaos game@>=
for (i=0;i<500;i++) {
	@<Take a step@>@;
}


@
@<Play the chaos game, with output@>=
for (i=0;i<cities;i++) {
	@<Take a step@>@;
	printf("%7d %24.19f %24.19f\n",i+1,here[0],here[1]);
}

@  Yes, it's this easy.
@<Take a step@>=
{const int c=gb_unif_rand(corners);
here[0] = (1-shrinkfactor) * here[0] + shrinkfactor * corner[c][0];
here[1] = (1-shrinkfactor) * here[1] + shrinkfactor * corner[c][1];
}

@*Index.
