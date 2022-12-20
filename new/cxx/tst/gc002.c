#include "../src/cxx.h"

// clear  ; gcc src/gc.c tst/gc002.c -o bin/x       -Wall -Wextra -pedantic 
// cls    & cl src\gc.c tst\gc002.c /Febin\x.exe    /WX /utf-8

int main(void)
{
    gc_t *map = gcLocalStart();
   
    char* c1 = (char*) gcLocalMalloc ( map,10 ) ;
    FILE* f1 = gcLocalFileOpen ( map , "deleteme.txt" , "w+" ) ;

    wchar_t *s = (wchar_t*)gcWcsDup(L"claudio daffra");
    
    c1=gcLocalRealloc( map,c1, 100 );
    c1=gcLocalRealloc( map,c1, 1 );
    
	gcLocalFree( map,(void*)c1 ) ;
	gcLocalFree( map,(void*)f1 ) ;

    gcLocalStop(map);
   
    printf ( "\n") ;    
    return 0;
}
