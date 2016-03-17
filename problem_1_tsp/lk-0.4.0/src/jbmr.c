#define mark_dirty(CITY) (dict_insert(dirty_set,dirty_work+(CITY) ) )  \

#define write_log(a) (change_log[change_log_next++]= a)  \

#define DEPTHS_BOUND (n+20) 
#define swap_bridge(a,b) {int temp= a[0];a[0]= b[0];b[0]= temp;temp= a[1];a[1]= b[1];b[1]= temp;}
#define bridge_less(a,b) (tour_inorder(edge[0][0],edge[0][1],a[0],b[0]) )  \
 \

#define bridge_t(X) (edge[(X-1) >>1][(X-1) &1]) 
#define bridge_move(a,b,c,d) (tour_flip_arb(bridge_t(a) ,bridge_t(b) ,bridge_t(c) ,bridge_t(d) ) )  \

#define mutate(a) (mutation[mutation_next++]= bridge_t(a) )  \

/*4:*/
#line 533 "./jbmr.w"

#include <config.h>
#include "lkconfig.h"
/*5:*/
#line 550 "./jbmr.w"

#include <stdio.h>
#define __USE_MISC  
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include "fixincludes.h"

/*:5*/
#line 536 "./jbmr.w"

/*8:*/
#line 581 "./jbmr.w"

#include "error.h"
#include "memory.h"
#include "length.h"
#include "read.h"
#include "nn.h"
#include "lk.h"


/*:8*/
#line 537 "./jbmr.w"

/*7:*/
#line 567 "./jbmr.w"

#include "prng.h"
#include "jbmr.h"


/*:7*//*21:*/
#line 733 "./jbmr.w"

#include "pool.h"
#include "dict.h"

/*:21*//*68:*/
#line 1769 "./jbmr.w"

#include "decluster.h"
#include "declevel.h"

/*:68*//*129:*/
#line 3343 "./jbmr.w"

#include "resource.h"


/*:129*/
#line 538 "./jbmr.w"


/*33:*/
#line 940 "./jbmr.w"

#if LENGTH_TYPE_IS_EXACT || defined(JBMR_REQUIRE_JOINED_GAIN_VAR)
#define SPLIT_GAIN_VAR 0
#else
#define SPLIT_GAIN_VAR 1
#endif

/*:33*//*58:*/
#line 1554 "./jbmr.w"

#if LENGTH_TYPE_IS_EXACT
#define CAREFUL_OP(LHS,OP,RHS) ((LHS) OP (RHS))
#elif SPLIT_GAIN_VAR
#define CAREFUL_OP(LHS,OP,RHS) ((LHS##_pos) OP ((RHS##_with_slop)+(LHS##_neg)))
#else
#define CAREFUL_OP(LHS,OP,RHS) ((LHS) OP (RHS##_with_slop))
#endif




/*:58*//*161:*/
#line 3765 "./jbmr.w"

#if JBMR_MAX_VERBOSE||JBMR_REPORT_DEPTHS
#define TRACK_DEPTHS 1
#else
#define TRACK_DEPTHS 0
#endif

/*:161*/
#line 540 "./jbmr.w"

/*49:*/
#line 1410 "./jbmr.w"

typedef struct{
length_t gain_for_comparison;
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
length_t cluster_dist;
#endif
#if !SPLIT_GAIN_VAR
length_t gain;
#else 
length_t gain_pos,gain_neg;
#endif 
int t2ip1,t2ip2,scheme_id;
}eligible_t;

/*:49*/
#line 541 "./jbmr.w"

/*11:*/
#line 606 "./jbmr.w"

static int n;

/*:11*//*16:*/
#line 656 "./jbmr.w"

static int*dirty_work;

/*:16*//*43:*/
#line 1160 "./jbmr.w"

static int scheme[14][16]= {
{
1,2,5,6,
4,3,2,5},


{
1,2,6,5,
2,6,4,3,
1,5,4,6},


{
5,6,3,4,
1,2,6,3,
6,2,8,7,
1,3,2,8},


{
5,6,3,4,
8,7,6,3,
1,2,3,8},


{
1,2,3,4},


{
1,2,3,4,
1,4,6,5,
6,4,8,7,
1,5,4,8},


{
1,2,3,4,
6,5,8,7,
1,4,5,8},


{
1,2,3,4,
1,4,5,6},


{
1,2,5,6,
5,2,3,4},


{
6,5,8,7,
4,3,8,5,
1,2,3,8},


{
1,2,8,7,
1,7,6,5,
1,5,2,8,
4,3,2,5},


{
6,5,4,3,
6,3,8,7,
1,2,3,8},


{
6,5,8,7,
1,2,5,8,
5,2,3,4},


{-1}
};

static int scheme_max[14]= {8,12,16,12,4,16,12,8,8,12,16,12,12,0};
static int scheme_num_cities[14]= {6,6,8,8,4,8,8,6,6,8,8,8,8,0};

/*:43*//*92:*/
#line 2632 "./jbmr.w"

static int scheme_feas_check[14][10]= {
{-1},
{-1},
{1,3,3,6,2,6,1,8,2,8},
{3,8,1,8,3,6},
{-1},
{1,4,4,6,1,5,4,8},
{1,4,5,8,1,8},
{-1},
{-1},
{1,8,3,8,5,8},
{1,7,1,5,2,8,2,5,1,8},
{1,8,3,6,3,8},
{5,8,2,5,1,8},
{-1}
};

static int scheme_feas_n[14]= {0,0,10,6,0,8,6,0,0,6,10,6,6,0};

/*:92*//*136:*/
#line 3428 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 100 && defined(JBMR_WATCH_THIS_CITY)
static int old_verbose,old_verbose_is_set= 0;
#endif


/*:136*//*174:*/
#line 3867 "./jbmr.w"

#if TRACK_DEPTHS
static int*p_depths= NULL,*m_depths= NULL;
#endif

/*:174*/
#line 542 "./jbmr.w"

/*23:*/
#line 749 "./jbmr.w"

static int
cmp_int(const void*a,const void*b){
return(*(const int*)a)-(*(const int*)b);
}

static void
prn_int(void*a){
printf("%lx=int %d",(unsigned long)a,*(int*)a);
}


/*:23*//*30:*/
#line 847 "./jbmr.w"

static int tour_inorder(int a,int b,int c,int d);
static int
tour_inorder(int a,int b,int c,int d){
if(tour_next(a)==b)return tour_between(b,c,d);
else if(tour_prev(a)==b)return tour_between(d,c,b);
else{
/*160:*/
#line 3749 "./jbmr.w"

{int i,c,cn;
printf("Tour: 0");
for(i= 0,c= 0;i<n;i++){
errorif(c==0&&i>0,"Not a tour");
cn= tour_next(c);
printf(" %d",cn);
c= cn;
if(i%20==19)printf("\n");
}
printf("\n");
fflush(stdout);
errorif(c!=0,"Not a tour");
}

/*:160*/
#line 854 "./jbmr.w"

errorif(1,"Bad tour_inorder(%d,%d,%d,%d)\n");
return-1;
}
}

/*:30*//*72:*/
#line 1873 "./jbmr.w"

static int
cmp_eligible(const void*a,const void*b)
{
length_t diff= ((const eligible_t*)a)->gain_for_comparison
-((const eligible_t*)b)->gain_for_comparison;
return diff>0?-1:(diff<0?1:

#if defined(QSORT_DETERMINATE)
(int)(((eligible_t*)a)-((eligible_t*)b))
#else
0
#endif
);
}

/*:72*//*88:*/
#line 2424 "./jbmr.w"

static void tour_flip_arb(int a,int b,int c,int d);
static void
tour_flip_arb(int a,int b,int c,int d){
/*144:*/
#line 3519 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("tour_flip_arb(%d,%d,%d,%d)",a,b,c,d);
fflush(stdout);
}
#endif

/*:144*/
#line 2428 "./jbmr.w"

if(b==d||a==c)return;
if(a==tour_next(b)&&d==tour_next(c)){
tour_flip(a,b,c,d);
/*146:*/
#line 3537 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf(" case a\n");
fflush(stdout);
}
#endif

/*:146*/
#line 2432 "./jbmr.w"

}else if(a==tour_prev(b)&&d==tour_prev(c)){
tour_flip(b,a,d,c);
/*147:*/
#line 3546 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf(" case b\n");
fflush(stdout);
}
#endif

/*:147*/
#line 2435 "./jbmr.w"

}else{
printf("\nNeighbour conditions not met\n");
/*160:*/
#line 3749 "./jbmr.w"

{int i,c,cn;
printf("Tour: 0");
for(i= 0,c= 0;i<n;i++){
errorif(c==0&&i>0,"Not a tour");
cn= tour_next(c);
printf(" %d",cn);
c= cn;
if(i%20==19)printf("\n");
}
printf("\n");
fflush(stdout);
errorif(c!=0,"Not a tour");
}

/*:160*/
#line 2438 "./jbmr.w"

printf("\t(%d) %d (%d)",tour_prev(a),a,tour_next(a));
printf("\t(%d) %d (%d)",tour_prev(b),b,tour_next(b));
printf("\t(%d) %d (%d)",tour_prev(c),c,tour_next(c));
printf("\t(%d) %d (%d)",tour_prev(d),d,tour_next(d));
printf("\n");
errorif(1,"Neighbour conditions not met.");
}
}

/*:88*//*119:*/
#line 3177 "./jbmr.w"

#if defined(TABU_SPLAY)
static int cmp_pair(const void*a,const void*b);
static int
cmp_pair(const void*a,const void*b){
int a1= *((const int*)a),a2= *(((const int*)a)+1);
int b1= *((const int*)b),b2= *(((const int*)b)+1);
if(a1<a2){int t= a1;a1= a2;a2= t;}
if(b1<b2){int t= b1;b1= b2;b2= t;}
return a1==b1?a2-b2:a1-b1;
}
#endif


/*:119*//*125:*/
#line 3280 "./jbmr.w"

#if defined(TABU_SPLAY)
static void move_t(void*env,void**p);
static void
move_t(void*env,void**p){
int*old_t= ((int**)env)[0],*t= ((int**)env)[1];
*p= (void*)(t+((int*)(*p)-old_t));
}
#endif


/*:125*//*149:*/
#line 3573 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
#if !SPLIT_GAIN_VAR
#define put_city(X) \
if ( verbose >= 300 ) { \
 int i;\
 length_t cg =  cum_gain, bg =  best_gain; \
 for ( i= 0;i<(X);i++) {printf(" ");}\
 printf("t%d == %d p=%d n=%d",(X),t[(X)],tour_prev(t[(X)]),tour_next(t[(X)]));\
 if (X>1) { \
  int c =  cost(t[(X)-1],t[X]); \
  printf(" c(t%d,t%d)=%d",(X)-1,(X),c); \
  c =  cost(t[(X)],t[1]); \
  printf(" c(t%d,t1)=%d",(X),c); \
 } \
 printf("\tcg "length_t_spec" bg "length_t_spec"\n",length_t_pcast(cg),\
  length_t_pcast(bg)); \
 fflush(stdout); \
}
#else
#define put_city(X) \
if ( verbose >= 300 ) { \
 int i;\
 length_t cg =  cum_gain_pos-cum_gain_neg, bg =  best_gain; \
 for ( i= 0;i<(X);i++) {printf(" ");}\
 printf("t%d == %d p=%d n=%d",(X),t[(X)],tour_prev(t[(X)]),tour_next(t[(X)]));\
 if (X>1) { \
  int c =  cost(t[(X)-1],t[X]); \
  printf(" c(t%d,t%d)=%d",(X)-1,(X),c); \
  c =  cost(t[(X)],t[1]); \
  printf(" c(t%d,t1)=%d",(X),c); \
 } \
 printf("\tcg "length_t_spec" bg "length_t_spec"\n",length_t_pcast(cg),\
  length_t_pcast(bg)); \
 fflush(stdout); \
}

