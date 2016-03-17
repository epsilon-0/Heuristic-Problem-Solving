#define normp(X) ((X) <num_groups?(X) :(X) -num_groups) 
#define normm(X) ((X) <0?(X) +num_groups:(X) ) 
/*3:*/
#line 293 "./twolevel.w"

#include <config.h>
#include "lkconfig.h"
/*4:*/
#line 308 "./twolevel.w"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*:4*//*73:*/
#line 1729 "./twolevel.w"

#include <stdio.h>
#if defined(OS_HAS_BROKEN_HEADERS)
#include "fixincludes.h"
#endif


/*:73*/
#line 296 "./twolevel.w"

/*6:*/
#line 322 "./twolevel.w"

#include "twolevel.h"

/*:6*//*15:*/
#line 446 "./twolevel.w"

#include "error.h"
#include "memory.h"

/*:15*//*70:*/
#line 1603 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
#include "array.h"
#endif

/*:70*/
#line 297 "./twolevel.w"


/*9:*/
#line 382 "./twolevel.w"


#define LINK_PREV 0
#define LINK_NEXT 1
#define prev link[LINK_PREV]
#define next link[LINK_NEXT]
#define CITY_LINK_HEAD 0
#define CITY_LINK_TAIL 1
#define head city_link[CITY_LINK_HEAD]
#define tail city_link[CITY_LINK_TAIL]

typedef struct parent_node_s{
int seq;
int reverse;
struct parent_node_s*link[2];
struct city_node_s*city_link[2];
}parent_node_t;

typedef struct city_node_s{
struct parent_node_s*parent;
int seq;
struct city_node_s*link[2];
}city_node_t;

/*:9*/
#line 299 "./twolevel.w"

/*10:*/
#line 412 "./twolevel.w"

static parent_node_t*parent_node= NULL;
static city_node_t*city_node= NULL;


/*:10*//*17:*/
#line 480 "./twolevel.w"

static int groupsize,num_groups;

/*:17*//*20:*/
#line 506 "./twolevel.w"

static int n= 0;

/*:20*//*43:*/
#line 934 "./twolevel.w"

static int implicit_balance_threshhold;



/*:43*//*68:*/
#line 1565 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
static int reverse;
#endif

/*:68*//*71:*/
#line 1609 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
static int using_two_representations;
#endif

/*:71*//*88:*/
#line 1980 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
static int count_flips= -1,print_at_flips= -1;
extern int verbose;
#endif


/*:88*/
#line 300 "./twolevel.w"

/*78:*/
#line 1869 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
static int check_tours_match(void);
static int check_self_consistency(void);
static int print_two_tours(void);
#endif

/*:78*/
#line 301 "./twolevel.w"

/*11:*/
#line 420 "./twolevel.w"

void
twolevel_setup(const int num_vertices,const int start_seg_size){
/*14:*/
#line 440 "./twolevel.w"

city_node= new_arr_of(city_node_t,num_vertices);

/*:14*//*18:*/
#line 493 "./twolevel.w"

groupsize= start_seg_size;
num_groups= num_vertices/groupsize;
parent_node= new_arr_of(parent_node_t,num_groups);


/*:18*//*21:*/
#line 510 "./twolevel.w"

n= num_vertices;

/*:21*//*42:*/
#line 930 "./twolevel.w"

implicit_balance_threshhold= (3*groupsize)/4;

/*:42*/
#line 423 "./twolevel.w"

}

/*:11*//*12:*/
#line 427 "./twolevel.w"

void
twolevel_cleanup(void){
/*16:*/
#line 451 "./twolevel.w"

free_mem(city_node);


/*:16*//*19:*/
#line 501 "./twolevel.w"

free_mem(parent_node);

/*:19*//*22:*/
#line 514 "./twolevel.w"

n= 0;

/*:22*/
#line 430 "./twolevel.w"

}

/*:12*//*24:*/
#line 575 "./twolevel.w"

void
twolevel_set(int const*tour){
int i,j,group,num_big_groups= n%num_groups,base_group_size= n/num_groups;
for(i= 0,group= 0;i<n;group++){
const int this_group_size= base_group_size+(group<num_big_groups);
parent_node[group].head= city_node+tour[i];
parent_node[group].tail= city_node+tour[i+this_group_size-1];
parent_node[group].reverse= 0;
parent_node[group].seq= group;
parent_node[group].prev= parent_node+((group-1+num_groups)%num_groups);
parent_node[group].next= parent_node+((group+1)%num_groups);
for(j= 0;j<this_group_size;j++,i++){
city_node[tour[i]].parent= parent_node+group;
city_node[tour[i]].seq= j;
city_node[tour[i]].prev= city_node+tour[(i-1+n)%n];
city_node[tour[i]].next= city_node+tour[(i+1)%n];
}
}
errorif(i!=n||group!=num_groups,"Bug in my 'rithmetic");
}

/*:24*//*31:*/
#line 659 "./twolevel.w"

int
twolevel_next(int a){
const city_node_t*ca= city_node+a;
return(ca->link[LINK_NEXT^ca->parent->reverse])-city_node;
}

int
twolevel_prev(int a){
const city_node_t*ca= city_node+a;
return(ca->link[LINK_PREV^ca->parent->reverse])-city_node;
}

/*:31*//*33:*/
#line 729 "./twolevel.w"

