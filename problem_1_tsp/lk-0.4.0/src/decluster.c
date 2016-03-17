#define child city
#define NO_CHILD (-1)  \
 \

#define NO_PARENT (-2)  \

#define lo_mask(X) (pow_2[(X) ]-1) 
#define hi_mask(X) (~lo_mask(i) )  \

#define min(A,B) ((A) <(B) ?(A) :(B) ) 
#define max(A,B) ((A) >(B) ?(A) :(B) )  \

/*9:*/
#line 521 "./decluster.w"

#include <config.h>
#include "lkconfig.h"
/*12:*/
#line 611 "./decluster.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*:12*/
#line 524 "./decluster.w"

/*15:*/
#line 638 "./decluster.w"

#include "error.h"
#include "memory.h"
#include "length.h"
#include "read.h"


/*:15*/
#line 525 "./decluster.w"

/*14:*/
#line 627 "./decluster.w"

#include "decluster.h"


/*:14*//*27:*/
#line 934 "./decluster.w"

#include "pq.h"
#include "kdtree.h"

/*:27*//*40:*/
#line 1111 "./decluster.w"

#include "lk.h"

/*:40*/
#line 526 "./decluster.w"


/*37:*/
#line 1071 "./decluster.w"

int decluster_discard_topology_tree= 1;

/*:37*/
#line 528 "./decluster.w"

/*42:*/
#line 1151 "./decluster.w"

#if SIZEOF_INT==8
# define copy_1_down(X) \
 (((X) |=  (X)>>1), \
  ((X) |=  (X)>>2), \
  ((X) |=  (X)>>4), \
  ((X) |=  (X)>>8), \
  ((X) |=  (X)>>16), \
  ((X) |=  (X)>>32) )
#else 
# define copy_1_down(X) \
 (((X) |=  (X)>>1), \
  ((X) |=  (X)>>2), \
  ((X) |=  (X)>>4), \
  ((X) |=  (X)>>8), \
  ((X) |=  (X)>>16) )
#endif


/*:42*//*76:*/
#line 1926 "./decluster.w"

#if DECLUSTER_DEBUG
#define print_tree(A,B) decluster_print_tree(stdout,A,B)
#else
#define print_tree(A,B)
#endif


/*:76*/
#line 529 "./decluster.w"

/*49:*/
#line 1399 "./decluster.w"

typedef struct{
int level,inlabel,ascendant;
length_t cost;
}digest_t;

/*:49*/
#line 530 "./decluster.w"

/*17:*/
#line 663 "./decluster.w"

static int n;

/*:17*//*35:*/
#line 1032 "./decluster.w"

static decluster_tree_t*T_prime= NULL;

/*:35*//*43:*/
#line 1173 "./decluster.w"


static const int pow_2[]= {
0x1,
0x2,
0x4,
0x8,
0x10,
0x20,
0x40,
0x80,
0x100,
0x200,
0x400,
0x800,
0x1000,
0x2000,
0x4000,
0x8000,
0x10000,
0x20000,
0x40000,
0x80000,
0x100000,
0x200000,
0x400000,
0x800000,
0x1000000,
0x2000000,
0x4000000,
0x8000000,
0x10000000,
0x20000000,
0x40000000,
0x80000000
#if SIZEOF_INT==8
,
0x100000000,
0x200000000,
0x400000000,
0x800000000,
0x1000000000,
0x2000000000,
0x4000000000,
0x8000000000,
0x10000000000,
0x20000000000,
0x40000000000,
0x80000000000,
0x100000000000,
0x200000000000,
0x400000000000,
0x800000000000,
0x1000000000000,
0x2000000000000,
0x4000000000000,
0x8000000000000,
0x10000000000000,
0x20000000000000,
0x40000000000000,
0x80000000000000,
0x100000000000000,
0x200000000000000,
0x400000000000000,
0x800000000000000,
0x1000000000000000,
0x2000000000000000,
0x4000000000000000,
0x8000000000000000
#endif
};


/*:43*//*44:*/
#line 1248 "./decluster.w"

