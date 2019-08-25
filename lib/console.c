
    #if defined(_WIN32) || defined(_WIN64)
        #include "console_win.c"
    #endif

    #if defined(__linux__)
        #include "console_lin.c"
    #endif
    
    
/**/


