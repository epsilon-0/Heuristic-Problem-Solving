#define SIZE (10000) 
#define TWO_TO_THE_31 ((double) ((unsigned long) 0x80000000) )  \

/*1:*/
#line 59 "./fullgrid.w"

#include <stdio.h>
#include <stdlib.h>
#include "fixincludes.h"

#define SIZE (10000)
int main(int argc,char**argv){
int i,j,n,levels,onedn;
if(argc!=3){
fprintf(stderr,"Usage: %s <levels> <name>\n",argv[0]);exit(1);
}
levels= atoi(argv[1]);
for(i= 0,onedn= n= 1;i<levels;n*= 4,onedn*= 2,i++);
printf("NAME: %s\n",argv[2]);
printf("TYPE: TSP\n");
printf("COMMENT: Generated with %d levels by fullgrid\n",levels);
printf("DIMENSION: %d\n",n);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");
for(i= 0;i<onedn;i++)
for(j= 0;j<onedn;j++){
double x,y;
x= SIZE*(((double)i)/onedn+0.5/onedn);
y= SIZE*(((double)j)/onedn+0.5/onedn);
printf("%7d %14.8f %14.8f\n",onedn*i+j+1,x,y);
}
printf("EOF\n");
return 0;
}/*:1*/
