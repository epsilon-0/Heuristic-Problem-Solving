/*1:*/
#line 139 "./error.w"

#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define FIXINCLUDES_NEED_VFPRINTF
#include "fixincludes.h"
#undef FIXINCLUDES_NEED_VFPRINTF

#include "error.h"
const char*error_rcs_id= "$Id: error.w,v 1.124 1998/07/16 21:58:55 neto Exp neto $";


/*3:*/
#line 183 "./error.w"

char const*error_in_file;
int error_at_line;

/*:3*//*9:*/
#line 273 "./error.w"

void(*error_precleanup_stats)(void)= NULL;
void(*error_cleanup)(void)= NULL;
void(*error_postcleanup_stats)(void)= NULL;

/*:9*/
#line 153 "./error.w"

/*8:*/
#line 267 "./error.w"

static int error_doing_precleanup_stats= 0;
static int error_doing_cleanup= 0;
static int error_doing_postcleanup_stats= 0;

/*:8*/
#line 154 "./error.w"


/*5:*/
#line 199 "./error.w"

int
error_real_if(const int condition,const char*fmt,...)
{
va_list args;
va_start(args,fmt);
if(condition){
/*7:*/
#line 247 "./error.w"

if(error_doing_precleanup_stats||error_doing_cleanup
||error_doing_postcleanup_stats)return 0;
if(error_precleanup_stats!=NULL){
error_doing_precleanup_stats= 1;
(*error_precleanup_stats)();
error_doing_precleanup_stats= 0;
}
if(error_cleanup!=NULL){
error_doing_cleanup= 1;
(*error_cleanup)();
error_doing_cleanup= 0;
}
if(error_postcleanup_stats!=NULL){
error_doing_postcleanup_stats= 1;
(*error_postcleanup_stats)();
error_doing_postcleanup_stats= 0;
}

/*:7*/
#line 206 "./error.w"

printf("%s:%d:",error_in_file,error_at_line);
vfprintf(stdout,fmt,args);
fputc('\n',stdout);
fflush(stdout);
fprintf(stderr,"%s:%d:",error_in_file,error_at_line);
vfprintf(stderr,fmt,args);
fputc('\n',stderr);
fflush(stderr);
#if defined(ERROR_DUMP_CORE_ON_ERROR)
*((int*)0)= 1;
#endif
exit(1);
}
va_end(args);

return 0;
}

/*:5*/
#line 156 "./error.w"


/*:1*/
