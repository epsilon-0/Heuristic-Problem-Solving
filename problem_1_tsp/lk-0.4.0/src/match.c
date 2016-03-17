#define make_mates(u,v) ((mate[(u) ]= (v) ) ,(mate[(v) ]= (u) ) ) 
#define dump_core(x) ((verbose%2) ?*(int*) 0= (x) :(s_x= (x) ) )  \

#define swap_mates(a,b,c,d) { \
s_a= a; \
s_b= b; \
s_c= c; \
s_d= d; \
if(a<0||a>=n) dump_core(41) ; \
if(b<0||b>=n) dump_core(42) ; \
if(c<0||c>=n) dump_core(43) ; \
if(d<0||d>=n) dump_core(44) ; \
if((mate[a]!=b&&mate[b]!=a) ||(mate[c]!=d&&mate[d]!=c) ) dump_core(45) ; \
errorif((mate[a]!=b&&mate[b]!=a) ||(mate[c]!=d&&mate[d]!=c) , \
"swap_mates(%d,%d,%d,%d) aren't pairwise mates",a,b,c,d) ; \
make_mates(a,d) ; \
make_mates(b,c) ; \
} \

#define city_name(I) (1+(original_city_num?original_city_num[I]:I) )  \

#define USE_DECLUSTER (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY \
)  \

#define VIRTUAL_BASE ((char*) 42)  \

#define write_log(A) (change_log[change_log_next++]= (A) )  \

/*4:*/
#line 190 "./match.w"

#include <config.h>
#include "declevel.h"
#include "lkconfig.h"
/*16:*/
#line 353 "./match.w"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*:16*//*37:*/
#line 684 "./match.w"

#include <limits.h>

/*:37*/
#line 194 "./match.w"

/*13:*/
#line 306 "./match.w"

#include "error.h"
#include "memory.h"
#include "length.h"
#include "read.h"
#include "match.h"

/*:13*//*23:*/
#line 491 "./match.w"

#include "lk.h"


/*:23*//*26:*/
#line 522 "./match.w"

#include "construct.h"

/*:26*//*46:*/
#line 839 "./match.w"

#include "nn.h"

/*:46*//*51:*/
#line 911 "./match.w"

#include "dict.h"
#include "prng.h"

/*:51*//*63:*/
#line 1134 "./match.w"

#include "decluster.h"

/*:63*//*103:*/
#line 1690 "./match.w"

#include "resource.h"


/*:103*/
#line 195 "./match.w"


/*33:*/
#line 610 "./match.w"

#define SPLIT_GAIN_VAR (!(LENGTH_TYPE_IS_EXACT))



/*:33*//*34:*/
#line 640 "./match.w"

#if !SPLIT_GAIN_VAR
#define CAREFUL_OP(LHS,OP,RHS) ((LHS) OP (RHS))
#else
#define CAREFUL_OP(LHS,OP,RHS) ((LHS##_pos) OP (RHS##_with_slop + LHS##_neg))
#endif

/*:34*/
#line 197 "./match.w"

/*44:*/
#line 798 "./match.w"

typedef struct{
length_t gain_for_comparison;
length_t cluster_distance;
#if SPLIT_GAIN_VAR
length_t gain_1_pos,gain_1_neg;
length_t gain_pos,gain_neg;
#else
length_t gain_1;
length_t gain;
#endif
int t2ip1,t2ip2;
int two_i;
}eligible_t;

/*:44*/
#line 198 "./match.w"

/*5:*/
#line 211 "./match.w"

static int*mate= NULL;
static int n= 0;

/*:5*//*28:*/
#line 544 "./match.w"

int*t;

/*:28*/
#line 199 "./match.w"

/*7:*/
#line 242 "./match.w"

static int s_a,s_b,s_c,s_d,s_x;
static void(*prev_cleanup_fn)(void);
static
void
dump_ds(void)
{
int i;
printf("dumping core: %d\n",s_x);
printf("possibly swapping (%d,%d,%d,%d)\n",s_a,s_b,s_c,s_d);
for(i= 0;i<n;i++){
printf("  mate[%d] = %d\n",i,mate[i]);
}
if(prev_cleanup_fn)prev_cleanup_fn();
}

/*:7*//*53:*/
#line 940 "./match.w"

static int cmp_virtual_char(const void*a,const void*b);
static int
cmp_virtual_char(const void*a,const void*b)
{
return(const char*)a-(const char*)b;
}

static void prn_virtual_char(void*a);
static void
prn_virtual_char(void*a)
{
printf("%d",(const char*)a-VIRTUAL_BASE);
}

