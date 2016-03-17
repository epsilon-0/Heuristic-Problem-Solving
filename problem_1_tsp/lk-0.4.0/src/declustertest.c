/*73:*/
#line 1847 "./decluster.w"

#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "length.h"
#include "memory.h"
#include "resource.h"
#include "dsort.h"
#include "read.h"
#include "kdtree.h"
#include "decluster.h"

tsp_instance_t*tsp_instance;
void(*sort)(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));
int verbose= 100;
int noround= 0;

/*77:*/
#line 1935 "./decluster.w"

#if DECLUSTER_DEBUG
#define print_tree decluster_print_tree
#else
#define print_tree(A,B)
#endif

/*:77*/
#line 1866 "./decluster.w"

/*75:*/
#line 1914 "./decluster.w"

static decluster_edge_t simple_mat_MST_edges[]= {
{{0,1},10},
{{2,3},11},
{{3,4},20},
{{4,5},30},
{{1,2},50}
};
static int simple_mat_n= 1+sizeof(simple_mat_MST_edges)/sizeof(decluster_edge_t);


/*:75*//*81:*/
#line 2053 "./decluster.w"

static length_t simple_mat_lca_len[6][6]= {
{0,10,50,50,50,50},
{10,0,50,50,50,50},
{50,50,0,11,20,30},
{50,50,11,0,20,30},
{50,50,20,20,0,30},
{50,50,30,30,30,0}
};


/*:81*//*85:*/
#line 2148 "./decluster.w"

static coord_2d euc_coord[]= 
{{{0,0}},{{0,10}},{{0,85}},{{0,96}},{{0,116}},{{0,146}}};
static decluster_edge_t euc_MST_edges[]= {
{{0,1},10},
{{2,3},11},
{{3,4},20},
{{4,5},30},
{{1,2},75}
};
static int euc_n= 1+sizeof(euc_MST_edges)/sizeof(decluster_edge_t);

/*:85*//*86:*/
#line 2161 "./decluster.w"

static length_t euc_lca_len[6][6]= {
{0,10,75,75,75,75},
{10,0,75,75,75,75},
{75,75,0,11,20,30},
{75,75,11,0,20,30},
{75,75,20,20,0,30},
{75,75,30,30,30,0}
};


/*:86*/
#line 1867 "./decluster.w"

/*30:*/
#line 967 "./decluster.w"

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
#line 968 "./decluster.w"




/*:30*//*74:*/
#line 1890 "./decluster.w"

static length_t simple_mat_cost(const int i,const int j);
static length_t
simple_mat_cost(const int i,const int j)
{
extern int verbose;
static length_t cost_matrix[6][6]= {
{0,10,60,71,91,121},
{10,0,50,61,81,111},
{60,50,0,11,31,61},
{71,61,11,0,20,50},
{91,81,31,20,0,30},
{121,111,61,50,30,0}
};
errorif(i<0||i>5,"simple_mat_cost: i==%d out of range 0..6\n",i);
errorif(j<0||j>5,"simple_mat_cost: j==%d out of range 0..6\n",j);
if(verbose>=1000)printf("   simple_mat_cost(%d,%d)="length_t_spec"\n",
i,j,cost_matrix[i][j]);
return cost_matrix[i][j];
}

/*:74*//*78:*/
#line 1947 "./decluster.w"

#define  swap(type,A,B) {type tmp; tmp= (A); (A)= (B);(B)= tmp;}



static void
canonicalize(decluster_tree_t*t)
{
int n= t->n,i;
extern int verbose;
errorif(t==NULL,"canonicalize: given a NULL tree\n");
errorif(n<0,"canonicalize: tree size %d < 0\n",n);
if(verbose>=1000)print_tree(t,"pre-canon");
dsort(t->edge,(size_t)n,sizeof(decluster_edge_t),edge_cmp);
for(i= 0;i<n;i++){
if(t->edge[i].city[0]>t->edge[i].city[1])
swap(int,t->edge[i].city[0],t->edge[i].city[1]);
}
if(verbose>=1000)print_tree(t,"post-canon");
}



