#define DEFAULT_VERBOSE 5
#define XNORM(V) (tsp_instance->xmax==tsp_instance->xmin?0.0: \
((V) -tsp_instance->xmin) /(tsp_instance->xmax-tsp_instance->xmin) /(1+10*DBL_EPSILON) ) ;
#define YNORM(V) (tsp_instance->ymax==tsp_instance->ymin?0.0: \
((V) -tsp_instance->ymin) /(tsp_instance->ymax-tsp_instance->ymin) /(1+10*DBL_EPSILON) ) ; \

#define sgn(value) ((value) <0?-1:((value) >0?1:0) )  \
 \

#define ALWAYS_BUILD_DECLUSTER_STRUCTURES  \
(LK_BUILD_DECLUSTER_STRUCTURES \
||JBMR_DECLUSTER_IN_ELIGIBILITY_TEST \
||JBMR_DECLUSTER_IN_GREEDY)  \

#define my_abs(A) ((A) <0?-(A) :(A) ) 
#define within_epsilon(A,B) (my_abs(((A) -(B) ) ) <0.5)  \

/*2:*/
#line 541 "./lk.w"

#include <config.h>
#include "lkconfig.h"
/*3:*/
#line 559 "./lk.w"

#include <stdio.h>
#define __USE_MISC  
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#if defined(OS_HAS_BROKEN_HEADERS)
#define FIXINCLUDES_USE_RCS_ID
#define FIXINCLUDES_NEED_GETHOSTNAME
#define FIXINCLUDES_NEED_TIME_STUFF
#include "fixincludes.h"
#undef FIXINCLUDES_USE_RCS_ID
#undef FIXINCLUDES_NEED_GETHOSTNAME
#undef FIXINCLUDES_NEED_TIME_STUFF
#endif

/*:3*//*29:*/
#line 1093 "./lk.w"

#include <ctype.h>

/*:29*//*35:*/
#line 1134 "./lk.w"

#include <limits.h>

/*:35*//*53:*/
#line 1526 "./lk.w"

#if HAVE_TIME_H
#include <time.h>
#endif

/*:53*//*66:*/
#line 1765 "./lk.w"

#include <float.h>


/*:66*//*116:*/
#line 2334 "./lk.w"

#if HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h> 
#endif

/*:116*/
#line 544 "./lk.w"

/*56:*/
#line 1579 "./lk.w"

#define LENGTH_USE_RCS_ID
#include "length.h"
#undef LENGTH_USE_RCS_ID
#include "read.h"

/*:56*//*96:*/
#line 2179 "./lk.w"

#include "error.h"
#include "memory.h"

/*:96*//*105:*/
#line 2234 "./lk.w"

#include "prng.h"

/*:105*/
#line 545 "./lk.w"

/*5:*/
#line 589 "./lk.w"

#include "lk.h"


/*:5*//*38:*/
#line 1185 "./lk.w"

#include "dsort.h"

/*:38*//*50:*/
#line 1444 "./lk.w"

#include "pool.h"
#include "dict.h"
#include "kdtree.h"


/*:50*//*60:*/
#line 1624 "./lk.w"

#include "ascend.h"

/*:60*//*68:*/
#line 1790 "./lk.w"

#include "resource.h"

/*:68*//*81:*/
#line 1931 "./lk.w"

#include "declevel.h"
#include "decluster.h"

/*:81*//*83:*/
#line 1953 "./lk.w"

#include "nn.h"

/*:83*//*91:*/
#line 2081 "./lk.w"

#include "array.h"
#include "twolevel.h"

/*:91*//*97:*/
#line 2184 "./lk.w"

#include "construct.h"

/*:97*//*104:*/
#line 2230 "./lk.w"

#include "jbmr.h"

/*:104*//*108:*/
#line 2256 "./lk.w"

#include "match.h"

/*:108*/
#line 546 "./lk.w"


/*9:*/
#line 849 "./lk.w"

static char*filename;
static int mst_edge_lengths_only;
static int do_weighted_perfect_matching;
static int held_karp_only;
static int held_karp_lambda_only;

/*:9*//*55:*/
#line 1573 "./lk.w"

static int n;
static FILE*TSPLIB_in,*ps_out;

/*:55*//*69:*/
#line 1797 "./lk.w"

static int last_resource_mark;

/*:69*//*98:*/
#line 2188 "./lk.w"

static int*tour;

/*:98*/
#line 548 "./lk.w"

/*11:*/
#line 883 "./lk.w"

int verbose,iterations,should_show_tour,should_show_version;
int representation,construction_algorithm;
long start_heuristic_param;
int candidate_expr,cand_nn_k,cand_nq_k,cand_del_d;
char*PostScript_filename,*lower_bound_name,*upper_bound_name;
void(*sort)(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));
int noround;
double upper_bound_value,lower_bound_value;

/*:11*//*25:*/
#line 1055 "./lk.w"

int should_sfc_reorder;


/*:25*//*32:*/
#line 1121 "./lk.w"

int max_generic_flips;

/*:32*//*57:*/
#line 1587 "./lk.w"

tsp_instance_t*tsp_instance;

/*:57*//*62:*/
#line 1681 "./lk.w"

int*original_city_num= NULL;

/*:62*//*72:*/
#line 1825 "./lk.w"

int begin_data_structures_mark;

/*:72*//*80:*/
#line 1921 "./lk.w"

decluster_tree_t*mst;
length_t mst_len;

/*:80*//*88:*/
#line 2020 "./lk.w"

int(*tour_next)(int)= NULL;
int(*tour_prev)(int)= NULL;
int(*tour_between)(int,int,int)= NULL;
void(*tour_flip)(int,int,int,int)= NULL;
void(*tour_set)(int const*)= NULL;
void(*tour_setup)(int n)= NULL;
void(*tour_cleanup)(void)= NULL;

/*:88*//*100:*/
#line 2200 "./lk.w"

length_t incumbent_len;

/*:100*/
#line 549 "./lk.w"

/*120:*/
#line 2376 "./lk.w"

static void lk_cleanup(void);

/*:120*/
#line 550 "./lk.w"

/*28:*/
#line 1079 "./lk.w"

static int
is_number(char*p)
{
if(p==NULL)return 0;
if(*p=='-')p++;
if(*p==0)return 0;
for(;*p;p++){
if(!isdigit(*p))return 0;
}
return 1;
}

