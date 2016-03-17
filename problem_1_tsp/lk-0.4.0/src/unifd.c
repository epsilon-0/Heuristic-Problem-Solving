#define SIZE (10000) 
#define TWO_TO_THE_31 ((double) ((unsigned long) 0x80000000) )  \

/*1:*/
#line 73 "./unifd.w"

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include "fixincludes.h"

#include "gb_flip.h"
#define SIZE (10000)
int main(int argc,char**argv){
int i,n;
long s;
if(argc!=4){
fprintf(stderr,"Usage: %s <seed> <n> <name>\n",argv[0]);exit(1);
}
s= atol(argv[1]);
n= atoi(argv[2]);
gb_init_rand(s);
printf("NAME: %s\n",argv[3]);
printf("TYPE: TSP\n");
printf("COMMENT: Automatically generated with seed %ld by unifd\n",s);
printf("DIMENSION: %d\n",n);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");
for(i= 0;i<n;i++){
double x,y;
x= ((SIZE*((double)gb_next_rand())))/TWO_TO_THE_31;
y= ((SIZE*((double)gb_next_rand())))/TWO_TO_THE_31;
printf("%7d %14.8f %14.8f\n",i+1,x,y);
}
printf("EOF\n");
return 0;
}/*:1*/
