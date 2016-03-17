


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
$Log: resource.w,v $
Revision 1.125  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.124  1997/12/05  22:15:52  neto
Remove dependency of error.w on resource.w

Revision 1.123  1997/10/17  21:50:37  neto
Added support for interval clicks from a given mark.

Revision 1.122  1997/09/27 18:04:39  neto
Fixed RCS log behaviour

Revision 1.121  1997/09/27 17:20:59  neto
Added a small convenience safety valve in resource mark.
I added this so the source code to tspgen wouldn't need to know
about this module.

Revision 1.120  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.119  1997/06/19  19:28:31  neto
Don't be so noisy on stderr.

Revision 1.118  1997/06/16  15:59:54  neto
No extra newline before a resource report.
Put initial brace of a function in column 0.

Revision 1.117  1997/05/16  21:15:43  neto
Now I don't need special behaviour for Linux regarding getpagesize.

Revision 1.116  1997/05/16  18:11:41  neto
Break locks by david and neto.
Include <config.h> and "lkconfig.h"

Revision 1.115  1997/05/16  18:09:40  neto
Include <config.h> and lkconfig.h

Revision 1.114  1997/04/23  20:44:34  neto
Added resource\_user\_tick

Revision 1.113  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.112  96/09/18  17:13:18  neto
Cleaner reporting.

Revision 1.111  1996/08/23  15:40:41  david
Fixed for linux.  Unistd declares gethostname and getpagesize only
if \_\_USE\_BSD is defined.  So I doit manually.

Revision 1.110  96/08/19  15:48:13  neto
Removed partial section.

Revision 1.109  96/08/19  15:46:55  neto
Added unistd.h for getpagesize().

Revision 1.108  96/08/16  13:05:03  neto
Added fixincludes.

Revision 1.107  96/08/15  12:35:29  neto
Make it pass -Wall

Revision 1.106  96/08/02  14:31:19  neto
Fixed the return value for resource\_mark.

Revision 1.105  96/07/30  16:43:27  neto
Bad begin or end marker in resource\_report is no longer a fatal error.
(This is so that some other error happening early on doesn't show up as
bad begin or end.)

Revision 1.104  96/07/29  17:20:55  neto
Fixed reporting in resource\_mark

Revision 1.103  96/07/29  17:07:51  neto
Fixed to compile.

Revision 1.102  96/07/29  16:20:13  neto
Added *\_rcs\_id.
Made sure RCS log is activated within this file.

}

@*Resource measurement.
We want to measure the performance of this program.
In particular, we will be measuring the
time required to build the auxiliary data structures, construct a starting
tour, and the run the Lin-Kernighan algorithm.

We'll use the resource measurement features introduced by Berkeley Unix.
The beginning of each of these phases of the program has an associated 
resource usage structure, and we have an extra one for the end of the 
execution as well.  These resource usage structures are stored in an array;
each entry has a message associated with it that describes the associated
phase.

This module has a few entry points: |resource_setup| initializes the module;
|resource_cleanup| cleans up for the purposes of termination;
|resource_mark| is called to mark the beginning of an execution phase;
|resource_user_tick| reports the
elapsed user seconds since the most recent call to |resource_mark|;
|resource_user_tick_from| reports the
elapsed user seconds since a given call to |resource_mark|;
|resource_report| reports the elapsed time between two given marks to
a given file handle.

@ The outline of the module is as follows.

@c
#include <config.h>
#include "lkconfig.h"
@<System headers@>@;
@<Module headers@>@;

@<Module variables@>@;
@<Subroutines@>@;
const char *resource_rcs_id="$Id: resource.w,v 1.125 1998/07/16 21:58:55 neto Exp neto $";

@ We will be using many routines from external libraries.  The interfaces
to those routines are described in the following headers.

@<System headers@>=
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>	/* For |getpagesize()| under AIX. */
#if 0 /* On May 16, 1997 I didn't need this anymore! */
#if defined(__linux__)
	size_t getpagesize(void);
#endif
#endif

@ The exported interface is contained in the {\tt resource.h} header file,
which has the following form.

