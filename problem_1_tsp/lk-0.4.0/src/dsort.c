#define W sizeof(WORD) 
#define SWAPINIT(a,es) swaptype= ((a-(char*) 0) |es) %W?2:es>W?1:0
#define exch(a,b,t) (t= a,a= b,b= t) 
#define swap(a,b) swaptype!=0?swapfunc(a,b,es,swaptype) :(void) exch(*(WORD*) (a) ,*(WORD*) (b) ,t) 
#define vecswap(a,b,n) if(n>0) swapfunc(a,b,n,swaptype)  \

#define min(a,b) ((a) <(b) ?(a) :(b) )  \

#define PVINIT(pv,pm) if(swaptype!=0) pv= a,swap(pv,pm) ;else pv= (char*) &v,v= *(WORD*) pm
/*1:*/
#line 136 "./dsort.w"

#include <config.h>
#include "lkconfig.h"
/*7:*/
#line 217 "./dsort.w"

#include <stddef.h>


/*:7*/
#line 139 "./dsort.w"

/*3:*/
#line 156 "./dsort.w"

#include "dsort.h"

/*:3*/
#line 140 "./dsort.w"


/*5:*/
#line 169 "./dsort.w"

typedef long WORD;

/*:5*/
#line 142 "./dsort.w"

/*6:*/
#line 194 "./dsort.w"

static void
swapfunc(char*a,char*b,size_t n,int swaptype){
if(swaptype<=1){
WORD t;
for(;n>0;a+= W,b+= W,n-= W)
exch(*(WORD*)a,*(WORD*)b,t);
}else{
char t;
for(;n>0;a+= 1,b+= 1,n-= 1)
exch(*a,*b,t);
}
}

static char*
med3(char*a,char*b,char*c,int(*cmp)(const void*a,const void*b)){
return
cmp(a,b)<0
?(cmp(b,c)<0?b:cmp(a,c)<0?c:a)
:(cmp(b,c)>0?b:cmp(a,c)>0?c:a);
}

/*:6*/
#line 143 "./dsort.w"

/*8:*/
#line 225 "./dsort.w"

void
dsort(void*aa,size_t n,size_t es,int(*cmp)(const void*,const void*))
{
char*a= (char*)aa,*pa,*pb,*pc,*pd,*pl,*pm,*pn,*pv;
int r,swaptype;
WORD t,v;
size_t s;
SWAPINIT(a,es);
if(n<7){
for(pm= a+es;pm<a+n*es;pm+= es)
for(pl= pm;pl>a&&cmp(pl-es,pl)>0;pl-= es){
swap(pl,pl-es);
}
return;
}
/*10:*/
#line 256 "./dsort.w"

pm= a+(n/2)*es;
if(n>7){
pl= a;
pn= a+(n-1)*es;
if(n>40){
s= (n/8)*es;
pl= med3(pl,pl+s,pl+2*s,cmp);
pm= med3(pm-s,pm,pm+s,cmp);
pn= med3(pn-2*s,pn-s,pn,cmp);
}
pm= med3(pl,pm,pn,cmp);
}

/*:10*/
#line 241 "./dsort.w"

/*11:*/
#line 272 "./dsort.w"

PVINIT(pv,pm);
pa= pb= a;
pc= pd= a+(n-1)*es;
for(;;){
while(pb<=pc&&(r= cmp(pb,pv))<=0){
if(r==0){swap(pa,pb);pa+= es;}
pb+= es;
}
while(pc>=pb&&(r= cmp(pc,pv))>=0){
if(r==0){swap(pc,pd);pd-= es;}
pc-= es;
}
if(pb>pc)break;
swap(pb,pc);
pb+= es;
pc-= es;
}

/*:11*/
#line 242 "./dsort.w"

pn= a+n*es;
s= min(pa-a,pb-pa);vecswap(a,pb-s,s);
s= min(pd-pc,pn-pd-es);vecswap(pb,pn-s,s);
if((s= pb-pa)>es)dsort(a,s/es,es,cmp);
if((s= pd-pc)>es)dsort(pn-s,s/es,es,cmp);
}
/*:8*//*12:*/
#line 298 "./dsort.w"

void*
select_range(void*aa,size_t n,size_t es,
int(*cmp)(const void*,const void*),int lo,int hi,int sorted)
{
char*a= (char*)aa,*pa,*pb,*pc,*pd,*pl,*pm,*pn,*pv;
int r,swaptype;
WORD t,v;
size_t s;

/*14:*/
#line 322 "./dsort.w"

if(n<0)return NULL;
if(n<=1)return aa;
if(lo<0||lo>=n)return NULL;
if(hi<lo||hi>n)return NULL;
if(lo==0&&hi==n){if(sorted)dsort(aa,n,es,cmp);return aa;}


/*:14*/
#line 308 "./dsort.w"

SWAPINIT(a,es);
/*15:*/
#line 331 "./dsort.w"

if(n<7){
for(pm= a+es;pm<a+n*es;pm+= es)
for(pl= pm;pl>a&&cmp(pl-es,pl)>0;pl-= es){
swap(pl,pl-es);
}
return a+lo*es;
}

/*:15*/
#line 310 "./dsort.w"

/*10:*/
#line 256 "./dsort.w"

pm= a+(n/2)*es;
if(n>7){
pl= a;
pn= a+(n-1)*es;
if(n>40){
s= (n/8)*es;
pl= med3(pl,pl+s,pl+2*s,cmp);
pm= med3(pm-s,pm,pm+s,cmp);
pn= med3(pn-2*s,pn-s,pn,cmp);
}
pm= med3(pl,pm,pn,cmp);
}

/*:10*/
#line 311 "./dsort.w"

/*11:*/
#line 272 "./dsort.w"

PVINIT(pv,pm);
pa= pb= a;
pc= pd= a+(n-1)*es;
for(;;){
while(pb<=pc&&(r= cmp(pb,pv))<=0){
if(r==0){swap(pa,pb);pa+= es;}
pb+= es;
}
while(pc>=pb&&(r= cmp(pc,pv))>=0){
if(r==0){swap(pc,pd);pd-= es;}
pc-= es;
}
if(pb>pc)break;
swap(pb,pc);
pb+= es;
pc-= es;
}

/*:11*/
#line 312 "./dsort.w"

/*16:*/
#line 352 "./dsort.w"

pn= a+n*es;
{
const int
ai= (pa-a)/es,
bi= (pb-a)/es,
ci= (pc-a)/es,
di= (pd-a)/es;
const size_t
right_greater= di-ci,
right_equal= n-di-1,
left_less= bi-ai;
const int
hi_wrt_greater= hi-bi-right_equal,
lo_wrt_greater= lo-bi-right_equal;

if(hi>bi){
s= min(pd-pc,pn-pd-es);vecswap(pb,pn-s,s);
if(hi_wrt_greater>0){
const int new_lo= lo_wrt_greater<0?0:lo_wrt_greater;
if(right_greater>1)
(void)select_range(pn-right_greater*es,right_greater,es,cmp,
new_lo,hi_wrt_greater,sorted);
}
}

if(lo<bi){
s= min(pa-a,pb-pa);vecswap(a,pb-s,s);
if(lo<left_less){
const int new_hi= hi<=left_less?hi:left_less;
if(left_less>1)
(void)select_range(a,left_less,es,cmp,lo,new_hi,sorted);
}
}
}
return a+lo*es;

/*:16*/
#line 313 "./dsort.w"

}
/*:12*/
#line 144 "./dsort.w"

const char*dsort_rcs_id= "$Id: dsort.w,v 1.134 1998/07/16 21:58:55 neto Exp neto $";

/*:1*/
