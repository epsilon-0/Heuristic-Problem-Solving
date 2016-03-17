/*11:*/
#line 291 "./match.w"

#include "prng.h"
/*12:*/
#line 296 "./match.w"

void match_setup(int n);
void match_cleanup(void);

/*:12*//*18:*/
#line 391 "./match.w"

void match_show(FILE*out);
void match_ps_out(FILE*ps_out,const char*name);

/*:18*//*20:*/
#line 447 "./match.w"

void
match_validate(length_t*validate_len,double*double_validate_len,
double*ordered_double_len,double*raw_len);


/*:20*//*25:*/
#line 517 "./match.w"

length_t match_construct(int alg,long alg_param);


/*:25*//*50:*/
#line 906 "./match.w"

void match_run(const int backtracking_levels,const int iterations,
prng_t*random_stream);

/*:50*/
#line 293 "./match.w"


/*:11*/