#endif
#else
#define put_city(X)
#endif

/*:149*/
#line 543 "./jbmr.w"

/*9:*/
#line 594 "./jbmr.w"

void
jbmr_setup(int the_n){
n= the_n;
/*15:*/
#line 649 "./jbmr.w"

dirty_work= new_arr_of(int,n);
{int i;
for(i= 0;i<n;i++)dirty_work[i]= i;
}

/*:15*//*172:*/
#line 3851 "./jbmr.w"

#if TRACK_DEPTHS && defined(TABU_JBMR)
p_depths= new_arr_of(int,DEPTHS_BOUND);
m_depths= new_arr_of(int,DEPTHS_BOUND);
{int i;for(i= 0;i<DEPTHS_BOUND;i++)p_depths[i]= m_depths[i]= 0;}
#endif


/*:172*/
#line 598 "./jbmr.w"

}

/*:9*//*12:*/
#line 610 "./jbmr.w"

void
jbmr_cleanup(void)
{
n= 0;
/*17:*/
#line 660 "./jbmr.w"

free_mem(dirty_work);

/*:17*//*173:*/
#line 3860 "./jbmr.w"

#if TRACK_DEPTHS
free_mem(p_depths);
free_mem(m_depths);
#endif

/*:173*/
#line 615 "./jbmr.w"

}

/*:12*//*19:*/
#line 697 "./jbmr.w"

void
jbmr_run(const int iterations,prng_t*random_stream)
{
/*26:*/
#line 799 "./jbmr.w"

int*t,t_max_alloc;

/*:26*//*34:*/
#line 948 "./jbmr.w"

#if SPLIT_GAIN_VAR
length_t cum_gain_pos,cum_gain_neg;
#endif

/*:34*//*35:*/
#line 957 "./jbmr.w"

length_t best_gain;

/*:35*//*36:*/
#line 969 "./jbmr.w"

#if !SPLIT_GAIN_VAR
length_t cum_gain;
#endif

/*:36*//*37:*/
#line 996 "./jbmr.w"

int best_two_i,best_exit_a,best_exit_b,best_scheme_id;


/*:37*//*38:*/
#line 1029 "./jbmr.w"

int more_backtracking;

/*:38*//*39:*/
#line 1044 "./jbmr.w"

int two_i;

/*:39*//*44:*/
#line 1263 "./jbmr.w"

int scheme_id,base_scheme[9];


/*:44*//*50:*/
#line 1433 "./jbmr.w"

eligible_t*(e[4]);

/*:50*//*53:*/
#line 1460 "./jbmr.w"

int en[4];

/*:53*//*54:*/
#line 1470 "./jbmr.w"

int ec[4];


/*:54*//*55:*/
#line 1503 "./jbmr.w"

#if !(LENGTH_TYPE_IS_EXACT)
length_t instance_epsilon= incumbent_len*LENGTH_MACHINE_EPSILON;
length_t best_gain_with_slop;
#endif

/*:55*//*60:*/
#line 1636 "./jbmr.w"

int num_reject_by_cum_1,num_reject_pre_e_build;

/*:60*//*64:*/
#line 1693 "./jbmr.w"

#if !defined(JBMR_UNROLL_PREV_NEXT_LOOP)
int(*tour_neighbour[2])(int);
#endif

/*:64*//*81:*/
#line 2056 "./jbmr.w"

int*change_log= NULL,change_log_max_alloc,change_log_next= 0;


/*:81*//*98:*/
#line 2806 "./jbmr.w"

int last_special_two_i;
int generic_flips_made;

/*:98*//*118:*/
#line 3161 "./jbmr.w"

#if defined(TABU_SPLAY)
dict_t*tabu= dict_create(cmp_pair,NULL);
#endif

/*:118*//*127:*/
#line 3318 "./jbmr.w"

const double milestone_percentage[]= 
{.10,
.099,.098,.097,.096,.095,.094,.093,.092,.091,.090,
.089,.088,.087,.086,.085,.084,.083,.082,.081,.080,
.079,.078,.077,.076,.075,.074,.073,.072,.071,.070,
.069,.068,.067,.066,.065,.064,.063,.062,.061,.060,
.059,.058,.057,.056,.055,.054,.053,.052,.051,.050,
.049,.048,.047,.046,.045,.044,.043,.042,.041,.040,
.039,.038,.037,.036,.035,.034,.033,.032,.031,.030,
.029,.028,.027,.026,.025,.024,.023,.022,.021,.020,
.019,.018,.017,.016,.015,.014,.013,.012,.011,.010,
.009,.008,.007,.006,.005,.004,.003,.002,.001,.000};
int milestone;
length_t milestone_value;
const int num_milestones= sizeof(milestone_percentage)/sizeof(double);
double milestone_time;

/*:127*//*153:*/
#line 3668 "./jbmr.w"

int num_reject_by_decluster;


/*:153*//*169:*/
#line 3821 "./jbmr.w"

#if TRACK_DEPTHS
int probe_depth,move_depth;
#endif

/*:169*//*171:*/
#line 3844 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
int probes= 0;
#endif

/*:171*//*178:*/
#line 3911 "./jbmr.w"

#if TRACK_DEPTHS
int last_probe_depth= 0;
#endif


/*:178*//*181:*/
#line 3951 "./jbmr.w"

length_t previous_incumbent_len= 0;

/*:181*//*192:*/
#line 4132 "./jbmr.w"

int mutation[12];

/*:192*/
#line 701 "./jbmr.w"

dict_t*dirty_set;
int*dirty,iteration;

/*61:*/
#line 1640 "./jbmr.w"

num_reject_by_cum_1= num_reject_pre_e_build= 0;


/*:61*//*65:*/
#line 1699 "./jbmr.w"

#if !defined(JBMR_UNROLL_PREV_NEXT_LOOP)
tour_neighbour[0]= tour_prev;
tour_neighbour[1]= tour_next;
#endif

/*:65*//*128:*/
#line 3337 "./jbmr.w"

milestone= 0;
milestone_value= lower_bound_value*(1+milestone_percentage[milestone]);
milestone_time= 0.0;

/*:128*//*154:*/
#line 3673 "./jbmr.w"

num_reject_by_decluster= 0;

/*:154*/
#line 705 "./jbmr.w"

/*27:*/
#line 810 "./jbmr.w"

t_max_alloc= 128;
t= new_arr_of(int,t_max_alloc);

/*:27*//*51:*/
#line 1440 "./jbmr.w"

e[0]= new_arr_of(eligible_t,nn_max_bound*2);
e[1]= new_arr_of(eligible_t,nn_max_bound*2);
e[2]= new_arr_of(eligible_t,nn_max_bound*2);
e[3]= new_arr_of(eligible_t,nn_max_bound*2);

/*:51*//*79:*/
#line 2044 "./jbmr.w"

change_log_max_alloc= 10000;
change_log= new_arr_of(int,change_log_max_alloc);

/*:79*/
#line 706 "./jbmr.w"

/*22:*/
#line 738 "./jbmr.w"

dirty_set= dict_create(cmp_int,prn_int);

/*:22*/
#line 707 "./jbmr.w"

/*24:*/
#line 765 "./jbmr.w"

{int i;
dict_delete_all(dirty_set,NULL);
for(i= 0;i<n;i++){
mark_dirty(i);
}
}

/*:24*/
#line 708 "./jbmr.w"

/*130:*/
#line 3348 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 25
if(lower_bound_name&&verbose>=25&&lower_bound_value>1e-5){
printf("Initial milestone: %.1f%% above %s\n",
100*(incumbent_len-lower_bound_value)/lower_bound_value,lower_bound_name);
fflush(stdout);
}
#endif

/*:130*/
#line 709 "./jbmr.w"


for(iteration= 0;iteration<iterations;iteration++){
/*99:*/
#line 2811 "./jbmr.w"

last_special_two_i= INT_MAX;
generic_flips_made= 0;




/*:99*/
#line 712 "./jbmr.w"

while((dirty= (int*)dict_delete_any(dirty_set,NULL))!=NULL){
/*45:*/
#line 1276 "./jbmr.w"

{
int t1_n[2],t1_i;
length_t t1_l[2];
/*135:*/
#line 3409 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 100
if(verbose>=100){
printf("Search for an improvement starting at city %d\n",*dirty);
fflush(stdout);
#if defined(JBMR_WATCH_THIS_CITY)
if(*dirty==JBMR_WATCH_THIS_CITY){
old_verbose= verbose;
old_verbose_is_set= 1;
verbose= 2000;
}else if(old_verbose_is_set){
verbose= old_verbose;
old_verbose_is_set= 0;
}
#endif
}
#endif

/*:135*/
#line 1280 "./jbmr.w"

t[1]= *dirty;
t1_n[0]= tour_prev(t[1]);
t1_n[1]= tour_next(t[1]);
t1_l[0]= cost(t1_n[0],t[1]);
t1_l[1]= cost(t1_n[1],t[1]);
#if JBMR_FARTHER_T1_FIRST
if(t1_l[0]<t1_l[1]){
int tmp;
length_t tmp_l;
tmp= t1_n[0];t1_n[0]= t1_n[1];t1_n[1]= tmp;
tmp_l= t1_l[0];t1_l[0]= t1_l[1];t1_l[1]= tmp_l;
}
#endif

/*46:*/
#line 1321 "./jbmr.w"

#if !SPLIT_GAIN_VAR
cum_gain= 0;
#else
cum_gain_pos= cum_gain_neg= 0;
#endif
best_gain= 0;best_two_i= 0;best_exit_a= best_exit_b= -1;
more_backtracking= 1;scheme_id= best_scheme_id= -1;

/*:46*//*56:*/
#line 1512 "./jbmr.w"

#if !(LENGTH_TYPE_IS_EXACT)
best_gain_with_slop= instance_epsilon;
#endif



/*:56*//*168:*/
#line 3815 "./jbmr.w"

#if TRACK_DEPTHS
probe_depth= move_depth= 0;
#endif

/*:168*/
#line 1295 "./jbmr.w"

put_city(1);
for(t1_i= 0;t1_i<2&&more_backtracking;t1_i++){
t[2]= t1_n[t1_i];
/*177:*/
#line 3897 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 70
if(verbose>=70){
printf("(t1,t2)= (%d,%d) cost=%f, d=%f p=%d\n",t[1],t[2],(double)cost(t[1],t[2]),
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
(double)decluster_d(t[1],t[2])
#else
(double)-1
#endif
,last_probe_depth);
}
#endif

/*:177*/
#line 1299 "./jbmr.w"

#if !SPLIT_GAIN_VAR
cum_gain= t1_l[t1_i];
#else
cum_gain_pos= t1_l[t1_i];
cum_gain_neg= 0;
#endif
put_city(2);
/*48:*/
#line 1375 "./jbmr.w"

two_i= 2;
/*167:*/
#line 3808 "./jbmr.w"

#if TRACK_DEPTHS
if(probe_depth<two_i+2)(probe_depth= two_i+2);
#endif


/*:167*/
#line 1377 "./jbmr.w"

#define BL 0
{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
const length_t cluster_dist= decluster_d(t[1],t[2]);
#else
const length_t cluster_dist= 0;
#endif
/*59:*/
#line 1596 "./jbmr.w"

en[BL]= ec[BL]= 0;
if(CAREFUL_OP(cum_gain,>,cluster_dist+best_gain)){
int i,t2ip1,t2ip2,enbl,*neighbour_list,nn_bound;
#if SPLIT_GAIN_VAR
length_t cum_1_pos,cum_1_neg,cum_2_pos,cum_2_neg;
#else
length_t cum_1,cum_2;
#endif
/*148:*/
#line 3555 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 400
if(verbose>=400){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3558 "./jbmr.w"

printf("%d %d "length_t_spec" "length_t_spec" s%d\n",t[two_i-1],t[two_i],
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_gain),
#else
length_t_pcast(cum_gain_pos-cum_gain_neg),
#endif
length_t_pcast(best_gain),scheme_id);
fflush(stdout);
}
#endif



/*:148*/
#line 1605 "./jbmr.w"



#if SPLIT_GAIN_VAR
cum_1_pos= cum_gain_pos;
#endif

neighbour_list= nn_list(t[two_i],&nn_bound);
for(i= 0,enbl= 0;i<nn_bound;i++){
t2ip1= neighbour_list[i];
#if SPLIT_GAIN_VAR
cum_1_neg= cum_gain_neg+cost(t[two_i],t2ip1);
#else
cum_1= cum_gain-cost(t[two_i],t2ip1);
#endif

if(CAREFUL_OP(cum_1,<=,best_gain)){
/*155:*/
#line 3677 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3680 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("Terminating |cum_1| "length_t_spec"\n",length_t_pcast(cum_1));
#else
printf("Terminating |cum_1| "length_t_spec" "
"(== "length_t_spec" - "length_t_spec")\n",
length_t_pcast(cum_1_pos-cum_1_neg),
length_t_pcast(cum_1_pos),
length_t_pcast(cum_1_neg));
#endif
fflush(stdout);
}
#endif

/*:155*/
#line 1622 "./jbmr.w"

num_reject_by_cum_1++;
break;
}

/*62:*/
#line 1650 "./jbmr.w"

#if BL==0
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 1652 "./jbmr.w"

#endif

/*:62*//*82:*/
#line 2092 "./jbmr.w"

#if BL==1
if(t2ip1!=t[3]){
switch(e[0][ec[0]].scheme_id){
case 0:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[3])?0:2;break;
case 4:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[4])?5:8;break;
default:errorif(1,"Non exhaustive switch: %d",e[0][ec[0]].scheme_id);
}
/*157:*/
#line 3724 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3727 "./jbmr.w"
printf("base_scheme5 == %d\n",base_scheme[5]);
fflush(stdout);
}
#endif

/*:157*/
#line 2100 "./jbmr.w"

/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2101 "./jbmr.w"

}
#endif


/*:82*//*89:*/
#line 2468 "./jbmr.w"

#if BL==2
if(t2ip1!=t[5]){
int i1,i2,i4;
switch(base_scheme[7]= e[1][ec[1]].scheme_id){
case 2:i1= 1;i2= 2;i4= 3;break;
case 5:i1= 6,i2= 5,i4= 4;break;
case 9:i1= 1,i2= 2,i4= 5;break;
default:errorif(1,"Got to 4-change in base scheme %d",base_scheme[7]);
i1= i2= i4= -1;
break;
}
if(tour_inorder(t[i1],t[i2],t2ip1,t[i4])){
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2481 "./jbmr.w"

}
}
#endif


/*:89*//*100:*/
#line 2821 "./jbmr.w"

#if BL==3
if(t[two_i]==tour_prev(t[1]))t2ip2= tour_next(t2ip1);
else t2ip2= tour_prev(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 2825 "./jbmr.w"

#endif


/*:100*/
#line 1627 "./jbmr.w"

}
en[BL]= enbl;
}else{
num_reject_pre_e_build++;
}

/*:59*/
#line 1385 "./jbmr.w"

}
/*71:*/
#line 1857 "./jbmr.w"

sort(e[BL],(size_t)en[BL],sizeof(eligible_t),cmp_eligible);

/*:71*/
#line 1387 "./jbmr.w"

#undef BL
/*74:*/
#line 1940 "./jbmr.w"

for(ec[0]= 0;more_backtracking&&ec[0]<en[0];ec[0]++){
eligible_t*this_move= &e[0][ec[0]];
t[3]= this_move->t2ip1;
t[4]= this_move->t2ip2;
#if !SPLIT_GAIN_VAR
cum_gain= this_move->gain;
#else
cum_gain_pos= this_move->gain_pos;
cum_gain_neg= this_move->gain_neg;
#endif
two_i= 4;
/*167:*/
#line 3808 "./jbmr.w"

#if TRACK_DEPTHS
if(probe_depth<two_i+2)(probe_depth= two_i+2);
#endif


/*:167*/
#line 1952 "./jbmr.w"

#define BL 1
{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
const length_t cluster_dist= this_move->cluster_dist;
#else
const length_t cluster_dist= 0;
#endif
/*59:*/
#line 1596 "./jbmr.w"

en[BL]= ec[BL]= 0;
if(CAREFUL_OP(cum_gain,>,cluster_dist+best_gain)){
int i,t2ip1,t2ip2,enbl,*neighbour_list,nn_bound;
#if SPLIT_GAIN_VAR
length_t cum_1_pos,cum_1_neg,cum_2_pos,cum_2_neg;
#else
length_t cum_1,cum_2;
#endif
/*148:*/
#line 3555 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 400
if(verbose>=400){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3558 "./jbmr.w"

printf("%d %d "length_t_spec" "length_t_spec" s%d\n",t[two_i-1],t[two_i],
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_gain),
#else
length_t_pcast(cum_gain_pos-cum_gain_neg),
#endif
length_t_pcast(best_gain),scheme_id);
fflush(stdout);
}
#endif



/*:148*/
#line 1605 "./jbmr.w"



#if SPLIT_GAIN_VAR
cum_1_pos= cum_gain_pos;
#endif

neighbour_list= nn_list(t[two_i],&nn_bound);
for(i= 0,enbl= 0;i<nn_bound;i++){
t2ip1= neighbour_list[i];
#if SPLIT_GAIN_VAR
cum_1_neg= cum_gain_neg+cost(t[two_i],t2ip1);
#else
cum_1= cum_gain-cost(t[two_i],t2ip1);
#endif

if(CAREFUL_OP(cum_1,<=,best_gain)){
/*155:*/
#line 3677 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3680 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("Terminating |cum_1| "length_t_spec"\n",length_t_pcast(cum_1));
#else
printf("Terminating |cum_1| "length_t_spec" "
"(== "length_t_spec" - "length_t_spec")\n",
length_t_pcast(cum_1_pos-cum_1_neg),
length_t_pcast(cum_1_pos),
length_t_pcast(cum_1_neg));
#endif
fflush(stdout);
}
#endif

/*:155*/
#line 1622 "./jbmr.w"

num_reject_by_cum_1++;
break;
}

/*62:*/
#line 1650 "./jbmr.w"

#if BL==0
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 1652 "./jbmr.w"

#endif

/*:62*//*82:*/
#line 2092 "./jbmr.w"

#if BL==1
if(t2ip1!=t[3]){
switch(e[0][ec[0]].scheme_id){
case 0:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[3])?0:2;break;
case 4:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[4])?5:8;break;
default:errorif(1,"Non exhaustive switch: %d",e[0][ec[0]].scheme_id);
}
/*157:*/
#line 3724 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3727 "./jbmr.w"
printf("base_scheme5 == %d\n",base_scheme[5]);
fflush(stdout);
}
#endif

/*:157*/
#line 2100 "./jbmr.w"

/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2101 "./jbmr.w"

}
#endif


