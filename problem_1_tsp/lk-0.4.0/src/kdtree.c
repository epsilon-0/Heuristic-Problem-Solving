#define new_box() ((E2_box_t*) pool_alloc(box_pool) ) 
#define free_box(P) pool_free(box_pool,(P) )  \
 \

#define new_node() ((E2_node_t*) (pool_alloc(node_pool) ) ) 
#define free_node(P) pool_free(node_pool,(P) )  \

#define val(a) (coord[perm[(a) ]].x[cutdimen]) 
#define valx(a) (coord[perm[(a) ]].x[0]) 
#define valy(a) (coord[perm[(a) ]].x[1]) 
#define med3(a,b,c) (val(a) <val(b) ?(val(b) <val(c) ?b:val(a) <val(c) ?(c) :(a) )  \
:(val(b) >val(c) ?b:val(a) >val(c) ?(c) :(a) ) )  \

#define swapint(J,K) {int t= J;J= K;K= t;} \
 \

#define min(x,y) ((x) <(y) ?(x) :(y) ) 
#define max(x,y) ((x) >(y) ?(x) :(y) ) 
#define my_sgn(X) ((X) <0?0:((X) >0?2:1) )  \
 \

#define verb(a) if(verbose>=(a) ) 
/*1:*/
#line 328 "./kdtree.w"

#include <config.h>
#include "lkconfig.h"
/*30:*/
#line 848 "./kdtree.w"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "fixincludes.h"


/*:30*//*59:*/
#line 1382 "./kdtree.w"

#include <stdio.h>

/*:59*//*75:*/
#line 1694 "./kdtree.w"

#include <math.h>


/*:75*/
#line 331 "./kdtree.w"

/*7:*/
#line 454 "./kdtree.w"

#include "length.h"
#include "read.h"

/*:7*/
#line 332 "./kdtree.w"

/*3:*/
#line 353 "./kdtree.w"

#include "kdtree.h"

/*:3*//*17:*/
#line 666 "./kdtree.w"

#include "pool.h"


/*:17*//*28:*/
#line 826 "./kdtree.w"

#include "error.h"
#include "memory.h"

/*:28*//*90:*/
#line 2054 "./kdtree.w"

#include "error.h"
#include "memory.h"

/*:90*/
#line 333 "./kdtree.w"


/*15:*/
#line 647 "./kdtree.w"

typedef struct{
double xmin,xmax,ymin,ymax;
}E2_box_t;

/*:15*/
#line 335 "./kdtree.w"

/*8:*/
#line 485 "./kdtree.w"

typedef struct E2_node_s{
/*12:*/
#line 580 "./kdtree.w"

struct E2_node_s*parent;


/*:12*//*14:*/
#line 643 "./kdtree.w"

E2_box_t*bbox;

/*:14*/
#line 487 "./kdtree.w"

union{
struct{
int cutdimen;
double cutvalue;
struct E2_node_s*lo_child,*hi_child;
/*21:*/
#line 745 "./kdtree.w"

struct E2_node_s*eq_child;

/*:21*/
#line 493 "./kdtree.w"

}i;
struct{
int lo,hi;
/*54:*/
#line 1305 "./kdtree.w"

int hi_all;

/*:54*/
#line 497 "./kdtree.w"

}e;
}f;
char is_bucket;
/*13:*/
#line 589 "./kdtree.w"

#if !defined(KD_NO_HIDDEN_BIT)
char hidden;
#endif


/*:13*/
#line 501 "./kdtree.w"

}E2_node_t;


/*:8*/
#line 336 "./kdtree.w"

/*25:*/
#line 806 "./kdtree.w"

static pool_t*node_pool,*box_pool;

/*:25*//*27:*/
#line 822 "./kdtree.w"

static int n;

/*:27*//*32:*/
#line 891 "./kdtree.w"

static E2_node_t*E2_root;
static coord_2d*coord;

/*:32*//*36:*/
#line 975 "./kdtree.w"

static E2_node_t**E2_point_to_bucket;

/*:36*//*70:*/
#line 1590 "./kdtree.w"

int quadrant_mask;


/*:70*//*71:*/
#line 1615 "./kdtree.w"

static int E2_nn_seed,E2_nn_incumbent;
static double E2_nn_dist,E2_nn_dist_sq,E2_nn_seed_x,E2_nn_seed_y;

/*:71*//*82:*/
#line 1909 "./kdtree.w"

static double E2_strict_upper_bound;

/*:82*//*95:*/
#line 2147 "./kdtree.w"

extern int verbose;

/*:95*/
#line 337 "./kdtree.w"

/*9:*/
#line 519 "./kdtree.w"

int*perm;


/*:9*//*10:*/
#line 542 "./kdtree.w"

