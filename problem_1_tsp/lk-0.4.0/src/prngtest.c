/*43:*/
#line 693 "./prng.w"

#include <config.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prng.h"
int main(void);
int main(void)
{
#define DO_UNIFORM
#define MEAN (0.5)
printf(
"  Uniform [0,1) double precision samples\n"
"  eventually should have mean near 0.5, stddev near 0.28\n"
);
/*44:*/
#line 729 "./prng.w"

{int seed,kind;

for(kind= 0;kind<PRNG_NUM_KINDS;kind++){
printf("Generator %s\n",prng_name_from_kind(kind));
if(kind==PRNG_NRAND48&&!(HAVE_NRAND48))continue;
for(seed= 42;seed<150;seed+= 50){
prng_t*g;
printf(" Seed %d\n",seed);
g= prng_new(kind,seed);
/*45:*/
#line 759 "./prng.w"

{
int i;
double sum,sum_sq,mean,stddev;
sum_sq= sum= 0.0;
for(i= 1;i<=10000;i++){
/*46:*/
#line 784 "./prng.w"

#if defined(DO_UNIFORM)
const double sample= prng_unif_double_01(g);
#endif
#if defined(DO_NORMAL)
const double sample= prng_normal(g,MEAN,STDDEV);
#endif


/*:46*/
#line 765 "./prng.w"

sum+= sample;
sum_sq+= sample*sample;
switch(i){
case 1:case 2:case 3:case 4:case 5:
case 10:case 100:case 250:case 500:case 1000:case 10000:
mean= sum/i;
{const double variance= sum_sq/i-mean*mean;
stddev= (variance<0.0)?0.0:sqrt(variance);}
printf("%8d  sample = %9f  mean-%3.1f = %10.6f  stddev = %10.6f\n",
i,sample,MEAN,mean-MEAN,stddev);
break;
default:break;
}
}
}


/*:45*/
#line 739 "./prng.w"

prng_free(g);
}
}
}

/*:44*/
#line 709 "./prng.w"

#undef MEAN
#undef DO_UNIFORM

#define DO_NORMAL
#define MEAN (5.0)
#define STDDEV (2.0)
printf(
"  Normal double precision samples, mean 5, stddev 2\n"
"  eventually should have mean near 5, stddev near 2\n"
);
/*44:*/
#line 729 "./prng.w"

{int seed,kind;

for(kind= 0;kind<PRNG_NUM_KINDS;kind++){
printf("Generator %s\n",prng_name_from_kind(kind));
if(kind==PRNG_NRAND48&&!(HAVE_NRAND48))continue;
for(seed= 42;seed<150;seed+= 50){
prng_t*g;
printf(" Seed %d\n",seed);
g= prng_new(kind,seed);
/*45:*/
#line 759 "./prng.w"

{
int i;
double sum,sum_sq,mean,stddev;
sum_sq= sum= 0.0;
for(i= 1;i<=10000;i++){
/*46:*/
#line 784 "./prng.w"

#if defined(DO_UNIFORM)
const double sample= prng_unif_double_01(g);
#endif
#if defined(DO_NORMAL)
const double sample= prng_normal(g,MEAN,STDDEV);
#endif


/*:46*/
#line 765 "./prng.w"

sum+= sample;
sum_sq+= sample*sample;
switch(i){
case 1:case 2:case 3:case 4:case 5:
case 10:case 100:case 250:case 500:case 1000:case 10000:
mean= sum/i;
{const double variance= sum_sq/i-mean*mean;
stddev= (variance<0.0)?0.0:sqrt(variance);}
printf("%8d  sample = %9f  mean-%3.1f = %10.6f  stddev = %10.6f\n",
i,sample,MEAN,mean-MEAN,stddev);
break;
default:break;
}
}
}


/*:45*/
#line 739 "./prng.w"

prng_free(g);
}
}
}

/*:44*/
#line 720 "./prng.w"

#undef STEDEV
#undef MEAN
#undef DO_NORMAL
return 0;
}


/*:43*/
