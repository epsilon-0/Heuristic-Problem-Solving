#define max(A,B) ((A) >(B) ?(A) :(B) )  \

/*5:*/
#line 199 "./nn.w"

#include <config.h>
#include "lkconfig.h"
/*6:*/
#line 216 "./nn.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*:6*/
#line 202 "./nn.w"

/*12:*/
#line 263 "./nn.w"

#include "length.h"

/*:12*//*24:*/
#line 392 "./nn.w"

#include "read.h"
#include "lk.h"


/*:24*//*37:*/
#line 531 "./nn.w"

#include "kdtree.h"

/*:37*/
#line 203 "./nn.w"

/*8:*/
#line 231 "./nn.w"

#include "nn.h"

/*:8*//*17:*/
#line 310 "./nn.w"

#include "error.h"
#include "memory.h"

/*:17*//*41:*/
#line 583 "./nn.w"

#include "dsort.h"


/*:41*/
#line 204 "./nn.w"


/*9:*/
#line 235 "./nn.w"

int nn_max_bound;

/*:9*/
#line 206 "./nn.w"

/*11:*/
#line 254 "./nn.w"

typedef struct{
length_t len;
int city;
}nn_entry_t;

/*:11*/
#line 207 "./nn.w"

/*15:*/
#line 297 "./nn.w"

static int*list,*begin,n;

/*:15*//*28:*/
#line 427 "./nn.w"

static int list_size;

/*:28*/
#line 208 "./nn.w"

/*34:*/
#line 481 "./nn.w"

static int
cmp_entry_compress(const void*a,const void*b){
const length_t ad= ((const nn_entry_t*)a)->len;
const length_t bd= ((const nn_entry_t*)b)->len;
if(ad<bd)return-1;
else if(ad>bd)return 1;
else return((const nn_entry_t*)a)->city-((const nn_entry_t*)b)->city;
}

/*:34*/
#line 209 "./nn.w"

/*13:*/
#line 281 "./nn.w"

int*
nn_list(int city,int*list_len)
{
*list_len= begin[city+1]-begin[city];
return list+begin[city];
}


/*:13*//*18:*/
#line 315 "./nn.w"

void
nn_cleanup(void){
/*19:*/
#line 322 "./nn.w"

if(begin){free_mem(begin);mem_deduct(sizeof(int)*(n+1));}

/*:19*//*27:*/
#line 421 "./nn.w"

if(list){free_mem(begin);mem_deduct(sizeof(int)*list_size);}

/*:27*/
#line 318 "./nn.w"

}

/*:18*//*21:*/
#line 347 "./nn.w"

