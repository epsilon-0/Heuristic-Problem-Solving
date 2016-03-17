/*8:*/
#line 202 "./prng.w"

#if !defined(_PRNG_H_)
#define _PRNG_H_
/*14:*/
#line 310 "./prng.w"

#include "error.h"

/*:14*//*28:*/
#line 529 "./prng.w"

#include "gb_flip.h"

/*:28*//*38:*/
#line 637 "./prng.w"

#if HAVE_NRAND48
#include <stdlib.h>
#define FIXINCLUDES_NEED_NRAND48
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_NRAND48
#endif

/*:38*/
#line 205 "./prng.w"

/*11:*/
#line 244 "./prng.w"

typedef enum{/*27:*/
#line 523 "./prng.w"

PRNG_GB_FLIP,

/*:27*//*33:*/
#line 575 "./prng.w"

PRNG_NRAND48,

/*:33*//*42:*/
#line 686 "./prng.w"

PRNG_NUM_KINDS,
PRNG_DEFAULT= PRNG_GB_FLIP

/*:42*/
#line 245 "./prng.w"
}prng_kind_t;
typedef struct{
prng_kind_t kind;
int seed;
/*20:*/
#line 413 "./prng.w"

int have_saved_normal;
double saved_normal;

/*:20*/
#line 249 "./prng.w"

union{
/*29:*/
#line 533 "./prng.w"

gb_prng_t*gb_flipper;

/*:29*//*34:*/
#line 580 "./prng.w"

#if SIZEOF_SHORT==2
unsigned short nrand48_state[3];
#else
#error "short int is not 16 bits"
#endif

/*:34*/
#line 251 "./prng.w"

}gen;
}prng_t;

/*:11*/
#line 206 "./prng.w"

/*9:*/
#line 227 "./prng.w"

prng_t*prng_new(prng_kind_t kind,int seed);
double prng_normal(prng_t*g,double mean,double stddev);
void prng_free(prng_t*g);
int prng_kind_from_name(char*name);
const char*prng_name_from_kind(int kind);
int prng_kind(prng_t*g);

/*:9*/
#line 207 "./prng.w"


#include "prngconfig.h"
#if PRNG_DESIRE_INLINING && COMPILER_SUPPORTS_INLINE
#define inline_proto inline extern
#define inline_def inline extern
#include <math.h> 
/*10:*/
#line 236 "./prng.w"

inline_proto int prng_unif_int(prng_t*g,long m);
inline_proto double prng_unif_double_01(prng_t*g);
inline_proto double prng_unif_double_range(prng_t*g,double a,double b);

/*:10*/
#line 214 "./prng.w"

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
#line 215 "./prng.w"

#undef inline_proto
#undef inline_def
#else
#define inline_proto
/*10:*/
#line 236 "./prng.w"

inline_proto int prng_unif_int(prng_t*g,long m);
inline_proto double prng_unif_double_01(prng_t*g);
inline_proto double prng_unif_double_range(prng_t*g,double a,double b);

/*:10*/
#line 220 "./prng.w"

#undef inline_proto
#endif

#endif 

/*:8*/
