/*2:*/
#line 177 "./read.w"

extern const char*read_rcs_id;
/*9:*/
#line 255 "./read.w"

/*16:*/
#line 378 "./read.w"

typedef enum{EUC_2D,CEIL_2D,EXPLICIT,RANDOM_EDGES}edge_weight_type_t;

/*:16*//*21:*/
#line 405 "./read.w"

typedef enum{NONE,LOWER_DIAG_ROW,FULL_MATRIX,UPPER_ROW}
edge_weight_format_t;

/*:21*//*29:*/
#line 545 "./read.w"

typedef struct{double x[2];}coord_2d;

/*:29*/
#line 256 "./read.w"

typedef struct{
char*name;
char*comment;
int n;
/*17:*/
#line 381 "./read.w"

edge_weight_type_t edge_weight_type;

/*:17*//*22:*/
#line 409 "./read.w"

edge_weight_format_t edge_weight_format;

/*:22*//*26:*/
#line 494 "./read.w"

length_t**edge_weights;

/*:26*//*30:*/
#line 548 "./read.w"

coord_2d*coord;
double xmin,xmax,ymin,ymax;

/*:30*//*35:*/
#line 601 "./read.w"

short**short_edge_weights;

/*:35*/
#line 261 "./read.w"

}tsp_instance_t;

/*:9*/
#line 179 "./read.w"

/*38:*/
#line 628 "./read.w"

extern length_t(*cost)(const int,const int);
extern length_t(*pseudo_cost)(const int,const int);


/*:38*/
#line 180 "./read.w"

/*5:*/
#line 211 "./read.w"

tsp_instance_t*
switch_to(tsp_instance_t*new_problem);

/*:5*//*8:*/
#line 239 "./read.w"

tsp_instance_t*read_tsp_file(FILE*in,FILE*out);


/*:8*//*45:*/
#line 752 "./read.w"

double cost_from_euc2d_raw(const int i,const int j);

/*:45*//*54:*/
#line 896 "./read.w"

void write_tsp_file(tsp_instance_t*tsp,FILE*out);

/*:54*/
#line 181 "./read.w"



/*:2*/
