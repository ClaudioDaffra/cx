
#include "../lib/gc.h"
#include "../lib/mpriorityQueue.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*

    cl  lib\gc.c lib\fs.c  test\ex_priorityQueue_2.c    /Fex.exe   /WX /EHsc
    gcc lib\gc.c lib\fs.c test\ex_priorityQueue_2.c    -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib\fs.c test/ex_priorityQueue_2.c    -o x       -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart() ;

/**/

    typedef char* stringc ;

    priorityQueueType(stringc,s) ; //

    s.compare = gcCompareStrC ;
 
    priorityQueueNew(s,128) ; // 
 
    // ...................................... empty
 
    printf ( "\nempty?%d\n",priorityQueueEmpty(s) );
    
    priorityQueuePush ( s , gcStrDup("claudio") ) ;

    // ...................................... top
 

    printf ( "\ntop[%s].",priorityQueueTop(s) );

    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%s]",s.data[i] ); 

    // ...................................... push

    priorityQueuePush ( s , gcStrDup("marisa")  ) ;    

    printf ( "\ntop[%s].",priorityQueueTop(s) );

    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%s]",s.data[i] ); 

    // ...................................... push

    priorityQueuePush ( s , gcStrDup("lorenzo") ) ;
   
    printf ( "\ntop[%s].",priorityQueueTop(s) );
 
    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%s]",s.data[i] ); 

    // ...................................... push

    priorityQueuePush ( s , gcStrDup("barbara")  ) ;

    printf ( "\ntop[%s].",priorityQueueTop(s) );
 
    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%s]",s.data[i] ); 

    // ...................................... pop

    priorityQueuePop(s);
 
    printf ( "\ntop[%s].",priorityQueueTop(s) );
 
    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%s]",s.data[i] ); 

    // ...................................... free
    
    priorityQueueFree(s);

    printf ("\n");
 
/**/

    gcStop();
 
    return 0 ;
}