void
nn_build(int num_pure,int num_quadrant,int num_delauney)
{
/*31:*/
#line 443 "./nn.w"

nn_entry_t*work;

/*:31*/
#line 351 "./nn.w"

int i;
n= tsp_instance->n;
/*23:*/
#line 378 "./nn.w"

/*50:*/
#line 685 "./nn.w"

if(verbose>=500){
printf("nn: build nn %d nq %d del %d\n",num_pure,num_quadrant,num_delauney);
fflush(stdout);
}

/*:50*/
#line 379 "./nn.w"

errorif(num_pure<0,
"Need positive number of nearest neighbours; %d specified",num_pure);
errorif(num_quadrant<0,
"Need positive number of quadrant neighbours; %d specified",num_quadrant);
errorif(num_delauney<0,
"Need positive Delauney depth; %d specified",num_delauney);
errorif(num_pure<=0&&num_quadrant<=0&&num_delauney<=0,
"Must specify some candidates");
errorif(num_pure>=n,
"%d nearest neighbours specified, but there are only %d cities",num_pure,n);

/*:23*//*42:*/
#line 593 "./nn.w"

errorif(num_quadrant>0&&!E2_supports(tsp_instance),
"Quadrant lists supported only when 2-d trees supported",num_pure);

/*:42*//*47:*/
#line 669 "./nn.w"

errorif(num_delauney,"Delauney neighbours not supported (yet)");

/*:47*/
#line 354 "./nn.w"


/*16:*/
#line 303 "./nn.w"

begin= new_arr_of(int,n+1);
begin[0]= 0;

/*:16*//*26:*/
#line 413 "./nn.w"

{int guess_avg;
/*25:*/
#line 402 "./nn.w"

if(num_pure)
guess_avg= num_pure+num_quadrant+num_delauney;
else if(num_quadrant)
guess_avg= 4*num_quadrant+num_delauney;
else
guess_avg= 3*num_delauney*num_delauney;

/*:25*/
#line 415 "./nn.w"

list_size= guess_avg*n;
list= new_arr_of(int,list_size);
}

/*:26*//*29:*/
#line 434 "./nn.w"

work= new_arr_of(nn_entry_t,3*n);

/*:29*/
#line 356 "./nn.w"

nn_max_bound= 0;
for(i= 0;i<n;i++){
/*33:*/
#line 471 "./nn.w"

int work_next= 0;


/*:33*/
#line 359 "./nn.w"

/*51:*/
#line 692 "./nn.w"

if(verbose>=1250){
printf("nn: about to build for %d; work_next=%d list_size=%d\n",
i,work_next,list_size);
fflush(stdout);
}

/*:51*/
#line 360 "./nn.w"

/*36:*/
#line 519 "./nn.w"

if(num_pure){
int start_work= work_next;
if(E2_supports(tsp_instance)){
/*38:*/
#line 539 "./nn.w"

{
int j,city;
for(j= 0;j<num_pure;j++){
city= E2_nn(i);
if(city==-1)break;
work[work_next].city= city;
work[work_next].len= cost(i,city);
work_next++;
E2_hide(city);
}
for(j= start_work;j<work_next;j++)E2_unhide(work[j].city);
}

/*:38*/
#line 523 "./nn.w"

}else{
/*39:*/
#line 556 "./nn.w"

{int j;
for(j= 0;j<i;j++){
work[start_work+j].city= j;
work[start_work+j].len= cost(i,j);
}
for(j= i+1;j<n;j++){
work[start_work+j-1].city= j;
work[start_work+j-1].len= cost(i,j);
}
}


/*:39*/
#line 525 "./nn.w"

/*40:*/
#line 577 "./nn.w"

select_range((void*)work,(size_t)n-1,sizeof(nn_entry_t),cmp_entry_compress,
0,num_pure,0);
work_next+= num_pure;

/*:40*/
#line 526 "./nn.w"

}
}

/*:36*/
#line 361 "./nn.w"

/*43:*/
#line 609 "./nn.w"

if(num_quadrant){
int quadrant;
/*45:*/
#line 657 "./nn.w"

{const int num_quadrant= n-1,quadrant= 0;
/*44:*/
#line 637 "./nn.w"

{int j,start_work= work_next;
for(j= 0;j<num_quadrant;j++){
const int city= E2_nn_quadrant(i,1<<quadrant);
if(city==-1)break;
work[work_next].city= city;
work[work_next].len= cost(i,city);
work_next++;
E2_hide(city);
}
for(j= start_work;j<work_next;j++)E2_unhide(work[j].city);
}

/*:44*/
#line 659 "./nn.w"

}


/*:45*/
#line 612 "./nn.w"

for(quadrant= 1;quadrant<=4;quadrant++){
/*44:*/
#line 637 "./nn.w"

{int j,start_work= work_next;
for(j= 0;j<num_quadrant;j++){
const int city= E2_nn_quadrant(i,1<<quadrant);
if(city==-1)break;
work[work_next].city= city;
work[work_next].len= cost(i,city);
work_next++;
E2_hide(city);
}
for(j= start_work;j<work_next;j++)E2_unhide(work[j].city);
}

/*:44*/
#line 614 "./nn.w"

}
}

/*:43*/
#line 362 "./nn.w"

/*48:*/
#line 673 "./nn.w"


/*:48*/
#line 363 "./nn.w"

/*32:*/
#line 456 "./nn.w"

errorif(work_next<1,"Must have nonempty candidate list");
{
int r,w,last_city;
sort(work,(size_t)work_next,sizeof(nn_entry_t),cmp_entry_compress);
for(r= w= 0,last_city= work[r].city-1;r<work_next;r++){
if(work[r].city!=last_city)
last_city= work[w++].city= work[r].city;
}
/*35:*/
#line 500 "./nn.w"

if(begin[i]+w>list_size){
int new_size= list_size;
while(begin[i]+w>new_size)new_size*= 2;
/*49:*/
#line 677 "./nn.w"

if(verbose>=750){
printf("nn: Resize list from %d elements to %d elements; begin[i]=%d, w=%d\n",
list_size,new_size,begin[i],w);
fflush(stdout);
}

/*:49*/
#line 504 "./nn.w"

list= mem_realloc(list,sizeof(int)*new_size);
list_size= new_size;
}

/*:35*/
#line 465 "./nn.w"

for(r= 0;r<w;r++)list[begin[i]+r]= work[r].city;
begin[i+1]= begin[i]+w;
}

/*:32*/
#line 364 "./nn.w"

nn_max_bound= max(nn_max_bound,begin[i+1]-begin[i]);
}
/*30:*/
#line 439 "./nn.w"

free_mem(work);mem_deduct(sizeof(nn_entry_t)*3*n);

/*:30*/
#line 367 "./nn.w"

}

/*:21*/
#line 210 "./nn.w"

const char*nn_rcs_id= "$Id: nn.w,v 1.129 1998/07/16 21:58:55 neto Exp neto $";

/*:5*/
