#define SETLINK(N,L,C) {(N) ->link[L]= (C) ;if(C) (C) ->parent= (N) ;} \

/*2:*/
#line 148 "./dict.w"

#include <config.h>
#include "lkconfig.h"
/*3:*/
#line 161 "./dict.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "fixincludes.h"

/*:3*/
#line 151 "./dict.w"

/*5:*/
#line 182 "./dict.w"

#include "dict.h"

/*:5*//*7:*/
#line 287 "./dict.w"

#include "error.h"
#include "memory.h"

/*:7*/
#line 152 "./dict.w"


/*11:*/
#line 341 "./dict.w"

#define NILLINK (-2) 
#define SELF (-1)
#define PARENT (0)
#define LEFT (1)
#define RIGHT (2)
#define parent link[PARENT]
#define left link[LEFT]
#define right link[RIGHT]

/*:11*/
#line 154 "./dict.w"

/*12:*/
#line 354 "./dict.w"

dict_t*dict_create(int(*the_cmp)(const void*a,const void*b),void(*the_prn)(void*a)){
dict_t*d= new_of(dict_t);
d->root= NULL;
errorif(the_cmp==NULL,"Need a non-null comparison function");
d->cmp= the_cmp;
d->prn= the_prn;
d->pool= pool_create(sizeof(dict_node_t),1000);
d->size= 0;
return d;
}

/*:12*//*13:*/
#line 370 "./dict.w"

void
dict_destroy(dict_t*d,void(*action)(void*)){
if(d!=NULL){
/*14:*/
#line 394 "./dict.w"

{
dict_node_t*here,*prev;
here= d->root;
prev= NULL;
while(here!=NULL){
if(here->left!=NULL&&prev==here->parent){
prev= here;
here= here->left;
}else if(here->right!=NULL&&prev!=here->right){
prev= here;
here= here->right;
}else{
if(action)action(here->payload);
prev= here;
here= here->parent;
pool_free(d->pool,prev);
}
}
}


/*:14*/
#line 374 "./dict.w"

d->cmp= NULL;
d->prn= NULL;
d->root= NULL;
pool_destroy(d->pool);
d->pool= NULL;
d->size= 0;
free_mem(d);
}
}

/*:13*//*15:*/
#line 419 "./dict.w"

void
dict_delete_all(dict_t*d,void(*action)(void*)){
/*14:*/
#line 394 "./dict.w"

{
dict_node_t*here,*prev;
here= d->root;
prev= NULL;
while(here!=NULL){
if(here->left!=NULL&&prev==here->parent){
prev= here;
here= here->left;
}else if(here->right!=NULL&&prev!=here->right){
prev= here;
here= here->right;
}else{
if(action)action(here->payload);
prev= here;
here= here->parent;
pool_free(d->pool,prev);
}
}
}


/*:14*/
#line 422 "./dict.w"

d->root= NULL;
d->size= 0;
}

/*:15*//*16:*/
#line 436 "./dict.w"

int
dict_insert(dict_t*d,void*e){
dict_node_t*here,*next;
int l;
int was_absent;

next= d->root;
/*17:*/
#line 467 "./dict.w"

l= PARENT;
for(here= NULL;next&&next!=here;){
int compared_as= d->cmp(e,next->payload);
here= next;
if(compared_as<0){
next= here->link[l= LEFT];
}else if(compared_as>0){
next= here->link[l= RIGHT];
}else if(compared_as==0){
l= SELF;
break;
}
}


/*:17*/
#line 444 "./dict.w"

if(0!=(was_absent= (l!=SELF))){
/*18:*/
#line 485 "./dict.w"

{
dict_node_t*node= (dict_node_t*)pool_alloc(d->pool);
node->payload= e;
node->left= node->right= NULL;
node->parent= here;
if(here==NULL)d->root= node;
else here->link[l]= node;
here= node;
}

/*:18*/
#line 446 "./dict.w"

d->size++;
}
/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 449 "./dict.w"

return!was_absent;
}

/*:16*//*24:*/
#line 658 "./dict.w"

void*
dict_find(dict_t*d,void*e){
dict_node_t*here,*next;
int l;
void*found= NULL;

next= d->root;
/*17:*/
#line 467 "./dict.w"

l= PARENT;
for(here= NULL;next&&next!=here;){
int compared_as= d->cmp(e,next->payload);
here= next;
if(compared_as<0){
next= here->link[l= LEFT];
}else if(compared_as>0){
next= here->link[l= RIGHT];
}else if(compared_as==0){
l= SELF;
break;
}
}


/*:17*/
#line 666 "./dict.w"

if(next!=NULL){
found= next->payload;
}
/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 670 "./dict.w"

return found;
}

/*:24*//*25:*/
#line 691 "./dict.w"

