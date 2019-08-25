
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"

/*

    cl  lib\gc.c  lib\fs.c   lib\stdio.c test\ex_dir_1.c   /Fex.exe    /WX
    gcc lib\gc.c  lib\fs.c   lib\stdio.c test\ex_dir_1.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c  lib/fs.c   lib/stdio.c test/ex_dir_1.c   -o x        -Wall -Wextra -pedantic

*/

/*
    this file contains follow function example :
    :   dirRename
    :   dirMake
    :   dirRemove
    :   dirRemoveAll
    :   getFullPath
    :   getRealPath
    :   DirExists
*/

/**/

int main ( void )
{
 
    gcStart(); 

    //

    dirRename ( "data\\pippo" , "data\\pluto" );

    dirMake ( "data\\pippo" );

    dirMake ( "data\\deleteme" );
    
    dirRemove ( "data\\deleteme" ); 

    dirMake ( "deleteme" );
    dirMake ( "deleteme\\deleteme" );
 
    dirRemoveAll("deleteme");

    //

    printf ( "\ncurrent working dir (%s)" , getFullPath() );

    printf ( "\nreal path od README.md := (%s)" , getRealPath("README.md") );

    printf ("\ndir exist test ? (%d). ",dirExists("test") ) ;

    // .......................... dir change
    
    
    printf ( "\nBefore dirChange\ncurrent working dir (%s)" , getFullPath() );    
    dirChange("..");
    printf ( "\nAtfter dirChange\ncurrent working dir (%s)" , getFullPath() );
    
    printf ("\n");

    //
    
    gcStop() ;
    
    return 0 ;
}

/*

    claudio@ubuntu:~/cx$ sh v.sh 
    ==7888== Memcheck, a memory error detector
    ==7888== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==7888== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==7888== Command: ../x
    ==7888== 
    ==7888== 
    ==7888== HEAP SUMMARY:
    ==7888==     in use at exit: 0 bytes in 0 blocks
    ==7888==   total heap usage: 17 allocs, 17 frees, 66,018 bytes allocated
    ==7888== 
    ==7888== All heap blocks were freed -- no leaks are possible
    ==7888== 
    ==7888== For counts of detected and suppressed errors, rerun with: -v
    ==7888== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/cx$ 

*/


