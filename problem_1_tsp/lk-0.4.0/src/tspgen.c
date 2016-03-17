#define next_component_slot() (component+n+n-nc)  \

#define sqr(X) ((X) *(X) ) 
#define hull_edge_len(HP) (sqr((HP) ->x-(HP) ->next->x) +sqr((HP) ->y-(HP) ->next->y) )  \

#define pi (3.1415926535897932384626433832795028841972) 
#define two_to_the_31 ((unsigned long) 0x80000000) 
#define scale_01(s,a,b) ((a) +((b) -(a) ) *(s) ) 
#define uniform_sample(g,a,b) scale_01((((double) gb_prng_next_rand(g) ) /two_to_the_31) ,(a) ,(b) )  \

#define uniform_sample_incl(g,a,b) scale_01(((double) gb_prng_next_rand(g) ) /(two_to_the_31-1) ,(a) ,(b) )  \
 \

/*4:*/
#line 186 "./tspgen.w"


const char*prog_name= "tspgen";
const char*tspgen_rcs_id= "$Id: tspgen.w,v 1.27 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
/*7:*/
#line 324 "./tspgen.w"

#define _POSIX_C_SOURCE 2   
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

/*:7*//*13:*/
#line 384 "./tspgen.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



/*:13*//*55:*/
#line 878 "./tspgen.w"

#include <math.h>


/*:55*//*62:*/
#line 1006 "./tspgen.w"

#include <errno.h>

/*:62*/
#line 191 "./tspgen.w"

/*8:*/
#line 331 "./tspgen.w"

#define FIXINCLUDES_NEED_GETOPT
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_GETOPT

/*:8*//*14:*/
#line 392 "./tspgen.w"

#include "error.h"
#include "memory.h"

/*:14*//*16:*/
#line 406 "./tspgen.w"

#include "dsort.h"

/*:16*//*23:*/
#line 477 "./tspgen.w"

#include "gb_flip.h"


/*:23*/
#line 192 "./tspgen.w"

/*50:*/
#line 826 "./tspgen.w"

typedef struct{
double theta;
double v[2];
}rigid_motion_t;

/*:50*/
#line 193 "./tspgen.w"

/*28:*/
#line 572 "./tspgen.w"


typedef struct hull_vertex_s{
double x,y;
struct hull_vertex_s*next,*prev;
}hull_vertex_t;

/*:28*//*37:*/
#line 672 "./tspgen.w"

typedef struct component_s{
struct component_s*left,*right;
hull_vertex_t*hull;
int hull_size;
rigid_motion_t transform;
}component_t;

/*:37*//*48:*/
#line 779 "./tspgen.w"

typedef struct{
hull_vertex_t*vertex;
double len;
}hull_sortbox_t;

/*:48*//*72:*/
#line 1141 "./tspgen.w"

typedef struct{double x,y,angle;}point_t;

/*:72*/
#line 194 "./tspgen.w"


#if !defined(DEBUG)
#define DEBUG 0
#endif

/*9:*/
#line 345 "./tspgen.w"

long seed;
double packing_factor,join_length_bias;

/*:9*//*12:*/
#line 379 "./tspgen.w"

int ne,n;
double*length= NULL;

/*:12*//*22:*/
#line 472 "./tspgen.w"

gb_prng_t*angle_prng;

/*:22*//*26:*/
#line 528 "./tspgen.w"

int nc;

/*:26*//*32:*/
#line 604 "./tspgen.w"

hull_vertex_t*hull_vertex;

/*:32*//*40:*/
#line 700 "./tspgen.w"

component_t*component;


/*:40*//*47:*/
#line 775 "./tspgen.w"

hull_sortbox_t*hull_sortbox;

/*:47*//*71:*/
#line 1135 "./tspgen.w"

point_t*hull_buf= NULL,west;
int*available,nh= 0;

/*:71*/
#line 200 "./tspgen.w"

/*6:*/
#line 288 "./tspgen.w"

