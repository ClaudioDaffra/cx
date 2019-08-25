
/*
    gcc lib\gc.c demo\d_vector_1.c -o x.exe    -Wall -Wextra -pedantic -O3
    gcc lib/gc.c demo/d_vector_1.c -o x        -Wall -Wextra -pedantic -O3
*/

#include "../lib/gc.h"
#include "../lib/mvector.h"

/*
    052 054 055 std::vector
    022 021 021 mvector
    42% faster
*/


int main ( void )
{
    gcStart() ;
    
    vectorType(int,v) ;
    vectorNew(v,128) ;
    
    int ITERATION_MAX       =10 * 1000 * 1000;
    int countErase          = 0 ;
    int i ;

    for ( i=0; i<ITERATION_MAX; i++ )
    {
        vectorPushBack( v , i ) ;       

        if ( ++countErase>10 ) vectorEraseAt(v,0);

        if ( ++countErase>20 ) vectorInsertAtVal(v,0,i);

        if (    ITERATION_MAX > 25 )   countErase = 0 ;  
    }
 
    vectorFree(v) ;
    
    gcStop() ;
    
    return 0 ;
}
