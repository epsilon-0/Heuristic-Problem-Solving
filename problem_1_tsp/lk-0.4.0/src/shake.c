#define child city \

#define pi (3.1415926535897932384626433832795028841972)  \

/*2:*/
#line 96 "./shake.w"


const char*prog_name= "shake";
const char*shake_rcs_id= "$Id: shake.w,v 1.7 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
#include "lkconfig.h"
/*7:*/
#line 238 "./shake.w"

#define _POSIX_C_SOURCE 2   
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

/*:7*//*32:*/
#line 499 "./shake.w"

#include <math.h>


/*:32*/
#line 102 "./shake.w"

/*5:*/
#line 190 "./shake.w"

#include "prng.h"
#include "error.h"

/*:5*//*8:*/
#line 252 "./shake.w"

#if HAVE_GETOPT
#define FIXINCLUDES_NEED_GETOPT
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_GETOPT
#endif 


/*:8*//*11:*/
#line 278 "./shake.w"

#include "length.h"
#include "read.h"

/*:11*//*15:*/
#line 316 "./shake.w"

#include "dsort.h"

/*:15*//*19:*/
#line 335 "./shake.w"

#include "pool.h"
#include "kdtree.h"
#include "decluster.h"


/*:19*//*25:*/
#line 396 "./shake.w"

#include "memory.h"

/*:25*/
#line 103 "./shake.w"


/*12:*/
#line 289 "./shake.w"

int noround= 1;

/*:12*//*14:*/
#line 311 "./shake.w"

int verbose= 100;
void(*sort)(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));

/*:14*/
#line 105 "./shake.w"

/*4:*/
#line 181 "./shake.w"

static long seed;
static prng_kind_t generator_kind;
static double deviation_factor;
static int num_to_shake;

/*:4*//*10:*/
#line 273 "./shake.w"

static tsp_instance_t*tsp_instance;
static int n;

/*:10*//*17:*/
#line 324 "./shake.w"

static decluster_tree_t*mst= NULL;
static double mst_len;

/*:17*//*21:*/
#line 365 "./shake.w"

decluster_tree_t*T_prime;

/*:21*//*24:*/
#line 392 "./shake.w"

int*size= NULL;

/*:24*//*30:*/
#line 460 "./shake.w"

static int*pending;


/*:30*/
#line 106 "./shake.w"

/*6:*/
#line 198 "./shake.w"

void usage(char**argv);
void
usage(char**argv)
{
printf("%s (LK %s)\n",prog_name,VERSION_STRING);
printf(
"Shake a TSPLIB instance.\n"
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
" -b <num>     : Shake the <num> longest branches in some MST of the instance\n"
"                Default <num> is 20\n"
" -d <f>       : Signed shake angle is normally distributed with mean\n"
"                0 and standard deviation <f>*pi/32\n"
"                Default <f> is 1\n"
" -h           : Output this help and quit\n"
" -R <gen-alg> : Use the named random number genarator.\n"
"                <gen-alg> is one of:");
{int i;for(i= 0;i<PRNG_NUM_KINDS;i++){
printf(" %s",prng_name_from_kind(i));
}
}
printf("\n"
" -s <seed>    : Use integer <seed> as the random number seed\n"
);
}

/*:6*/
#line 107 "./shake.w"



int main(int argc,char**argv)
{
/*16:*/
#line 320 "./shake.w"

sort= dsort;

/*:16*/
#line 112 "./shake.w"

/*3:*/
#line 155 "./shake.w"

seed= 1969L;
generator_kind= PRNG_DEFAULT;
num_to_shake= 20;
deviation_factor= 1.0;
#if HAVE_GETOPT
while(1){
extern char*optarg;
extern int getopt(int,char*const*,const char*);
const int opt= getopt(argc,argv,"s:hR:d:b:");
if(opt==EOF)break;
switch(opt){
case's':seed= atol(optarg);break;
case'h':usage(argv);exit(0);break;
case'R':generator_kind= prng_kind_from_name(optarg);break;
case'b':num_to_shake= atol(optarg);break;
case'd':deviation_factor= atof(optarg);break;
case':':errorif(1,"Some option is missing an argument");break;
case'?':usage(argv);errorif(1,"Unrecognized option");break;
default:errorif(1,"getopt returned character 0%o",opt);
}
}
errorif(num_to_shake<0,"-b requires a non-negative argument, but given %d",num_to_shake);
#endif 

/*:3*/
#line 113 "./shake.w"

/*9:*/
#line 266 "./shake.w"

tsp_instance= read_tsp_file(stdin,NULL);
n= tsp_instance->n;
errorif(num_to_shake>n-1,
"There are only %d nodes, so I can't shake %d branches",n,num_to_shake);

/*:9*/
#line 114 "./shake.w"

/*28:*/
#line 452 "./shake.w"

pending= new_arr_of(int,n);

/*:28*/
#line 115 "./shake.w"

/*13:*/
#line 297 "./shake.w"

E2_create(tsp_instance);
mst= decluster_setup(n);
mst_len= decluster_mst(tsp_instance,mst);
/*35:*/
#line 534 "./shake.w"

#if defined(SHAKE_DEBUG)
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
#endif

/*:35*/
#line 301 "./shake.w"

errorif(n!=1+mst->n,"Wrong number of edges in MST: %d instead of %d",
mst->n,n-1);

/*:13*//*20:*/
#line 357 "./shake.w"

decluster_discard_topology_tree= 0;
decluster_preprocess(mst);
T_prime= decluster_topology_tree();
errorif(T_prime->n!=2*n-1,"Topology tree is the wrong size: %d instead of %d",
T_prime->n,2*n-1);

/*:20*//*22:*/
#line 379 "./shake.w"

{int i,size_T_prime= 2*n-1;
size= new_arr_of(int,size_T_prime);
for(i= 0;i<n;i++)size[i]= 1;
for(i= n;i<size_T_prime;i++)
size[i]= size[T_prime->edge[i].child[0]]+size[T_prime->edge[i].child[1]];
}

/*:22*/
#line 116 "./shake.w"

/*26:*/
#line 407 "./shake.w"

{int i;
const double stddev= deviation_factor*pi/32.0;
const double mean= 0.0;
prng_t*shake_prng= prng_new(generator_kind,seed);
int*fringe= new_arr_of(int,n),fringe_size;

for(i= 0;i<num_to_shake;i++){
const double angle= prng_normal(shake_prng,mean,stddev);
const decluster_edge_t*branch= T_prime->edge+((2*n-1)-1-i);
const int smaller_end= 
(size[branch->child[0]]<size[branch->child[1]])?0:1;
/*36:*/
#line 561 "./shake.w"

#if defined(SHAKE_DEBUG)
printf("mst edge (%f,%f) to (%f,%f) length %f\n",
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[smaller_end]].x[0],
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[smaller_end]].x[1],
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[1-smaller_end]].x[0],
tsp_instance->coord[mst->edge[branch-T_prime->edge-n].city[1-smaller_end]].x[1],
mst->edge[branch-T_prime->edge-n].cost);
#endif

