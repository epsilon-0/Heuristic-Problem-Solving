#define gb_next_rand() (*gb_fptr>=0?*gb_fptr--:gb_flip_cycle() )  \

#define mod_diff(x,y) (((x) -(y) ) &0x7fffffff)  \

#define two_to_the_31 ((unsigned long) 0x80000000)  \

/*3:*/
#line 57 "gb_flip.w"

/*4:*/
#line 75 "gb_flip.w"

static long A[56]= {-1};

/*:4*/
#line 58 "gb_flip.w"

/*5:*/
#line 87 "gb_flip.w"

long*gb_fptr= A;

/*:5*/
#line 59 "gb_flip.w"

/*7:*/
#line 125 "gb_flip.w"

#line 36 "gb_flip.ch"
long gb_flip_cycle(void);
long gb_flip_cycle(void)
#line 127 "gb_flip.w"
{register long*ii,*jj;
for(ii= &A[1],jj= &A[32];jj<=&A[55];ii++,jj++)
*ii= mod_diff(*ii,*jj);
for(jj= &A[1];ii<=&A[55];ii++,jj++)
*ii= mod_diff(*ii,*jj);
gb_fptr= &A[54];
return A[55];
}

/*:7*//*8:*/
#line 150 "gb_flip.w"

#line 43 "gb_flip.ch"
void gb_init_rand(long seed);
void gb_init_rand(long seed)
#line 153 "gb_flip.w"
{register long i;
register long prev= seed,next= 1;
seed= prev= mod_diff(prev,0);
A[55]= prev;
for(i= 21;i;i= (i+21)%55){
A[i]= next;
/*9:*/
#line 178 "gb_flip.w"

next= mod_diff(prev,next);
if(seed&1)seed= 0x40000000+(seed>>1);
else seed>>= 1;
next= mod_diff(next,seed);

/*:9*/
#line 159 "gb_flip.w"
;
prev= A[i];
}
/*10:*/
#line 215 "gb_flip.w"

(void)gb_flip_cycle();
(void)gb_flip_cycle();
(void)gb_flip_cycle();
(void)gb_flip_cycle();
(void)gb_flip_cycle();

/*:10*/
#line 162 "gb_flip.w"
;
}

/*:8*//*12:*/
#line 243 "gb_flip.w"

#line 55 "gb_flip.ch"
long gb_unif_rand(long m);
long gb_unif_rand(long m)
#line 246 "gb_flip.w"
{register unsigned long t= two_to_the_31-(two_to_the_31%m);
register long r;
do{
r= gb_next_rand();
}while(t<=(unsigned long)r);
return r%m;
}

/*:12*//*15:*/
#line 96 "gb_flip.ch"

#include <stdlib.h> 
#include "gb_flip.h"

gb_prng_t*gb_prng_new(long seed);
gb_prng_t*
gb_prng_new(long seed)
{
gb_prng_t*prng= malloc(sizeof(gb_prng_t));
if(prng){
register long i;
register long prev= seed,next= 1;
prng->A[0]= -1;
seed= prev= mod_diff(prev,0);
prng->A[55]= prev;
for(i= 21;i;i= (i+21)%55){
prng->A[i]= next;
/*9:*/
#line 178 "gb_flip.w"

next= mod_diff(prev,next);
if(seed&1)seed= 0x40000000+(seed>>1);
else seed>>= 1;
next= mod_diff(next,seed);

/*:9*/
#line 113 "gb_flip.ch"
;
prev= prng->A[i];
}
gb_prng_cycle(prng);
gb_prng_cycle(prng);
gb_prng_cycle(prng);
gb_prng_cycle(prng);
gb_prng_cycle(prng);
}
return prng;
}


/*:15*//*16:*/
#line 128 "gb_flip.ch"

long gb_prng_cycle(gb_prng_t*prng);
long gb_prng_cycle(gb_prng_t*prng)
{register long*ii,*jj;
for(ii= &prng->A[1],jj= &prng->A[32];jj<=&prng->A[55];ii++,jj++)
*ii= mod_diff(*ii,*jj);
for(jj= &prng->A[1];ii<=&prng->A[55];ii++,jj++)
*ii= mod_diff(*ii,*jj);
prng->fptr= &prng->A[54];
return prng->A[55];
}

/*:16*//*17:*/
#line 141 "gb_flip.ch"

long gb_prng_unif_rand(gb_prng_t*prng,long m);
long gb_prng_unif_rand(gb_prng_t*prng,long m)
{register unsigned long t= two_to_the_31-(two_to_the_31%m);
register long r;
do{
r= gb_prng_next_rand(prng);
}while(t<=(unsigned long)r);
return r%m;
}

/*:17*//*18:*/
#line 153 "gb_flip.ch"

void
gb_prng_free(gb_prng_t*prng)
{
if(prng){free(prng);}
}

/*:18*/
#line 60 "gb_flip.w"


/*:3*/