/*:53*//*67:*/
#line 1202 "./match.w"

static int cmp_eligible(const void*a,const void*b);
static int
cmp_eligible(const void*a,const void*b)
{
const eligible_t*ea= (const eligible_t*)a;
const eligible_t*eb= (const eligible_t*)b;
length_t diff= ea->gain_for_comparison-eb->gain_for_comparison;
return diff<0?1:(diff>0?-1:0);
}

/*:67*//*96:*/
#line 1617 "./match.w"

static void
show_entry_with_string_at_verbose(const eligible_t*e_entry,const char*str,int the_verbose)
{
if(verbose>=the_verbose){
printf("\n%s: %p two_i %d  t2ip1 = %d  t2ip2 = %d "length_t_spec" -> "length_t_spec,
str,
e_entry,
e_entry->two_i,
e_entry->t2ip1,
e_entry->t2ip2,
#if SPLIT_GAIN_VAR
length_t_pcast(e_entry->gain_pos-e_entry->gain_neg),
#else
length_t_pcast(e_entry->gain),
#endif
length_t_pcast(e_entry->gain_for_comparison)
);
fflush(stdout);
}
}

/*:96*/
#line 200 "./match.w"

/*9:*/
#line 265 "./match.w"

void
match_setup(int the_n)
{
errorif(the_n%2,
"Perfect matchings require an even number of vertices; given %d\n",the_n);
n= the_n;
mate= new_arr_of(int,n);
mate[0]= -1;
/*29:*/
#line 548 "./match.w"

t= new_arr_of(int,n+1);

/*:29*/
#line 274 "./match.w"

}


/*:9*//*10:*/
#line 279 "./match.w"

void
match_cleanup(void)
{
if(mate){free_mem(mate);mem_deduct(n*sizeof(int));}
/*30:*/
#line 552 "./match.w"

if(t){free_mem(t);mem_deduct(sizeof(int)*(n+1));}

/*:30*/
#line 284 "./match.w"

n= 0;
}

/*:10*//*15:*/
#line 328 "./match.w"

void
match_show(FILE*out)
{
length_t weight= 0;
int i;
errorif(mate==NULL||mate[0]==-1,
"Tried to print a matching before it is initialized");
fprintf(out,"Perfect matching:\n");
for(i= 0;i<n;i++){
const int i_mate= mate[i];
if(i_mate>i){
fprintf(out,"%d %d\n",city_name(i),city_name(i_mate));
weight+= cost(i,i_mate);
}
}
fprintf(out,"Length: "length_t_spec"\n",length_t_pcast(weight));
}


/*:15*//*17:*/
#line 363 "./match.w"

void
match_ps_out(FILE*ps_out,const char*name)
{
length_t weight= 0;
int i;
errorif(mate==NULL||mate[0]==-1,
"Tried to print a matching before it is initialized");
fprintf(ps_out,"%%Here's a weighted perfect matching\n");
for(i= 0;i<n;i++){
const int i_mate= mate[i];
if(i_mate>i){
weight+= cost(i,i_mate);
fprintf(ps_out,"%f x %f y %f x %f y rawedge\n",
tsp_instance->coord[i].x[0],
tsp_instance->coord[i].x[1],
tsp_instance->coord[i_mate].x[0],
tsp_instance->coord[i_mate].x[1]);
}
}

fprintf(ps_out,"(%s matching, weight "length_t_spec") title\n",
name,length_t_pcast(weight));
fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
fprintf(ps_out,"showpage\n");fflush(ps_out);
}

/*:17*//*19:*/
#line 404 "./match.w"