/*:78*//*79:*/
#line 1971 "./decluster.w"

#define max(A,B) ((A)>(B)?(A):(B))
static void
compare_trees(decluster_tree_t*a,decluster_tree_t*b)
{
int i,n,ok= 1;
if(verbose>=200)printf("a->n==%d\n",a->n);
if(verbose>=200)printf("b->n==%d\n",b->n);
if(a->n!=b->n)ok= 0,printf("compare_trees: trees differ in size %d vs. %d\n",
a->n,b->n);
n= a->n;
if(ok)
for(i= 0;i<n;i++){
decluster_edge_t ea= a->edge[i],eb= b->edge[i];
if(ea.city[0]!=eb.city[0])ok= 0,printf("compare_trees: "
"a->edge[%d].city[0]==%d != b->edge[%d].city[0]==%d\n",
i,ea.city[0],i,eb.city[0]);
if(ea.city[1]!=eb.city[1])ok= 0,printf("compare_trees: "
"a->edge[%d].city[1]==%d != b->edge[%d].city[1]==%d\n",
i,ea.city[1],i,eb.city[1]);
if(ea.cost!=eb.cost)ok= 0,printf("compare_trees: "
"a->edge[%d].cost=="length_t_spec" != b->edge[%d].cost=="length_t_spec"\n",
i,length_t_pcast(ea.cost),i,length_t_pcast(eb.cost));
}
if(!ok){
int n= max(a->n,b->n);
printf("a->n==%d\tb->n==%d\n",a->n,b->n);
for(i= 0;i<n;i++){
decluster_edge_t ea= a->edge[i],eb= b->edge[i];
printf(" %d",i);
if(i<a->n)printf(" a(%d,%d) "length_t_spec,
ea.city[0],ea.city[1],ea.cost);
else printf("\t");
if(i<b->n)printf(" b(%d,%d) "length_t_spec,
eb.city[0],eb.city[1],eb.cost);
printf("\n");
}
errorif(1,"Trees are different");
}
}


/*:79*/
#line 1868 "./decluster.w"



