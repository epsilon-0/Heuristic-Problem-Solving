#define matchword(STR) (0==strncmp(keyword,STR,strlen(STR) ) )  \

#define min(X,Y) ((X) >(Y) ?(Y) :(X) ) 
#define max(X,Y) ((X) <(Y) ?(Y) :(X) )  \

/*1:*/
#line 155 "./read.w"

#include <config.h>
#include "lkconfig.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "fixincludes.h"
/*7:*/
#line 234 "./read.w"

#include "memory.h"
#include "error.h"

/*:7*//*12:*/
#line 330 "./read.w"

#include <string.h>

/*:12*//*14:*/
#line 356 "./read.w"

#include <ctype.h>

/*:14*//*19:*/
#line 387 "./read.w"

#include "gb_flip.h"




/*:19*//*25:*/
#line 491 "./read.w"

#include "length.h"

/*:25*//*32:*/
#line 563 "./read.w"

#include <limits.h>

/*:32*//*46:*/
#line 759 "./read.w"

#include <math.h>

/*:46*/
#line 162 "./read.w"


#include "read.h"

/*3:*/
#line 191 "./read.w"

static tsp_instance_t*p;

/*:3*//*37:*/
#line 623 "./read.w"

length_t(*cost)(const int,const int);
length_t(*pseudo_cost)(const int,const int);

/*:37*/
#line 166 "./read.w"

/*42:*/
#line 713 "./read.w"

#if defined(COST_USE_HYPOT)
#define my_hypot(A,B) (hypot((A),(B)))
#else
#define my_hypot(A,B) (sqrt((A)*(A)+(B)*(B)))
#endif

/*:42*/
#line 167 "./read.w"

/*39:*/
#line 636 "./read.w"

length_t cost_from_matrix(const int i,const int j);

length_t
cost_from_matrix(const int i,const int j)
{
return(length_t)p->edge_weights[i][j];
}

length_t cost_from_short_matrix(const int i,const int j);

length_t
cost_from_short_matrix(const int i,const int j)
{
return(length_t)p->short_edge_weights[i][j];
}


/*:39*//*40:*/
#line 675 "./read.w"

length_t cost_from_euc2d(const int i,const int j);
length_t
cost_from_euc2d(const int i,const int j)
{
coord_2d*coord_array= p->coord;
double xd= coord_array[i].x[0]-coord_array[j].x[0];
double yd= coord_array[i].x[1]-coord_array[j].x[1];
return(length_t)floor(0.5+my_hypot(xd,yd));
}

/*:40*//*41:*/
#line 690 "./read.w"

length_t cost_from_ceil2d(const int i,const int j);
length_t
cost_from_ceil2d(const int i,const int j)
{
coord_2d*coord_array= p->coord;
double xd= coord_array[i].x[0]-coord_array[j].x[0];
double yd= coord_array[i].x[1]-coord_array[j].x[1];
return(length_t)ceil(my_hypot(xd,yd));
}

/*:41*//*43:*/
#line 723 "./read.w"

length_t cost_from_euc2d_not_rounded(const int i,const int j);
length_t
cost_from_euc2d_not_rounded(const int i,const int j)
{
coord_2d*coord_array= p->coord;
double xd= coord_array[i].x[0]-coord_array[j].x[0];
double yd= coord_array[i].x[1]-coord_array[j].x[1];
return(length_t)my_hypot(xd,yd);
}

/*:43*//*47:*/
#line 766 "./read.w"

length_t pseudo_cost_from_euc2d(const int i,const int j);
length_t
pseudo_cost_from_euc2d(const int i,const int j)
{
coord_2d*coord_array= p->coord;
double xd= coord_array[i].x[0]-coord_array[j].x[0];
double yd= coord_array[i].x[1]-coord_array[j].x[1];
return(length_t)(xd*xd+yd*yd);
}


/*:47*/
#line 168 "./read.w"

/*4:*/
#line 199 "./read.w"