void
match_validate(length_t*validate_len,double*double_validate_len,
double*ordered_double_len,double*raw_len)
{
length_t my_validate_len= 0;
double my_double_validate_len= 0,my_ordered_double_len= 0,my_raw_len= 0;
double*length= new_arr_of(double,n/2);
double*raw_length= new_arr_of(double,n/2);
double*length_t_length= new_arr_of(length_t,n/2);

int i,w;
errorif(mate==NULL||mate[0]==-1,
"Tried to validate a matching before it is initialized");

/*21:*/
#line 454 "./match.w"

{
int i,*visited= new_arr_of_zero(int,n);
for(i= 0;i<n;i++){
const int i_mate= mate[i];
errorif(i_mate<0||i_mate>=n,
"Mate of %d is %d, out of range\n",i_mate);
visited[i]++;
visited[i_mate]++;
}
for(i= 0;i<n;i++){
errorif(visited[i]!=2,"Vertex %d visited %d times, not 2 times",i,visited[i]);
}

free_mem(visited);
}


/*:21*/
#line 419 "./match.w"


for(i= 0,w= 0;i<n;i++){
const int i_mate= mate[i];
if(i_mate>i){
length_t_length[w]= cost(i,i_mate);
length[w]= (double)length_t_length[w];
my_double_validate_len+= length[w];
switch(tsp_instance->edge_weight_type){
case EUC_2D:
case CEIL_2D:
raw_length[w]= cost_from_euc2d_raw(i,i_mate);
break;
default:raw_length[w]= length[w];
}
w++;
}
}
/*22:*/
#line 476 "./match.w"

sort(length,(unsigned)n/2,sizeof(double),lk_double_cmp);
sort(raw_length,(unsigned)n/2,sizeof(double),lk_double_cmp);
sort(length_t_length,(unsigned)n/2,sizeof(length_t),lk_length_t_cmp);
my_validate_len= 0;
my_ordered_double_len= my_raw_len= 0.0;
for(i= 0;i<n/2;i++){
my_validate_len+= length_t_length[i];
my_ordered_double_len+= length[i];
my_raw_len+= raw_length[i];
}

/*:22*/
#line 437 "./match.w"

free_mem(length);
free_mem(raw_length);
free_mem(length_t_length);
*validate_len= my_validate_len;
*double_validate_len= my_double_validate_len;
*ordered_double_len= my_ordered_double_len;
*raw_len= my_raw_len;
}
/*:19*//*24:*/
#line 507 "./match.w"

length_t
match_construct(int alg,long alg_param)
{
errorif(mate==NULL,
"Tried to construct a matching before space is allocated");
return construct_matching(n,mate,alg,alg_param);
}

/*:24*//*49:*/
#line 877 "./match.w"

