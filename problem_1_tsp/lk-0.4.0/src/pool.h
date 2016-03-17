/*5:*/
#line 149 "./pool.w"

#if !defined(_POOL_H_)
#define _POOL_H_
extern const char*pool_rcs_id;
/*7:*/
#line 167 "./pool.w"

typedef struct pool_block_freelist_s{
struct pool_block_freelist_s*next;
}pool_block_freelist_t;

typedef struct pool_s{
struct pool_s*next;
size_t os;
int bs;
void*block;
pool_block_freelist_t*freelist_head;
}pool_t;

/*:7*/
#line 153 "./pool.w"

/*10:*/
#line 215 "./pool.w"

pool_t*pool_create(size_t os,int bs);

/*:10*//*13:*/
#line 276 "./pool.w"

void pool_destroy(pool_t*p);

/*:13*//*15:*/
#line 305 "./pool.w"

void*pool_alloc(pool_t*p);

/*:15*//*17:*/
#line 338 "./pool.w"

void pool_free(pool_t*p,void*vp);

/*:17*/
#line 154 "./pool.w"

#endif

/*:5*/
