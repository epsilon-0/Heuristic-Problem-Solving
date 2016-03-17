/*2:*/
#line 75 "./tspps.w"


const char*prog_name= "tspps";
const char*tspps_rcs_id= "$Id: tspps.w,v 1.2 1998/07/16 21:58:55 neto Exp neto $";
#include <config.h>
#include "lkconfig.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/*7:*/
#line 160 "./tspps.w"

#include <ctype.h>

/*:7*/
#line 84 "./tspps.w"

/*4:*/
#line 120 "./tspps.w"

#include "error.h"

/*:4*//*8:*/
#line 165 "./tspps.w"

#include "length.h"
#include "read.h"

/*:8*/
#line 85 "./tspps.w"


/*9:*/
#line 171 "./tspps.w"

int noround= 1;

/*:9*/
#line 87 "./tspps.w"


/*6:*/
#line 144 "./tspps.w"

static void write_PS_string(FILE*out,char*str);
static void
write_PS_string(FILE*out,char*str)
{
char*p;
fputc('(',out);
for(p= str;*p;p++){
if(*p=='('||*p==')'||*p=='\\')fprintf(out,"\\%c",*p);
else if(isprint(*p))fputc(*p,out);
else fprintf(out,"\\%3o",*p);
}
fputc(')',out);
}

/*:6*/
#line 89 "./tspps.w"


int main(int argc,char**argv)
{
/*3:*/
#line 103 "./tspps.w"

{
FILE*prolog;
char buf[8192];
size_t countin,countout;
prolog= fopen("prolog.ps","r");
errorif(prolog==NULL,"Couldn't open prolog.ps for reading");
while((countin= fread(buf,1,8192,prolog))>0){
char*p= buf;
while((countout= fwrite(p,1,countin,stdout))<countin){
countin-= countout;p+= countout;
}
}
fclose(prolog);
}

/*:3*/
#line 93 "./tspps.w"

/*5:*/
#line 128 "./tspps.w"

{tsp_instance_t*tsp;
tsp= read_tsp_file(stdin,stdout);
if(tsp->name)write_PS_string(stdout,tsp->name),printf(" title\n");
if(tsp->comment)write_PS_string(stdout,tsp->comment),printf(" comment\n");
}

/*:5*/
#line 94 "./tspps.w"

/*10:*/
#line 180 "./tspps.w"

fputs("end\n",stdout);
fputs("grestore\n",stdout);
fputs("showpage\n",stdout);
fputs("%%EOF\n",stdout);

/*:10*/
#line 95 "./tspps.w"

return 0;
}

/*:2*/
