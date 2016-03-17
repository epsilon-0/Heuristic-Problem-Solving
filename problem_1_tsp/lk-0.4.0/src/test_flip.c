/*2:*/
#line 34 "gb_flip.w"

#include <stdio.h>
#include "gb_flip.h"   

#line 4 "gb_flip.ch"
int main(int argc,char**argv);
int main(int argc,char**argv)
#line 39 "gb_flip.w"
{long j;
gb_init_rand(-314159L);
if(gb_next_rand()!=119318998){
fprintf(stderr,"Failure on the first try!\n");return-1;
}
for(j= 1;j<=133;j++)
gb_next_rand();
#line 14 "gb_flip.ch"
if(gb_unif_rand(0x55555555L)!=748103812){
fprintf(stderr,"Failure on the second try!\n");return-2;
}
/*19:*/
#line 161 "gb_flip.ch"

{gb_prng_t*a,*b;
gb_init_rand(-314159L);
a= gb_prng_new(-314159L);
b= gb_prng_new(-314159L);
if(gb_next_rand()!=119318998
||gb_prng_next_rand(a)!=119318998
||gb_prng_next_rand(b)!=119318998){
fprintf(stderr,"OO Failure on the first try!\n");return-1;
}
for(j= 1;j<=133;j++){
gb_next_rand();
gb_prng_next_rand(a);
gb_prng_next_rand(b);
}
if(gb_unif_rand(0x55555555L)!=748103812
||gb_prng_unif_rand(a,0x55555555L)!=748103812
||gb_prng_unif_rand(b,0x55555555L)!=748103812){
fprintf(stderr,"OO Failure on the second try!\n");return-2;
}
gb_prng_free(a);
gb_prng_free(b);
}
#line 256 "gb_flip.w"

/*:19*/
#line 17 "gb_flip.ch"

fprintf(stderr,"OK, the gb_flip routines seem to work!\n");
return 0;
#line 51 "gb_flip.w"
}

/*:2*/
