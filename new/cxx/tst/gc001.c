
#include "../src/cxx.h"

// clear    ; gcc   src/gc.c tst/gc001.c  -o bin/x       -Wall -Wextra -pedantic 
// cls      & cl    src\gc.c tst\gc001.c /Febin\x.exe   /WX /utf-8

int main(void)
{
    gcStart();
    
    //
   
    char* c1 = (char*) gcMalloc ( 10 ) ;
    
    FILE* f1 = gcFileOpen ( "deleteme.txt" , "w+" ) ;
   
    char *s = gcStrDup("claudio daffra");
    
    c1=gcRealloc( c1, 100 );
    c1=gcRealloc( c1, 1   );
    
	gcFree( c1 ) ;
	gcFree( f1 ) ;

	//

    gcStop();
   
    printf ( "\n") ;
    
    return 0;
}
