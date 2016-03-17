


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
$Log: error.w,v $
Revision 1.124  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.123  1998/05/08 22:47:34  neto
Make core dump on error when compiled with special flag

Revision 1.122  1997/12/13 17:25:38  neto
Re-engineered the thing.  It's now more CWEB-like, and has better and
more correct functionality. It also is disentangled from the memory
module.

Revision 1.121  1997/12/05  22:15:52  neto
Remove dependency of error.w on resource.w

Revision 1.120  1997/09/27 17:53:40  neto
Fixed RCS behaviour about prefix to Log.

Revision 1.119  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.118  1997/06/13  17:29:51  neto
I accidentally deleted the RCS id and the cleanup function.
I now put them back.

Revision 1.117  1997/06/13  17:13:10  neto
Fixed conflicting types for error real if.

Revision 1.116  1997/06/13  17:07:34  neto
ANSI C forbids use of compound expressions as lvalues, so I took the
parens out from around the errorif macro.

Revision 1.115  1997/06/13  16:17:19  neto
Make errorif macro like a real function call, instead of a statement.
It now won't break if it's the only statement in a branch of an
if or body of a loop.

Revision 1.114  1997/06/11  17:54:04  neto
Fixed a formatting error.

Revision 1.113  1997/05/16  20:38:52  neto
Added a comment about vfprintf and autoconf.

Revision 1.112  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.111  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.110  96/08/16  13:08:27  neto
Added vfprintf to the list of things needed.

Revision 1.109  96/08/16  13:04:43  neto
Added fixincludes.

Revision 1.108  96/08/15  14:33:59  neto
Fixed one more const-related warning.

Revision 1.107  96/08/15  14:24:30  neto
Fixed the broken cast so that gcc doesn't complain about losing the
const on assignment from \_\_FILE\_\_.

Revision 1.106  96/08/15  12:31:08  neto
Include interface to memory.h,  needed mem\_report

Revision 1.105  96/08/15  11:15:49  neto
Include interface to resource

Revision 1.104  96/07/29  17:09:21  neto
Fixed to compile.

Revision 1.103  96/07/29  16:19:48  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@* Reporting errors. 
The function |errorif| provides a handy shorthand for the usual test
and print code
sequence used after allocation routines.

Since this package uses, GNU Autoconf, we can be a little smarter about
using |HAVE_VFPRINTF|.  I don't know what the alternatives are --- I'm an
ANSI C guy!

@c
#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define FIXINCLUDES_NEED_VFPRINTF
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_VFPRINTF

#include "error.h"
const char *error_rcs_id="$Id: error.w,v 1.124 1998/07/16 21:58:55 neto Exp neto $";


@<Global variables@>@;
@<Module variables@>@;

@<Subroutines@>@;

@ The |errorif| macro is overly elaborate only because I want to know
the offending source file and source line.  Note that 0 can be cast into
(just about?) anything.  
The |errorif| macro behaves almost like a function call.  
Note that in all cases, all side effects in the condition and 
the error message arguments take place, even if the error condition
is false, and even if errors aren't being
checked at all.

Just be sure that
|error_at_line| and |error_in_file| aren't masked in this
scope by local definitions.  (This would be a great time for 
\CPLUSPLUS/'s scope resolution operator |::|.)

@(error.h@>=
@<Exported variables@>@;
@<Exported subroutines@>@;

#if defined(ERROR_NO_CHECK)
#define errorif  /* Side effects in the condition still occur. */
#else
#define @[errorif@] @[(error_in_file=__FILE__),(error_at_line=__LINE__),error_real_if@]
#endif

@
@<Global variables@>=
char const *error_in_file;
int error_at_line;

@
@<Exported variables@>=
extern const char *error_rcs_id;
extern char const *error_in_file; 
extern int error_at_line;


@ The |error_real_if| function actually does the hard work.  It checks to see
if the condition is true, and if so, shuts down the program, with
a message both on the standard output stream and the standard error output
stream.

@<Subroutines@>=
int
error_real_if(const int condition, const char *fmt,...)
{
	va_list args;
	va_start(args,fmt);
	if ( condition ) {
		@<Do abnormal ending external reporting and cleanup@>@;
		printf("%s:%d:",error_in_file,error_at_line);
		vfprintf(stdout,fmt,args);
		fputc('\n',stdout);
		fflush(stdout);
		fprintf(stderr,"%s:%d:",error_in_file,error_at_line);
		vfprintf(stderr,fmt,args);
		fputc('\n',stderr);
		fflush(stderr);
#if defined(ERROR_DUMP_CORE_ON_ERROR)
		*((int *)0) = 1;	/* Dump core */
#endif
		exit(1);
	}
	va_end(args); /* |__ksr__| and AIX want this */
	/* Used to be |va_end| only for SUNOS */
	return 0; /* We need a return value for the |errorif| macro. */
}

@
@<Exported subroutines@>=
int error_real_if(const int condition, const char *fmt,...);



@ Sometimes it is convenient to display diagnostics from other parts
of the program.  For example, we optionally display statistics
both before and after cleaning up.  This might eventually be useful,
with a little discipline, for detecting memory leaks.

This module defines hooks for calling external reporting and cleanup
functions and the rest of the program is charged with the responsibility
of using those hooks.

Additionally, each call to the hooked procedures is guarded by a test
to see if we're already in that procedure.  After all, the program might
trigger another error while cleaning up or reporting!
The guard prevents endless mutual recursion: termination with a deficient
error message is better than non-termination.


@<Do abnormal ending external reporting and cleanup@>=
if ( error_doing_precleanup_stats || error_doing_cleanup 
	|| error_doing_postcleanup_stats ) return 0;
if ( error_precleanup_stats != NULL ) {
	error_doing_precleanup_stats = 1;
	(*error_precleanup_stats)();
	error_doing_precleanup_stats = 0;
}
if ( error_cleanup != NULL ) {
	error_doing_cleanup = 1;
	(*error_cleanup)();
	error_doing_cleanup = 0;
}
if ( error_postcleanup_stats != NULL ) {
	error_doing_postcleanup_stats = 1;
	(*error_postcleanup_stats)();
	error_doing_postcleanup_stats = 0;
}

@
@<Module variables@>=
static int error_doing_precleanup_stats=0;
static int error_doing_cleanup=0;
static int error_doing_postcleanup_stats=0;

@ The hook functions expect no arguments and don't return a value.
@<Global variables@>=
void (*error_precleanup_stats)(void) = NULL;
void (*error_cleanup)(void) = NULL;
void (*error_postcleanup_stats)(void) = NULL;

@
@<Exported variables@>=
extern void (*error_precleanup_stats)(void);
extern void (*error_cleanup)(void);
extern void (*error_postcleanup_stats)(void);

@*Index.
