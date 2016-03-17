/*6:*/
#line 184 "./prng.w"


const char*prng_rcs_id= "$Id: prng.w,v 1.10 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
/*16:*/
#line 319 "./prng.w"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*:16*//*18:*/
#line 364 "./prng.w"

#include <float.h>
#include <math.h>



/*:18*//*25:*/
#line 504 "./prng.w"

#include <errno.h>




/*:25*/
#line 188 "./prng.w"

/*15:*/
#line 314 "./prng.w"

#include "memory.h"

/*:15*/
#line 189 "./prng.w"

#include "prng.h"

#define inline_def  
/*13:*/
#line 297 "./prng.w"

inline_def int
prng_unif_int(prng_t*g,long m)
{
switch(g->kind){
/*32:*/
#line 551 "./prng.w"

case PRNG_GB_FLIP:
return gb_prng_unif_rand(g->gen.gb_flipper,m);


/*:32*//*37:*/
#line 619 "./prng.w"

case PRNG_NRAND48:
#if HAVE_NRAND48
{unsigned long t= 0x80000000UL-(0x80000000UL%m);
long r;
do{
r= nrand48(g->gen.nrand48_state);
}while(t<=(unsigned long)r);
return r%m;
}
#else
errorif(1,"Sorry, nrand48 is not available on this system.");
return 0;
#endif
break;

/*:37*/
#line 302 "./prng.w"

default:errorif(1,"No such kind of random number generator: %d",g->kind);
return 0;
}
}

/*:13*//*17:*/
#line 343 "./prng.w"

inline_def double
prng_unif_double_01(prng_t*g)
{
#if FLT_RADIX==2
double i= prng_unif_int(g,1<<30);
double j= prng_unif_int(g,1<<(DBL_MANT_DIG-30));
return ldexp(ldexp(i,-30)+j,-(DBL_MANT_DIG-30));
#else 
double x= 0.0,full= 0.0;
while(full<1.0){
x= ldexp(x+prng_unif_int(g,2),-1);
full= ldexp(1.0+full,-1);
}
return x;
#endif
}

/*:17*//*19:*/
#line 390 "./prng.w"

inline_def double
prng_unif_double_range(prng_t*g,double a,double b)
{
const double t= prng_unif_double_01(g);
return a+t*(b-a);
}


/*:19*/
#line 193 "./prng.w"

#undef inline_def
/*12:*/
#line 262 "./prng.w"

prng_t*
prng_new(prng_kind_t kind,int seed)
{
prng_t*g= new_of(prng_t);
errorif(g==NULL,"Couldn't allocate a new generic random number generator");
g->kind= kind;
switch(kind){
/*30:*/
#line 537 "./prng.w"

case PRNG_GB_FLIP:
g->gen.gb_flipper= gb_prng_new(seed);
errorif(g->gen.gb_flipper==NULL,"Couldn't allocate a new GB_FLIP generator");
break;


/*:30*//*35:*/
#line 592 "./prng.w"

case PRNG_NRAND48:
#if HAVE_NRAND48
g->gen.nrand48_state[0]= 0x330E;
g->gen.nrand48_state[1]= seed&0xffff;
g->gen.nrand48_state[2]= (seed>>16)&0xffff;
#else
errorif(1,"Sorry, nrand48 is not available on this system.");
#endif
break;


/*:35*/
#line 270 "./prng.w"

default:errorif(1,"No such kind of random number generator: %d",kind);
}
/*21:*/
#line 418 "./prng.w"

g->have_saved_normal= 0;

/*:21*/
#line 273 "./prng.w"

return g;
}

void
prng_free(prng_t*g)
{
if(g){
switch(g->kind){
/*31:*/
#line 545 "./prng.w"

case PRNG_GB_FLIP:
gb_prng_free(g->gen.gb_flipper);
break;

/*:31*//*36:*/
#line 605 "./prng.w"

case PRNG_NRAND48:
break;

/*:36*/
#line 282 "./prng.w"

default:break;
}
}
}

/*:12*//*22:*/
#line 424 "./prng.w"

double
prng_normal(prng_t*g,double mean,double stddev)
{
if(g->have_saved_normal){
g->have_saved_normal= 0;
return mean+stddev*g->saved_normal;
}else{
double v_1,v_2,s,n_1,n_2;
do{
v_1= prng_unif_double_01(g);
v_2= prng_unif_double_01(g);
/*23:*/
#line 460 "./prng.w"

v_1= 2*v_1-1;if(v_1>=0)v_1= 1-v_1;
v_2= 2*v_2-1;if(v_2>=0)v_2= 1-v_2;

/*:23*/
#line 436 "./prng.w"

s= v_1*v_1+v_2*v_2;
}while(s>=1);
/*24:*/
#line 483 "./prng.w"

{double Rprime;
errno= 0;
Rprime= sqrt(-2*log(s)/s);
switch(errno){
case ERANGE:
case EDOM:
n_1= v_1<0?-DBL_MAX:DBL_MAX;
n_2= v_2<0?-DBL_MAX:DBL_MAX;
break;
default:
n_1= v_1*Rprime;
n_2= v_2*Rprime;
}
errno= 0;
}


/*:24*/
#line 439 "./prng.w"

g->saved_normal= n_2;
g->have_saved_normal= 1;
return mean+n_1*stddev;
}
}

/*:22*//*40:*/
#line 659 "./prng.w"

int
prng_kind_from_name(char*name){
int i;
/*39:*/
#line 650 "./prng.w"

const static char*prng_name_map[PRNG_NUM_KINDS]= {
"gb_flip",
"nrand48"
};

/*:39*/
#line 663 "./prng.w"

for(i= 0;i<PRNG_NUM_KINDS;i++){
if(0==strcmp(name,prng_name_map[i]))return i;
}
return PRNG_DEFAULT;
}

const char*
prng_name_from_kind(int kind){
/*39:*/
#line 650 "./prng.w"

const static char*prng_name_map[PRNG_NUM_KINDS]= {
"gb_flip",
"nrand48"
};

/*:39*/
#line 672 "./prng.w"

errorif(kind<0||kind>=PRNG_NUM_KINDS,
"No such kind of pseudo-random number generator: %d",kind);
return prng_name_map[kind];
}

/*:40*//*41:*/
#line 679 "./prng.w"

int
prng_kind(prng_t*g){
return g->kind;
}

/*:41*/
#line 195 "./prng.w"


/*:6*/
