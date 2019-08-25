
#include "../lib/gc.h"
#include "../lib/mqueue.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*

    cl  lib\gc.c lib\fs.c test\ex_queue_1.c /Fex.exe   /WX  /EHsc 
    gcc lib\gc.c lib\fs.c test\ex_queue_1.c -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c test/ex_queue_1.c -o x       -Wall -Wextra -pedantic

*/



int main ( void )
{
    gcStart() ;

/**/

    queueType(int,s) ; // 
    queueNew(s,128) ; // 
 
    // ...................................... push
 
    printf ( "\nempty?%d\n",queueEmpty(s) );
    
    queuePush ( s , 1 ) ;

    printf ( "\ntop[%d]",queueTop(s) );
 
    queuePush ( s , 2 ) ;    

    printf ( "\ntop[%d]",queueTop(s) );

    queuePush ( s , 3 ) ;
    
    printf ( "\ntop[%d]",queueTop(s) );
 
    queuePop(s);

    printf ( "\ntop[%d]",queueTop(s) );
 
    // ...................................... free
    
    queueFree(s);

    printf ("\n");
 
/**/

    gcStop();
 
    return 0 ;
}





