
#include "../lib/miterator.h"
#include "../lib/mvector.h"

/*
    cl  lib\gc.c lib\fs.c  test\ex_iterator_1.c /Fex.exe
    gcc lib\gc.c lib\fs.c  test\ex_iterator_1.c -o   x.exe
    gcc lib/gc.c lib/fs.c  test/ex_iterator_1.c -o   x   
*/

int main ( void )
{
    // .................................... vector

    printf ( "\n --- vectorType(float,v1); " );

    vectorType(float,v1);

    printf ( "\n --- vectorNew( v1 , 128 ); " );

    vectorNew( v1 , 128 );

    vectorPushBack( v1, 1.1 ) ;
    vectorPushBack( v1, 2.2 ) ;
    vectorPushBack( v1, 5.5 ) ;    
    vectorPushBack( v1, 3.3 ) ;
    vectorPushBack( v1, 3.4 ) ;    
    vectorPushBack( v1, 4.0 ) ;
    
    iterator(vector,v1) it ;
 
    printf ( "\n" ); 
    for(it=itBegin(v1);it!=itEnd(v1);itNext(it))
    {
        printf ( "{%g}",*it );
    }
    printf ( "\n" ); 
    for(it=itRBegin(v1);it!=itREnd(v1);itPrev(it))
    {
        printf ( "{%g}",*it );
    }
    printf ( "\n" ); 
    for(it=itBegin(v1);it!=itEnd(v1);itAdvance(it,1))
    {
        printf ( "{%g}",*it );
    }
    
    int dist=0;
    itDistance(vector,v1,itBegin(v1),itEnd(v1),dist);
        
    printf ( "\n distance %d",dist );
    
    printf ( "\n" );
    
 return 0 ;
}