int
twolevel_between(int a,int b,int c){
const city_node_t*ca= city_node+a,*cb= city_node+b,*cc= city_node+c;
const parent_node_t*pa= ca->parent,*pb= cb->parent,*pc= cc->parent;
const int sa= ca->seq-pa->head->seq,sb= cb->seq-pb->head->seq,sc= cc->seq-pc->head->seq;

if(pa==pb)
if(pa==pc)
if(pa->reverse)
return(sa>=sb?((sb>=sc)|(sc>sa)):((sb>=sc)&(sc>sa)));
else return(sa<=sb?((sb<=sc)|(sc<sa)):((sb<=sc)&(sc<sa)));
else
return(sa==sb)|(pa->reverse^(sa<sb));
else
if(pa==pc)
return(sa!=sc)&(pa->reverse^(sa>sc));
else
if(pb==pc)
return(sb==sc)|((pb->reverse)^(sb<sc));
else{
const int psa= pa->seq,psb= pb->seq,psc= pc->seq;
return(psa<=psb?((psb<=psc)|(psc<psa)):((psb<=psc)&(psc<psa)));
}
}

/*:33*//*36:*/
#line 805 "./twolevel.w"

#define SWAP(x,y,t)  ((t)= (x),(x)= (y),(y)= (t))
#define abs(x) ((x)<0?-(x):(x))
void
twolevel_flip(int a,int b,int c,int d){
city_node_t*ca= city_node+a,*cb= city_node+b,
*cc= city_node+c,*cd= city_node+d,*tcn;
int psa= ca->parent->seq,psb= cb->parent->seq,
psc= cc->parent->seq,psd= cd->parent->seq,ti;
#if defined(TWOLEVEL_FLIP_CHECK_PRECONDITION)
errorif(a!=twolevel_next(b),"a != twolevel_next(b)");
errorif(d!=twolevel_next(c),"d != twolevel_next(c)");
#endif

/*38:*/
#line 848 "./twolevel.w"

/*79:*/
#line 1877 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(print_at_flips!=-1&&print_at_flips<=count_flips){
if(verbose>=200)printf(" Handle case 1\n");
if(using_two_representations){
check_tours_match();
print_two_tours();
}
}
#endif

/*:79*/
#line 849 "./twolevel.w"

if(psb==psd){
SWAP(ca,cb,tcn);SWAP(cc,cd,tcn);
SWAP(psa,psb,ti);SWAP(psc,psd,ti);

}
if(psa==psc){
/*39:*/
#line 880 "./twolevel.w"

/*40:*/
#line 905 "./twolevel.w"

if(ca==cc)return;
if(ca->seq>cc->seq)SWAP(ca,cc,tcn),SWAP(cb,cd,tcn);
if(ca->next==cb)ca= cb,cc= cd;

/*:40*/
#line 881 "./twolevel.w"

/*41:*/
#line 919 "./twolevel.w"

if(abs(ca->seq-cc->seq)>implicit_balance_threshhold){
/*48:*/
#line 1049 "./twolevel.w"

/*49:*/
#line 1069 "./twolevel.w"

/*85:*/
#line 1944 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d begin\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:85*/
#line 1070 "./twolevel.w"

{parent_node_t*p= ca->parent;
city_node_t*lc= p->head;
city_node_t*rc= ca->prev;
city_node_t*llc= lc->prev;
parent_node_t*lp= llc->parent;
int lpr= lp->reverse,pr= p->reverse;
errorif(lp==p,"Bug");
if(lc!=ca){
/*50:*/
#line 1108 "./twolevel.w"

p->head= ca;
lp->city_link[(pr==lpr)?CITY_LINK_TAIL:CITY_LINK_HEAD]= rc;


/*:50*/
#line 1079 "./twolevel.w"

/*51:*/
#line 1142 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(lpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= llc->seq+1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= llc->seq-1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1154 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= lp;
i->seq= seq_num;
}
i->parent= lp;
i->seq= seq_num;
}

/*:51*/
#line 1080 "./twolevel.w"

}
}
/*86:*/
#line 1952 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d end\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:86*/
#line 1083 "./twolevel.w"


/*:49*/
#line 1050 "./twolevel.w"

/*52:*/
#line 1176 "./twolevel.w"

/*83:*/
#line 1928 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d begin\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:83*/
#line 1177 "./twolevel.w"

{parent_node_t*p= cc->parent;
city_node_t*rc= p->tail;
city_node_t*lc= cc->next;
city_node_t*rrc= rc->next;
parent_node_t*rp= rrc->parent;
int rpr= rp->reverse,pr= p->reverse;
errorif(rp==p,"Bug");
if(rc!=cc){
/*53:*/
#line 1194 "./twolevel.w"

p->tail= cc;
rp->city_link[(pr==rpr)?CITY_LINK_HEAD:CITY_LINK_TAIL]= lc;

/*:53*/
#line 1186 "./twolevel.w"

/*54:*/
#line 1216 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(rpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= rrc->seq+u->seq-v->seq-1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= rrc->seq+v->seq-u->seq+1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1228 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= rp;
i->seq= seq_num;
}
i->parent= rp;
i->seq= seq_num;
}


/*:54*/
#line 1187 "./twolevel.w"

}
}
/*84:*/
#line 1936 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d end\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:84*/
#line 1190 "./twolevel.w"


/*:52*/
#line 1051 "./twolevel.w"

/*55:*/
#line 1255 "./twolevel.w"

{
city_node_t*l= ca->prev,*r= cc->next;
parent_node_t*lp= l->parent,*rp= r->parent;
const int ac_rev= ca->parent->reverse;
city_node_t**inbound_l= &l->link[LINK_NEXT^lp->reverse^ac_rev],
**inbound_r= &r->link[LINK_PREV^rp->reverse^ac_rev];
errorif(*inbound_l!=ca,
"Inbound left %d != ca %d",
*inbound_l-city_node,ca-city_node);
errorif(*inbound_r!=cc,
"Inbound right %d != cc %d",
*inbound_r-city_node,cc-city_node);
SWAP(*inbound_l,*inbound_r,tcn);
SWAP(ca->prev,cc->next,tcn);
}

/*:55*/
#line 1052 "./twolevel.w"

