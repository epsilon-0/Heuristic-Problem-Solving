



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
$Log: pool.w,v $
Revision 1.110  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.109  1997/09/27 18:05:01  neto
Fixed comment and RCS log behaviour.

Revision 1.108  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.107  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.106  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.105  96/08/16  13:21:27  neto
Go through long * instead of char *.  This doesn't trigger the cast
warning from GCCC.

Revision 1.104  96/08/15  15:09:57  neto
Documented the alignment increase.

Revision 1.103  96/08/02  14:19:29  neto
Allow multiple includes of our interface.

Revision 1.102  96/07/29  17:07:56  neto
Fixed to compile.

Revision 1.101  96/07/29  16:20:07  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*Pool-oriented memory allocation.
Sometimes programs perform many allocations and deallocations.  
This is especially true of programs that perform some irregularly structured
computation.

Parallelizing such a program can lead to poor results because the memory
allocator is often serialized on parallel machines.  For example, the
KSR memory allocator is surrounded by a strict single-lock protocol: each
allocation or deallocation is preceded by a lock  and followed by
an unlock of a fixed lock variable.  This can be disastrous for performance.


How do we greatly reduce this contention?  One answer is to use our own
allocator built on top of the system-wide one, making sure that 
requests from different processors may be  serviced concurrently.

An elegant way to do this is to use a pool-oriented allocator.  Each
processor (or thread) creates a pool of memory for the exclusive use
of each class of objects it will be allocating.  For example, one
pool would be created for tree nodes, one pool for linked list nodes,
\etc.

@ The interface of the pool-oriented allocator is as follows.

|pool_t *pool_create(size_t os, int bs)| takes an object size |os|
and a block size |bs|.  The 
system-wide allocator will be asked to provide space for at least
|bs| user-level 
objects at a time.

|void pool_destroy(pool_t *p)| destroys the given pool.

|void *pool_alloc(pool_t *p)| allocates a single object from the given pool.

|void pool_free(pool_t *p, void *obj)| deallocates the given object from 
the given pool.  If the object does not belong to that pool, or the
object has not been allocated since the last
deallocation from that pool, then the results are undefined.
Thus, take great care.

@ The outline of this module is as follows.
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Subroutines@>@;
const char *pool_rcs_id="$Id: pool.w,v 1.110 1998/07/16 21:58:55 neto Exp neto $";

@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

@ The exported interface is contained in the \file{pool.h} header file,
which has the following form.