static const int floor_log_2_small[16]= {
0,
0,
1,1,
2,2,2,2,
3,3,3,3,3,3,3,3};


/*:44*//*50:*/
#line 1406 "./decluster.w"

static digest_t*digest;

/*:50*//*62:*/
#line 1640 "./decluster.w"

int*parent_of_head;

/*:62*//*92:*/
#line 2233 "./decluster.w"

#if DECLUSTER_DEBUG
static char pp[]= "          ";
#endif

/*:92*/
#line 531 "./decluster.w"

/*29:*/
#line 963 "./decluster.w"

/*28:*/
#line 948 "./decluster.w"

static int
edge_cmp(const void*a,const void*b)
{
length_t len_diff= ((const decluster_edge_t*)a)->cost
-((const decluster_edge_t*)b)->cost;
return len_diff<0?-1:
(len_diff>0?
1:
((int)(((const decluster_edge_t*)a)-((const decluster_edge_t*)b))));
}

/*:28*/
#line 964 "./decluster.w"


/*:29*//*45:*/
#line 1296 "./decluster.w"

#if SIZEOF_INT>8
#error "The bit twiddling handles integers of at most 64 bits."
#endif
static inline int
floor_log_2(unsigned int x)
{
int ans= 0;

#if SIZEOF_UNSIGNED_INT==8
if(x&(0xffffffff<<32))ans+= 32,x>>= 32;
#endif
if(x&(0xffff<<16))ans+= 16,x>>= 16;
if(x&(0xff<<8))ans+= 8,x>>= 8;
if(x&(0xf<<4))ans+= 4,x>>= 4;
ans+= floor_log_2_small[x];
return ans;
}


/*:45*//*65:*/
#line 1655 "./decluster.w"

static inline int
decluster_lca(int x,int y)
{
const digest_t xd= digest[x],yd= digest[y];
if(xd.inlabel==yd.inlabel)return(xd.level<=yd.level)?x:y;
else{
const int xil= xd.inlabel,yil= yd.inlabel;
int b,inlabel_z,common,jmask,xpp,ypp;
/*66:*/
#line 1718 "./decluster.w"

{
const unsigned int xfuzz= xil^(xil-1),yfuzz= yil^(yil-1);
const unsigned int lomask= max(xfuzz,yfuzz)>>1;
int hi_diff= (xil^yil)&(~lomask);
if(hi_diff){
int t= hi_diff;
copy_1_down(t);


b= (~t)&xil;
b|= t^(t>>1);
}else{
b= (xfuzz>=yfuzz)?xil:yil;
}
/*93:*/
#line 2239 "./decluster.w"

#if DECLUSTER_DEBUG
if(verbose>=2000){
printf("\n%s x=%d {lev=%d, inl=%d, asc=%d}\n",pp,
x,xd.level,xd.inlabel,xd.ascendant);
printf("%s y=%d {lev=%d, inl=%d, asc=%d}\n",pp,
y,yd.level,yd.inlabel,yd.ascendant);
printf("%s b=%d\n",pp,b);
}
#endif

/*:93*/
#line 1733 "./decluster.w"

}

/*:66*/
#line 1664 "./decluster.w"

/*67:*/
#line 1751 "./decluster.w"

{const int imask= (b^(b-1))>>1;
const int u= (common= xd.ascendant&yd.ascendant)&~imask;
jmask= (u^(u-1))>>1;

inlabel_z= (xd.inlabel&~jmask)|(jmask+1);
/*94:*/
#line 2251 "./decluster.w"

#if DECLUSTER_DEBUG
if(verbose>=2000){
printf("%s inlabel_z=%d, common=%d, jmask=%d\n",pp,inlabel_z,common,jmask);
}
#endif


/*:94*/
#line 1757 "./decluster.w"

}




/*:67*/
#line 1665 "./decluster.w"

/*68:*/
#line 1770 "./decluster.w"

if(xd.inlabel==inlabel_z)xpp= x;
else{
int inlabel_w_x;
int kmask= xd.ascendant&jmask;
copy_1_down(kmask);
inlabel_w_x= (~kmask)&xil;
inlabel_w_x|= kmask^(kmask>>1);
xpp= parent_of_head[inlabel_w_x];
/*95:*/
#line 2260 "./decluster.w"

#if DECLUSTER_DEBUG
if(verbose>=2000){
printf("%s inlabel_w_x=%d, xpp=%d\n",pp,inlabel_w_x,xpp);
}
#endif

/*:95*/
#line 1779 "./decluster.w"

}
if(yd.inlabel==inlabel_z)ypp= y;
else{
int inlabel_w_y;
int kmask= yd.ascendant&jmask;
copy_1_down(kmask);
inlabel_w_y= (~kmask)&yil;
inlabel_w_y|= kmask^(kmask>>1);
ypp= parent_of_head[inlabel_w_y];
/*96:*/
#line 2268 "./decluster.w"

#if DECLUSTER_DEBUG
if(verbose>=2000){
printf("%s inlabel_w_y=%d, ypp=%d\n",pp,inlabel_w_y,ypp);
}
#endif

/*:96*/
#line 1789 "./decluster.w"

}


/*:68*/
#line 1666 "./decluster.w"

return(digest[xpp].level<=digest[ypp].level)?xpp:ypp;
}
}