int kd_bucket_cutoff= 5;

/*:10*//*18:*/
#line 676 "./kdtree.w"

int kd_bbox_skip= 3;

/*:18*/
#line 338 "./kdtree.w"

/*33:*/
#line 915 "./kdtree.w"

static E2_node_t*
E2_build_helper(E2_node_t*parent,int flat_dimens,int level,
int lo,int hi,
double xmin,double xmax,double ymin,double ymax){
E2_node_t*node= new_node();
node->parent= parent;
#if !defined(KD_NO_HIDDEN_BIT)
node->hidden= lo>=hi;
#endif
if((++level%kd_bbox_skip)==0){
node->bbox= new_box();
node->bbox->xmin= xmin;
node->bbox->xmax= xmax;
node->bbox->ymin= ymin;
node->bbox->ymax= ymax;
/*94:*/
#line 2125 "./kdtree.w"

#ifdef KD_CHECK_BBOX
verb(1000)printf("lo %d hi %d\n",lo,hi);
if(lo<hi)
{double xl,xh,yl,yh;int i;
xl= xmax;xh= xmin;yl= ymax;yh= ymin;
for(i= lo;i<hi;i++){
verb(1000)printf("xl %f i %d perm[i] %d %f %f xl\n",xl,i,perm[i],
coord[perm[i]].x[0],coord[perm[i]].x[1]);
xl= min(xl,valx(i));
yl= min(yl,valy(i));
xh= max(xh,valx(i));
yh= max(yh,valy(i));
}
errorif(xl!=xmin,"xl %f!= xmin %f",xl,xmin);
errorif(yl!=ymin,"yl %f!= ymin %f",yl,ymin);
errorif(xh!=xmax,"xh %f!= xmax %f",xh,xmax);
errorif(yh!=ymax,"yh %f!= ymax %f",yh,ymax);
}
#endif

/*:94*/
#line 931 "./kdtree.w"

}else{
node->bbox= NULL;
}
if(hi-lo<=kd_bucket_cutoff||flat_dimens==0x03){
node->is_bucket= 1;
node->f.e.lo= lo;
node->f.e.hi= hi;
/*55:*/
#line 1309 "./kdtree.w"

node->f.e.hi_all= hi;

/*:55*/
#line 939 "./kdtree.w"

/*35:*/
#line 969 "./kdtree.w"

{int i;
for(i= lo;i<hi;i++)E2_point_to_bucket[perm[i]]= node;
}

/*:35*/
#line 940 "./kdtree.w"

}else{
node->is_bucket= 0;
/*39:*/
#line 998 "./kdtree.w"

{int cutdimen= 0;
switch(flat_dimens){
case 0:
if(xmax-xmin>ymax-ymin)cutdimen= 0;
else cutdimen= 1;
break;
case 1:
cutdimen= 1;
break;
case 2:
cutdimen= 0;
break;
case 3:
default:
errorif(1,"Invalid flat_dimens: %d",flat_dimens);
}
/*40:*/
#line 1021 "./kdtree.w"

{int p;
int a,b,c,d;
double exl,exh,lxl,lxh,gxl,gxh;
double eyl,eyh,lyl,lyh,gyl,gyh;
/*41:*/
#line 1069 "./kdtree.w"

p= (lo+hi)/2;
if(hi-lo>7){
int p1= lo,pn= hi-1;
if(hi-lo>40){
int s= (hi-lo)/8;
p1= med3(p1,p1+s,p1+s+s);
p= med3(p-s,p,p+s);
pn= med3(pn-s-s,pn-s,pn);
}
p= med3(p1,p,pn);
}

/*:41*/
#line 1026 "./kdtree.w"

/*42:*/
#line 1101 "./kdtree.w"

/*43:*/
#line 1139 "./kdtree.w"

exl= lxl= gxl= xmax;
exh= lxh= gxh= xmin;
eyl= lyl= gyl= ymax;
eyh= lyh= gyh= ymin;

/*:43*/
#line 1102 "./kdtree.w"

a= b= lo;c= d= hi-1;
{double v= val(p),diff;
node->f.i.cutdimen= cutdimen;
node->f.i.cutvalue= v;
for(;;){
while(b<=c&&(diff= val(b)-v)<=0.0){
if(diff==0.0){
/*44:*/
#line 1148 "./kdtree.w"

exl= min(exl,valx(b));
exh= max(exh,valx(b));
eyl= min(eyl,valy(b));
eyh= max(eyh,valy(b));

/*:44*/
#line 1110 "./kdtree.w"

swapint(perm[a],perm[b]);
a++;
}else{
/*45:*/
#line 1155 "./kdtree.w"

lxl= min(lxl,valx(b));
lxh= max(lxh,valx(b));
lyl= min(lyl,valy(b));
lyh= max(lyh,valy(b));

/*:45*/
#line 1114 "./kdtree.w"

}
b++;
}
while(c>=b&&(diff= val(c)-v)>=0.0){
if(diff==0.0){
/*46:*/
#line 1162 "./kdtree.w"

exl= min(exl,valx(c));
exh= max(exh,valx(c));
eyl= min(eyl,valy(c));
eyh= max(eyh,valy(c));

/*:46*/
#line 1120 "./kdtree.w"

swapint(perm[d],perm[c]);
d--;
}else{
/*47:*/
#line 1169 "./kdtree.w"

gxl= min(gxl,valx(c));
gxh= max(gxh,valx(c));
gyl= min(gyl,valy(c));
gyh= max(gyh,valy(c));

/*:47*/
#line 1124 "./kdtree.w"

}
c--;
}
if(b>c)break;
swapint(perm[b],perm[c]);
/*45:*/
#line 1155 "./kdtree.w"

lxl= min(lxl,valx(b));
lxh= max(lxh,valx(b));
lyl= min(lyl,valy(b));
lyh= max(lyh,valy(b));

/*:45*/
#line 1130 "./kdtree.w"

/*47:*/
#line 1169 "./kdtree.w"

gxl= min(gxl,valx(c));
gxh= max(gxh,valx(c));
gyl= min(gyl,valy(c));
gyh= max(gyh,valy(c));

/*:47*/
#line 1131 "./kdtree.w"

b++;c--;
}
/*48:*/
#line 1176 "./kdtree.w"

{
int s,l,h;
s= min(a-lo,b-a);
for(l= lo,h= b-s;s;s--){swapint(perm[l],perm[h]);l++;h++;}
s= min(d-c,hi-1-d);
for(l= b,h= hi-s;s;s--){swapint(perm[l],perm[h]);l++;h++;}
}

/*:48*/
#line 1134 "./kdtree.w"

}
/*89:*/
#line 2030 "./kdtree.w"

#ifdef KD_CHECK_PARTITIONING

{int i;double v= node->f.i.cutvalue;
verb(1000)printf("\nDimension %d\n",cutdimen);
for(i= lo;i<hi;i++){
if(i==lo)verb(1000)printf("Checking lesser: %d %d\n",lo,lo+b-a);
if(i==lo+b-a)verb(1000)printf("Checking equal: %d %d\n",lo+b-a,hi-(d-c));
if(i==hi-(d-c))verb(1000)printf("Checking greater: %d %d\n",hi-(d-c),hi);
verb(1000)printf("%d (%.0f,%.0f)\t %.0f %.0f\n",i,valx(i),valy(i),val(i),v);fflush(stdout);
}
for(i= lo;i<lo+b-a;i++){
errorif(val(i)>=v,"Not lesser at %d",i);
}
for(i= lo+b-a;i<hi-(d-c);i++){
errorif(val(i)!=v,"Not equal at %d",i);
}
for(i= hi-(d-c);i<hi;i++){
errorif(val(i)<=v,"Not greater at %d",i);
}
}
#endif

/*:89*/
#line 1136 "./kdtree.w"


/*:42*/
#line 1027 "./kdtree.w"

/*49:*/
#line 1245 "./kdtree.w"

#if defined(KD_BUILD_SMALLEST_SEGMENT_FIRST)
{int l= b-a,m= hi-(d-c)-lo+b-a,h= d-c;
if(l<=m){
if(m<=h){/*50:*/
#line 1272 "./kdtree.w"

node->f.i.lo_child= 
E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

/*:50*/
#line 1249 "./kdtree.w"
/*52:*/
#line 1286 "./kdtree.w"

node->f.i.eq_child= 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


/*:52*/
#line 1249 "./kdtree.w"

/*51:*/
#line 1276 "./kdtree.w"

node->f.i.hi_child= 
E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

/*:51*/
#line 1250 "./kdtree.w"
}
else if(l<=h){/*50:*/
#line 1272 "./kdtree.w"

node->f.i.lo_child= 
E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

/*:50*/
#line 1251 "./kdtree.w"
/*51:*/
#line 1276 "./kdtree.w"

node->f.i.hi_child= 
E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

/*:51*/
#line 1251 "./kdtree.w"
/*52:*/
#line 1286 "./kdtree.w"

node->f.i.eq_child= 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


/*:52*/
#line 1251 "./kdtree.w"
}
else{/*51:*/
#line 1276 "./kdtree.w"

node->f.i.hi_child= 
E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

/*:51*/
#line 1252 "./kdtree.w"
/*50:*/
#line 1272 "./kdtree.w"

node->f.i.lo_child= 
E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

/*:50*/
#line 1252 "./kdtree.w"
/*52:*/
#line 1286 "./kdtree.w"

node->f.i.eq_child= 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


/*:52*/
#line 1252 "./kdtree.w"
}
}else{
if(l<=h){/*52:*/
#line 1286 "./kdtree.w"

node->f.i.eq_child= 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


/*:52*/
#line 1254 "./kdtree.w"
/*50:*/
#line 1272 "./kdtree.w"

node->f.i.lo_child= 
E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

/*:50*/
#line 1254 "./kdtree.w"
/*51:*/
#line 1276 "./kdtree.w"

node->f.i.hi_child= 
E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

/*:51*/
#line 1254 "./kdtree.w"
}
else if(m<=h){/*52:*/
#line 1286 "./kdtree.w"

node->f.i.eq_child= 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


/*:52*/
#line 1255 "./kdtree.w"
/*51:*/
#line 1276 "./kdtree.w"

node->f.i.hi_child= 
E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

/*:51*/
#line 1255 "./kdtree.w"
/*50:*/
#line 1272 "./kdtree.w"

node->f.i.lo_child= 
E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

/*:50*/
#line 1255 "./kdtree.w"
}
else{/*51:*/
#line 1276 "./kdtree.w"

node->f.i.hi_child= 
E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

/*:51*/
#line 1256 "./kdtree.w"
/*52:*/
#line 1286 "./kdtree.w"

node->f.i.eq_child= 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


/*:52*/
#line 1256 "./kdtree.w"
/*50:*/
#line 1272 "./kdtree.w"

node->f.i.lo_child= 
E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

/*:50*/
#line 1256 "./kdtree.w"
}
}
}
#else
/*50:*/
#line 1272 "./kdtree.w"

node->f.i.lo_child= 
E2_build_helper(node,flat_dimens,level,lo,lo+b-a,lxl,lxh,lyl,lyh);

/*:50*/
#line 1260 "./kdtree.w"

/*52:*/
#line 1286 "./kdtree.w"

node->f.i.eq_child= 
E2_build_helper(node,flat_dimens|(cutdimen+1),level,lo+b-a,hi-(d-c),exl,exh,eyl,eyh);


/*:52*/
#line 1261 "./kdtree.w"

/*51:*/
#line 1276 "./kdtree.w"

node->f.i.hi_child= 
E2_build_helper(node,flat_dimens,level,hi-(d-c),hi,gxl,gxh,gyl,gyh);

/*:51*/
#line 1262 "./kdtree.w"

#endif

/*:49*/
#line 1028 "./kdtree.w"

}

/*:40*/
#line 1015 "./kdtree.w"

}

/*:39*/
#line 943 "./kdtree.w"

}
return node;
}

