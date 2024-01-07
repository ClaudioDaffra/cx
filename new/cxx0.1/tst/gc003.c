
#include "../src/cxx.h"

// clear    ; gcc   src/gc.c tst/gc003.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c tst\gc003.c /Febin\x.exe   /WX /utf-8

#define KPTRMAX 100

int main(void)
{
    gcStart();
    
    //
    
    int *ptr = NULL;
    
    for(int i = 0 ; i < KPTRMAX ; i++)
    {
        ptr = (int*) gcMalloc ( 10*i ) ; 
        
        //printf ( "[%p]\n",ptr ) ;
        
        if ( i%3==0 ) ptr=gcRealloc( ptr, 100*i ); 
        
        if ( i%5==0 ) ptr=gcRealloc( ptr, 1*i   );
        
        if ( i%2==0 ) gcFree(ptr); 
    }

    gcStop();
   
    printf ( "\n") ;
    
    return 0;
}
