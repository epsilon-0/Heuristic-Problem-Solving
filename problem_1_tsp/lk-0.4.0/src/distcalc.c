/*1:*/
#line 53 "./distcalc.w"

#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "length.h"
#include "read.h"

/*2:*/
#line 66 "./distcalc.w"

int noround= 1;
int
main(int argc,char**argv){
char const*TSPLIB_in= "../data/lin105.tsp";
tsp_instance_t*tsp;
FILE*TSPLIB_file;
int a,b;
if(argc>1){
TSPLIB_in= argv[1];
}
if(NULL==(TSPLIB_file= fopen(TSPLIB_in,"r"))){
fprintf(stderr,"Couldn't open %s for reading\n",TSPLIB_in);
exit(1);
}
tsp= read_tsp_file(TSPLIB_file,NULL);
while(scanf(" %d %d",&a,&b)==2){
if(a<0||a>tsp->n){
printf("a=%d is out of range [0,%d)\n",a,tsp->n);
continue;
}
if(b<0||b>tsp->n){
printf("b=%d is out of range [0,%d)\n",b,tsp->n);
continue;
}
printf("cost(%d,%d)=="length_t_spec"\n",a,b,cost(a,b));
}
return 0;
}

/*:2*/
#line 63 "./distcalc.w"


/*:1*/