/*:33*//*66:*/
#line 1498 "./kdtree.w"

static void
E2_hide_all_helper(E2_node_t*p){
#if !defined(KD_NO_HIDDEN_BIT)
p->hidden= 1;
#endif
if(p->is_bucket)p->f.e.hi= p->f.e.lo;
else{
#if !defined(KD_NO_HIDDEN_BIT)
if(!p->f.i.lo_child->hidden)E2_hide_all_helper(p->f.i.lo_child);
if(!p->f.i.eq_child->hidden)E2_hide_all_helper(p->f.i.eq_child);
if(!p->f.i.hi_child->hidden)E2_hide_all_helper(p->f.i.hi_child);
#else
E2_hide_all_helper(p->f.i.lo_child);
E2_hide_all_helper(p->f.i.eq_child);
E2_hide_all_helper(p->f.i.hi_child);
#endif
}
}

/*:66*//*68:*/
#line 1533 "./kdtree.w"

static void
E2_unhide_all_helper(E2_node_t*p){
if(p->is_bucket){
p->f.e.hi= p->f.e.hi_all;
#if !defined(KD_NO_HIDDEN_BIT)
p->hidden= p->f.e.lo>=p->f.e.hi;
#endif
}else{
#if !defined(KD_NO_HIDDEN_BIT)
p->hidden= 0;
#endif
E2_unhide_all_helper(p->f.i.lo_child);
E2_unhide_all_helper(p->f.i.eq_child);
E2_unhide_all_helper(p->f.i.hi_child);
}
}

