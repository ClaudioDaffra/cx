
#include "../src/cxx.h"

/*
    1)  clear   ; gcc src/gc.c tst/array001.c             -o   bin/x        -Wall -Wextra -pedantic
    2)  cls     & cl  src\gc.c tst\array001.c           /Febin\x.exe        /WX /utf-8
*/


int main ( void )
{
    gcStart() ;
 
    // .................................... array typedef 
 
    printf ( "--- arrayType(int,a1); \n" );

    // array_ID_d            :    TYPE
    // array_ID_s            :    struct array_ID_s
    // array_ID_t            :    array_ID_s
    // array_ID_p            :    array_ID_t*
     
    arrayTypeDef(int,a1);
    
    printf ( "array : data size %zu , struct size %zu , struct size %zu,  struct * size %zu\n"
        ,sizeof(array_a1_d),sizeof(struct array_a1_s),sizeof(array_a1_t),sizeof(array_a1_p) );

    // .................................... array new
    
    array_a1_t    a1 ;
    
    arrayAlloc(a1,8) ;
 
    // .................................... array size capacity empty
    
    printf ( "array : size %zu empty %d.\n",arraySize(a1),arrayEmpty(a1)    ) ; 

    // .................................... iterator
    
    printf ( "--- iterator ; \n" );
    
    static int cont=0;
    for ( itArray(a1) it = arrayBegin(a1); it<arrayEnd(a1); it++) 
    {
        *it=++cont;
        printf ( "(%02d)",*it );
    }
    printf ( "\n" );
    
    for ( itArray(a1) it = arrayRBegin(a1); it>arrayREnd(a1); it--) 
    {
        printf ( "(%02d)",*it );
    }
    printf ( "\n" );   

    // .................................... array front back at
    
    printf ( "--- array front %d back %d  at[3]=%d; \n",arrayFront(a1),arrayBack(a1),arrayGetAt(a1,3) );

    // .................................... sort
  
    arraySetAt(a1,3)=21;

    printf ( "--- sort \n" );   
     
    arraySort(array_a1_d,a1,gcCompareInt);

    for ( itArray(a1) it = arrayBegin(a1); it<arrayEnd(a1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" ); 

    // .................................... binary search
    
    array_a1_d key = 80 ;
    array_a1_d* value = (array_a1_d*)arrayBinarySearch(array_a1_d,a1,gcCompareInt,key ) ;
    
    if ( value != NULL ) printf ( "found %d in array.\n" ,key) ; 
    else printf ( "not found %d in array.\n" ,key);
 
    // .................................... array Fill/printf
    
    arrayTypeDef(int,b1);

    array_b1_t    b1 ;
    
    arrayAlloc(b1,16) ;
    
    arrayFill(b1,3) ;
    
    arrayPrintf("%d",b1);

    // .................................... array copy
    
    printf ( "\n array copy " );
    
    arrayCopy(a1,b1);
    
    printf ( "\n printf a1  " );
    
    arrayPrintf("%d",a1);
    
    printf ( "\n" );

    // .................................... dealloc
    
    printf ( "--- dealloc a1\n" ) ;
    arrayDealloc(a1);

    // .................................... stop

    gcStop() ;

    printf ("\n");
    
    return 0 ;
}



/**/