ca->parent->reverse^= 1;
/*87:*/
#line 1960 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)printf("\t\t\tImplicit rebalance done\n");

{
const int old_reverse= reverse;
if(using_two_representations){
reverse= array_next(0)!=twolevel_next(0);
if(verbose>=200)
printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
twolevel_next(0));
}
check_self_consistency();
if(using_two_representations){
reverse= old_reverse;
}
}
#endif

/*:87*/
#line 1054 "./twolevel.w"



/*:48*/
#line 921 "./twolevel.w"

}else{
/*44:*/
#line 962 "./twolevel.w"

{city_node_t*u= ca,*v= cc;
/*45:*/
#line 976 "./twolevel.w"

{city_node_t*i= u,*done= v->next;
int s;
for(s= v->seq,i= u;i!=done;i= i->next,s--){
i->seq= s;
}
}

/*:45*/
#line 964 "./twolevel.w"

/*46:*/
#line 1006 "./twolevel.w"

{parent_node_t*p= u->parent;
const int upn_to_v= u->prev->next==u,upp_to_v= u->prev->prev==u,
vnp_to_u= v->next->prev==v,vnn_to_u= v->next->next==v;
if(upn_to_v)u->prev->next= v;
if(upp_to_v)u->prev->prev= v;
if(vnp_to_u)v->next->prev= u;
if(vnn_to_u)v->next->next= u;
if(p->head==ca)p->head= cc;
else if(p->head==cc)p->head= ca;
if(p->tail==ca)p->tail= cc;
else if(p->tail==cc)p->tail= ca;
}


/*:46*/
#line 965 "./twolevel.w"

SWAP(u->prev,v->next,tcn);
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 967 "./twolevel.w"

}

/*:44*/
#line 923 "./twolevel.w"

}

/*:41*/
#line 882 "./twolevel.w"


/*:39*/
#line 856 "./twolevel.w"

return;
}

/*:38*/
#line 819 "./twolevel.w"

if(psa==psb){
/*57:*/
#line 1287 "./twolevel.w"

/*80:*/
#line 1889 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(print_at_flips!=-1&&print_at_flips<=count_flips){
if(verbose>=200)
printf(" Split the a-b segment, a=%d b=%d c=%d d=%d\n",a,b,c,d);
if(using_two_representations){
check_tours_match();
print_two_tours();
}
}
#endif

/*:80*/
#line 1288 "./twolevel.w"

{city_node_t*l,*r;parent_node_t*p= ca->parent;
if(ca->seq<cb->seq)l= ca,r= cb;
else l= cb,r= ca;
if(l->seq-p->head->seq<p->tail->seq-r->seq){
city_node_t*ca= r;
/*49:*/
#line 1069 "./twolevel.w"

/*85:*/
#line 1944 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d begin\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:85*/
#line 1070 "./twolevel.w"

{parent_node_t*p= ca->parent;
city_node_t*lc= p->head;
city_node_t*rc= ca->prev;
city_node_t*llc= lc->prev;
parent_node_t*lp= llc->parent;
int lpr= lp->reverse,pr= p->reverse;
errorif(lp==p,"Bug");
if(lc!=ca){
/*50:*/
#line 1108 "./twolevel.w"

p->head= ca;
lp->city_link[(pr==lpr)?CITY_LINK_TAIL:CITY_LINK_HEAD]= rc;


/*:50*/
#line 1079 "./twolevel.w"

/*51:*/
#line 1142 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(lpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= llc->seq+1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= llc->seq-1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1154 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= lp;
i->seq= seq_num;
}
i->parent= lp;
i->seq= seq_num;
}

/*:51*/
#line 1080 "./twolevel.w"

}
}
/*86:*/
#line 1952 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d end\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:86*/
#line 1083 "./twolevel.w"


/*:49*/
#line 1294 "./twolevel.w"

}else{
city_node_t*cc= l;
/*52:*/
#line 1176 "./twolevel.w"

/*83:*/
#line 1928 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d begin\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:83*/
#line 1177 "./twolevel.w"

{parent_node_t*p= cc->parent;
city_node_t*rc= p->tail;
city_node_t*lc= cc->next;
city_node_t*rrc= rc->next;
parent_node_t*rp= rrc->parent;
int rpr= rp->reverse,pr= p->reverse;
errorif(rp==p,"Bug");
if(rc!=cc){
/*53:*/
#line 1194 "./twolevel.w"

p->tail= cc;
rp->city_link[(pr==rpr)?CITY_LINK_HEAD:CITY_LINK_TAIL]= lc;

/*:53*/
#line 1186 "./twolevel.w"

/*54:*/
#line 1216 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(rpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= rrc->seq+u->seq-v->seq-1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= rrc->seq+v->seq-u->seq+1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1228 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= rp;
i->seq= seq_num;
}
i->parent= rp;
i->seq= seq_num;
}


/*:54*/
#line 1187 "./twolevel.w"

}
}
/*84:*/
#line 1936 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d end\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:84*/
#line 1190 "./twolevel.w"


/*:52*/
#line 1297 "./twolevel.w"

}
}
/*58:*/
#line 1312 "./twolevel.w"

psa= ca->parent->seq;
psb= cb->parent->seq;
psc= cc->parent->seq;
psd= cd->parent->seq;

/*:58*/
#line 1300 "./twolevel.w"


/*:57*//*59:*/
#line 1328 "./twolevel.w"

/*38:*/
#line 848 "./twolevel.w"

/*79:*/
#line 1877 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(print_at_flips!=-1&&print_at_flips<=count_flips){
if(verbose>=200)printf(" Handle case 1\n");
if(using_two_representations){
check_tours_match();
print_two_tours();
}
}
#endif

/*:79*/
#line 849 "./twolevel.w"

