
#include "../lib/pthread.h"
#include "../lib/timer.h"
#include <stdio.h>

/*

    cl /EHsc test\ex_timer_1.c lib\timer.c lib\gc.c lib\fs.c /Fex.exe /WX
    __MINGW32__ NO
    gcc test/ex_timer_1.c lib/timer.c lib/gc.c    lib/fs.c    -o x     -Wall -Wextra -lpthread
   
*/

//......................................................... callback

void timeout_cb_int(void*_x)
{
    int x = *(int*)_x;
    printf("\n=== CALLBACK INT %d===\n",x);
}
void timeout_cb_strc(void*_x)
{
    char* x = (char*)_x;
    printf("\n=== CALLBACK STRING %s===\n",x);
}

//......................................................... main

int main(void)
{
    gcStart();
 
    // .............................................    set interval
    
    int x = 123 ;
    
    pthread_t pt2 = setInterval((void*)timeout_cb_int,1000,&x ) ;

    // .............................................    set time out

    char* s = "Claudio";

    pthread_t pt1 = setTimeOut((void*)timeout_cb_strc,5000,s ) ;

    // .............................................    join
    
    pthread_join( pt1, NULL);
    
    pthread_join( pt2, NULL);
 
    
    // TODO
    
    // kill process after condition
    
    // .............................................

    printf("\n=== End of Program - all threads in ===\n");

    //
    
    gcStop();
    
    return 0;

}

