
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"

/*

    cl  lib\gc.c  lib\fs.c   lib\stdio.c test\ex_dir_2.c   /Fex.exe    /WX
    gcc lib\gc.c  lib\fs.c   lib\stdio.c test\ex_dir_2.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c  lib/fs.c   lib/stdio.c test/ex_dir_2.c   -o x        -Wall -Wextra -pedantic

*/

/*
    this file contains follow function example :
    : isDir
    : isFile
    : dirOpen
    : dirClose
    : dirType
    : itDir
    : dirBegin
    : dirEnd
    : dirNext
*/

int main ( void )
{
 
    gcStart(); 

    //

    printf ( "\n license.txt is dir ? %d ." , isDir("license.txt") ) ;
    printf ( "\n test        is dir ? %d ." , isDir("test") ) ;
    printf ( "\n license.txt is dir ? %d ." , isFile("license.txt") ) ;
    printf ( "\n test        is dir ? %d ." , isFile("test") ) ;

    // ............................................... iterator

    dirType(dir);   
    
    itDir(it);  
    
    dir = dirOpen (".");
    
    if (dir != NULL) 
    {
        for ( it = dirBegin(dir) ; it!=dirEnd(); it = dirNext (dir)  )
        {
            printf ("((%s))\n", it->d_name);
        }
        dirClose (dir);
    } 
    else 
    {
        return EXIT_FAILURE;
    }

    //
    
    gcStop() ;
    
    return 0 ;
}

/*
    ==12358== 
    ==12358== HEAP SUMMARY:
    ==12358==     in use at exit: 0 bytes in 0 blocks
    ==12358==   total heap usage: 4 allocs, 4 frees, 33,882 bytes allocated
    ==12358== 
    ==12358== All heap blocks were freed -- no leaks are possible
    ==12358== 
    ==12358== For counts of detected and suppressed errors, rerun with: -v
    ==12358== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/cx$  
*/


