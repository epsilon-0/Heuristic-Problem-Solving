/*2:*/
#line 160 "./resource.w"

#include <config.h>
#include "lkconfig.h"
/*3:*/
#line 173 "./resource.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h> 
#if 0 
#if defined(__linux__)
size_t getpagesize(void);
#endif
#endif

/*:3*//*8:*/
#line 227 "./resource.w"

#include <sys/time.h>
#include <sys/resource.h>
#define FIXINCLUDES_NEED_RESOURCE_STUFF
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_RESOURCE_STUFF

/*:8*/
#line 163 "./resource.w"

/*9:*/
#line 240 "./resource.w"

#include "error.h"
#include "memory.h"
#include "resource.h"

/*:9*/
#line 164 "./resource.w"


/*7:*/
#line 219 "./resource.w"

static struct rusage*mark= NULL;
static int max_marks= -1,next_mark= -1;
static char**mark_name= NULL;

/*:7*/
#line 166 "./resource.w"

/*5:*/
#line 202 "./resource.w"

void
resource_setup(const int m)
{
mark= new_arr_of(struct rusage,m);
mark_name= new_arr_of(char*,m);
max_marks= m;
next_mark= 0;
}

/*:5*//*10:*/
#line 247 "./resource.w"

void
resource_cleanup(void)
{
if(mark!=NULL){
free_mem(mark);
free_mem(mark_name);
max_marks= next_mark= -1;
}
}

/*:10*//*12:*/
#line 270 "./resource.w"

int
resource_mark(const char*name)
{
if(max_marks<0)resource_setup(10);
errorif(next_mark>=max_marks,
"Too many resource marks; you need at least %d",max_marks+1);
getrusage(RUSAGE_SELF,mark+next_mark);
mark_name[next_mark]= dup_string(name);
next_mark++;
return next_mark-1;
}

/*:12*//*14:*/
#line 301 "./resource.w"

void
resource_report(FILE*out,int begin,int end)
{
float begin_s,end_s;
if(begin<0||begin>end||end>=next_mark){
fprintf(stderr,
"resource_report: bad begin==%d or end==%d (or both!); next_mark==%d.\n"
,begin,end,next_mark);
return;
}

begin_s= mark[begin].ru_utime.tv_sec+
mark[begin].ru_utime.tv_usec/((float)1000000);
end_s= mark[end].ru_utime.tv_sec+
mark[end].ru_utime.tv_usec/((float)1000000);
fprintf(out,"%s to\n\t%s\n\t%.2f user seconds",
mark_name[begin],mark_name[end],end_s-begin_s);

begin_s= mark[begin].ru_stime.tv_sec+
mark[begin].ru_stime.tv_usec/((float)1000000);
end_s= mark[end].ru_stime.tv_sec+
mark[end].ru_stime.tv_usec/((float)1000000);
fprintf(out," and %.2f system seconds\n",end_s-begin_s);

fprintf(out,"\tdelta max resident set size %8ld * %d bytes (ru_maxrss)\n",
mark[end].ru_maxrss-mark[begin].ru_maxrss,getpagesize());
fprintf(out,"\tdelta major page faults     %8ld (ru_majflt)\n",
mark[end].ru_majflt-mark[begin].ru_majflt);
fprintf(out,"\tdelta minor page faults     %8ld (ru_minflt)\n",
mark[end].ru_minflt-mark[begin].ru_minflt);
fflush(out);
}

/*:14*//*16:*/
#line 351 "./resource.w"


double resource_user_tick(void){return resource_user_tick_from(next_mark-1);}

double
resource_user_tick_from(int marknum)
{
struct rusage r;
double begin_s,end_s;
errorif(max_marks<0,"resource_user_tick called before resource_setup");
errorif(next_mark<=0,"resource_mark must be called before resource_user_tick");
errorif(marknum<0||marknum>=next_mark,
"invalid mark number %d",marknum);
getrusage(RUSAGE_SELF,&r);
begin_s= mark[marknum].ru_utime.tv_sec+
mark[marknum].ru_utime.tv_usec/((double)1000000);
end_s= r.ru_utime.tv_sec+
r.ru_utime.tv_usec/((double)1000000);
return end_s-begin_s;
}


/*:16*//*18:*/
#line 382 "./resource.w"

void
resource_abnormal_exit_output(void)
{
int i;
if(mark!=NULL&&mark_name&&next_mark<max_marks){
resource_mark("abnormal ending");
}else{
fprintf(stdout,"Abnormal ending\n");
fprintf(stderr,"Abnormal ending\n");
}
for(i= 0;i<next_mark-1;i++){
resource_report(stdout,i,next_mark-1);
resource_report(stderr,i,next_mark-1);
}
}

/*:18*/
#line 167 "./resource.w"

const char*resource_rcs_id= "$Id: resource.w,v 1.125 1998/07/16 21:58:55 neto Exp neto $";

/*:2*/