/*:65*/
#line 532 "./decluster.w"

/*16:*/
#line 651 "./decluster.w"

decluster_tree_t*
decluster_setup(int the_n)
{
decluster_tree_t*mst;
n= the_n;
/*20:*/
#line 695 "./decluster.w"

mst= new_of(decluster_tree_t);
mst->n= n-1;
mst->edge= new_arr_of(decluster_edge_t,n-1);


/*:20*/
#line 657 "./decluster.w"

/*32:*/
#line 1015 "./decluster.w"

/*31:*/
#line 1000 "./decluster.w"

if(T_prime==NULL||T_prime->n!=n+n-1){
int i;
/*33:*/
#line 1019 "./decluster.w"

if(T_prime){
const int n= T_prime->n;
free_mem(T_prime->edge);mem_deduct(n*sizeof(decluster_edge_t));
free_mem(T_prime);mem_deduct(sizeof(decluster_tree_t));
T_prime= NULL;
}

/*:33*/
#line 1003 "./decluster.w"

T_prime= new_of(decluster_tree_t);
T_prime->n= n+n-1;
T_prime->edge= new_arr_of(decluster_edge_t,n+n-1);
for(i= 0;i<n;i++){
T_prime->edge[i].child[0]= NO_CHILD;
T_prime->edge[i].child[1]= NO_CHILD;
T_prime->edge[i].cost= 0;
}
}

/*:31*/
#line 1016 "./decluster.w"


/*:32*//*51:*/
#line 1414 "./decluster.w"

digest= new_arr_of(digest_t,n+n-1);
{
int i;
for(i= 0;i<n;i++){
digest[i].cost= 0;
}
}

/*:51*//*63:*/
#line 1644 "./decluster.w"

parent_of_head= new_arr_of(int,n+n);

/*:63*/
#line 658 "./decluster.w"

return mst;
}

/*:16*//*18:*/
#line 667 "./decluster.w"

void
decluster_cleanup(void)
{
/*34:*/
#line 1028 "./decluster.w"

/*33:*/
#line 1019 "./decluster.w"

if(T_prime){
const int n= T_prime->n;
free_mem(T_prime->edge);mem_deduct(n*sizeof(decluster_edge_t));
free_mem(T_prime);mem_deduct(sizeof(decluster_tree_t));
T_prime= NULL;
}

/*:33*/
#line 1029 "./decluster.w"


/*:34*//*52:*/
#line 1424 "./decluster.w"

free_mem(digest);
mem_deduct((n+n-1)*sizeof(digest_t));

/*:52*//*64:*/
#line 1648 "./decluster.w"

free_mem(parent_of_head);mem_deduct((n+n)*sizeof(int));


/*:64*/
#line 671 "./decluster.w"

n= 0;
}

/*:18*//*21:*/
#line 703 "./decluster.w"

