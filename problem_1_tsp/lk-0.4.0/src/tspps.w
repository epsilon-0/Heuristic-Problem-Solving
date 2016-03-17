


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

\def\9#1{{\sl #1}}
{\obeylines
$Log: tspps.w,v $
Revision 1.2  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.1  1997/12/17 15:44:56  neto
Initial revision

}

@*TSPPS.
This program takes an instance of the Traveling Salesman Problem (TSP) and
outputs it graphical form.
The input is a two-dimensional instance TSPLIB form, 
and the output is in PostScript.
The input is taken from the standard input stream, and the output
goes onto the standard output stream.
@^TSPLIB@>
@^PostScript@>

@ The outline of this program is as follows.


@c

const char *prog_name = "tspps";
const char *tspps_rcs_id = "$Id: tspps.w,v 1.2 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
#include "lkconfig.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
@<System headers@>@;
@<Module headers@>@;

@<Global variables@>@;

@<Module subroutines@>@;

int main(int argc, char **argv) 
{
	@<Write the PostScript prolog@>@;
	@<Write the instance data@>@;
	@<Close up@>@;
	return 0;
}

@ The PostScript prolog contains PostScript language procedures used by
the rest of the output.  For now, we assume that the prolog is accessible
from the current directory.

@<Write the PostScript prolog@>=
{
FILE *prolog;
char buf[8192];
size_t countin, countout;
prolog = fopen("prolog.ps","r");
errorif( prolog==NULL,"Couldn't open prolog.ps for reading");
while ( (countin=fread(buf,1,8192,prolog)) > 0 ) {
	char *p=buf;
	while ( (countout=fwrite(p,1,countin,stdout)) < countin ) {
		countin-=countout; p+= countout;
	}
}
fclose(prolog);
}

@ We've used the error handling routines, so we need their definition.
@<Module headers@>=
#include "error.h"

@ Now, the instance reading routine happens to be able to write
instance-specific coordinates.
We just have to tell it where to put it.
The only extra job we have to do is to write the title and the comment.

@<Write the instance data@>=
{tsp_instance_t *tsp;
tsp=read_tsp_file(stdin,stdout);
if ( tsp->name ) write_PS_string(stdout,tsp->name),printf(" title\n");
if ( tsp->comment ) write_PS_string(stdout,tsp->comment),printf(" comment\n");
}

@ There is a slight complication.  PostScript strings are delimited by
parentheses.  So we must escape any parentheses in the string to be
printed.

For the rules on PostScript strings, see {\sl PostScript Language 
Reference Manual}, Adobe Systems Incorporated.  I used the second edition.
@:PostScript Language Reference Manual@>
@^Adobe Systems Incorporated@>

@<Module subroutines@>=
static void write_PS_string(FILE *out,char *str);
static void
write_PS_string(FILE *out,char *str) 
{
	char *p;
	fputc('(',out);
	for (p=str;*p;p++) {
		if ( *p=='(' || *p==')' || *p=='\\' ) fprintf(out,"\\%c",*p); 
		else if ( isprint(*p) ) fputc(*p,out); 
		else fprintf(out,"\\%3o",*p);
	}
	fputc(')',out);
}

@ We need the character classifier macro |isprint|.
@<System headers@>=
#include <ctype.h>

@ We need the definition of the reading routine.  In turn, the
\module{READ} module requires definitions of the |length_t| type.
@<Module headers@>=
#include "length.h"
#include "read.h"

@ The reading routine also needs to know whether to round distances.
That facility is not used here, but we need to define it anyway.
@<Global variables@>=
int noround=1;

@ 
The prolog introduces a new graphics scope and a new dictionary scope.
To finish up, we need to close both up, tell the page to print itself,
and finally 
add an end-of-file comment post-processors can use.

@<Close up@>=
fputs("end\n",stdout);
fputs("grestore\n",stdout);
fputs("showpage\n",stdout);
fputs("%%EOF\n",stdout);

@*Index.