/*:82*//*89:*/
#line 2468 "./jbmr.w"

#if BL==2
if(t2ip1!=t[5]){
int i1,i2,i4;
switch(base_scheme[7]= e[1][ec[1]].scheme_id){
case 2:i1= 1;i2= 2;i4= 3;break;
case 5:i1= 6,i2= 5,i4= 4;break;
case 9:i1= 1,i2= 2,i4= 5;break;
default:errorif(1,"Got to 4-change in base scheme %d",base_scheme[7]);
i1= i2= i4= -1;
break;
}
if(tour_inorder(t[i1],t[i2],t2ip1,t[i4])){
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2481 "./jbmr.w"

}
}
#endif


/*:89*//*100:*/
#line 2821 "./jbmr.w"

#if BL==3
if(t[two_i]==tour_prev(t[1]))t2ip2= tour_next(t2ip1);
else t2ip2= tour_prev(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 2825 "./jbmr.w"

#endif


/*:100*/
#line 1627 "./jbmr.w"

}
en[BL]= enbl;
}else{
num_reject_pre_e_build++;
}

/*:59*/
#line 1960 "./jbmr.w"

}
/*71:*/
#line 1857 "./jbmr.w"

sort(e[BL],(size_t)en[BL],sizeof(eligible_t),cmp_eligible);

/*:71*/
#line 1962 "./jbmr.w"

#undef BL
/*85:*/
#line 2332 "./jbmr.w"

