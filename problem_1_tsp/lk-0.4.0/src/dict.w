


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
$Log: dict.w,v $
Revision 1.127  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.126  1998/06/12 22:48:21  neto
Fixed a bug.  delete min and delete max weren't returning the right
think.  (That's ok, LK wasn't using that stuff anyway...)

Revision 1.125  1998/05/23 16:36:37  neto
Get rid of unused l in delete min and delete max.
Give a value to variable here so GCC's dataflow analysis is satisfied.

Revision 1.124  1998/05/21 20:28:29  neto
Added dict size, dict delete min, dict delete max.

Revision 1.123  1997/09/27 18:05:36  neto
Fixed RCS log behaviour.

Revision 1.122  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.121  1997/05/16  22:39:33  neto
Fix the pointer print spec.

Revision 1.120  1997/05/16  21:30:19  neto
Fixed a printf spec: from integer to pointer.
(This is in dicttest).

Revision 1.119  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.118  1997/05/16  18:09:40  neto
Include <config.h> and lkconfig.h

Revision 1.117  1997/05/16  16:45:31  neto
Make dicttest's main conform to ANSI standard by making it take
int, char ** arguments.

Revision 1.116  1997/05/16  16:34:16  neto
Removed dumb conditional in dicttest.

Revision 1.115  1997/05/16  16:21:31  neto
Dont discard const.

Revision 1.114  1997/05/16  16:20:20  neto
Add prototypes for functions in dicttest.

Revision 1.113  1997/05/14  20:23:29  neto
dicttest.w doesn't actually use resource measurement. removed.

Revision 1.112  97/01/27  16:35:30  neto
Fixed the function definition for dict\_ create

Revision 1.111  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.110  96/12/17  10:58:36  neto
Fixed some dataflow analysis warnings.

Revision 1.109  96/08/20  11:30:14  neto
Fixed uninitialized variable l.  That was a bug.
Also fixed ggpl.  Not a bug, but a dataflow analysis warning.

Revision 1.108  96/08/16  13:04:40  neto
Added fixincludes.

Revision 1.107  96/08/15  14:14:53  neto
Adde prototype to satisfy all the warning options of GCC.

Revision 1.106  96/08/15  13:14:35  neto
Make it pass -Wall

Revision 1.105  96/08/02  14:20:24  neto
Allow others to get dict without first getting pool.

Revision 1.104  96/08/01  15:50:44  neto
Maked dict\_delete return the item it just deleted.

Revision 1.103  96/07/29  17:09:58  neto
Fixed to compile.

Revision 1.102  96/07/29  16:19:45  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*Dictionaries.
This module is implements the dictionary abstract data type over
any totally ordered domain.

% Format |dict_t| as an int.
@s dict_t int

@ The outline of this module is as follows:
@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Module macros@>@;
@<Subroutines@>@;
const char *dict_rcs_id = "$Id: dict.w,v 1.127 1998/07/16 21:58:55 neto Exp neto $";

@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "fixincludes.h"

@ The exported interface is contained in the \file{dict.h} header file,
which has the following form.

