/*6:*/
#line 215 "./ascend.w"

#include <config.h>
#include "lkconfig.h"
/*7:*/
#line 227 "./ascend.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*:7*/
#line 218 "./ascend.w"

/*8:*/
#line 233 "./ascend.w"

#include "error.h"
#include "length.h"
#include "read.h" 
#include "lk.h"
#include "memory.h"
#include "decluster.h"

/*:8*//*10:*/
#line 252 "./ascend.w"

#include "ascend.h"

/*:10*/
#line 219 "./ascend.w"


/*15:*/
#line 309 "./ascend.w"

static int n= 0;
static int total_iter= -1;
static double*best_lambda= NULL,*read_lambda= NULL,*write_lambda= NULL;

/*:15*//*18:*/
#line 330 "./ascend.w"

static int*degree_less_2= NULL;
static int*degree_less_2_old= NULL;


/*:18*//*27:*/
#line 488 "./ascend.w"

static decluster_edge_t*onetree= NULL;

/*:27*//*42:*/
#line 671 "./ascend.w"

static int*work_from= NULL;
static double*work_dist= NULL;


/*:42*/
#line 221 "./ascend.w"

/*43:*/
#line 679 "./ascend.w"

static length_t
custom_cost(int i,int j)
{
return cost(i,j)+read_lambda[i]+read_lambda[j];
}


/*:43*/
#line 222 "./ascend.w"

/*19:*/
#line 344 "./ascend.w"

static double normalizer(int n,int*degree_less_2);
static double
normalizer(int n,int*degree_less_2)
{
int i;
double l;
for(l= 0.0,i= 0;i<n;i++){
l+= degree_less_2[i]*degree_less_2[i];
}
return l;
}

/*:19*//*20:*/
#line 365 "./ascend.w"

static void update_lambda(int n,double t,int*degree_less_2,int
*degree_less_2_old,double
*read_lambda,double*write_lambda);
static void
update_lambda(int n,double t,int*degree_less_2,int*degree_less_2_old,
double*read_lambda,double*write_lambda)
{
int i;
const double recent_share= 0.75;
const double ta= t*recent_share,tb= t*(1.0-recent_share);
for(i= 0;i<n;i++){
write_lambda[i]= read_lambda[i]
+ta*degree_less_2[i]+tb*degree_less_2_old[i];
}
}

/*:20*//*38:*/
#line 634 "./ascend.w"

static length_t compute_onetree(decluster_edge_t*onetree);
static length_t
compute_onetree(decluster_edge_t*onetree)
{
length_t len;
/*39:*/
#line 648 "./ascend.w"

{
decluster_tree_t T;
T.n= n-2;
T.edge= onetree;
len= decluster_mst_custom(&T,work_from,work_dist,custom_cost);
}

/*:39*/
#line 640 "./ascend.w"

/*44:*/
#line 692 "./ascend.w"

{const int v= n-1;
int i,short_to[2];
length_t short_dist[2]= {INFINITY,INFINITY};
for(i= 0;i<v;i++){
const length_t di= custom_cost(v,i);
if(di<short_dist[0]){
short_to[1]= short_to[0];
short_dist[1]= short_dist[0];
short_to[0]= i;
short_dist[0]= di;
}else if(di<short_dist[1]){
short_to[1]= i;
short_dist[1]= di;
}
}
onetree[n-2].city[0]= v;
onetree[n-2].city[1]= short_to[0];
onetree[n-2].cost= short_dist[0];
onetree[n-1].city[0]= v;
onetree[n-1].city[1]= short_to[1];
onetree[n-1].cost= short_dist[1];
len+= short_dist[0]+short_dist[1];
}

/*:44*/
#line 641 "./ascend.w"

return len;
}

/*:38*/
#line 223 "./ascend.w"

/*11:*/
#line 267 "./ascend.w"

void
ascend_setup(int the_n)
{
n= the_n;
best_lambda= new_arr_of(double,n);
read_lambda= new_arr_of(double,n);
write_lambda= new_arr_of(double,n);
/*16:*/
#line 320 "./ascend.w"

degree_less_2= new_arr_of(int,n);
degree_less_2_old= new_arr_of(int,n);

/*:16*//*25:*/
#line 480 "./ascend.w"

onetree= new_arr_of(decluster_edge_t,n);

/*:25*//*40:*/
#line 660 "./ascend.w"

work_from= new_arr_of(int,n-1);
work_dist= new_arr_of(double,n-1);

/*:40*/
#line 275 "./ascend.w"

total_iter= -1;
}

/*:11*//*12:*/
#line 281 "./ascend.w"

void
ascend_cleanup(void)
{
free_mem(best_lambda);
free_mem(read_lambda);
free_mem(write_lambda);
mem_deduct(sizeof(double)*3*n);
/*17:*/
#line 325 "./ascend.w"

free_mem(degree_less_2);mem_deduct(sizeof(int)*n);
free_mem(degree_less_2_old);mem_deduct(sizeof(int)*n);

/*:17*//*26:*/
#line 484 "./ascend.w"

free_mem(onetree);mem_deduct(n*sizeof(decluster_edge_t));

/*:26*//*41:*/
#line 665 "./ascend.w"

free_mem(work_from);
free_mem(work_dist);
mem_deduct((n-1)*(sizeof(int)+sizeof(double)));

/*:41*/
#line 289 "./ascend.w"

n= 0;
total_iter= -1;
}

/*:12*//*13:*/
#line 295 "./ascend.w"

double*const
ascend_best_lambda(void)
{
return best_lambda;
}

/*:13*//*22:*/
#line 409 "./ascend.w"

