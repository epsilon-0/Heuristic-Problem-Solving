/*1:*/
#line 110 "./memory.w"

#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fixincludes.h"

#include "error.h"
#include "memory.h"
const char*memory_rcs_id= "$Id: memory.w,v 1.116 1998/07/16 21:58:55 neto Exp neto $";

static unsigned long mem_total= 0,mem_max= 0;

void mem_usage_reset(void){mem_total= 0;}
void mem_deduct(unsigned long n){mem_total-= n;}
void mem_report(void){
printf("Maximum memory usage (UNRELIABLE): %ld bytes\n",mem_max);
}




void*
mem_alloc(const size_t n)
{
void*p;
errorif(n<0,"Can't allocate fewer than zero bytes: %d\n",n);
p= malloc(n);
errorif(p==NULL,"Couldn't allocate %ld bytes.",(long int)n);
mem_total+= n;
if(mem_total>mem_max)mem_max= mem_total;
return p;
}

void*
mem_calloc(const size_t nmemb,const size_t size)
{
void*p;
errorif(nmemb<0,"Can't allocate fewer than zero elements: %d\n",nmemb);
errorif(size<0,"Element size can't be negative: %d\n",size);
p= calloc(nmemb,size);
errorif(p==NULL,"Couldn't allocate %ld bytes.",(long int)(nmemb*size));
mem_total+= nmemb*size;
if(mem_total>mem_max)mem_max= mem_total;
return p;
}

void*
mem_realloc(void*ptr,size_t n){
void*p;
errorif(n<0,"Can't allocate fewer than zero bytes: %d\n",n);
p= realloc(ptr,n);
errorif(p==NULL,"Couldn't reallocate %ld bytes.",(long int)n);
mem_total+= n;
if(mem_total>mem_max)mem_max= mem_total;
return p;
}

char*
dup_string(const char*s)
{
char*p;
char*strdup(const char*);
p= strdup(s);
errorif(p==NULL,"Couldn't duplicate string \"%s\".",s);
return p;
}
/*:1*/
