#ifndef cdCXX
#define cdCXX

    #if defined(_WIN32) || defined(_WIN64)
        #include <windows.h>
        #include <io.h>
        #include <fcntl.h>
        #include <locale.h>
        #define cdWINDOWS
    #endif

    #if defined(_WIN64)
        #define cdWINDOWS64
    #endif
    #if defined(_WIN32)
        #define cdWINDOWS32
    #endif
    
    #ifdef __linux__
        #include <wchar.h>
        #define cdLINUX
    #endif

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #ifdef __APPLE__
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdollar-in-identifier-extension"
        #define cdAPPLE
    #endif

    #ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    #endif


    #define _GNU_SOURCE
    #define _XOPEN_SOURCE_EXTENDED 1

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>
    #include <wchar.h>
    #include <uchar.h>
    #include <xmmintrin.h>
    #include <assert.h>
    #include <errno.h>
    #include <ctype.h>
    #include <limits.h>
    #include <float.h>
    #include <stdarg.h>
    #include <locale.h>
    #include <stdbool.h>
    #include <wctype.h>
    #include <time.h>
    
    // .............................................. string.h

    #ifndef cdMB_CUR_MAX
        #if defined(_MSC_VER)
            #define cdMB_CUR_MAX (2)
        #else
            #define cdMB_CUR_MAX 2
        #endif
    #endif

    #define gcMaxStringBuffer    1024

    // ................................................ merge

    #ifndef CONCATENATE
    #define CONCATENATE(x,y)   x##y
    #endif

    #ifndef MERGE
    #define MERGE(x,y)    CONCATENATE(x,y)
    #endif

    // (not standard) : error: use of undeclared identifier 'errno_t'
    typedef int errno_t;

    #include "gc.h"
    #include "hashMap.h"

    #include "stdio.h"

    #include "string.h"
    #include "stringw.h"
    #include "string8.h"

    #include "mvector.h"
    #include "iterator.h"
    #include "mstack.h"


    // ................................................ new

    #define new(ID)       gcMalloc(sizeof(ID));

    // ................................................ delete

    #define delete(ID)    if((ID)!=NULL){gcFree(ID);(ID)=NULL;}

    //

    #ifndef CONCATENATE
    #define CONCATENATE(x,y)   x##y
    #endif

    #ifndef TYPEOF
    #define TYPEOF(x,y)    CONCATENATE(x,y)
    #endif

    #ifndef MERGE
    #define MERGE    TYPEOF
    #endif

#endif


/**/


