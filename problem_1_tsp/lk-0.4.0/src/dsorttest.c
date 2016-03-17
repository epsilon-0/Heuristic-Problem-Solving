/*17:*/
#line 395 "./dsort.w"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "dsort.h"
static int
cmp_char(const void*aa,const void*bb)
{
return*(const char*)aa-*(const char*)bb;
}

static void
test_string(const char*s)
{
size_t len= strlen(s);
int l,h,sorted;
extern char*strdup(const char*s);
char*p,*ss= strdup(s);
printf("dsorttest Testing \"%s\"\n",s);
qsort(ss,len,sizeof(char),cmp_char);
printf("          Sorted: \"%s\"\n",ss);
for(l= 0;l<len;l+= 1){
for(h= l+1;h<=len;h+= 1){
for(sorted= 0;sorted<2;sorted++){
strcpy(ss,s);
p= select_range(ss,len,sizeof(char),cmp_char,l,h,sorted);
printf("                  \"%s\" l=%d h=%d ",ss,l,h);
ss[h]= '\0';
printf("result=\"%s\" sorted=%d\n",p,sorted);
}
}
}
}

int main(int argc,char**argv)
{
int i;
test_string("abcdefghijklmnopqrstuvwx");
test_string("xwvutsrqponmlkjihgfedcba");
test_string("David Neto was here");
for(i= 0;i<argc;i++)
test_string(argv[i]);
return 0;
}


/*:17*/
