
#include "../lib/gc.h"
#include "../lib/mstack.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
 
    cl  lib\gc.c lib\fs.c test\ex_stack_1.c /Fex.exe   /WX /EHsc
    gcc lib\gc.c lib\fs.c test\ex_stack_1.c -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib\fs.c test/ex_stack_1.c -o x       -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart() ;

/**/

    stackType(int,s) ;
    stackNew(s,128);
 
    // ...................................... push
 
    printf ( "\nempty?%d\n",stackEmpty(s) );
    
    stackPush ( s , 1 ) ;
    stackPush ( s , 2 ) ;    
    stackPush ( s , 3 ) ;
    
    printf ( "\ntop[%d]",stackTop(s) );
   
    stackPop(s);

    printf ( "\ntop[%d]",stackTop(s) );
   
    // ...................................... free
    
    stackFree(s);

    printf ("\n");

/**/

    gcStop();
 
    return 0 ;
}