void
decluster_cleanup_tree(decluster_tree_t*T)
{
if(T){
size_t r= (T->n)*sizeof(decluster_edge_t)+sizeof(decluster_tree_t);
T->n= 0;
free_mem(T->edge);
free_mem(T);
mem_deduct(r);
}
}

/*:21*//*22:*/
#line 751 "./decluster.w"

length_t
decluster_mst(tsp_instance_t*tsp_instance,decluster_tree_t*T)
{
extern int verbose;
length_t total_len= 0;
errorif(T->n!=n-1,"decluster_mst: passed storage for a tree with %d"
" vertices instead of %d vertices",T->n,n-1);
if(E2_supports(tsp_instance)){
/*26:*/
#line 886 "./decluster.w"

{
decluster_edge_t*bridge= new_arr_of(decluster_edge_t,n);
pq_t*bridge_pq= pq_create_size(edge_cmp,n);
int next_edge;char*is_in_component= new_arr_of_zero(char,n);

errorif(bridge_pq==NULL,"Couldn't allocate a priority queue!");

E2_hide(0);
bridge[0].city[0]= 0;
bridge[0].city[1]= E2_nn(0);
bridge[0].cost= cost(0,bridge[0].city[1]);
is_in_component[0]= 1;
pq_insert(bridge_pq,&bridge[0]);

for(next_edge= 0;next_edge<n-1;next_edge++){
int in,out;
decluster_edge_t*short_bridge;
while(1){
short_bridge= pq_delete_min(bridge_pq);
in= short_bridge->city[0];

out= short_bridge->city[1];
if(!is_in_component[out])break;
bridge[in].city[1]= E2_nn(in);
bridge[in].cost= cost(in,bridge[in].city[1]);
pq_insert(bridge_pq,bridge+in);
}
T->edge[next_edge]= *short_bridge;
total_len+= short_bridge->cost;
E2_hide(out);
is_in_component[out]= 1;

bridge[in].city[1]= E2_nn(in);
bridge[in].cost= cost(in,bridge[in].city[1]);
pq_insert(bridge_pq,bridge+in);
bridge[out].city[0]= out;
bridge[out].city[1]= E2_nn(out);
bridge[out].cost= cost(out,bridge[out].city[1]);
pq_insert(bridge_pq,bridge+out);
}
pq_destroy(bridge_pq);
free_mem(is_in_component);mem_deduct(n*sizeof(char));
free_mem(bridge);mem_deduct(n*sizeof(decluster_edge_t));
E2_unhide_all();
}

/*:26*/
#line 760 "./decluster.w"

}else{
int*from= new_arr_of(int,n);
length_t*dist= new_arr_of(length_t,n);
total_len= 
decluster_mst_custom(T,from,dist,cost);
free_mem(from);mem_deduct(n*sizeof(int));
free_mem(dist);mem_deduct(n*sizeof(length_t));
}
return total_len;
}

/*:22*//*23:*/
#line 792 "./decluster.w"

length_t
decluster_mst_custom(
decluster_tree_t*T,int*from,length_t*dist,length_t(*cost)(int,int))
{
int i,next_edge,short_to,n;
length_t short_len,total_len= 0;
from[0]= -1;
errorif(T==NULL||T->n<0,"Bug!");
n= T->n+1;
for(i= 1,short_len= INFINITY,short_to= -1;i<n;i++){
from[i]= 0;
dist[i]= cost(0,i);
if(short_len>dist[i]){
short_len= dist[i];
short_to= i;
}
}
for(next_edge= 0;next_edge<n-1;next_edge++){
/*24:*/
#line 819 "./decluster.w"

if(verbose>=1000)printf("decluster_mst_plain: adding edge (%d,%d) "length_t_spec"\n",
from[short_to],short_to,length_t_pcast(short_len));
T->edge[next_edge].city[0]= short_to;
T->edge[next_edge].city[1]= from[short_to];
T->edge[next_edge].cost= short_len;
total_len+= short_len;
from[short_to]= -1;

/*:24*/
#line 811 "./decluster.w"

/*25:*/
#line 843 "./decluster.w"

{
const int new_inside_city= short_to;
short_len= INFINITY;
for(i= 1;i<n;i++){
length_t d;
if(from[i]==-1)continue;
d= cost(new_inside_city,i);
if(d<dist[i]){
dist[i]= d;
from[i]= new_inside_city;
}
if(dist[i]<short_len){
short_len= dist[i];
short_to= i;
}
}
}

/*:25*/
#line 812 "./decluster.w"

}
return total_len;
}


