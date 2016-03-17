#define norm(x) ((x) <n?(x) :(x) -n)  \

/*3:*/
#line 133 "./array.w"

#include <config.h>
#include "lkconfig.h"
/*4:*/
#line 147 "./array.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

/*:4*/
#line 136 "./array.w"

/*6:*/
#line 162 "./array.w"

#include "array.h"



/*:6*//*11:*/
#line 203 "./array.w"

#include "memory.h"

/*:11*//*22:*/
#line 330 "./array.w"

#include "error.h"

/*:22*/
#line 137 "./array.w"


/*21:*/
#line 324 "./array.w"

#if !defined(ARRAY_DEBUG)
#define ARRAY_DEBUG 0
#endif

/*:21*/
#line 139 "./array.w"

/*7:*/
#line 175 "./array.w"

static int*A= NULL,*B= NULL;

/*:7*//*8:*/
#line 181 "./array.w"

static int n,nm1;

/*:8*/
#line 140 "./array.w"

/*9:*/
#line 187 "./array.w"

void
array_setup(int num_vertices){
/*10:*/
#line 194 "./array.w"

n= num_vertices;
nm1= n-1;
A= new_arr_of(int,n);
B= new_arr_of(int,n);

/*:10*/
#line 190 "./array.w"

}

/*:9*//*12:*/
#line 207 "./array.w"

void
array_cleanup(void){
/*13:*/
#line 214 "./array.w"

free_mem(A);
free_mem(B);

/*:13*/
#line 210 "./array.w"

}

/*:12*//*15:*/
#line 232 "./array.w"

int
array_next(int a){
int ra;
/*28:*/
#line 405 "./array.w"

/*:28*/
#line 236 "./array.w"

ra= B[a];
if(ra==nm1)return A[0];
else return A[ra+1];
}

int
array_prev(int a){
int ra;
/*29:*/
#line 407 "./array.w"

/*:29*/
#line 245 "./array.w"

ra= B[a];
if(ra==0)return A[nm1];
else return A[ra-1];
}

/*:15*//*17:*/
#line 265 "./array.w"

int
array_between(int a,int b,int c){
int ra,rb,rc;
ra= B[a];
rb= B[b];
rc= B[c];
/*30:*/
#line 409 "./array.w"

/*:30*/
#line 272 "./array.w"

if(rb<ra)rb+= n;
if(rc<ra)rc+= n;
return rb<=rc;
}

/*:17*//*19:*/
#line 294 "./array.w"

void
array_flip(int a,int b,int c,int d){
int ra,rb,rc,rd;
/*20:*/
#line 314 "./array.w"

#if ARRAY_DEBUG
errorif(a!=array_next(b),"a != array_next(b)");
errorif(d!=array_next(c),"d != array_next(c)");
#endif 

/*:20*/
#line 298 "./array.w"

/*23:*/
#line 341 "./array.w"

ra= B[a];
rb= B[b];
rc= B[c];
rd= B[d];
if(rc<ra)rc+= n;
if(rb<rd)rb+= n;
if(rc-ra>rb-rd){
int t;
t= a;a= d;d= t;
t= b;b= c;c= t;
t= ra;ra= rd;rd= t;
t= rb;rb= rc;rc= t;
}

/*:23*/
#line 299 "./array.w"

/*31:*/
#line 411 "./array.w"


/*:31*/
#line 300 "./array.w"

/*24:*/
#line 364 "./array.w"

{
int ri,rj,t;
for(ri= ra,rj= rc;ri<rj;ri++,rj--){
B[A[norm(ri)]]= norm(rj);
B[A[norm(rj)]]= norm(ri);
t= A[norm(ri)];A[norm(ri)]= A[norm(rj)];A[norm(rj)]= t;
}
#if ARRAY_DEBUG>1000 
for(i= 0;i<n;i++){
assert(B[A[i]]==i);
assert(A[B[i]]==i);
}
#endif
}

/*:24*/
#line 301 "./array.w"

}


/*:19*//*26:*/
#line 388 "./array.w"

void
array_set(int const*tour){
int i;
for(i= 0;i<n;i++){
A[i]= tour[i];
B[A[i]]= i;
}
}

/*:26*/
#line 141 "./array.w"

const char*array_rcs_id= "$Id: array.w,v 1.112 1998/07/16 21:58:55 neto Exp neto $";

/*:3*/
