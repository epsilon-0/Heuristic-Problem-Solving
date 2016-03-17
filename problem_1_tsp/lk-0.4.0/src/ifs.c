#define DIMENSIONS 2
#define two_to_the_31 ((double) 0x80000000)  \

/*4:*/
#line 239 "./ifs.w"

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
/*6:*/
#line 296 "./ifs.w"

#include "gb_flip.h" 

/*:6*//*19:*/
#line 554 "./ifs.w"

#include "fixincludes.h"


/*:19*/
#line 243 "./ifs.w"


/*8:*/
#line 325 "./ifs.w"

typedef double point_t[DIMENSIONS];

/*:8*//*9:*/
#line 346 "./ifs.w"

typedef struct{double A[DIMENSIONS][DIMENSIONS],v[DIMENSIONS];}affine_t;

/*:9*/
#line 245 "./ifs.w"


int main(int argc,char**argv){
/*10:*/
#line 366 "./ifs.w"

int n_ifs;
double*weight,*cum_norm_weight;
affine_t*map;

/*:10*//*17:*/
#line 525 "./ifs.w"

int next_map;

/*:17*/
#line 248 "./ifs.w"

/*5:*/
#line 277 "./ifs.w"

long seed;
int n;
char*name;
if(argc!=4){
fprintf(stderr,
"Usage: %s <seed> <n> <name>\n",argv[0]);
exit(1);
}
seed= atol(argv[1]);
n= atoi(argv[2]);
if(n<10){
fprintf(stderr,"Need at least 10 cities; only %d specified.\n",n);
exit(2);
}
name= argv[3];
gb_init_rand(seed);

/*:5*/
#line 249 "./ifs.w"

/*11:*/
#line 383 "./ifs.w"

if(1!=scanf(" %d",&n_ifs))
{fprintf(stderr,"IFS does not specify n_ifs, number of maps\n");exit(3);}
if(n_ifs<1)
{fprintf(stderr,"Need a positive number of maps: n_ifs=%d\n",n_ifs);exit(4);}
weight= malloc(sizeof(double)*n_ifs);
cum_norm_weight= malloc(sizeof(double)*n_ifs);
map= malloc(sizeof(affine_t)*n_ifs);
if(weight==NULL||cum_norm_weight==NULL||map==NULL)
{fprintf(stderr,"Couldn't allocate arrays\n");exit(5);}
{int i,j,k;
for(i= 0;i<n_ifs;i++){
for(j= 0;j<DIMENSIONS;j++)
for(k= 0;k<DIMENSIONS;k++)
if(1!=scanf(" %lf",&map[i].A[j][k]))
{fprintf(stderr,"Couldn't read map %d array entry (%d,%d)\n",i,j,k);
exit(6);}
for(j= 0;j<DIMENSIONS;j++)
if(1!=scanf(" %lf",&map[i].v[j]))
{fprintf(stderr,"Couldn't read map %d vector entry (%d)\n",i,j);
exit(7);}
if(1!=scanf(" %lf",&weight[i]))
{fprintf(stderr,"Couldn't read map %d weight\n",i);
exit(8);}
}
}

/*:11*/
#line 250 "./ifs.w"

/*7:*/
#line 311 "./ifs.w"

printf("NAME: %s\n",name);
printf("TYPE: TSP\n");
printf("COMMENT: %s %s %s %s\n",argv[0],argv[1],argv[2],argv[3]);
printf("DIMENSION: %d\n",n);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");

/*:7*/
#line 251 "./ifs.w"

/*12:*/
#line 429 "./ifs.w"

/*13:*/
#line 449 "./ifs.w"

{int i;double total_weight= 0.0,sum_weight= 0.0;
for(i= 0;i<n_ifs;i++)
total_weight+= weight[i];
if(total_weight<1e-10)
{fprintf(stderr,"Total weight %f is too small (less than 1e-10)\n",total_weight);exit(9);}
for(i= 0;i<n_ifs;i++){
sum_weight+= weight[i];
cum_norm_weight[i]= sum_weight/total_weight;
}
}

/*:13*/
#line 430 "./ifs.w"

{int i;point_t u;
for(i= 0;i<DIMENSIONS;i++)u[i]= 0.0;
/*15:*/
#line 503 "./ifs.w"

{int i;
for(i= 0;i<2000;i++){
/*16:*/
#line 513 "./ifs.w"

{int d,i;point_t u_prime;
/*14:*/
#line 476 "./ifs.w"

{
const double fair_toss= gb_next_rand()/two_to_the_31;
int i;
for(i= 0;i<n_ifs&&cum_norm_weight[i]<fair_toss;i++)
;
if(i==n_ifs)i--;
next_map= i;
}



/*:14*/
#line 515 "./ifs.w"

for(d= 0;d<DIMENSIONS;d++){
u_prime[d]= map[next_map].v[d];
for(i= 0;i<DIMENSIONS;i++)
u_prime[d]+= map[next_map].A[d][i]*u[i];
}
for(d= 0;d<DIMENSIONS;d++)u[d]= u_prime[d];
}

/*:16*/
#line 506 "./ifs.w"

}
}

/*:15*/
#line 433 "./ifs.w"

/*18:*/
#line 536 "./ifs.w"

{int i,d;
for(i= 0;i<n;i++){
/*16:*/
#line 513 "./ifs.w"

{int d,i;point_t u_prime;
/*14:*/
#line 476 "./ifs.w"

{
const double fair_toss= gb_next_rand()/two_to_the_31;
int i;
for(i= 0;i<n_ifs&&cum_norm_weight[i]<fair_toss;i++)
;
if(i==n_ifs)i--;
next_map= i;
}



/*:14*/
#line 515 "./ifs.w"

for(d= 0;d<DIMENSIONS;d++){
u_prime[d]= map[next_map].v[d];
for(i= 0;i<DIMENSIONS;i++)
u_prime[d]+= map[next_map].A[d][i]*u[i];
}
for(d= 0;d<DIMENSIONS;d++)u[d]= u_prime[d];
}

/*:16*/
#line 539 "./ifs.w"

printf("%7d",i+1);
for(d= 0;d<DIMENSIONS;d++)
printf(" %25f",u[d]);
printf("\n");
}
}

/*:18*/
#line 434 "./ifs.w"

printf("EOF\n");
}

/*:12*/
#line 252 "./ifs.w"

return 0;
}

/*:4*/