@(resource.h@>=
extern const char *resource_rcs_id;
@<Exported subroutines@>@;

@ Procedure |resource_setup| allocates the space required for all the
marks that will be used during the execution of the program.  
For simplicity, we use an array to store all the marks; the caller 
supplies a number stating the maximum number of marks that will be required.

I could have chosen to grow the array as necessary, 
but that would complicate the memory
management module.  I decided that it is unlikely that the caller would not
know a maximum on the number of calls to |resource_mark|, so I left the 
design simple in this way.

@<Subroutines@>=
void
resource_setup( const int m ) 
{
	mark = new_arr_of(struct rusage,m);
	mark_name = new_arr_of(char *,m);
	max_marks = m;
	next_mark = 0;
}

@ We need to export this routine.
@<Exported subroutines@>=
void resource_setup(const int);

@ We need to declare these variables as module-level variables.
Just for safety's sake, we put sentinel values in the counters.

@<Module variables@>=
static struct rusage *mark = NULL;
static int max_marks = -1, next_mark = -1;
static char **mark_name = NULL;

@ We are using the Berkeley Unix resource usage interface, which is defined in
the following headers.

@<System headers@>=
#include <sys/time.h>
#include <sys/resource.h>
#define FIXINCLUDES_NEED_RESOURCE_STUFF
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_RESOURCE_STUFF

@ We also need the memory module interface.  While we're at it, let's grab
the error checking interface as well.

To ensure consistency between the procedure definitions and their declarations,
we add the exported interface of this module to this list.

@<Module headers@>=
#include "error.h"
#include "memory.h"
#include "resource.h"

@ Cleanup is easy.  The only trick is to make it idempotent.

@<Subroutines@>=
void
resource_cleanup( void ) 
{
	if ( mark != NULL ) {
		free_mem(mark);
		free_mem(mark_name);
		max_marks = next_mark = -1;
	}
}

@
@<Exported subroutines@>=
void resource_cleanup( void );

@ At a phase transition in the program, the program calls |resource_mark|.
This records the current resource usage in the next available slot.

We make sure we are writing to a valid slot.

We return the index into the array to the caller, so that they can do 
intelligent selective reporting later.

@<Subroutines@>=
int
resource_mark( const char *name ) 
{
	if ( max_marks < 0 ) resource_setup(10); /* A convenience. */
	errorif( next_mark>=max_marks, 
		"Too many resource marks; you need at least %d",max_marks+1);
	getrusage(RUSAGE_SELF,mark+next_mark);
	mark_name[next_mark] = dup_string(name);
	next_mark++;
	return next_mark-1;
}

@
@<Exported subroutines@>=
int resource_mark( const char * );




@ So far we've described how to put information into the |mark|
data structure.  But it's  only useful if we can get it out agian.
This is the job of |resource_report|.

This procedure is given a file handle and a pair of indices into the
mark array and prints the elapsed time between those two phase transitions.

Currently I only support elapsed time reporting.  This may change in the
future if I see the need.  I can imagine implementing an |fprintf|-style
interface via |vfprintf|.

@<Subroutines@>=
void
resource_report( FILE *out, int begin, int end ) 
{
	float begin_s, end_s;
	if( begin<0 || begin > end || end >= next_mark ) {
		fprintf(stderr,
		"resource_report: bad begin==%d or end==%d (or both!); next_mark==%d.\n"
			,begin,end,next_mark);
		return;
	}

	begin_s = mark[begin].ru_utime.tv_sec + 
		mark[begin].ru_utime.tv_usec/((float)1000000);
	end_s = mark[end].ru_utime.tv_sec + 
		mark[end].ru_utime.tv_usec/((float)1000000);
	fprintf(out,"%s to\n\t%s\n\t%.2f user seconds",
		mark_name[begin],mark_name[end], end_s - begin_s);

	begin_s = mark[begin].ru_stime.tv_sec + 
		mark[begin].ru_stime.tv_usec/((float)1000000);
	end_s = mark[end].ru_stime.tv_sec + 
		mark[end].ru_stime.tv_usec/((float)1000000);
	fprintf(out," and %.2f system seconds\n", end_s - begin_s);

	fprintf(out,"\tdelta max resident set size %8ld * %d bytes (ru_maxrss)\n",
		mark[end].ru_maxrss - mark[begin].ru_maxrss, getpagesize());
	fprintf(out,"\tdelta major page faults     %8ld (ru_majflt)\n",
		mark[end].ru_majflt - mark[begin].ru_majflt);
	fprintf(out,"\tdelta minor page faults     %8ld (ru_minflt)\n",
		mark[end].ru_minflt - mark[begin].ru_minflt);
	fflush(out);
}

@
@<Exported subroutines@>=
void resource_report( FILE *, int, int );


@ Sometimes it is useful to measure elapsed time without the need
for the relatively heavy-weight procedure of calling |resource_mark|.
Function |resource_user_tick| just returns the number of user seconds
elapsed since the most recent call to |resource_mark|.  No structures
are stored, so this is suitable for ongoing monitoring of the
program: we don't need to know in advance how often we might
call this function.

Function |resource_user_tick_from(int marknum)| returns the number of seconds
since a given mark.

@<Subroutines@>=

double resource_user_tick(void) {return resource_user_tick_from(next_mark-1);}

double
resource_user_tick_from( int marknum ) 
{
	struct rusage r;
	double begin_s, end_s;
	errorif( max_marks<0, "resource_user_tick called before resource_setup");
	errorif( next_mark<=0, "resource_mark must be called before resource_user_tick");
	errorif( marknum < 0 || marknum >= next_mark, 
			"invalid mark number %d", marknum);
	getrusage(RUSAGE_SELF,&r);
	begin_s = mark[marknum].ru_utime.tv_sec + 
		mark[marknum].ru_utime.tv_usec/((double)1000000);
	end_s = r.ru_utime.tv_sec + 
		r.ru_utime.tv_usec/((double)1000000);
	return end_s-begin_s;
}


@
@<Exported subroutines@>=
double resource_user_tick_from( int marknum );
double resource_user_tick( void );


@ Finally, we want some summary output when the program exits abnormally.
Procedure |resource_abnormal_exit_output| does just that.

@<Subroutines@>=
void
resource_abnormal_exit_output(void) 
{
	int i;
	if ( mark != NULL && mark_name && next_mark < max_marks ) {
		resource_mark("abnormal ending");
	} else {
		fprintf(stdout,"Abnormal ending\n");
		fprintf(stderr,"Abnormal ending\n");
	}
	for ( i=0;i<next_mark-1; i++ ) {
		resource_report(stdout,i,next_mark-1);
		resource_report(stderr,i,next_mark-1);
	}
}

@
@<Exported subroutines@>=
void resource_abnormal_exit_output(void);

@*Index.
