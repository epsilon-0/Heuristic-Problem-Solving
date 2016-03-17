#define max_per_city_nn_cache 30
#define max(X,Y) ((X) <(Y) ?(Y) :(X) ) 
#define min(X,Y) ((X) >(Y) ?(Y) :(X) )  \

/*1:*/
#line 174 "./construct.w"

#include <config.h>
#include "lkconfig.h"
/*22:*/
#line 457 "./construct.w"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "fixincludes.h"

/*:22*/
#line 177 "./construct.w"

/*3:*/
#line 198 "./construct.w"

#include "construct.h"

/*:3*//*7:*/
#line 235 "./construct.w"

#include "error.h"

/*:7*//*12:*/
#line 302 "./construct.w"

#include "gb_flip.h"
#include "read.h"


/*:12*//*21:*/
#line 449 "./construct.w"

#include "memory.h"
#include "pq.h"
#include "pool.h"

/*:21*//*25:*/
#line 518 "./construct.w"

#include "lk.h"
#include "kdtree.h"

/*:25*//*35:*/
#line 656 "./construct.w"

#include "dsort.h"


/*:35*/
#line 178 "./construct.w"

/*17:*/
#line 406 "./construct.w"

typedef struct{
length_t len;
int this_end;
int other_end;
}pq_edge_t;

/*:17*//*38:*/
#line 677 "./construct.w"

typedef struct{
int count;
int city[2];
}adj_entry_t;

/*:38*/
#line 179 "./construct.w"

/*23:*/
#line 481 "./construct.w"

static int
cmp_pq_edge(const void*a,const void*b){
length_t len_diff= ((const pq_edge_t*)a)->len-((const pq_edge_t*)b)->len;
return len_diff<0?-1:(len_diff>0?1:
(int)(((const pq_edge_t*)a)-((const pq_edge_t*)b)));
}

/*:23*//*49:*/
#line 834 "./construct.w"

static void nn_link_prn(void*p);
void
nn_link_prn(void*p){
pq_edge_t*np= (pq_edge_t*)p;
printf(" %d,%d ",np->this_end,np->other_end);
}

/*:49*/
#line 180 "./construct.w"

/*4:*/
#line 213 "./construct.w"

