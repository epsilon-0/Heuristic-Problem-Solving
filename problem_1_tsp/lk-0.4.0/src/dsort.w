


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
$Log: dsort.w,v $
Revision 1.134  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.133  1998/04/11 14:34:37  neto
 Duh.  select is a Unix system call.  Renamed my select to select_range

Revision 1.132  1998/04/10 20:51:30  neto
Added select function to do order range selection.

Revision 1.131  1997/09/27 18:05:36  neto
Fixed RCS log behaviour.

Revision 1.130  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.129  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.128  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.127  96/12/16  14:12:13  neto
Changed owner to neto.

Revision 1.126  1996/08/23  17:46:26  david
Fixed bitwise or and TeX problem.

Revision 1.125  96/08/16  17:56:59  neto
Broke a comment to make it go to dvi

Revision 1.124  96/08/15  15:17:17  neto
Document the pointer alignment warning.

Revision 1.123  96/08/15  14:11:05  neto
Import our own interface.

Revision 1.122  96/08/15  13:10:14  neto
Make it pass -Wall

Revision 1.121  96/08/14  14:38:04  neto
Initial revision

}

@*DSORT.
This module implements two functions.

Procedure |dsort| is a deterministic sorting function
with the same interface as the Standard C Library function |qsort|.
That is,
|dsort(void *A, size_t n, size_t es, 
int (*cmp)(const void *,const void *))| sorts the $n$ elements in array
|A| into non-decreasing order using comparison function |cmp|; each element
has size |es| bytes.
The function |dsort| is an implementation of the 
|qsort| algorithm as described by Bentley \&
McIlroy.

Sometimes sorting a whole array is overkill.  In some situations all 
we need to do is find a subrange of ordered items within an array, for example,
the 43rd through the 199th smallest items in an array.  
This is a generalization of sorting, and can save us a lot of work.
The type signature of |select| is
|select_range(void *A, size_t n, size_t es, 
int (*cmp)(const void *,const void *), int lo, int hi, int sorted)|.
The first four parameters are the same as |dsort|.  
Procedure |select_range| finds the elements that are the |lo| through |hi-1|
least elements of the array (according to |cmp|) and puts them 
into consecutive positions
|lo| through |hi-1| inside the array, and returns a pointer to 
position |lo| in
the array.
If |sorted| is non-zero, then they are also sorted.
As an example, |dsort(A,n,es,cmp)| can be implemented as
|select_range(A,n,es,cmp,0,n,1)|.  
(Actually, this isn't true because |select_range| 
uses |dsort|! But that can be fixed.)
If |lo| or |hi| are out of bounds, |select_range|
returns |NULL|.

The outline of this module is as follows:

@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Type definitions@>@;
@<Module subroutines@>@;
@<Subroutines@>@;
const char *dsort_rcs_id = "$Id: dsort.w,v 1.134 1998/07/16 21:58:55 neto Exp neto $";

@ The exported interface is contained in the \file{dsort.h} header file,
which has the following form.

