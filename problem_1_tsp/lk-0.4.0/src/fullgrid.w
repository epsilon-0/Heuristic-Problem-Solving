



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

@*Full grid Euclidean TSP instances.
This program generates grid Euclidean TSP instances in the
TSPLIB format (INSERT REFERENCE).    
These instances are good for debugging space-filling curve code, because the
Moore curve is an optimal tour for them.

@d SIZE (10000)
@d TWO_TO_THE_31 ((double)((unsigned long) 0x80000000))

@c
#include <stdio.h>
#include <stdlib.h>
#include "fixincludes.h"

#define SIZE (10000)
int main(int argc, char**argv) {
	int i,j,n, levels,onedn;
	if ( argc != 3 ) {
		fprintf(stderr,"Usage: %s <levels> <name>\n",argv[0]); exit(1);
	}
	levels=atoi(argv[1]);
	for (i=0,onedn=n=1;i<levels;n*=4,onedn*=2,i++);
	printf("NAME: %s\n",argv[2]);
	printf("TYPE: TSP\n");
	printf("COMMENT: Generated with %d levels by fullgrid\n",levels);
	printf("DIMENSION: %d\n",n);
	printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
	printf("NODE_COORD_SECTION\n");
	for (i=0;i<onedn;i++) 
		for (j=0;j<onedn;j++) {
		double x,y;
		x= SIZE * (((double)i)/onedn + 0.5/onedn);
		y= SIZE * (((double)j)/onedn + 0.5/onedn);
		printf("%7d %14.8f %14.8f\n",onedn*i+j+1,x,y);
	}
	printf("EOF\n");
	return 0;
}
