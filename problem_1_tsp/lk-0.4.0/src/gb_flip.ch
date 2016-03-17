@x
int main()
@y
int main(int argc, char **argv);
int main(int argc, char **argv)
@z
@x
  if (gb_unif_rand(0x55555555L)!=748103812) {
     fprintf(stderr,"Failure on the second try!\n"); return -2;
  }
  fprintf(stderr,"OK, the gb_flip routines seem to work!\n");
  return 0;
@y
  if (gb_unif_rand(0x55555555L)!=748103812) {
     fprintf(stderr,"Failure on the second try!\n"); return -2;
  }
  @<Test the object-oriented generators@>@;
  fprintf(stderr,"OK, the gb_flip routines seem to work!\n");
  return 0;
@z
@x
#define gb_next_rand() @t\quad@>(*gb_fptr>=0?*gb_fptr--:gb_flip_cycle())
@y
#ifndef gb_next_rand
#define gb_next_rand() @t\quad@>(*gb_fptr>=0?*gb_fptr--:gb_flip_cycle())
#endif
@z
@x
extern long gb_flip_cycle(); /* compute 55 more pseudo-random numbers */
@y
extern long gb_flip_cycle(void); /* compute 55 more pseudo-random numbers */
@z
@x
long gb_flip_cycle()
@y
long gb_flip_cycle(void);
long gb_flip_cycle(void)
@z
@x
void gb_init_rand(seed)
    long seed;
@y
void gb_init_rand(long seed);
void gb_init_rand(long seed)
@z
@x
extern void gb_init_rand();
@y
extern void gb_init_rand(long seed);
@z
@x
long gb_unif_rand(m)
    long m;
@y
long gb_unif_rand(long m);
long gb_unif_rand(long m)
@z
@x
extern long gb_unif_rand();
@y
extern long gb_unif_rand(long m);

@*Multiple independent streams.
({\sl David Neto here.})
Sometimes it is convenient to have multiple random number sequences alive
at once, especially when trying to tame a particularly obstreperous 
set of experiments.  Each generator is a separate object.

I've just copied the code from above.  Alas, this not the easiest
to maintain, but it works.  
In any case, Knuth's code will never change, right?  
Right?! (Insert smileys$\ldots$)

To separate the namespace from Knuth's
routines, each procedure or function name has
the prefix |gb_prng|.

These are compatible extensions to the Stanford GraphBase.  They are
{\it not\/} part of the Stanford GraphBase.


@(gb_flip.h@>=
#define gb_prng_next_rand(PRNG) @t\quad@>(*(PRNG)->fptr>=0? *(PRNG)->fptr--: gb_prng_cycle((PRNG)))

typedef struct {
long *fptr;
long A[56];
} gb_prng_t;

gb_prng_t *gb_prng_new(long seed);
long gb_prng_cycle(gb_prng_t *prng);
long gb_prng_unif_rand(gb_prng_t *prng, long m);
void gb_prng_free(gb_prng_t *prng);

@  Function |gb_prng_new| allocates and initializes the generator.
@<External functions@>=
#include <stdlib.h> /* We need |malloc|. */
#include "gb_flip.h"

gb_prng_t *gb_prng_new(long seed);
gb_prng_t *
gb_prng_new(long seed)
{
	gb_prng_t *prng = malloc(sizeof(gb_prng_t));
	if ( prng ) {
		register long i;
		register long prev=seed, next=1;
		prng->A[0]=-1;
		seed=prev=mod_diff(prev,0); /* strip off the sign */
		prng->A[55]=prev;
		for (i=21; i; i=(i+21)%55) {
			prng->A[i]=next;
			@<Compute a new |next| value, based on |next|, |prev|, and |seed|@>;
			prev=prng->A[i];
		}
		gb_prng_cycle(prng);
		gb_prng_cycle(prng);
		gb_prng_cycle(prng);
		gb_prng_cycle(prng);
		gb_prng_cycle(prng);
	}
	return prng;
}


@ The other \CEE/ code is pretty easy if you've digested Knuth's code.

@<External functions@>=
long gb_prng_cycle(gb_prng_t *prng);
long gb_prng_cycle(gb_prng_t *prng)
{@+register long *ii, *jj;
  for (ii=&prng->A[1],jj=&prng->A[32];jj<=&prng->A[55];ii++,jj++)
    *ii=mod_diff(*ii,*jj);
  for (jj=&prng->A[1];ii<=&prng->A[55];ii++,jj++)
    *ii=mod_diff(*ii,*jj);
  prng->fptr=&prng->A[54];
  return prng->A[55];
}

@
@<External f...@>=
long gb_prng_unif_rand(gb_prng_t *prng, long m);
long gb_prng_unif_rand(gb_prng_t *prng, long m)
{@+register unsigned long t=two_to_the_31-(two_to_the_31 % m);
  register long r;
  do@+{
    r=gb_prng_next_rand(prng);
  }@+while (t<=(unsigned long)r);
  return r%m;
}

@ Finally, we also add functionality for freeing the generator object.
@<External f...@>=
void 
gb_prng_free(gb_prng_t *prng) 
{
	if ( prng ) {free(prng);}
}

@
@<Test the object-oriented generators@>=
{ gb_prng_t *a, *b;  
  gb_init_rand(-314159L);
  a=gb_prng_new(-314159L);
  b=gb_prng_new(-314159L);
  if (gb_next_rand()!=119318998
  || gb_prng_next_rand(a)!=119318998
  || gb_prng_next_rand(b)!=119318998) {
     fprintf(stderr,"OO Failure on the first try!\n"); return -1;
  }
  for (j=1; j<=133; j++) {
    gb_next_rand();
    gb_prng_next_rand(a);
    gb_prng_next_rand(b);
  }
  if ( gb_unif_rand(0x55555555L)!=748103812
  || gb_prng_unif_rand(a,0x55555555L)!=748103812
  || gb_prng_unif_rand(b,0x55555555L)!=748103812) {
     fprintf(stderr,"OO Failure on the second try!\n"); return -2;
  }
  gb_prng_free(a);	
  gb_prng_free(b);	
}
@z