for(ec[1]= 0;more_backtracking&&ec[1]<en[1];ec[1]++){
eligible_t*this_move= &e[1][ec[1]];
t[5]= this_move->t2ip1;
t[6]= this_move->t2ip2;
#if !SPLIT_GAIN_VAR
cum_gain= this_move->gain;
#else
cum_gain_pos= this_move->gain_pos;
cum_gain_neg= this_move->gain_neg;
#endif
two_i= 6;
/*167:*/
#line 3808 "./jbmr.w"

#if TRACK_DEPTHS
if(probe_depth<two_i+2)(probe_depth= two_i+2);
#endif


/*:167*/
#line 2344 "./jbmr.w"

if(scheme_num_cities[this_move->scheme_id]==6){
scheme_id= this_move->scheme_id;
/*87:*/
#line 2409 "./jbmr.w"

{int i,n= scheme_max[scheme_id],*s= &scheme[scheme_id][0];
/*141:*/
#line 3475 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Implement scheme %d\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3479 "./jbmr.w"

fflush(stdout);
}
#endif

/*:141*/
#line 2411 "./jbmr.w"

for(i= 0;i<n;i+= 4){
tour_flip_arb(t[s[i]],t[s[i+1]],t[s[i+2]],t[s[i+3]]);
}
}

/*:87*/
#line 2347 "./jbmr.w"

/*96:*/
#line 2736 "./jbmr.w"

{int go_deeper;
last_special_two_i= two_i;
generic_flips_made= 0;
/*114:*/
#line 3133 "./jbmr.w"


/*:114*//*121:*/
#line 3213 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{
int i;
for(i= 2;i<two_i;i+= 2)dict_insert(tabu,t+i);
}
#endif

/*:121*/
#line 2740 "./jbmr.w"

/*139:*/
#line 3454 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 175
if(verbose>=175){
printf("Start generic search\n");
fflush(stdout);
}
#endif


/*:139*/
#line 2741 "./jbmr.w"

for(go_deeper= 1;go_deeper;){
/*97:*/
#line 2770 "./jbmr.w"

#if defined(JBMR_LIMIT_PROBE_DEPTH)
if(generic_flips_made>=max_generic_flips){
/*179:*/
#line 3918 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 75
if(verbose>=75){
printf(" hit max generic flips: %d >= %d\n",
generic_flips_made,max_generic_flips);
}
#endif

/*:179*/
#line 2773 "./jbmr.w"

/*105:*/
#line 2963 "./jbmr.w"

if(best_gain==0){
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2965 "./jbmr.w"

}else if(best_scheme_id==13){
/*106:*/
#line 2974 "./jbmr.w"

{
int low_j,best_is_prefix;
errorif(best_gain<=0,"Bad best_scheme_id == 13");
best_is_prefix= t[best_two_i+1]==best_exit_a
&&t[best_two_i+2]==best_exit_b;
low_j= best_two_i+(best_is_prefix?2:0);
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 2981 "./jbmr.w"

if(!best_is_prefix){
tour_flip_arb(t[1],t[best_two_i],best_exit_a,best_exit_b);
}
/*76:*/
#line 1989 "./jbmr.w"

{int i;
for(i= 1;i<=best_two_i;i++){
mark_dirty(t[i]);
}
mark_dirty(best_exit_a);
mark_dirty(best_exit_b);
}

/*:76*//*77:*/
#line 2017 "./jbmr.w"

if(iteration>0){
const int more_log= 4+best_two_i;
/*78:*/
#line 2034 "./jbmr.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:78*/
#line 2020 "./jbmr.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


/*:77*/
#line 2985 "./jbmr.w"

/*165:*/
#line 3794 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= best_two_i+2;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3797 "./jbmr.w"

#endif

/*:165*/
#line 2986 "./jbmr.w"

more_backtracking= 0;
}

/*:106*/
#line 2967 "./jbmr.w"

}

/*:105*/
#line 2774 "./jbmr.w"

go_deeper= 0;
break;
}
#endif

/*:97*/
#line 2743 "./jbmr.w"

/*167:*/
#line 3808 "./jbmr.w"

#if TRACK_DEPTHS
if(probe_depth<two_i+2)(probe_depth= two_i+2);
#endif


/*:167*/
#line 2744 "./jbmr.w"

/*29:*/
#line 828 "./jbmr.w"

if(two_i+3>=t_max_alloc){
#if defined(TABU_SPLAY)
int*old_t= t;
#endif
do{
t_max_alloc*= 2;
}while(two_i+3>=t_max_alloc);
t= (int*)mem_realloc(t,sizeof(int)*t_max_alloc);
/*124:*/
#line 3266 "./jbmr.w"

#if defined(TABU_SPLAY)
{int*env[2];
env[0]= old_t;
env[1]= t;
dict_update_all(tabu,move_t,env);
}
#endif

/*:124*/
#line 837 "./jbmr.w"

}


/*:29*/
#line 2745 "./jbmr.w"

#define BL 3
{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
const length_t cluster_dist= decluster_d(t[1],t[two_i]);
#else
const length_t cluster_dist= 0;
#endif
/*59:*/
#line 1596 "./jbmr.w"

en[BL]= ec[BL]= 0;
if(CAREFUL_OP(cum_gain,>,cluster_dist+best_gain)){
int i,t2ip1,t2ip2,enbl,*neighbour_list,nn_bound;
#if SPLIT_GAIN_VAR
length_t cum_1_pos,cum_1_neg,cum_2_pos,cum_2_neg;
#else
length_t cum_1,cum_2;
#endif
/*148:*/
#line 3555 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 400
if(verbose>=400){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3558 "./jbmr.w"

printf("%d %d "length_t_spec" "length_t_spec" s%d\n",t[two_i-1],t[two_i],
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_gain),
#else
length_t_pcast(cum_gain_pos-cum_gain_neg),
#endif
length_t_pcast(best_gain),scheme_id);
fflush(stdout);
}
#endif



/*:148*/
#line 1605 "./jbmr.w"



#if SPLIT_GAIN_VAR
cum_1_pos= cum_gain_pos;
#endif

neighbour_list= nn_list(t[two_i],&nn_bound);
for(i= 0,enbl= 0;i<nn_bound;i++){
t2ip1= neighbour_list[i];
#if SPLIT_GAIN_VAR
cum_1_neg= cum_gain_neg+cost(t[two_i],t2ip1);
#else
cum_1= cum_gain-cost(t[two_i],t2ip1);
#endif

if(CAREFUL_OP(cum_1,<=,best_gain)){
/*155:*/
#line 3677 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3680 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("Terminating |cum_1| "length_t_spec"\n",length_t_pcast(cum_1));
#else
printf("Terminating |cum_1| "length_t_spec" "
"(== "length_t_spec" - "length_t_spec")\n",
length_t_pcast(cum_1_pos-cum_1_neg),
length_t_pcast(cum_1_pos),
length_t_pcast(cum_1_neg));
#endif
fflush(stdout);
}
#endif

/*:155*/
#line 1622 "./jbmr.w"

num_reject_by_cum_1++;
break;
}

/*62:*/
#line 1650 "./jbmr.w"

#if BL==0
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 1652 "./jbmr.w"

#endif

/*:62*//*82:*/
#line 2092 "./jbmr.w"

#if BL==1
if(t2ip1!=t[3]){
switch(e[0][ec[0]].scheme_id){
case 0:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[3])?0:2;break;
case 4:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[4])?5:8;break;
default:errorif(1,"Non exhaustive switch: %d",e[0][ec[0]].scheme_id);
}
/*157:*/
#line 3724 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3727 "./jbmr.w"
printf("base_scheme5 == %d\n",base_scheme[5]);
fflush(stdout);
}
#endif

/*:157*/
#line 2100 "./jbmr.w"

/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2101 "./jbmr.w"

}
#endif


/*:82*//*89:*/
#line 2468 "./jbmr.w"

#if BL==2
if(t2ip1!=t[5]){
int i1,i2,i4;
switch(base_scheme[7]= e[1][ec[1]].scheme_id){
case 2:i1= 1;i2= 2;i4= 3;break;
case 5:i1= 6,i2= 5,i4= 4;break;
case 9:i1= 1,i2= 2,i4= 5;break;
default:errorif(1,"Got to 4-change in base scheme %d",base_scheme[7]);
i1= i2= i4= -1;
break;
}
if(tour_inorder(t[i1],t[i2],t2ip1,t[i4])){
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2481 "./jbmr.w"

}
}
#endif


/*:89*//*100:*/
#line 2821 "./jbmr.w"

#if BL==3
if(t[two_i]==tour_prev(t[1]))t2ip2= tour_next(t2ip1);
else t2ip2= tour_prev(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 2825 "./jbmr.w"

#endif


/*:100*/
#line 1627 "./jbmr.w"

}
en[BL]= enbl;
}else{
num_reject_pre_e_build++;
}

/*:59*/
#line 2753 "./jbmr.w"

}
#undef BL
if(en[3]>0){
/*104:*/
#line 2907 "./jbmr.w"

{int i,best_i= -1;
#if !SPLIT_GAIN_VAR
length_t best_len= 0;
#else
length_t best_len_pos= 0,best_len_neg= 0;
#endif
/*156:*/
#line 3695 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
int i;
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3699 "./jbmr.w"
printf("go deeper candidates begin\n");
for(i= 0;i<en[3];i++){
#if !SPLIT_GAIN_VAR
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3702 "./jbmr.w"
printf("%d %d "length_t_spec" s%d\n",
e[3][i].t2ip1,
e[3][i].t2ip2,
length_t_pcast(e[3][i].gain),
e[3][i].scheme_id);
#else
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3708 "./jbmr.w"
printf("%d %d "length_t_spec" (=="length_t_spec"-"
length_t_spec") s%d\n",
e[3][i].t2ip1,
e[3][i].t2ip2,
length_t_pcast(e[3][i].gain_pos-e[3][i].gain_neg),
length_t_pcast(e[3][i].gain_pos),
length_t_pcast(e[3][i].gain_neg),
e[3][i].scheme_id);
#endif
}
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3718 "./jbmr.w"
printf("go deeper candidates end\n");
fflush(stdout);
}
#endif

/*:156*/
#line 2914 "./jbmr.w"

for(i= 0;i<en[3];i++){
if(
#if JBMR_DECLUSTER_IN_GREEDY
e[3][i].cluster_dist+
#endif
#if !SPLIT_GAIN_VAR
best_len<e[3][i].gain
#else
best_len_pos+e[3][i].gain_neg<best_len_neg+e[3][i].gain_pos
#endif
)
{
best_i= i;
#if !SPLIT_GAIN_VAR
best_len= e[3][i].gain;
#else
best_len_pos= e[3][i].gain_pos;
best_len_neg= e[3][i].gain_neg;
#endif
}
}
errorif(best_i==-1,"Shouldn't be going deeper.");
#if !SPLIT_GAIN_VAR
cum_gain= best_len;
#else
cum_gain_pos= best_len_pos;
cum_gain_neg= best_len_neg;
#endif
t[two_i+1]= e[3][best_i].t2ip1;
t[two_i+2]= e[3][best_i].t2ip2;
tour_flip_arb(t[1],t[two_i],t[two_i+1],t[two_i+2]);
/*115:*/
#line 3136 "./jbmr.w"


/*:115*//*122:*/
#line 3222 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
dict_insert(tabu,t+two_i);
#endif

/*:122*/
#line 2946 "./jbmr.w"

two_i+= 2;
generic_flips_made++;
/*137:*/
#line 3435 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips made: %d\n",generic_flips_made);
fflush(stdout);
}
#endif

/*:137*/
#line 2949 "./jbmr.w"

}

/*:104*/
#line 2757 "./jbmr.w"

}else{
/*105:*/
#line 2963 "./jbmr.w"

if(best_gain==0){
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2965 "./jbmr.w"

}else if(best_scheme_id==13){
/*106:*/
#line 2974 "./jbmr.w"

{
int low_j,best_is_prefix;
errorif(best_gain<=0,"Bad best_scheme_id == 13");
best_is_prefix= t[best_two_i+1]==best_exit_a
&&t[best_two_i+2]==best_exit_b;
low_j= best_two_i+(best_is_prefix?2:0);
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 2981 "./jbmr.w"

if(!best_is_prefix){
tour_flip_arb(t[1],t[best_two_i],best_exit_a,best_exit_b);
}
/*76:*/
#line 1989 "./jbmr.w"

{int i;
for(i= 1;i<=best_two_i;i++){
mark_dirty(t[i]);
}
mark_dirty(best_exit_a);
mark_dirty(best_exit_b);
}

/*:76*//*77:*/
#line 2017 "./jbmr.w"

if(iteration>0){
const int more_log= 4+best_two_i;
/*78:*/
#line 2034 "./jbmr.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:78*/
#line 2020 "./jbmr.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


/*:77*/
#line 2985 "./jbmr.w"

/*165:*/
#line 3794 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= best_two_i+2;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3797 "./jbmr.w"

#endif

/*:165*/
#line 2986 "./jbmr.w"

more_backtracking= 0;
}

/*:106*/
#line 2967 "./jbmr.w"

}

/*:105*/
#line 2759 "./jbmr.w"

go_deeper= 0;
}
}
/*116:*/
#line 3139 "./jbmr.w"


/*:116*//*123:*/
#line 3231 "./jbmr.w"

#if defined(TABU_SPLAY)
dict_delete_all(tabu,NULL);
#endif

/*:123*/
#line 2763 "./jbmr.w"

}

/*:96*/
#line 2348 "./jbmr.w"

/*86:*/
#line 2386 "./jbmr.w"

