/*40:*/
#line 969 "./dict.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "error.h"
#include "memory.h"
#include "pool.h"
#include "dict.h"
#include "gb_flip.h"

#define N 5

static int intcmp(const void*a,const void*b);
static void prn(void*a);
static void del(void*a);
int main(int,char**);

static int
intcmp(const void*a,const void*b)
{
return(*(const int*)a)-(*(const int*)b);
}

void prn(void*a)
{
printf("%d",*(int*)a);
}
static void
del(void*a)
{
printf("freeing integer %d\n",*(int*)a);
}

int
main(int argc,char**argv)
{
int i;
int a[N];
dict_t*d;
d= dict_create(intcmp,prn);
printf("Empty is:\n");dict_doall(d,prn);printf("\n");

for(i= 0;i<N;i++){
a[i]= i;
dict_insert(d,a+i);
printf("Inserted %d:",i);
dict_doall(d,prn);
printf("\n-------\n");
}
printf("All built");
dict_doall(d,prn);
printf("\n-------\n");

i= 7;
dict_find(d,&i);
printf("After find %d: ",i);dict_doall(d,prn);printf("\n------\n");

for(i= N-1;i>-1;i--){
int*r= dict_find(d,&i);
printf("i==%d a+i == %x r == %x\n",i,(int)(a+i),(int)r);
printf("  ");dict_doall(d,prn);printf("\n------\n");
}

i= 2;
dict_find(d,&i);
printf("After find %d: ",i);dict_doall(d,prn);printf("\n------\n");

i= N*2;
printf("About to dict_find(%d)\n",i);
errorif(dict_find(d,&i)!=NULL,"Should have returned NULL");
dict_doall(d,prn);
printf("\n------\n");

i= -N*2;
printf("About to dict_find(%d)\n",i);
errorif(dict_find(d,&i)!=NULL,"Should have returned NULL");
dict_doall(d,prn);
printf("\n------\n");


gb_init_rand(42L);
for(i= 0;i<N*N;i++){
int j,*r;
j= gb_unif_rand((long)N*2)-N/2;
r= dict_find(d,&j);
if(0<=j&&j<N){
if(a+j!=r){
printf("%d j==%d a+j == %x r == %x\n",i,j,(int)(a+j),(int)r);
printf("  ");dict_doall(d,prn);printf("\n------\n");
errorif(1,"BUG");
}
}else{
if(r!=NULL){
printf("r == %p != NULL when it should be.\n",(void*)r);
printf("%d j==%d a+j == %x r == %x\n",i,j,(int)(a+j),(int)r);
printf("  ");dict_doall(d,prn);printf("\n------\n");
}
}
}


dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 1;dict_find(d,&i);
i= 2;dict_find(d,&i);
printf("Bare long left bottom:");dict_doall(d,prn);printf("\n");
i= 0;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");

dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 1;dict_find(d,&i);
i= 2;dict_find(d,&i);
printf("Bare long left middle:");dict_doall(d,prn);printf("\n");
i= 1;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");

dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 1;dict_find(d,&i);
i= 2;dict_find(d,&i);
printf("Bare long left top:");dict_doall(d,prn);printf("\n");
i= 2;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");


dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 2;dict_find(d,&i);
i= 1;dict_find(d,&i);
i= 0;dict_find(d,&i);
printf("Bare long right bottom:");dict_doall(d,prn);printf("\n");
i= 2;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");

dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 2;dict_find(d,&i);
i= 1;dict_find(d,&i);
i= 0;dict_find(d,&i);
printf("Bare long right middle:");dict_doall(d,prn);printf("\n");
i= 1;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");

dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 2;dict_find(d,&i);
i= 1;dict_find(d,&i);
i= 0;dict_find(d,&i);
printf("Bare long right top:");dict_doall(d,prn);printf("\n");
i= 0;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");


dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 1;dict_find(d,&i);
printf("Bare balanced left:");dict_doall(d,prn);printf("\n");
i= 0;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");

dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 1;dict_find(d,&i);
printf("Bare balanced middle:");dict_doall(d,prn);printf("\n");
i= 1;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");

dict_delete_all(d,NULL);
for(i= 0;i<3;i++)dict_insert(d,a+i);
i= 1;dict_find(d,&i);
printf("Bare balanced right:");dict_doall(d,prn);printf("\n");
i= 2;dict_delete(d,&i,del);
printf("Deleted %d:",i);dict_doall(d,prn);printf("\n------\n");




for(i= 4;i>=0;i--){
dict_insert(d,a+i);
}
dict_find(d,a+3);
dict_find(d,a+1);
printf("Complex two-child delete:");dict_doall(d,prn);printf("\n");
dict_delete(d,a+1,del);
printf("Deleted %d:",1);dict_doall(d,prn);printf("\n------\n");

dict_destroy(d,del);
printf("\n------\nPassed all tests! (NOT EXHAUSTIVE)\n");
return 0;
}

/*:40*/
