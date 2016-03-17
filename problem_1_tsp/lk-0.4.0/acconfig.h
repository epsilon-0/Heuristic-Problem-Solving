/* David Neto wrote this.  In particular, this is human-editable. */

/* We want to know our own version number */
#define VERSION_STRING "0.0.0"

/* We may need to supply function prototypes and structures. */
#define OS_HAS_BROKEN_HEADERS 0

/* The following are used only on SunOS/Solaris. */
#define OS_IS_SUNOS 0
#define OS_VERSION_MAJOR 0
#define OS_VERSION_MINOR 0

/* Sometimes libraries define optarg, etc. but their headers don't declare them.  Solaris can be like that.  */
#define LIBRARY_DEFINES_OPTARG_ETC 0
#define HEADERS_DECLARE_OPTARG_ETC 0
#define COMPILER_SUPPORTS_INLINE 0