/*:68*//*72:*/
#line 1622 "./kdtree.w"

static void
E2_rnn(E2_node_t*p){
if(p->is_bucket){
/*73:*/
#line 1635 "./kdtree.w"

{int i,hi= p->f.e.hi;
for(i= p->f.e.lo;i<hi;i++){
int pi= perm[i];
/*74:*/
#line 1674 "./kdtree.w"

{
const double
diff_x= E2_nn_seed_x-coord[pi].x[0],
diff_y= E2_nn_seed_y-coord[pi].x[1];
const int qmask[3][3]= {{0x02,0x02,0x10},{0x04,0x01,0x10},{0x04,0x08,0x08}};
if(quadrant_mask&qmask[my_sgn(diff_x)][my_sgn(diff_y)]){

const double dist_sq= diff_x*diff_x+diff_y*diff_y;
/*96:*/
#line 2151 "./kdtree.w"

#if KD_ALLOW_VERBOSE
if(verbose>=2000){
printf("  city %5d (%7.0f,%7.0f) is dist %10.3f\n",
pi,coord[pi].x[0],coord[pi].x[1],sqrt(dist_sq));
}
#endif


/*:96*/
#line 1683 "./kdtree.w"

if(dist_sq<E2_nn_dist_sq){
/*97:*/
#line 2161 "./kdtree.w"

#if KD_ALLOW_VERBOSE
if(verbose>=1000){
printf("    new champion\n");
}
#endif

/*:97*/
#line 1685 "./kdtree.w"

E2_nn_dist= sqrt(dist_sq);
E2_nn_dist_sq= dist_sq;
E2_nn_incumbent= pi;
}
}
}

/*:74*/
#line 1639 "./kdtree.w"

}
}


/*:73*/
#line 1626 "./kdtree.w"

}else{
/*79:*/
#line 1807 "./kdtree.w"

#if !defined(KD_NO_HIDDEN_BIT) && !defined(KD_NO_HIDDEN_RNN_TEST)
#define recurse_if_not_hidden(P) ((P)->hidden || (E2_rnn(P),42))
#else
#define recurse_if_not_hidden(P) (E2_rnn(P),42)
#endif
{
const int cutdimen= p->f.i.cutdimen;
const double seed_coord= cutdimen==0?E2_nn_seed_x:E2_nn_seed_y,
diff= seed_coord-p->f.i.cutvalue;
if(diff<0){
recurse_if_not_hidden(p->f.i.lo_child);
if(E2_nn_dist>=-diff&&((cutdimen?0x12:0x06)&quadrant_mask)){
recurse_if_not_hidden(p->f.i.eq_child);
recurse_if_not_hidden(p->f.i.hi_child);
}
}else if(diff>0){
recurse_if_not_hidden(p->f.i.hi_child);
if(E2_nn_dist>=diff&&((cutdimen?0x0c:0x18)&quadrant_mask)){
recurse_if_not_hidden(p->f.i.eq_child);
recurse_if_not_hidden(p->f.i.lo_child);
}
}else{
recurse_if_not_hidden(p->f.i.eq_child);
recurse_if_not_hidden(p->f.i.lo_child);
recurse_if_not_hidden(p->f.i.hi_child);
}
}

/*:79*/
#line 1628 "./kdtree.w"

}
}


