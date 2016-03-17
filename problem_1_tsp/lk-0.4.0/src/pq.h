/*3:*/
#line 96 "./pq.w"

/*5:*/
#line 114 "./pq.w"

typedef int(*pq_cmp_func_t)(const void*,const void*);

typedef struct{
void**A;
int A_size;
int last_elem_i;
pq_cmp_func_t cmp;
void(*print_func)(void*);
}pq_t;

/*:5*/
#line 97 "./pq.w"

/*4:*/
#line 102 "./pq.w"

pq_t*pq_create(pq_cmp_func_t cmp);
pq_t*pq_create_size(pq_cmp_func_t cmp,int n);
void pq_destroy(pq_t*pq);
void pq_make_empty(pq_t*pq);
void pq_insert(pq_t*pq,void*payload);
void*pq_delete_min(pq_t*pq);
void*pq_min(pq_t*pq);
int pq_empty(pq_t*pq);
void pq_set_print_func(pq_t*pq,void(*print_func)(void*));

/*:4*/
#line 98 "./pq.w"



/*:3*/
