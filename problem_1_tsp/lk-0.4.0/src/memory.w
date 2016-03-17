



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
$Log: memory.w,v $
Revision 1.116  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.115  1998/02/13 21:16:30  neto
Made prototypes and function declarations match w.r.t. const.

Revision 1.114  1997/10/28  20:41:47  neto
Fixed comments to compile.

Revision 1.113  1997/09/27 18:06:21  neto
Fixed RCS log behaviour.

Revision 1.112  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.111  1997/06/16  16:05:26  neto
Make the report prettier.

Revision 1.110  1997/06/04  20:57:55  neto
Removed const modifiers on some prototypes.  Explicit cast to
size t in mem calloc call.

Revision 1.109  1997/06/04  20:51:03  neto
Added prototype for mem calloc.

Revision 1.108  1997/05/23  20:28:49  neto
Added interface to calloc.

Revision 1.107  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.106  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.105  96/09/19  15:26:37  neto
Removed useless "const".

Revision 1.104  96/08/16  13:10:10  neto
Fixed the file reference to fixincludes.h

Revision 1.103  96/08/16  13:05:00  neto
Added fixincludes.

Revision 1.102  96/07/29  17:08:23  neto
Fixed to compile

Revision 1.101  96/07/29  16:20:05  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*Memory management.
We treat memory very simply: if we can't allocate the space required,
then just exit the program with a message and error code.

@c
#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fixincludes.h"

#include "error.h"
#include "memory.h"
const char *memory_rcs_id="$Id: memory.w,v 1.116 1998/07/16 21:58:55 neto Exp neto $";

static unsigned long mem_total = 0, mem_max = 0;

void mem_usage_reset(void) { mem_total = 0; }
void mem_deduct(unsigned long n) { mem_total -= n; }
void mem_report(void) {
	printf("Maximum memory usage (UNRELIABLE): %ld bytes\n", mem_max);
}




void *
mem_alloc(const size_t n)
{
	void *p;
	errorif(n<0,"Can't allocate fewer than zero bytes: %d\n",n);
	p=malloc(n);
	errorif(p==NULL,"Couldn't allocate %ld bytes.",(long int)n);
	mem_total += n;
	if ( mem_total > mem_max ) mem_max = mem_total;
	return p;
}

void *
mem_calloc(const size_t nmemb, const size_t size)
{
	void *p;
	errorif(nmemb<0,"Can't allocate fewer than zero elements: %d\n",nmemb);
	errorif(size<0,"Element size can't be negative: %d\n",size);
	p=calloc(nmemb,size);
	errorif(p==NULL,"Couldn't allocate %ld bytes.",(long int)(nmemb*size));
	mem_total += nmemb*size;
	if ( mem_total > mem_max ) mem_max = mem_total;
	return p;
}

void *
mem_realloc(void *ptr, size_t n) {
	void *p;
	errorif(n<0,"Can't allocate fewer than zero bytes: %d\n",n);
	p=realloc(ptr,n);
	errorif(p==NULL,"Couldn't reallocate %ld bytes.",(long int)n);
	mem_total += n;
	if ( mem_total > mem_max ) mem_max = mem_total;
	return p;
}

char *
dup_string( const char *s )
{
	char *p;
	char *strdup(const char *);
	p=strdup(s);
	errorif(p==NULL,"Couldn't duplicate string \"%s\".",s);
	return p;
}
@ We also supply some macros to make things a little more convenient.

|free_mem(p)| requires |p| to be an lvalue because it ends up
assigning |NULL| to |p|.

@(memory.h@>=
extern const char *memory_rcs_id;

void *mem_alloc(const size_t);
void *mem_calloc(const size_t nmemb, const size_t size);
void *mem_realloc(void *,size_t);
char *dup_string(const char *);
void mem_usage_reset(void);
void mem_deduct(unsigned long n);
void mem_report(void);
#define new_of(t)  ((t *)mem_alloc(sizeof(t)))
#define new_arr_of(t,n)  ((t *)mem_alloc(sizeof(t)*(n)))
#define new_arr_of_zero(t,n)  ((t *)mem_calloc((size_t)(n),sizeof(t)))
#define free_mem(p)	do {if (p!=NULL) {free((void *)p);} p = NULL;} while (0)

@*Index.