if(psb==psd){
SWAP(ca,cb,tcn);SWAP(cc,cd,tcn);
SWAP(psa,psb,ti);SWAP(psc,psd,ti);

}
if(psa==psc){
/*39:*/
#line 880 "./twolevel.w"

/*40:*/
#line 905 "./twolevel.w"

if(ca==cc)return;
if(ca->seq>cc->seq)SWAP(ca,cc,tcn),SWAP(cb,cd,tcn);
if(ca->next==cb)ca= cb,cc= cd;

/*:40*/
#line 881 "./twolevel.w"

/*41:*/
#line 919 "./twolevel.w"

if(abs(ca->seq-cc->seq)>implicit_balance_threshhold){
/*48:*/
#line 1049 "./twolevel.w"

/*49:*/
#line 1069 "./twolevel.w"

/*85:*/
#line 1944 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d begin\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:85*/
#line 1070 "./twolevel.w"

{parent_node_t*p= ca->parent;
city_node_t*lc= p->head;
city_node_t*rc= ca->prev;
city_node_t*llc= lc->prev;
parent_node_t*lp= llc->parent;
int lpr= lp->reverse,pr= p->reverse;
errorif(lp==p,"Bug");
if(lc!=ca){
/*50:*/
#line 1108 "./twolevel.w"

p->head= ca;
lp->city_link[(pr==lpr)?CITY_LINK_TAIL:CITY_LINK_HEAD]= rc;


/*:50*/
#line 1079 "./twolevel.w"

/*51:*/
#line 1142 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(lpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= llc->seq+1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= llc->seq-1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1154 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= lp;
i->seq= seq_num;
}
i->parent= lp;
i->seq= seq_num;
}

/*:51*/
#line 1080 "./twolevel.w"

}
}
/*86:*/
#line 1952 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d end\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:86*/
#line 1083 "./twolevel.w"


/*:49*/
#line 1050 "./twolevel.w"

/*52:*/
#line 1176 "./twolevel.w"

/*83:*/
#line 1928 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d begin\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:83*/
#line 1177 "./twolevel.w"

{parent_node_t*p= cc->parent;
city_node_t*rc= p->tail;
city_node_t*lc= cc->next;
city_node_t*rrc= rc->next;
parent_node_t*rp= rrc->parent;
int rpr= rp->reverse,pr= p->reverse;
errorif(rp==p,"Bug");
if(rc!=cc){
/*53:*/
#line 1194 "./twolevel.w"

p->tail= cc;
rp->city_link[(pr==rpr)?CITY_LINK_HEAD:CITY_LINK_TAIL]= lc;

/*:53*/
#line 1186 "./twolevel.w"

/*54:*/
#line 1216 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(rpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= rrc->seq+u->seq-v->seq-1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= rrc->seq+v->seq-u->seq+1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1228 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= rp;
i->seq= seq_num;
}
i->parent= rp;
i->seq= seq_num;
}


/*:54*/
#line 1187 "./twolevel.w"

}
}
/*84:*/
#line 1936 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d end\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:84*/
#line 1190 "./twolevel.w"


/*:52*/
#line 1051 "./twolevel.w"

/*55:*/
#line 1255 "./twolevel.w"

{
city_node_t*l= ca->prev,*r= cc->next;
parent_node_t*lp= l->parent,*rp= r->parent;
const int ac_rev= ca->parent->reverse;
city_node_t**inbound_l= &l->link[LINK_NEXT^lp->reverse^ac_rev],
**inbound_r= &r->link[LINK_PREV^rp->reverse^ac_rev];
errorif(*inbound_l!=ca,
"Inbound left %d != ca %d",
*inbound_l-city_node,ca-city_node);
errorif(*inbound_r!=cc,
"Inbound right %d != cc %d",
*inbound_r-city_node,cc-city_node);
SWAP(*inbound_l,*inbound_r,tcn);
SWAP(ca->prev,cc->next,tcn);
}

/*:55*/
#line 1052 "./twolevel.w"

ca->parent->reverse^= 1;
/*87:*/
#line 1960 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)printf("\t\t\tImplicit rebalance done\n");

{
const int old_reverse= reverse;
if(using_two_representations){
reverse= array_next(0)!=twolevel_next(0);
if(verbose>=200)
printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
twolevel_next(0));
}
check_self_consistency();
if(using_two_representations){
reverse= old_reverse;
}
}
#endif

/*:87*/
#line 1054 "./twolevel.w"



/*:48*/
#line 921 "./twolevel.w"

}else{
/*44:*/
#line 962 "./twolevel.w"

{city_node_t*u= ca,*v= cc;
/*45:*/
#line 976 "./twolevel.w"

{city_node_t*i= u,*done= v->next;
int s;
for(s= v->seq,i= u;i!=done;i= i->next,s--){
i->seq= s;
}
}

/*:45*/
#line 964 "./twolevel.w"

/*46:*/
#line 1006 "./twolevel.w"

{parent_node_t*p= u->parent;
const int upn_to_v= u->prev->next==u,upp_to_v= u->prev->prev==u,
vnp_to_u= v->next->prev==v,vnn_to_u= v->next->next==v;
if(upn_to_v)u->prev->next= v;
if(upp_to_v)u->prev->prev= v;
if(vnp_to_u)v->next->prev= u;
if(vnn_to_u)v->next->next= u;
if(p->head==ca)p->head= cc;
else if(p->head==cc)p->head= ca;
if(p->tail==ca)p->tail= cc;
else if(p->tail==cc)p->tail= ca;
}


/*:46*/
#line 965 "./twolevel.w"

SWAP(u->prev,v->next,tcn);
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 967 "./twolevel.w"

}

/*:44*/
#line 923 "./twolevel.w"

}

/*:41*/
#line 882 "./twolevel.w"


/*:39*/
#line 856 "./twolevel.w"

return;
}