@(pool.h@>=
#if !defined(_POOL_H_)
#define _POOL_H_
extern const char *pool_rcs_id;
@<Exported types@>@;
@<Exported subroutines@>@;
#endif

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "pool.h"


@ Each pool is a linked list of blocks.  Each block maintains a free list.
For simplicity, we store the object size and the block size in each
node in the list.

@<Exported types@>=
typedef struct pool_block_freelist_s {
	struct pool_block_freelist_s *next;
} pool_block_freelist_t;

typedef struct pool_s {
	struct pool_s *next;
	size_t os;
	int bs;
	void *block;
	pool_block_freelist_t *freelist_head;
} pool_t;

@ The only trick to the allocation routine is to make sure the
object size is rounded up so that every object we give back to the
user is aligned for any object.

Of course, this is system-dependent, but rounding up to 
a |MINIMUM_GRANULARITY| of 8 bytes should do
on any machine we're likely to port this program to.
@^system dependencies@>

@d MINIMUM_GRANULARITY 8

@<Subroutines@>=
pool_t *
pool_create(size_t os,int bs) {
	pool_t *p;

	if ( os % MINIMUM_GRANULARITY ) os += MINIMUM_GRANULARITY - (os % MINIMUM_GRANULARITY);
	errorif(bs<1,"Need a positive block size");
	p = new_of(pool_t);
	p->next = NULL;
	p->os = os;
	p->bs = bs;
	p->block = mem_alloc(os*bs);
	@<Initialize the free list@>@;
	return p;
}

@ We've used the error checking and memory allocations routines.
We need their definitions.

@<Module headers@>=
#include "error.h"
#include "memory.h"

@ We need to export the creation routine.
@<Exported subroutines@>=
pool_t *pool_create(size_t os,int bs);

@
The free list initially is is a linked list of all the cells.  Each
points to the next, and the last is a null pointer.

The size of these cells have been rounded up to be multiples of 
|MINIMUM_GRANULARITY|.  Let's hope that the granularity is large
enough so that all alignment requirements are met.   In stepping
through the block, we increment the pointer by an appropriate number
not bytes.  Incrementing by adding values to a 
|char *| and then casting back to |pool_block_freelist_t *|
gets a warning from GCC about the cast 
increasing the alignment requirement of
the pointer.  So we go through a word pointer instead.  Hopefully, 
a |long *| will do.
@^system dependencies@>

%We need to be able to compute addresses in byte-size chunks.
%So we need a synonym for |byte|.  On most machines this is |char|.
%If the size of |byte| ever gets larger than 1 or can't be arbitrarily
%byte-aligned, then this bit of code will overrun the end of the allocated
%block.
%%
%Some compilers, such as GCC, will complain that the cast  from |byte *| to 
%|pool_block_freelist_t *| increases the alignment requirement of the pointer.
%This is ok; the warning can be ignored on most 32-bit architectures.

@d byte char
@<Initialize the free list@>=
{
int i;
pool_block_freelist_t *fl, *next;

for ( fl = p->freelist_head = (pool_block_freelist_t*)p->block, i=0; 
	  i<bs-1 ; 
	  i++ ) {
	next = (pool_block_freelist_t*)(((long *)fl)+os/sizeof(long));
	fl->next = next;
	fl = next;
}
fl->next = NULL;
}



@ Destroying a pool is easy.  Just deallocate every block on the list, and
every pool node on the list.

@<Subroutines@>=
void pool_destroy(pool_t *p) {
	while (p) {
		pool_t *next = p->next;
		free_mem(p->block);
		free_mem(p);
		p = next;
	}
}

@ We need to export the destruction routine.
@<Exported subroutines@>=
void pool_destroy(pool_t *p);

@ Allocation is easy if there is space on the free list.
I assume that the pool is valid.  (In particular, this means |p != NULL| upon
entry.)

If there isn't space on the free list, then we neeed to find the
first block that does have free space.  If no blocks have free space,
then we allocate a new block.  But we make the new one twice as large as
the largest so far.  This way we still get good performance in case the
user picked a too-small block size, and they are allocating a very
large number of objects in a row.


@<Subroutines@>=
void *
pool_alloc(pool_t *p) {
	pool_t *last_p;
	void *ret;
	for ( last_p = p; p && p->freelist_head == NULL; last_p = p, p = p->next )
		;
	if ( p == NULL ) last_p->next = p = pool_create(last_p->os,2*last_p->bs);
	ret = p->freelist_head;
	p->freelist_head = p->freelist_head->next;
	return ret;
}

@ We need to export the allocation routine.
@<Exported subroutines@>=
void *pool_alloc(pool_t *p);

@ On deallocation of an object, we have the choice of deallocating the
entire block if that block is now empty.  I choose not to do this because
it can lead to thrashing if we're near the border and repeatedly doing 
many allocations followed by many deallocations.
So the amount of memory devoted to any pool is monotonoically non-decreasing.

With this design, we can be {\it superdevious} when it comes to
deallocation.  Whenever an object is deallocated, we put it on the
free list of the {\it first} block, no matter which block it came from.
This actually works, and doesn't muck things up because any object
taken from the free list of any block but the first is never returned to
that free list or any other (except the first block's) free list.
So no object will appear on two different free lists simultaneously.

This scheme is simpler to code, and faster (mostly because of the simplicity.)

This routine requires that the object being freed must have been allocated
from the given pool.  The results are undefined otherwise.
(In particular, this means that we need |vp!=NULL|.)

For performance reasons, we don't check for these conditions.

@<Subroutines@>=
void pool_free(pool_t *p, void *vp) {
	pool_block_freelist_t *flp = vp;
	flp->next = p->freelist_head;
	p->freelist_head = flp;
}

@ We need to export the deallocation routine.
@<Exported subroutines@>=
void pool_free(pool_t *p, void *vp);

@*Index.