void usage(char**argv);
void
usage(char**argv)
{
printf("%s (LK %s)\n",prog_name,VERSION_STRING);
printf(
"Generate TSPLIB instances from minimum spanning tree edge lengths\n"
"\nCopyright (C) 1997 David M. Neto\n");
printf(
"LK comes with NO WARRANTY, to the extent permitted by law.\n");
printf(
"You may redistribute and/or modify copies of LK under the terms of the\n"
"GNU General Public License, version 2 or any later version.\n"
"For more information about these matters, see the file named COPYING.\n");
printf(
"\n"
"Usage: %s [options]\n"
" -h                      : Output this help and quit\n"
" -j <join-length-bias>   : Bias choice of hull point based on associated\n"
"                           hull edge length.\n"
"                             negative means random vertex\n"
"                             0 to 1: use this as a fractional ordinal in\n"
"                               sorted hull edge lengths (read the source!)\n"
" -p <packing-factor>     : Non-negative <packing-factor> is a hint on how\n"
"                           tight to try to make the instance:\n"
"                             0 means try hard to stretch it loose,\n"
"                             large values means try to pack it tight\n"
" -s <seed>               : Use integer <seed> as the random number seed\n",
argv[0]);
}

/*:6*//*17:*/
#line 410 "./tspgen.w"

static int
cmp_double(const void*ap,const void*bp)
{
const double a= *(const double*)ap,b= *(const double*)bp;
if(a<b)return-1;
if(a>b)return 1;
return 0;
}


/*:17*//*33:*/
#line 611 "./tspgen.w"

static void
hull_then_rotate(hull_vertex_t*h,double theta)
{
const double ct= cos(theta),st= sin(theta);
const hull_vertex_t*start= h;
do{
const double x= h->x,y= h->y;
h->x= x*ct-y*st;
h->y= x*st+y*ct;
h= h->next;
}while(h!=start);
}

static void
hull_then_translate(hull_vertex_t*h,double x,double y)
{
const hull_vertex_t*start= h;
do{
h->x+= x;
h->y+= y;
h= h->next;
}while(h!=start);
}

/*:33*//*49:*/
#line 786 "./tspgen.w"

static int
cmp_hull_sortbox(const void*ap,const void*bp)
{
const double
al= ((const hull_sortbox_t*)ap)->len,
bl= ((const hull_sortbox_t*)bp)->len;
if(al<bl)return-1;
if(al>bl)return 1;
return 0;
}

/*:49*//*51:*/
#line 836 "./tspgen.w"

static void
transform_init(rigid_motion_t*t)
{
t->theta= t->v[0]= t->v[1]= 0.0;
}

/*:51*//*53:*/
#line 855 "./tspgen.w"

static void
transform_then_translate(rigid_motion_t*t,double x,double y)
{
t->v[0]+= x;
t->v[1]+= y;
}

/*:53*//*54:*/
#line 866 "./tspgen.w"

static void
transform_then_rotate(rigid_motion_t*t,double theta)
{
const double ct= cos(theta),st= sin(theta);
const double x= t->v[0],y= t->v[1];
t->v[0]= x*ct-y*st;
t->v[1]= x*st+y*ct;
t->theta+= theta;
}

/*:54*//*56:*/
#line 885 "./tspgen.w"

static void
transform_then_transform(rigid_motion_t*t,rigid_motion_t*t2)

{
rigid_motion_t copy;
if(t==t2){copy= *t2;t2= &copy;}
transform_then_rotate(t,t2->theta);
transform_then_translate(t,t2->v[0],t2->v[1]);
}

/*:56*//*57:*/
#line 899 "./tspgen.w"

static void
component_then_rotate(component_t*c,double theta)
{
transform_then_rotate(&(c->transform),theta);
hull_then_rotate(c->hull,theta);
}

static void
component_then_translate(component_t*c,double x,double y)
{
transform_then_translate(&(c->transform),x,y);
hull_then_translate(c->hull,x,y);
}


/*:57*//*61:*/
#line 983 "./tspgen.w"