tsp_instance_t*
switch_to(tsp_instance_t*new_problem)
{
tsp_instance_t*old_problem;
old_problem= p;
p= new_problem;
/*48:*/
#line 782 "./read.w"

switch(p->edge_weight_type){
case EXPLICIT:
cost= cost_from_matrix;
pseudo_cost= cost_from_matrix;
break;
case EUC_2D:
{
extern int noround;
cost= noround?cost_from_euc2d_not_rounded:cost_from_euc2d;
}
pseudo_cost= pseudo_cost_from_euc2d;
break;
case CEIL_2D:
{
extern int noround;
cost= noround?cost_from_euc2d_not_rounded:cost_from_ceil2d;
}
pseudo_cost= pseudo_cost_from_euc2d;
break;
case RANDOM_EDGES:
errorif(p->short_edge_weights==NULL,"RANDOM_EDGES specified but no SEED given");
cost= cost_from_short_matrix;
pseudo_cost= cost_from_short_matrix;
break;
}

/*:48*/
#line 206 "./read.w"

return old_problem;
}

/*:4*//*6:*/
#line 221 "./read.w"

tsp_instance_t*
read_tsp_file(FILE*in,FILE*debug)
{
p= new_of(tsp_instance_t);
/*10:*/
#line 267 "./read.w"

p->name= NULL;
p->comment= NULL;
p->n= 0;

/*:10*//*18:*/
#line 384 "./read.w"

p->edge_weight_type= EUC_2D;

/*:18*//*23:*/
#line 412 "./read.w"

p->edge_weight_format= NONE;


/*:23*//*27:*/
#line 497 "./read.w"

p->edge_weights= NULL;


/*:27*//*31:*/
#line 558 "./read.w"

p->coord= NULL;
p->xmin= p->ymin= INT_MAX;
p->xmax= p->ymax= INT_MIN;

/*:31*//*36:*/
#line 604 "./read.w"

p->short_edge_weights= NULL;

/*:36*/
#line 226 "./read.w"

/*11:*/
#line 277 "./read.w"

{
#define MAX_KEYWORD_LEN (25)
#define MAX_LINE_LEN (200)
char keyword[MAX_KEYWORD_LEN],rest_of_line[MAX_LINE_LEN];
int more_input= 1,lineno= 0;
while(more_input){
char*colon;int r;
keyword[0]= 0;
r= fscanf(in," %s ",keyword);
if(r==EOF){more_input= 0;break;}
errorif(r!=1,"%d: Couldn't read the word following \"%s\". (r==%d)",
lineno+1,keyword,r);
if(NULL!=(colon= strchr(keyword,':')))*colon= '\0';
if(matchword("EOF")){
more_input= 0;
}else if(matchword("NAME")){
/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 294 "./read.w"

p->name= dup_string(rest_of_line);
}else if(matchword("COMMENT")){
/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 297 "./read.w"

p->comment= dup_string(rest_of_line);
}else if(matchword("TYPE")){
/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 300 "./read.w"

errorif(strcmp(rest_of_line,"TSP"),"Can't read TSPLIB files of type %s.",rest_of_line);
}else if(matchword("DIMENSION")){
/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 303 "./read.w"

p->n= atoi(rest_of_line);
}else if(matchword("DISPLAY_DATA_TYPE")){
/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 306 "./read.w"


}else if(matchword("EDGE_WEIGHT_TYPE")){
/*15:*/
#line 364 "./read.w"

/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 365 "./read.w"

if(0==strcmp(rest_of_line,"EUC_2D")){
p->edge_weight_type= EUC_2D;
}else if(0==strcmp(rest_of_line,"CEIL_2D")){
p->edge_weight_type= CEIL_2D;
}else if(0==strcmp(rest_of_line,"EXPLICIT")){
p->edge_weight_type= EXPLICIT;
}else if(0==strcmp(rest_of_line,"RANDOM_EDGES")){
p->edge_weight_type= RANDOM_EDGES;
}else{
errorif(1,"%d: Apology: Unknown edge weight type \"%s\".",lineno,rest_of_line);
}

/*:15*/
#line 309 "./read.w"

}else if(matchword("EDGE_WEIGHT_FORMAT")){
/*20:*/
#line 393 "./read.w"

/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 394 "./read.w"

if(0==strcmp(rest_of_line,"LOWER_DIAG_ROW")){
p->edge_weight_format= LOWER_DIAG_ROW;
}else if(0==strcmp(rest_of_line,"FULL_MATRIX")){
p->edge_weight_format= FULL_MATRIX;
}else if(0==strcmp(rest_of_line,"UPPER_ROW")){
p->edge_weight_format= UPPER_ROW;
}else{
errorif(1,"%d: Unknown edge weight format \"%s\".",lineno,rest_of_line);
}

/*:20*/
#line 311 "./read.w"

}else if(matchword("EDGE_WEIGHT_SECTION")){
/*24:*/
#line 421 "./read.w"

switch(p->edge_weight_format){
long int long_dummy;
case LOWER_DIAG_ROW:
{
int row,col;
p->edge_weights= new_arr_of(length_t*,p->n);

for(row= 0;row<p->n;row++){
p->edge_weights[row]= new_arr_of(length_t,p->n);
}
for(row= 0;row<p->n;row++){
for(col= 0;col<=row;col++){
int r= fscanf(in," %ld ",&long_dummy);
errorif(1!=r,
"Couldn't convert an edge weight: %d to %d.",row+1,col+1);
p->edge_weights[col][row]= p->edge_weights[row][col]= long_dummy;
}
}
}
break;
case FULL_MATRIX:
{
int row,col;
p->edge_weights= new_arr_of(length_t*,p->n);

for(row= 0;row<p->n;row++){
p->edge_weights[row]= new_arr_of(length_t,p->n);
}
for(row= 0;row<p->n;row++){
for(col= 0;col<p->n;col++){
int r= fscanf(in," %ld ",&long_dummy);
errorif(1!=r,
"Couldn't convert an edge weight: %d to %d.",row+1,col+1);
p->edge_weights[row][col]= long_dummy;
}
}
for(row= 0;row<p->n;row++){
for(col= 0;col<row;col++){
errorif(p->edge_weights[row][col]!=p->edge_weights[col][row],
"Asymmetric FULL_MATRIX:  (%d,%d) does not match (%d,%d)",
row,col,col,row);
}
}
}
break;
case UPPER_ROW:
{
int row,col;
p->edge_weights= new_arr_of(length_t*,p->n);

for(row= 0;row<p->n;row++){
p->edge_weights[row]= new_arr_of(length_t,p->n);
p->edge_weights[row][row]= 0;
}
for(row= 0;row<p->n;row++){

for(col= row+1;col<p->n;col++){
int r= fscanf(in," %ld ",&long_dummy);
errorif(1!=r,
"Couldn't convert an edge weight: %d to %d.",row+1,col+1);
p->edge_weights[col][row]= p->edge_weights[row][col]= long_dummy;
}
}
}
break;
default:break;
}

/*:24*/
#line 313 "./read.w"

}else if(matchword("NODE_COORD_SECTION")){
/*28:*/
#line 521 "./read.w"

{

int i,j;
p->coord= new_arr_of(coord_2d,p->n);
for(i= 0;i<p->n;i++){
fscanf(in," %d ",&j);
fscanf(in," %lf %lf ",&p->coord[j-1].x[0],&p->coord[j-1].x[1]);
p->xmin= min(p->xmin,p->coord[j-1].x[0]);
p->ymin= min(p->ymin,p->coord[j-1].x[1]);
p->xmax= max(p->xmax,p->coord[j-1].x[0]);
p->ymax= max(p->ymax,p->coord[j-1].x[1]);
lineno++;
}
}

/*:28*/
#line 315 "./read.w"

}else if(matchword("DISPLAY_DATA_SECTION")){
/*33:*/
#line 568 "./read.w"

{
int i;
double dummy;
for(i= 0;i<p->n;i++){
fscanf(in," %lf %lf %lf ",&dummy,&dummy,&dummy);
}
}

/*:33*/
#line 317 "./read.w"

}else if(matchword("SEED")){
/*34:*/
#line 579 "./read.w"

/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 580 "./read.w"

gb_init_rand(atol(rest_of_line));
{int i,j;
p->short_edge_weights= new_arr_of(short*,p->n);
for(i= 0;i<p->n;i++){
p->short_edge_weights[i]= new_arr_of(short,p->n);
p->short_edge_weights[i][i]= 0;
}
for(i= 0;i<p->n;i++)
for(j= 0;j<i;j++)
p->short_edge_weights[i][j]= p->short_edge_weights[j][i]= 
(short)(1+gb_unif_rand(1000L));
if(p->n<=10){
printf("Cost matrix:\n");
for(i= 0;i<p->n;i++){
for(j= 0;j<p->n;j++)printf(" %4d",p->short_edge_weights[i][j]);
printf("\n");
}
}
}

/*:34*/
#line 319 "./read.w"

}else{
/*13:*/
#line 339 "./read.w"

{
int l;char*rcp;
if(colon==NULL){
int r= fscanf(in," : ");
errorif(r!=0,"%d: Missed the colon.",lineno);
}
rcp= fgets(rest_of_line,MAX_LINE_LEN,in);
errorif(NULL==rcp,
"%d: Couldn't read after the colon; truncated file?",lineno);
l= strlen(rest_of_line)-1;
if(l>=0&&rest_of_line[l]=='\n'){rest_of_line[l--]= '\0';lineno++;}
while(l>=0&&isspace(rest_of_line[l]))rest_of_line[l--]= '\0';
if(feof(in))more_input= 0;
}

/*:13*/
#line 321 "./read.w"

errorif(1,"%d: Don't know what the keyword %s is!",lineno,keyword);
}
}
/*48:*/
#line 782 "./read.w"

switch(p->edge_weight_type){
case EXPLICIT:
cost= cost_from_matrix;
pseudo_cost= cost_from_matrix;
break;
case EUC_2D:
{
extern int noround;
cost= noround?cost_from_euc2d_not_rounded:cost_from_euc2d;
}
pseudo_cost= pseudo_cost_from_euc2d;
break;
case CEIL_2D:
{
extern int noround;
cost= noround?cost_from_euc2d_not_rounded:cost_from_ceil2d;
}
pseudo_cost= pseudo_cost_from_euc2d;
break;
case RANDOM_EDGES:
errorif(p->short_edge_weights==NULL,"RANDOM_EDGES specified but no SEED given");
cost= cost_from_short_matrix;
pseudo_cost= cost_from_short_matrix;
break;
}

/*:48*/
#line 325 "./read.w"

}

/*:11*/
#line 227 "./read.w"

/*50:*/
#line 826 "./read.w"

if(debug){
fprintf(debug,"/N {%d} def        %% number of nodes\n",p->n);
if(p->n<8191)
fprintf(debug,"/xs N 1 add array def\n/ys N 1 add array def\n");
}


/*:50*//*51:*/
#line 836 "./read.w"

if(debug){
const double xdiff= ((double)p->xmax)-((double)p->xmin);
const double ydiff= ((double)p->ymax)-((double)p->ymin);
const double maxrange= max(xdiff,ydiff);
const double xoffset= xdiff<ydiff?(maxrange-xdiff)/2:0.0;
const double yoffset= ydiff<xdiff?(maxrange-ydiff)/2:0.0;
fprintf(debug,"/xmin {%f} def \n",p->xmin);
fprintf(debug,"/xmax {%f} def \n",p->xmax);
fprintf(debug,"/ymin {%f} def \n",p->ymin);
fprintf(debug,"/ymax {%f} def \n",p->ymax);
fprintf(debug,"/maxrange {%f} def \n",maxrange);
fprintf(debug,"/xoffset  {%f} def \n",xoffset);
fprintf(debug,"/yoffset  {%f} def \n",yoffset);
}

/*:51*//*52:*/
#line 853 "./read.w"

if(debug){int i;
for(i= 0;i<p->n;i++){
fprintf(debug,"%f %f ts\n",p->coord[i].x[0],p->coord[i].x[1]);
}
fflush(debug);
}

/*:52*/
#line 228 "./read.w"

return p;
}

