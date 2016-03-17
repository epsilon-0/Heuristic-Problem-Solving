/*1:*/
#line 134 "./fixincludes.w"

#if defined(OS_HAS_BROKEN_HEADERS) && !defined(_FIXINCLUDES_H_)
#define _FIXINCLUDES_H_

#if defined(FIXINCLUDES_USE_RCS_ID)
static const char*fixincludes_rcs_id= 
"$Id: fixincludes.w,v 1.159 1998/07/16 21:58:55 neto Exp neto $";
#endif 


int fclose(FILE*stream);
int fflush(FILE*stream);
int fprintf(FILE*stream,const char*format,...);
int fputc(int c,FILE*stream);
size_t fread(void*ptr,size_t size,size_t nmemb,FILE*stream);
int scanf(const char*format,...);
int fscanf(FILE*stream,const char*format,...);
size_t fwrite(const void*ptr,size_t size,size_t nmemb,FILE*stream);
int printf(const char*format,...);

#if defined(FIXINCLUDES_NEED_VFPRINTF)
#if HAVE_VPRINTF
int vfprintf(FILE*stream,const char*format,va_list arg);
#else 
#define vfprintf 
#endif 
#endif 


#if defined(FIXINCLUDES_NEED_GETHOSTNAME)
#if HAVE_GETHOSTNAME
int gethostname(char*nameptr,size_t namelen);
#else   
static int gethostname(char*nameptr,size_t namelen)
{return strncpy(nameptr,"<unknown>",namelen);}
#endif   
#endif 


#if defined(FIXINCLUDES_NEED_RESOURCE_STUFF)

#if OS_IS_SUNOS && OS_VERSION_MAJOR==5 && OS_VERSION_MINOR==4
#include <../ucbinclude/sys/rusage.h>
#endif 
#if HAVE_GETPAGESIZE && HAVE_GETRUSAGE
int getpagesize(void);
int getrusage(int who,struct rusage*rusage);
#else 
static int getpagesize(void){return 0;}
static int getrusage(void){return NULL;}
#endif 
#endif 

#if defined(FIXINCLUDES_NEED_TIME_STUFF)
#if HAVE_TIME_H
#include <time.h>
#else 
typedef long time_t;
#endif 
time_t time(time_t*);
#endif 


#if defined(FIXINCLUDES_NEED_GETOPT)
#if HAVE_GETOPT
int getopt(int argc,char*const argv[],const char*optstring);
#if LIBRARY_DEFINES_OPTARG_ETC && !HEADERS_DECLARE_OPTARG_ETC
extern char*optarg;
extern int optind,opterr,optopt;
#else
char*optarg;
int optind,opterr,optopt;
#endif 
#endif 
#endif 


#if defined(FIXINCLUDES_NEED_NRAND48)
#if HAVE_NRAND48
long nrand48(unsigned short int state[3]);
#endif 
#endif 


#endif 

/*:1*/