void match_run(const int backtracking_levels,const int iterations,
prng_t*random_stream)
{
int iteration;
/*31:*/
#line 565 "./match.w"

int two_i;


/*:31*//*32:*/
#line 599 "./match.w"

#if SPLIT_GAIN_VAR
length_t cum_gain_pos,cum_gain_neg;
#else
length_t cum_gain;
#endif


/*:32*//*35:*/
#line 673 "./match.w"

length_t best_gain;
int best_two_i,best_exit_a,best_exit_b;

/*:35*//*38:*/
#line 697 "./match.w"

#if !LENGTH_TYPE_IS_EXACT
length_t best_gain_with_slop;
length_t instance_epsilon;
#endif

/*:38*//*45:*/
#line 834 "./match.w"

eligible_t**e;
int*en,*ei;

/*:45*//*58:*/
#line 1019 "./match.w"

int keep_going;

/*:58*//*71:*/
#line 1280 "./match.w"

const int max_two_i= 
(max_generic_flips==INT_MAX?INT_MAX:2*(backtracking_levels+max_generic_flips));

/*:71*//*78:*/
#line 1398 "./match.w"

int*change_log= NULL,change_log_max_alloc,change_log_next= 0;

/*:78*//*80:*/
#line 1422 "./match.w"

length_t previous_incumbent_len= 0;


/*:80*/
#line 882 "./match.w"

dict_t*dirty_set= dict_create(cmp_virtual_char,prn_virtual_char);
char*dirty_pointer;
/*54:*/
#line 958 "./match.w"

{
int i;
for(i= 0;i<n;i++){
dict_insert(dirty_set,VIRTUAL_BASE+i);
}
}

/*:54*/
#line 885 "./match.w"


/*8:*/
#line 259 "./match.w"

prev_cleanup_fn= error_precleanup_stats;
error_precleanup_stats= dump_ds;


/*:8*//*40:*/
#line 712 "./match.w"

/*39:*/
#line 706 "./match.w"

#if !LENGTH_TYPE_IS_EXACT
instance_epsilon= incumbent_len*LENGTH_MACHINE_EPSILON;
#endif

/*:39*/
#line 713 "./match.w"


/*:40*//*47:*/
#line 843 "./match.w"

{int l;
e= new_arr_of(eligible_t*,1+2*backtracking_levels);
en= new_arr_of(int,1+2*backtracking_levels);
ei= new_arr_of(int,1+2*backtracking_levels);
for(l= 2;l<=2*backtracking_levels;l+= 2)
e[l]= new_arr_of(eligible_t,nn_max_bound);
}

/*:47*//*76:*/
#line 1386 "./match.w"

change_log_max_alloc= 10000;
change_log= new_arr_of(int,change_log_max_alloc);

/*:76*/
#line 887 "./match.w"

for(iteration= 0;iteration<iterations;iteration++){
while((dirty_pointer= dict_delete_any(dirty_set,NULL))!=NULL){
t[1]= dirty_pointer-VIRTUAL_BASE;
t[2]= mate[t[1]];
two_i= 2;
/*36:*/
#line 678 "./match.w"

best_gain= 0;
best_two_i= 0;
best_exit_a= best_exit_b= INT_MAX;

/*:36*//*41:*/
#line 716 "./match.w"

#if SPLIT_GAIN_VAR
best_gain_with_slop= instance_epsilon;
#endif



/*:41*//*52:*/
#line 916 "./match.w"

#if SPLIT_GAIN_VAR
cum_gain_pos= cost(t[1],t[2]);
cum_gain_neg= 0;
#else
cum_gain= cost(t[1],t[2]);
#endif

/*:52*/
#line 893 "./match.w"

/*57:*/
#line 994 "./match.w"

/*97:*/
#line 1640 "./match.w"

if(verbose>=105){
printf("*");
}

/*:97*/
#line 995 "./match.w"

ei[two_i]= -2;
en[two_i]= -1;
{keep_going= 1;
while(keep_going){
if(two_i<=2*backtracking_levels){
if(ei[two_i]==-2){
/*59:*/
#line 1030 "./match.w"

{int j,num_candidates,*candidates;
candidates= nn_list(t[two_i],&num_candidates);
for(en[two_i]= j= 0;j<num_candidates;j++){
const int t2ip1= candidates[j],t2ip2= mate[t2ip1];
eligible_t*e_entry= &e[two_i][en[two_i]];
/*61:*/
#line 1092 "./match.w"

{
int j,tabu= 0;
if(t2ip2==t[two_i]){/*91:*/
#line 1591 "./match.w"

if(verbose>=500){
printf("X");
fflush(stdout);
}
/*:91*/
#line 1095 "./match.w"
continue;}
for(j= 2;j<two_i;j+= 2){
if((t2ip1==t[j]&&t2ip2==t[j+1])
||(t2ip1==t[j+1]&&t2ip2==t[j])){tabu= 1;break;}
}
if(tabu){/*91:*/
#line 1591 "./match.w"

if(verbose>=500){
printf("X");
fflush(stdout);
}
/*:91*/
#line 1100 "./match.w"
continue;}
}


/*:61*/
#line 1036 "./match.w"

/*62:*/
#line 1108 "./match.w"

{
const length_t this_neg= cost(t[two_i],t2ip1),
this_pos= cost(t2ip1,t2ip2),this_net= this_pos-this_neg;

e_entry->t2ip1= t2ip1;
e_entry->t2ip2= t2ip2;
#if SPLIT_GAIN_VAR
e_entry->gain_1_neg= cum_gain_neg+this_neg;
e_entry->gain_1_pos= cum_gain_pos;
e_entry->gain_neg= cum_gain_neg+this_neg;
e_entry->gain_pos= cum_gain_pos+this_pos;
#else
e_entry->gain_1= cum_gain-this_neg;
e_entry->gain= cum_gain+this_net;
#endif
#if USE_DECLUSTER
e_entry->cluster_distance= decluster_d(t[1],t2ip2);
e_entry->gain_for_comparison= this_net-e_entry->cluster_distance;
#else
e_entry->gain_for_comparison= this_net;
#endif
e_entry->two_i= two_i;
}

/*:62*/
#line 1037 "./match.w"

/*64:*/
#line 1142 "./match.w"

{
const length_t cluster_dist= (USE_DECLUSTER?e_entry->cluster_distance:0);
if(CAREFUL_OP(e_entry->gain,<=,cluster_dist+best_gain)
||CAREFUL_OP(e_entry->gain_1,<=,best_gain)){
/*92:*/
#line 1597 "./match.w"

if(verbose>=500){
printf("<");
fflush(stdout);
}

/*:92*/
#line 1147 "./match.w"

continue;
}
}


/*:64*/
#line 1038 "./match.w"

/*93:*/
#line 1604 "./match.w"

show_entry_with_string_at_verbose(e_entry,"accept",500);

/*:93*/
#line 1039 "./match.w"

/*65:*/
#line 1165 "./match.w"

{
#if SPLIT_GAIN_VAR
const length_t possible_best_gain_pos= e_entry->gain_pos,
possible_best_gain_neg= e_entry->gain_neg+cost(t[1],e_entry->t2ip2);
#else
const length_t possible_best_gain= e_entry->gain-cost(t[1],e_entry->t2ip2);
#endif

if(CAREFUL_OP(possible_best_gain,>,best_gain)){
best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
#if SPLIT_GAIN_VAR
best_gain= possible_best_gain_pos-possible_best_gain_neg;
#else
best_gain= possible_best_gain;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif
/*86:*/
#line 1540 "./match.w"

if(verbose>=125){
printf(" verbose %d ===two_i %d best_two_i %d best_exit_a %d best_exit_b %d\n",
verbose,
two_i,best_two_i,best_exit_a,best_exit_b);
fflush(stdout);
}

/*:86*/
#line 1186 "./match.w"

}
}

/*:65*/
#line 1040 "./match.w"

en[two_i]++;
}
/*66:*/
#line 1194 "./match.w"

sort(e[two_i],(size_t)en[two_i],sizeof(eligible_t),cmp_eligible);

/*:66*/
#line 1043 "./match.w"

ei[two_i]= 0;
}

/*:59*//*60:*/
#line 1048 "./match.w"

if(two_i<2*backtracking_levels){
ei[two_i+2]= -2;
en[two_i+2]= -1;
}


/*:60*/
#line 1002 "./match.w"

}
if(ei[two_i]<en[two_i]){
const eligible_t*e_entry= e[two_i]+ei[two_i];
/*98:*/
#line 1646 "./match.w"

if(verbose>=109){
printf("g");
}

/*:98*/
#line 1006 "./match.w"

ei[two_i]++;
/*68:*/
#line 1221 "./match.w"

/*95:*/
#line 1613 "./match.w"

show_entry_with_string_at_verbose(e_entry,"doing move",500);

/*:95*/
#line 1222 "./match.w"

#if SPLIT_GAIN_VAR
cum_gain_pos= e_entry->gain_pos;
cum_gain_neg= e_entry->gain_neg;
#else
cum_gain= e_entry->gain;
#endif
if(e_entry->two_i!=two_i)dump_core(96);

t[two_i+1]= e_entry->t2ip1;
t[two_i+2]= e_entry->t2ip2;
swap_mates(t[1],t[two_i],t[two_i+1],t[two_i+2]);
two_i+= 2;
/*85:*/
#line 1529 "./match.w"

if(verbose>125){
int i;
printf("\n");
for(i= 0;i<two_i;i++)putchar(' ');
printf("+");
fflush(stdout);
}


/*:85*/
#line 1235 "./match.w"

/*88:*/
#line 1557 "./match.w"

if(verbose>=150){
int i;
printf("t:");
for(i= 1;i<=two_i;i++)printf(" %d",t[i]);
printf("\n");
fflush(stdout);
}

/*:88*/
#line 1236 "./match.w"


/*:68*/
#line 1008 "./match.w"

}else if(best_two_i){keep_going= 0;}
else{/*69:*/
#line 1241 "./match.w"

if(two_i>2){
if(two_i<=2*backtracking_levels){
ei[two_i]= -2;
en[two_i]= -1;
}
two_i-= 2;
/*84:*/
#line 1519 "./match.w"

if(verbose>125){
int i;
printf("\n");
for(i= 0;i<two_i;i++)putchar(' ');
printf("-");
fflush(stdout);
}

/*:84*/
#line 1248 "./match.w"

swap_mates(t[1],t[two_i+2],t[two_i+1],t[two_i]);
/*88:*/
#line 1557 "./match.w"

if(verbose>=150){
int i;
printf("t:");
for(i= 1;i<=two_i;i++)printf(" %d",t[i]);
printf("\n");
fflush(stdout);
}

/*:88*/
#line 1250 "./match.w"

}else keep_going= 0;



/*:69*/
#line 1010 "./match.w"
}
}else{
/*99:*/
#line 1652 "./match.w"

if(verbose>=109){
printf("G");
}

/*:99*/
#line 1012 "./match.w"

/*70:*/
#line 1265 "./match.w"

{int none_eligible= 1;
if(two_i<=max_two_i){
/*72:*/
#line 1293 "./match.w"

{
eligible_t best_move;
int j,num_candidates,*candidates= nn_list(t[two_i],&num_candidates);
for(j= 0;j<num_candidates;j++){
const int t2ip1= candidates[j],t2ip2= mate[t2ip1];
eligible_t trial_move,*e_entry= &trial_move;
/*61:*/
#line 1092 "./match.w"

{
int j,tabu= 0;
if(t2ip2==t[two_i]){/*91:*/
#line 1591 "./match.w"

if(verbose>=500){
printf("X");
fflush(stdout);
}
/*:91*/
#line 1095 "./match.w"
continue;}
for(j= 2;j<two_i;j+= 2){
if((t2ip1==t[j]&&t2ip2==t[j+1])
||(t2ip1==t[j+1]&&t2ip2==t[j])){tabu= 1;break;}
}
if(tabu){/*91:*/
#line 1591 "./match.w"

if(verbose>=500){
printf("X");
fflush(stdout);
}
/*:91*/
#line 1100 "./match.w"
continue;}
}


/*:61*/
#line 1300 "./match.w"

/*62:*/
#line 1108 "./match.w"

{
const length_t this_neg= cost(t[two_i],t2ip1),
this_pos= cost(t2ip1,t2ip2),this_net= this_pos-this_neg;

e_entry->t2ip1= t2ip1;
e_entry->t2ip2= t2ip2;
#if SPLIT_GAIN_VAR
e_entry->gain_1_neg= cum_gain_neg+this_neg;
e_entry->gain_1_pos= cum_gain_pos;
e_entry->gain_neg= cum_gain_neg+this_neg;
e_entry->gain_pos= cum_gain_pos+this_pos;
#else
e_entry->gain_1= cum_gain-this_neg;
e_entry->gain= cum_gain+this_net;
#endif
#if USE_DECLUSTER
e_entry->cluster_distance= decluster_d(t[1],t2ip2);
e_entry->gain_for_comparison= this_net-e_entry->cluster_distance;
#else
e_entry->gain_for_comparison= this_net;
#endif
e_entry->two_i= two_i;
}

/*:62*/
#line 1301 "./match.w"

/*64:*/
#line 1142 "./match.w"

{
const length_t cluster_dist= (USE_DECLUSTER?e_entry->cluster_distance:0);
if(CAREFUL_OP(e_entry->gain,<=,cluster_dist+best_gain)
||CAREFUL_OP(e_entry->gain_1,<=,best_gain)){
/*92:*/
#line 1597 "./match.w"

if(verbose>=500){
printf("<");
fflush(stdout);
}

/*:92*/
#line 1147 "./match.w"

continue;
}
}


/*:64*/
#line 1302 "./match.w"

/*65:*/
#line 1165 "./match.w"

{
#if SPLIT_GAIN_VAR
const length_t possible_best_gain_pos= e_entry->gain_pos,
possible_best_gain_neg= e_entry->gain_neg+cost(t[1],e_entry->t2ip2);
#else
const length_t possible_best_gain= e_entry->gain-cost(t[1],e_entry->t2ip2);
#endif

if(CAREFUL_OP(possible_best_gain,>,best_gain)){
best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
#if SPLIT_GAIN_VAR
best_gain= possible_best_gain_pos-possible_best_gain_neg;
#else
best_gain= possible_best_gain;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif
/*86:*/
#line 1540 "./match.w"

if(verbose>=125){
printf(" verbose %d ===two_i %d best_two_i %d best_exit_a %d best_exit_b %d\n",
verbose,
two_i,best_two_i,best_exit_a,best_exit_b);
fflush(stdout);
}

/*:86*/
#line 1186 "./match.w"

}
}

/*:65*/
#line 1303 "./match.w"

/*93:*/
#line 1604 "./match.w"

show_entry_with_string_at_verbose(e_entry,"accept",500);

/*:93*/
#line 1304 "./match.w"

if(none_eligible||best_move.gain_for_comparison<trial_move.gain_for_comparison){
none_eligible= 0;
best_move= trial_move;
/*94:*/
#line 1608 "./match.w"

show_entry_with_string_at_verbose(e_entry,"best move",500);


/*:94*/
#line 1308 "./match.w"

}
}
if(!none_eligible){eligible_t*e_entry= &best_move;
/*68:*/
#line 1221 "./match.w"

/*95:*/
#line 1613 "./match.w"

show_entry_with_string_at_verbose(e_entry,"doing move",500);

/*:95*/
#line 1222 "./match.w"

#if SPLIT_GAIN_VAR
cum_gain_pos= e_entry->gain_pos;
cum_gain_neg= e_entry->gain_neg;
#else
cum_gain= e_entry->gain;
#endif
if(e_entry->two_i!=two_i)dump_core(96);

t[two_i+1]= e_entry->t2ip1;
t[two_i+2]= e_entry->t2ip2;
swap_mates(t[1],t[two_i],t[two_i+1],t[two_i+2]);
two_i+= 2;
/*85:*/
#line 1529 "./match.w"

if(verbose>125){
int i;
printf("\n");
for(i= 0;i<two_i;i++)putchar(' ');
printf("+");
fflush(stdout);
}


/*:85*/
#line 1235 "./match.w"

/*88:*/
#line 1557 "./match.w"

if(verbose>=150){
int i;
printf("t:");
for(i= 1;i<=two_i;i++)printf(" %d",t[i]);
printf("\n");
fflush(stdout);
}

/*:88*/
#line 1236 "./match.w"


/*:68*/
#line 1312 "./match.w"

}
}

/*:72*/
#line 1268 "./match.w"

}
if(none_eligible){
if(best_two_i==0)
while(two_i>2*backtracking_levels){/*69:*/
#line 1241 "./match.w"

if(two_i>2){
if(two_i<=2*backtracking_levels){
ei[two_i]= -2;
en[two_i]= -1;
}
two_i-= 2;
/*84:*/
#line 1519 "./match.w"

if(verbose>125){
int i;
printf("\n");
for(i= 0;i<two_i;i++)putchar(' ');
printf("-");
fflush(stdout);
}

/*:84*/
#line 1248 "./match.w"

swap_mates(t[1],t[two_i+2],t[two_i+1],t[two_i]);
/*88:*/
#line 1557 "./match.w"

if(verbose>=150){
int i;
printf("t:");
for(i= 1;i<=two_i;i++)printf(" %d",t[i]);
printf("\n");
fflush(stdout);
}

/*:88*/
#line 1250 "./match.w"

}else keep_going= 0;



/*:69*/
#line 1272 "./match.w"
}
else{keep_going= 0;}
}
}

/*:70*/
#line 1013 "./match.w"

}
}
}

/*:57*/
#line 894 "./match.w"

if(best_two_i){/*73:*/
#line 1330 "./match.w"

while(best_two_i<two_i){/*69:*/
#line 1241 "./match.w"

if(two_i>2){
if(two_i<=2*backtracking_levels){
ei[two_i]= -2;
en[two_i]= -1;
}
two_i-= 2;
/*84:*/
#line 1519 "./match.w"

if(verbose>125){
int i;
printf("\n");
for(i= 0;i<two_i;i++)putchar(' ');
printf("-");
fflush(stdout);
}

/*:84*/
#line 1248 "./match.w"

swap_mates(t[1],t[two_i+2],t[two_i+1],t[two_i]);
/*88:*/
#line 1557 "./match.w"

if(verbose>=150){
int i;
printf("t:");
for(i= 1;i<=two_i;i++)printf(" %d",t[i]);
printf("\n");
fflush(stdout);
}

/*:88*/
#line 1250 "./match.w"

}else keep_going= 0;



/*:69*/
#line 1331 "./match.w"
}
/*90:*/
#line 1579 "./match.w"

if(verbose>=110){
int i,m= (two_i<best_two_i?two_i:best_two_i);
printf("two_i %d best_two_i %d best_exit_a %d best_exit_b %d\n",
two_i,best_two_i,best_exit_a,best_exit_b);

printf("B:");
for(i= 1;i<=m;i++)printf(" %d",t[i]);
printf("\n");
fflush(stdout);
}
/*:90*/
#line 1332 "./match.w"

swap_mates(t[1],t[best_two_i],best_exit_a,best_exit_b);
/*74:*/
#line 1361 "./match.w"

if(iteration>0){
const int more_log= 3+best_two_i;
/*75:*/
#line 1376 "./match.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:75*/
#line 1364 "./match.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(2+best_two_i);
}

/*:74*/
#line 1334 "./match.w"

/*55:*/
#line 967 "./match.w"

{int i;
for(i= 1;i<=best_two_i;i++){
dict_insert(dirty_set,VIRTUAL_BASE+t[i]);
}
dict_insert(dirty_set,VIRTUAL_BASE+best_exit_a);
dict_insert(dirty_set,VIRTUAL_BASE+best_exit_b);
}

/*:55*/
#line 1335 "./match.w"

/*89:*/
#line 1567 "./match.w"

if(verbose>=110){
int i;
printf("T:");
for(i= 1;i<=best_two_i;i++)printf(" %d",t[i]);
printf(" %d",best_exit_a);
printf(" %d",best_exit_b);
printf("\n");
fflush(stdout);
}

/*:89*/
#line 1336 "./match.w"

incumbent_len-= best_gain;
/*87:*/
#line 1549 "./match.w"

if(verbose>=100){
printf("=== improve by "length_t_spec" to "length_t_spec"\n",
length_t_pcast(best_gain),length_t_pcast(incumbent_len));
fflush(stdout);
}

/*:87*/
#line 1338 "./match.w"

/*39:*/
#line 706 "./match.w"

#if !LENGTH_TYPE_IS_EXACT
instance_epsilon= incumbent_len*LENGTH_MACHINE_EPSILON;
#endif

/*:39*/
#line 1339 "./match.w"


/*:73*/
#line 895 "./match.w"
}
}
/*101:*/
#line 1666 "./match.w"

#if JBMR_MAX_VERBOSE >= 40
if(verbose>=40){
printf("End of LK step %d, incumbent_len = "length_t_spec"\n",
iteration+1,
length_t_pcast(incumbent_len));
}
#endif

/*:101*/
#line 897 "./match.w"

/*79:*/
#line 1409 "./match.w"

if(iteration>0&&change_log_next>0&&previous_incumbent_len<incumbent_len){
/*100:*/
#line 1658 "./match.w"

#if JBMR_MAX_VERBOSE >= 57
if(verbose>=57){
printf("Reverting to previous\n");
}
#endif

/*:100*/
#line 1411 "./match.w"

while(change_log_next>0){
/*81:*/
#line 1439 "./match.w"

{
const int t1_pos= change_log_next-change_log[change_log_next-1]-1;
int j;
for(j= change_log_next-3;j>=t1_pos;j-= 2){
const int a= change_log[j],b= change_log[j+1];
make_mates(a,b);
}
errorif(j!=t1_pos-2,"Fencepost Bug!");
}


/*:81*/
#line 1413 "./match.w"

change_log_next-= change_log[change_log_next-1]+1;
}
errorif(change_log_next!=0,"Bug!");
incumbent_len= previous_incumbent_len;
}
change_log_next= 0;

/*:79*/
#line 898 "./match.w"

/*82:*/
#line 1463 "./match.w"

if(iteration+1<iterations){
int m[8],i;

/*83:*/
#line 1489 "./match.w"

{
int count= 0,still_clashing;

do{
int j;
errorif(count++>=10000,"Ummm, 4-change matching mutation didn't terminate after 10000 tries!\n");
for(j= 0;j<8;j+= 2){
m[j]= prng_unif_int(random_stream,n);
m[j+1]= mate[m[j]];
}
still_clashing= 0;
for(j= 0;j<8;j+= 2){
int k;
for(k= j+2;k<8;k++){
if(m[j]==m[k]){
still_clashing= 1;
break;
}
}
}
}while(still_clashing);
}





/*:83*/
#line 1467 "./match.w"

make_mates(m[0],m[7]);
make_mates(m[1],m[2]);
make_mates(m[3],m[4]);
make_mates(m[5],m[6]);
for(i= 0;i<8;i++)write_log(m[i]);
write_log(8);


previous_incumbent_len= incumbent_len;
incumbent_len+= 
cost(m[1],m[2])+cost(m[3],m[4])+cost(m[5],m[6])+cost(m[7],m[0])
-cost(m[0],m[1])-cost(m[2],m[3])-cost(m[4],m[5])-cost(m[6],m[7]);


for(i= 0;i<8;i++)dict_insert(dirty_set,VIRTUAL_BASE+m[i]);
}

/*:82*/
#line 899 "./match.w"

}
/*102:*/
#line 1676 "./match.w"

#if JBMR_MAX_VERBOSE >= 20
if(verbose>=20){
const double lk_time= resource_user_tick();
const double ds_time= 
resource_user_tick_from(begin_data_structures_mark);
printf("LK phase ended with incumbent_len == "length_t_spec
" after %.3f sec for LK and %.3f sec for ds+LK\n",
length_t_pcast(incumbent_len),lk_time,ds_time);
fflush(stdout);
}
#endif

/*:102*/
#line 901 "./match.w"

/*48:*/
#line 853 "./match.w"

{int l;
for(l= 2;l<=2*backtracking_levels;l+= 2){
free_mem(e[l]);
mem_deduct(sizeof(eligible_t)*nn_max_bound);
}
free_mem(e);mem_deduct(sizeof(eligible_t*)*(1+2*backtracking_levels));
free_mem(en);mem_deduct(sizeof(int)*(1+2*backtracking_levels));
free_mem(ei);mem_deduct(sizeof(int)*(1+2*backtracking_levels));
}



/*:48*//*77:*/
#line 1391 "./match.w"

free_mem(change_log);mem_deduct(sizeof(int)*change_log_max_alloc);


/*:77*/
#line 902 "./match.w"

}

/*:49*/
#line 201 "./match.w"


/*:4*/
