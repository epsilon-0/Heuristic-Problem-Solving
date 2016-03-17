/*2:*/
#line 172 "./error.w"

/*4:*/
#line 188 "./error.w"

extern const char*error_rcs_id;
extern char const*error_in_file;
extern int error_at_line;


/*:4*//*10:*/
#line 279 "./error.w"

extern void(*error_precleanup_stats)(void);
extern void(*error_cleanup)(void);
extern void(*error_postcleanup_stats)(void);

/*:10*/
#line 173 "./error.w"

/*6:*/
#line 226 "./error.w"

int error_real_if(const int condition,const char*fmt,...);



/*:6*/
#line 174 "./error.w"


#if defined(ERROR_NO_CHECK)
#define errorif  
#else
#define errorif (error_in_file= __FILE__),(error_at_line= __LINE__),error_real_if
#endif

/*:2*/