/*:6*//*44:*/
#line 741 "./read.w"

double
cost_from_euc2d_raw(const int i,const int j)
{
coord_2d*coord_array= p->coord;
double xd= coord_array[i].x[0]-coord_array[j].x[0];
double yd= coord_array[i].x[1]-coord_array[j].x[1];
return my_hypot(xd,yd);
}

/*:44*//*53:*/
#line 864 "./read.w"

void
write_tsp_file(tsp_instance_t*tsp,FILE*out)
{
if(out){
fprintf(out,"NAME: %s\n",tsp->name);
fprintf(out,"TYPE: TSP\n");
if(tsp->comment){fprintf(out,"COMMENT: %s\n",tsp->comment);}
fprintf(out,"DIMENSION: %d\n",tsp->n);
switch(tsp->edge_weight_type){
case CEIL_2D:fprintf(out,"EDGE_WEIGHT_TYPE: CEIL_2D\n");
/*55:*/
#line 900 "./read.w"

fprintf(out,"NODE_COORD_SECTION\n");
{int i;
for(i= 0;i<tsp->n;i++){
fprintf(out,"%d %20g %20g\n",i+1,tsp->coord[i].x[0],tsp->coord[i].x[1]);
}
}


/*:55*/
#line 875 "./read.w"

break;
case EUC_2D:fprintf(out,"EDGE_WEIGHT_TYPE: EUC_2D\n");
/*55:*/
#line 900 "./read.w"

fprintf(out,"NODE_COORD_SECTION\n");
{int i;
for(i= 0;i<tsp->n;i++){
fprintf(out,"%d %20g %20g\n",i+1,tsp->coord[i].x[0],tsp->coord[i].x[1]);
}
}


/*:55*/
#line 878 "./read.w"

break;
case EXPLICIT:fprintf(out,"EDGE_WEIGHT_TYPE: EXPLICIT\n");
{int format= tsp->edge_weight_format;
/*56:*/
#line 910 "./read.w"

{int row,col;
switch(format){
case LOWER_DIAG_ROW:
fprintf(out,"EDGE_WEIGHT_FORMAT: LOWER_DIAG_ROW\n");
fprintf(out,"EDGE_WEIGHT_SECTION\n");
for(row= 0;row<tsp->n;row++){
for(col= 0;col<=row;col++){
fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
}
fprintf(out,"\n");
}
break;
case FULL_MATRIX:
fprintf(out,"EDGE_WEIGHT_FORMAT: FULL_MATRIX\n");
fprintf(out,"EDGE_WEIGHT_SECTION:\n");
for(row= 0;row<tsp->n;row++){
for(col= 0;col<tsp->n;col++){
fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
}
fprintf(out,"\n");
}
break;
case UPPER_ROW:
fprintf(out,"EDGE_WEIGHT_FORMAT: UPPER_ROW\n");
fprintf(out,"EDGE_WEIGHT_SECTION:\n");
for(row= 0;row<tsp->n;row++){
for(col= row+1;col<tsp->n;col++){
fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
}
fprintf(out,"\n");
}
break;
default:break;
}
}


/*:56*/
#line 882 "./read.w"

}
break;
case RANDOM_EDGES:fprintf(out,"EDGE_WEIGHT_TYPE: EXPLICIT\n");
{int format= UPPER_ROW;
/*56:*/
#line 910 "./read.w"

{int row,col;
switch(format){
case LOWER_DIAG_ROW:
fprintf(out,"EDGE_WEIGHT_FORMAT: LOWER_DIAG_ROW\n");
fprintf(out,"EDGE_WEIGHT_SECTION\n");
for(row= 0;row<tsp->n;row++){
for(col= 0;col<=row;col++){
fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
}
fprintf(out,"\n");
}
break;
case FULL_MATRIX:
fprintf(out,"EDGE_WEIGHT_FORMAT: FULL_MATRIX\n");
fprintf(out,"EDGE_WEIGHT_SECTION:\n");
for(row= 0;row<tsp->n;row++){
for(col= 0;col<tsp->n;col++){
fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
}
fprintf(out,"\n");
}
break;
case UPPER_ROW:
fprintf(out,"EDGE_WEIGHT_FORMAT: UPPER_ROW\n");
fprintf(out,"EDGE_WEIGHT_SECTION:\n");
for(row= 0;row<tsp->n;row++){
for(col= row+1;col<tsp->n;col++){
fprintf(out," %ld",(long)(tsp->edge_weights[row][col]));
}
fprintf(out,"\n");
}
break;
default:break;
}
}


/*:56*/
#line 887 "./read.w"

}
break;
fprintf(out,"EOF\n");
}
}
}

/*:53*/
#line 169 "./read.w"

const char*read_rcs_id= "$Id: read.w,v 1.135 1998/07/16 21:58:55 neto Exp neto $";


/*:1*/
