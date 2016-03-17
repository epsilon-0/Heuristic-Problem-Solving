


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

\def\Rprime{R'}
\def\9#1{{\sl #1}} % Used to control formatting of 'at'::  index entries
@f Rprime TeX
@s prng_t int
@s prng_kind_t int
@s gb_prng_t int
\def\vx{v_}
\def\nx{n_}
@f v_1 TeX
@f v_2 TeX
@f n_1 TeX
@f n_2 TeX

{\obeylines
$Log: prng.w,v $
Revision 1.10  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.9  1998/04/16 16:31:05  neto
Now include stdlib too.

Revision 1.8  1997/12/13  19:43:32  neto
Added math.h

Revision 1.7  1997/12/06 17:59:11  neto
Fixed a minor NaN in test output. (It was harmless too.)
Improved the index entries.

Revision 1.6  1997/12/06 16:25:45  neto
Compensate for asymmetric [0,1) interval during normal compuation, and
try to avoid blowup at the same time.
Test normal output.

Revision 1.5  1997/12/05  21:40:54  neto
Allow inlining or not inlining.

Revision 1.4  1997/12/05  20:43:11  neto
Changed the generator label type to an enumerated type.

Revision 1.3  1997/12/05  20:35:29  neto
I finished converting to [0,1) on double 01.
I also converted the generator labels to an enumeration.  That should
ease maintenance a wee bit, and it might help GCC optimize.

Revision 1.2  1997/12/05  20:09:08  neto
Tried to fix double 01 routine, but I can't think of a good way.
So I'm converting to [0,1) instead.

Revision 1.1  1997/12/04  22:16:22  neto
Initial revision

}

@*PRNG.
This is a simple wrapper for random number generators.
It serves two purposes.  First, it provides generic access to different
kinds of random number generators.  Second, it provides extra services
beyond just uniform distributions.  

@ In {\sl The Art of Computer Programming}, Donald Knuth advises 
experimenters
to verify their results with several different random number generators.
That's right, different {\it generators}, not just different seeds.
This  module makes it easy to use different generators by accesing them
through the same namespace.
@^Knuth, Donald Ervin@>
@:Art of Computer Programming, The@>

@ Most random number generators provide access to uniform 
distributions, and nothing else.  This module transforms the uniform
distribution into others, such as the normal distribution.  
The base generator need only provide access to integers uniformly distributed
over $\{0,\ldots,2^{31}-1\}$, \ie, the full non-negative range of 
two's-complement 32-bit arithmetic.

@ One should not use random number generators without becoming acquainted with
Chapter 3 of Knuth's life work, {\sl The Art of Computer Programming}.
The third edition of Volume 2 was published in the fall of 1997, with new
recommendations on generators, and even some \CEE/ code.
@^Knuth, Donald Ervin@>
@:Art of Computer Programming, The@>

@ The interface to this module is as follows.

Function |prng_t *prng_new(prng_kind_t kind, int seed)| 
returns a new random number stream initialized with the given seed.
The generator algorithm to be used is specified by the |kind|
value.  The |kind| value must be drawn from the enumerated list defined 
in header 
file \file{prng.h}.

Function |int prng_unif_int(prng_t *g, long m)| 
returns an integer drawn from the uniform
distribution over integers in the interval from 0 through $m-1$.  
The upper bound $m$ should be less than $2^{31}$ (and positive!).
This function uses the next few bits provided by stream |g|.

Function |double prng_unif_double_01(prng_t *g)|
returns a |double| value drawn uniformly from the half-open interval 
$[0,1)$.
That is, the answer |x| satisfies $0 \le x < 1$.
This function uses the next few bits provided by stream |g|.

Function |double prng_unif_double_range(prng_t *g, double a, double b)|
returns a |double| value drawn uniformly from the half-open interval 
$[a,b)$, subject to numerical stability.
This function uses the next few bits provided by stream |g|.

Function |double prng_normal(prng_t *g, double mean, double stddev)| answers 
a number drawn from a normal distribution with the given mean and standard
deviation.  
It uses bits from stream |g|.

Function |prng_free(prng_t *g)| shuts down the given generator and
deallocates its resources.

Function |int prng_kind_from_name(char *name)| maps a generator name
to its kind number, suitable for passing into |prng_new|.
If the name doesn't match one of the generators, it returns a default
kind number.
Function |const char *prng_name_from_kind(int kind)| computes
the opposite mapping.

Function |int prng_kind(prng_t *g)| returns the integer identifying the
kind of generator that |g| is.

@ The outline of this module is as follows.  

Some of it is complicated because I allow the option of configuring
the software to inline some
of the functions.  In my computing environment, inlining slows down
the code a whole lot.

@c

const char *prng_rcs_id = "$Id: prng.w,v 1.10 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
@<System headers@>@;
@<Module headers@>@;
#include "prng.h"

#define inline_def  /* Force compilation with an address. */
@<Inline subroutines@>@;
#undef inline_def
@<Subroutines@>@;

@ The header file should announce the public, types, values, and subroutines
to the world.


@
@(prng.h@>=
#if !defined(_PRNG_H_)
#define _PRNG_H_
@<Early headers@>@;
@<Type definitions@>@;
@<Full function prototypes@>@;

#include "prngconfig.h"
#if PRNG_DESIRE_INLINING && COMPILER_SUPPORTS_INLINE
#define inline_proto inline extern
#define inline_def inline extern
#include <math.h> /* We need a prototyp for |ldexp|. */
@<Inline function prototypes@>@;
@<Inline subroutines@>@;
#undef inline_proto
#undef inline_def
#else
#define inline_proto
@<Inline function prototypes@>@;
#undef inline_proto
#endif

#endif /* |defined(_PRNG_H_)| */

@
@<Full function prototypes@>=
prng_t *prng_new(prng_kind_t kind, int seed);
double prng_normal(prng_t *g, double mean, double stddev);
void prng_free(prng_t *g);
int prng_kind_from_name(char *name);
const char *prng_name_from_kind(int kind);
int prng_kind(prng_t *g);

@
@<Inline function prototypes@>=
inline_proto int prng_unif_int(prng_t *g, long m);@;
inline_proto double prng_unif_double_01(prng_t *g);@;
inline_proto double prng_unif_double_range(prng_t *g, double a, double b);@;

@ The generic generator structure wraps generators providing
streams of integers.

@<Type definitions@>=
typedef enum { @<Generator labels@> } prng_kind_t;
typedef struct {
	prng_kind_t kind;
	int seed;
	@<Other generic fields@>@;
	union {
		@<Generator-specific structures@>@;
	} gen;
} prng_t;

@ Each of the four functions is basically a |switch| statement.
Yes, I could have used \CPLUSPLUS/, or I could have used function pointers.
I chose a |switch| statement so that we can take better advantage of inlining.

Here are the outlines to the basic functions.  The others are more involved,
but can be coded generically.

@<Subroutines@>=
prng_t *
prng_new(prng_kind_t kind, int seed)
{
	prng_t *g = new_of(prng_t);
	errorif(g==NULL,"Couldn't allocate a new generic random number generator");
	g->kind = kind;
	switch(kind) {
	@<|prng_new| cases@>@;
	default: errorif(1,"No such kind of random number generator: %d",kind);
	}
	@<Initialize the generic fields@>@;
	return g;
}

void
prng_free(prng_t *g)
{
	if (g) {
		switch(g->kind) {
		@<|prng_free| cases@>@;
		default: break;  /* Who cares now? */
		}
	}
}

@
I have chosen to inline some time-critical functions, at least when
used within this compilation unit.
Although it isn't strict ANSI \CEE/, most compilers support inlining
in one way or another.
Don't worry, GNU Autoconf makes the configuration header \file{config.h}
define |inline| in an appropriate way so that it won't break compilers
that don't provide inlining.  

@<Inline subroutines@>=
inline_def int
prng_unif_int(prng_t *g, long m)
{
	switch(g->kind) {
	@<|prng_unif_int| cases@>@;
	default: errorif(1,"No such kind of random number generator: %d",g->kind);
		return 0; /* Satisfy GCC's dataflow analyzer. */
	}
}

@ We've used the |errorif| checking and reporting facility, and the memory
management facilities.
@<Early headers@>=
#include "error.h"

@
@<Module headers@>=
#include "memory.h"

@ We've also used the defintion of |NULL| from file \file{<stddef.h>}.
We may as well get all the standard goodies.
@<System headers@>=
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

@ An IEEE-754 double precision number has 53 bits of mantissa.  
It's not good enought to just fill the most significant 31 bits with random
bits and leave the rest all zeros.  (I found out the hard way!)

We start with an exponent of 0 and fill the whole mantissa with random bits.
In the case that the underlying representation uses a radix of 2,
\ie, all modern systems I know of,
we can fill the mantissa with two samples.
Otherwise, we fill the mantissa one bit at a time.  That's slow, but
I don't expect it to ever be executed.
@^system dependencies@>

The first verision of this code just put 60 random bits into the mantissa,
hoping to close the interval on the right with some rounding.
But any rounding whatever skews the distribution, all through the interval.  
So we only put in as many bits as there are bits in the mantissa.
The skew isn't much, but it's easy to get rid of, just by paying close
attention to |FLT_RADIX| and |DBL_MANT_DIG|.

@<Inline subroutines@>=
inline_def double
prng_unif_double_01(prng_t *g)
{
#if FLT_RADIX==2
	double i = prng_unif_int(g,1<<30); /* Force sequencing for portability. */
	double j = prng_unif_int(g,1<<(DBL_MANT_DIG-30));
	return ldexp(ldexp(i,-30)+j,-(DBL_MANT_DIG-30));
#else /* Very uncommon case. */
	double x=0.0,full=0.0;
	while (full<1.0) {
		x = ldexp(x+prng_unif_int(g,2),-1);
		full = ldexp(1.0+full,-1);
	}
	return x;
#endif
}

@ We've used the |ldexp| function from the standard \CEE/ library, and
the definitions of implementation-dependent constants |DBL_MANT_DIG| and 
|FLT_RADIX|.
@<System headers@>=
#include <float.h>
#include <math.h>



@ The |prng_unif_double_range| function is very simple, but very useful.
Defining it here is just a convenience.  
I make no guarantees about getting the range exactly right, mostly
because floating point arithmetic is so darned unreliable.

Note that we don't even need to check whether $a < b$ or if $a > b$ or
even if $a=b$.  We get sensible results in all cases.

I will {\it not\/} concern myself with catastrophic cancellation.
I could have used |(1-t)*a + t*b| without worry because |t| is random,
but that would have cost two multiplications.  That might be fine on
a superscalar architecture. Hmmm.

%I was going to write that would {it not\/} concern myself with catastrophic
%cancellation, but thought of an easy and fast way to avoid subtraction.
%Alas.  That is, the subtraction in the obvious code 
%|return a+(b-a)*prng_unif_double_01(g)|,
%subtraction might lose a lot of precision.  
%I've gone with equally obvious code that avoids a dangerous subtraction.

@<Inline subroutines@>=
inline_def double
prng_unif_double_range(prng_t *g, double a, double b)
{
	const double t = prng_unif_double_01(g);
	return a + t*(b-a);
}


@ One can get two samples from a normal distribution by transforming
two samples from a uniform distribution.  It's not obvious.
See Knuth's {\sl The Art of Computer Programming}, Volume 2, Section 3.4.1,
algorithm P.  (That's why one should get those books.)
@^Knuth, Donald Ervin@>
@:Art of Computer Programming, The@>

We generate samples in pairs, so must keep one in the generic portion
of the generator structure, and an indication of whether or not it is there.
(After all, bits are just bits.)

The value |saved_normal| is a sample from the normal distribution with mean
0 and standard deviation 1.

@<Other generic fields@>=
int have_saved_normal;
double saved_normal;

@
@<Initialize the generic fields@>=
g->have_saved_normal=0;

@ Here's the non-obvious code.


@<Subroutines@>=
double
prng_normal(prng_t *g, double mean, double stddev)
{
	if ( g->have_saved_normal ) {
		g->have_saved_normal = 0; 
		return mean + stddev * g->saved_normal; 
	} else {
		double v_1, v_2, s, n_1, n_2;
		do {
			v_1 = prng_unif_double_01(g);
			v_2 = prng_unif_double_01(g);
			@<Transform the intervals to $[-1,0)\cup(0,-1]$@>@;
			s = v_1*v_1 + v_2*v_2;
		} while ( s >= 1 );
		@<Carefully compute normal samples |n_1| and |n_2|@>@;
		g->saved_normal = n_2;
		g->have_saved_normal=1;
		return mean + n_1*stddev;  /* Alas, what to do with |DBL_MAX|, now or later? */
	}
}

@ Now, the samples we get back from |prng_unif_double_01(g)| are
drawn from a 
uniform distribution over the interval $[0,1)$.   
The rest of the algorithm requires $[-1,1]$.  In fact, it blows up
to infinity if both |v_1| and |v_2| are 0.

So we can feed two birds with one crust by transforming 
$[0,1)$ to
 $[-1,0)\cup(0,-1]$.
First, it makes the result symmetric.
Second, it avoids the double 0, even if the chances of getting would
have been miniscule.
@^miniscule@>

@<Transform the intervals to $[-1,0)\cup(0,-1]$@>=
v_1 = 2*v_1-1; @+ if ( v_1 >= 0 ) v_1 = 1-v_1;
v_2 = 2*v_2-1; @+ if ( v_2 >= 0 ) v_2 = 1-v_2;

@  
Once we have |v_1| and |v_2| uniform in $[-1,1]$, normal samples |n_1| and |n_2|
are defined
by
$ n_1 = v_1 \cdot R'$ and 
$ n_2 = v_2 \cdot R'$, where $R' = \sqrt{-2 \log(s)/s}$.

When |s| is very close to zero, $-\log(s)/s$  blows up to very large 
positive values.  So we have to pay close attention to floating point
errors.  We have both |v_1| and |v_2| very small, but we also have
$R'$
very big.  
If |v_1| and |v_2| are shrinking to zero at similar rates, then 
the $R'$ grows to infinity much faster than either
|v_1| or |v_2| shrinks to zero.  
(Hint: Set $v_1=v_2=v$ and small, and therefore $s=2v^2$ and then cancel.)
So if we get a blowup in the calculation, then
we should go to infinity, but with the same sign as the |v| in question.

@<Carefully compute normal samples |n_1| and |n_2|@>=
{ double Rprime;
errno = 0;
Rprime = sqrt(-2*log(s)/s);
switch(errno) {
case ERANGE:@;
case EDOM:@;
	n_1 = v_1 < 0 ? -DBL_MAX : DBL_MAX;
	n_2 = v_2 < 0 ? -DBL_MAX : DBL_MAX;
	break;
default: @;
	n_1 = v_1 * Rprime;
	n_2 = v_2 * Rprime;
}
errno=0;
}


@ 
We've used the |errno| error detection facility.

@<System headers@>=
#include <errno.h>




@*Accessing the generators.
Now that the wrapper work is mostly done, accessing each generator is
rather easy.

@*1 GB\_\,FLIP. 
The first generator was published in Knuth's {\sl The Stanford GraphBase}
as the source module \module{GB\_\,FLIP}.
I've included change file \file{gb\_\,flip.ch} in this package.
It adds access to multiple
random number streams in ordinary object-oriented fashion.
@^Knuth, Donald Ervin@>
@:Stanford GraphBase, The@>

@<Generator labels@>=
PRNG_GB_FLIP,

@ We need to import the interface to the GraphBase coin flipper.  
We import it in file \file{prng.h} because the header needs to be
able to declare the type |gb_prng_t|.
@<Early headers@>=
#include "gb_flip.h"

@
@<Generator-specific structures@>=
gb_prng_t *gb_flipper;

@
@<|prng_new| cases@>=
case PRNG_GB_FLIP:
	g->gen.gb_flipper = gb_prng_new(seed);
	errorif(g->gen.gb_flipper == NULL,"Couldn't allocate a new GB_FLIP generator");
	break;


@
@<|prng_free| cases@>=
case PRNG_GB_FLIP:
	gb_prng_free(g->gen.gb_flipper);
	break;

@
@<|prng_unif_int| cases@>=
case PRNG_GB_FLIP:
	return gb_prng_unif_rand(g->gen.gb_flipper,m);


@*1 NRAND48.
Most variants of Unix have a 48-bit linear congruential generator.  
That is, given a 48-bit integer $X_n$, it computes
$$X_{n+1} =  (a\cdot X_n+c)\,\, \mod\, m$$
with appropriate values of $a$ and $c$; also, $m=2^{48}$, forcing $X_{n+1}$
to also be a 48-bit integer.
See the \type{nrand48} manual page for the details of the particular
generator used by the library, and Knuth's {\sl The Art of Computer 
Programming} for the attributes of linear congruential generators in
general.
@^Knuth, Donald Ervin@>
@:Art of Computer Programming, The@>
@^Unix@>

There are many variants of the 48-bit generator, each giving doling out
different kinds of numbers: integers, natural numbers, and floating point
numbers.  I've chosen to use |nrand48| because it doles out natural numbers in 
the range $[0,2^{31})$ and uses explicitly-passed state.

@<Generator labels@>=
PRNG_NRAND48,

@ Type |short| had better be 16-bit integers.
@^system dependencies@>
@<Generator-specific structures@>=
#if SIZEOF_SHORT==2
unsigned short nrand48_state[3];
#else
#error "short int is not 16 bits"
#endif

@ We're only given a |long| seed, which is usually 32-bits.  
As per the description of |srand48| (on Solaris at least), we put the seed
bits into the high-order bits of the 48-bit state, and fill the lower
bits with |0x330E|.

@<|prng_new| cases@>=
case PRNG_NRAND48:
#if HAVE_NRAND48
	g->gen.nrand48_state[0] = 0x330E;
	g->gen.nrand48_state[1] = seed & 0xffff;
	g->gen.nrand48_state[2] = (seed >> 16) & 0xffff;
#else
	errorif(1,"Sorry, nrand48 is not available on this system.");
#endif
	break;


@ We own the state, so there's nothing to free.
@<|prng_free| cases@>=
case PRNG_NRAND48:
	break;

@ Here things get a little interesting.  We get random integers in
the range $[0,2^{31})$.  We must reduce them to the range $[0,m)$.

Most of this code comes from Knuth's \file{gb\_\,flip}.  See
{\sl The Stanford GraphBase}, page 221.  
(At least that's the page number in my edition.)
Of course, I've substituted |nrand48| for |gb_next_rand|.
@^Knuth, Donald Ervin@>
@:Stanford GraphBase, The@>

@<|prng_unif_int| cases@>=
case PRNG_NRAND48:
#if HAVE_NRAND48
	{ unsigned long t = 0x80000000UL- (0x80000000UL%m); 
	long r;
	do {
		r = nrand48(g->gen.nrand48_state);
	} while ( t<= (unsigned long) r);
	return r%m;
	}
#else
	errorif(1,"Sorry, nrand48 is not available on this system.");
	return 0; /* Satisfy GCC's dataflow analysis. */
#endif
	break;

@ We need a proper declaration for |nrand48|.  Some operating systems
don't have them, so we substitute one if necessary.
@<Early headers@>=
#if HAVE_NRAND48
#include <stdlib.h>
#define FIXINCLUDES_NEED_NRAND48
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_NRAND48
#endif

@*Finishing up. 
To ease the burden on the users of this module, it is useful to be able to 
map the names of generators to their numbers, and vice versa.


@<Define name mapping@>=
const static char *prng_name_map[PRNG_NUM_KINDS] = {/* Must be in the right order. */
	"gb_flip",
	"nrand48"
};

@
If the name does not match a generator name, we answer the default kind.

@<Subroutines@>=
int
prng_kind_from_name(char *name) {
	int i;
	@<Define name mapping@>@;
	for(i=0;i<PRNG_NUM_KINDS;i++) {
		if ( 0==strcmp(name,prng_name_map[i]) ) return i;
	}
	return PRNG_DEFAULT;
}

const char *
prng_name_from_kind(int kind) {
	@<Define name mapping@>@;
	errorif(kind < 0 || kind >= PRNG_NUM_KINDS, 
		"No such kind of pseudo-random number generator: %d",kind);
	return prng_name_map[kind];
}

@ It might also be useful to ask a generator its kind.
@<Subroutines@>=
int
prng_kind(prng_t *g) {
	return g->kind;
}

@
@<Generator labels@>=
PRNG_NUM_KINDS,
PRNG_DEFAULT=PRNG_GB_FLIP

@*Self-test.
Here's a short program to test the generators.

@(prngtest.c@>=
#include <config.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prng.h"
int main(void);
int main(void) 
{
#define DO_UNIFORM
#define MEAN (0.5)
	printf(
		"  Uniform [0,1) double precision samples\n" @|
		"  eventually should have mean near 0.5, stddev near 0.28\n"
	);
	@<Test all the kinds of generators@>@;
#undef MEAN
#undef DO_UNIFORM

#define DO_NORMAL
#define MEAN (5.0)
#define STDDEV (2.0)
	printf(
		"  Normal double precision samples, mean 5, stddev 2\n" @|
		"  eventually should have mean near 5, stddev near 2\n"
	);
	@<Test all the kinds of generators@>@;
#undef STEDEV
#undef MEAN
#undef DO_NORMAL
	return 0;
}


@
@<Test all the kinds of generators@>=
{ int seed, kind;

for ( kind = 0 ; kind < PRNG_NUM_KINDS ; kind++ ) {
	printf("Generator %s\n", prng_name_from_kind(kind));
	if ( kind == PRNG_NRAND48 && !(HAVE_NRAND48) ) continue;
	for ( seed=42; seed<150; seed +=50) {
		prng_t *g;
		printf(" Seed %d\n",seed);
		g = prng_new(kind,seed);
		@<Take 10000 samples@>@;
		prng_free(g);
	}
}
}

@ Here we print a few samples, along with the running mean and standard
deviation.

Occasionally on the first step the standard deviation computation
breaks, returning
a NaN (Not a Number).  
That's because on the first step the subtraction to compute the variance 
might answer a small negative number due to catastrophic cancellation.  
So if the variance
is computed as negative, we rail it to 0.  
This does not contaminate the test because the identity used to compute the 
variance is independent of the quality of the random numbers.
Besides, the identity is easily proved mathematically.

@<Take 10000 samples@>=
{
int i;
double sum, sum_sq, mean, stddev;	
sum_sq = sum = 0.0;
for (i=1;i<=10000;i++) {
	@<Take a |sample|@>@;
	sum += sample;
	sum_sq += sample*sample;
	switch(i) {
	case 1: case 2: case 3: case 4: case 5:
	case 10: case 100: case 250: case 500: case 1000: case 10000:
		mean = sum/i;
		{ const double variance = sum_sq/i - mean*mean;
			stddev = (variance < 0.0) ? 0.0 : sqrt(variance); }
		printf("%8d  sample = %9f  mean-%3.1f = %10.6f  stddev = %10.6f\n",
			i, sample, MEAN, mean-MEAN, stddev);
	break;
	default: break;
	}
}
}


@
@<Take a |sample|@>=
#if defined(DO_UNIFORM)
const double sample = prng_unif_double_01(g);
#endif
#if defined(DO_NORMAL)
const double sample = prng_normal(g,MEAN,STDDEV);
#endif


@*Index.
