#define RADIUS (10000/2)  \

#define PI (3.1415926535897932384626433832795028841971693993751) 
/*3:*/
#line 106 "./sier.w"

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fixincludes.h"
#include "gb_flip.h"

int main(int argc,char**argv){
/*4:*/
#line 123 "./sier.w"

int cities,corners;
long seed;
double rotation,shrinkfactor;
char*name;
if(argc!=7){
fprintf(stderr,
"Usage: %s <seed> <cities> <corners> <shrinkfactor> <rotation> <name>\n",argv[0]);
exit(1);
}
seed= atol(argv[1]);
cities= atoi(argv[2]);
if(cities<10){
fprintf(stderr,"Need at least 10 cities; only %d specified.\n",cities);
exit(2);
}
corners= atoi(argv[3]);
shrinkfactor= atof(argv[4]);
rotation= atof(argv[5]);
name= argv[6];
gb_init_rand(seed);

/*:4*/
#line 116 "./sier.w"

/*5:*/
#line 146 "./sier.w"

printf("NAME: %s\n",name);
printf("TYPE: TSP\n");
printf("COMMENT: %s %s %s %s %s %s %s\n",
argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
printf("DIMENSION: %d\n",cities);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");

/*:5*/
#line 117 "./sier.w"

/*6:*/
#line 156 "./sier.w"

{int i;
typedef double point_t[2];
point_t*corner,here= {0.0,0.0};
/*7:*/
#line 174 "./sier.w"


if((corner= malloc(sizeof(point_t)*corners))==NULL){
fprintf(stderr,"Couldn't allocate an array of %d corners\n",corners);
exit(1);
}
{const double shift= rotation*PI/180;
for(i= 0;i<corners;i++){
corner[i][0]= RADIUS*cos(PI*2*((double)i)/corners+shift);
corner[i][1]= RADIUS*sin(PI*2*((double)i)/corners+shift);
}
}

/*:7*/
#line 160 "./sier.w"

/*8:*/
#line 191 "./sier.w"

for(i= 0;i<500;i++){
/*10:*/
#line 205 "./sier.w"

{const int c= gb_unif_rand(corners);
here[0]= (1-shrinkfactor)*here[0]+shrinkfactor*corner[c][0];
here[1]= (1-shrinkfactor)*here[1]+shrinkfactor*corner[c][1];
}

/*:10*/
#line 193 "./sier.w"

}


/*:8*/
#line 161 "./sier.w"

/*9:*/
#line 198 "./sier.w"

for(i= 0;i<cities;i++){
/*10:*/
#line 205 "./sier.w"

{const int c= gb_unif_rand(corners);
here[0]= (1-shrinkfactor)*here[0]+shrinkfactor*corner[c][0];
here[1]= (1-shrinkfactor)*here[1]+shrinkfactor*corner[c][1];
}

/*:10*/
#line 200 "./sier.w"

printf("%7d %24.19f %24.19f\n",i+1,here[0],here[1]);
}

/*:9*/
#line 162 "./sier.w"

printf("EOF\n");
}


/*:6*/
#line 118 "./sier.w"

return 0;
}

/*:3*/
