#include "../src/cxx.h"


/*
    1)  clear   ; gcc src/gc.c tst/vector002.c   -o   bin/x      -Wall -Wextra -pedantic
    2)  cls     & cl src\gc.c  tst\vector002.c   /Febin\x.exe    /WX /utf-8 
*/


int main ( void )
{
    gcStart() ;
   
    // .................................... vector typedef
 
    printf ( "--- vectorType(int,v1);\n" );

    // vector_ID_d            :    TYPE
    // vector_ID_s            :    struct vector_ID_s
    // vector_ID_t            :    vector_ID_s
    // vector_ID_p            :    vector_ID_t*
     
    vectorTypeDef(int,v1);
    
    printf ( "vector : data size %zu , struct size %zu , struct size %zu,  struct * size %zu\n"
        ,sizeof(vector_v1_d),sizeof(struct vector_v1_s),sizeof(vector_v1_t),sizeof(vector_v1_p) );

    // .................................... vector new
    
    vector_v1_t    *v1 = new(vector_v1_t);
    
    vectorAlloc(*v1,8) ;

    // .................................... vector size capacity empty
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)    ) ; 

    // .................................... vector push back
    
    printf ( "--- vectorPushBack( *v1 ,10 ) ; \n" );
    
    vectorPushBack( *v1 ,5 ) ;
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)    ) ; 

    printf ( "--- vectorPushBack( v1 ,10 item ) ; \n" );
    
    for(int i=0;i<10;i++) vectorPushBack( *v1 ,i*11 ) ;

    // .................................... vector pop back
    
    printf ( "--- vectorPop( *v1 ) ; \n" );

    vectorPopBack( *v1 ) ;
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)    ) ;  

    // .................................... vector front back at
    
    printf ( "--- vector front %d back %d  at[3]=%d; \n",vectorFront(*v1),vectorBack(*v1),vectorAt(*v1,3) );

    // .................................... iterator
    
    printf ( "--- iterator ; \n" );
    
    for ( itVector(v1) it = vectorBegin(*v1); it<vectorEnd(*v1); it++) 
    {
        printf ( "(%02d)",*it );
    }
    printf ( "\n" );   
    for ( itVector(v1) it = vectorRBegin(*v1); it>vectorREnd(*v1); it--) 
    {
        printf ( "(%02d)",*it );
    }
    printf ( "\n" );   

    // .................................... shrink to fit

    printf ( "--- shrink to fit *v1\n" ) ; 
    vectorShrinkToFit(*v1);
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)    ) ;
        
    // .................................... reserve

    printf ( "--- reserve *v1\n" ) ; 
    vectorReserve(*v1,16);
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)    ) ;

    // .................................... sort
    
    printf ( "--- sort \n" );   
     
    vectorSort(vector_v1_d,*v1,gcCompareInt);

    for ( itVector(v1) it = vectorBegin(*v1); it<vectorEnd(*v1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" ); 

    // .................................... binary search
     
    vector_v1_d key = 88 ;
    vector_v1_d* value = (vector_v1_d*)vectorBinarySearch(vector_v1_d,*v1,gcCompareInt,key ) ;
    if ( value != NULL ) printf ( "found %d in vector.\n" ,key) ; else printf ( "not found %d in vector.\n" ,key);

    // .................................... insert erase eraseN
        
    printf ( "--- insert at 3 34 \n" );  
    vectorInsertAtVal(*v1,3,34); 
        
    printf ( "--- erase at 2 \n" );  
    vectorEraseAt(*v1,2); 

    printf ( "--- erase at 4 n.3 elements \n" );  
    vectorEraseAtN(*v1,4,3);
    
    for ( itVector(v1) it = vectorBegin(*v1); it<vectorEnd(*v1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" );  

    // .................................... resize

    printf ( "--- resize < 5,0\n" );  
    vectorResize(*v1,5,0); 
    printf ( "vector *v1 : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)    ) ;
    for ( itVector(v1) it = vectorBegin(*v1); it<vectorEnd(*v1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" );      

    // .................................... new vector

    printf ( "--- new vector copy append\n" );

    vectorTypeDef(int,v2);

    vector_v1_t    *v2 = new(vector_v2_t);

    vectorAlloc(*v2,8) ; // always allocated first

    vectorCopy( *v2 , *v1 ) ;
    vectorAppend( *v2 , *v1 ) ;
        
    printf ( "vector *v2 : size %zu capacity %zu empty %d.\n",vectorSize(*v2),vectorCapacity(*v2),vectorEmpty(*v2)    ) ; 
    for ( itVector(v2) it = vectorBegin(*v2); it<vectorEnd(*v2); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" );     

    // .................................... insert vector

    printf ( "--- vectorInsertAtVector(*v2,5,v1); \n" );
    
    // *v1 [00][05][34][22][66]
    // *v2 [00][05][34][22][66][00][05][34][22][66] 
    
    // *v2 (00)(05)(34)(22)(66)        (00)(05)(34)(22)(66)    (00)(05)(34)(22)(66)
    
    vectorInsertAtVector(*v2,5,*v1);
    
    vectorPrintf("(%02d)",*v2);
    printf ( "\n" );      

    // *v1 [00][05][34]    V    [22][66]
    // *v2 (00)(05)(34)        (22)(66)(00)(05)(34)    (22)(66)(00)(05)(34)(22)(66)
    // *v1 (00)(05)(34)        (22)(66)(00)(05)(34)    (22)(66)    
    
    vectorInsertAtVectorFromN(*v1, 3, *v2 , 3 , 5 );

    vectorPrintf("(%02d)",*v1);
    printf ( "\n" ); 
                              
    // .................................... dealloc
    
    printf ( "--- dealloc *v1,*v2\n" ) ;   
     
    vectorDealloc(*v1);
    vectorDealloc(*v2);    
    
    // .................................... delete

    printf ( "--- delete v1,v2\n" ) ;  
     
    delete(v1) ;
    delete(v2) ;
                                       
    // .................................... stop
    
    gcStop() ;

    printf ("\n");
    
    return 0 ;
}



/**/
