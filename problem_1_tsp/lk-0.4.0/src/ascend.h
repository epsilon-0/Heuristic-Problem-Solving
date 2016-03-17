/*9:*/
#line 244 "./ascend.w"

#if !defined(_ASCEND_H_)
#define _ASCEND_H_
/*14:*/
#line 303 "./ascend.w"

void ascend_setup(int the_n);
void ascend_cleanup(void);
double*const ascend_best_lambda(void);

/*:14*//*24:*/
#line 475 "./ascend.w"

length_t ascend(const int n,double upper_bound_len);
length_t ascend_alpha_beta(const int n,double upper_bound_len,double alpha,double beta);

/*:24*/
#line 247 "./ascend.w"

#endif


/*:9*/