void rotate_hull_with_bias(component_t*comp,int is_foward);
void
rotate_hull_with_bias(component_t*comp,int is_forward)
{
hull_vertex_t*comph= comp->hull;
if(errno){perror("main: about to rotate comp");errorif(1,"Oops!");}
if(comp->hull_size>1){
double rot;
double alpha= -atan2(comph->y-comph->prev->y,comph->x-comph->prev->x);
double beta= -atan2(comph->next->y-comph->y,comph->next->x-comph->x);
errorif(errno==EDOM,"Sorry, my call to atan2 had a bad argument.");
errorif(errno==ERANGE,"Sorry, the answer to my atan2 call was out of range.");
while(alpha<beta)beta-= 2*pi;

/*64:*/
#line 1038 "./tspgen.w"

/*63:*/
#line 1010 "./tspgen.w"

errno= 0;


/*:63*/
#line 1039 "./tspgen.w"

{double y= 1-uniform_sample(angle_prng,0,1),t= exp(packing_factor*log(y));
switch(errno){
case 0:break;
case ERANGE:t= 1.0;/*63:*/
#line 1010 "./tspgen.w"

errno= 0;


/*:63*/
#line 1043 "./tspgen.w"
;break;
default:perror("main: about to sample alpha beta");errorif(1,"Oops!");
}
errorif(t<0.0||1.0<t,"alpha-beta mediation is %f, not in [0,1]",t);
if(!is_forward)t= 1-t;
rot= t*alpha+(1-t)*beta;
/*87:*/
#line 1417 "./tspgen.w"

#if DEBUG >= 200
{double frac= (rot-beta)/(alpha-beta);
fprintf(stderr," angle %10.5f%% alpha and %10.5f%% beta %s\n",
100*frac,100*(1-frac),(is_forward?"forward":"reverse"));
errorif(frac<0.0||1.0<frac,"Frac %f out of [0,1]",frac);
}
#endif

/*:87*/
#line 1049 "./tspgen.w"

}




/*:64*/
#line 998 "./tspgen.w"


component_then_rotate(comp,rot);
}
/*84:*/
#line 1346 "./tspgen.w"

#if DEBUG >= 100
{int i;hull_vertex_t*here;
printf("Hull size %d, bottom point listed first.\n",a->hull_size);
for(i= 0,here= comp->hull;i<comp->hull_size;i++,here= here->next){
printf("\t%10.5f  %10.5f\n",here->x,here->y);
}
errorif(here!=comp->hull,"hull_size wrong");
}
#endif

/*:84*/
#line 1002 "./tspgen.w"

}

/*:61*//*75:*/
#line 1176 "./tspgen.w"

#define abs(A) ((A)<0 ? -(A) : (A))
static int
cmp_point(const void*ap,const void*bp)
{
const point_t a= *(const point_t*)ap,b= *(const point_t*)bp;
if(a.angle<b.angle)return-1;
if(a.angle>b.angle)return 1;
if(a.x<b.x)return-1;
if(a.x>b.x)return 1;
if(abs(a.y-west.y)<abs(b.y-west.y))return-1;
if(abs(a.y-west.y)>abs(b.y-west.y))return 1;
return 0;
}

/*:75*//*81:*/
#line 1284 "./tspgen.w"

static int
left_turn(point_t u,point_t v,point_t w)
{
const double
ad= (u.x-w.x)*(v.y-w.y),
bc= (u.y-w.y)*(v.x-w.x);
return ad>bc;
}


/*:81*//*83:*/
#line 1324 "./tspgen.w"

static void
write_component(FILE*file,component_t*c,int*city_num)
{
if(c->left){
transform_then_transform(&(c->left->transform),&(c->transform));
write_component(file,c->left,city_num);
}
if(c->left==NULL&&c->right==NULL){
printf("%10d %.15f %.15f\n",
*city_num,
c->transform.v[0],c->transform.v[1]);
*city_num+= 1;
}
if(c->right){
transform_then_transform(&(c->right->transform),&(c->transform));
write_component(file,c->right,city_num);
}
}

/*:83*//*86:*/
#line 1405 "./tspgen.w"

#if DEBUG >= 100
static double
euc2hull(hull_vertex_t*ah,hull_vertex_t*bh)
{
const double dx= ah->x-bh->x,dy= ah->y-bh->y;
return sqrt(dx*dx+dy*dy);
}
#endif


/*:86*/
#line 201 "./tspgen.w"



