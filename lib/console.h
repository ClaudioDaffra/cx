
#ifndef cdCONSOLE
#define cdCONSOLE

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #ifndef TRUE
    #define TRUE    1
    #endif
    #ifndef FALSE
    #define FALSE    0
    #endif
    #ifndef ON
    #define ON    1
    #endif
    #ifndef OFF
    #define OFF    0
    #endif
    
    #include <stdio.h>

    #if defined(_WIN32) || defined(_WIN64)
        #include "console_win.h"
    #endif

    #if defined(__linux__)
        #include "console_lin.h"
    #endif

#endif


/**/