@(dsort.h@>=
extern const char *dsort_rcs_id;
@<Exported subroutines@>@;

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "dsort.h"

@*1 Deterministic sorting.
Under SunOS, the |qsort| library function does not return repeatable 
results.  At one point, on identical inputs, my deterministic program
was returning different answers in 500 seconds and 1100 seconds,
all because |qsort| wasn't deterministic.  For the purposes of
repeatable experiments, this module implements a deterministic sort function
|dsort|.
It is taken pretty much verbatim from Bentley and McIlroy INSERT
REFERENCE, which is an implementation of Quicksort.

@ @<Type definitions@>=
typedef long WORD;

@ Bentley and McIlroy say ``The strange formula to check data size and 
alignment works even on Cray computers, where plausible code such
as |(((long)a) |$\,\mid\,$| es) % sizeof(long)| fails because the least significant
part of a byte address occupies the most significant part of a  |long|.''

Some compilers, such as GCC, may complain about the |swap| macro because
it uses a cast that increases the alignment requirement of the pointers 
it dereferences.  Specifically, a |char| pointer may 
point to any byte, but the cast to a |WORD|/|long| pointer may force
it to a word boundary.    But the definition and use of |swaptype| makes
sure this is only done when it is legal.
@^warnings@>
@^pointer alignment@>
@^alignment, pointer@>
@^system dependencies@>

@d W sizeof(WORD) 	/*Must be a power of 2 */
@d SWAPINIT(a,es) swaptype =  ((a-(char*)0)|es) % W ? 2 : es > W  ? 1 : 0
@d exch(a,b,t) (t=a,a=b,b=t)
@d swap(a,b) swaptype != 0 ? swapfunc(a,b,es,swaptype) : (void)exch(*(WORD*)(a),*(WORD*)(b),t)
@d vecswap(a,b,n) if(n>0)swapfunc(a,b,n,swaptype)

@<Module subroutines@>=
static void
swapfunc(char *a, char *b, size_t n, int swaptype) {
	if ( swaptype <= 1 ) {
		WORD t;
		for ( ; n > 0 ; a+= W, b+= W, n-=W ) 
			exch(*(WORD*)a,*(WORD*)b,t);
	} else {
		char t;
		for ( ; n > 0 ; a+= 1, b+= 1, n-=1 ) 
			exch(*a,*b,t);
	}
}

static char *
med3(char *a, char *b, char *c, int (*cmp)(const void *a, const void *b)) {
	return 
	cmp(a,b)<0 
	? 	(cmp(b,c)<0?b:cmp(a,c)<0?c:a) 
	:	(cmp(b,c)>0?b:cmp(a,c)>0?c:a);
}
	
@ 
@<System headers@>=
#include <stddef.h>


@ Here's the sorting function itself.  It appears as Program 7 in the article.

@d min(a,b) ((a)<(b)?(a):(b))

@<Subroutines@>=
void 
dsort(void *aa, size_t n, size_t es, int (*cmp)(const void *,const void *)) 
{
	char *a = (char *)aa, *pa, *pb, *pc, *pd, *pl, *pm, *pn, *pv;
	int r, swaptype;
	WORD t, v;
	size_t s;
	SWAPINIT(a,es);
	if ( n<7) { /* Insertion sort on smallest arrays. */
		for (pm =a+es;pm <a+n*es;pm+=es)
			for(pl=pm;pl>a&&cmp(pl-es,pl)>0;pl-=es) {
				swap(pl,pl-es);
			}
		return;
	}
	@<Find a partition point |pm|@>@;
	@<Partition around the value in |pm|@>@;
	pn = a+n*es;
	s = min(pa-a, pb-pa);    vecswap(a, pb-s,s);
	s = min(pd-pc,pn-pd-es); vecswap(pb,pn-s,s);
	if ( (s=pb-pa)>es) dsort(a,   s/es,es,cmp);
	if ( (s=pd-pc)>es) dsort(pn-s,s/es,es,cmp);
}
@
@<Exported subroutines@>=
extern void 
dsort(void *a, size_t n, size_t es, int (*cmp)(const void *,const void *));


@
@<Find a partition point |pm|@>=
pm =a +(n/2)*es; /*Small arrays, middle element */
if (n>7) {
	pl=a;
	pn=a+(n-1)*es;
	if (n>40) { /* Big arrays, pseudo-median of 9 */
		s = (n/8)*es;
		pl=med3(pl,pl+s,pl+2*s,cmp);
		pm=med3(pm-s,pm,pm+s,cmp);
		pn=med3(pn-2*s,pn-s,pn,cmp);
	}
	pm=med3(pl,pm,pn,cmp);	/* Mid-size, median of three */
}

@
@d PVINIT(pv,pm) if (swaptype != 0) pv=a, swap(pv,pm); else pv=(char*)&v, v=*(WORD*)pm
@<Partition around the value in |pm|@>=
PVINIT(pv,pm);	/* |pv| points to partition value */
pa=pb=a;
pc=pd=a+(n-1)*es;
for(;;) {
	while(pb<=pc&&(r=cmp(pb,pv))<=0) {
		if (r==0) {swap(pa,pb); pa+= es;}
		pb+=es;
	}
	while(pc>=pb&&(r=cmp(pc,pv))>=0) {
		if (r==0) {swap(pc,pd); pd-= es;}
		pc-=es;
	}
	if ( pb>pc) break;
	swap(pb,pc);
	pb+=es;
	pc-=es;
}

@*1 Selection.
Function |select_range| first checks for trivial cases.

We use the same partitioning scheme as |dsort|.
We save time by not sorting the portions of the array that are out of
the |lo| to |hi| range.

@<Subroutines@>=
void *
select_range(void *aa, size_t n, size_t es, 
int (*cmp)(const void *,const void *), int lo, int hi, int sorted)
{
	char *a = (char *)aa, *pa, *pb, *pc, *pd, *pl, *pm, *pn, *pv;
	int r, swaptype;
	WORD t, v;
	size_t s;

	@<Trivial |select_range| cases@>@;
	SWAPINIT(a,es);
	@<Non-trivial small cases@>@;
	@<Find a partition point |pm|@>@;
	@<Partition around the value in |pm|@>@;
	@<Possibly select on either side of the partition value@>@;
}
@
@<Exported subroutines@>=
extern void *
select_range(void *a, size_t n, size_t es, int (*cmp)(const void *,const void *),
int lo, int hi, int sorted);

@
@<Trivial |select_range| cases@>=
if ( n < 0 ) return NULL;
if ( n <= 1 ) return aa;
if ( lo < 0 || lo >= n) return NULL;
if ( hi < lo || hi > n ) return NULL;
if ( lo == 0 && hi == n ) { if (sorted) dsort(aa,n,es,cmp); return aa; }


@ We just sort small arrays and answer the right pointer.
@<Non-trivial small cases@>=
if ( n<7) { /* Insertion sort on smallest arrays. */
	for (pm =a+es;pm <a+n*es;pm+=es)
		for(pl=pm;pl>a&&cmp(pl-es,pl)>0;pl-=es) {
			swap(pl,pl-es);
		}
	return a+lo*es;
}

@ At this point values equal to the pivot are in locations
|aa| up to but not including |pa|; 
values less than the pivot are
in locations from
|pa| up to but not including |pb|;
values greater than the pivot are
in locations from
|pb| up to and including |pd|;
still other values greater equal to the pivot are
in locations from
|pd+es| up to but not including |pn|; finally, |pc=pb-es|.

@<Possibly select on either side of the partition value@>=
pn = a+n*es;
{
const int 
ai = (pa-a)/es,
bi = (pb-a)/es,
ci = (pc-a)/es,
di = (pd-a)/es;
const size_t
right_greater = di-ci,
right_equal = n-di-1,
left_less = bi-ai;
const int
hi_wrt_greater=hi-bi-right_equal,
lo_wrt_greater=lo-bi-right_equal;

if ( hi > bi ) { /* Right end of range to the right of the pivot. */
	s=min(pd-pc,pn-pd-es); vecswap(pb,pn-s,s);/* Swap greater with righthand equals. */
	if ( hi_wrt_greater > 0 ) { /* Right end of range in greater part.  */
		const int new_lo = lo_wrt_greater<0?0:lo_wrt_greater;
		if (right_greater>1)
			(void)select_range(pn-right_greater*es,right_greater,es,cmp,
					new_lo,hi_wrt_greater,sorted);
	}
} 

if ( lo < bi ) { /* Left end of range to the left of the pivot. */
	s=min(pa-a,pb-pa);vecswap(a,pb-s,s); /* Swap lesser with lefthand equals.*/
	if ( lo < left_less ) { /* Left end of range in lesser part. */
		const int new_hi = hi <= left_less ? hi : left_less;
		if (left_less > 1)
			(void)select_range(a,left_less,es,cmp,lo,new_hi,sorted);
	}
}
}
return a+lo*es;

@ Here's a simple program to test |select_range|.  You'll have to inspect the
output yourself...  :-)

The |select_range| code worked the first time, but as usual, I had a bug in the
testing code.  Doh!

@(dsorttest.c@>=
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "dsort.h"
static int
cmp_char(const void * aa, const void * bb) 
{
	return *(const char *)aa - *(const char *)bb;
}

static void
test_string(const char *s)
{
	size_t len=strlen(s);
	int l,h, sorted;
extern char *strdup(const char*s);
	char *p, *ss=strdup(s);
	printf("dsorttest Testing \"%s\"\n",s);
	qsort(ss,len,sizeof(char),cmp_char);
	printf("          Sorted: \"%s\"\n",ss);
	for (l=0;l<len;l+=1) {
		for (h=l+1;h<=len;h+=1) {
			for(sorted=0;sorted<2;sorted++) {
				strcpy(ss,s);
				p=select_range(ss,len,sizeof(char),cmp_char,l,h,sorted);
				printf("                  \"%s\" l=%d h=%d ", ss,l,h);
				ss[h]='\0';
				printf("result=\"%s\" sorted=%d\n",p,sorted);
			}
		}
	}
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
