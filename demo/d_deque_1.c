
/*
    gcc lib\gc.c demo\d_deque_1.c -o x.exe    -Wall -Wextra -pedantic -O3
    gcc lib/gc.c demo/d_deque_1.c -o x        -Wall -Wextra -pedantic -O3
*/

#include "../lib/gc.h"
#include "../lib/mdeque.h"

/*
    029 029 029 std::deque
    025 023 024 mdeque
    20% faster
*/


int main ( void )
{
    gcStart() ;
    
    dequeType(int,v) ;
    dequeNew(v,128) ;
    
    int ITERATION_MAX       =10 * 1000 * 1000;
    int countErase          = 0 ;
    int i ;

    for ( i=0; i<ITERATION_MAX; i++ )
    {
        dequePushBack( v , i ) ;       

        if ( ++countErase>10 ) dequePushFront(v,0);

        if ( ++countErase>20 ) dequeInsertAtVal(v,0,i);

        if ( ++countErase>30 )  dequePopBack(v);

        if ( ++countErase>40 )  dequePopFront(v);

        if (    ITERATION_MAX > 50 )   countErase = 0 ;  
    }
 
    dequeFree(v) ;
    
    gcStop() ;
    
    return 0 ;
}



/**/