/*:28*//*65:*/
#line 1724 "./lk.w"

int cmp_sfc_Moore(const void*voida,const void*voidb);
int
cmp_sfc_Moore(const void*voida,const void*voidb)
{
int ai= *(const int*)voida,bi= *(const int*)voidb;
double a[2],b[2];
int ax,ay,bx,by,aq,bq,lastq= 12;
int order[13][4]= 
{{0,3,1,2},{0,1,3,2},{0,3,1,2},{2,3,1,0},
{0,3,1,2},{2,3,1,0},{0,1,3,2},{2,1,3,0},
{0,1,3,2},{2,3,1,0},{2,1,3,0},{2,1,3,0},{3,2,0,1}};
int rewrite[13][4]= 
{{1,3,2,0},{4,1,7,6},{8,9,2,0},{9,0,5,10},
{1,9,2,0},{9,0,5,11},{2,1,11,6},{7,10,8,5},
{2,1,7,6},{9,4,5,10},{7,10,6,3},{7,10,6,5},{7,10,2,0}};

a[0]= XNORM(tsp_instance->coord[ai].x[0]);
b[0]= XNORM(tsp_instance->coord[bi].x[0]);
a[1]= YNORM(tsp_instance->coord[ai].x[1]);
b[1]= YNORM(tsp_instance->coord[bi].x[1]);



errorif(a[0]<0||a[0]>=1,"cmp_sfc_Moore: a[0] out of range [0,1): %f",a[0]);
errorif(a[1]<0||a[1]>=1,"cmp_sfc_Moore: a[1] out of range [0,1): %f",a[1]);
errorif(b[0]<0||b[0]>=1,"cmp_sfc_Moore: b[0] out of range [0,1): %f",b[0]);
errorif(b[1]<0||b[1]>=1,"cmp_sfc_Moore: b[1] out of range [0,1): %f",b[1]);
while(1){
if(a[0]==b[0]&&a[1]==b[1])return 0;
ax= a[0]>=0.5;ay= a[1]>=0.5;aq= (ax<<1)+ay;
bx= b[0]>=0.5;by= b[1]>=0.5;bq= (bx<<1)+by;
if(aq!=bq)return order[lastq][aq]-order[lastq][bq];
lastq= rewrite[lastq][aq];
a[0]= (2*a[0])-ax;a[1]= (2*a[1])-ay;
b[0]= (2*b[0])-bx;b[1]= (2*b[1])-by;
}
}

/*:65*//*119:*/
#line 2369 "./lk.w"

static void lk_cleanup(void)
{
/*78:*/
#line 1903 "./lk.w"

#if ALWAYS_BUILD_DECLUSTER_STRUCTURES
if(verbose>=50)printf("Cleaning up MST\n");
if(mst!=NULL)decluster_cleanup_tree(mst);
if(verbose>=50)printf("Cleaning up decluster data strucutres\n");
decluster_cleanup();
#endif

/*:78*//*84:*/
#line 1960 "./lk.w"

if(verbose>=50)printf("Cleaning up nn structure\n");
nn_cleanup();


/*:84*//*93:*/
#line 2129 "./lk.w"

if(!do_weighted_perfect_matching){
if(verbose>=50)printf("Cleaning up tour data structure\n");
if(tour_cleanup!=NULL)(*tour_cleanup)();
}

/*:93*//*99:*/
#line 2192 "./lk.w"

if(!do_weighted_perfect_matching){
if(verbose>=50)printf("Cleaning initial tour\n");
free_mem(tour);
}

/*:99*//*107:*/
#line 2242 "./lk.w"

if(!do_weighted_perfect_matching){
if(verbose>=50)printf("Cleaning up jbmr structures\n");
jbmr_cleanup();
}

/*:107*//*111:*/
#line 2276 "./lk.w"

if(do_weighted_perfect_matching){
match_cleanup();
}

/*:111*//*123:*/
#line 2402 "./lk.w"

resource_cleanup();


/*:123*/
#line 2372 "./lk.w"

}

/*:119*/
#line 551 "./lk.w"

/*6:*/
#line 601 "./lk.w"