/*:72*/
#line 339 "./kdtree.w"

/*6:*/
#line 438 "./kdtree.w"

int
E2_supports(tsp_instance_t*tsp)
{
switch(tsp->edge_weight_type){
case EUC_2D:
case CEIL_2D:
return 1;
default:
return 0;
}
}


/*:6*//*23:*/
#line 776 "./kdtree.w"

void
E2_create(tsp_instance_t*tsp)
{
errorif(!E2_supports(tsp),"2-d trees may not be used for this instance");
/*24:*/
#line 801 "./kdtree.w"

node_pool= pool_create(sizeof(E2_node_t),500);
box_pool= pool_create(sizeof(E2_box_t),500);

/*:24*//*26:*/
#line 816 "./kdtree.w"

n= tsp->n;
perm= new_arr_of(int,n);
{int i;for(i= 0;i<n;i++)perm[i]= i;}

/*:26*//*37:*/
#line 979 "./kdtree.w"

E2_point_to_bucket= new_arr_of(E2_node_t*,n);

/*:37*/
#line 781 "./kdtree.w"

/*31:*/
#line 882 "./kdtree.w"

coord= tsp->coord;
errorif(n<=0,"Need at least one point; instance has %d points",n);
E2_root= E2_build_helper(NULL,0,0,0,n,
tsp->xmin,tsp->xmax,tsp->ymin,tsp->ymax);

/*:31*//*81:*/
#line 1903 "./kdtree.w"

{double xrange= tsp->xmax-tsp->xmin,yrange= tsp->ymax-tsp->ymin;
E2_strict_upper_bound= 2.0*(xrange*xrange+yrange*yrange)+1.0;
}

/*:81*/
#line 782 "./kdtree.w"

}

/*:23*//*29:*/
#line 833 "./kdtree.w"

