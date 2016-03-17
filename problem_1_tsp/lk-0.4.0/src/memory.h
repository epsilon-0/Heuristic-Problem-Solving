/*2:*/
#line 183 "./memory.w"

extern const char*memory_rcs_id;

void*mem_alloc(const size_t);
void*mem_calloc(const size_t nmemb,const size_t size);
void*mem_realloc(void*,size_t);
char*dup_string(const char*);
void mem_usage_reset(void);
void mem_deduct(unsigned long n);
void mem_report(void);
#define new_of(t)  ((t *)mem_alloc(sizeof(t)))
#define new_arr_of(t,n)  ((t *)mem_alloc(sizeof(t)*(n)))
#define new_arr_of_zero(t,n)  ((t *)mem_calloc((size_t)(n),sizeof(t)))
#define free_mem(p) do {if (p!=NULL) {free((void *)p);} p =  NULL;} while (0)

/*:2*/