@(dict.h@>=
#if !defined(_DICT_H_)
#define _DICT_H_
@<Headers required for the interface@>@;
extern const char *dict_rcs_id;
@<Exported type definitions@>@;
@<Exported subroutines@>@;
#endif

@ To ensure consistency between the interface and the implementation,
we include our own header.
@<Module headers@>=
#include "dict.h"

@ The interface is as follows:

|dict_t *dict_create(int (*cmp_fnc)(const void *, const void*),void (*prn_fnc)(void *))| 
takes a comparison function
and returns a new dictionary for items that may be compared with that
function.  The comparison function is the same kind as required for
the |qsort| library function.  That is, given pointers to two objects,
it should return an integer that is less than, equal to, or greater than
zero if the first object compares less than, equal to, or greater than
the second object, respectively.
For debugging purposes, we also take a node printing function.


|void dict_destroy(dict_t *d, void (*action)(void *))| 
destroys a previously created dictionary.  If |action != NULL|, then
|action| is called on every item in the dictionary.

|int dict_insert(dict_t *d,void *e)| inserts item |e| into the given dictionary.
This function returns a non-zero value if and only if the item was 
already in the dictionary.  If the item was already present, then a new
copy is {\it not} added.  You can always get around this no-duplicates
limitation
by modifying the comparison function to return the difference of the two
pointers if the pointed-to items would otherwise compare as equal.

|void *dict_find(dict_t *d,void *e)| finds any previously inserted item
which tests as equal to the given item.  If the item is found, it
returns the previously stored pointer (not necessarily the pointer
provided in this call); otherwise, NULL is returned.

|void *dict_delete(dict_t *d, void *e, void (*action)(void *))| 
deletes the item which compares equal
to the given item.  If it isn't present, then nothing happens.
If |action| is non-NULL, then it is called with the item found equal to |e|.
(This is useful for deallocation of space, for example.)
The procedure returns the entry that it deleted, if any.  Note that this
is not necessarily the same pointer value passed to it as |e|, but is
the pointer value that compared as equal to |e|.  If no entry was
deleted, then this procedure returns |NULL|.


|void dict_delete_all(dict_t *, void (*action)(void *))| 
empties the dictionary.  If |action != NULL|, then it is called on every
deleted element.

|void *dict_delete_any(dict_t *)| deletes and 
returns an arbitrary element of the dictionary.
If the dictionary is empty, then it returns |NULL|.

|void *dict_min(dict_t *)| returns the minimum element of the dictionary.
If the dictionary is empty, then it returns |NULL|.

|void *dict_delete_min(dict_t *)| returns the minimum element of the
dictionary,
removing it from the dictionary.
If the dictionary is empty, then it returns |NULL|.

|void *dict_max(dict_t *)| returns the maximum element of the dictionary.
If the dictionary is empty, then it returns |NULL|.

|void *dict_delete_max(dict_t *)| returns the maximum element of the dictionary,
removing it from the dictionary.
If the dictionary is empty, then it returns |NULL|.

|void dict_update_all(dict_t *,void (*proc)(void *env2,void **payload_p),void *env1)|,
for each item in the dictionary, calls |proc| on |env1| and a pointer to 
that item's payload pointer.  This allows update in place of all the
items in the dictionary.   Procedure |proc| must not call any of the other
dicitonary routines on this dictionary.
It also must not change the relative ordering of any of the nodes.
The results are undefined if |proc| breaks either of these rules.

|size_t dict_size(dict_t *)| returns the number of elements in the
dictionary.
This is accounting is ok if the routines aren't used re-entrantly on
the same dictionary.  That is, if the destruction routine for a
dictionary
entry calls a routine modifying the entry, then this count could be wrong.
Heck all hell might break loose.


@<Exported subroutines@>=
dict_t *dict_create(int (*cmp_fnc)(const void *, const void*), 
		void (*prn_fnc)(void *));
void dict_destroy(dict_t *d,void (*action)(void *));
int dict_insert(dict_t *d,void *e);
void *dict_find(dict_t *d,void *e);
void *dict_delete(dict_t *d, void *e, void (*action)(void *));
void dict_delete_all(dict_t *d, void (*action)(void *));
void *dict_delete_any(dict_t *d, void (*action)(void *));
void *dict_min(dict_t *d);
void *dict_max(dict_t *d);
void *dict_delete_min(dict_t *d);
void *dict_delete_max(dict_t *d);
void dict_update_all(dict_t *d,void (*proc)(void *env2,void **payload_p),void *env1);
size_t dict_size(dict_t *d);


@ Up front, we know we'll need interfaces to
the error checking and memory allocation
modules.

@<Module headers@>=
#include "error.h"
#include "memory.h"

@*The dictionary implementation.
I'll use splay trees.  They have linear worst-case storage, and logarithmic
amortized worst-case time per operation.  
Splay trees have the added
feature that
perform very well when there is a lot of locality present in the
sequence of operations.  They adjust well to a shifting distribution of
accesses.

% Format |pool_t| as if it were an |int|.
@s pool_t int

@ Each dictionary consists of just a pointer to the root node, 
a pointer to the comparison function, and an optional pointer to 
a payload printing function.

Each node has pointers to its parent, its left and right children,
and the payload.

Each dictionary allocates from its own pool of memory.  We keep a pointer
to that pool.

@<Exported type definitions@>=

typedef struct dict_node_s {
	void *payload;
	struct dict_node_s *link[3];
} dict_node_t;

typedef struct {
	dict_node_t *root;
	int (*cmp)(const void *a, const void *b);
	void (*prn)(void *a);
	pool_t *pool;
	size_t size;
} dict_t;

@ We need the interface for the pool-oriented allocator.  Since
part of our own interface includes a pool type, we must include the
pool interface within our own interface.

@<Headers required for the interface@>=
#include "pool.h"

@ We've allocated space for three links per node.  It will be convenient
to give them the following standard names.  

I've allocated an an array instead of using the names themselves because
it will compact the code later on.

@<Module macros@>=
#define NILLINK (-2)	/* A nonsense value, for debugging purposes. */
#define SELF (-1)
#define PARENT (0)
#define LEFT (1)
#define RIGHT (2)
#define parent link[PARENT]
#define left link[LEFT]
#define right link[RIGHT]

@ Creating the dictionary just means allocating and initializing a 
|dict_t| structure.

@<Subroutines@>=
dict_t *dict_create(int (*the_cmp)(const void *a, const void *b),void (*the_prn)(void *a)) {
	dict_t *d = new_of(dict_t);
	d->root = NULL;
	errorif(the_cmp == NULL,"Need a non-null comparison function");
	d->cmp = the_cmp;
	d->prn = the_prn;
	d->pool = pool_create(sizeof(dict_node_t),1000);
	d->size = 0;
	return d;
}

@ Destroying the dictionary involves freeing all the nodes int the tree,
and freeing the |dict_t| structure as well.


@<Subroutines@>=
void
dict_destroy(dict_t *d, void (*action)(void *)) {
	if ( d != NULL ) {
		@<Deallocate the subtree rooted at |d->root|, calling |action| on each item@>@;
		d->cmp = NULL;
		d->prn = NULL;
		d->root = NULL;
		pool_destroy(d->pool);
		d->pool = NULL;
		d->size = 0;
		free_mem(d);
	}
}

@ We can traverse the entire tree non-recursively because we have parent
pointers.  This is a darn clever bit of code.  It does a post-order
traversal.

Note that this bit of code requires only constant space.  A recursive
traversal would take linear space in the worst case.  Remember that
splay trees have bad operation sequences which sometimes force them to 
into degenerate trees.

@<Deallocate the subtree rooted at |d->root|, calling |action| on each item@>=
{
dict_node_t *here, *prev;
here = d->root;
prev = NULL;
while ( here != NULL ) {
	if ( here->left != NULL && prev == here->parent ) {
		prev = here;
		here = here->left;
	} else if ( here->right != NULL && prev != here->right ) {
		prev = here;
		here = here->right;
	} else { /* Deallocate the |here| node. */
		if ( action ) action(here->payload);
		prev = here;
		here = here->parent;
		pool_free(d->pool,prev);
	}
}
}


@ We've just coded most of what is needed for |dict_delete_all|.  It does
a subset of |dict_destroy|.

@<Subroutines@>=
void
dict_delete_all(dict_t *d,void (*action)(void *)) {
	@<Deallocate the subtree rooted at |d->root|, calling |action| on each item@>@;
	d->root = NULL;
	d->size = 0;
}

@ We will take some care in coding  the insertion routine so that we can
reuse parts of it later.

To insert a node, we find where it should go, add it there, and then 
splay it to the root.

If there already was an item that compared equal to |e|, then we don't
add anything.

@<Subroutines@>=
int
dict_insert(dict_t *d, void *e) {
	dict_node_t *here, *next;
	int l;	/* The link where |e| goes. */
	int was_absent;

	next = d->root;
	@<Find |e| in the subtree rooted at |next|@>@;
	if ( 0!=(was_absent = (l!=SELF)) )  {
		@<Add |e|, and make |here| to point its node@>@;
		d->size++;
	}
	@<Splay |here| to the root@>@;
	return !was_absent;
}

@ To find a node, we do the usual binary search down from the root.
We do the test for equality last because it is the most likely test
to fail.  Make the common code fast, and make the fast code common.

If |e| exists in the subtree, then this code will make both |next| and |here|
point to its node, and set |l| to |SELF|.  The otherwise case
splits into two cases.  If |e| isn't in the tree because the tree
is empty, then |l| is set to something other than |SELF| and |here| is
set to |NULL|.  If |e| isn't in the tree and the tree is non-empty,
then we make
|next==NULL|, and 
|here->link[l]| is the null pointer that should point to a new node for 
|e|.

@<Find |e| in the subtree rooted at |next|@>=
l=PARENT;	/* Something other than |SELF|. */
for ( here = NULL; next && next != here ; ) {
	int compared_as = d->cmp(e,next->payload);
	here = next;
	if ( compared_as < 0 ) {
		next = here->link[l=LEFT];
	} else if ( compared_as > 0 ) {
		next = here->link[l=RIGHT];
	} else if ( compared_as == 0 ) {
		l = SELF;
		break;
	}
}


@ We need to allocate a node for |e|, and set the pointers properly.

@<Add |e|, and make |here| to point its node@>=
{
	dict_node_t *node = (dict_node_t*)pool_alloc(d->pool);
	node->payload = e;
	node->left = node->right = NULL;
	node->parent = here;
	if ( here == NULL ) d->root = node;
	else here->link[l] = node;
	here = node;
}

@ Splaying a node to the root is the only feature of splay trees over ordinary
binary trees.  It was described and analysed by Sleator and Tarjan (insert
reference!!!).

For now, all you have to know about splaying a node to the root is that it
is a sequence of splay operations.  Each splay operation moves the current
node up two levels (or only one if the current node is at depth 1 in the
tree) while maintaining the left-to right (or in-order traversal order) 
order of the nodes.   


@<Splay |here| to the root@>=
if (here) {
	dict_node_t *p, *gp, *ggp=NULL; /* Parent, grandparent, and great-grandparent */
	int pl, gpl; /* Parent and grandparent links down to |here|. */
	int ggpl=NILLINK;	/* Great grandparent link.   Initialized to nonsense
		value to satisfy GCC's data flow analysis. */
	dict_node_t *subtree[2];	/* Subtrees that are moved */
	do {
		errorif(here==NULL,"|here| must not be NULL");
		@<Name the links, |break| if done@>@;
		@<Splay |here| up once@>@;
	} while (1);
}

@ Here we initialize all the pointers to parents, grandparents,
and determine which pointers came from where.

@<Name the links, |break| if done@>=
gpl = pl = SELF;	/* Something that isn't LEFT or RIGHT */
p = here->parent;
if ( p ) {
	if ( p->left == here ) pl = LEFT;
	else if ( p->right == here ) pl = RIGHT;
	else { dict_doall(d,d->prn); errorif(1,"Bug"); }
	gp = p->parent;
	if ( gp ) {
		if ( gp->left == p ) gpl = LEFT;
		else if ( gp->right == p ) gpl = RIGHT;
		else { dict_doall(d,d->prn); errorif(1,"Bug"); }
		ggp = gp->parent;
		if ( ggp ) {
			if ( ggp->left == gp ) ggpl = LEFT;
			else if ( ggp->right == gp ) ggpl = RIGHT;
			else { dict_doall(d,d->prn); errorif(1,"Bug"); }
		}
	}
} else {
	break;
}


@ There are six cases in splaying a node up: two when |here| is at depth 1
in the tree, and four when |here| is deeper.

The SETLINK macro will be very handy.

@d SETLINK(N,L,C) { (N)->link[L] = (C); if (C) (C)->parent = (N); }

@<Splay |here| up once@>=
if ( gp ) {
	@<Splay |here| up two levels@>@;
} else {
	@<Splay |here| up one level to the root@>@;
}

@ The two level case is the common case.  


The description so far isn't quite enough to derive
all the details of the splay operation.  There are still at least two choices 
in how to rearrange the tree.  The following rewrite rules define
the ``right'' way to do it, \ie, the way that makes the amortized analysis
work out.  (In each case, the capitalized-letter node is the one that
is being splayed.)

\def\becomes{\rightarrow}
$$(((1A2)b3)c4) \becomes (1A(2b(3c4)))$$
$$((1a(2B3))c4) \becomes ((1a2)B(3c4))$$
$$(1a((2B3)c4)) \becomes ((1a2)B(3c4))$$
$$(1a(2b(3C4))) \becomes (((1a2)b3)C4)$$

In coding this transformation, we must be careful in case
the splayed node becomes the new root.

@<Splay |here| up two levels@>=
switch ( gpl ) {
case LEFT:
	switch( pl ) {
	case LEFT:
		subtree[0] = here->right;
		subtree[1] = p->right;
		SETLINK(here,RIGHT,p);
		SETLINK(p,RIGHT,gp);
		SETLINK(p,LEFT,subtree[0]);
		SETLINK(gp,LEFT,subtree[1]);
		break;
	case RIGHT:
		subtree[0] = here->left;
		subtree[1] = here->right;
		SETLINK(here,LEFT,p);
		SETLINK(here,RIGHT,gp);
		SETLINK(p,RIGHT,subtree[0]);
		SETLINK(gp,LEFT,subtree[1]);
		break;
	}
	break;
case RIGHT:
	switch( pl ) {
	case LEFT:
		subtree[0] = here->left;
		subtree[1] = here->right;
		SETLINK(here,LEFT,gp);
		SETLINK(here,RIGHT,p);
		SETLINK(gp,RIGHT,subtree[0]);
		SETLINK(p,LEFT,subtree[1]);
		break;
	case RIGHT:
		subtree[0] = p->left;
		subtree[1] = here->left;
		SETLINK(here,LEFT,p);
		SETLINK(p,LEFT,gp);
		SETLINK(gp,RIGHT,subtree[0]);
		SETLINK(p,RIGHT,subtree[1]);
		break;
	}
	break;
}
if ( ggp ) { 
	if(ggpl != NILLINK){
		SETLINK(ggp,ggpl,here);
	} else {
		errorif(1,"Uninitialized great grandparent link.");
	}
} else { here->parent = NULL; d->root = here; }


@ Splaying up one level is simpler.  It is a simple rotation.

Here are its rewrite rules:
$$((1A2)b3) \becomes (1A(2b3))$$
$$(1a(2B3)) \becomes ((1a2)B3)$$

@<Splay |here| up one level to the root@>=
switch( pl ) {
case LEFT:
	subtree[0] = here->right;
	SETLINK(here,RIGHT,p);
	SETLINK(p,LEFT,subtree[0]);
	break;
case RIGHT:
	subtree[0] = here->left;
	SETLINK(here,LEFT,p);
	SETLINK(p,RIGHT,subtree[0]);
	break;
}
here->parent = NULL;
d->root = here;

@ Procedure |dict_find| is much the same as |dict_insert|, except we
skip the insertion.

@<Subroutines@>=
void *
dict_find(dict_t *d,void *e) {
	dict_node_t *here, *next;
	int l;	/* The link where |e| goes. */
	void *found = NULL;

	next = d->root;
	@<Find |e| in the subtree rooted at |next|@>@;
	if ( next != NULL ) {
		found = next->payload;
	}
	@<Splay |here| to the root@>@;
	return found;
}

@ Now we can get to the deletion routine.

This works much like the |dict_find| routine, except that we remove the
item if it is present.  We must take care to keep the subtrees that were
its children.  

In more detail, there are three cases:

If we delete a leaf, then splay its parent.

If we delete a node with one child, then replace the deleted node by its
child and splay that child.

If we delete a node with two children, then move the smallest node in the right
subtree in place of the deleted node.  Then splay the old parent of that
leaf we promoted.

@<Subroutines@>=
void *
dict_delete(dict_t *d, void *e, void (*action)(void *)) {
	dict_node_t *next, *here, *splay_this; void *deleted_payload=NULL;
	int l;
	next = d->root;
	@<Find |e| in the subtree rooted at |next|@>@;
	if ( next ) deleted_payload = next->payload;
	@<If |next| isn't |NULL|, delete it@>@;
	@<Splay |here| to the root@>@;
	return deleted_payload;
}

@ This is the first level of the nitty gritty of deleting
the node.
@<If |next| isn't |NULL|, delete it@>=
{ 
dict_node_t *e_node, *ep;
int l;
e_node = next;
if ( e_node ) {
	if ( e_node->left == NULL && e_node->right == NULL ) {
		@<Remove the leaf |e_node|@>@;
		splay_this = e_node->parent;
	} else if ( e_node->left == NULL ) {
		@<Promote |e_node->right|@>@;
		splay_this = e_node->right;
	} else if ( e_node->right == NULL ) {
		@<Promote |e_node->left|@>@;
		splay_this = e_node->left;
	} else {
		@<Replace |e_node| by a merge of its two children@>@;
	}
	if ( action ) action(e_node->payload);
	pool_free(d->pool,e_node);
	d->size--;
	here = splay_this;
}
}

@ This is simple surgery.  It is tricky only because |e_node| may be the root.
@<Remove the leaf |e_node|@>=
@<Name the parent and its link@>@;
if ( ep ) { ep->link[l]=NULL; }
else { d->root = NULL; }



@ Here we do a shallower version of what was needed in the splaying routine.

After this section is executed, 
the value of |l| is used only if |ep!=NULL|, \ie, |e_node| is the root node.
Unfortunately, GCC's dataflow analysis isn't smart enough to detect this.
So we eliminate the dataflow analysis warning by assigning a garbage
value |NILLINK| to |l| right away.

@<Name the parent and its link@>=
ep = e_node->parent;
l=NILLINK; /* Satisfy GCC's dataflow analysis. */
if ( ep ) {
	if ( ep->left == e_node ) l = LEFT;
	else if ( ep->right == e_node ) l = RIGHT;
	else { errorif(1,"Bug"); }
}

@ Promoting |e_node|'s right child is only tricky because we need to take
care of the case when |e_node| is the root.

@<Promote |e_node->right|@>=
@<Name the parent and its link@>@;
if ( ep ) { SETLINK(ep,l,e_node->right); }
else { e_node->right->parent = NULL; d->root = e_node->right; }

@ Promoting |e_node|'s left child is symmetrical to the right case.
@<Promote |e_node->left|@>=
@<Name the parent and its link@>@;
if ( ep ) { SETLINK(ep,l,e_node->left); }
else { e_node->left->parent = NULL; d->root = e_node->left; }

@ The tough case is when |e_node| has two children.  

Move the smallest node in the right
subtree in place of the deleted node.  Then splay the old parent of that
leaf we promoted.

The difficulty with this is that the leftmost node in the right
subtree might itself have a right child (but it certainly won't have
a left child).  So we may need to promote that right child of that leftmost
node in that right subtree.


@<Replace |e_node| by a merge of its two children@>=
{	dict_node_t *erL, *save_e_node = e_node;

	for ( erL = e_node->right; erL->left ; erL = erL->left )
		;
	if ( erL->right ) {
		splay_this = erL->right;
	} else {
		if ( erL->parent != e_node ) splay_this = erL->parent;
		else splay_this = erL;
	}
	e_node = erL;
	@<Promote |e_node->right|@>@;
	e_node = save_e_node;

	/* Now put |erL| in place of |e_node| */
	SETLINK(erL,LEFT,e_node->left);
	if ( e_node->right != erL ) { SETLINK(erL,RIGHT,e_node->right);	}
/* |e_node->right| may have changed with the promotion!  
But it's ok because |e_node| is a pointer. */
	@<Name the parent and its link@>@;
	if ( ep ) { SETLINK(ep,l,erL); }
	else { erL->parent = NULL; d->root = erL; }
}

@ The |dict_delete_any| routine 
just deletes and returns the root node.  This is easy.

@<Subroutines@>=
void *
dict_delete_any(dict_t *d, void (*action)(void *)) {
	if ( d->root ) { 
		dict_node_t *next, *here=NULL, *splay_this;
		void *ret;
		next = d->root;
		ret = next->payload;
		@<If |next| isn't |NULL|, delete it@>@;
		@<Splay |here| to the root@>@;
		return ret;
	} else return NULL;
}

@ The |dict_min| routine is almost as easy.

@<Subroutines@>=
void *
dict_min(dict_t *d) {
	dict_node_t *here;
	if ( d->root ) {
		for ( here=d->root ; here->left ; here = here->left )
			;
		@<Splay |here| to the root@>@;
		return here->payload;
	} else return NULL;
}

@ The |dict_max| routine is much the same.

@<Subroutines@>=
void *
dict_max(dict_t *d) 
{
	dict_node_t *here;
	if ( d->root ) {
		for ( here=d->root ; here->right ; here = here->right )
			;
		@<Splay |here| to the root@>@;
		return here->payload;
	} else return NULL;
}

@ The |dict_delete_min| and |dict_delete_max| routines are combinations
of what we've already seen.

@<Subroutines@>=

void *
dict_delete_min(dict_t *d) 
{
	if ( d->root ) {
		dict_node_t *m, *next, *here=NULL, *splay_this; 
		void (*action)(void*)=NULL, *payload;
		for ( m=d->root ; m->left ; m = m->left )
			;
		next=m;
		payload = m->payload;
		@<If |next| isn't |NULL|, delete it@>@;
		@<Splay |here| to the root@>@;
		return payload;
	} else return NULL;
}

void *
dict_delete_max(dict_t *d) 
{
	if ( d->root ) {
		dict_node_t *m, *next, *here=NULL, *splay_this;
		void (*action)(void*)=NULL, *payload;
		for ( m=d->root ; m->right ; m = m->right )
			;
		next=m;
		payload = m->payload;
		@<If |next| isn't |NULL|, delete it@>@;
		@<Splay |here| to the root@>@;
		return payload;
	} else return NULL;
}

@ The update procedure does a post-order traversal of the tree, calling
|proc| at each node.  (Hint: most of this code is stolen from the
|dict_delete_all| routine.)

@<Subroutines@>=
void 
dict_update_all(dict_t *d,void (*proc)(void *env2,void **payload_p),void *env1)
{
dict_node_t *here, *prev;
here = d->root;
prev = NULL;
while ( here != NULL ) {
	if ( here->left != NULL && prev == here->parent ) {
		prev = here;
		here = here->left;
	} else if ( here->right != NULL && prev != here->right ) {
		prev = here;
		here = here->right;
	} else { /* Visit the |here| node . */
		proc(env1,&(here->payload));
		prev = here;
		here = here->parent;
	}
}
}

@ As for returning the number of elements in the dictionary, the
|dict_insert|, |dict_delete|, |dict_destroy|, |dict_create|, and
|dict_delete_all| routines do all the hard work.
@<Subroutines@>=
size_t 
dict_size(dict_t *d)
{
	return d->size; 
}

@* Debugging routines.
@<Subroutines@>=

void visit(dict_node_t *n,void (*action)(void *));
void visit(dict_node_t *n,void (*action)(void *)) {
	if (n) {
		printf("(");
		visit(n->left,action);
		errorif( n->left != NULL && n->left->parent != n,"Bug");
		if (action) action(n->payload);
		visit(n->right,action);
		errorif( n->right != NULL && n->right->parent != n,"Bug");
		printf(")");
	}
}

void
dict_doall(dict_t *d, void (*action)(void *)) {
	visit(d->root,action);
	errorif( d->root != NULL && d->root->parent != NULL,"Bug");
}

void
dict_show_node(dict_t *d,dict_node_t *h) {
	printf("%lx",(unsigned long)h);
	if ( h ) {
		printf("={\"");
		d->prn(h->payload);
		printf("\" p=%lx l=%lx r=%lx}",
			(unsigned long)h->parent, 
			(unsigned long)h->left, 
			(unsigned long)h->right);
	}
}

@
@<Exported subroutines@>=
void
dict_doall(dict_t *d, void (*action)(void *));   /* Unsupported! */
void
dict_show_node(dict_t *d,dict_node_t *h);		/* Unsupported! */

@ The following program tests this module, though certainly not exhaustively.
@(dicttest.c@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "error.h"
#include "memory.h"
#include "pool.h"
#include "dict.h"
#include "gb_flip.h"

#define N 5

static int intcmp(const void *a, const void *b);
static void prn(void *a);
static void del(void *a);
int main(int, char **);

static int
intcmp(const void *a, const void *b) 
{
	return (*(const int *)a)-(*(const int *)b);
}

void prn(void *a) 
{
	printf("%d",*(int *)a);
}
static void 
del(void *a) 
{
	printf("freeing integer %d\n",*(int *)a);
}

int 
main(int argc, char **argv) 
{
	int i;
	int a[N];
	dict_t *d;
	d = dict_create(intcmp,prn);
	printf("Empty is:\n"); dict_doall(d,prn); printf("\n");

	for ( i=0; i<N; i++ ) {
		a[i] = i;
		dict_insert(d,a+i);
		printf("Inserted %d:",i);
		dict_doall(d,prn);
		printf("\n-------\n");
	}
	printf("All built");
	dict_doall(d,prn);
	printf("\n-------\n");

	i = 7;
	dict_find(d,&i);
	printf("After find %d: ",i);dict_doall(d,prn);printf("\n------\n");

	for ( i=N-1;i>-1;i--) {
		int *r = dict_find(d,&i);
		printf("i==%d a+i == %x r == %x\n",i,(int)(a+i), (int)r);
		printf("  ");dict_doall(d,prn);printf("\n------\n");
	}

	i = 2;
	dict_find(d,&i);
	printf("After find %d: ",i);dict_doall(d,prn);printf("\n------\n");

	i = N*2;
	printf("About to dict_find(%d)\n",i);
	errorif( dict_find(d,&i) != NULL, "Should have returned NULL" );
	dict_doall(d,prn);
	printf("\n------\n");

	i = -N*2;
	printf("About to dict_find(%d)\n",i);
	errorif( dict_find(d,&i) != NULL, "Should have returned NULL" );
	dict_doall(d,prn);
	printf("\n------\n");

/* Randomized testing */
	gb_init_rand(42L);
	for ( i=0;i<N*N;i++) {
		int j, *r;
		j = gb_unif_rand((long)N*2)-N/2;
		r = dict_find(d,&j);
		if ( 0 <= j && j < N ) {
			if ( a+j != r ) {
printf("%d j==%d a+j == %x r == %x\n",i,j,(int)(a+j), (int)r);
printf("  ");dict_doall(d,prn);printf("\n------\n");
				errorif(1,"BUG");
			}
		} else {
			if ( r != NULL) {
				printf("r == %p != NULL when it should be.\n", (void *)r);
printf("%d j==%d a+j == %x r == %x\n",i,j,(int)(a+j), (int)r);
printf("  ");dict_doall(d,prn);printf("\n------\n");
			}
		}
	}

/* Bare long left */
	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=1;dict_find(d,&i);
	i=2;dict_find(d,&i);
	printf("Bare long left bottom:");dict_doall(d,prn);printf("\n");
	i=0; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=1;dict_find(d,&i);
	i=2;dict_find(d,&i);
	printf("Bare long left middle:");dict_doall(d,prn);printf("\n");
	i=1; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=1;dict_find(d,&i);
	i=2;dict_find(d,&i);
	printf("Bare long left top:");dict_doall(d,prn);printf("\n");
	i=2; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

/* Bare long right */
	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=2;dict_find(d,&i);
	i=1;dict_find(d,&i);
	i=0;dict_find(d,&i);
	printf("Bare long right bottom:");dict_doall(d,prn);printf("\n");
	i=2; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=2;dict_find(d,&i);
	i=1;dict_find(d,&i);
	i=0;dict_find(d,&i);
	printf("Bare long right middle:");dict_doall(d,prn);printf("\n");
	i=1; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=2;dict_find(d,&i);
	i=1;dict_find(d,&i);
	i=0;dict_find(d,&i);
	printf("Bare long right top:");dict_doall(d,prn);printf("\n");
	i=0; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

/* Bare balanced */
	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=1;dict_find(d,&i);
	printf("Bare balanced left:");dict_doall(d,prn);printf("\n");
	i=0; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=1;dict_find(d,&i);
	printf("Bare balanced middle:");dict_doall(d,prn);printf("\n");
	i=1; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");

	dict_delete_all(d,NULL);
	for (i=0;i<3;i++) dict_insert(d,a+i);
	i=1;dict_find(d,&i);
	printf("Bare balanced right:");dict_doall(d,prn);printf("\n");
	i=2; dict_delete(d,&i,del);
	printf("Deleted %d:",i); dict_doall(d,prn); printf("\n------\n");


/* Now test the two-child delete where the right child must itself be 
replaced */
	for ( i=4;i>=0;i-- ) {
		dict_insert(d,a+i);
	}
	dict_find(d,a+3);
	dict_find(d,a+1);
	printf("Complex two-child delete:");dict_doall(d,prn);printf("\n");
	dict_delete(d,a+1,del);
	printf("Deleted %d:",1);dict_doall(d,prn);printf("\n------\n");

	dict_destroy(d,del);
	printf("\n------\nPassed all tests! (NOT EXHAUSTIVE)\n");
	return 0;
}

@*Index.