int main(int argc,char**argv)
{
/*21:*/
#line 468 "./tspgen.w"

gb_prng_t*component_prng,*hull_prng;

/*:21*//*77:*/
#line 1235 "./tspgen.w"

int*stack;

/*:77*/
#line 206 "./tspgen.w"

/*5:*/
#line 256 "./tspgen.w"

seed= -42L;
packing_factor= 100;
join_length_bias= 1;
while(1){
extern char*optarg;
const int opt= getopt(argc,argv,"s:p:j:h");
if(opt==EOF)break;
switch(opt){
case's':seed= atol(optarg);break;
case'p':
packing_factor= atof(optarg);
errorif(packing_factor<0,
"Packing factor should be non-negative, but given %f",packing_factor);
break;
case'j':
join_length_bias= atof(optarg);
errorif(join_length_bias>1,
"Join length bias should be no more than 1, but given %f",
join_length_bias);
break;
case'h':usage(argv);exit(0);break;
case':':errorif(1,"some option is missing an argument");break;
case'?':usage(argv);errorif(1,"Unrecognized option");break;
default:errorif(1,"getopt returned character 0%o",opt);
}
}

/*:5*/
#line 207 "./tspgen.w"

/*20:*/
#line 457 "./tspgen.w"

component_prng= gb_prng_new(seed);
hull_prng= gb_prng_new(seed^42);
angle_prng= gb_prng_new(seed^(42*42));
errorif(
component_prng==NULL
||hull_prng==NULL
||angle_prng==NULL
,"Couldn't allocate three random number generators");

/*:20*/
#line 208 "./tspgen.w"

/*10:*/
#line 356 "./tspgen.w"

/*63:*/
#line 1010 "./tspgen.w"

errno= 0;


/*:63*/
#line 357 "./tspgen.w"

{int num_read,i;
num_read= scanf(" %d ",&ne);
errorif(num_read!=1,"Couldn't read ne, the number of edge lengths.");
errorif(ne<1,"ne, the number of edge lengths, is %d but must be positive.",ne);
n= ne+1;
length= new_arr_of(double,ne);
for(i= 0;i<ne;i++){
num_read= scanf(" %lf ",length+i);
errorif(num_read!=1,"Couldn't read length %d.",i);
errorif(length[i]<=0,"Length %d should be positive, but is %f.",i,length[i]);

}
}
/*63:*/
#line 1010 "./tspgen.w"

errno= 0;


/*:63*/
#line 371 "./tspgen.w"



/*:10*/
#line 209 "./tspgen.w"

/*15:*/
#line 402 "./tspgen.w"

dsort(length,(size_t)ne,sizeof(double),cmp_double);

/*:15*/
#line 210 "./tspgen.w"

/*29:*/
#line 581 "./tspgen.w"

hull_vertex= new_arr_of(hull_vertex_t,n);
/*30:*/
#line 589 "./tspgen.w"

{int i;
for(i= 0;i<n;i++){
hull_vertex[i].x= 0;
hull_vertex[i].y= 0;
hull_vertex[i].next= hull_vertex[i].prev= hull_vertex+i;
}
}

/*:30*/
#line 583 "./tspgen.w"


/*:29*//*38:*/
#line 684 "./tspgen.w"

component= new_arr_of(component_t,n+ne);
{int i;
for(i= 0;i<n;i++){
component[i].hull= hull_vertex+i;
component[i].hull_size= 1;
transform_init(&component[i].transform);
}
for(i= 0;i<n+ne;i++)component[i].left= component[i].right= NULL;
}

/*:38*//*45:*/
#line 767 "./tspgen.w"

hull_sortbox= new_arr_of(hull_sortbox_t,n);

/*:45*//*69:*/
#line 1125 "./tspgen.w"

hull_buf= new_arr_of(point_t,n);
available= new_arr_of(int,n);

/*:69*//*78:*/
#line 1239 "./tspgen.w"

stack= new_arr_of(int,n+1);

/*:78*/
#line 211 "./tspgen.w"

/*19:*/
#line 445 "./tspgen.w"

for(nc= n;nc>1;nc--){
component_t*a,*b;
const double this_length= length[n-nc];


/*27:*/
#line 540 "./tspgen.w"

{component_t temp;
int base= 2*(n-nc),r;
r= base+gb_prng_unif_rand(component_prng,nc);
temp= component[base];component[base]= component[r];component[r]= temp;
r= base+1+gb_prng_unif_rand(component_prng,nc-1);
temp= component[base+1];component[base+1]= component[r];component[r]= temp;
a= component+base;
b= component+base+1;
}


/*:27*/
#line 451 "./tspgen.w"

/*41:*/
#line 711 "./tspgen.w"

if(join_length_bias<0){
/*42:*/
#line 723 "./tspgen.w"

{long steps;
for(steps= gb_prng_unif_rand(hull_prng,a->hull_size);steps;steps--)
a->hull= a->hull->next;
for(steps= gb_prng_unif_rand(hull_prng,b->hull_size);steps;steps--)
b->hull= b->hull->next;
}

/*:42*/
#line 713 "./tspgen.w"

}else{
/*43:*/
#line 732 "./tspgen.w"

{component_t*c;
c= a;/*44:*/
#line 753 "./tspgen.w"

{hull_vertex_t*here= c->hull;
int i,index;
for(i= 0,here= c->hull;i<c->hull_size;i++,here= here->next){
hull_sortbox[i].vertex= here;
hull_sortbox[i].len= hull_edge_len(here);
}
dsort(hull_sortbox,(size_t)c->hull_size,sizeof(hull_sortbox_t),cmp_hull_sortbox);
index= floor(scale_01(join_length_bias,0,c->hull_size));
if(index==c->hull_size)index--;
c->hull= hull_sortbox[index].vertex;
}

/*:44*/
#line 734 "./tspgen.w"

c= b;/*44:*/
#line 753 "./tspgen.w"

{hull_vertex_t*here= c->hull;
int i,index;
for(i= 0,here= c->hull;i<c->hull_size;i++,here= here->next){
hull_sortbox[i].vertex= here;
hull_sortbox[i].len= hull_edge_len(here);
}
dsort(hull_sortbox,(size_t)c->hull_size,sizeof(hull_sortbox_t),cmp_hull_sortbox);
index= floor(scale_01(join_length_bias,0,c->hull_size));
if(index==c->hull_size)index--;
c->hull= hull_sortbox[index].vertex;
}

/*:44*/
#line 735 "./tspgen.w"

}

/*:43*/
#line 715 "./tspgen.w"

}

/*:41*/
#line 452 "./tspgen.w"

/*58:*/
#line 928 "./tspgen.w"

rotate_hull_with_bias(a,1);
b->hull= b->hull->next;rotate_hull_with_bias(b,0);component_then_rotate(b,pi);
{
component_t*c= next_component_slot();
hull_vertex_t*ah= a->hull,*bh= b->hull;
/*59:*/
#line 940 "./tspgen.w"

component_then_translate(a,bh->x-ah->x,bh->y-ah->y+this_length);
/*85:*/
#line 1358 "./tspgen.w"

#if DEBUG >= 100
{
hull_vertex_t*here,*ahere,*bhere;
const double d= euc2hull(ah,bh);
int fail= 0;
here= ah;


for(here= bh->next;here!=bh;here= here->next){
const double hd= euc2hull(ah,here);
if(d>hd)fail= 1,fprintf(stderr,"d = %f > hd = %f\n",d,hd);
fprintf(stderr,"a");
}

for(here= ah->next;here!=ah;here= here->next){
const double hd= euc2hull(bh,here);
if(d>hd)fail= 1,fprintf(stderr,"d = %f > hd = %f\n",d,hd);
fprintf(stderr,"b");
}


ahere= ah;
do{
bhere= bh;
do{
const double hd= euc2hull(ahere,bhere);
if((ahere!=ah||bhere!=bh)&&d>hd)
fail= 1,fprintf(stderr,"full d = %f > hd = %f\n",d,hd);
bhere= bhere->next;
fprintf(stderr,"c");
}while(bhere!=bh);
ahere= ahere->next;
}while(ahere!=ah);



if(d<this_length-1e-6)
fail= 1,fprintf(stderr,"d = %f < %f = this_length\n",d,this_length);
if(d>this_length+1e-6)
fail= 1,fprintf(stderr,"d = %f > %f = this_length\n",d,this_length);
fprintf(stderr,"\n");
errorif(fail,"distances mucked up!");
}
#endif

/*:85*/
#line 942 "./tspgen.w"


/*:59*/
#line 934 "./tspgen.w"

/*65:*/
#line 1064 "./tspgen.w"

c->left= a;
c->right= b;
/*67:*/
#line 1092 "./tspgen.w"

/*68:*/
#line 1102 "./tspgen.w"

{hull_vertex_t*start,*here;
nh= 0;
here= start= a->hull;
do{
hull_buf[nh].x= here->x;
hull_buf[nh].y= here->y;
available[nh]= here-hull_vertex;
here= here->next;
nh++;
}while(here!=start);
here= start= b->hull;
do{
hull_buf[nh].x= here->x;
hull_buf[nh].y= here->y;
available[nh]= here-hull_vertex;
here= here->next;
nh++;
}while(here!=start);
}

/*:68*/
#line 1093 "./tspgen.w"

/*73:*/
#line 1146 "./tspgen.w"

{int i;
west= hull_buf[0];
for(i= 1;i<nh;i++)
if(hull_buf[i].x<west.x){
west= hull_buf[i];
hull_buf[i]= hull_buf[0];
hull_buf[0]= west;
}
}

/*:73*/
#line 1094 "./tspgen.w"

/*74:*/
#line 1163 "./tspgen.w"

{int i;
for(i= 1;i<nh;i++){
hull_buf[i].angle= atan2(hull_buf[i].y-west.y,hull_buf[i].x-west.x);
}
qsort(&hull_buf[1],(size_t)nh-1,sizeof(point_t),cmp_point);
}

/*:74*/
#line 1095 "./tspgen.w"

/*76:*/
#line 1213 "./tspgen.w"

{
int i;
int top= -1;
/*88:*/
#line 1427 "./tspgen.w"

#if DEBUG >= 100
printf("Graham scan: nh==%d\n",nh);fflush(stdout);
#endif

/*:88*/
#line 1217 "./tspgen.w"

for(i= 0;i<=nh;i++){
stack[++top]= (i<nh)?i:0;
/*89:*/
#line 1433 "./tspgen.w"

#if DEBUG >= 100
printf(" push   %d, top==%d\n",stack[top],top);fflush(stdout);
#endif


/*:89*/
#line 1220 "./tspgen.w"

while(top>=2&&stack[top-2]!=stack[top]
&&!left_turn(hull_buf[stack[top-2]],
hull_buf[stack[top-1]],
hull_buf[stack[top]])){
/*90:*/
#line 1440 "./tspgen.w"

#if DEBUG>=100
printf(" remove %d, top==%d\n",stack[top-1],top-1);fflush(stdout);
#endif

/*:90*/
#line 1225 "./tspgen.w"

stack[top-1]= stack[top];
top--;
}
}
/*91:*/
#line 1446 "./tspgen.w"

#if DEBUG >=100
printf("Done Graham scan: top==%d\n",top);fflush(stdout);
#endif

/*:91*/
#line 1230 "./tspgen.w"

/*80:*/
#line 1255 "./tspgen.w"

for(i= 0;i<top;i++){
hull_vertex_t*here= &hull_vertex[available[i]];
here->x= hull_buf[stack[i]].x;
here->y= hull_buf[stack[i]].y;
here->prev= &hull_vertex[available[(i-1+top)%top]];
here->next= &hull_vertex[available[(i+1)%top]];
}
c->hull= &hull_vertex[available[0]];
c->hull_size= top;

/*:80*/
#line 1231 "./tspgen.w"

}

/*:76*/
#line 1096 "./tspgen.w"


/*:67*/
#line 1067 "./tspgen.w"


/*:65*/
#line 935 "./tspgen.w"

if(nc>2){/*60:*/
#line 954 "./tspgen.w"

component_then_rotate(c,uniform_sample(angle_prng,-pi,pi));

/*:60*/
#line 936 "./tspgen.w"
}
}

/*:58*/
#line 453 "./tspgen.w"

}

/*:19*/
#line 212 "./tspgen.w"

/*82:*/
#line 1306 "./tspgen.w"

/*30:*/
#line 589 "./tspgen.w"

{int i;
for(i= 0;i<n;i++){
hull_vertex[i].x= 0;
hull_vertex[i].y= 0;
hull_vertex[i].next= hull_vertex[i].prev= hull_vertex+i;
}
}

/*:30*/
#line 1307 "./tspgen.w"

printf("NAME: egen%d\n",n);
printf(
"COMMENT: generated from MST edge lengths, (LK %s) %s -s %ld -j %f -p %f\n",
VERSION_STRING,prog_name,seed,join_length_bias,packing_factor);
printf("TYPE: TSP\n");
printf("DIMENSION: %d\n",n);
printf("EDGE_WEIGHT_TYPE: EUC_2D\n");
printf("NODE_COORD_SECTION\n");
errorif(nc!=1,"Must be only one component, but nc==%d.",nc);
{int city_num= 1;
write_component(stdout,next_component_slot()-1,&city_num);
errorif(city_num-1!=n,"Wrote %d cities instead of %d.",city_num,n);
}
printf("EOF\n");

/*:82*/
#line 213 "./tspgen.w"

/*11:*/
#line 375 "./tspgen.w"

free_mem(length);

/*:11*//*31:*/
#line 600 "./tspgen.w"

free_mem(hull_vertex);

/*:31*//*39:*/
#line 696 "./tspgen.w"

free_mem(component);

/*:39*//*46:*/
#line 771 "./tspgen.w"

free_mem(hull_sortbox);

/*:46*//*70:*/
#line 1130 "./tspgen.w"

free_mem(hull_buf);
free_mem(available);

/*:70*//*79:*/
#line 1243 "./tspgen.w"

free_mem(stack);


/*:79*/
#line 214 "./tspgen.w"

return 0;
}

/*:4*/
