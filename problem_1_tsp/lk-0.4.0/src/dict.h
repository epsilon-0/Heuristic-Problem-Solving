/*4:*/
#line 171 "./dict.w"

#if !defined(_DICT_H_)
#define _DICT_H_
/*10:*/
#line 332 "./dict.w"

#include "pool.h"

/*:10*/
#line 174 "./dict.w"

extern const char*dict_rcs_id;
/*9:*/
#line 313 "./dict.w"


typedef struct dict_node_s{
void*payload;
struct dict_node_s*link[3];
}dict_node_t;

typedef struct{
dict_node_t*root;
int(*cmp)(const void*a,const void*b);
void(*prn)(void*a);
pool_t*pool;
size_t size;
}dict_t;

/*:9*/
#line 176 "./dict.w"

/*6:*/
#line 266 "./dict.w"

dict_t*dict_create(int(*cmp_fnc)(const void*,const void*),
void(*prn_fnc)(void*));
void dict_destroy(dict_t*d,void(*action)(void*));
int dict_insert(dict_t*d,void*e);
void*dict_find(dict_t*d,void*e);
void*dict_delete(dict_t*d,void*e,void(*action)(void*));
void dict_delete_all(dict_t*d,void(*action)(void*));
void*dict_delete_any(dict_t*d,void(*action)(void*));
void*dict_min(dict_t*d);
void*dict_max(dict_t*d);
void*dict_delete_min(dict_t*d);
void*dict_delete_max(dict_t*d);
void dict_update_all(dict_t*d,void(*proc)(void*env2,void**payload_p),void*env1);
size_t dict_size(dict_t*d);


/*:6*//*39:*/
#line 962 "./dict.w"

void
dict_doall(dict_t*d,void(*action)(void*));
void
dict_show_node(dict_t*d,dict_node_t*h);

/*:39*/
#line 177 "./dict.w"

#endif

/*:4*/
