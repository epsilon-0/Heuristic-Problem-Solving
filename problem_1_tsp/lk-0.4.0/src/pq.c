#define SWAP(x,y) {void*t= x;x= y;y= t;} \

/*2:*/
#line 86 "./pq.w"


#include <stdlib.h>
#include <stddef.h>
#include "pq.h"
#include "error.h"

/*6:*/
#line 126 "./pq.w"

pq_t*
pq_create(pq_cmp_func_t cmp)
{
return pq_create_size(cmp,1023);
}

pq_t*
pq_create_size(pq_cmp_func_t cmp,int n)
{
pq_t*pq= malloc(sizeof(pq_t));
if(pq){
pq->cmp= cmp;
pq->last_elem_i= 0;
pq->A_size= 1+((n<63)?63:n);
pq->A= malloc(sizeof(void*)*pq->A_size);
errorif(pq->A==NULL,"Couldn't allocate a heap array of %d bytes",sizeof(void*)*pq->A_size);
}
return pq;
}

/*:6*//*7:*/
#line 148 "./pq.w"

void
pq_make_empty(pq_t*pq)
{
pq->last_elem_i= 0;
}

/*:7*//*8:*/
#line 156 "./pq.w"

void
pq_destroy(pq_t*pq)
{
if(pq){
if(pq->A){free(pq->A);pq->A= NULL;}
pq->last_elem_i= 0;
pq->A_size= 0;
free(pq);
}
}

/*:8*//*9:*/
#line 169 "./pq.w"

int
pq_empty(pq_t*pq)
{
return pq->last_elem_i==0;
}

/*:9*//*10:*/
#line 183 "./pq.w"

void
pq_insert(pq_t*pq,void*payload)
{
pq_cmp_func_t cmp= pq->cmp;
int i= pq->last_elem_i+1;
void**A;
if(i>=pq->A_size){
pq->A_size*= 2;
pq->A= realloc(pq->A,sizeof(void*)*pq->A_size);
errorif(pq->A==NULL,"pq_insert: realloc failed: couldn't grow array");
}
A= pq->A;
A[i]= payload;
while(i>1&&cmp(A[i/2],A[i])>0){
SWAP(A[i],A[i/2]);
i/= 2;
}
pq->last_elem_i++;
/*11:*/
#line 206 "./pq.w"

#if PQ_DEBUGGING_CHARS
{int i;
for(i= 1;i<=pq->last_elem_i;i++){
putchar(*(char*)pq->A[i]);
}
putchar('\n');
}
#endif

/*:11*/
#line 202 "./pq.w"

}

/*:10*//*12:*/
#line 217 "./pq.w"

void*
pq_min(pq_t*pq)
{
return pq->last_elem_i?pq->A[1]:NULL;
}

/*:12*//*13:*/
#line 225 "./pq.w"

void*
pq_delete_min(pq_t*pq)
{
if(pq->last_elem_i){
void**A= pq->A;
void*the_min= A[1];
A[1]= A[pq->last_elem_i--];
/*14:*/
#line 243 "./pq.w"

{
const int last_elem_i= pq->last_elem_i;
pq_cmp_func_t cmp= pq->cmp;
int i,next_i;
for(i= 1,next_i= 0;i;i= next_i,next_i= 0){
const int child1= i*2,child2= child1+1;
if(child2<=last_elem_i){
const int least_child= cmp(A[child1],A[child2])<0?child1:child2;
if(cmp(A[i],A[least_child])>0){
SWAP(A[i],A[least_child]);
next_i= least_child;
}
}else if(child1<=last_elem_i&&cmp(A[i],A[child1])>0){
SWAP(A[i],A[child1]);
next_i= child1;
}
}
}

/*:14*/
#line 233 "./pq.w"

/*11:*/
#line 206 "./pq.w"

#if PQ_DEBUGGING_CHARS
{int i;
for(i= 1;i<=pq->last_elem_i;i++){
putchar(*(char*)pq->A[i]);
}
putchar('\n');
}
#endif

/*:11*/
#line 234 "./pq.w"

return the_min;
}else{return NULL;}
}


/*:13*//*15:*/
#line 266 "./pq.w"

void
pq_set_print_func(pq_t*pq,void(*print_func)(void*))
{
pq->print_func= print_func;
}

/*:15*/
#line 93 "./pq.w"


/*:2*/
