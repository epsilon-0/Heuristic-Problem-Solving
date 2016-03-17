#define min(X,Y) ((X) <(Y) ?(X) :(Y) ) 
#define max(X,Y) ((X) >(Y) ?(X) :(Y) )  \

/*2:*/
#line 95 "./jitter.w"


const char*prog_name= "jitter";
const char*jitter_rcs_id= "$Id: jitter.w,v 1.8 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
#include "lkconfig.h"
/*6:*/
#line 256 "./jitter.w"

#define _POSIX_C_SOURCE 2   
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

/*:6*/
#line 101 "./jitter.w"

/*4:*/
#line 200 "./jitter.w"

#include "prng.h"
#include "error.h"

/*:4*//*7:*/
#line 270 "./jitter.w"

#if HAVE_GETOPT
#define FIXINCLUDES_NEED_GETOPT
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_GETOPT
#endif 

/*:7*//*12:*/
#line 306 "./jitter.w"

#include "length.h"
#include "read.h"

/*:12*//*16:*/
#line 351 "./jitter.w"

#include "dsort.h"

/*:16*//*20:*/
#line 370 "./jitter.w"

#include "pool.h"
#include "kdtree.h"
#include "length.h"
#include "decluster.h"


/*:20*//*25:*/
#line 448 "./jitter.w"

#include "memory.h"

/*:25*/
#line 102 "./jitter.w"

/*9:*/
#line 286 "./jitter.w"

typedef enum{BENCHMARK_MIN,BENCHMARK_AVG,BENCHMARK_MAX}benchmark_t;
typedef enum{DOMAIN_LOCAL,DOMAIN_GLOBAL}domain_t;

/*:9*//*27:*/
#line 456 "./jitter.w"

typedef struct nbhd_link_s{
int neighbour;
struct nbhd_link_s*next;
}nbhd_link_t;

/*:27*/
#line 103 "./jitter.w"


/*13:*/
#line 313 "./jitter.w"

int noround= 1;

/*:13*//*15:*/
#line 346 "./jitter.w"

int verbose= 100;
void(*sort)(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));

/*:15*/
#line 105 "./jitter.w"

/*8:*/
#line 278 "./jitter.w"

static long seed;
static prng_kind_t generator_kind;
static domain_t domain;
static benchmark_t benchmark_kind;
static double deviation_factor;

/*:8*//*11:*/
#line 301 "./jitter.w"

static tsp_instance_t*tsp_instance;
static int n;

/*:11*//*18:*/
#line 359 "./jitter.w"

static decluster_tree_t*mst= NULL;
static double mst_len;

/*:18*//*22:*/
#line 407 "./jitter.w"

static double global_benchmark_len= -1.0;


/*:22*//*26:*/
#line 452 "./jitter.w"

static nbhd_link_t*nbhd_link,**nbhd= NULL;

/*:26*//*29:*/
#line 497 "./jitter.w"

static double*local_benchmark_len= NULL;

/*:29*//*33:*/
#line 539 "./jitter.w"

static prng_t*jitter_prng;

/*:33*/
#line 106 "./jitter.w"

/*5:*/
#line 208 "./jitter.w"

void usage(char**argv);
void
usage(char**argv)
{
printf("%s (LK %s)\n",prog_name,VERSION_STRING);
printf(
"Add jitter to TSPLIB instances.\n"
"\nCopyright (C) 1997 David M. Neto\n");
printf(
"%s comes with NO WARRANTY, to the extent permitted by law.\n",prog_name);
printf(
"You may redistribute and/or modify copies of %s under the terms of the\n"
"GNU General Public License, version 2 or any later version.\n"
"For more information about these matters, see the file named COPYING.\n",
prog_name);
printf(
"\n"
"Usage: %s [options]\n",argv[0]);
printf(
" -h           : Output this help and quit\n"
" -R <gen-alg> : Use the named random number genarator.\n"
"                <gen-alg> is one of:");
{int i;for(i= 0;i<PRNG_NUM_KINDS;i++){
printf(" %s",prng_name_from_kind(i));
}
}
printf("\n"
" -s <seed>    : Use integer <seed> as the random number seed\n"
" -g           : Make all edges in minimum spanning tree the\n"
"                domain edges for each node\n"
" -l           : Make all edges incident upon node u in a minimum\n"
"                spanning tree for the graph be domain edges for u\n"
"                (not well defined, I know)\n"
"                -l is the default\n"
" -m           : <benchmark-len> is minimum of domain edge lengths\n"
" -a           : <benchmark-len> is average (mean) of domain edge lengths.\n"
"                This is the default.\n"
" -M           : <benchmark-len> is maximum of domain edge lengths\n"
" -d <f>       : Signed jitter distance is normally distributed with mean\n"
"                0 and standard deviation <f>*<benchmark-len>\n"
"                Default <f> is 0.125\n"
);
}