length_t
construct(const int n,int*tour,const int heuristic,const long heur_param){
switch(heuristic){
/*8:*/
#line 242 "./construct.w"

case CONSTRUCT_CANONICAL:{
int i;length_t len;
for(i= 0;i<n;i++)tour[i]= i;

len= cost(tour[0],tour[n-1]);
for(i= 1;i<n;i++)len+= cost(tour[i-1],tour[i]);
return len;
break;
}

/*:8*//*10:*/
#line 266 "./construct.w"

case CONSTRUCT_RANDOM:{
int i;length_t len;

for(i= 0;i<n;i++){
tour[i]= i;
}

gb_init_rand(heur_param);
for(i= 0;i<n;i++){
const int next= gb_unif_rand(n-i);
const int t= tour[next];
tour[next]= tour[n-1-i];
tour[n-1-i]= t;
}

len= cost(tour[0],tour[n-1]);
for(i= 1;i<n;i++)len+= cost(tour[i-1],tour[i]);

return len;
break;
}


/*:10*//*15:*/
#line 373 "./construct.w"

case CONSTRUCT_GREEDY:{
length_t len= 0;
const int E2_case= E2_supports(tsp_instance);
#define DO_TOUR
/*18:*/
#line 432 "./construct.w"

pool_t*nn_link_pool= pool_create(sizeof(pq_edge_t),n);
pq_t*pq_edge= pq_create_size(cmp_pq_edge,n);

/*:18*//*26:*/
#line 529 "./construct.w"

int*farthest_in_queue= NULL;

/*:26*//*29:*/
#line 550 "./construct.w"

int*unsaturated= NULL,num_unsaturated= 0,*inv_unsaturated= NULL;

/*:29*//*36:*/
#line 661 "./construct.w"

pq_edge_t*nn_work= NULL;


/*:36*//*39:*/
#line 685 "./construct.w"

#if defined(DO_TOUR)
adj_entry_t*adj= new_arr_of(adj_entry_t,n);
#endif

/*:39*//*42:*/
#line 714 "./construct.w"

#if defined(DO_TOUR)
int*tail= new_arr_of(int,n);
#endif

/*:42*/
#line 378 "./construct.w"

/*19:*/
#line 437 "./construct.w"

errorif(pq_edge==NULL,"Couldn't create the priority queue!");
pq_set_print_func(pq_edge,nn_link_prn);

/*:19*//*24:*/
#line 502 "./construct.w"

if(E2_case){
int i;
for(i= 0;i<n;i++){
pq_edge_t*e= pool_alloc(nn_link_pool);
e->this_end= i;
e->other_end= E2_nn(i);
e->len= cost(i,e->other_end);
pq_insert(pq_edge,e);
/*41:*/
#line 697 "./construct.w"

#if defined(DO_TOUR)
adj[i].count= 0;
#endif

/*:41*//*44:*/
#line 726 "./construct.w"

#if defined(DO_TOUR)
tail[i]= i;
#endif

/*:44*//*55:*/
#line 956 "./construct.w"

#if defined(DO_MATCHING)
mate[i]= -1;
#endif


/*:55*/
#line 511 "./construct.w"

}
}else{
/*27:*/
#line 533 "./construct.w"

farthest_in_queue= new_arr_of(int,n);

/*:27*//*30:*/
#line 554 "./construct.w"

unsaturated= new_arr_of(int,n);
inv_unsaturated= new_arr_of(int,n);
num_unsaturated= n;
{int i;
for(i= 0;i<n;i++)inv_unsaturated[i]= unsaturated[i]= i;
}

/*:30*//*33:*/
#line 586 "./construct.w"

{
int i;
nn_work= new_arr_of(pq_edge_t,n);
for(i= 0;i<n;i++){
const int x= i,not_me= -1;
/*34:*/
#line 624 "./construct.w"

{
int i,num_chosen,farthest_city;
size_t w;
length_t farthest_len;
for(i= w= 0;i<num_unsaturated;i++){
const int c= unsaturated[i];
if(c==x||c==not_me)continue;
nn_work[w].this_end= x;
nn_work[w].other_end= c;
nn_work[w].len= cost(x,c);
w++;
}
num_chosen= min(w,max_per_city_nn_cache);
errorif(num_chosen==0,"Bug!");
(void)select_range(nn_work,w,sizeof(pq_edge_t),cmp_pq_edge,
0,num_chosen,0);
farthest_len= nn_work[i].len;
farthest_city= nn_work[i].other_end;
for(i= 0;i<num_chosen;i++){
pq_edge_t*e= pool_alloc(nn_link_pool);
*e= nn_work[i];
pq_insert(pq_edge,e);
if(farthest_len<e->len){
farthest_city= e->other_end;
farthest_len= e->len;
}
}
farthest_in_queue[x]= farthest_city;
}

/*:34*/
#line 592 "./construct.w"

/*41:*/
#line 697 "./construct.w"

#if defined(DO_TOUR)
adj[i].count= 0;
#endif

/*:41*//*44:*/
#line 726 "./construct.w"

#if defined(DO_TOUR)
tail[i]= i;
#endif

/*:44*//*55:*/
#line 956 "./construct.w"

#if defined(DO_MATCHING)
mate[i]= -1;
#endif


/*:55*/
#line 593 "./construct.w"

}
}

/*:33*/
#line 514 "./construct.w"

}

/*:24*/
#line 379 "./construct.w"

/*45:*/
#line 742 "./construct.w"

{int i,x,y,tx,ty;
errorif(n<3,"Only %d cities.  Can't build a tour.",n);
tx= ty= -1;
for(i= 0;i<n-1;i++){
pq_edge_t*e;
/*46:*/
#line 780 "./construct.w"

while(1){
e= pq_delete_min(pq_edge);
errorif(e==NULL,"Exhausted the priority queue of links.");
x= e->this_end;y= e->other_end;
if(adj[x].count==2){
continue;
}
if(adj[y].count<2&&y!=tail[x])break;
/*47:*/
#line 804 "./construct.w"

if(E2_case){
E2_hide(tail[x]);
e->other_end= E2_nn(x);
e->len= cost(x,e->other_end);
E2_unhide(tail[x]);
pq_insert(pq_edge,e);
}else{
pool_free(nn_link_pool,e);
if(farthest_in_queue[x]==y){
const int not_me= tail[x];
/*34:*/
#line 624 "./construct.w"

{
int i,num_chosen,farthest_city;
size_t w;
length_t farthest_len;
for(i= w= 0;i<num_unsaturated;i++){
const int c= unsaturated[i];
if(c==x||c==not_me)continue;
nn_work[w].this_end= x;
nn_work[w].other_end= c;
nn_work[w].len= cost(x,c);
w++;
}
num_chosen= min(w,max_per_city_nn_cache);
errorif(num_chosen==0,"Bug!");
(void)select_range(nn_work,w,sizeof(pq_edge_t),cmp_pq_edge,
0,num_chosen,0);
farthest_len= nn_work[i].len;
farthest_city= nn_work[i].other_end;
for(i= 0;i<num_chosen;i++){
pq_edge_t*e= pool_alloc(nn_link_pool);
*e= nn_work[i];
pq_insert(pq_edge,e);
if(farthest_len<e->len){
farthest_city= e->other_end;
farthest_len= e->len;
}
}
farthest_in_queue[x]= farthest_city;
}

/*:34*/
#line 815 "./construct.w"

}
}

/*:47*/
#line 789 "./construct.w"

}
len+= e->len;

/*:46*/
#line 748 "./construct.w"

adj[x].city[adj[x].count++]= y;
adj[y].city[adj[y].count++]= x;
if(adj[y].count==2){if(E2_case)E2_hide(y);else{const int c= y;
/*32:*/
#line 576 "./construct.w"

{const int inv= inv_unsaturated[c];
if(inv<num_unsaturated&&unsaturated[inv]==c)
unsaturated[inv]= unsaturated[--num_unsaturated];
}

/*:32*/
#line 752 "./construct.w"
}}
if(adj[x].count==2){if(E2_case)E2_hide(x);else{const int c= x;
/*32:*/
#line 576 "./construct.w"

{const int inv= inv_unsaturated[c];
if(inv<num_unsaturated&&unsaturated[inv]==c)
unsaturated[inv]= unsaturated[--num_unsaturated];
}

/*:32*/
#line 754 "./construct.w"
}}
else{/*47:*/
#line 804 "./construct.w"

if(E2_case){
E2_hide(tail[x]);
e->other_end= E2_nn(x);
e->len= cost(x,e->other_end);
E2_unhide(tail[x]);
pq_insert(pq_edge,e);
}else{
pool_free(nn_link_pool,e);
if(farthest_in_queue[x]==y){
const int not_me= tail[x];
/*34:*/
#line 624 "./construct.w"

{
int i,num_chosen,farthest_city;
size_t w;
length_t farthest_len;
for(i= w= 0;i<num_unsaturated;i++){
const int c= unsaturated[i];
if(c==x||c==not_me)continue;
nn_work[w].this_end= x;
nn_work[w].other_end= c;
nn_work[w].len= cost(x,c);
w++;
}
num_chosen= min(w,max_per_city_nn_cache);
errorif(num_chosen==0,"Bug!");
(void)select_range(nn_work,w,sizeof(pq_edge_t),cmp_pq_edge,
0,num_chosen,0);
farthest_len= nn_work[i].len;
farthest_city= nn_work[i].other_end;
for(i= 0;i<num_chosen;i++){
pq_edge_t*e= pool_alloc(nn_link_pool);
*e= nn_work[i];
pq_insert(pq_edge,e);
if(farthest_len<e->len){
farthest_city= e->other_end;
farthest_len= e->len;
}
}
farthest_in_queue[x]= farthest_city;
}

/*:34*/
#line 815 "./construct.w"

}
}

/*:47*/
#line 755 "./construct.w"
}
tx= tail[x];
ty= tail[y];
tail[tx]= ty;
tail[ty]= tx;
}
adj[tx].city[adj[tx].count++]= ty;
adj[ty].city[adj[ty].count++]= tx;
if(E2_case)E2_unhide_all();
len+= cost(tx,ty);
}

/*:45*//*48:*/
#line 822 "./construct.w"

{int i= 0,prev= -1,here= 0;
do{
tour[i++]= here;
if(adj[here].city[0]!=prev){prev= here;here= adj[here].city[0];}
else{prev= here;here= adj[here].city[1];}
}while(here!=0);
errorif(i!=n,"Not a tour.");
}


/*:48*/
#line 380 "./construct.w"

/*20:*/
#line 442 "./construct.w"

pool_destroy(nn_link_pool);
pq_destroy(pq_edge);

/*:20*//*28:*/
#line 537 "./construct.w"

if(!E2_case){free_mem(farthest_in_queue);mem_deduct(sizeof(int)*n);}


/*:28*//*31:*/
#line 563 "./construct.w"

if(!E2_case){
free_mem(unsaturated);mem_deduct(sizeof(int)*n);
free_mem(inv_unsaturated);mem_deduct(sizeof(int)*n);
}

/*:31*//*37:*/
#line 666 "./construct.w"

if(!E2_case){free_mem(nn_work);mem_deduct(sizeof(pq_edge_t)*n);}


/*:37*//*40:*/
#line 691 "./construct.w"

#if defined(DO_TOUR)
free_mem(adj);
#endif

/*:40*//*43:*/
#line 720 "./construct.w"

#if defined(DO_TOUR)
free_mem(tail);mem_deduct(sizeof(int)*n);
#endif

/*:43*/
#line 381 "./construct.w"

#undef DO_TOUR
return len;
break;
}

/*:15*/
#line 217 "./construct.w"

}
errorif(1,"Unknown heuristic: %d",heuristic);
return(length_t)0;
}

