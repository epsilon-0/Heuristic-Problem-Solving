/*16:*/
#line 281 "./pq.w"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "pq.h"

void
pqsort(void*a,size_t len,size_t es,pq_cmp_func_t cmp);
void
pqsort(void*a,size_t len,size_t es,pq_cmp_func_t cmp)
{
int i;
const int n= len/es;
pq_t*pq= pq_create_size(cmp,n);
void*copy= malloc(len);
errorif(copy==NULL,"Couldn't allocate copy array.");
memcpy(copy,a,len);
for(i= 0;i<n;i++){
pq_insert(pq,((char*)copy)+es*i);
}
for(i= 0;i<n;i++){
void*m= pq_min(pq);
void*dm;
void*dest,*src;
errorif(pq_empty(pq),"empty!");
dm= pq_delete_min(pq);
errorif(m!=dm,"min not same as delete_min");
src= m;
dest= ((char*)a)+i*es;
memcpy(dest,src,es);
}
errorif(!pq_empty(pq),"not empty!");
pq_destroy(pq);
}

static int
cmp_char(const void*aa,const void*bb)
{
return*(const char*)aa-*(const char*)bb;
}

static void
test_string(const char*s)
{
size_t len= strlen(s);
extern char*strdup(const char*s);
char*ss= strdup(s);
printf("pqtest    Testing \"%s\"\n",s);

pqsort(ss,len,sizeof(char),cmp_char);
printf("   Heap   Sorted: \"%s\"\n",ss);

strcpy(ss,s);
qsort(ss,len,sizeof(char),cmp_char);
printf("          Sorted: \"%s\"\n",ss);
free(ss);
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



/*:16*/
