/*13:*/
#line 619 "./decluster.w"

extern const char*decluster_rcs_id;
/*19:*/
#line 682 "./decluster.w"

typedef struct{
int city[2];
length_t cost;
}decluster_edge_t;

typedef struct{
int n;
decluster_edge_t*edge;
}decluster_tree_t;

/*:19*/
#line 621 "./decluster.w"

/*38:*/
#line 1075 "./decluster.w"

extern int decluster_discard_topology_tree;



/*:38*/
#line 622 "./decluster.w"

/*11:*/
#line 594 "./decluster.w"

decluster_tree_t*decluster_setup(int n);
void decluster_cleanup_tree(decluster_tree_t*T);
void decluster_cleanup(void);
length_t decluster_mst(tsp_instance_t*tsp_instance,decluster_tree_t*T);
length_t decluster_mst_custom(decluster_tree_t*T,int*from,
length_t*dist,length_t(*cost)(int,int));
void decluster_preprocess(decluster_tree_t*T);
length_t decluster_d(int u,int v);

decluster_tree_t*decluster_topology_tree(void);
void decluster_print_tree(FILE*out,decluster_tree_t const*t,const char*name);


/*:11*/
#line 623 "./decluster.w"


/*:13*/
