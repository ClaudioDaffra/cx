
#include "../lib/gc.h"
#include "../lib/mpriorityQueue.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*

    cl  lib\gc.c lib\fs.c  test\ex_priorityQueue_1.c    /Fex.exe   /WX  /EHsc 
    gcc lib\gc.c lib\fs.c  test\ex_priorityQueue_1.c    -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c  test/ex_priorityQueue_1.c    -o x       -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart() ;

/**/

    priorityQueueType(int,s) ; //

    s.compare = gcCompareInt ;
 
    priorityQueueNew(s,128) ; // 
 
    // ...................................... push
 
    printf ( "\nempty?%d\n",priorityQueueEmpty(s) );
    
    priorityQueuePush ( s , 7 ) ;

    printf ( "\ntop[%d].",priorityQueueTop(s) );

    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%d]",s.data[i] ); 

    // ...................................... push

    priorityQueuePush ( s , 2 ) ;    

    printf ( "\ntop[%d].",priorityQueueTop(s) );

    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%d]",s.data[i] ); 

    // ...................................... push

    priorityQueuePush ( s , 8 ) ;
   
    printf ( "\ntop[%d].",priorityQueueTop(s) );
 
    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%d]",s.data[i] ); 

    // ...................................... push

    priorityQueuePush ( s , 80 ) ;

    printf ( "\ntop[%d].",priorityQueueTop(s) );
 
    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%d]",s.data[i] ); 

    // ...................................... pop

    priorityQueuePop(s);
 
    printf ( "\ntop[%d].",priorityQueueTop(s) );
 
    for(int i=0;i<priorityQueueSize(s);i++) printf ( "[%d]",s.data[i] ); 

    // ...................................... free
    
    priorityQueueFree(s);

    printf ("\n");
 
/**/

    gcStop();
 
    return 0 ;
}