/*:38*/
#line 1329 "./twolevel.w"


/*:59*/
#line 821 "./twolevel.w"

}
if(psc==psd){
/*60:*/
#line 1334 "./twolevel.w"

/*81:*/
#line 1902 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(print_at_flips!=-1&&print_at_flips<=count_flips){
if(verbose>=200)
printf(" Split the c-d segment, a=%d b=%d c=%d d=%d\n",a,b,c,d);
if(using_two_representations){
check_tours_match();
print_two_tours();
}
}
#endif

/*:81*/
#line 1335 "./twolevel.w"

{city_node_t*l,*r;parent_node_t*p= cc->parent;
if(cc->seq<cd->seq)l= cc,r= cd;
else l= cd,r= cc;
if(l->seq-p->head->seq<p->tail->seq-r->seq){
city_node_t*ca= r;
/*49:*/
#line 1069 "./twolevel.w"

/*85:*/
#line 1944 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d begin\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:85*/
#line 1070 "./twolevel.w"

{parent_node_t*p= ca->parent;
city_node_t*lc= p->head;
city_node_t*rc= ca->prev;
city_node_t*llc= lc->prev;
parent_node_t*lp= llc->parent;
int lpr= lp->reverse,pr= p->reverse;
errorif(lp==p,"Bug");
if(lc!=ca){
/*50:*/
#line 1108 "./twolevel.w"

p->head= ca;
lp->city_link[(pr==lpr)?CITY_LINK_TAIL:CITY_LINK_HEAD]= rc;


/*:50*/
#line 1079 "./twolevel.w"

/*51:*/
#line 1142 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(lpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= llc->seq+1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= llc->seq-1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1154 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= lp;
i->seq= seq_num;
}
i->parent= lp;
i->seq= seq_num;
}

/*:51*/
#line 1080 "./twolevel.w"

}
}
/*86:*/
#line 1952 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d end\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:86*/
#line 1083 "./twolevel.w"


/*:49*/
#line 1341 "./twolevel.w"

}else{
city_node_t*cc= l;
/*52:*/
#line 1176 "./twolevel.w"

/*83:*/
#line 1928 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d begin\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:83*/
#line 1177 "./twolevel.w"

{parent_node_t*p= cc->parent;
city_node_t*rc= p->tail;
city_node_t*lc= cc->next;
city_node_t*rrc= rc->next;
parent_node_t*rp= rrc->parent;
int rpr= rp->reverse,pr= p->reverse;
errorif(rp==p,"Bug");
if(rc!=cc){
/*53:*/
#line 1194 "./twolevel.w"

p->tail= cc;
rp->city_link[(pr==rpr)?CITY_LINK_HEAD:CITY_LINK_TAIL]= lc;

/*:53*/
#line 1186 "./twolevel.w"

/*54:*/
#line 1216 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(rpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= rrc->seq+u->seq-v->seq-1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= rrc->seq+v->seq-u->seq+1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1228 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= rp;
i->seq= seq_num;
}
i->parent= rp;
i->seq= seq_num;
}


/*:54*/
#line 1187 "./twolevel.w"

}
}
/*84:*/
#line 1936 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d end\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:84*/
#line 1190 "./twolevel.w"


/*:52*/
#line 1344 "./twolevel.w"

}
}
/*58:*/
#line 1312 "./twolevel.w"

psa= ca->parent->seq;
psb= cb->parent->seq;
psc= cc->parent->seq;
psd= cd->parent->seq;

/*:58*/
#line 1347 "./twolevel.w"


/*:60*//*61:*/
#line 1354 "./twolevel.w"

/*38:*/
#line 848 "./twolevel.w"

/*79:*/
#line 1877 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(print_at_flips!=-1&&print_at_flips<=count_flips){
if(verbose>=200)printf(" Handle case 1\n");
if(using_two_representations){
check_tours_match();
print_two_tours();
}
}
#endif

/*:79*/
#line 849 "./twolevel.w"

if(psb==psd){
SWAP(ca,cb,tcn);SWAP(cc,cd,tcn);
SWAP(psa,psb,ti);SWAP(psc,psd,ti);

}
if(psa==psc){
/*39:*/
#line 880 "./twolevel.w"

/*40:*/
#line 905 "./twolevel.w"

if(ca==cc)return;
if(ca->seq>cc->seq)SWAP(ca,cc,tcn),SWAP(cb,cd,tcn);
if(ca->next==cb)ca= cb,cc= cd;

/*:40*/
#line 881 "./twolevel.w"

/*41:*/
#line 919 "./twolevel.w"

if(abs(ca->seq-cc->seq)>implicit_balance_threshhold){
/*48:*/
#line 1049 "./twolevel.w"

/*49:*/
#line 1069 "./twolevel.w"

/*85:*/
#line 1944 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d begin\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:85*/
#line 1070 "./twolevel.w"

{parent_node_t*p= ca->parent;
city_node_t*lc= p->head;
city_node_t*rc= ca->prev;
city_node_t*llc= lc->prev;
parent_node_t*lp= llc->parent;
int lpr= lp->reverse,pr= p->reverse;
errorif(lp==p,"Bug");
if(lc!=ca){
/*50:*/
#line 1108 "./twolevel.w"

p->head= ca;
lp->city_link[(pr==lpr)?CITY_LINK_TAIL:CITY_LINK_HEAD]= rc;


/*:50*/
#line 1079 "./twolevel.w"

/*51:*/
#line 1142 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(lpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= llc->seq+1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= llc->seq-1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1154 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= lp;
i->seq= seq_num;
}
i->parent= lp;
i->seq= seq_num;
}

/*:51*/
#line 1080 "./twolevel.w"

}
}
/*86:*/
#line 1952 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the left of |ca|, a=%d end\n",ca-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:86*/
#line 1083 "./twolevel.w"