if(more_backtracking){
if(best_gain>0&&scheme_num_cities[best_scheme_id]==6){
if(best_exit_a==t[5]&&best_exit_b==t[6]){
/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 2390 "./jbmr.w"

}else{
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2392 "./jbmr.w"

t[5]= best_exit_a;t[6]= best_exit_b;
scheme_id= best_scheme_id;
/*87:*/
#line 2409 "./jbmr.w"

{int i,n= scheme_max[scheme_id],*s= &scheme[scheme_id][0];
/*141:*/
#line 3475 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Implement scheme %d\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3479 "./jbmr.w"

fflush(stdout);
}
#endif

/*:141*/
#line 2411 "./jbmr.w"

for(i= 0;i<n;i+= 4){
tour_flip_arb(t[s[i]],t[s[i+1]],t[s[i+2]],t[s[i+3]]);
}
}

/*:87*/
#line 2395 "./jbmr.w"

}
/*76:*/
#line 1989 "./jbmr.w"

{int i;
for(i= 1;i<=best_two_i;i++){
mark_dirty(t[i]);
}
mark_dirty(best_exit_a);
mark_dirty(best_exit_b);
}

/*:76*//*77:*/
#line 2017 "./jbmr.w"

if(iteration>0){
const int more_log= 4+best_two_i;
/*78:*/
#line 2034 "./jbmr.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:78*/
#line 2020 "./jbmr.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


/*:77*/
#line 2397 "./jbmr.w"

/*163:*/
#line 3780 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 6;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3783 "./jbmr.w"

#endif

/*:163*/
#line 2398 "./jbmr.w"

more_backtracking= 0;
}else{
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2401 "./jbmr.w"

}
}

/*:86*/
#line 2349 "./jbmr.w"

}else{
#define BL 2
{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
const length_t cluster_dist= this_move->cluster_dist;
#else
const length_t cluster_dist= 0;
#endif
/*59:*/
#line 1596 "./jbmr.w"

en[BL]= ec[BL]= 0;
if(CAREFUL_OP(cum_gain,>,cluster_dist+best_gain)){
int i,t2ip1,t2ip2,enbl,*neighbour_list,nn_bound;
#if SPLIT_GAIN_VAR
length_t cum_1_pos,cum_1_neg,cum_2_pos,cum_2_neg;
#else
length_t cum_1,cum_2;
#endif
/*148:*/
#line 3555 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 400
if(verbose>=400){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3558 "./jbmr.w"

printf("%d %d "length_t_spec" "length_t_spec" s%d\n",t[two_i-1],t[two_i],
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_gain),
#else
length_t_pcast(cum_gain_pos-cum_gain_neg),
#endif
length_t_pcast(best_gain),scheme_id);
fflush(stdout);
}
#endif



/*:148*/
#line 1605 "./jbmr.w"



#if SPLIT_GAIN_VAR
cum_1_pos= cum_gain_pos;
#endif

neighbour_list= nn_list(t[two_i],&nn_bound);
for(i= 0,enbl= 0;i<nn_bound;i++){
t2ip1= neighbour_list[i];
#if SPLIT_GAIN_VAR
cum_1_neg= cum_gain_neg+cost(t[two_i],t2ip1);
#else
cum_1= cum_gain-cost(t[two_i],t2ip1);
#endif

if(CAREFUL_OP(cum_1,<=,best_gain)){
/*155:*/
#line 3677 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3680 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("Terminating |cum_1| "length_t_spec"\n",length_t_pcast(cum_1));
#else
printf("Terminating |cum_1| "length_t_spec" "
"(== "length_t_spec" - "length_t_spec")\n",
length_t_pcast(cum_1_pos-cum_1_neg),
length_t_pcast(cum_1_pos),
length_t_pcast(cum_1_neg));
#endif
fflush(stdout);
}
#endif

/*:155*/
#line 1622 "./jbmr.w"

num_reject_by_cum_1++;
break;
}

/*62:*/
#line 1650 "./jbmr.w"

#if BL==0
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 1652 "./jbmr.w"

#endif

/*:62*//*82:*/
#line 2092 "./jbmr.w"

#if BL==1
if(t2ip1!=t[3]){
switch(e[0][ec[0]].scheme_id){
case 0:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[3])?0:2;break;
case 4:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[4])?5:8;break;
default:errorif(1,"Non exhaustive switch: %d",e[0][ec[0]].scheme_id);
}
/*157:*/
#line 3724 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3727 "./jbmr.w"
printf("base_scheme5 == %d\n",base_scheme[5]);
fflush(stdout);
}
#endif

/*:157*/
#line 2100 "./jbmr.w"

/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2101 "./jbmr.w"

}
#endif


/*:82*//*89:*/
#line 2468 "./jbmr.w"

#if BL==2
if(t2ip1!=t[5]){
int i1,i2,i4;
switch(base_scheme[7]= e[1][ec[1]].scheme_id){
case 2:i1= 1;i2= 2;i4= 3;break;
case 5:i1= 6,i2= 5,i4= 4;break;
case 9:i1= 1,i2= 2,i4= 5;break;
default:errorif(1,"Got to 4-change in base scheme %d",base_scheme[7]);
i1= i2= i4= -1;
break;
}
if(tour_inorder(t[i1],t[i2],t2ip1,t[i4])){
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2481 "./jbmr.w"

}
}
#endif


/*:89*//*100:*/
#line 2821 "./jbmr.w"

#if BL==3
if(t[two_i]==tour_prev(t[1]))t2ip2= tour_next(t2ip1);
else t2ip2= tour_prev(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 2825 "./jbmr.w"

#endif


/*:100*/
#line 1627 "./jbmr.w"

}
en[BL]= enbl;
}else{
num_reject_pre_e_build++;
}

/*:59*/
#line 2358 "./jbmr.w"

}
/*71:*/
#line 1857 "./jbmr.w"

sort(e[BL],(size_t)en[BL],sizeof(eligible_t),cmp_eligible);

/*:71*/
#line 2360 "./jbmr.w"

#undef BL
/*94:*/
#line 2673 "./jbmr.w"

for(ec[2]= 0;more_backtracking&&ec[2]<en[2];ec[2]++){
eligible_t*this_move= &e[2][ec[2]];
t[7]= this_move->t2ip1;
t[8]= this_move->t2ip2;
#if !SPLIT_GAIN_VAR
cum_gain= this_move->gain;
#else
cum_gain_pos= this_move->gain_pos;
cum_gain_neg= this_move->gain_neg;
#endif
two_i= 8;
/*167:*/
#line 3808 "./jbmr.w"

#if TRACK_DEPTHS
if(probe_depth<two_i+2)(probe_depth= two_i+2);
#endif


/*:167*/
#line 2685 "./jbmr.w"

scheme_id= this_move->scheme_id;
/*87:*/
#line 2409 "./jbmr.w"

{int i,n= scheme_max[scheme_id],*s= &scheme[scheme_id][0];
/*141:*/
#line 3475 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Implement scheme %d\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3479 "./jbmr.w"

fflush(stdout);
}
#endif

/*:141*/
#line 2411 "./jbmr.w"

for(i= 0;i<n;i+= 4){
tour_flip_arb(t[s[i]],t[s[i+1]],t[s[i+2]],t[s[i+3]]);
}
}

/*:87*/
#line 2687 "./jbmr.w"

/*96:*/
#line 2736 "./jbmr.w"

{int go_deeper;
last_special_two_i= two_i;
generic_flips_made= 0;
/*114:*/
#line 3133 "./jbmr.w"


/*:114*//*121:*/
#line 3213 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{
int i;
for(i= 2;i<two_i;i+= 2)dict_insert(tabu,t+i);
}
#endif

/*:121*/
#line 2740 "./jbmr.w"

/*139:*/
#line 3454 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 175
if(verbose>=175){
printf("Start generic search\n");
fflush(stdout);
}
#endif


/*:139*/
#line 2741 "./jbmr.w"

