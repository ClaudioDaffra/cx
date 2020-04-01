#ifndef cdSTDIO
#define cdSTDIO

#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>


// questo perr evitare warning comparazione ( signed wchar_t / unsigned wchar_t )
#define _WEOF (wchar_t)WEOF

// (not standard ) : error: use of undeclared identifier 'errno_t'
typedef int errno_t;

//

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <io.h>
#include <fcntl.h>

#endif

#include <wchar.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/**/

//extern int  cdFile_wopen        ( FILE** pf, const char* fileName, const char* flag , const char* ccs  )  ;
extern void cdConsolesetUTF8    ( void    ) ;

#define consoleSetUTF8  cdConsolesetUTF8
#define stdSetUTF8      cdConsolesetUTF8

// gnu gcc in windows si basa sulle librerie microsoft
// queste non supportano il 'long double' (mingw)
 
#ifdef __GNUC__    
    #if defined(_WIN32) || defined(_WIN64)
		#ifndef __USE_MINGW_ANSI_STDIO
			#define __USE_MINGW_ANSI_STDIO  1
	    #endif
    #endif
#endif

#ifdef __USE_MINGW_ANSI_STDIO

        #define printf      __mingw_printf
        #define wprintf     __mingw_wprintf  
        #define fprintf     __mingw_fprintf 
        #define fwprintf    __mingw_fwprintf 
        #define snprintf    __mingw_snprintf  
        #define snwprintf   __mingw_snwprintf         
        #define sprintf     __mingw_sprintf 
        #define swprintf    __mingw_swprintf         
        #define scanf       __mingw_scanf 
        #define wscanf      __mingw_wscanf    
        #define sscanf      __mingw_sscanf  
        #define swscanf     __mingw_swscanf  
        #define fscanf      __mingw_fscanf 
        #define fwscanf     __mingw_fwscanf   

        // creano qualche casino
        
        // #define vsnprintf   __mingw_vsnprintf
        // #define vsnwprintf  __mingw_vsnwprintf

        #define vfprintf    __mingw_vfprintf
        #define vfscanf     __mingw_vfscanf
        #define vprintf     __mingw_vprintf 
        #define vsscanf     __mingw_vsscanf
        
#endif

/**/


typedef enum console_stream_e
{
    
    console_stream_ansi=100,
    console_stream_wide=200
    
} console_stream_t ;

extern console_stream_t std_stream;

/**/

#endif  /* cdSTDIO */


/**/