/*:49*/
#line 1050 "./twolevel.w"

/*52:*/
#line 1176 "./twolevel.w"

/*83:*/
#line 1928 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d begin\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:83*/
#line 1177 "./twolevel.w"

{parent_node_t*p= cc->parent;
city_node_t*rc= p->tail;
city_node_t*lc= cc->next;
city_node_t*rrc= rc->next;
parent_node_t*rp= rrc->parent;
int rpr= rp->reverse,pr= p->reverse;
errorif(rp==p,"Bug");
if(rc!=cc){
/*53:*/
#line 1194 "./twolevel.w"

p->tail= cc;
rp->city_link[(pr==rpr)?CITY_LINK_HEAD:CITY_LINK_TAIL]= lc;

/*:53*/
#line 1186 "./twolevel.w"

/*54:*/
#line 1216 "./twolevel.w"

{
city_node_t*i,*u= lc,*v= rc;
int succ_link,seq_inc,seq_num;
if(rpr==pr){
succ_link= LINK_NEXT;
seq_inc= 1;
seq_num= rrc->seq+u->seq-v->seq-1;
}else{
succ_link= LINK_PREV;
seq_inc= -1;
seq_num= rrc->seq+v->seq-u->seq+1;
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 1228 "./twolevel.w"

}
for(i= lc;i!=rc;i= i->link[succ_link],seq_num+= seq_inc){

i->parent= rp;
i->seq= seq_num;
}
i->parent= rp;
i->seq= seq_num;
}


/*:54*/
#line 1187 "./twolevel.w"

}
}
/*84:*/
#line 1936 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)
printf("\t\t\tSplit off the end to the right of |cc|, c=%d end\n",cc-city_node);
if(using_two_representations)check_tours_match();
#endif

/*:84*/
#line 1190 "./twolevel.w"


/*:52*/
#line 1051 "./twolevel.w"

/*55:*/
#line 1255 "./twolevel.w"

{
city_node_t*l= ca->prev,*r= cc->next;
parent_node_t*lp= l->parent,*rp= r->parent;
const int ac_rev= ca->parent->reverse;
city_node_t**inbound_l= &l->link[LINK_NEXT^lp->reverse^ac_rev],
**inbound_r= &r->link[LINK_PREV^rp->reverse^ac_rev];
errorif(*inbound_l!=ca,
"Inbound left %d != ca %d",
*inbound_l-city_node,ca-city_node);
errorif(*inbound_r!=cc,
"Inbound right %d != cc %d",
*inbound_r-city_node,cc-city_node);
SWAP(*inbound_l,*inbound_r,tcn);
SWAP(ca->prev,cc->next,tcn);
}

/*:55*/
#line 1052 "./twolevel.w"

ca->parent->reverse^= 1;
/*87:*/
#line 1960 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(verbose>=150)printf("\t\t\tImplicit rebalance done\n");

{
const int old_reverse= reverse;
if(using_two_representations){
reverse= array_next(0)!=twolevel_next(0);
if(verbose>=200)
printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
twolevel_next(0));
}
check_self_consistency();
if(using_two_representations){
reverse= old_reverse;
}
}
#endif

/*:87*/
#line 1054 "./twolevel.w"



/*:48*/
#line 921 "./twolevel.w"

}else{
/*44:*/
#line 962 "./twolevel.w"

{city_node_t*u= ca,*v= cc;
/*45:*/
#line 976 "./twolevel.w"

{city_node_t*i= u,*done= v->next;
int s;
for(s= v->seq,i= u;i!=done;i= i->next,s--){
i->seq= s;
}
}

/*:45*/
#line 964 "./twolevel.w"

/*46:*/
#line 1006 "./twolevel.w"

{parent_node_t*p= u->parent;
const int upn_to_v= u->prev->next==u,upp_to_v= u->prev->prev==u,
vnp_to_u= v->next->prev==v,vnn_to_u= v->next->next==v;
if(upn_to_v)u->prev->next= v;
if(upp_to_v)u->prev->prev= v;
if(vnp_to_u)v->next->prev= u;
if(vnn_to_u)v->next->next= u;
if(p->head==ca)p->head= cc;
else if(p->head==cc)p->head= ca;
if(p->tail==ca)p->tail= cc;
else if(p->tail==cc)p->tail= ca;
}


/*:46*/
#line 965 "./twolevel.w"

SWAP(u->prev,v->next,tcn);
/*47:*/
#line 1029 "./twolevel.w"

{
city_node_t*i= u,*done= v->next;
for(i= u;i!=done;i= i->prev){
SWAP(i->next,i->prev,tcn);
}
}

/*:47*/
#line 967 "./twolevel.w"

}

/*:44*/
#line 923 "./twolevel.w"

}

/*:41*/
#line 882 "./twolevel.w"


/*:39*/
#line 856 "./twolevel.w"

return;
}

/*:38*/
#line 1355 "./twolevel.w"


/*:61*/
#line 824 "./twolevel.w"

}
/*62:*/
#line 1363 "./twolevel.w"

/*82:*/
#line 1915 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
if(print_at_flips!=-1&&print_at_flips<=count_flips){
if(verbose>=125)printf(" flip a sequence of segments\n");
if(using_two_representations){
check_tours_match();
print_two_tours();
}
}
#endif


/*:82*/
#line 1364 "./twolevel.w"

errorif((psa==psb||psc==psd),"psa %d==psb %d or psc %d == psd %d",psa,psb,psc,psd);
/*63:*/
#line 1403 "./twolevel.w"

