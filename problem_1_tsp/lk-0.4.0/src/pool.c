#define MINIMUM_GRANULARITY 8 \

#define byte char
/*3:*/
#line 129 "./pool.w"

#include <config.h>
#include "lkconfig.h"
/*4:*/
#line 141 "./pool.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*:4*/
#line 132 "./pool.w"

/*6:*/
#line 159 "./pool.w"

#include "pool.h"


/*:6*//*9:*/
#line 210 "./pool.w"

#include "error.h"
#include "memory.h"

/*:9*/
#line 133 "./pool.w"


/*8:*/
#line 191 "./pool.w"

pool_t*
pool_create(size_t os,int bs){
pool_t*p;

if(os%MINIMUM_GRANULARITY)os+= MINIMUM_GRANULARITY-(os%MINIMUM_GRANULARITY);
errorif(bs<1,"Need a positive block size");
p= new_of(pool_t);
p->next= NULL;
p->os= os;
p->bs= bs;
p->block= mem_alloc(os*bs);
/*11:*/
#line 245 "./pool.w"

{
int i;
pool_block_freelist_t*fl,*next;

for(fl= p->freelist_head= (pool_block_freelist_t*)p->block,i= 0;
i<bs-1;
i++){
next= (pool_block_freelist_t*)(((long*)fl)+os/sizeof(long));
fl->next= next;
fl= next;
}
fl->next= NULL;
}



/*:11*/
#line 203 "./pool.w"

return p;
}

/*:8*//*12:*/
#line 265 "./pool.w"

void pool_destroy(pool_t*p){
while(p){
pool_t*next= p->next;
free_mem(p->block);
free_mem(p);
p= next;
}
}

/*:12*//*14:*/
#line 291 "./pool.w"

void*
pool_alloc(pool_t*p){
pool_t*last_p;
void*ret;
for(last_p= p;p&&p->freelist_head==NULL;last_p= p,p= p->next)
;
if(p==NULL)last_p->next= p= pool_create(last_p->os,2*last_p->bs);
ret= p->freelist_head;
p->freelist_head= p->freelist_head->next;
return ret;
}

/*:14*//*16:*/
#line 330 "./pool.w"

void pool_free(pool_t*p,void*vp){
pool_block_freelist_t*flp= vp;
flp->next= p->freelist_head;
p->freelist_head= flp;
}

/*:16*/
#line 135 "./pool.w"

const char*pool_rcs_id= "$Id: pool.w,v 1.110 1998/07/16 21:58:55 neto Exp neto $";

/*:3*/