void
E2_destroy(void){
pool_destroy(node_pool);
pool_destroy(box_pool);
box_pool= node_pool= NULL;
free_mem(perm);
/*38:*/
#line 983 "./kdtree.w"

free_mem(E2_point_to_bucket);

/*:38*/
#line 840 "./kdtree.w"

}

/*:29*//*56:*/
#line 1315 "./kdtree.w"

void
E2_hide(int c){
int ci;
E2_node_t*node;
errorif(c<0||c>=n,"Invalid city %d to hide",c);
node= E2_point_to_bucket[c];
/*57:*/
#line 1350 "./kdtree.w"

{int hi_all= node->f.e.hi_all;
for(ci= node->f.e.lo;ci<hi_all;ci++){
if(perm[ci]==c)break;
}
errorif(ci==hi_all,"Point %d not found in its bucket",c);
}

/*:57*/
#line 1322 "./kdtree.w"

/*58:*/
#line 1370 "./kdtree.w"

{int t,hi= node->f.e.hi;
if(ci<hi){
hi= --node->f.e.hi;
t= perm[ci];perm[ci]= perm[hi];perm[hi]= t;
}else{
fprintf(stderr,"Hiding hidden city %d at perm[%d]\n",c,ci);
}
}

/*:58*/
#line 1323 "./kdtree.w"

/*60:*/
#line 1399 "./kdtree.w"

#if !defined(KD_NO_HIDDEN_BIT)
if(node->f.e.lo==node->f.e.hi&&!node->hidden){
do{
node->hidden= 1;

node= node->parent;
}while(node
&&!node->hidden
&&node->f.i.lo_child->hidden
&&node->f.i.eq_child->hidden
&&node->f.i.hi_child->hidden);
}
#endif

/*:60*/
#line 1324 "./kdtree.w"

}


/*:56*//*61:*/
#line 1420 "./kdtree.w"

void
E2_unhide(int c){
int ci;
E2_node_t*node= E2_point_to_bucket[c];
/*57:*/
#line 1350 "./kdtree.w"

{int hi_all= node->f.e.hi_all;
for(ci= node->f.e.lo;ci<hi_all;ci++){
if(perm[ci]==c)break;
}
errorif(ci==hi_all,"Point %d not found in its bucket",c);
}

/*:57*/
#line 1425 "./kdtree.w"

/*62:*/
#line 1436 "./kdtree.w"

{int t,hi= node->f.e.hi;
if(ci>=hi){
t= perm[ci];perm[ci]= perm[hi];perm[hi]= t;
node->f.e.hi++;
}else{
fprintf(stderr,"Unhiding unhidden city %d at perm[%d]\n",c,ci);
}
}




/*:62*/
#line 1426 "./kdtree.w"

/*63:*/
#line 1454 "./kdtree.w"

#if !defined(KD_NO_HIDDEN_BIT)
while(node&&node->hidden){
node->hidden= 0;
node= node->parent;
}
#endif

/*:63*/
#line 1427 "./kdtree.w"

}


/*:61*//*65:*/
#line 1471 "./kdtree.w"

void
E2_hide_all(void){
#if !defined(KD_NO_HIDDEN_BIT)
if(E2_root&&!E2_root->hidden)E2_hide_all_helper(E2_root);
#else
if(E2_root)E2_hide_all_helper(E2_root);
#endif
}

/*:65*//*67:*/
#line 1523 "./kdtree.w"

void
E2_unhide_all(void){
if(E2_root)E2_unhide_all_helper(E2_root);
}

/*:67*//*80:*/
#line 1864 "./kdtree.w"

int E2_nn(int c){return E2_nn_quadrant(c,0x1f);}