void*
dict_delete(dict_t*d,void*e,void(*action)(void*)){
dict_node_t*next,*here,*splay_this;void*deleted_payload= NULL;
int l;
next= d->root;
/*17:*/
#line 467 "./dict.w"

l= PARENT;
for(here= NULL;next&&next!=here;){
int compared_as= d->cmp(e,next->payload);
here= next;
if(compared_as<0){
next= here->link[l= LEFT];
}else if(compared_as>0){
next= here->link[l= RIGHT];
}else if(compared_as==0){
l= SELF;
break;
}
}


/*:17*/
#line 697 "./dict.w"

if(next)deleted_payload= next->payload;
/*26:*/
#line 706 "./dict.w"

{
dict_node_t*e_node,*ep;
int l;
e_node= next;
if(e_node){
if(e_node->left==NULL&&e_node->right==NULL){
/*27:*/
#line 732 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 733 "./dict.w"

if(ep){ep->link[l]= NULL;}
else{d->root= NULL;}



/*:27*/
#line 713 "./dict.w"

splay_this= e_node->parent;
}else if(e_node->left==NULL){
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 716 "./dict.w"

splay_this= e_node->right;
}else if(e_node->right==NULL){
/*30:*/
#line 765 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 766 "./dict.w"

if(ep){SETLINK(ep,l,e_node->left);}
else{e_node->left->parent= NULL;d->root= e_node->left;}

/*:30*/
#line 719 "./dict.w"

splay_this= e_node->left;
}else{
/*31:*/
#line 782 "./dict.w"

{dict_node_t*erL,*save_e_node= e_node;

for(erL= e_node->right;erL->left;erL= erL->left)
;
if(erL->right){
splay_this= erL->right;
}else{
if(erL->parent!=e_node)splay_this= erL->parent;
else splay_this= erL;
}
e_node= erL;
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 794 "./dict.w"

e_node= save_e_node;


SETLINK(erL,LEFT,e_node->left);
if(e_node->right!=erL){SETLINK(erL,RIGHT,e_node->right);}


/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 802 "./dict.w"

if(ep){SETLINK(ep,l,erL);}
else{erL->parent= NULL;d->root= erL;}
}

/*:31*/
#line 722 "./dict.w"

}
if(action)action(e_node->payload);
pool_free(d->pool,e_node);
d->size--;
here= splay_this;
}
}

/*:26*/
#line 699 "./dict.w"

/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 700 "./dict.w"

return deleted_payload;
}

/*:25*//*32:*/
#line 810 "./dict.w"

void*
dict_delete_any(dict_t*d,void(*action)(void*)){
if(d->root){
dict_node_t*next,*here= NULL,*splay_this;
void*ret;
next= d->root;
ret= next->payload;
/*26:*/
#line 706 "./dict.w"

{
dict_node_t*e_node,*ep;
int l;
e_node= next;
if(e_node){
if(e_node->left==NULL&&e_node->right==NULL){
/*27:*/
#line 732 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 733 "./dict.w"

if(ep){ep->link[l]= NULL;}
else{d->root= NULL;}



/*:27*/
#line 713 "./dict.w"

splay_this= e_node->parent;
}else if(e_node->left==NULL){
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 716 "./dict.w"

splay_this= e_node->right;
}else if(e_node->right==NULL){
/*30:*/
#line 765 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 766 "./dict.w"

if(ep){SETLINK(ep,l,e_node->left);}
else{e_node->left->parent= NULL;d->root= e_node->left;}

/*:30*/
#line 719 "./dict.w"

splay_this= e_node->left;
}else{
/*31:*/
#line 782 "./dict.w"

{dict_node_t*erL,*save_e_node= e_node;

for(erL= e_node->right;erL->left;erL= erL->left)
;
if(erL->right){
splay_this= erL->right;
}else{
if(erL->parent!=e_node)splay_this= erL->parent;
else splay_this= erL;
}
e_node= erL;
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 794 "./dict.w"

e_node= save_e_node;


SETLINK(erL,LEFT,e_node->left);
if(e_node->right!=erL){SETLINK(erL,RIGHT,e_node->right);}


/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 802 "./dict.w"

if(ep){SETLINK(ep,l,erL);}
else{erL->parent= NULL;d->root= erL;}
}

/*:31*/
#line 722 "./dict.w"

}
if(action)action(e_node->payload);
pool_free(d->pool,e_node);
d->size--;
here= splay_this;
}
}

/*:26*/
#line 818 "./dict.w"

/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 819 "./dict.w"

return ret;
}else return NULL;
}

/*:32*//*33:*/
#line 826 "./dict.w"

void*
dict_min(dict_t*d){
dict_node_t*here;
if(d->root){
for(here= d->root;here->left;here= here->left)
;
/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 833 "./dict.w"

return here->payload;
}else return NULL;
}

/*:33*//*34:*/
#line 840 "./dict.w"