if(psb==psd){
SWAP(a,b,ti),SWAP(c,d,ti),
SWAP(ca,cb,tcn),SWAP(cc,cd,tcn),
SWAP(psa,psb,ti),SWAP(psc,psd,ti);
}else if(psa!=psc){
if(normp(psa+1)==psb){
const int dmb= psd-psb,amc= psa-psc;
if(normm(dmb)<normm(amc))
SWAP(a,b,ti),SWAP(c,d,ti),
SWAP(ca,cb,tcn),SWAP(cc,cd,tcn),
SWAP(psa,psb,ti),SWAP(psc,psd,ti);
}else{
const int bmd= psb-psd,cma= psc-psa;
if(normm(bmd)<normm(cma))
SWAP(a,b,ti),SWAP(c,d,ti),
SWAP(ca,cb,tcn),SWAP(cc,cd,tcn),
SWAP(psa,psb,ti),SWAP(psc,psd,ti);
}
}

/*:63*/
#line 1366 "./twolevel.w"

/*64:*/
#line 1433 "./twolevel.w"

{
parent_node_t*u,*v;
if(normp(psa+1)==psb)u= cc->parent,v= ca->parent;
else u= ca->parent,v= cc->parent;
/*65:*/
#line 1455 "./twolevel.w"

{
parent_node_t*tpn;
int ur,vr;
city_node_t**u_outbound,**v_outbound,**u_inbound,**v_inbound,*u_first,*v_last;
ur= u->reverse;
vr= v->reverse;
u_first= u->city_link[ur^CITY_LINK_HEAD];
v_last= v->city_link[vr^CITY_LINK_TAIL];
u_outbound= u_first->link+(ur^LINK_PREV);
v_outbound= v_last->link+(vr^LINK_NEXT);
u_inbound= (*u_outbound)->link+
((*u_outbound)->link[LINK_NEXT]==u_first?LINK_NEXT:LINK_PREV);
v_inbound= (*v_outbound)->link+
((*v_outbound)->link[LINK_NEXT]==v_last?LINK_NEXT:LINK_PREV);

SWAP(*u_inbound,*v_inbound,tcn);
SWAP(*u_outbound,*v_outbound,tcn);
u->prev->next= v;
v->next->prev= u;
SWAP(u->prev,v->next,tpn);
}

/*:65*/
#line 1438 "./twolevel.w"

/*66:*/
#line 1511 "./twolevel.w"

{
const int upv= u->seq+v->seq,upvn= normp(upv);
parent_node_t*i,*done= v->next,*tpn;
errorif(upv<u->seq||upv<v->seq,
"We've overflowed the integer representation");
for(i= u;i!=done;i= i->prev){
const int new_seq= upvn-i->seq;
i->seq= normm(new_seq);
i->reverse^= 1;
SWAP(i->next,i->prev,tpn);
}
}

/*:66*/
#line 1439 "./twolevel.w"

}


/*:64*/
#line 1367 "./twolevel.w"


/*:62*/
#line 826 "./twolevel.w"

}

/*:36*//*69:*/
#line 1573 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
void
twolevel_debug_setup(const int num_vertices,const int start_seg_size){
array_setup(num_vertices);
twolevel_setup(num_vertices,start_seg_size);
using_two_representations= 1;
}

void
twolevel_debug_cleanup(void){
twolevel_cleanup();
array_cleanup();
using_two_representations= 0;
}

void
twolevel_debug_set(int const*tour){
if(verbose>=100){printf("set\n");}
array_set(tour);
twolevel_set(tour);
reverse= array_next(0)!=twolevel_next(0);
if(verbose>=200)
printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
twolevel_next(0));
check_tours_match();
}
#endif

/*:69*//*72:*/
#line 1622 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
static int
check_self_consistency(void)
{int i,c,cnt,an_error= 0,cnpt,gs,s,tail_s,lgs,ls,ng= 0,ph,pt;
const int first_city= 
parent_node[0].city_link[CITY_LINK_HEAD^parent_node[0].reverse]
-city_node;
parent_node_t*p;
if(verbose>=150)
printf("Checking twolevel tour consistency, reverse==%d\n",reverse);
tail_s= ls= city_node[twolevel_prev(first_city)].seq;
lgs= parent_node[0].seq-1;
for(i= 0,c= first_city;i<n&&!an_error;i++,c= cnt){
if(c==first_city&&i>0){an_error= 1;printf("Not a tour\n");}
cnt= twolevel_next(c);
cnpt= twolevel_prev(cnt);
if(cnpt!=c){
an_error= 1;
printf("twolevel next/prev inconsistent pos %d city %d next: %d, nextprev: %d\n",
i,c,cnt,cnpt);
}
p= city_node[c].parent;
if(lgs!=(gs= p->seq)){
ng++;
if(gs!=((lgs+1)%num_groups)){
an_error= 1;
printf("Parent sequence numbers %d to %d not consecutive\n",
lgs,gs);
}
lgs= gs;
if(tail_s!=ls){
an_error= 1;
printf("Seq of last city in segment %d doesn't seq of \"tail\"%d\n",
ls,tail_s);
}
tail_s= p->city_link[CITY_LINK_TAIL^p->reverse]->seq;
ls= city_node[c].seq;
if(c!=(ph= p->city_link[CITY_LINK_HEAD^p->reverse]-city_node)){
an_error= 1;
printf("First city in segment %d isn't \"head\"%d\n",
c,ph);
}
{const cp= twolevel_prev(c);
const parent_node_t*pp= city_node[cp].parent;
if(cp!=(pt= pp->city_link[CITY_LINK_TAIL^pp->reverse]-city_node)){
an_error= 1;
printf("Last city %d in previous segment isn't \"tail\" %d; step %d\n",
cp,pt,i);
}
}
}else{
const int s_should_be= ls+(p->reverse?-1:1);
s= city_node[c].seq;
if(s!=s_should_be){
an_error= 1;
printf("Sequence number %d of %d should be %d\n",
s,c,s_should_be);
}
ls= s;
}
}
if(ng!=num_groups){
an_error= 1;
printf("Only counted %d groups; should be %d groups\n",
ng,num_groups);
}
if(c!=first_city){
an_error= 1;
printf("Not a tour: didn't loop back from %d to itself\n",
first_city);
}
if(an_error)print_two_tours();
errorif(an_error,"Incorrect state for two-level trees.");
return 1;
}