int
main(int argc,char**argv)
{
length_t len;
decluster_tree_t*mst;
tsp_instance= new_of(tsp_instance_t);
sort= dsort;
mem_usage_reset();
resource_setup(100);
/*80:*/
#line 2014 "./decluster.w"

{
decluster_tree_t simple_mat_MST;
simple_mat_MST.n= simple_mat_n-1;
simple_mat_MST.edge= simple_mat_MST_edges;
printf("Testing simple matrix");
tsp_instance->name= dup_string("dtsm");
tsp_instance->comment= dup_string("decluster test simple matrix");
tsp_instance->n= simple_mat_MST.n+1;
tsp_instance->edge_weight_type= EXPLICIT;
tsp_instance->edge_weight_format= FULL_MATRIX;
tsp_instance->edge_weights= NULL;
tsp_instance->short_edge_weights= NULL;
tsp_instance->coord= NULL;
tsp_instance->xmin= 0;
tsp_instance->xmax= 0;
tsp_instance->ymin= 0;
tsp_instance->ymax= 0;
mst= decluster_setup(simple_mat_n);
printf(".");
errorif(mst==NULL,"declustertest: Got null tree from decluster_setup\n");
cost= simple_mat_cost;
len= decluster_mst(tsp_instance,mst);
printf(".");
canonicalize(&simple_mat_MST);
printf(".");
canonicalize(mst);
printf(".");
compare_trees(&simple_mat_MST,mst);
printf(".");
decluster_preprocess(mst);
printf(".");
decluster_cleanup_tree(mst);
printf(".");
printf("mst works");
}

/*:80*//*82:*/
#line 2065 "./decluster.w"

{
int n= simple_mat_n;
print_tree(decluster_topology_tree(),"simple mat T_prime");
#define lca_table simple_mat_lca_len
/*83:*/
#line 2076 "./decluster.w"

{
int i,j,k;
for(k= 0;k<2;k++){
printf("\n<");
for(i= 0;i<n;i++){
printf(":");
for(j= 0;j<n;j++){
const length_t d= decluster_d(i,j);
printf(".");
if(verbose>=500)printf("\n\t%d %d "length_t_spec,i,j,length_t_pcast(d));
if(d!=lca_table[i][j]){
printf(
"decluster_d(%d,%d) "
"computed wrong: expected "length_t_spec
" got "length_t_spec,
i,j,
length_t_pcast(lca_table[i][j]),
length_t_pcast(d));
errorif(1,"LCA bug");
}
}
}
printf(">");
}
}

/*:83*/
#line 2070 "./decluster.w"

#undef lca_table
printf("lca works");
}

/*:82*/
#line 1880 "./decluster.w"

/*88:*/
#line 2186 "./decluster.w"

decluster_cleanup();
printf(".\n");


/*:88*/
#line 1881 "./decluster.w"

/*84:*/
#line 2104 "./decluster.w"

{
decluster_tree_t euc_MST;
euc_MST.n= euc_n-1;
euc_MST.edge= euc_MST_edges;
printf("Testing simple Euclidean");
tsp_instance->name= dup_string("dtse");
tsp_instance->comment= dup_string("decluster test simple Euclidean");
tsp_instance->n= euc_MST.n+1;
tsp_instance->edge_weight_type= EUC_2D;
tsp_instance->edge_weight_format= NONE;
tsp_instance->edge_weights= NULL;
tsp_instance->short_edge_weights= NULL;
tsp_instance->coord= euc_coord;
tsp_instance->xmin= 0;
tsp_instance->xmax= 0;
tsp_instance->ymin= 0;
tsp_instance->ymax= 121;
E2_create(tsp_instance);
printf(".");
mst= decluster_setup(euc_n);
printf(".");
errorif(mst==NULL,"declustertest: Got null tree from decluster_setup\n");
switch_to(tsp_instance);
len= decluster_mst(tsp_instance,mst);
printf(".");
canonicalize(&euc_MST);
printf(".");
canonicalize(mst);
printf(".");
compare_trees(&euc_MST,mst);
printf(".");
decluster_preprocess(mst);
printf(".");
decluster_cleanup_tree(mst);
printf(".");
E2_destroy();
printf(".");
printf("mst works");
}

/*:84*//*87:*/
#line 2173 "./decluster.w"

{
int n= euc_n;
print_tree(decluster_topology_tree(),"Euc T_prime");
#define lca_table euc_lca_len
/*83:*/
#line 2076 "./decluster.w"

{
int i,j,k;
for(k= 0;k<2;k++){
printf("\n<");
for(i= 0;i<n;i++){
printf(":");
for(j= 0;j<n;j++){
const length_t d= decluster_d(i,j);
printf(".");
if(verbose>=500)printf("\n\t%d %d "length_t_spec,i,j,length_t_pcast(d));
if(d!=lca_table[i][j]){
printf(
"decluster_d(%d,%d) "
"computed wrong: expected "length_t_spec
" got "length_t_spec,
i,j,
length_t_pcast(lca_table[i][j]),
length_t_pcast(d));
errorif(1,"LCA bug");
}
}
}
printf(">");
}
}

/*:83*/
#line 2178 "./decluster.w"

#undef lca_table
printf("lca works");
}



/*:87*/
#line 1882 "./decluster.w"

/*88:*/
#line 2186 "./decluster.w"

decluster_cleanup();
printf(".\n");


/*:88*/
#line 1883 "./decluster.w"

free_mem(tsp_instance);
return 0;
}

/*:73*/