void*
dict_max(dict_t*d)
{
dict_node_t*here;
if(d->root){
for(here= d->root;here->right;here= here->right)
;
/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 848 "./dict.w"

return here->payload;
}else return NULL;
}

/*:34*//*35:*/
#line 856 "./dict.w"


void*
dict_delete_min(dict_t*d)
{
if(d->root){
dict_node_t*m,*next,*here= NULL,*splay_this;
void(*action)(void*)= NULL,*payload;
for(m= d->root;m->left;m= m->left)
;
next= m;
payload= m->payload;
/*26:*/
#line 706 "./dict.w"

{
dict_node_t*e_node,*ep;
int l;
e_node= next;
if(e_node){
if(e_node->left==NULL&&e_node->right==NULL){
/*27:*/
#line 732 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 733 "./dict.w"

if(ep){ep->link[l]= NULL;}
else{d->root= NULL;}



/*:27*/
#line 713 "./dict.w"

splay_this= e_node->parent;
}else if(e_node->left==NULL){
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 716 "./dict.w"

splay_this= e_node->right;
}else if(e_node->right==NULL){
/*30:*/
#line 765 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 766 "./dict.w"

if(ep){SETLINK(ep,l,e_node->left);}
else{e_node->left->parent= NULL;d->root= e_node->left;}

/*:30*/
#line 719 "./dict.w"

splay_this= e_node->left;
}else{
/*31:*/
#line 782 "./dict.w"

{dict_node_t*erL,*save_e_node= e_node;

for(erL= e_node->right;erL->left;erL= erL->left)
;
if(erL->right){
splay_this= erL->right;
}else{
if(erL->parent!=e_node)splay_this= erL->parent;
else splay_this= erL;
}
e_node= erL;
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 794 "./dict.w"

e_node= save_e_node;


SETLINK(erL,LEFT,e_node->left);
if(e_node->right!=erL){SETLINK(erL,RIGHT,e_node->right);}


/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 802 "./dict.w"

if(ep){SETLINK(ep,l,erL);}
else{erL->parent= NULL;d->root= erL;}
}

/*:31*/
#line 722 "./dict.w"

}
if(action)action(e_node->payload);
pool_free(d->pool,e_node);
d->size--;
here= splay_this;
}
}

/*:26*/
#line 868 "./dict.w"

/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 869 "./dict.w"

return payload;
}else return NULL;
}