length_t
ascend_alpha_beta(const int n,double upper_bound_len,double alpha,double beta)
{
extern int verbose;
int i,best_iter,iter= -1,new_is_best;
double t,norm,best_lower_bound= 0.0,onetree_len;
errorif(LENGTH_TYPE_IS_INTEGRAL,
"Held-Karp lower bound computations require length_t to be a "
"floating point type.  Sorry, but you have to recompile.");
errorif(n<3,"ascend: n=%d < 3\n",n);
errorif(beta>=1.0,"ascend: beta=%f > 1\n",beta);
errorif(beta<=0,"ascend: beta=%f <= 0\n",beta);

for(i= 0;i<n;i++)degree_less_2_old[i]= read_lambda[i]= 0.0;
best_lower_bound= 0.0;
while(1){
total_iter++,iter++;
/*28:*/
#line 494 "./ascend.w"

{
const double len= compute_onetree(onetree);
double lambda_2= 0.0;
int i;
for(lambda_2= 0.0,i= 0;i<n;i++)lambda_2+= 2*read_lambda[i];
onetree_len= len-lambda_2;
}



/*:28*/
#line 427 "./ascend.w"

/*45:*/
#line 720 "./ascend.w"

{int i;
for(i= 0;i<n;i++)degree_less_2[i]= -2;
for(i= 0;i<n-1;i++){
degree_less_2[onetree[i].city[0]]++;
degree_less_2[onetree[i].city[1]]++;
}
}


/*:45*/
#line 428 "./ascend.w"

new_is_best= (onetree_len>best_lower_bound);
norm= normalizer(n,degree_less_2);

/*34:*/
#line 564 "./ascend.w"

if(new_is_best){
best_lower_bound= onetree_len;
best_iter= iter;
}

/*:34*/
#line 432 "./ascend.w"

/*35:*/
#line 572 "./ascend.w"

if(new_is_best){
double err= (upper_bound_len-onetree_len)/upper_bound_len;
if(err<0.001){
if(verbose>=75)
printf("#  Ascend: stopping criteria met: %.2f%% away from upper\n",err*100);
break;
}
}

/*:35*/
#line 433 "./ascend.w"

/*29:*/
#line 509 "./ascend.w"

if(norm==0.0){
/*48:*/
#line 751 "./ascend.w"

#if 0
if(verbose>=50)
printf("#  Ascend: Page %% total_iter %d Found a tour of length %f\n",
total_iter,(float)(onetree_len));
#endif


/*:48*/
#line 511 "./ascend.w"

for(onetree_len= 0.0,i= 0;i<n;i++)
onetree_len+= onetree[i].cost;
best_lower_bound= onetree_len;
/*49:*/
#line 760 "./ascend.w"

#if 0
if(verbose>=100){
char s[100];
sprintf(s,"Tour length %f",(float)onetree_len);
show_onetree(debug_ps,s,n,NULL,edge);
}
#endif

/*:49*/
#line 515 "./ascend.w"

break;
}

/*:29*/
#line 434 "./ascend.w"

/*32:*/
#line 545 "./ascend.w"

if(iter>1500){
if(verbose>=75)
printf("#  Ascend: Iterations exceeded 1500\n");
break;
}


/*:32*/
#line 435 "./ascend.w"


t= alpha*(upper_bound_len-onetree_len)/norm;
/*46:*/
#line 731 "./ascend.w"

if(verbose>=100){
printf("%d %f # 1-tree weight iter = %d L(l) t == %f alpha = %f\n",
total_iter,onetree_len,iter,t,alpha);
fflush(stdout);
}

/*:46*/
#line 438 "./ascend.w"

/*33:*/
#line 554 "./ascend.w"

if(t<1e-2){
if(verbose>=75)
printf("#  Ascend: stopping criteria met: t < 0.01 \n");
break;
}

/*:33*/
#line 439 "./ascend.w"

/*31:*/
#line 524 "./ascend.w"

#if 0
if(is_random_dist_matrix){
if(iter>1000&&iter-best_iter>5&&iter-best_iter<8){
if(verbose>=75)
printf("#  Ascend: stopping criteria met:  best is old\n");
break;
}
}else{
if(iter>1000&&iter-best_iter>5){
if(verbose>=75)
printf("#  Ascend: stopping criteria met:  best is old\n");
break;
}
}
#endif



/*:31*/
#line 440 "./ascend.w"


update_lambda(n,t,degree_less_2,degree_less_2_old,read_lambda,write_lambda);
alpha*= beta;
/*47:*/
#line 739 "./ascend.w"

#if 0
if(total_iter==0&&verbose>=100)
show_onetree(debug_ps,"First 1-tree, lambda==0 vector",n,NULL,edge);
else if(verbose>=500)
show_onetree(debug_ps,NULL,n,NULL,edge);

if(verbose)fflush(stdout);
#endif


/*:47*/
#line 444 "./ascend.w"

/*36:*/
#line 594 "./ascend.w"

{
double*b= best_lambda,*r= read_lambda,*w= write_lambda;
if(new_is_best){
best_lambda= b;
read_lambda= w;
write_lambda= r;
}else{
best_lambda= r;
read_lambda= w;
write_lambda= b;
}
}


/*:36*/
#line 445 "./ascend.w"

/*21:*/
#line 385 "./ascend.w"

{
int*t= degree_less_2;
degree_less_2= degree_less_2_old;
degree_less_2_old= t;
}

/*:21*/
#line 446 "./ascend.w"

}
return best_lower_bound;
}

/*:22*//*23:*/
#line 467 "./ascend.w"

length_t
ascend(const int n,double upper_bound_len)
{
return ascend_alpha_beta(n,upper_bound_len,1.5,0.995);
}

/*:23*/
#line 224 "./ascend.w"


/*:6*/
