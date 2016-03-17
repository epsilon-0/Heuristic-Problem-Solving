


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

@*A distance calculator for TSPLIB files.

@c
#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "length.h"
#include "read.h"@;

@<Subroutines@>@;

@
@<Subroutines@>=
int noround=1;
int 
main(int argc, char **argv) {
	char const * TSPLIB_in = "../data/lin105.tsp";
	tsp_instance_t *tsp;
	FILE *TSPLIB_file;
	int a, b;
	if (argc > 1) {
		TSPLIB_in = argv[1];
	}
	if ( NULL==(TSPLIB_file=fopen(TSPLIB_in,"r")) ) {
		fprintf(stderr,"Couldn't open %s for reading\n",TSPLIB_in);
		exit(1);
	}
	tsp = read_tsp_file(TSPLIB_file,NULL);
	while( scanf(" %d %d",&a,&b) == 2 ) {
		if ( a < 0 || a > tsp->n ) {
			printf("a=%d is out of range [0,%d)\n",a,tsp->n);
			continue;
		}
		if ( b < 0 || b > tsp->n ) {
			printf("b=%d is out of range [0,%d)\n",b,tsp->n);
			continue;
		}
		printf("cost(%d,%d)=="length_t_spec"\n",a,b,cost(a,b));
	}
	return 0;
}

@*Index.