void*
dict_delete_max(dict_t*d)
{
if(d->root){
dict_node_t*m,*next,*here= NULL,*splay_this;
void(*action)(void*)= NULL,*payload;
for(m= d->root;m->right;m= m->right)
;
next= m;
payload= m->payload;
/*26:*/
#line 706 "./dict.w"

{
dict_node_t*e_node,*ep;
int l;
e_node= next;
if(e_node){
if(e_node->left==NULL&&e_node->right==NULL){
/*27:*/
#line 732 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 733 "./dict.w"

if(ep){ep->link[l]= NULL;}
else{d->root= NULL;}



/*:27*/
#line 713 "./dict.w"

splay_this= e_node->parent;
}else if(e_node->left==NULL){
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 716 "./dict.w"

splay_this= e_node->right;
}else if(e_node->right==NULL){
/*30:*/
#line 765 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 766 "./dict.w"

if(ep){SETLINK(ep,l,e_node->left);}
else{e_node->left->parent= NULL;d->root= e_node->left;}

/*:30*/
#line 719 "./dict.w"

splay_this= e_node->left;
}else{
/*31:*/
#line 782 "./dict.w"

{dict_node_t*erL,*save_e_node= e_node;

for(erL= e_node->right;erL->left;erL= erL->left)
;
if(erL->right){
splay_this= erL->right;
}else{
if(erL->parent!=e_node)splay_this= erL->parent;
else splay_this= erL;
}
e_node= erL;
/*29:*/
#line 759 "./dict.w"

/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 760 "./dict.w"

if(ep){SETLINK(ep,l,e_node->right);}
else{e_node->right->parent= NULL;d->root= e_node->right;}

/*:29*/
#line 794 "./dict.w"

e_node= save_e_node;


SETLINK(erL,LEFT,e_node->left);
if(e_node->right!=erL){SETLINK(erL,RIGHT,e_node->right);}


/*28:*/
#line 747 "./dict.w"

ep= e_node->parent;
l= NILLINK;
if(ep){
if(ep->left==e_node)l= LEFT;
else if(ep->right==e_node)l= RIGHT;
else{errorif(1,"Bug");}
}

/*:28*/
#line 802 "./dict.w"

if(ep){SETLINK(ep,l,erL);}
else{erL->parent= NULL;d->root= erL;}
}

/*:31*/
#line 722 "./dict.w"

}
if(action)action(e_node->payload);
pool_free(d->pool,e_node);
d->size--;
here= splay_this;
}
}

/*:26*/
#line 884 "./dict.w"

/*19:*/
#line 507 "./dict.w"

if(here){
dict_node_t*p,*gp,*ggp= NULL;
int pl,gpl;
int ggpl= NILLINK;

dict_node_t*subtree[2];
do{
errorif(here==NULL,"|here| must not be NULL");
/*20:*/
#line 524 "./dict.w"

gpl= pl= SELF;
p= here->parent;
if(p){
if(p->left==here)pl= LEFT;
else if(p->right==here)pl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
gp= p->parent;
if(gp){
if(gp->left==p)gpl= LEFT;
else if(gp->right==p)gpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
ggp= gp->parent;
if(ggp){
if(ggp->left==gp)ggpl= LEFT;
else if(ggp->right==gp)ggpl= RIGHT;
else{dict_doall(d,d->prn);errorif(1,"Bug");}
}
}
}else{
break;
}


/*:20*/
#line 516 "./dict.w"

/*21:*/
#line 555 "./dict.w"

if(gp){
/*22:*/
#line 581 "./dict.w"

switch(gpl){
case LEFT:
switch(pl){
case LEFT:
subtree[0]= here->right;
subtree[1]= p->right;
SETLINK(here,RIGHT,p);
SETLINK(p,RIGHT,gp);
SETLINK(p,LEFT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,p);
SETLINK(here,RIGHT,gp);
SETLINK(p,RIGHT,subtree[0]);
SETLINK(gp,LEFT,subtree[1]);
break;
}
break;
case RIGHT:
switch(pl){
case LEFT:
subtree[0]= here->left;
subtree[1]= here->right;
SETLINK(here,LEFT,gp);
SETLINK(here,RIGHT,p);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,LEFT,subtree[1]);
break;
case RIGHT:
subtree[0]= p->left;
subtree[1]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,LEFT,gp);
SETLINK(gp,RIGHT,subtree[0]);
SETLINK(p,RIGHT,subtree[1]);
break;
}
break;
}
if(ggp){
if(ggpl!=NILLINK){
SETLINK(ggp,ggpl,here);
}else{
errorif(1,"Uninitialized great grandparent link.");
}
}else{here->parent= NULL;d->root= here;}


/*:22*/
#line 557 "./dict.w"

}else{
/*23:*/
#line 639 "./dict.w"

switch(pl){
case LEFT:
subtree[0]= here->right;
SETLINK(here,RIGHT,p);
SETLINK(p,LEFT,subtree[0]);
break;
case RIGHT:
subtree[0]= here->left;
SETLINK(here,LEFT,p);
SETLINK(p,RIGHT,subtree[0]);
break;
}
here->parent= NULL;
d->root= here;

/*:23*/
#line 559 "./dict.w"

}

/*:21*/
#line 517 "./dict.w"

}while(1);
}

/*:19*/
#line 885 "./dict.w"

return payload;
}else return NULL;
}

/*:35*//*36:*/
#line 894 "./dict.w"

void
dict_update_all(dict_t*d,void(*proc)(void*env2,void**payload_p),void*env1)
{
dict_node_t*here,*prev;
here= d->root;
prev= NULL;
while(here!=NULL){
if(here->left!=NULL&&prev==here->parent){
prev= here;
here= here->left;
}else if(here->right!=NULL&&prev!=here->right){
prev= here;
here= here->right;
}else{
proc(env1,&(here->payload));
prev= here;
here= here->parent;
}
}
}

/*:36*//*37:*/
#line 919 "./dict.w"

size_t
dict_size(dict_t*d)
{
return d->size;
}

/*:37*//*38:*/
#line 927 "./dict.w"


void visit(dict_node_t*n,void(*action)(void*));
void visit(dict_node_t*n,void(*action)(void*)){
if(n){
printf("(");
visit(n->left,action);
errorif(n->left!=NULL&&n->left->parent!=n,"Bug");
if(action)action(n->payload);
visit(n->right,action);
errorif(n->right!=NULL&&n->right->parent!=n,"Bug");
printf(")");
}
}

void
dict_doall(dict_t*d,void(*action)(void*)){
visit(d->root,action);
errorif(d->root!=NULL&&d->root->parent!=NULL,"Bug");
}

void
dict_show_node(dict_t*d,dict_node_t*h){
printf("%lx",(unsigned long)h);
if(h){
printf("={\"");
d->prn(h->payload);
printf("\" p=%lx l=%lx r=%lx}",
(unsigned long)h->parent,
(unsigned long)h->left,
(unsigned long)h->right);
}
}

/*:38*/
#line 155 "./dict.w"

const char*dict_rcs_id= "$Id: dict.w,v 1.127 1998/07/16 21:58:55 neto Exp neto $";

/*:2*/
