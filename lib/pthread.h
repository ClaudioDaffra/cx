
#ifndef cdPTHREAD
#define cdPTHREAD



    #if defined(_WIN32) || defined(_WIN64)
    
        //
        // https://locklessinc.com/articles/pthreads_on_windows/
        //
        
        #include "winpthreads.h"

        #define sleep(...)   Sleep(__VA_ARGS__)
        
    #endif

    #if defined(__linux__)

        #include <pthread.h>
        #include <unistd.h>
        
        #define sleep(...)   usleep(__VA_ARGS__*1000)
 
    #endif


#endif


/**/