/*:23*//*36:*/
#line 1047 "./decluster.w"

void
decluster_preprocess(decluster_tree_t*T)
{
errorif(T->n!=n-1,"decluster_preprocess: MST size %d should be %d",T->n,n-1);
if(T_prime==NULL)/*31:*/
#line 1000 "./decluster.w"

if(T_prime==NULL||T_prime->n!=n+n-1){
int i;
/*33:*/
#line 1019 "./decluster.w"

if(T_prime){
const int n= T_prime->n;
free_mem(T_prime->edge);mem_deduct(n*sizeof(decluster_edge_t));
free_mem(T_prime);mem_deduct(sizeof(decluster_tree_t));
T_prime= NULL;
}

/*:33*/
#line 1003 "./decluster.w"

T_prime= new_of(decluster_tree_t);
T_prime->n= n+n-1;
T_prime->edge= new_arr_of(decluster_edge_t,n+n-1);
for(i= 0;i<n;i++){
T_prime->edge[i].child[0]= NO_CHILD;
T_prime->edge[i].child[1]= NO_CHILD;
T_prime->edge[i].cost= 0;
}
}

/*:31*/
#line 1052 "./decluster.w"

/*39:*/
#line 1096 "./decluster.w"

{int r,w,i,*component= new_arr_of(int,n+n);

for(i= 0;i<n;i++)component[i]= NO_PARENT;
sort(T->edge,(size_t)(n-1),sizeof(decluster_edge_t),edge_cmp);
print_tree(T,"T");
for(r= 0,w= n;r<n-1;r++,w++){
T_prime->edge[w]= T->edge[r];
/*41:*/
#line 1129 "./decluster.w"

{int i,here,parent;
component[w]= NO_PARENT;
for(i= 0;i<2;i++){
here= T_prime->edge[w].city[i];
while((parent= component[here])!=NO_PARENT){
component[here]= w;
here= parent;
}
component[here]= w;
T_prime->edge[w].child[i]= here;
}
}

/*:41*/
#line 1104 "./decluster.w"

}
free_mem(component);mem_deduct((n+n)*sizeof(int));
}

/*:39*/
#line 1053 "./decluster.w"

print_tree(T_prime,"T_prime");
/*53:*/
#line 1429 "./decluster.w"

{
int i;
for(i= n;i<n+n-1;i++)digest[i].cost= T_prime->edge[i].cost;
}

/*:53*/
#line 1055 "./decluster.w"

/*54:*/
#line 1442 "./decluster.w"

{int*queue= new_arr_of(int,n+n-1),r,w,i,ch;
digest[n+n-2].level= 0;
queue[0]= n+n-2;
for(r= 0,w= 1;r<w;r++){
const int here= queue[r],cur_level= digest[here].level+1;
for(i= 0;i<2;i++)if((ch= T_prime->edge[here].child[i])!=NO_CHILD){
digest[ch].level= cur_level;
queue[w++]= ch;
}
}
free_mem(queue);mem_deduct((n+n-1)*sizeof(int));
}


/*:54*/
#line 1056 "./decluster.w"

/*55:*/
#line 1465 "./decluster.w"

{
int*preorder= new_arr_of(int,n+n-1),*size= new_arr_of(int,n+n-1);
int preorder_number= 0;
#define DFS_INLABEL
/*56:*/
#line 1495 "./decluster.w"

{
int*in= new_arr_of(int,n+n-1),*cur_child= new_arr_of(int,n+n-1);
int top,here,next_child;

top= 0;
in[top]= n+n-2;
cur_child[top]= -1;

while(top>=0){
here= in[top];
switch(cur_child[top]){
case-1:
/*57:*/
#line 1530 "./decluster.w"

#if defined(DFS_INLABEL)
preorder[here]= ++preorder_number;
#endif

/*:57*//*60:*/
#line 1582 "./decluster.w"

#if defined(DFS_ASCENDANT)
if(top==0){
digest[here].ascendant= digest[here].inlabel;
}else{
const int p= in[top-1],ap= digest[p].ascendant,ip= digest[p].inlabel;
if(digest[here].inlabel==ip)digest[here].ascendant= ap;
else{
const int ih= digest[here].inlabel;
digest[here].ascendant= ap+((ih^(ih-1))&ih);
}
}
#endif

/*:60*/
#line 1508 "./decluster.w"

case 0:
next_child= T_prime->edge[here].child[++cur_child[top]];
if(next_child!=NO_CHILD){

in[++top]= next_child;
cur_child[top]= -1;
}
break;
default:
/*58:*/
#line 1556 "./decluster.w"

#if defined(DFS_INLABEL)
{const int child0= T_prime->edge[here].child[0],
child1= T_prime->edge[here].child[1];
size[here]= 1+(child0==NO_CHILD?0:size[child0])
+(child1==NO_CHILD?0:size[child1]);
}
{
const unsigned int last= preorder[here]+size[here]-1,
i= floor_log_2((preorder[here]-1)^last);
digest[here].inlabel= hi_mask(i)&last;
}
#endif

/*:58*/
#line 1518 "./decluster.w"


top--;
}
}
free_mem(in);free_mem(cur_child);
mem_deduct(2*(n+n-1)*sizeof(int));
}

/*:56*/
#line 1470 "./decluster.w"

#undef DFS_INLABEL

free_mem(preorder);free_mem(size);
mem_deduct(2*(n+n-1)*sizeof(int));
}


/*:55*/
#line 1057 "./decluster.w"

/*59:*/
#line 1573 "./decluster.w"

#define DFS_ASCENDANT
/*56:*/
#line 1495 "./decluster.w"

{
int*in= new_arr_of(int,n+n-1),*cur_child= new_arr_of(int,n+n-1);
int top,here,next_child;

top= 0;
in[top]= n+n-2;
cur_child[top]= -1;

while(top>=0){
here= in[top];
switch(cur_child[top]){
case-1:
/*57:*/
#line 1530 "./decluster.w"

#if defined(DFS_INLABEL)
preorder[here]= ++preorder_number;
#endif

/*:57*//*60:*/
#line 1582 "./decluster.w"

#if defined(DFS_ASCENDANT)
if(top==0){
digest[here].ascendant= digest[here].inlabel;
}else{
const int p= in[top-1],ap= digest[p].ascendant,ip= digest[p].inlabel;
if(digest[here].inlabel==ip)digest[here].ascendant= ap;
else{
const int ih= digest[here].inlabel;
digest[here].ascendant= ap+((ih^(ih-1))&ih);
}
}
#endif

/*:60*/
#line 1508 "./decluster.w"

case 0:
next_child= T_prime->edge[here].child[++cur_child[top]];
if(next_child!=NO_CHILD){

in[++top]= next_child;
cur_child[top]= -1;
}
break;
default:
/*58:*/
#line 1556 "./decluster.w"

#if defined(DFS_INLABEL)
{const int child0= T_prime->edge[here].child[0],
child1= T_prime->edge[here].child[1];
size[here]= 1+(child0==NO_CHILD?0:size[child0])
+(child1==NO_CHILD?0:size[child1]);
}
{
const unsigned int last= preorder[here]+size[here]-1,
i= floor_log_2((preorder[here]-1)^last);
digest[here].inlabel= hi_mask(i)&last;
}
#endif

/*:58*/
#line 1518 "./decluster.w"


top--;
}
}
free_mem(in);free_mem(cur_child);
mem_deduct(2*(n+n-1)*sizeof(int));
}

/*:56*/
#line 1575 "./decluster.w"

#undef DFS_ASCENDANT

/*:59*/
#line 1058 "./decluster.w"

/*61:*/
#line 1615 "./decluster.w"

{
int i,j,*head= new_arr_of(int,n+n),*parent= new_arr_of(int,n+n-1);
for(i= 0;i<n+n;i++)head[i]= -1;
for(i= 0;i<n+n-1;i++){
const int ii= digest[i].inlabel,hii= head[ii];
if(hii==-1||digest[i].level<digest[hii].level)head[ii]= i;
}
for(i= 0;i<n+n-1;i++)parent[i]= NO_PARENT,parent_of_head[i]= NO_PARENT;

for(i= 0;i<n+n-1;i++)
for(j= 0;j<2;j++){
const int child= T_prime->edge[i].child[j];
if(child!=NO_CHILD)parent[child]= i;
}
for(i= 0;i<n+n-1;i++)
parent_of_head[digest[i].inlabel]= parent[head[digest[i].inlabel]];
/*90:*/
#line 2211 "./decluster.w"

#if DECLUSTER_DEBUG
{
int i;
printf("parent list:\n");
for(i= 0;i<n+n-1;i++)
printf(" %5d   %12d\n",i,parent[i]);
}
#endif

/*:90*/
#line 1632 "./decluster.w"

/*91:*/
#line 2222 "./decluster.w"

#if DECLUSTER_DEBUG
{
int i;
printf("head list:\n");
for(i= 1;i<n+n;i++)
printf(" %5d   %12d\n",i,head[i]);
}
#endif

/*:91*/
#line 1633 "./decluster.w"


free_mem(head);mem_deduct((n+n)*sizeof(int));
free_mem(parent);mem_deduct((n+n-1)*sizeof(int));
}

/*:61*/
#line 1059 "./decluster.w"

/*89:*/
#line 2192 "./decluster.w"

#if DECLUSTER_DEBUG
{
int i;
printf("digest:   %12s %12s %12s %s\n",
"level","inlabel","ascendant","cost");
for(i= 0;i<n+n-1;i++){
printf("%9d %12d %12d %12d "length_t_spec"\n",
i,digest[i].level,digest[i].inlabel,digest[i].ascendant,
length_t_pcast(digest[i].cost));
}
printf("parent_of_head: (indexed by inlabel number)\n");
for(i= 1;i<n+n;i++){
printf(" %5d   %12d\n",i,parent_of_head[i]);
}
}
#endif

/*:89*/
#line 1060 "./decluster.w"

if(decluster_discard_topology_tree){
/*33:*/
#line 1019 "./decluster.w"

if(T_prime){
const int n= T_prime->n;
free_mem(T_prime->edge);mem_deduct(n*sizeof(decluster_edge_t));
free_mem(T_prime);mem_deduct(sizeof(decluster_tree_t));
T_prime= NULL;
}

/*:33*/
#line 1062 "./decluster.w"

}
}