int
main(int argc,char**argv)
{
/*129:*/
#line 2508 "./lk.w"

length_t validate_len;
double double_validate_len,ordered_double_len,raw_len;


/*:129*/
#line 605 "./lk.w"

/*67:*/
#line 1783 "./lk.w"

mem_usage_reset();
resource_setup(50);

error_postcleanup_stats= resource_abnormal_exit_output;

/*:67*//*121:*/
#line 2384 "./lk.w"

error_cleanup= lk_cleanup;

/*:121*//*122:*/
#line 2392 "./lk.w"

error_postcleanup_stats= mem_report;

/*:122*/
#line 606 "./lk.w"

/*8:*/
#line 824 "./lk.w"

/*10:*/
#line 858 "./lk.w"

verbose= DEFAULT_VERBOSE;
iterations= 1;
should_show_tour= 0;
should_show_version= 0;
mst_edge_lengths_only= 0;
held_karp_only= 0;
held_karp_lambda_only= 0;
do_weighted_perfect_matching= 0;
representation= REP_ARRAY;
candidate_expr= CAND_NN;
cand_nn_k= 20;
cand_nq_k= 5;
cand_del_d= 3;
construction_algorithm= CONSTRUCT_GREEDY;
start_heuristic_param= 42L;
PostScript_filename= NULL;
lower_bound_name= NULL;
lower_bound_value= 1.0;
upper_bound_name= NULL;
upper_bound_value= 0.0;
sort= (void(*)(void*,size_t,size_t,int(*)(const void*,const void*)))qsort;
noround= 0;

/*:10*//*24:*/
#line 1051 "./lk.w"

should_sfc_reorder= 0;

/*:24*//*34:*/
#line 1130 "./lk.w"

max_generic_flips= INT_MAX;

/*:34*/
#line 825 "./lk.w"

{int r,filecount= 0,postscript_filecount= 0,more_options= 1;
filename= NULL;
for(r= 1;r<argc;r++){
if(more_options&&argv[r][0]=='-'&&argv[r][1]!=0){
/*14:*/
#line 922 "./lk.w"

if(strcmp(argv[r],"-h")==0||strcmp(argv[r],"--help")==0){
printf("Usage: %s [options] [filename]\n",argv[0]);
printf(" -                          TSPLIB input on stdin\n");
printf(" --                         End options\n");
printf(" -l --lower-bound <name> <length> \n"
"                            Give lower bound, enable milestones\n");
printf(" -c --candidate <p>         Specify candidate cities\n");
printf("      <p> ::= <bp> | <bp> or <p>\n");
printf("      <bp> ::= nn <k> | nq <k> | del <d>\n");
printf("                            (nq, del are unimplemented)\n");
printf("    --held-karp             Compute approx Held-Karp TSP lower bound,\n");
printf("                            then exit successfully.  Requires -u\n");
printf("    --held-karp-lambda      Compute approx Held-Karp TSP lower bound,\n");
printf("                            print the best Lagrange multipliers found,\n");
printf("                            then exit successfully.  Requires -u\n");
printf(" -h --help                  Give this help, then exit\n");
printf(" -i --iterate [n]           Iterated LK n times (default is 1, n default is 20)\n");
printf("                            (unimplemented)\n");
printf(" -m --matching              Find cheap weighted perfect matchings\n"
"                            rather than short tours\n");
printf(" -M --mst-edge-lengths-only Print the edge lengths in a minimum spanning tree\n");
printf("                            and then exit successfully\n");
printf("    --maxdepth [d]          Limit probe depth to d cities\n");
printf("    --no-round              Don't round distance computations\n");
printf(" -p --print                 Print the LK-optimal tour or matching\n");
printf(" -P --postscript <file>     Generate PostScript output and write to <file>\n");
printf(" -q --quiet                 Same as --verbose 0\n");
printf(" -r --representation <rep>  Specify tour representation (default is array)\n");
printf("      <rep> ::= array | two-level | tld (two-level-debug)| splay\n");
printf("                            (This has no effect if finding a matching)\n");
printf(" -s --start <kind>          Specify staring tour (matching) algorithm"
"                            Greedy is default.\n");
printf("      <kind> ::= canonical | greedy | random [seed]\n");
printf("    --sfc                   Reorder cities by Moore's space filling curve\n");
printf(" -S --sort <kind>           Specify sorting procedure (default is qsort)\n");
printf("      <kind> ::= qsort (from system library) | dsort (Bentley&McIlroy qsort)\n");
printf(" -u --upper-bound <name> <length> \n"
"                            Give upper bound, required for Held-Karp\n");
printf(" -v --verbose [n]           Set verbose level (default is 5, n default is 100)\n");
printf("    --version               Print LK version number, then exit successfully\n");
exit(0);
}

/*:14*//*15:*/
#line 969 "./lk.w"

if(strcmp(argv[r],"--")==0){
more_options= 0;
continue;
}

/*:15*//*16:*/
#line 977 "./lk.w"

if(strcmp(argv[r],"--no-round")==0){
noround= 1;
continue;
}

/*:16*//*17:*/
#line 985 "./lk.w"

if(strcmp(argv[r],"-p")==0||strcmp(argv[r],"--print")==0){
should_show_tour= 1;
continue;
}

/*:17*//*18:*/
#line 993 "./lk.w"

if(strcmp(argv[r],"-M")==0||strcmp(argv[r],"--mst-edge-lengths-only")==0){
mst_edge_lengths_only= 1;
continue;
}

/*:18*//*19:*/
#line 1001 "./lk.w"

if(strcmp(argv[r],"--held-karp")==0){
held_karp_only= 1;
continue;
}

/*:19*//*20:*/
#line 1009 "./lk.w"

if(strcmp(argv[r],"--held-karp-lambda")==0){
held_karp_lambda_only= 1;
continue;
}

/*:20*//*21:*/
#line 1020 "./lk.w"

if(strcmp(argv[r],"-m")==0||strcmp(argv[r],"--matching")==0){
do_weighted_perfect_matching= 1;
continue;
}



/*:21*//*22:*/
#line 1029 "./lk.w"

if(strcmp(argv[r],"--version")==0){
should_show_version= 1;
/*48:*/
#line 1420 "./lk.w"

printf("LK %s",VERSION_STRING);
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
printf("de");
# if JBMR_DECLUSTER_IN_GREEDY
printf("g");
# endif
#endif
printf("\n");

/*:48*/
#line 1032 "./lk.w"

exit(0);
continue;
}


/*:22*//*23:*/
#line 1044 "./lk.w"

if(strcmp(argv[r],"--sfc")==0){
should_sfc_reorder= 1;
continue;
}

/*:23*//*26:*/
#line 1060 "./lk.w"

if(strcmp(argv[r],"-q")==0||strcmp(argv[r],"--quiet")==0){
verbose= 0;
continue;
}

/*:26*//*27:*/
#line 1068 "./lk.w"

if(strcmp(argv[r],"-v")==0||strcmp(argv[r],"--verbose")==0){
verbose= 100;
if(r+1<argc&&is_number(argv[r+1]))verbose= atoi(argv[++r]);
continue;
}

/*:27*//*30:*/
#line 1098 "./lk.w"

if(strcmp(argv[r],"-i")==0||strcmp(argv[r],"--iterate")==0){
iterations= 20;
if(r+1<argc&&is_number(argv[r+1]))iterations= atoi(argv[++r]);
continue;
}

/*:30*//*31:*/
#line 1109 "./lk.w"

if(strcmp(argv[r],"--maxdepth")==0){
#if !defined(JBMR_LIMIT_PROBE_DEPTH)
errorif(1,
"Option --maxdepth requires JBMR_LIMIT_PROBE_DEPTH compilation flag.\n");
#endif
max_generic_flips= 50;
if(r+1<argc&&is_number(argv[r+1]))max_generic_flips= atoi(argv[++r]);
continue;
}

/*:31*//*36:*/
#line 1140 "./lk.w"

if(strcmp(argv[r],"-s")==0||strcmp(argv[r],"--start")==0){
if(r+1>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1143 "./lk.w"

fprintf(stderr,"Need one of {canonical,greedy,random [seed]}\n");
exit(1);
}
r++;

if(strcmp(argv[r],"greedy")==0)construction_algorithm= CONSTRUCT_GREEDY;
else if(strcmp(argv[r],"canonical")==0)construction_algorithm= CONSTRUCT_CANONICAL;
else if(strcmp(argv[r],"random")==0){
construction_algorithm= CONSTRUCT_RANDOM;
if(r+1<argc&&is_number(argv[r+1]))start_heuristic_param= atol(argv[++r]);
}else{
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1155 "./lk.w"

fprintf(stderr,"Need one of {canonical,greedy,random [seed],best}\n");
exit(1);
}
continue;
}

/*:36*//*37:*/
#line 1164 "./lk.w"

if(strcmp(argv[r],"-S")==0||strcmp(argv[r],"--sort")==0){
if(r+1>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1167 "./lk.w"

fprintf(stderr,"Need one of {dsort,qsort}\n");
exit(1);
}
r++;

if(strcmp(argv[r],"qsort")==0)
sort= (void(*)(void*,size_t,size_t,int(*)(const void*,const void*)))qsort;
else if(strcmp(argv[r],"dsort")==0)sort= dsort;
else{
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1177 "./lk.w"

fprintf(stderr,"Need one of {dsort,qsort}\n");
exit(1);
}
continue;
}

/*:37*//*39:*/
#line 1191 "./lk.w"

if(strcmp(argv[r],"-r")==0||strcmp(argv[r],"--representation")==0){
if(r+1>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1194 "./lk.w"

fprintf(stderr,"Need one of {array,splay [level],two-level,tld}\n");
exit(1);
}
r++;
if(strcmp(argv[r],"array")==0){
representation= REP_ARRAY;
}else if(strcmp(argv[r],"two-level")==0){
representation= REP_TWO_LEVEL;
}else if(strcmp(argv[r],"tld")==0){
representation= REP_TWO_LEVEL_DEBUG;
}else if(strcmp(argv[r],"splay")==0){
int level= 0;
if(r+1<argc&&is_number(argv[r+1]))level= atoi(argv[++r]);
if(level<0||level>3){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1209 "./lk.w"

fprintf(stderr,"Splay level must be 0, 1, 2, or 3\n");
exit(1);
}
representation= REP_SPLAY_0+level;
}else{
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1215 "./lk.w"

fprintf(stderr,"Need one of {array,splay [level],two-level,tld}\n");
exit(1);
}
continue;
}

/*:39*//*40:*/
#line 1223 "./lk.w"

if(strcmp(argv[r],"-P")==0||strcmp(argv[r],"--postscript")==0){
if(r+1>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1226 "./lk.w"

fprintf(stderr,"Need a file name\n");
exit(1);
}
r++;
if(postscript_filecount){
fprintf(stderr,
"Warning: %s already specified as PostScript output file; "
"%s overrides\n",
PostScript_filename,argv[r]);
}
postscript_filecount++;
PostScript_filename= argv[r];
continue;
}

/*:40*//*41:*/
#line 1245 "./lk.w"

if(strcmp(argv[r],"-l")==0||strcmp(argv[r],"--lower-bound")==0){
if(r+1>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1248 "./lk.w"

fprintf(stderr,"Need a lower bound name\n");
exit(1);
}
if(r+2>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1253 "./lk.w"

fprintf(stderr,"Need a lower bound on length\n");
exit(1);
}
r++;
lower_bound_name= dup_string(argv[r]);
r++;
lower_bound_value= atof(argv[r]);
continue;
}

/*:41*//*42:*/
#line 1266 "./lk.w"

if(strcmp(argv[r],"-u")==0||strcmp(argv[r],"--upper-bound")==0){
if(r+1>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1269 "./lk.w"

fprintf(stderr,"Need an upper bound name\n");
exit(1);
}
if(r+2>=argc){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1274 "./lk.w"

fprintf(stderr,"Need an upper bound on length\n");
exit(1);
}
r++;
upper_bound_name= dup_string(argv[r]);
r++;
upper_bound_value= atof(argv[r]);
continue;
}

/*:42*//*44:*/
#line 1295 "./lk.w"

if(strcmp(argv[r],"-c")==0||strcmp(argv[r],"--candidate")==0){
int numeric_param;
candidate_expr= cand_nn_k= cand_nq_k= cand_del_d= 0;
r++;
do{
if(r>=argc||
(strcmp(argv[r],"nn")!=0&&strcmp(argv[r],"nq")!=0&&
strcmp(argv[r],"del")!=0)
){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1305 "./lk.w"

fprintf(stderr,"Need one of {nn,nq,del}\n");
exit(1);
}
if(r+1>=argc||!is_number(argv[r+1])){
r++;
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1311 "./lk.w"

fprintf(stderr,"Need a numeric parameter\n");
exit(1);
}else numeric_param= atoi(argv[r+1]);
if(strcmp(argv[r],"nn")==0){
candidate_expr|= CAND_NN;
if(cand_nn_k<numeric_param)cand_nn_k= numeric_param;
}else if(strcmp(argv[r],"nq")==0){
candidate_expr|= CAND_NQ;
if(cand_nq_k<numeric_param)cand_nq_k= numeric_param;
}else if(strcmp(argv[r],"del")==0){
candidate_expr|= CAND_DEL;
if(cand_del_d<numeric_param)cand_del_d= numeric_param;
}else{
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1325 "./lk.w"

fprintf(stderr,"Need one of {nn,nq,del}\n");
exit(1);
}
r++;
}while(r+1<argc&&strcmp(argv[r+1],"or")==0&&(r+= 2));
continue;
}

/*:44*/
#line 830 "./lk.w"

/*45:*/
#line 1339 "./lk.w"

/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 1340 "./lk.w"

fprintf(stderr,"Skipping unrecognized option %s\n",argv[r]);

/*:45*/
#line 831 "./lk.w"

}else{
if(filecount){
/*46:*/
#line 1355 "./lk.w"

{int chars_before_split= 0,i;
for(i= 0;i<=r&&i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
chars_before_split+= strlen(argv[i])+1;
}
fputc('\n',stderr);
for(i= 0;i<chars_before_split;i++){fputc(' ',stderr);}
for(i= r+1;i<argc;i++){
fprintf(stderr,"%s ",argv[i]);
}
fputc('\n',stderr);
}

/*:46*/
#line 834 "./lk.w"

fprintf(stderr,"Only one input file allowed\n");
exit(1);
}
if(!(more_options&&strcmp(argv[r],"-")==0))
filename= argv[r];

filecount++;
}
}
}
/*43:*/
#line 1286 "./lk.w"

errorif((held_karp_only||held_karp_lambda_only)&&upper_bound_name==NULL,
"Held-Karp lower bounding requires an upper bound\n");


/*:43*/
#line 845 "./lk.w"



/*:8*//*90:*/
#line 2043 "./lk.w"

switch(representation){
case REP_ARRAY:
tour_next= array_next;
tour_prev= array_prev;
tour_between= array_between;
tour_flip= array_flip;
tour_set= array_set;
tour_setup= array_setup;
tour_cleanup= array_cleanup;
break;
case REP_TWO_LEVEL:
tour_next= twolevel_next;
tour_prev= twolevel_prev;
tour_between= twolevel_between;
tour_flip= twolevel_flip;
tour_set= twolevel_set;
tour_setup= NULL;
tour_cleanup= twolevel_cleanup;
break;
case REP_TWO_LEVEL_DEBUG:
#if defined(TWOLEVEL_DEBUG)
tour_next= twolevel_debug_next;
tour_prev= twolevel_debug_prev;
tour_between= twolevel_debug_between;
tour_flip= twolevel_debug_flip;
tour_set= twolevel_debug_set;
tour_setup= NULL;
tour_cleanup= twolevel_debug_cleanup;
#else
errorif(1,"Two-level tree debugging (-DTWOLEVEL_DEBUG) wasn't compiled into the program");
#endif
break;
default:
errorif(1,"Only array, two-level, and tld representations are currently supported");
}

/*:90*/
#line 607 "./lk.w"

/*47:*/
#line 1380 "./lk.w"

if(verbose>=10){
extern const char*compile_compile,*compile_link;
/*48:*/
#line 1420 "./lk.w"

printf("LK %s",VERSION_STRING);
#if JBMR_DECLUSTER_IN_ELIGIBILITY_TEST
printf("de");
# if JBMR_DECLUSTER_IN_GREEDY
printf("g");
# endif
#endif
printf("\n");

/*:48*/
#line 1383 "./lk.w"

if(verbose>=10)/*49:*/
#line 1431 "./lk.w"

printf(
"LK approximately solves the traveling salesman problem.\n"
"\nCopyright (C) 1997 David M. Neto\n"
"LK comes with NO WARRANTY, to the extent permitted by law.\n"
"You may redistribute and/or modify copies of LK under the terms of the\n"
"GNU General Public License, version 2 or any later version.\n"
"For more information about these matters, see the file named COPYING.\n"

);

/*:49*/
#line 1384 "./lk.w"

if(verbose>=100){
printf("%s\n",compile_compile);
printf("%s\n",compile_link);
printf("%s\n",array_rcs_id);
printf("%s\n",construct_rcs_id);
printf("%s\n",dict_rcs_id);
printf("%s\n",dsort_rcs_id);
printf("%s\n",error_rcs_id);
#if defined(OS_HAS_BROKEN_HEADERS)
printf("%s\n",fixincludes_rcs_id);
#endif
printf("%s\n",jbmr_rcs_id);
printf("%s\n",kdtree_rcs_id);
printf("%s\n",length_rcs_id);
printf("%s\n",lk_rcs_id);
printf("%s\n",memory_rcs_id);
printf("%s\n",nn_rcs_id);
printf("%s\n",pool_rcs_id);
printf("%s\n",read_rcs_id);
printf("%s\n",resource_rcs_id);
}
printf("Command line equivalent: ");/*51:*/
#line 1454 "./lk.w"

if(verbose>=10){
printf("%s ",argv[0]);
if(verbose!=DEFAULT_VERBOSE)printf("-v %d ",verbose);
if(should_show_version)printf("--version ");
if(do_weighted_perfect_matching)printf("-m ");
if(mst_edge_lengths_only)printf("-M ");
if(held_karp_only)printf("--held-karp ");
if(held_karp_lambda_only)printf("--held-karp-lambda ");
if(should_show_tour)printf("-p ");
if(noround)printf("--no-round ");
if(NULL!=PostScript_filename)printf("-P %s ",PostScript_filename);
if(iterations!=1)printf("-i %d ",iterations);
switch(construction_algorithm){
case CONSTRUCT_CANONICAL:printf("-s canonical ");break;
case CONSTRUCT_GREEDY:printf("-s greedy ");break;
case CONSTRUCT_RANDOM:printf("-s random %ld ",start_heuristic_param);break;
default:errorif(1,"Bad construction_algorithm == %d\n",construction_algorithm);
}

if(sort==dsort)printf("-S dsort ");

printf("-c ");
if(candidate_expr&CAND_NN)
printf("nn %d %s",cand_nn_k,
candidate_expr&(CAND_NQ|CAND_DEL)?"or ":"");
if(candidate_expr&CAND_NQ)
printf("nq %d %s",cand_nq_k,
candidate_expr&CAND_DEL?"or ":"");
if(candidate_expr&CAND_DEL)
printf("del %d ",cand_del_d);

switch(representation){
case REP_ARRAY:printf("-r array ");break;
case REP_TWO_LEVEL:printf("-r two-level ");break;
case REP_TWO_LEVEL_DEBUG:printf("-r tld ");break;
case REP_SPLAY_0:printf("-r splay 0 ");break;
case REP_SPLAY_1:printf("-r splay 1 ");break;
case REP_SPLAY_2:printf("-r splay 2 ");break;
case REP_SPLAY_3:printf("-r splay 3 ");break;
default:errorif(1,"Bad representation == %d\n",representation);
}

if(should_sfc_reorder)printf("--sfc ");

if(max_generic_flips!=INT_MAX)printf("--maxdepth %d ",max_generic_flips);

if(lower_bound_name!=NULL)printf("-l %s %f ",lower_bound_name,lower_bound_value);
if(upper_bound_name!=NULL)printf("-u %s %f ",upper_bound_name,upper_bound_value);

if(filename){
if(filename[0]=='-')printf("-- %s",filename);
else printf("%s",filename);
}else printf("-");
printf("\n");
}

/*:51*/
#line 1406 "./lk.w"

printf("Start time: ");/*52:*/
#line 1516 "./lk.w"

{
#if HAVE_TIME_H && HAVE_TIME && HAVE_CTIME
time_t now= time(NULL);
printf("%s",ctime(&now));
fflush(stdout);
#endif
}

/*:52*/
#line 1407 "./lk.w"

}

/*:47*/
#line 608 "./lk.w"

/*54:*/
#line 1547 "./lk.w"

last_resource_mark= resource_mark("Reading the instance");
if(filename){
TSPLIB_in= fopen(filename,"r");
errorif(TSPLIB_in==NULL,"Couldn't open \"%s\" for reading",filename);
}else TSPLIB_in= stdin;
if(PostScript_filename){
FILE*prolog;
char buf[8192];
size_t countin,countout;
ps_out= fopen(PostScript_filename,"w");
errorif(ps_out==NULL,"Couldn't open \"%s\" for writing",filename);
prolog= fopen("prolog.ps","r");
errorif(prolog==NULL,"Couldn't open prolog.ps for reading");
while((countin= fread(buf,1,8192,prolog))>0){
char*p= buf;
while((countout= fwrite(p,1,countin,ps_out))<countin){
countin-= countout;p+= countout;
}
}
fclose(prolog);
}else ps_out= NULL;
tsp_instance= read_tsp_file(TSPLIB_in,ps_out);
n= tsp_instance->n;

/*:54*//*109:*/
#line 2262 "./lk.w"

if(do_weighted_perfect_matching){
errorif(n%2,"Must have even number of vertices to have a perfect matching");
}

/*:109*/
#line 609 "./lk.w"

/*59:*/
#line 1599 "./lk.w"

if(held_karp_only||held_karp_lambda_only){
length_t held_karp_bound;
errorif(upper_bound_value<=0,"main: upper bound %d should be positive.",upper_bound_value);
ascend_setup(n);
held_karp_bound= ascend(n,upper_bound_value);
printf("Held-Karp lower bound: "length_t_spec
" (%.2f%% below upper bound "length_t_spec")\n",
length_t_pcast(held_karp_bound),
100.0*((double)(upper_bound_value-held_karp_bound))/upper_bound_value,
length_t_pcast(upper_bound_value));
if(held_karp_lambda_only){
int i;
double*const lambda= ascend_best_lambda();
errorif(lambda==NULL,"No Lagrange multilpier lambda vector!\n");
printf("Lagrange multipliers:\n");
for(i= 0;i<n;i++){
printf("%d %f\n",1+i,lambda[i]);
}
}
ascend_cleanup();
exit(0);
}

/*:59*/
#line 610 "./lk.w"

/*61:*/
#line 1638 "./lk.w"

if(should_sfc_reorder){
int i,n= tsp_instance->n;
coord_2d*new_coord;
errorif(tsp_instance->coord==NULL,
"Space filling curve reordering applies only to geometric instances.\n");
original_city_num= new_arr_of(int,n);
for(i= 0;i<n;i++)original_city_num[i]= i;
sort(original_city_num,(size_t)n,sizeof(int),cmp_sfc_Moore);
new_coord= new_arr_of(coord_2d,n);
for(i= 0;i<n;i++)new_coord[i]= tsp_instance->coord[original_city_num[i]];
#if 0
free_mem(tsp_instance->coord);mem_deduct(n*sizeof(coord_2d));
tsp_instance->coord= new_coord;
#else
for(i= 0;i<n;i++)tsp_instance->coord[i]= new_coord[i];
free_mem(new_coord);mem_deduct(n*sizeof(coord_2d));
#endif
#if defined(LK_SHOW_AFTER_SFC)
if(ps_out){
length_t len= cost(0,n-1);int i;for(i= 1;i<n;i++,len+= cost(i,i-1));
fprintf(ps_out,"(SFC(Moore) tour, len "length_t_spec") title\n",
length_t_pcast(len));
fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
for(i= 0;i<n;i++){
fprintf(ps_out,"%d %f %f sfcs\n",i+1,
tsp_instance->coord[i].x,tsp_instance->coord[i].y);
fprintf(ps_out,"(%d) %d label\n",i,i);
if(i>0)fprintf(ps_out,"%d %d edge\n",i-1,i);
}
fprintf(ps_out,"%d %d edge\n",n-1,0);
fprintf(ps_out,
"1 1 N { dup xs exch get exch ys exch get circle } for\n");
fprintf(ps_out,"showpage\n");
fflush(ps_out);
}
#endif
}

/*:61*/
#line 611 "./lk.w"

/*79:*/
#line 1912 "./lk.w"

if(ALWAYS_BUILD_DECLUSTER_STRUCTURES||mst_edge_lengths_only){
mst= decluster_setup(n);
}

/*:79*//*92:*/
#line 2098 "./lk.w"

if(do_weighted_perfect_matching){
tour_setup= NULL;
}else{
switch(representation){
case REP_TWO_LEVEL:
{
const int n= tsp_instance->n;
twolevel_setup
(n,n<50?n:(n<1000?50:(n>100000?200:100)));
}
break;
case REP_TWO_LEVEL_DEBUG:
{
#if defined(TWOLEVEL_DEBUG)
const int n= tsp_instance->n;
twolevel_debug_setup
(n,n<50?n:(n<1000?50:(n>100000?200:100)));
#else
errorif(1,"Debugging of two-level isn't possible.  Recompile with -DTWOLEVEL_DEBUG");
#endif
}
break;
default:
tour_setup(tsp_instance->n);
}
}


/*:92*//*106:*/
#line 2238 "./lk.w"

if(!do_weighted_perfect_matching)jbmr_setup(n);

/*:106*//*110:*/
#line 2270 "./lk.w"

if(do_weighted_perfect_matching){
match_setup(n);
}

/*:110*/
#line 612 "./lk.w"

/*71:*/
#line 1811 "./lk.w"

if(E2_supports(tsp_instance)){
begin_data_structures_mark= 
last_resource_mark= resource_mark("Build the 2-d tree");
E2_create(tsp_instance);
if(ps_out){E2_postscript_show(ps_out);}
/*133:*/
#line 2565 "./lk.w"

#ifdef LK_CHECK_KDTREE
if(E2_supports(tsp_instance)){
int i,c,d,*done= new_arr_of(int,n),last;
length_t last_dist,next_dist;
for(c= 0;c<n;c++){
if(verbose)printf("%d ",c);fflush(stdout);
for(i= 0;i<n;i++){
done[i]= 0;
}
done[c]= 1;
last_dist= 0;
last= c;
for(i= 0;i<n-1;i++){
d= E2_nn(c);
if(0<=d&&d<n){
next_dist= cost(c,d);
errorif(last_dist>next_dist,
"NN for %d out of order: #%d %d cost="length_t_spec", "
"#%d %d cost="length_t_spec,
c,i-1,last,length_t_pcast(last_dist),
i,d,length_t_pcast(next_dist));

if(verbose>=500){
printf("nn(%d) #%d = %d dist "length_t_spec"\n",c,i,d,length_t_pcast(cost(c,d)));
}

last_dist= next_dist;
last= d;
}else{
printf("Invalid city %d returned on nn query %d from %d\n",
d,i,c);
}
errorif(done[d],"Shouldn't return %d on nn query at %d",d,c);
E2_hide(d);
done[d]= 1;
}
d= E2_nn(c);
errorif(d!=-1,"nn(%d) returned %d when all others hidden; should be -1.\n",
c,d);
E2_unhide_all();
}
free_mem(done);
if(verbose)printf("\nkd tree passed an integrity test on nearest-neighbour searching\n");
}
#endif



/*:133*/
#line 1817 "./lk.w"

}else{
begin_data_structures_mark
= resource_mark("Begin building data structures (but not k-d tree)");
}


/*:71*//*74:*/
#line 1844 "./lk.w"

if(ALWAYS_BUILD_DECLUSTER_STRUCTURES||mst_edge_lengths_only){
last_resource_mark= resource_mark("Build a MST (decluster)");
mst_len= decluster_mst(tsp_instance,mst);
if(mst_edge_lengths_only){
/*76:*/
#line 1872 "./lk.w"

if(ps_out&&tsp_instance->coord){
int i;
fprintf(ps_out,"(MST length "length_t_spec") title\n",
length_t_pcast(mst_len));
fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
for(i= 0;i<n-1;i++){
const int*city= mst->edge[i].city;
fprintf(ps_out,"%f %f %f %f ue\n",
tsp_instance->coord[city[0]].x[0],
tsp_instance->coord[city[0]].x[1],
tsp_instance->coord[city[1]].x[0],
tsp_instance->coord[city[1]].x[1]);
}
fprintf(ps_out,"showpage\ngrestore\n%%%%EOF");
fclose(ps_out);ps_out= NULL;
}


/*:76*/
#line 1849 "./lk.w"

/*75:*/
#line 1862 "./lk.w"

{
int i;
printf("%d\n",n-1);
for(i= 0;i<n-1;i++)printf("%.15f\n",(double)(mst->edge[i].cost));
exit(0);
}

/*:75*/
#line 1850 "./lk.w"

}
}


/*:74*//*77:*/
#line 1896 "./lk.w"

#if ALWAYS_BUILD_DECLUSTER_STRUCTURES
last_resource_mark= resource_mark("Preprocess the MST (decluster)");
decluster_preprocess(mst);
#endif

/*:77*//*82:*/
#line 1940 "./lk.w"

last_resource_mark= resource_mark("Build the adjacency structure");
errorif((candidate_expr&CAND_NN)&&(cand_nn_k<1),
"Neighbourhood bound must be positive, but is %d",cand_nn_k);
errorif((candidate_expr&CAND_NQ)&&(cand_nq_k<1),
"Neighbourhood quadrant bound must be positive, but is %d",cand_nq_k);
errorif(candidate_expr&CAND_DEL,"Candidate structure %d not supported",candidate_expr);
nn_build(
(candidate_expr&CAND_NN)?cand_nn_k:0,
(candidate_expr&CAND_NQ)?cand_nq_k:0,
(candidate_expr&CAND_DEL)?cand_del_d:0);

/*:82*/
#line 613 "./lk.w"

if(do_weighted_perfect_matching){
/*112:*/
#line 2282 "./lk.w"

last_resource_mark= resource_mark("Construct starting matching");
incumbent_len= match_construct(construction_algorithm,start_heuristic_param);
if(verbose>=10)printf("Initial matching length: "length_t_spec"\n",
length_t_pcast(incumbent_len));
/*113:*/
#line 2291 "./lk.w"

if(ps_out&&tsp_instance->coord){
char heuristic_name[200];
switch(construction_algorithm){
case CONSTRUCT_CANONICAL:sprintf(heuristic_name,"Canonical");break;
case CONSTRUCT_GREEDY:sprintf(heuristic_name,"Greedy");break;
case CONSTRUCT_RANDOM:sprintf(heuristic_name,"Random %ld",start_heuristic_param);break;
default:sprintf(heuristic_name,"unknown--Bug!");
}
match_ps_out(ps_out,heuristic_name);
}



/*:113*/
#line 2287 "./lk.w"



/*:112*/
#line 615 "./lk.w"

}else{
/*94:*/
#line 2139 "./lk.w"

last_resource_mark= resource_mark("Construct starting tour");
tour= new_arr_of(int,n);
incumbent_len= construct(n,tour,construction_algorithm,start_heuristic_param);
if(verbose>=10)printf("Initial tour length: "length_t_spec"\n",length_t_pcast(incumbent_len));
/*95:*/
#line 2148 "./lk.w"

if(ps_out&&tsp_instance->coord&&verbose>=50&&
!do_weighted_perfect_matching){
int i;
const char*tour_name;
switch(construction_algorithm){
case CONSTRUCT_CANONICAL:tour_name= "Canonical";break;
case CONSTRUCT_GREEDY:tour_name= "Greedy";break;
case CONSTRUCT_RANDOM:tour_name= "Random";break;
default:errorif(1,"Unkown start tour parameter %d\n",construction_algorithm);
tour_name= "";
}
fprintf(ps_out,"(%s tour length "length_t_spec") title\n",
tour_name,
length_t_pcast(incumbent_len));
fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
for(i= 0;i<n;i++){
const int city= tour[i],next_city= tour[(i+1)%n];
fprintf(ps_out,"%f %f %f %f ue\n",
tsp_instance->coord[city].x[0],
tsp_instance->coord[city].x[1],
tsp_instance->coord[next_city].x[0],
tsp_instance->coord[next_city].x[1]);
}
fprintf(ps_out,"showpage\n");
}

/*:95*/
#line 2144 "./lk.w"


/*:94*//*102:*/
#line 2210 "./lk.w"

tour_set(tour);

/*:102*/
#line 617 "./lk.w"

}
/*103:*/
#line 2220 "./lk.w"

last_resource_mark= resource_mark("Lin-Kernighan");
if(do_weighted_perfect_matching){
match_run(3,iterations,prng_new(PRNG_DEFAULT,1998));
}else{
jbmr_run(iterations,prng_new(PRNG_DEFAULT,1998));
}

/*:103*/
#line 619 "./lk.w"

/*115:*/
#line 2314 "./lk.w"

last_resource_mark= resource_mark("The end");
if(verbose>=2){
int i;
if(verbose>=5)
for(i= 0;i<last_resource_mark;i++){
resource_report(stdout,i,i+1);
}
if(last_resource_mark>0){
resource_report(stdout,begin_data_structures_mark,last_resource_mark);
}
if(verbose>=10){
printf("End time: ");/*52:*/
#line 1516 "./lk.w"

{
#if HAVE_TIME_H && HAVE_TIME && HAVE_CTIME
time_t now= time(NULL);
printf("%s",ctime(&now));
fflush(stdout);
#endif
}

/*:52*/
#line 2326 "./lk.w"

mem_report();
}
/*117:*/
#line 2346 "./lk.w"

#if HAVE_GETHOSTNAME
{
#if !defined(MAXHOSTNAMELEN)
#define MAXHOSTNAMELEN 256
#endif 
char buf[MAXHOSTNAMELEN+1];
gethostname(buf,MAXHOSTNAMELEN);
buf[MAXHOSTNAMELEN]= 0;
printf("Machine: %s\n",buf);
}
#endif 


/*:117*/
#line 2329 "./lk.w"

}


/*:115*/
#line 620 "./lk.w"

/*127:*/
#line 2429 "./lk.w"

if(do_weighted_perfect_matching){
match_validate(&validate_len,&double_validate_len,&ordered_double_len,&raw_len);
}else{
int i,c,cn;
double*lengths= new_arr_of(double,n);
double*raw_lengths= new_arr_of(double,n);
double*length_t_lengths= new_arr_of(length_t,n);
validate_len= 0;
double_validate_len= ordered_double_len= raw_len= 0.0;
for(i= 0,c= 0;i<n;i++){
errorif(c==0&&i>0,"Not a tour");
cn= tour_next(c);
length_t_lengths[i]= cost(c,cn);
double_validate_len+= (double)length_t_lengths[i];
lengths[i]= (double)length_t_lengths[i];
if(tsp_instance->edge_weight_type==EUC_2D||
tsp_instance->edge_weight_type==CEIL_2D){
raw_lengths[i]= cost_from_euc2d_raw(c,cn);
}else{
raw_lengths[i]= lengths[i];
}
c= cn;
}
sort(lengths,(unsigned)n,sizeof(double),lk_double_cmp);
sort(raw_lengths,(unsigned)n,sizeof(double),lk_double_cmp);
sort(length_t_lengths,(unsigned)n,sizeof(length_t),lk_length_t_cmp);
for(i= 0;i<n;i++){
ordered_double_len+= lengths[i];
raw_len+= raw_lengths[i];
validate_len+= length_t_lengths[i];
}
free_mem(lengths);
free_mem(raw_lengths);
free_mem(length_t_lengths);
mem_deduct(n*(sizeof(double)+sizeof(double)+sizeof(length_t)));
errorif(c!=0,"Not a tour");
}

/*:127*//*128:*/
#line 2469 "./lk.w"

if(verbose>=2){
printf("Instance name: %s\n",tsp_instance->name);
printf("Instance comment: %s\n",tsp_instance->comment);
}
if(should_show_tour){
if(do_weighted_perfect_matching){
match_show(stdout);
}else{
int i,c;
printf("Tour:\n");
for(i= 0,c= 0;i<n;i++,c= tour_next(c)){
printf("%d ",(original_city_num?original_city_num[c]:c)+1);

if((i%10)==9||i==n-1)printf("\n");
}
}
}
if(verbose>=2)printf("Length: ");
if(verbose)printf(noround?"%f\n":"%.0f\n",(double)validate_len);
if(verbose>=10){
printf("\tincumbent_len       == "length_t_spec"\n"
"\tvalidate_len        == "length_t_spec"\n"
"\tdouble_validate_len == %f\n"
"\tordered_double_len  == %f\n"
"\traw_len             == %f\n"
"\tdiscrepancy == (incumbent_len-ordered_double_len) == %-10g\n",
length_t_pcast(incumbent_len),
length_t_pcast(validate_len),
double_validate_len,
ordered_double_len,
raw_len,
((double)incumbent_len)-ordered_double_len);
}
errorif(!within_epsilon(((double)incumbent_len),ordered_double_len),
"%s mistaken about improvement",
do_weighted_perfect_matching?"match_run()":"jbmr_run()");

/*:128*//*130:*/
#line 2514 "./lk.w"

if(ps_out){
if(do_weighted_perfect_matching){
match_ps_out(ps_out,(const char*)"LK-opt");
}else{
int i,c,cn;
fprintf(ps_out,"%%Here's the final tour\n");
fprintf(ps_out,"(LK opt, tour len "length_t_spec") title\n",
length_t_pcast(incumbent_len));
fprintf(ps_out,"(%s) comment\n",tsp_instance->comment);
for(i= 0,c= 0;i<n;i++,c= cn){
cn= tour_next(c);
errorif(c==0&&i>0,"Not a tour");
fprintf(ps_out,"%f x %f y %f x %f y rawedge\n",
tsp_instance->coord[cn].x[0],
tsp_instance->coord[cn].x[1],
tsp_instance->coord[c].x[0],
tsp_instance->coord[c].x[1]);
}
fprintf(ps_out,"showpage\n");fflush(ps_out);
}
fprintf(ps_out,"end\ngrestore\n%%EOF\n");fclose(ps_out);
}


/*:130*/
#line 621 "./lk.w"

/*64:*/
#line 1690 "./lk.w"

free_mem(original_city_num);

/*:64*//*118:*/
#line 2363 "./lk.w"

lk_cleanup();

/*:118*/
#line 622 "./lk.w"

return 0;
}


/*:6*//*131:*/
#line 2540 "./lk.w"

int
lk_double_cmp(const void*a,const void*b)
{
const double da= *((const double*)a),db= *((const double*)b);
if(da<db)return-1;
if(da>db)return+1;
return 0;
}

int
lk_length_t_cmp(const void*a,const void*b)
{
const length_t da= *((const length_t*)a),db= *((const length_t*)b);
if(da<db)return-1;
if(da>db)return+1;
return 0;
}

/*:131*/
#line 552 "./lk.w"

const char*lk_rcs_id= "$Id: lk.w,v 1.251 1998/07/16 21:58:55 neto Exp neto $";


/*:2*/
