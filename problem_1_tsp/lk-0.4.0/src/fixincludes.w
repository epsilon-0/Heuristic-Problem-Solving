



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
$Log: fixincludes.w,v $
Revision 1.159  1998/07/16 21:58:55  neto
Added the LGPL notice in each file.

Revision 1.158  1998/05/21 15:48:15  neto
use size t instead of int in gethostname.
Red Hat Linux (Biltmore) barfs now on ustat...

Revision 1.157  1997/12/13 19:43:57  neto
Added test for whether header defines prototypes for getopt.
But I give up my hands on it (at least in JITTER).

Revision 1.156  1997/12/04  21:28:51  neto
Added support for nrand48

Revision 1.155  1997/11/27  19:13:57  neto
Attempt at clean declaration of getopt and friends.

Revision 1.154  1997/11/15 19:03:46  neto
Fixed comments for CWEB.
Also, Autoconf macro is HAVE VPRINTF, not HAVE VFPRINTF...

Revision 1.153  1997/09/27 18:05:36  neto
Fixed RCS log behaviour.

Revision 1.152  1997/08/15  20:18:25  neto
Added Index major section.

Revision 1.151  1997/05/16  21:06:39  neto
Be less intrusive with vfprintf.

Revision 1.150  1997/05/16  21:01:52  neto
Fixed other unterminated hash ifs.
Also commented them.. :)

Revision 1.149  1997/05/16  20:49:20  neto
Put a hash endif on.

Revision 1.148  1997/05/16  20:36:37  neto
Put some support in from configure

Revision 1.147  1997/04/22  21:47:42  neto
SunOS 5.4 does not put struct rusage in sys/resource.h.
So I must handle it specially.  See the changes to
the Makefile as well.

Revision 1.146  1997/02/07  22:54:45  neto
Added scanf

Revision 1.145  1997/01/21  22:26:34  david
Line was too long.

Revision 1.144  1997/01/21  21:55:55  david
Added standard copyright notice by including copyrt.w

Revision 1.143  96/12/16  17:06:55  neto
Added time header.

Revision 1.142  96/08/16  16:50:13  neto
Fixed a preprocessor syntax error.
Added rcs id.

Revision 1.141  96/08/16  13:36:11  neto
Split resource stuff into resource stuff and gethostname

Revision 1.140  96/08/16  13:05:17  neto
Initial revision.

}

@*Missing prototypes.
Some operating environments don't provide full prototypes for some of
their library functions.  SunOS is guilty of this.  This module defines
these prototypes we need in a special header file \file{fixincludes.h}.  

Most of the missing prototypes are taken from P.~J.~Plauger's {\sl 
The Standard C Library}, Prentice-Hall, ISBN 0-13-131509-9.

Prototypes dealing with resources are taken from the SunOS manual page
for the respective functions.  They are not part of the standard C library.

@(fixincludes.h@>=
#if defined(OS_HAS_BROKEN_HEADERS) && !defined(_FIXINCLUDES_H_)
#define _FIXINCLUDES_H_

#if defined(FIXINCLUDES_USE_RCS_ID)
static const char *fixincludes_rcs_id = 
	"$Id: fixincludes.w,v 1.159 1998/07/16 21:58:55 neto Exp neto $";
#endif /* |defined(FIXINCLUDES_USE_RCS_ID)| */


int fclose(FILE *stream);
int fflush(FILE *stream);
int fprintf(FILE *stream, const char *format,...);
int fputc(int c, FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE*stream);
int scanf(const char *format,...);
int fscanf(FILE *stream, const char *format,...);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE*stream);
int printf(const char *format,...);

#if defined(FIXINCLUDES_NEED_VFPRINTF)
#if HAVE_VPRINTF
int vfprintf(FILE *stream, const char *format, va_list arg);
#else /* not |HAVE_VFPRINTF| */
#define vfprintf /* Just throw it away... */
#endif /* not |HAVE_VFPRINTF| */
#endif /* |defined(FIXINCLUDES_NEED_VFPRINTF)| */


#if defined(FIXINCLUDES_NEED_GETHOSTNAME)
#if HAVE_GETHOSTNAME
int gethostname(char *nameptr, size_t namelen);
#else 		/* not |HAVE_GETHOSTNAME| */
static int gethostname(char *nameptr, size_t namelen)
{ return strncpy(nameptr,"<unknown>",namelen); }
#endif 		/* not |HAVE_GETHOSTNAME| */
#endif /* |defined(FIXINCLUDES_NEED_GETHOSTNAME)| */


#if defined(FIXINCLUDES_NEED_RESOURCE_STUFF)
/* SunOS 5.4, a.k.a. Solaris 2.4 is peculiar.  Why, why, why? */
#if OS_IS_SUNOS && OS_VERSION_MAJOR==5 && OS_VERSION_MINOR==4 
#include <../ucbinclude/sys/rusage.h>
#endif /* |defined(FIXINCLUDES_NEED_RESOURCE_STUFF)| */
#if HAVE_GETPAGESIZE && HAVE_GETRUSAGE
int getpagesize(void);
int getrusage(int who, struct rusage *rusage);
#else /* not |(HAVE_GETPAGESIZE && HAVE_GETRUSAGE)| */
static int getpagesize(void) {return 0;}
static int getrusage(void) {return NULL;} /* Only resolve the function call. */
#endif /* not |(HAVE_GETPAGESIZE && HAVE_GETRUSAGE)| */
#endif /* |defined(FIXINCLUDES_NEED_RESOURCE_STUFF)| */

#if defined(FIXINCLUDES_NEED_TIME_STUFF)
#if HAVE_TIME_H
#include <time.h>
#else /* not |HAVE_TIME_H| */
typedef long time_t;
#endif /* not |HAVE_TIME_H| */
time_t time(time_t *);
#endif /* |defined(FIXINCLUDES_NEED_TIME_STUFF)| */

/* Solaris headers appear to not have a prototype for |getopt|. */
#if defined(FIXINCLUDES_NEED_GETOPT)
#if HAVE_GETOPT
int getopt(int argc, char * const argv[], const char *optstring);
#if LIBRARY_DEFINES_OPTARG_ETC && !HEADERS_DECLARE_OPTARG_ETC
extern char *optarg;
extern int optind, opterr, optopt;
#else
char *optarg;
int optind, opterr, optopt;
#endif /* |LIBRARY_DEFINES_OPTARG_ETC| */
#endif /* |HAVE_GETOPT| */
#endif /* |defined(FIXINCLUDES_NEED_GETOPT)| */

/* Solaris headers appear to not have a prototype for |nrand48|. */
#if defined(FIXINCLUDES_NEED_NRAND48)
#if HAVE_NRAND48
long nrand48(unsigned short int state[3]);
#endif /* |HAVE_NRAND48| */
#endif /* |defined(FIXINCLUDES_NEED_NRAND48)| */


#endif /* |defined(OS_HAS_BROKEN_HEADERS) && !defined(_FIXINCLUDES_H_)| */

@*Index.