static int
check_tours_match(void)
{int i,c,cna,cnt,an_error= 0;
const int first_city= 
parent_node[0].city_link[CITY_LINK_HEAD^parent_node[0].reverse]
-city_node;
check_self_consistency();
if(verbose>=150)printf("Checking tours match\n");
for(i= 0,c= first_city;i<n&&!an_error;i++,c= cnt){
if(c==first_city&&i>0){an_error= 1;printf("Not a tour\n");}
cna= reverse?array_prev(c):array_next(c);
cnt= twolevel_next(c);
if(cna!=cnt){
an_error= 1;
printf("next's don't match: position %d city %d array: %d, twolevel: %d\n",
i,c,cna,cnt);
}
}
if(c!=first_city){
an_error= 1;
printf("Not a tour: didn't loop back from %d to itself\n",
first_city);
}
if(an_error)print_two_tours();
errorif(an_error,"Tours don't match.");
return 1;
}
#endif

/*:72*//*74:*/
#line 1737 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
static int
print_two_tours(void){
int i,ca,ct,amore= 1,tmore= 1,
first_city= parent_node[0].city_link[CITY_LINK_HEAD^parent_node[0].reverse]
-city_node;
char a[100],t[100];
for(i= 0,ca= ct= first_city;i<n;i++){
if(i==0)printf("Tour: Array Two-level\n");
sprintf(a,"%d",ca);
sprintf(t,"%d",ct);
printf("\t%4d %7s %7s",i,amore?a:" ",tmore?t:" ");
if(tmore){
printf("\tseq=%3d p=%p g=%2d %s h=%4d t=%4d",
city_node[ct].seq,
city_node[ct].parent,
city_node[ct].parent->seq,
city_node[ct].parent->reverse?"r":" ",
city_node[ct].parent->head-city_node,
city_node[ct].parent->tail-city_node);
}
printf("\n");
ca= reverse?array_prev(ca):array_next(ca);
ct= twolevel_next(ct);
amore&= ca!=first_city;
tmore&= ct!=first_city;
}
return 1;
}
#endif

/*:74*//*75:*/
#line 1773 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
int
twolevel_debug_next(int a){
const int tn= twolevel_next(a);
const int an= reverse?array_prev(a):array_next(a);
const int tnp= twolevel_prev(tn);
if(verbose>=125)printf("next(%d)\n",a);
errorif(tn!=an&&check_tours_match(),
"next: twolevel_next(%d)=%d, array_%s(%d)=%d",
a,tn,reverse?"prev":"next",an);
errorif(tnp!=a&&check_tours_match(),
"next(%d)=%d, prev(%d)=%d",a,tn,tn,tnp);
return tn;
}

int
twolevel_debug_prev(int a){
const int tp= twolevel_prev(a);
const int ap= reverse?array_next(a):array_prev(a);
const int tpn= twolevel_next(tp);
if(verbose>=125)printf("prev(%d)\n",a);
errorif(tp!=ap&&check_tours_match(),
"next: twolevel_next(%d)=%d, array_%s(%d)=%d",
a,tp,reverse?"next":"prev",ap);
errorif(tpn!=a&&check_tours_match(),
"prev(%d)=%d, next(%d)=%d",a,tp,tp,tpn);
return tp;
}
#endif

/*:75*//*76:*/
#line 1811 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
int
twolevel_debug_between(int a,int b,int c){
const int ab= reverse?array_between(c,b,a):array_between(a,b,c);
const int tb= twolevel_between(a,b,c);
if(verbose>=125)printf("between(%d,%d,%d)\n",a,b,c);
errorif(ab!=tb&&check_tours_match()&&print_two_tours(),
"between(%d,%d,%d) don't match: twolevel=%d array=%d",
a,b,c,tb,ab);
return tb;
}
#endif

/*:76*//*77:*/
#line 1832 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
void
twolevel_debug_flip(int a,int b,int c,int d){
if(verbose>=110)printf("flip(%d,%d,%d,%d) %d\n",a,b,c,d,++count_flips);
twolevel_flip(a,b,c,d);
if(reverse)array_flip(b,a,d,c);
else array_flip(a,b,c,d);
reverse= array_next(0)!=twolevel_next(0);
if(verbose>=200)
printf("\t\treverse %d == (an0=%d != tn0=%d)\n",reverse,array_next(0),
twolevel_next(0));
check_tours_match();
{int an_error= 0;
const int an= twolevel_next(a),ap= twolevel_prev(a);
const int bn= twolevel_next(b),bp= twolevel_prev(b);
const int cn= twolevel_next(c),cp= twolevel_prev(c);
const int dn= twolevel_next(d),dp= twolevel_prev(d);
if(an==d){
if(dp!=a)an_error= 1,printf("dp!=a\n");
if(bn!=c)an_error= 1,printf("bn!=c\n");
if(cp!=b)an_error= 1,printf("cp!=b\n");
}else if(ap==d){
if(dn!=a)an_error= 1,printf("dn!=a\n");
if(bp!=c)an_error= 1,printf("bp!=c\n");
if(cn!=b)an_error= 1,printf("cn!=b\n");
}
if(an_error){
print_two_tours();
errorif(1,"Bug");
}
}
}
#endif


/*:77*/
#line 302 "./twolevel.w"

const char*twolevel_rcs_id= "$Id: twolevel.w,v 1.145 1998/07/16 21:58:55 neto Exp neto $";

/*:3*/
