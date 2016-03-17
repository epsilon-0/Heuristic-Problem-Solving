/*6:*/
#line 95 "gb_flip.w"

#line 24 "gb_flip.ch"
#ifndef gb_next_rand
#define gb_next_rand() (*gb_fptr>=0?*gb_fptr--:gb_flip_cycle())
#endif
#line 97 "gb_flip.w"
 extern long*gb_fptr;
#line 31 "gb_flip.ch"
extern long gb_flip_cycle(void);
#line 99 "gb_flip.w"

/*:6*//*11:*/
#line 222 "gb_flip.w"

#line 49 "gb_flip.ch"
extern void gb_init_rand(long seed);
#line 224 "gb_flip.w"

/*:11*//*13:*/
#line 254 "gb_flip.w"

#line 61 "gb_flip.ch"
extern long gb_unif_rand(long m);

/*:13*//*14:*/
#line 82 "gb_flip.ch"

#define gb_prng_next_rand(PRNG) (*(PRNG)->fptr>=0? *(PRNG)->fptr--: gb_prng_cycle((PRNG)))

typedef struct{
long*fptr;
long A[56];
}gb_prng_t;

gb_prng_t*gb_prng_new(long seed);
long gb_prng_cycle(gb_prng_t*prng);
long gb_prng_unif_rand(gb_prng_t*prng,long m);
void gb_prng_free(gb_prng_t*prng);

/*:14*/