int
E2_nn_quadrant(int c,const int mask)
{
E2_node_t*node= E2_point_to_bucket[c];
quadrant_mask= mask;
E2_nn_seed= c;
E2_nn_seed_x= coord[c].x[0];
E2_nn_seed_y= coord[c].x[1];
E2_nn_incumbent= -1;
E2_nn_dist= E2_nn_dist_sq= E2_strict_upper_bound;
/*83:*/
#line 1915 "./kdtree.w"

{
int i,hi= node->f.e.hi;
for(i= node->f.e.lo;i<hi;i++){
int pi= perm[i];
if(pi!=E2_nn_seed){
/*74:*/
#line 1674 "./kdtree.w"

{
const double
diff_x= E2_nn_seed_x-coord[pi].x[0],
diff_y= E2_nn_seed_y-coord[pi].x[1];
const int qmask[3][3]= {{0x02,0x02,0x10},{0x04,0x01,0x10},{0x04,0x08,0x08}};
if(quadrant_mask&qmask[my_sgn(diff_x)][my_sgn(diff_y)]){

const double dist_sq= diff_x*diff_x+diff_y*diff_y;
/*96:*/
#line 2151 "./kdtree.w"

#if KD_ALLOW_VERBOSE
if(verbose>=2000){
printf("  city %5d (%7.0f,%7.0f) is dist %10.3f\n",
pi,coord[pi].x[0],coord[pi].x[1],sqrt(dist_sq));
}
#endif


/*:96*/
#line 1683 "./kdtree.w"

if(dist_sq<E2_nn_dist_sq){
/*97:*/
#line 2161 "./kdtree.w"

#if KD_ALLOW_VERBOSE
if(verbose>=1000){
printf("    new champion\n");
}
#endif

/*:97*/
#line 1685 "./kdtree.w"

E2_nn_dist= sqrt(dist_sq);
E2_nn_dist_sq= dist_sq;
E2_nn_incumbent= pi;
}
}
}

/*:74*/
#line 1921 "./kdtree.w"

}
}
}


/*:83*/
#line 1877 "./kdtree.w"

do{
/*84:*/
#line 1939 "./kdtree.w"

{E2_box_t*b= node->bbox;
if(b
&&(b->xmin<=E2_nn_seed_x-E2_nn_dist)
&&(b->xmax>=E2_nn_seed_x+E2_nn_dist)
&&(b->ymin<=E2_nn_seed_y-E2_nn_dist)
&&(b->ymax>=E2_nn_seed_y+E2_nn_dist)){
/*98:*/
#line 2169 "./kdtree.w"

#if KD_ALLOW_VERBOSE
if(verbose>=500){
printf("     rnn break: seed=(%0.0f,%0.0f) dist=%f\n",
E2_nn_seed_x,E2_nn_seed_y,E2_nn_dist);
printf("     seedbb=(%0.0f,%0.0f,%0.0f,%0.0f) bb=(%0.0f,%0.0f,%0.0f,%0.0f)\n",
E2_nn_seed_x-E2_nn_dist,
E2_nn_seed_y-E2_nn_dist,
E2_nn_seed_x+E2_nn_dist,
E2_nn_seed_y+E2_nn_dist,
b->xmin,
b->ymin,
b->xmax,
b->ymax);
}
#endif


/*:98*/
#line 1946 "./kdtree.w"

break;
}
}

/*:84*/
#line 1879 "./kdtree.w"

/*85:*/
#line 1959 "./kdtree.w"


#if !defined(KD_NO_HIDDEN_BIT)
#define recurse_if_not_last_or_hidden(P) ((P)==last||(E2_rnn(P),42))
#else
#define recurse_if_not_last_or_hidden(P) ((P)==last||(P)->hidden||(E2_rnn(P),42))
#endif

{E2_node_t*last;
for(last= node,node= node->parent;node;last= node,node= node->parent){
E2_node_t*l= node->f.i.lo_child,*e= node->f.i.eq_child,*h= node->f.i.hi_child;
if((node->f.i.cutdimen==0&&E2_nn_seed_x<node->f.i.cutvalue)
||(node->f.i.cutdimen==1&&E2_nn_seed_y<node->f.i.cutvalue)){
recurse_if_not_last_or_hidden(l);
recurse_if_not_last_or_hidden(e);
recurse_if_not_last_or_hidden(h);
}else{
recurse_if_not_last_or_hidden(h);
recurse_if_not_last_or_hidden(e);
recurse_if_not_last_or_hidden(l);
}
/*84:*/
#line 1939 "./kdtree.w"

{E2_box_t*b= node->bbox;
if(b
&&(b->xmin<=E2_nn_seed_x-E2_nn_dist)
&&(b->xmax>=E2_nn_seed_x+E2_nn_dist)
&&(b->ymin<=E2_nn_seed_y-E2_nn_dist)
&&(b->ymax>=E2_nn_seed_y+E2_nn_dist)){
/*98:*/
#line 2169 "./kdtree.w"

#if KD_ALLOW_VERBOSE
if(verbose>=500){
printf("     rnn break: seed=(%0.0f,%0.0f) dist=%f\n",
E2_nn_seed_x,E2_nn_seed_y,E2_nn_dist);
printf("     seedbb=(%0.0f,%0.0f,%0.0f,%0.0f) bb=(%0.0f,%0.0f,%0.0f,%0.0f)\n",
E2_nn_seed_x-E2_nn_dist,
E2_nn_seed_y-E2_nn_dist,
E2_nn_seed_x+E2_nn_dist,
E2_nn_seed_y+E2_nn_dist,
b->xmin,
b->ymin,
b->xmax,
b->ymax);
}
#endif


/*:98*/
#line 1946 "./kdtree.w"

break;
}
}

/*:84*/
#line 1980 "./kdtree.w"

}
}


/*:85*/
#line 1880 "./kdtree.w"

}while(0);
return E2_nn_incumbent;
}


