
#include "../lib/stdio.h"
#include "../lib/gc.h"

/*

    cl  lib\gc.c  lib\fs.c lib\stdio.c test\ex_stdio_1.c   /Fex.exe    /WX
    gcc lib\gc.c  lib\fs.c lib\stdio.c test\ex_stdio_1.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c  lib/fs.c lib/stdio.c test\ex_stdio_1.c   -o x        -Wall -Wextra -pedantic

*/

int main ( void )
{
    gcStart(); 
    
    //
    
    printf ( "\n STREAM [%d]\n",std_stream );
    
    stdSetUTF8() ;

    wprintf ( L"\n STREAM [%d]\n",std_stream );
    
    //

    gcStop() ;
    
    return 0 ;
}