/*:4*//*50:*/
#line 862 "./construct.w"

length_t
construct_matching(int n,int*mate,int alg,long alg_param)
{
int i;
length_t weight= 0;
errorif(n%2,
"Perfect matchings need an even number of vertices; given %d",n);
errorif(mate==NULL,
"Tried to construct a matching before space is allocated");
switch(alg){
/*52:*/
#line 894 "./construct.w"

case CONSTRUCT_CANONICAL:
for(i= 0;i<n;i+= 2){
mate[i]= i+1;
mate[i+1]= i;
weight+= cost(i,i+1);
}
break;

/*:52*//*53:*/
#line 912 "./construct.w"

case CONSTRUCT_RANDOM:
{
int*unmated= new_arr_of(int,n),num_unmated= n,u,v,ui,vi;
for(i= 0;i<n;i++)unmated[i]= i;
gb_init_rand(alg_param);
while(num_unmated>0){
ui= gb_unif_rand(num_unmated);
u= unmated[ui];unmated[ui]= unmated[--num_unmated];
vi= gb_unif_rand(num_unmated);
v= unmated[vi];unmated[vi]= unmated[--num_unmated];
mate[u]= v;
mate[v]= u;
weight+= cost(u,v);
}
free_mem(unmated);mem_deduct(sizeof(int)*n);
}
break;

/*:53*//*54:*/
#line 939 "./construct.w"

case CONSTRUCT_GREEDY:
{
const int E2_case= E2_supports(tsp_instance);
#define DO_MATCHING
/*18:*/
#line 432 "./construct.w"

pool_t*nn_link_pool= pool_create(sizeof(pq_edge_t),n);
pq_t*pq_edge= pq_create_size(cmp_pq_edge,n);

/*:18*//*26:*/
#line 529 "./construct.w"

int*farthest_in_queue= NULL;

/*:26*//*29:*/
#line 550 "./construct.w"

int*unsaturated= NULL,num_unsaturated= 0,*inv_unsaturated= NULL;

/*:29*//*36:*/
#line 661 "./construct.w"

pq_edge_t*nn_work= NULL;


/*:36*//*39:*/
#line 685 "./construct.w"

#if defined(DO_TOUR)
adj_entry_t*adj= new_arr_of(adj_entry_t,n);
#endif

/*:39*//*42:*/
#line 714 "./construct.w"

#if defined(DO_TOUR)
int*tail= new_arr_of(int,n);
#endif

/*:42*/
#line 944 "./construct.w"

/*19:*/
#line 437 "./construct.w"

errorif(pq_edge==NULL,"Couldn't create the priority queue!");
pq_set_print_func(pq_edge,nn_link_prn);

/*:19*//*24:*/
#line 502 "./construct.w"

if(E2_case){
int i;
for(i= 0;i<n;i++){
pq_edge_t*e= pool_alloc(nn_link_pool);
e->this_end= i;
e->other_end= E2_nn(i);
e->len= cost(i,e->other_end);
pq_insert(pq_edge,e);
/*41:*/
#line 697 "./construct.w"

#if defined(DO_TOUR)
adj[i].count= 0;
#endif

/*:41*//*44:*/
#line 726 "./construct.w"

#if defined(DO_TOUR)
tail[i]= i;
#endif

/*:44*//*55:*/
#line 956 "./construct.w"

#if defined(DO_MATCHING)
mate[i]= -1;
#endif


/*:55*/
#line 511 "./construct.w"

}
}else{
/*27:*/
#line 533 "./construct.w"

farthest_in_queue= new_arr_of(int,n);

/*:27*//*30:*/
#line 554 "./construct.w"

unsaturated= new_arr_of(int,n);
inv_unsaturated= new_arr_of(int,n);
num_unsaturated= n;
{int i;
for(i= 0;i<n;i++)inv_unsaturated[i]= unsaturated[i]= i;
}

/*:30*//*33:*/
#line 586 "./construct.w"

{
int i;
nn_work= new_arr_of(pq_edge_t,n);
for(i= 0;i<n;i++){
const int x= i,not_me= -1;
/*34:*/
#line 624 "./construct.w"

{
int i,num_chosen,farthest_city;
size_t w;
length_t farthest_len;
for(i= w= 0;i<num_unsaturated;i++){
const int c= unsaturated[i];
if(c==x||c==not_me)continue;
nn_work[w].this_end= x;
nn_work[w].other_end= c;
nn_work[w].len= cost(x,c);
w++;
}
num_chosen= min(w,max_per_city_nn_cache);
errorif(num_chosen==0,"Bug!");
(void)select_range(nn_work,w,sizeof(pq_edge_t),cmp_pq_edge,
0,num_chosen,0);
farthest_len= nn_work[i].len;
farthest_city= nn_work[i].other_end;
for(i= 0;i<num_chosen;i++){
pq_edge_t*e= pool_alloc(nn_link_pool);
*e= nn_work[i];
pq_insert(pq_edge,e);
if(farthest_len<e->len){
farthest_city= e->other_end;
farthest_len= e->len;
}
}
farthest_in_queue[x]= farthest_city;
}

/*:34*/
#line 592 "./construct.w"

/*41:*/
#line 697 "./construct.w"

#if defined(DO_TOUR)
adj[i].count= 0;
#endif

/*:41*//*44:*/
#line 726 "./construct.w"

#if defined(DO_TOUR)
tail[i]= i;
#endif

/*:44*//*55:*/
#line 956 "./construct.w"

#if defined(DO_MATCHING)
mate[i]= -1;
#endif


/*:55*/
#line 593 "./construct.w"

}
}

/*:33*/
#line 514 "./construct.w"

}

/*:24*/
#line 945 "./construct.w"

/*56:*/
#line 972 "./construct.w"

{
int num_remaining= n/2;
while(num_remaining>0){
int u,v;
pq_edge_t*next_edge= pq_delete_min(pq_edge);
errorif(next_edge==NULL,
"Priority queue exhausted while we expect 2*%d more",num_remaining);
u= next_edge->this_end;
v= next_edge->other_end;
if(mate[u]>=0)continue;
if(mate[v]>=0){/*57:*/
#line 1003 "./construct.w"

if(E2_case){
next_edge->other_end= E2_nn(u);
next_edge->len= cost(u,next_edge->other_end);
pq_insert(pq_edge,next_edge);
}else{
pool_free(nn_link_pool,next_edge);
if(farthest_in_queue[u]==v){
const int x= u,not_me= x;
/*34:*/
#line 624 "./construct.w"

{
int i,num_chosen,farthest_city;
size_t w;
length_t farthest_len;
for(i= w= 0;i<num_unsaturated;i++){
const int c= unsaturated[i];
if(c==x||c==not_me)continue;
nn_work[w].this_end= x;
nn_work[w].other_end= c;
nn_work[w].len= cost(x,c);
w++;
}
num_chosen= min(w,max_per_city_nn_cache);
errorif(num_chosen==0,"Bug!");
(void)select_range(nn_work,w,sizeof(pq_edge_t),cmp_pq_edge,
0,num_chosen,0);
farthest_len= nn_work[i].len;
farthest_city= nn_work[i].other_end;
for(i= 0;i<num_chosen;i++){
pq_edge_t*e= pool_alloc(nn_link_pool);
*e= nn_work[i];
pq_insert(pq_edge,e);
if(farthest_len<e->len){
farthest_city= e->other_end;
farthest_len= e->len;
}
}
farthest_in_queue[x]= farthest_city;
}

/*:34*/
#line 1012 "./construct.w"

}
}

/*:57*/
#line 983 "./construct.w"
continue;}
mate[u]= v;
mate[v]= u;
if(E2_case)E2_hide(u);else{const int c= u;/*32:*/
#line 576 "./construct.w"

{const int inv= inv_unsaturated[c];
if(inv<num_unsaturated&&unsaturated[inv]==c)
unsaturated[inv]= unsaturated[--num_unsaturated];
}

/*:32*/
#line 987 "./construct.w"
}
if(E2_case)E2_hide(v);else{const int c= v;/*32:*/
#line 576 "./construct.w"

{const int inv= inv_unsaturated[c];
if(inv<num_unsaturated&&unsaturated[inv]==c)
unsaturated[inv]= unsaturated[--num_unsaturated];
}

/*:32*/
#line 989 "./construct.w"
}
weight+= cost(u,v);
num_remaining--;
}
}
if(E2_case)E2_unhide_all();

/*:56*/
#line 946 "./construct.w"

/*20:*/
#line 442 "./construct.w"

pool_destroy(nn_link_pool);
pq_destroy(pq_edge);

/*:20*//*28:*/
#line 537 "./construct.w"

if(!E2_case){free_mem(farthest_in_queue);mem_deduct(sizeof(int)*n);}


/*:28*//*31:*/
#line 563 "./construct.w"

if(!E2_case){
free_mem(unsaturated);mem_deduct(sizeof(int)*n);
free_mem(inv_unsaturated);mem_deduct(sizeof(int)*n);
}

/*:31*//*37:*/
#line 666 "./construct.w"

if(!E2_case){free_mem(nn_work);mem_deduct(sizeof(pq_edge_t)*n);}


/*:37*//*40:*/
#line 691 "./construct.w"

#if defined(DO_TOUR)
free_mem(adj);
#endif

/*:40*//*43:*/
#line 720 "./construct.w"

#if defined(DO_TOUR)
free_mem(tail);mem_deduct(sizeof(int)*n);
#endif

/*:43*/
#line 947 "./construct.w"

#undef DO_MATCHING
}
break;

/*:54*/
#line 873 "./construct.w"

default:
errorif(1,"Unrecognized matching construction algorithm %d",alg);
}
return weight;
}

/*:50*/
#line 181 "./construct.w"

const char*construct_rcs_id= "$Id: construct.w,v 1.132 1998/07/16 21:58:55 neto Exp neto $";

/*:1*/
