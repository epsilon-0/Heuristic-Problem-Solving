/*2:*/
#line 164 "./length.w"

#if !defined(_LENGTH_H_)
#define _LENGTH_H_

#if defined(LENGTH_USE_RCS_ID)
static const char*length_rcs_id= "$Id: length.w,v 1.122 1998/07/16 21:58:55 neto Exp neto $";
#endif

#if defined(LENGTH_LONG_LONG)

typedef long long length_t;
# define LENGTH_TYPE_IS_EXACT (1)
# define LENGTH_TYPE_IS_INTEGRAL (1)
# define INFINITY \
 ((( ((long long)0x7FFF) << 16   \
     |((long long)0xFFFF)) << 16 \
     |((long long)0xFFFF)) << 16 \
     |((long long)0xFFFF))  

# define length_t_pcast(Y) (long)((Y)>>32),(unsigned long)((Y)&0xffffffff)
# define length_t_spec "(0000%ld*2^32+%ld)"
#else 
#if defined(LENGTH_DOUBLE)

typedef double length_t;
# define LENGTH_TYPE_IS_EXACT (0)
# define LENGTH_TYPE_IS_INTEGRAL (0)
#   include <math.h>
#   include <float.h>
#   define LENGTH_MACHINE_EPSILON  DBL_EPSILON
# define INFINITY DBL_MAX
# define length_t_pcast(Y) ((double)(Y))
# define length_t_spec "(0*2^32+%f)"
#else 
#if defined(LENGTH_FLOAT)

typedef float length_t;
# define LENGTH_TYPE_IS_EXACT (0)
# define LENGTH_TYPE_IS_INTEGRAL (0)
#   include <math.h>
#   include <float.h>
#   define LENGTH_MACHINE_EPSILON  FLT_EPSILON
# define INFINITY FLT_MAX
# define length_t_pcast(Y) ((double)(Y))
# define length_t_spec "(000*2^32+%.3f)"
#else 

typedef int length_t;
# define LENGTH_TYPE_IS_EXACT (1)
# define LENGTH_TYPE_IS_INTEGRAL (1)
# define INFINITY (0x7FFFFFFF)
# define length_t_pcast(Y) (Y)
# define length_t_spec "(00*2^32+%d)"
#endif 
#endif 
#endif 

#endif /*:2*/