/*:80*//*88:*/
#line 2013 "./kdtree.w"

void
E2_frnn(int c,double rad,void(*proc)(int j)){
errorif(1,"Fixed radius nearest neighbour not implemented");
}

void E2_set_radius(int i,double r){
errorif(1,"Ball searching not implemented");
}

void E2_ball_search(int i,void(*proc)(int j)){
errorif(1,"Ball searching not implemented");
}


/*:88*//*91:*/
#line 2061 "./kdtree.w"

extern tsp_instance_t*tsp_instance;

static void
E2_postscript_show_helper(FILE*ps_out,int level,E2_node_t*node,
double xmin,double xmax,double ymin,double ymax){
if(!node->is_bucket){
double cv= node->f.i.cutvalue;
fprintf(ps_out,"%%cutdimen == %d\n",node->f.i.cutdimen);
switch(node->f.i.cutdimen){
case 0:
fprintf(ps_out,"newpath %f x %f y moveto %f x %f y lineto stroke\n",
cv,ymin,cv,ymax);
/*93:*/
#line 2121 "./kdtree.w"

verb(1000){int i;for(i= 0;i<level;i++)printf(" ");}

/*:93*/
#line 2074 "./kdtree.w"
verb(1000)printf("= in x = %f\n",cv);
E2_postscript_show_helper(ps_out,level+1,node->f.i.eq_child,cv,cv,ymin,ymax);
/*93:*/
#line 2121 "./kdtree.w"

verb(1000){int i;for(i= 0;i<level;i++)printf(" ");}

/*:93*/
#line 2076 "./kdtree.w"
verb(1000)printf("< in x < %f\n",cv);
E2_postscript_show_helper(ps_out,level+1,node->f.i.lo_child,xmin,cv,ymin,ymax);
/*93:*/
#line 2121 "./kdtree.w"

verb(1000){int i;for(i= 0;i<level;i++)printf(" ");}

/*:93*/
#line 2078 "./kdtree.w"
verb(1000)printf("> in x > %f\n",cv);
E2_postscript_show_helper(ps_out,level+1,node->f.i.hi_child,cv,xmax,ymin,ymax);
break;
case 1:
fprintf(ps_out,"newpath %f x %f y moveto %f x %f y lineto stroke\n",
xmin,cv,xmax,cv);
/*93:*/
#line 2121 "./kdtree.w"

verb(1000){int i;for(i= 0;i<level;i++)printf(" ");}

/*:93*/
#line 2084 "./kdtree.w"
verb(1000)printf("= in y = %f\n",cv);
E2_postscript_show_helper(ps_out,level+1,node->f.i.eq_child,xmin,xmax,cv,cv);
/*93:*/
#line 2121 "./kdtree.w"

verb(1000){int i;for(i= 0;i<level;i++)printf(" ");}

/*:93*/
#line 2086 "./kdtree.w"
verb(1000)printf("< in y < %f\n",cv);
E2_postscript_show_helper(ps_out,level+1,node->f.i.lo_child,xmin,xmax,ymin,cv);
/*93:*/
#line 2121 "./kdtree.w"

verb(1000){int i;for(i= 0;i<level;i++)printf(" ");}

/*:93*/
#line 2088 "./kdtree.w"
verb(1000)printf("> in y > %f\n",cv);
E2_postscript_show_helper(ps_out,level+1,node->f.i.hi_child,xmin,xmax,cv,ymax);
break;
}
}else{
int i;
/*93:*/
#line 2121 "./kdtree.w"

verb(1000){int i;for(i= 0;i<level;i++)printf(" ");}

/*:93*/
#line 2094 "./kdtree.w"

for(i= node->f.e.lo;i<node->f.e.hi_all;i++){
verb(1000)printf("%d ",perm[i]);
}
verb(1000)printf("\n");
}
}

void
E2_postscript_show(FILE*ps_out){
#if defined(KD_SHOW_KDTREE)
fprintf(ps_out,"gsave 0 setlinewidth\n");
E2_postscript_show_helper(ps_out,0,E2_root,
tsp_instance->xmin,tsp_instance->xmax,tsp_instance->ymin,tsp_instance->ymax);
fprintf(ps_out,"grestore\n");
fflush(ps_out);
fprintf(stderr,"Printed stuff to ps_out\n");
#else
return;
#endif
}

/*:91*/
#line 340 "./kdtree.w"

const char*kdtree_rcs_id= "$Id: kdtree.w,v 1.159 1998/07/16 21:58:55 neto Exp neto $";

/*:1*/
