/*5:*/
#line 316 "./twolevel.w"

extern const char*twolevel_rcs_id;
/*13:*/
#line 434 "./twolevel.w"

void twolevel_setup(const int num_vertices,const int start_seg_size);
void twolevel_cleanup(void);

/*:13*//*25:*/
#line 598 "./twolevel.w"

void twolevel_set(int const*tour);


/*:25*//*32:*/
#line 673 "./twolevel.w"

int twolevel_next(int a);
int twolevel_prev(int a);

/*:32*//*34:*/
#line 756 "./twolevel.w"

int twolevel_between(int a,int b,int c);


/*:34*//*37:*/
#line 830 "./twolevel.w"

void twolevel_flip(int a,int b,int c,int d);

/*:37*//*67:*/
#line 1536 "./twolevel.w"

#if defined(TWOLEVEL_DEBUG)
void twolevel_debug_setup(const int num_vertices,const int start_seg_size);
void twolevel_debug_cleanup(void);
void twolevel_debug_set(int const*tour);
int twolevel_debug_next(int a);
int twolevel_debug_prev(int a);
int twolevel_debug_between(int a,int b,int c);
void twolevel_debug_flip(int a,int b,int c,int d);
#endif


/*:67*/
#line 318 "./twolevel.w"


/*:5*/
