/*4:*/
#line 579 "./lk.w"

extern const char*lk_rcs_id;
/*124:*/
#line 2407 "./lk.w"

/*:124*/
#line 581 "./lk.w"

/*13:*/
#line 905 "./lk.w"

#define REP_ARRAY  1 
#define REP_TWO_LEVEL 2
#define REP_SPLAY_0  3
#define REP_SPLAY_1  4
#define REP_SPLAY_2  5
#define REP_SPLAY_3  6
#define REP_TWO_LEVEL_DEBUG  7


#define CAND_NN   1 
#define CAND_NQ   2
#define CAND_DEL  4



/*:13*/
#line 582 "./lk.w"

/*12:*/
#line 894 "./lk.w"

extern int verbose,iterations,should_show_tour,should_show_version;
extern int representation,construction_algorithm;
extern long start_heuristic_param;
extern int candidate_expr,cand_nn_k,cand_nq_k,cand_del_d;
extern char*PostScript_filename,*lower_bound_name,*upper_bound_name;
extern void(*sort)(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));
extern int noround;
extern double lower_bound_value,upper_bound_value;

/*:12*//*33:*/
#line 1125 "./lk.w"

extern int max_generic_flips;

/*:33*//*58:*/
#line 1590 "./lk.w"

extern tsp_instance_t*tsp_instance;

/*:58*//*63:*/
#line 1685 "./lk.w"

extern int*original_city_num;


/*:63*//*73:*/
#line 1829 "./lk.w"

extern int begin_data_structures_mark;


/*:73*//*89:*/
#line 2030 "./lk.w"

extern int(*tour_next)(int);
extern int(*tour_prev)(int);
extern int(*tour_between)(int,int,int);
extern void(*tour_flip)(int,int,int,int);
extern void(*tour_set)(int const*);
extern void(*tour_setup)(int n);
extern void(*tour_cleanup)(void);

/*:89*//*101:*/
#line 2204 "./lk.w"

extern length_t incumbent_len;

/*:101*//*125:*/
#line 2409 "./lk.w"

/*:125*/
#line 583 "./lk.w"

/*126:*/
#line 2411 "./lk.w"


/*:126*//*132:*/
#line 2560 "./lk.w"

int lk_double_cmp(const void*a,const void*b);
int lk_length_t_cmp(const void*a,const void*b);

/*:132*/
#line 584 "./lk.w"


/*:4*/
