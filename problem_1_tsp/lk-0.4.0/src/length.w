



\noindent Copyright \copyright 1994, 1995, 1996, 1997, 1998 David Neto
\smallskip

\noindent 
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
\smallskip

\noindent 
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
\smallskip

\noindent   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA  02111-1307, USA.
\smallskip

\noindent   
   You may contact David Neto via email at {\tt netod@@acm.org}, or with
   greater latency at
\smallskip
\noindent{\obeylines
     Department of Computer Science
     University of Toronto
     10 King's College Rd.
     Toronto, Ontario
     M5S 3G4
     Canada
}
\medskip


\noindent\hbox{}\hrule\hbox{}\penalty-1000
\vskip0.5cm\relax


@i webdefs.w
@i types.w

{\obeylines
$Log: length.w,v $
Revision 1.122  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.121  1998/06/19 16:24:09  neto
Added an integral test.

Revision 1.120  1998/01/24  16:58:02  neto
Changed the print spec for double to be shorter by 2 characters.  double
is the most common type for length t.

Revision 1.119  1997/12/04  16:37:33  neto
HUGE VAL is not necessarily a valid floating point number, so I
have replaced it with DBL MAX when we use doubles.

Revision 1.118  1997/10/28  20:41:47  neto
Fixed comments to compile.

Revision 1.117  1997/09/27 18:06:55  neto
Fixed RCS log behaviour.
Give more precision in printing double lengths.

Revision 1.116  1997/05/16  20:47:09  neto
Terminated the comment at the very end.  Doh!

Revision 1.115  1997/05/16  20:44:57  neto
Put comments on preprocesser conditionals, as per GNU standards.

Revision 1.114  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.113  96/12/20  16:26:11  neto
Put parens around macro

Revision 1.112  96/12/20  12:25:46  neto
Fixed an int vs. long int printf spec.

Revision 1.111  96/12/19  12:54:25  neto
Added exactness macro, and a machine epsilon macro.

Revision 1.110  96/12/13  15:09:13  neto
Fixed the double entry.  Added a float entry.

Revision 1.109  96/11/08  15:43:48  neto
Fixed print spec for double.

Revision 1.108  96/11/08  12:08:09  neto
Fixed comment about doubles.

Revision 1.107  96/11/08  12:05:30  neto
Added double option.  Also, doubles have 48 bits of mantissa, not 53.

Revision 1.106  96/08/15  14:45:33  neto
Restrict definition of length\_rcs\_id.

Revision 1.105  96/08/02  14:27:49  neto
Allow multiple includes.

Revision 1.104  96/07/29  17:08:14  neto
Fixed to compile

Revision 1.103  96/07/29  16:20:01  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@* Lengths.
The primary atomic abstraction of a TSP program is the distance between
two cities.  We need to declare a numerical type for values of this kind.

We would like for all our calculations to be repeatable and accurate.
This suggests the use of an integral type for our calculations.

However, we don't want to have distances overflow.  This suggests the
use of type |double| in place of |long| because |doubles| often have 53
bits of mantissa.  Compare this with the 32 bits that are often provided
for |long| or |int|.

When 32 bits (including sign) suffice, 
we will use |int|.  Otherwise we will use
type |long long| which is supported by some compilers.  These 
are integers with at least 64 bits of precision.

This module defines both the length type and the appropriate |printf|
output specification strings.  Hopefully this isolates this design decision
well enough that a simple |define| change in this module changes over the
entire program.

Type |long long| is supported both by GCC and the IBM AIX C compilers.
That's good.
However, I couldn't get 
|long long|s to print out properly on the Sun machines, so I compromise
by printing it out in two components: the upper and lower 32 bits.

This module only defines a header file.

@ Sometimes I use a floating point type, and sometimes I use an integral
type.  The two cases require different handling, so I define a compile-time
constant
|LENGTH_TYPE_IS_EXACT| that allows other source code to be compiled
according to the nature of the current meaning of the |length_t| type.

If a floating point type is used, we need to know what the machine epsilon
is.  This number is defined to be ``the difference between 1 and the least value
greater than 1 that is representable in the given floating-point type''.
See page 61 of P.~J.~Plauger's {\sl The Standard C Library} for this excerpt
from the ISO C Library Standard.  The values for types |float| and |double| 
are given in the header file \file{float.h} as macros |FLT_EPSILON| and
|DBL_EPSILON|, respectively.  We define |LENGTH_MACHINE_EPSILON| to be
the same as whichever machine epsilon is in effect.

@(length.h@>=
#if !defined(_LENGTH_H_)
#define _LENGTH_H_

#if defined(LENGTH_USE_RCS_ID)
static const char *length_rcs_id = "$Id: length.w,v 1.122 1998/07/16 21:58:55 neto Exp neto $";
#endif

#if defined(LENGTH_LONG_LONG)
	/* Use |long long|, and assume they are 8-bytes long */
	typedef long long length_t;
#	define LENGTH_TYPE_IS_EXACT (1)
#	define LENGTH_TYPE_IS_INTEGRAL (1)
#	define INFINITY \
	((( ((long long)0x7FFF) << 16   \
     |((long long)0xFFFF)) << 16	\
     |((long long)0xFFFF)) << 16	\
     |((long long)0xFFFF)) 	

#	define length_t_pcast(Y) (long)((Y)>>32),(unsigned long)((Y)&0xffffffff)
#	define length_t_spec "(0000%ld*2^32+%ld)"  
#else /* |!defined(LENGTH_LONG_LONG)| */
#if defined(LENGTH_DOUBLE)
	/* Use |double|. We get the infinity value from \file{math.h}. */
	typedef double length_t;
#	define LENGTH_TYPE_IS_EXACT (0)
#	define LENGTH_TYPE_IS_INTEGRAL (0)
#   include <math.h>
#   include <float.h>
#   define LENGTH_MACHINE_EPSILON  DBL_EPSILON
#	define INFINITY DBL_MAX
#	define length_t_pcast(Y) ((double)(Y))
#	define length_t_spec "(0*2^32+%f)"  
#else /* |!defined(LENGTH_DOUBLE)| */
#if defined(LENGTH_FLOAT)
	/* Use |float|. We get the infinity value from \file{math.h}. */
	typedef float length_t;
#	define LENGTH_TYPE_IS_EXACT (0)
#	define LENGTH_TYPE_IS_INTEGRAL (0)
#   include <math.h>
#   include <float.h>
#   define LENGTH_MACHINE_EPSILON  FLT_EPSILON
#	define INFINITY FLT_MAX
#	define length_t_pcast(Y) ((double)(Y))
#	define length_t_spec "(000*2^32+%.3f)"  
#else /* |!defined(LENGTH_FLOAT)| */
	/* Use |int|, and assume they are 4-bytes long */
	typedef int length_t;
#	define LENGTH_TYPE_IS_EXACT (1)
#	define LENGTH_TYPE_IS_INTEGRAL (1)
#	define INFINITY (0x7FFFFFFF)
#	define length_t_pcast(Y) (Y)
#	define length_t_spec "(00*2^32+%d)"  
#endif /* |!defined(LENGTH_FLOAT)| */
#endif /* |!defined(LENGTH_DOUBLE)| */
#endif /* |!defined(LENGTH_LONG_LONG)| */

#endif /* |!defined(_LENGTH_H_)| */