/*:5*/
#line 107 "./jitter.w"



int main(int argc,char**argv)
{
/*17:*/
#line 355 "./jitter.w"

sort= dsort;

/*:17*/
#line 112 "./jitter.w"

/*3:*/
#line 168 "./jitter.w"

seed= 42L;
generator_kind= PRNG_DEFAULT;
domain= DOMAIN_GLOBAL;
benchmark_kind= BENCHMARK_AVG;
deviation_factor= 1.0/8;
#if HAVE_GETOPT
while(1){
extern char*optarg;
extern int getopt(int,char*const*,const char*);
const int opt= getopt(argc,argv,"s:hR:glmaMd:");
if(opt==EOF)break;
switch(opt){
case's':seed= atol(optarg);break;
case'h':usage(argv);exit(0);break;
case'R':generator_kind= prng_kind_from_name(optarg);break;
case'g':domain= DOMAIN_GLOBAL;break;
case'l':domain= DOMAIN_LOCAL;break;
case'm':benchmark_kind= BENCHMARK_MIN;break;
case'a':benchmark_kind= BENCHMARK_AVG;break;
case'M':benchmark_kind= BENCHMARK_MAX;break;
case'd':deviation_factor= atof(optarg);break;
case':':errorif(1,"Some option is missing an argument");break;
case'?':usage(argv);errorif(1,"Unrecognized option");break;
default:errorif(1,"getopt returned character 0%o",opt);
}
}
#endif 

/*:3*/
#line 113 "./jitter.w"

/*10:*/
#line 296 "./jitter.w"

tsp_instance= read_tsp_file(stdin,NULL);
n= tsp_instance->n;

/*:10*/
#line 114 "./jitter.w"

/*14:*/
#line 323 "./jitter.w"

E2_create(tsp_instance);
mst= decluster_setup(n);
mst_len= decluster_mst(tsp_instance,mst);
/*35:*/
#line 574 "./jitter.w"

if(verbose>=1000){
int i;
double sum;
decluster_edge_t*edge= mst->edge;
printf("mst len is %f\n",mst_len);
printf("mst has %d edges\n",mst->n);
for(i= 0,sum= 0.0;i<mst->n;i++){
printf(" cost(%d,%d)=%f\n",i,(i+1)%n,cost(i,(i+1)%n));
printf("   cost(%d,%d)=%f\n",
edge[i].city[0],
edge[i].city[1],
(double)edge[i].cost);
sum+= edge[i].cost;
}
printf("mst computed len is %f\n",mst_len);
}

/*:35*/
#line 327 "./jitter.w"

errorif(n!=1+mst->n,"Wrong number of edges in MST: %d instead of %d",
mst->n,n-1);
switch(domain){
case DOMAIN_GLOBAL:
/*21:*/
#line 383 "./jitter.w"

switch(benchmark_kind){
case BENCHMARK_AVG:global_benchmark_len= mst_len/mst->n;
break;
case BENCHMARK_MIN:
{int i;
global_benchmark_len= mst->edge[0].cost;
for(i= 1;i<mst->n;i++){
global_benchmark_len= min(global_benchmark_len,mst->edge[i].cost);
}
}
break;
case BENCHMARK_MAX:
{int i;
global_benchmark_len= mst->edge[0].cost;
for(i= 1;i<mst->n;i++){
global_benchmark_len= max(global_benchmark_len,mst->edge[i].cost);
}
}
break;
default:errorif(1,"Bug!");
}

/*:21*/
#line 332 "./jitter.w"
break;
case DOMAIN_LOCAL:
/*23:*/
#line 421 "./jitter.w"

{int i,next_nbhd_link;
nbhd= new_arr_of(nbhd_link_t*,n);
nbhd_link= new_arr_of(nbhd_link_t,2*mst->n);
for(i= 0;i<n;i++)nbhd[i]= NULL;
next_nbhd_link= 0;

for(i= 0;i<n;i++){
const int u= mst->edge[i].city[0];
const int v= mst->edge[i].city[1];
nbhd_link[next_nbhd_link].next= nbhd[u];
nbhd_link[next_nbhd_link+1].next= nbhd[v];
nbhd[u]= &nbhd_link[next_nbhd_link];
nbhd[v]= &nbhd_link[next_nbhd_link+1];
next_nbhd_link+= 2;
nbhd[u]->neighbour= v;
nbhd[v]->neighbour= u;
}
errorif(next_nbhd_link!=2*mst->n,"Bug!");
}

/*:23*/
#line 334 "./jitter.w"

/*28:*/
#line 467 "./jitter.w"

local_benchmark_len= new_arr_of(double,n);
{int i;
nbhd_link_t*nb;
switch(benchmark_kind){
case BENCHMARK_AVG:
for(i= 0;i<n;i++){
double sum= 0.0;int count= 0;
for(nb= nbhd[i];nb;nb= nb->next){sum+= cost(i,nb->neighbour);count++;}
local_benchmark_len[i]= sum/count;
}
break;
case BENCHMARK_MIN:
for(i= 0;i<n;i++){
double len= cost(i,nbhd[i]->neighbour);
for(nb= nbhd[i];nb;nb= nb->next){len= min(len,cost(i,nb->neighbour));}
local_benchmark_len[i]= len;
}
break;
case BENCHMARK_MAX:
for(i= 0;i<n;i++){
double len= cost(i,nbhd[i]->neighbour);
for(nb= nbhd[i];nb;nb= nb->next){len= max(len,cost(i,nb->neighbour));}
local_benchmark_len[i]= len;
}
break;
}
}

/*:28*/
#line 335 "./jitter.w"

break;
default:errorif(1,"Bug!");
}

/*:14*/
#line 115 "./jitter.w"

/*31:*/
#line 521 "./jitter.w"

/*32:*/
#line 535 "./jitter.w"

jitter_prng= prng_new(generator_kind,seed);

/*:32*/
#line 522 "./jitter.w"

{int i;
for(i= 0;i<n;i++){
const double len= (domain==DOMAIN_LOCAL?local_benchmark_len[i]:global_benchmark_len);
const double stddev= len*deviation_factor;
const double dx= prng_normal(jitter_prng,0.0,stddev);
const double dy= prng_normal(jitter_prng,0.0,stddev);
tsp_instance->coord[i].x[0]+= dx;
tsp_instance->coord[i].x[1]+= dy;
}
}

/*:31*/
#line 116 "./jitter.w"

/*34:*/
#line 550 "./jitter.w"

{
char*old_comment= tsp_instance->comment;
char*new_comment= new_arr_of(char,200+strlen(old_comment));
sprintf(new_comment,"%s | %s -R %s -s %ld %s %s -d %g",
old_comment,
prog_name,
prng_name_from_kind((int)generator_kind),
seed,
(domain==DOMAIN_LOCAL?"-l":"-g"),
(benchmark_kind==BENCHMARK_MIN?"-m":
(benchmark_kind==BENCHMARK_AVG?"-a":
(benchmark_kind==BENCHMARK_MAX?"-m":
(errorif(1,"Bug!"),"unknown")
)
)
),
deviation_factor);
free_mem(old_comment);
tsp_instance->comment= new_comment;
write_tsp_file(tsp_instance,stdout);
}

/*:34*/
#line 117 "./jitter.w"

/*19:*/
#line 364 "./jitter.w"

E2_destroy();
decluster_cleanup_tree(mst);
decluster_cleanup();

/*:19*//*24:*/
#line 443 "./jitter.w"

free_mem(nbhd);
free_mem(nbhd_link);

/*:24*//*30:*/
#line 501 "./jitter.w"

free_mem(local_benchmark_len);










/*:30*/
#line 118 "./jitter.w"

return 0;
}

/*:2*/
