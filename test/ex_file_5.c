
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"

/*

    cl  lib\gc.c lib\fs.c lib\stdio.c test\ex_file_5.c   /Fex.exe    /WX
    gcc lib\gc.c lib\fs.c lib\stdio.c test\ex_file_5.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/stdio.c test/ex_file_5.c   -o x        -Wall -Wextra -pedantic

*/

/**

    this file contains follow function example :
    : fileExists
    : fileLock
    : fileUnLock
    : freeSpaceOnDrive 
    : fileCopy
    : fileTemp
    : dirTemp
*/

int main ( void )
{
    gcStart(); 

    //

    printf ("\nfile exist README.md ? (%d). "   ,   fileExist("README.md") ) ;
    
    printf ("\nfile EXT README.md ? (%s). "     ,   fileExt("README.md") ) ;
    
    printf ("\nfile EXT makefile ? (%s). "      ,   fileExt("makefile") ) ;
    
    printf ("\nfile Space On Drive %ld "        ,   freeSpaceOnDrive("\\") ) ;
    
    fileCopy( "README.copy.md", "README.md"   );

    FILE* ft0 = fileTemp() ;
    
    printf ( "\n temp dir (%s).",dirTemp() );
    
    //

    gcStop() ;
 
    return 0 ;
}

/*
 

*/


