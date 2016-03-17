/*2:*/
#line 187 "./construct.w"

#if !defined(_CONSTRUCT_H_)
#define _CONSTRUCT_H_
/*6:*/
#line 230 "./construct.w"

#include "length.h"

/*:6*/
#line 190 "./construct.w"

extern const char*construct_rcs_id;
/*9:*/
#line 254 "./construct.w"

#define CONSTRUCT_CANONICAL 0




/*:9*//*11:*/
#line 291 "./construct.w"

#define CONSTRUCT_RANDOM 1


/*:11*//*16:*/
#line 388 "./construct.w"

#define CONSTRUCT_GREEDY 2

/*:16*/
#line 192 "./construct.w"

/*5:*/
#line 224 "./construct.w"

length_t
construct(const int n,int*tour,const int heuristic,const long heur_param);

/*:5*//*51:*/
#line 881 "./construct.w"

length_t construct_matching(int n,int*mate,int alg,long alg_param);


/*:51*/
#line 193 "./construct.w"

#endif

/*:2*/
