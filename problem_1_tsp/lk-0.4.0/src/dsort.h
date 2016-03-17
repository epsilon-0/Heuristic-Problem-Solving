/*2:*/
#line 150 "./dsort.w"

extern const char*dsort_rcs_id;
/*9:*/
#line 250 "./dsort.w"

extern void
dsort(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*));


/*:9*//*13:*/
#line 316 "./dsort.w"

extern void*
select_range(void*a,size_t n,size_t es,int(*cmp)(const void*,const void*),
int lo,int hi,int sorted);

/*:13*/
#line 152 "./dsort.w"


/*:2*/