for(go_deeper= 1;go_deeper;){
/*97:*/
#line 2770 "./jbmr.w"

#if defined(JBMR_LIMIT_PROBE_DEPTH)
if(generic_flips_made>=max_generic_flips){
/*179:*/
#line 3918 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 75
if(verbose>=75){
printf(" hit max generic flips: %d >= %d\n",
generic_flips_made,max_generic_flips);
}
#endif

/*:179*/
#line 2773 "./jbmr.w"

/*105:*/
#line 2963 "./jbmr.w"

if(best_gain==0){
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2965 "./jbmr.w"

}else if(best_scheme_id==13){
/*106:*/
#line 2974 "./jbmr.w"

{
int low_j,best_is_prefix;
errorif(best_gain<=0,"Bad best_scheme_id == 13");
best_is_prefix= t[best_two_i+1]==best_exit_a
&&t[best_two_i+2]==best_exit_b;
low_j= best_two_i+(best_is_prefix?2:0);
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 2981 "./jbmr.w"

if(!best_is_prefix){
tour_flip_arb(t[1],t[best_two_i],best_exit_a,best_exit_b);
}
/*76:*/
#line 1989 "./jbmr.w"

{int i;
for(i= 1;i<=best_two_i;i++){
mark_dirty(t[i]);
}
mark_dirty(best_exit_a);
mark_dirty(best_exit_b);
}

/*:76*//*77:*/
#line 2017 "./jbmr.w"

if(iteration>0){
const int more_log= 4+best_two_i;
/*78:*/
#line 2034 "./jbmr.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:78*/
#line 2020 "./jbmr.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


/*:77*/
#line 2985 "./jbmr.w"

/*165:*/
#line 3794 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= best_two_i+2;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3797 "./jbmr.w"

#endif

/*:165*/
#line 2986 "./jbmr.w"

more_backtracking= 0;
}

/*:106*/
#line 2967 "./jbmr.w"

}

/*:105*/
#line 2774 "./jbmr.w"

go_deeper= 0;
break;
}
#endif

/*:97*/
#line 2743 "./jbmr.w"

/*167:*/
#line 3808 "./jbmr.w"

#if TRACK_DEPTHS
if(probe_depth<two_i+2)(probe_depth= two_i+2);
#endif


/*:167*/
#line 2744 "./jbmr.w"

/*29:*/
#line 828 "./jbmr.w"

if(two_i+3>=t_max_alloc){
#if defined(TABU_SPLAY)
int*old_t= t;
#endif
do{
t_max_alloc*= 2;
}while(two_i+3>=t_max_alloc);
t= (int*)mem_realloc(t,sizeof(int)*t_max_alloc);
/*124:*/
#line 3266 "./jbmr.w"

#if defined(TABU_SPLAY)
{int*env[2];
env[0]= old_t;
env[1]= t;
dict_update_all(tabu,move_t,env);
}
#endif

/*:124*/
#line 837 "./jbmr.w"

}


/*:29*/
#line 2745 "./jbmr.w"

#define BL 3
{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
const length_t cluster_dist= decluster_d(t[1],t[two_i]);
#else
const length_t cluster_dist= 0;
#endif
/*59:*/
#line 1596 "./jbmr.w"

en[BL]= ec[BL]= 0;
if(CAREFUL_OP(cum_gain,>,cluster_dist+best_gain)){
int i,t2ip1,t2ip2,enbl,*neighbour_list,nn_bound;
#if SPLIT_GAIN_VAR
length_t cum_1_pos,cum_1_neg,cum_2_pos,cum_2_neg;
#else
length_t cum_1,cum_2;
#endif
/*148:*/
#line 3555 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 400
if(verbose>=400){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3558 "./jbmr.w"

printf("%d %d "length_t_spec" "length_t_spec" s%d\n",t[two_i-1],t[two_i],
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_gain),
#else
length_t_pcast(cum_gain_pos-cum_gain_neg),
#endif
length_t_pcast(best_gain),scheme_id);
fflush(stdout);
}
#endif



/*:148*/
#line 1605 "./jbmr.w"



#if SPLIT_GAIN_VAR
cum_1_pos= cum_gain_pos;
#endif

neighbour_list= nn_list(t[two_i],&nn_bound);
for(i= 0,enbl= 0;i<nn_bound;i++){
t2ip1= neighbour_list[i];
#if SPLIT_GAIN_VAR
cum_1_neg= cum_gain_neg+cost(t[two_i],t2ip1);
#else
cum_1= cum_gain-cost(t[two_i],t2ip1);
#endif

if(CAREFUL_OP(cum_1,<=,best_gain)){
/*155:*/
#line 3677 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3680 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("Terminating |cum_1| "length_t_spec"\n",length_t_pcast(cum_1));
#else
printf("Terminating |cum_1| "length_t_spec" "
"(== "length_t_spec" - "length_t_spec")\n",
length_t_pcast(cum_1_pos-cum_1_neg),
length_t_pcast(cum_1_pos),
length_t_pcast(cum_1_neg));
#endif
fflush(stdout);
}
#endif

/*:155*/
#line 1622 "./jbmr.w"

num_reject_by_cum_1++;
break;
}

/*62:*/
#line 1650 "./jbmr.w"

#if BL==0
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 1652 "./jbmr.w"

#endif

/*:62*//*82:*/
#line 2092 "./jbmr.w"

#if BL==1
if(t2ip1!=t[3]){
switch(e[0][ec[0]].scheme_id){
case 0:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[3])?0:2;break;
case 4:base_scheme[5]= tour_inorder(t[1],t[2],t2ip1,t[4])?5:8;break;
default:errorif(1,"Non exhaustive switch: %d",e[0][ec[0]].scheme_id);
}
/*157:*/
#line 3724 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3727 "./jbmr.w"
printf("base_scheme5 == %d\n",base_scheme[5]);
fflush(stdout);
}
#endif

/*:157*/
#line 2100 "./jbmr.w"

/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2101 "./jbmr.w"

}
#endif


/*:82*//*89:*/
#line 2468 "./jbmr.w"

#if BL==2
if(t2ip1!=t[5]){
int i1,i2,i4;
switch(base_scheme[7]= e[1][ec[1]].scheme_id){
case 2:i1= 1;i2= 2;i4= 3;break;
case 5:i1= 6,i2= 5,i4= 4;break;
case 9:i1= 1,i2= 2,i4= 5;break;
default:errorif(1,"Got to 4-change in base scheme %d",base_scheme[7]);
i1= i2= i4= -1;
break;
}
if(tour_inorder(t[i1],t[i2],t2ip1,t[i4])){
/*63:*/
#line 1678 "./jbmr.w"

#if defined(JBMR_UNROLL_PREV_NEXT_LOOP)
#error "JBMR_UNROLL_PREV_NEXT_LOOP is not implemented"
#else
{int which_neighbour;
for(which_neighbour= 0;which_neighbour<2;which_neighbour++){
t2ip2= (tour_neighbour[which_neighbour])(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 1685 "./jbmr.w"

}
}
#endif

/*:63*/
#line 2481 "./jbmr.w"

}
}
#endif


/*:89*//*100:*/
#line 2821 "./jbmr.w"

#if BL==3
if(t[two_i]==tour_prev(t[1]))t2ip2= tour_next(t2ip1);
else t2ip2= tour_prev(t2ip1);
/*66:*/
#line 1709 "./jbmr.w"

#if BL==0
if(t[2]!=t2ip2){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 1712 "./jbmr.w"

}
#endif

/*:66*//*83:*/
#line 2157 "./jbmr.w"

#if BL==1
if(!(
(t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int is_illegal= 0;
switch(base_scheme[5]){
case 0:

if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 0;




is_illegal= t[2]==t2ip1||t[1]==t2ip2;
}else{
base_scheme[6]= 1;





is_illegal= t[2]==t2ip2||t[1]==t2ip1||t[4]==t2ip2
||t[1]==t2ip2;
}
break;
case 2:
base_scheme[6]= 2;
is_illegal= tour_inorder(t[3],t[4],t2ip1,t2ip2);







break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[6]= 5;











}else{
base_scheme[6]= 7;




is_illegal= t2ip2==t[1]||t[1]==t[4];
}
break;
case 8:
if(tour_inorder(t[4],t[3],t2ip2,t2ip1)){
base_scheme[6]= 8;













}else{
base_scheme[6]= 9;










is_illegal= t2ip2==t[2];
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[5]);
}
if(!is_illegal){
/*158:*/
#line 3733 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 1000
if(verbose>=1000){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3736 "./jbmr.w"
printf("base_scheme6 == %d\n",base_scheme[6]);
fflush(stdout);
}
#endif


/*:158*/
#line 2253 "./jbmr.w"

/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2254 "./jbmr.w"

}
}
#endif 

/*:83*//*90:*/
#line 2535 "./jbmr.w"

#if BL==2
if(!(
(t2ip2==t[6])
||(t2ip1==t[4]&&t2ip2==t[5])
||(t2ip1==t[5]&&t2ip2==t[4])
||(t2ip1==t[2]&&t2ip2==t[3])
||(t2ip1==t[3]&&t2ip2==t[2]))){
int infeasible_4_change,is_illegal= 0;
switch(base_scheme[7]){
case 2:
if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 2;
is_illegal= t2ip2==t[4]||t2ip2==t[1];
}else{
base_scheme[8]= 3;


}
break;
case 5:
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 5;


}else{
base_scheme[8]= 6;
is_illegal= t2ip2==t[3];


}
break;
case 9:
if(tour_inorder(t[1],t[2],t2ip1,t[4])){
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
base_scheme[8]= 9;





}else{
base_scheme[8]= 10;
is_illegal= t2ip2==t[3];



}
}else{




if(tour_inorder(t[1],t[2],t2ip1,t2ip2)){
base_scheme[8]= 11;
is_illegal= t2ip2==t[6];


}else{
base_scheme[8]= 12;
is_illegal= t2ip2==t[4];


}
}
break;
default:errorif(1,"Non-exhaustive switch: %d",base_scheme[7]);
}
if(!is_illegal){
/*91:*/
#line 2616 "./jbmr.w"

{int i,*sc,sn;
t[7]= t2ip1;
t[8]= t2ip2;
infeasible_4_change= 0;
sc= &scheme_feas_check[base_scheme[8]][0];
sn= scheme_feas_n[base_scheme[8]];
for(i= 0;i<sn;i+= 2){
if(t[sc[i]]==t[sc[i+1]]){infeasible_4_change= 1;break;}
}
}

/*:91*/
#line 2604 "./jbmr.w"

if(!infeasible_4_change){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2606 "./jbmr.w"

}
}
}
#endif

/*:90*//*102:*/
#line 2876 "./jbmr.w"

#if BL==3
if(t2ip2!=t[1]&&t2ip2!=t[two_i]){
int is_tabu= 0;
/*113:*/
#line 3112 "./jbmr.w"

#if defined(TABU_LINEAR)
#if defined(TABU_JBMR)
{
int i;
for(i= 2,is_tabu= 0;i<two_i;i+= 2){
if((t2ip1==t[i]&&t2ip2==t[i+1])
||(t2ip1==t[i+1]&&t2ip2==t[i])){
is_tabu= 1;
break;
}
}
}
#elif defined(TABU_Papadimitriou)
{errorif(1,"TABU_Papadimitriou is not implemented yet");}
#else
#error "Need one of TABU_JBMR or TABU_Papadimitriou defined"
#endif
#endif 

/*:113*//*120:*/
#line 3195 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
{int edge[2];
if(t2ip1<t2ip2){edge[0]= t2ip2;edge[1]= t2ip1;}
else{edge[0]= t2ip1;edge[1]= t2ip2;}
is_tabu= dict_find(tabu,edge)!=NULL;
}
#endif

/*:120*/
#line 2880 "./jbmr.w"

if(!is_tabu){
/*67:*/
#line 1722 "./jbmr.w"

{
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST || JBMR_DECLUSTER_IN_GREEDY
const length_t cluster_dist= decluster_d(t[1],t2ip2);
/*151:*/
#line 3637 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 501 && (JBMR_DECLUSTER_IN_ELIGIBILITY_TEST||JBMR_DECLUSTER_IN_GREEDY)
if(verbose>=501){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3640 "./jbmr.w"

printf(" v---- next clust_dist==%f\n",(double)cluster_dist);
}
#endif

/*:151*/
#line 1726 "./jbmr.w"

#endif

#if !SPLIT_GAIN_VAR
cum_2= cum_1+cost(t2ip1,t2ip2);
#else 
cum_2_pos= cum_1_pos+cost(t2ip1,t2ip2);
cum_2_neg= cum_1_neg;
#endif 

#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
if(CAREFUL_OP(cum_2,<,cluster_dist+best_gain)){
/*152:*/
#line 3646 "./jbmr.w"

#if JBMR_MAX_VERBOSE
num_reject_by_decluster++;
#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3651 "./jbmr.w"

printf("%d: %d %d "length_t_spec" s%d rejected (#%d), clust_dist==%f\n",
enbl,t2ip1,t2ip2,
#if !SPLIT_GAIN_VAR
length_t_pcast(cum_2),
#else
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id,
num_reject_by_decluster,
(double)cluster_dist);
fflush(stdout);
}
#endif
#endif

/*:152*/
#line 1738 "./jbmr.w"

}else
#endif

{
/*69:*/
#line 1792 "./jbmr.w"

#if BL==0
if(tour_inorder(t[1],t[2],t2ip2,t2ip1)){
e[BL][enbl].scheme_id= 4;
if(t[1]!=t[4]){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 1797 "./jbmr.w"

}
}else{
e[BL][enbl].scheme_id= 0;
}
#endif



/*:69*//*84:*/
#line 2318 "./jbmr.w"

#if BL==1
if(scheme_num_cities[e[BL][enbl].scheme_id= base_scheme[6]]==6){
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2321 "./jbmr.w"

}
#endif

/*:84*//*93:*/
#line 2656 "./jbmr.w"

#if BL==2
e[BL][enbl].scheme_id= base_scheme[8];
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2659 "./jbmr.w"

#endif

/*:93*//*103:*/
#line 2891 "./jbmr.w"

#if BL==3
e[BL][enbl].scheme_id= 13;
/*70:*/
#line 1814 "./jbmr.w"

{const length_t cost_phantom= cost(t[1],t2ip2);
#if !SPLIT_GAIN_VAR
const length_t cum_exit_now= cum_2-cost_phantom;
#endif

if(
#if LENGTH_TYPE_IS_EXACT
cum_exit_now>best_gain
#elif SPLIT_GAIN_VAR
cum_2_pos>best_gain_with_slop+cum_2_neg+cost_phantom
#else
cum_exit_now>best_gain_with_slop
#endif
)
{

#if SPLIT_GAIN_VAR
best_gain= cum_2_pos-cum_2_neg-cost_phantom;
#else
best_gain= cum_exit_now;
#endif
#if !LENGTH_TYPE_IS_EXACT
best_gain_with_slop= best_gain+instance_epsilon;
#endif

best_two_i= two_i;
best_exit_a= t2ip1;
best_exit_b= t2ip2;
best_scheme_id= e[BL][enbl].scheme_id;
/*140:*/
#line 3464 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 200
if(verbose>=200){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3467 "./jbmr.w"

printf("best_gain = "length_t_spec" %d %d s%d\n",
length_t_pcast(best_gain),best_exit_a,best_exit_b,best_scheme_id);
fflush(stdout);
}
#endif

/*:140*/
#line 1844 "./jbmr.w"

}
}

/*:70*/
#line 2894 "./jbmr.w"

#endif

/*:103*/
#line 1743 "./jbmr.w"

e[BL][enbl].t2ip1= t2ip1;
e[BL][enbl].t2ip2= t2ip2;

#if !SPLIT_GAIN_VAR
e[BL][enbl].gain_for_comparison= e[BL][enbl].gain= cum_2;
#else
e[BL][enbl].gain_for_comparison= cum_2_pos-cum_2_neg;
e[BL][enbl].gain_pos= cum_2_pos;
e[BL][enbl].gain_neg= cum_2_neg;
#endif

#if JBMR_DECLUSTER_IN_GREEDY
# if BL<3
e[BL][enbl].gain_for_comparison-= cluster_dist;
# else
e[BL][enbl].cluster_dist= cluster_dist;
# endif
#endif

/*150:*/
#line 3616 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3619 "./jbmr.w"

#if !SPLIT_GAIN_VAR
printf("%d: %d %d "length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2),
#else
printf("%d: %d %d "length_t_spec"-"length_t_spec"="length_t_spec" s%d\n",
enbl,t2ip1,t2ip2,
length_t_pcast(cum_2_pos),
length_t_pcast(cum_2_neg),
length_t_pcast(cum_2_pos-cum_2_neg),
#endif
e[BL][enbl].scheme_id);
fflush(stdout);
}
#endif

/*:150*/
#line 1763 "./jbmr.w"

enbl++;
}
}