/*:36*/
#line 419 "./shake.w"


/*27:*/
#line 435 "./shake.w"

{
int r,w;
fringe_size= 0;
pending[0]= branch->child[smaller_end];
for(r= 0,w= 1;r<w;r++){
if(pending[r]<n)fringe[fringe_size++]= pending[r];
else{
pending[w++]= T_prime->edge[pending[r]].child[0];
pending[w++]= T_prime->edge[pending[r]].child[1];
}
}
errorif(w>n,"Bug: fringe breadth first search overran array. %d>%d",w,n);
}
errorif(fringe_size>n/2,"Bug: fringe too big.\n");

/*:27*/
#line 421 "./shake.w"

/*31:*/
#line 475 "./shake.w"

/*40:*/
#line 596 "./shake.w"

#if defined(SHAKE_DEBUG)
{int i;
for(i= 0;i<n-1;i++){
errorif(mst->edge[i].cost!=T_prime->edge[i+n].cost,
"Bug: Icky kludgy part at %d\n",i);
}
}
#endif

/*:40*/
#line 476 "./shake.w"

{
int i;
double ct= cos(angle),st= sin(angle);
const int smaller_end_city= 
mst->edge[branch-T_prime->edge-n].city[smaller_end];
const double anchor_x= tsp_instance->coord[smaller_end_city].x[0];
const double anchor_y= tsp_instance->coord[smaller_end_city].x[1];
/*37:*/
#line 572 "./shake.w"

#if defined(SHAKE_DEBUG)
printf(" angle is %f\n",angle);
printf(" anchor at (%f,%f)\n",anchor_x,anchor_y);
#endif

/*:37*/
#line 484 "./shake.w"

for(i= 0;i<fringe_size;i++){
const int city= fringe[i];
const double x= tsp_instance->coord[city].x[0]-anchor_x;
const double y= tsp_instance->coord[city].x[1]-anchor_y;
/*38:*/
#line 579 "./shake.w"

#if defined(SHAKE_DEBUG)
printf("   city at (%f,%f)\n",tsp_instance->coord[city].x[0],
tsp_instance->coord[city].x[1]);
#endif

/*:38*/
#line 489 "./shake.w"

tsp_instance->coord[city].x[0]= x*ct-y*st+anchor_x;
tsp_instance->coord[city].x[1]= x*st+y*ct+anchor_y;
/*39:*/
#line 586 "./shake.w"

#if defined(SHAKE_DEBUG)
printf("   city now at (%f,%f)\n",tsp_instance->coord[city].x[0],
tsp_instance->coord[city].x[1]);
#endif


/*:39*/
#line 492 "./shake.w"

}
}

/*:31*/
#line 422 "./shake.w"

}
free_mem(fringe);mem_deduct(sizeof(int)*n);
prng_free(shake_prng);
}

/*:26*/
#line 117 "./shake.w"

/*33:*/
#line 511 "./shake.w"

{
char*old_comment= tsp_instance->comment;
char*new_comment= new_arr_of(char,200+strlen(old_comment));
sprintf(new_comment,"%s | %s -R %s -s %ld -b %d -d %g",
old_comment,
prog_name,
prng_name_from_kind((int)generator_kind),
seed,
num_to_shake,
deviation_factor);
free_mem(old_comment);
tsp_instance->comment= new_comment;
write_tsp_file(tsp_instance,stdout);
}

/*:33*/
#line 118 "./shake.w"

/*18:*/
#line 329 "./shake.w"

E2_destroy();
decluster_cleanup_tree(mst);
decluster_cleanup();

/*:18*//*23:*/
#line 388 "./shake.w"

free_mem(size);mem_deduct((2*n-1)*sizeof(int));

/*:23*//*29:*/
#line 456 "./shake.w"

free_mem(pending);mem_deduct(n*sizeof(int));

/*:29*/
#line 119 "./shake.w"

return 0;
}

/*:2*/
