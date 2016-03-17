


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
$Log: pq.w,v $
Revision 1.4  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.3  1998/06/19 16:24:48  neto
oops, added CWEB stuff to include pq set print func routine.

Revision 1.2  1998/06/19 15:17:58  neto
Added printing support, sort of.

Revision 1.1  1998/06/13 22:59:54  neto
Initial revision

}


@*Priority Queues.
This is yet another implementation of priority queues based on
a binary heap.  If all you need is a priority queue, then this is
more efficient than using a |dict|. 
(Tests with Wayne Hayes. Thanks Wayne!)

@
A \term{binary heap} is an 
array |A| with entries |A[1]| through |A[last_elem_i]|
with invariant that 
|A[i/2] <= A[i]| whenever
|1 < i <= last_elem_i|.

Algorithms for insertion and deletion of the minimum item take
$O(\log n)$ time if there are already |n| items in the heap.

@c

#include <stdlib.h>
#include <stddef.h>
#include "pq.h"
#include "error.h"

@<Subroutines@>@;

@
@(pq.h@>=
@<Type definitions@>@;
@<Exported subroutines@>@;


@
@<Exported subroutines@>=
pq_t *pq_create			(pq_cmp_func_t cmp);
pq_t *pq_create_size	(pq_cmp_func_t cmp, int n);
void pq_destroy			(pq_t *pq);
void pq_make_empty		(pq_t *pq);
void pq_insert			(pq_t *pq, void *payload);
void *pq_delete_min		(pq_t *pq);
void *pq_min			(pq_t *pq);
int pq_empty			(pq_t *pq);
void pq_set_print_func	(pq_t *pq, void (*print_func)(void *));

@
@<Type definitions@>=
typedef int (*pq_cmp_func_t)(const void*,const void*);

typedef struct {
	void **A;
	int A_size;
	int last_elem_i;
	pq_cmp_func_t cmp;
	void (*print_func)(void *);/* Used for printing nodes while debugging.*/
} pq_t;

@
@<Subroutines@>=
pq_t *
pq_create(pq_cmp_func_t cmp)
{
	return pq_create_size(cmp,1023);
}

pq_t *
pq_create_size(pq_cmp_func_t cmp, int n)
{
	pq_t *pq=malloc(sizeof(pq_t));
	if ( pq ) {
		pq->cmp=cmp;
		pq->last_elem_i=0;
		pq->A_size = 1+((n<63) ? 63 : n);
		pq->A = malloc(sizeof(void*)*pq->A_size);
		errorif(pq->A==NULL,"Couldn't allocate a heap array of %d bytes",sizeof(void*)*pq->A_size);
	}
	return pq;
}

@
@<Subroutines@>=
void
pq_make_empty(pq_t *pq)
{
	pq->last_elem_i=0;
}

@
@<Subroutines@>=
void
pq_destroy(pq_t *pq)
{
	if ( pq ) {
		if ( pq->A )@+ {@+ free(pq->A); @+ pq->A=NULL;@+}
		pq->last_elem_i=0;
		pq->A_size=0;
		free(pq);
	}
}

@
@<Subroutines@>=
int
pq_empty(pq_t *pq)
{
	return pq->last_elem_i == 0;
}

@ First we need to see if we have to grow the array.

Then we insert the new element at the bottom of the array and percolate
it up to its natural spot according to the invariant.

@d SWAP(x,y) { void *t=x; x=y; y=t; }

@<Subroutines@>=
void 
pq_insert(pq_t *pq, void *payload)
{
	pq_cmp_func_t cmp=pq->cmp;
	int i = pq->last_elem_i + 1;
	void **A;
	if ( i >= pq->A_size ) {
		pq->A_size *= 2;
		pq->A = realloc(pq->A,sizeof(void*)*pq->A_size);
		errorif(pq->A==NULL, "pq_insert: realloc failed: couldn't grow array");
	}
	A = pq->A;
	A[i] = payload;
	while ( i > 1 && cmp(A[i/2],A[i]) > 0 ) {
		SWAP(A[i],A[i/2]);
		i /= 2;
	}
	pq->last_elem_i++;
	@<Print the current array.@>
}

@
@<Print the current array.@>=
#if PQ_DEBUGGING_CHARS
{int i;
for (i=1;i<=pq->last_elem_i; i++) {
	putchar(*(char *)pq->A[i]);
}
putchar('\n');
}
#endif

@
@<Subroutines@>=
void *
pq_min(pq_t *pq)
{
	return pq->last_elem_i ? pq->A[1] : NULL;
}

@
@<Subroutines@>=
void *
pq_delete_min(pq_t *pq)
{
	if ( pq->last_elem_i ) {
		void **A=pq->A;
		void *the_min=A[1];
		A[1]=A[pq->last_elem_i--];
		@<Sink |A[1]| down as far as it needs to go@>@;
		@<Print the current array.@>
		return the_min;	
	} else { return NULL; }
}


@  The only tricky bit here is that we don't want to run off the end
of the array.

@<Sink |A[1]| down as far as it needs to go@>=
{ 
const int last_elem_i = pq->last_elem_i;
pq_cmp_func_t cmp=pq->cmp;
int i, next_i;
for (i=1, next_i=0; i ; i = next_i, next_i=0) {
	const int child1 = i*2, child2=child1+1;
	if ( child2 <= last_elem_i ) {
		const int least_child = cmp(A[child1],A[child2]) < 0 ?  child1 : child2;
		if ( cmp(A[i],A[least_child]) > 0 ) {
			SWAP(A[i],A[least_child]);
			next_i=least_child;
		}
	} else if ( child1 <= last_elem_i && cmp(A[i],A[child1]) > 0 ) {
		SWAP(A[i],A[child1]);
		next_i = child1;
	}
}
}

@  While debugging it is useful to be able to print a node.
Here's how we set the function.

@<Subroutines@>=
void 
pq_set_print_func(pq_t *pq, void (*print_func)(void *))
{
	pq->print_func = print_func;
}

@*Testing.

Here's a simple program to test this module, though certainly not
exhaustively.  
You'll have to inspect the output yourself...  :-)



@(pqtest.c@>=
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "pq.h"

void
pqsort(void *a,size_t len,size_t es,pq_cmp_func_t cmp);
void
pqsort(void *a,size_t len,size_t es,pq_cmp_func_t cmp)
{
	int i;
	const int n=len/es;
	pq_t *pq = pq_create_size(cmp,n);
	void *copy= malloc(len);
	errorif(copy==NULL,"Couldn't allocate copy array.");
	memcpy(copy,a,len);
	for (i=0;i<n;i++) {
		pq_insert(pq,((char *)copy)+es*i);
	}
	for (i=0;i<n;i++) {
		void *m=pq_min(pq);
		void *dm;
		void *dest, *src;
		errorif(pq_empty(pq),"empty!");
		dm = pq_delete_min(pq);
		errorif(m!=dm,"min not same as delete_min");
		src=m;
		dest=((char*)a)+i*es;
		memcpy(dest,src,es);
	}
	errorif(!pq_empty(pq),"not empty!");
	pq_destroy(pq);
}

static int
cmp_char(const void * aa, const void * bb) 
{
	return *(const char *)aa - *(const char *)bb;
}

static void
test_string(const char *s)
{
	size_t len=strlen(s);
extern char *strdup(const char*s);
	char *ss=strdup(s);
	printf("pqtest    Testing \"%s\"\n",s);

	pqsort(ss,len,sizeof(char),cmp_char);
	printf("   Heap   Sorted: \"%s\"\n",ss);

	strcpy(ss,s);
	qsort(ss,len,sizeof(char),cmp_char);
	printf("          Sorted: \"%s\"\n",ss);
	free(ss);
}

int main(int argc, char **argv)
{
	int i;
	test_string("abcdefghijklmnopqrstuvwx");
	test_string("xwvutsrqponmlkjihgfedcba");
	test_string("David Neto was here");
	for (i=0;i<argc;i++) 
		test_string(argv[i]);
	return 0;
}



@*Index.
