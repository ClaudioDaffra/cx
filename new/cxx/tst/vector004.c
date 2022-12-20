#include "../src/cxx.h"



/*
    1)  clear   ; gcc src/gc.c tst/vector004.c  -o   bin/x      -Wall -Wextra -pedantic

    2)  cls     & cl src\gc.c tst\vector004.c   /Febin\x.exe    /WX /utf-8  
*/


int main ( void )
{
    gcStart() ;
   
    // .................................... vector typedef 
 
    printf ( "--- vectorType(int,v1); \n" );

    // vector_ID_d            :    TYPE
    // vector_ID_s            :    struct vector_ID_s
    // vector_ID_t            :    vector_ID_s
    // vector_ID_p            :    vector_ID_t*
     
    vectorTypeDef(char*,v1);
    
    printf ( "vector : data size %zu , struct size %zu , struct size %zu,  struct * size %zu\n"
        ,sizeof(vector_v1_d),sizeof(struct vector_v1_s),sizeof(vector_v1_t),sizeof(vector_v1_p) );

    // .................................... vector new
    
    vector_v1_t    v1 ;
    
    vectorAlloc(v1,8) ;

    // .................................... vector size capacity empty
    
    printf ( "\nvector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)    ) ; 
           
    // .................................... vector push back
    
    printf ( "--- vectorPushBack( v1 ,10 ) ; \n" );
    
    //vectorPushBack( v1 ,5) ;

    // .................................... vector push
    
     
    vectorPushBack( v1 , gcStrDup( "claudio" )  );
    vectorPushBack( v1 , gcStrDup( "daffra" )   );
    vectorPushBack( v1 , gcStrDup( "barbara" )  );
    vectorPushBack( v1 , gcStrDup( "marisa" )   );
    vectorPushBack( v1 , gcStrDup( "lorenzo" )  );
    vectorPushBack( v1 , gcStrDup( "enzo" )     );

    printf ( "\nvector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)    ) ;

    // .................................... sort
  
    printf ( "--- sort \n" );   
     
    vectorSort(vector_v1_d,v1,gcCompareStrC);

    for ( itVector(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++)   printf ( "[%s]" ,*it ) ; 
    printf ( "\n" ); 

    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
    return 0 ;
}



/**/
