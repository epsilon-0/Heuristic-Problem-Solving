/*2:*/
#line 346 "./kdtree.w"

extern const char*kdtree_rcs_id;
/*11:*/
#line 546 "./kdtree.w"

extern int kd_bucket_cutoff;




/*:11*//*19:*/
#line 680 "./kdtree.w"

extern int kd_bbox_skip;

/*:19*/
#line 348 "./kdtree.w"

/*4:*/
#line 416 "./kdtree.w"

void E2_create(tsp_instance_t*tsp);
void E2_destroy(void);
void E2_hide(int i);
void E2_unhide(int i);
void E2_hide_all(void);
void E2_unhide_all(void);
int E2_nn(int i);
int E2_nn_quadrant(int i,const int q);
void E2_frnn(int i,double rad,void(*proc)(int j));
void E2_set_radius(int i,double r);
void E2_ball_search(int i,void(*proc)(int j));


/*:4*//*5:*/
#line 432 "./kdtree.w"

int E2_supports(tsp_instance_t*tsp);


/*:5*//*92:*/
#line 2117 "./kdtree.w"

void E2_postscript_show(FILE*);

/*:92*/
#line 349 "./kdtree.w"


/*:2*/