/*:36*//*69:*/
#line 1798 "./decluster.w"

length_t
decluster_d(int u,int v)
{
return digest[decluster_lca(u,v)].cost;
}

/*:69*//*71:*/
#line 1813 "./decluster.w"

decluster_tree_t*
decluster_topology_tree(void)
{
return T_prime;
}

/*:71*//*72:*/
#line 1821 "./decluster.w"

void
decluster_print_tree(FILE*out,decluster_tree_t const*t,const char*name)
{
if(t){
int n= t->n,i;
const char*print_name= name?name:"";
errorif(t==NULL,"decluster_print_tree: given a NULL tree\n");
errorif(n<0,"decluster_print_tree: tree %s size %d < 0\n",print_name,n);
fprintf(out,"%s->n==%d\n",print_name,t->n);
for(i= 0;i<n;i++){
fprintf(out," %d (%d,%d) "length_t_spec"\n",
i,
t->edge[i].city[0],t->edge[i].city[1],
length_t_pcast(t->edge[i].cost));
}
}else{
fprintf(out,"Tree %s is NULL\n",name);
fprintf(out,"For more data, make sure variable decluster_discard_topology_tree is zero)\n");
}
}

/*:72*/
#line 533 "./decluster.w"

const char*decluster_rcs_id= "$Id: decluster.w,v 1.59 1998/07/16 21:58:55 neto Exp neto $";


/*:9*/