/*:67*/
#line 2882 "./jbmr.w"

}
}
#endif


/*:102*/
#line 2825 "./jbmr.w"

#endif


/*:100*/
#line 1627 "./jbmr.w"

}
en[BL]= enbl;
}else{
num_reject_pre_e_build++;
}

/*:59*/
#line 2753 "./jbmr.w"

}
#undef BL
if(en[3]>0){
/*104:*/
#line 2907 "./jbmr.w"

{int i,best_i= -1;
#if !SPLIT_GAIN_VAR
length_t best_len= 0;
#else
length_t best_len_pos= 0,best_len_neg= 0;
#endif
/*156:*/
#line 3695 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 500
if(verbose>=500){
int i;
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3699 "./jbmr.w"
printf("go deeper candidates begin\n");
for(i= 0;i<en[3];i++){
#if !SPLIT_GAIN_VAR
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3702 "./jbmr.w"
printf("%d %d "length_t_spec" s%d\n",
e[3][i].t2ip1,
e[3][i].t2ip2,
length_t_pcast(e[3][i].gain),
e[3][i].scheme_id);
#else
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3708 "./jbmr.w"
printf("%d %d "length_t_spec" (=="length_t_spec"-"
length_t_spec") s%d\n",
e[3][i].t2ip1,
e[3][i].t2ip2,
length_t_pcast(e[3][i].gain_pos-e[3][i].gain_neg),
length_t_pcast(e[3][i].gain_pos),
length_t_pcast(e[3][i].gain_neg),
e[3][i].scheme_id);
#endif
}
/*159:*/
#line 3743 "./jbmr.w"

#if JBMR_MAX_VERBOSE
{int i;for(i= 0;i<two_i;i++)printf(" ");}
#endif

/*:159*/
#line 3718 "./jbmr.w"
printf("go deeper candidates end\n");
fflush(stdout);
}
#endif

/*:156*/
#line 2914 "./jbmr.w"

for(i= 0;i<en[3];i++){
if(
#if JBMR_DECLUSTER_IN_GREEDY
e[3][i].cluster_dist+
#endif
#if !SPLIT_GAIN_VAR
best_len<e[3][i].gain
#else
best_len_pos+e[3][i].gain_neg<best_len_neg+e[3][i].gain_pos
#endif
)
{
best_i= i;
#if !SPLIT_GAIN_VAR
best_len= e[3][i].gain;
#else
best_len_pos= e[3][i].gain_pos;
best_len_neg= e[3][i].gain_neg;
#endif
}
}
errorif(best_i==-1,"Shouldn't be going deeper.");
#if !SPLIT_GAIN_VAR
cum_gain= best_len;
#else
cum_gain_pos= best_len_pos;
cum_gain_neg= best_len_neg;
#endif
t[two_i+1]= e[3][best_i].t2ip1;
t[two_i+2]= e[3][best_i].t2ip2;
tour_flip_arb(t[1],t[two_i],t[two_i+1],t[two_i+2]);
/*115:*/
#line 3136 "./jbmr.w"


/*:115*//*122:*/
#line 3222 "./jbmr.w"

#if defined(TABU_SPLAY) && defined(TABU_JBMR)
dict_insert(tabu,t+two_i);
#endif

/*:122*/
#line 2946 "./jbmr.w"

two_i+= 2;
generic_flips_made++;
/*137:*/
#line 3435 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips made: %d\n",generic_flips_made);
fflush(stdout);
}
#endif

/*:137*/
#line 2949 "./jbmr.w"

}

/*:104*/
#line 2757 "./jbmr.w"

}else{
/*105:*/
#line 2963 "./jbmr.w"

if(best_gain==0){
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2965 "./jbmr.w"

}else if(best_scheme_id==13){
/*106:*/
#line 2974 "./jbmr.w"

{
int low_j,best_is_prefix;
errorif(best_gain<=0,"Bad best_scheme_id == 13");
best_is_prefix= t[best_two_i+1]==best_exit_a
&&t[best_two_i+2]==best_exit_b;
low_j= best_two_i+(best_is_prefix?2:0);
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 2981 "./jbmr.w"

if(!best_is_prefix){
tour_flip_arb(t[1],t[best_two_i],best_exit_a,best_exit_b);
}
/*76:*/
#line 1989 "./jbmr.w"

{int i;
for(i= 1;i<=best_two_i;i++){
mark_dirty(t[i]);
}
mark_dirty(best_exit_a);
mark_dirty(best_exit_b);
}

/*:76*//*77:*/
#line 2017 "./jbmr.w"

if(iteration>0){
const int more_log= 4+best_two_i;
/*78:*/
#line 2034 "./jbmr.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:78*/
#line 2020 "./jbmr.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


/*:77*/
#line 2985 "./jbmr.w"

/*165:*/
#line 3794 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= best_two_i+2;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3797 "./jbmr.w"

#endif

/*:165*/
#line 2986 "./jbmr.w"

more_backtracking= 0;
}

/*:106*/
#line 2967 "./jbmr.w"

}

/*:105*/
#line 2759 "./jbmr.w"

go_deeper= 0;
}
}
/*116:*/
#line 3139 "./jbmr.w"


/*:116*//*123:*/
#line 3231 "./jbmr.w"

#if defined(TABU_SPLAY)
dict_delete_all(tabu,NULL);
#endif

/*:123*/
#line 2763 "./jbmr.w"

}

/*:96*/
#line 2688 "./jbmr.w"

/*95:*/
#line 2702 "./jbmr.w"

if(more_backtracking){
if(best_gain>0&&scheme_num_cities[best_scheme_id]==8){
if(best_exit_a==t[7]&&best_exit_b==t[8]){
/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 2706 "./jbmr.w"

}else{
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2708 "./jbmr.w"

t[7]= best_exit_a;t[8]= best_exit_b;
scheme_id= best_scheme_id;
/*87:*/
#line 2409 "./jbmr.w"

{int i,n= scheme_max[scheme_id],*s= &scheme[scheme_id][0];
/*141:*/
#line 3475 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Implement scheme %d\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3479 "./jbmr.w"

fflush(stdout);
}
#endif

/*:141*/
#line 2411 "./jbmr.w"

for(i= 0;i<n;i+= 4){
tour_flip_arb(t[s[i]],t[s[i+1]],t[s[i+2]],t[s[i+3]]);
}
}

/*:87*/
#line 2711 "./jbmr.w"

}
/*76:*/
#line 1989 "./jbmr.w"

{int i;
for(i= 1;i<=best_two_i;i++){
mark_dirty(t[i]);
}
mark_dirty(best_exit_a);
mark_dirty(best_exit_b);
}

/*:76*//*77:*/
#line 2017 "./jbmr.w"

if(iteration>0){
const int more_log= 4+best_two_i;
/*78:*/
#line 2034 "./jbmr.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:78*/
#line 2020 "./jbmr.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


/*:77*/
#line 2713 "./jbmr.w"

/*164:*/
#line 3787 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 8;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3790 "./jbmr.w"

#endif

/*:164*/
#line 2714 "./jbmr.w"

more_backtracking= 0;
}else{
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 2717 "./jbmr.w"

}
}

/*:95*/
#line 2689 "./jbmr.w"

}

/*:94*/
#line 2362 "./jbmr.w"

}
}


/*:85*/
#line 1964 "./jbmr.w"

/*75:*/
#line 1974 "./jbmr.w"

if(best_scheme_id==4){
/*109:*/
#line 3018 "./jbmr.w"

/*108:*/
#line 3009 "./jbmr.w"

if(generic_flips_made){
int low_j= last_special_two_i;
/*107:*/
#line 2994 "./jbmr.w"

{int j;
errorif(low_j<last_special_two_i,"Generic broken! caught at unrolling time");
for(j= two_i;j>low_j;j-= 2){
/*145:*/
#line 3528 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 350
if(verbose>=350){
printf("Rollback generic flip(t%d t%d t%d t%d)\n",1,j,j-1,j-2);
fflush(stdout);
}
#endif

/*:145*/
#line 2998 "./jbmr.w"

tour_flip_arb(t[1],t[j],t[j-1],t[j-2]);
}
generic_flips_made= (low_j-last_special_two_i)/2;
/*138:*/
#line 3444 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 150
if(verbose>=150){
printf("Generic flips remain after rollback: %d\n",generic_flips_made);
fflush(stdout);
}
#endif


/*:138*/
#line 3002 "./jbmr.w"

}

/*:107*/
#line 3012 "./jbmr.w"

}

/*:108*/
#line 3019 "./jbmr.w"

/*110:*/
#line 3030 "./jbmr.w"

if(scheme_id>=0){
int j,*s= scheme[scheme_id];
/*142:*/
#line 3485 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Unrolling the scheme %d changes\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3489 "./jbmr.w"

fflush(stdout);
}
#endif

/*:142*/
#line 3033 "./jbmr.w"

for(j= scheme_max[scheme_id]-4;j>=0;j-= 4){
tour_flip_arb(t[s[j]],t[s[j+3]],t[s[j+2]],t[s[j+1]]);
}
scheme_id= -1;
/*166:*/
#line 3801 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 0;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3804 "./jbmr.w"

#endif

/*:166*/
#line 3038 "./jbmr.w"

}

/*:110*/
#line 3020 "./jbmr.w"


/*:109*/
#line 1976 "./jbmr.w"

t[3]= best_exit_a;t[4]= best_exit_b;
scheme_id= 4;
/*87:*/
#line 2409 "./jbmr.w"

{int i,n= scheme_max[scheme_id],*s= &scheme[scheme_id][0];
/*141:*/
#line 3475 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
printf("Implement scheme %d\n",scheme_id);
/*143:*/
#line 3495 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 300
if(verbose>=300){
int i;
length_t c= 0,b= 0;
printf("t: ");
for(i= 1;i<=two_i;i++){
if(i%2){
if(i>1)c-= cost(t[i],t[i-1]);
}else{
c+= cost(t[i],t[i-1]);
}
printf("%d ",t[i]);
}
b= c-cost(t[1],t[two_i]);
printf(length_t_spec" ",length_t_pcast(c));
printf(length_t_spec"\n",length_t_pcast(b));
fflush(stdout);
}
#endif



/*:143*/
#line 3479 "./jbmr.w"

fflush(stdout);
}
#endif

/*:141*/
#line 2411 "./jbmr.w"

for(i= 0;i<n;i+= 4){
tour_flip_arb(t[s[i]],t[s[i+1]],t[s[i+2]],t[s[i+3]]);
}
}

/*:87*/
#line 1979 "./jbmr.w"

/*76:*/
#line 1989 "./jbmr.w"

{int i;
for(i= 1;i<=best_two_i;i++){
mark_dirty(t[i]);
}
mark_dirty(best_exit_a);
mark_dirty(best_exit_b);
}

/*:76*//*77:*/
#line 2017 "./jbmr.w"

if(iteration>0){
const int more_log= 4+best_two_i;
/*78:*/
#line 2034 "./jbmr.w"

if(more_log>=change_log_max_alloc){
do{
change_log_max_alloc*= 2;
}while(more_log>=change_log_max_alloc);
change_log= (int*)mem_realloc(change_log,sizeof(int)*change_log_max_alloc);
}

/*:78*/
#line 2020 "./jbmr.w"

{int j;
for(j= 1;j<=best_two_i;j++){
write_log(t[j]);
}
}
write_log(best_exit_a);
write_log(best_exit_b);
write_log(scheme_id);
write_log(3+best_two_i);
}


/*:77*/
#line 1980 "./jbmr.w"

/*162:*/
#line 3773 "./jbmr.w"

#if TRACK_DEPTHS
move_depth= 4;
/*170:*/
#line 3827 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 125
if(verbose>=125){
printf("Move_stats: %d %d %d\n",probes,move_depth,probe_depth);
fflush(stdout);
probes++;
}
#endif
#if TRACK_DEPTHS
last_probe_depth= probe_depth;
p_depths[probe_depth]++;
m_depths[move_depth]++;
move_depth= probe_depth= 0;
#endif


/*:170*/
#line 3776 "./jbmr.w"

#endif

/*:162*/
#line 1981 "./jbmr.w"

more_backtracking= 0;
}

/*:75*/
#line 1965 "./jbmr.w"

}

/*:74*/
#line 1389 "./jbmr.w"


/*:48*/
#line 1307 "./jbmr.w"

}
if(best_gain>0){
incumbent_len-= best_gain;
/*133:*/
#line 3381 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 50
if(verbose>=50){
static double last_time= 0.0;
const double this_time= resource_user_tick();
printf("=== improve by "length_t_spec" to "length_t_spec,
length_t_pcast(best_gain),length_t_pcast(incumbent_len));
printf("  after %.3f (+ %.3f) sec\n",this_time,this_time-last_time);
last_time= this_time;
fflush(stdout);
}
#endif


/*:133*/
#line 1311 "./jbmr.w"

/*126:*/
#line 3297 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 25
if(lower_bound_name&&verbose>=25){
double this_time= 0;
if(incumbent_len<=milestone_value)this_time= resource_user_tick();
while(incumbent_len<=milestone_value&&milestone<num_milestones){
printf("Milestone: %4.2f%% above %s after %.2f (+ %.2f) sec\n",
milestone_percentage[milestone]*100,
lower_bound_name,
this_time,
this_time==milestone_time?0:this_time-milestone_time);
milestone_time= this_time;
milestone++;
if(milestone<num_milestones)
milestone_value= lower_bound_value*(1+milestone_percentage[milestone]);
}
fflush(stdout);
}
#endif

/*:126*/
#line 1312 "./jbmr.w"

/*57:*/
#line 1532 "./jbmr.w"

#if !(LENGTH_TYPE_IS_EXACT)
instance_epsilon= incumbent_len*LENGTH_MACHINE_EPSILON;
#endif

/*:57*/
#line 1313 "./jbmr.w"

}
}

/*:45*/
#line 714 "./jbmr.w"

}
/*194:*/
#line 4143 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 40
if(verbose>=40){
printf("End of LK step %d, incumbent_len = "length_t_spec"\n",
iteration+1,
length_t_pcast(incumbent_len));
}
#endif

/*:194*/
#line 716 "./jbmr.w"

/*180:*/
#line 3937 "./jbmr.w"

if(iteration>0&&change_log_next>0&&previous_incumbent_len<incumbent_len){
/*196:*/
#line 4162 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 57
if(verbose>=57){
printf("Reverting to previous\n");
}
#endif

/*:196*/
#line 3939 "./jbmr.w"

while(change_log_next>0){
/*182:*/
#line 3976 "./jbmr.w"

{
const int len= change_log[change_log_next-1],
revert_scheme_id= change_log[change_log_next-2],
first_pos= change_log_next-1-len,
first_generic_pos= first_pos+scheme_num_cities[revert_scheme_id],
t1= change_log[first_pos],*st= (&change_log[first_pos])-1;
int j,si,*s= &scheme[revert_scheme_id][0];
/*197:*/
#line 4170 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 65
if(verbose>=65){
printf("  first_pos = %d change_log_next = %d\n",first_pos,change_log_next);
}
#endif

/*:197*/
#line 3984 "./jbmr.w"

errorif(first_pos<0,"Bug!");
for(j= change_log_next-4;j>=first_generic_pos;j-= 2){
tour_flip_arb(t1,change_log[j+1],change_log[j],change_log[j-1]);
}
for(si= scheme_max[revert_scheme_id]-4;si>=0;si-= 4){
tour_flip_arb(st[s[si]],st[s[si+3]],st[s[si+2]],st[s[si+1]]);
}
}

/*:182*/
#line 3941 "./jbmr.w"

change_log_next-= change_log[change_log_next-1]+1;
}
errorif(change_log_next!=0,"Bug!");
/*193:*/
#line 4136 "./jbmr.w"

{int i;
for(i= 8;i>=0;i-= 4)
tour_flip_arb(mutation[i],mutation[i+3],mutation[i+2],mutation[i+1]);
}

/*:193*/
#line 3945 "./jbmr.w"

incumbent_len= previous_incumbent_len;
}
change_log_next= 0;

/*:180*/
#line 717 "./jbmr.w"

/*183:*/
#line 3999 "./jbmr.w"

if(iteration<iterations-1){
int edge[4][2];
previous_incumbent_len= incumbent_len;
/*184:*/
#line 4012 "./jbmr.w"

{
int ok,count= 0;
do{
int i,j;
errorif(count++>1000,"Ummm, random double-bridge search didn't stop after 1000 tries");
for(i= 0,ok= 1;ok&&i<4;i++){
edge[i][0]= prng_unif_int(random_stream,(long)n);
edge[i][1]= tour_next(edge[i][0]);
for(j= 0;ok&&j<i;j++){
if(edge[j][0]==edge[i][0])ok= 0;
}
}
}while(!ok);
}

/*:184*//*185:*/
#line 4029 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 60
if(verbose>=60){
int i;
printf("Doing double-bridge: ");
for(i= 0;i<4;i++)printf("%d(%d,%d) ",i,edge[i][0],edge[i][1]);
printf("\n");
}
#endif

/*:185*/
#line 4003 "./jbmr.w"

/*186:*/
#line 4046 "./jbmr.w"

{int bottom,rock;
for(bottom= 3;bottom>1;bottom--){
for(rock= 1;rock<bottom;rock++){
if(bridge_less(edge[rock],edge[rock+1])){
swap_bridge(edge[rock],edge[rock+1]);
}
}
}
}


/*:186*/
#line 4004 "./jbmr.w"

/*187:*/
#line 4065 "./jbmr.w"

bridge_move(1,2,6,5);
bridge_move(8,7,4,3);
bridge_move(1,5,2,6);

/*:187*//*188:*/
#line 4075 "./jbmr.w"

{int mutation_next= 0;
mutate(1);
mutate(2);
mutate(6);
mutate(5);

mutate(8);
mutate(7);
mutate(4);
mutate(3);

mutate(1);
mutate(5);
mutate(2);
mutate(6);
}

/*:188*//*189:*/
#line 4098 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 60
#define bc(a,b) (<erbose: print double bridge edge |(a,b)|,
cost(bridge_t(a),bridge_t(b)))
#else
#define bc(a,b) (cost(bridge_t(a),bridge_t(b)))
#endif

incumbent_len+= bc(1,6);
incumbent_len+= bc(2,5);
incumbent_len+= bc(4,7);
incumbent_len+= bc(3,8);
incumbent_len-= bc(1,2);
incumbent_len-= bc(3,4);
incumbent_len-= bc(5,6);
incumbent_len-= bc(7,8);

/*:189*//*191:*/
#line 4124 "./jbmr.w"

{int i;
for(i= 1;i<=8;i++)
mark_dirty(bridge_t(i));
}


/*:191*/
#line 4005 "./jbmr.w"

}
/*195:*/
#line 4153 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 60
if(verbose>=60){
printf("+++incumbent_len is now "length_t_spec"\n",length_t_pcast(incumbent_len));
}
#endif


/*:195*/
#line 4007 "./jbmr.w"




/*:183*/
#line 718 "./jbmr.w"

}
/*134:*/
#line 3396 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 20
if(verbose>=20){
const double lk_time= resource_user_tick();
const double ds_time= resource_user_tick_from(begin_data_structures_mark);
printf("LK phase ended with incumbent_len == "length_t_spec
" after %.3f sec for LK and %.3f sec for ds+LK\n",
length_t_pcast(incumbent_len),lk_time,ds_time);
fflush(stdout);
}
#endif

/*:134*/
#line 720 "./jbmr.w"

/*131:*/
#line 3358 "./jbmr.w"

#if JBMR_MAX_VERBOSE >= 25
if(lower_bound_name&&verbose>=25&&lower_bound_value>1e-5){
printf("Final milestone: %.2f%% above %s\n",
100*(incumbent_len-lower_bound_value)/lower_bound_value,lower_bound_name);
fflush(stdout);
}
#endif


/*:131*/
#line 721 "./jbmr.w"

/*25:*/
#line 776 "./jbmr.w"

dict_destroy(dirty_set,NULL);


/*:25*//*28:*/
#line 815 "./jbmr.w"

free_mem(t);

/*:28*//*52:*/
#line 1447 "./jbmr.w"

free_mem(e[0]);
free_mem(e[1]);
free_mem(e[2]);
free_mem(e[3]);

/*:52*//*80:*/
#line 2049 "./jbmr.w"

free_mem(change_log);


/*:80*/
#line 722 "./jbmr.w"

/*176:*/
#line 3889 "./jbmr.w"

/*175:*/
#line 3873 "./jbmr.w"

#if TRACK_DEPTHS
{int i,j;
for(i= DEPTHS_BOUND-1;p_depths[i]!=0;i--);
for(j= 0;j<=i;j++){
if(p_depths[j])printf("p %d citydeep %d\n",j,p_depths[j]);
}
for(i= DEPTHS_BOUND-1;m_depths[i]!=0;i--);
for(j= 0;j<=i;j++){
if(m_depths[j])printf("m %d citydeep %d\n",j,m_depths[j]);
}
}
#endif


/*:175*/
#line 3890 "./jbmr.w"

printf("Statistics: num_reject_by_cum_1 %d\n",num_reject_by_cum_1);
printf("Statistics: num_reject_pre_e_build %d\n",num_reject_pre_e_build);
printf("Statistics: num_reject_by_decluster %d\n",num_reject_by_decluster);


/*:176*/
#line 723 "./jbmr.w"

}

/*:19*/
#line 544 "./jbmr.w"

const char*jbmr_rcs_id= "$Id: jbmr.w,v 1.192 1998/07/16 21:58:55 neto Exp neto $";

/*:4*/
