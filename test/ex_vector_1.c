
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/*
   cl  lib\gc.c lib\fs.c test\ex_vector_1.c      /Fex.exe    /EHsc /WX
   gcc lib\gc.c lib\fs.c test\ex_vector_1.c -o   x.exe       -Wall -Wextra -pedantic
   gcc lib/gc.c lib\fs.c test/ex_vector_1.c -o   x           -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart() ;
    
    // .................................... vector
 
    printf ( "\n --- vectorType(int,v1); " );
  
    vectorType(int,v1);

    printf ( "\n --- vectorNew( v1 , 128 ); " );

    vectorNew( v1 , 128 );

    printf ( "\n --- vectorPushBack( v1 ,10 ) ; " );
    
    vectorPushBack( v1 ,10 ) ;
    
    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );    
    printf ( "\nv1 :: vector at vectorAt(v1,0):=%d.", vectorAt(v1,0) ); // 10
    
    // .................................... vector of vector
 
    printf ( "\n --- vectorType(vector_v1,v2); " );

    vectorType(vector_v1,v2);

    printf ( "\n --- vectorNew( v2 , 64 ); " );

    vectorNew( v2 , 64 );

    printf ( "\n --- vectorPushBack( v2 ,v1 ); " );

    vectorPushBack( v2 ,v1 ) ;
    
    printf ( "\nv2 :: size %d capacity %d.", (int)vectorSize(v2) , (int)vectorCapacity(v2) );   

    printf ( "\n --- vectorAt(vectorAt(v2,0),0)) " ) ;
    
    printf ( "\nv2 :: vectorAt(vectorAt(v2,0),0)):=%d.", vectorAt(vectorAt(v2,0),0)    );  // 10
    printf ( "\nv2 :: vectorAt(vectorAt(v2,0),0)):=%d.", vectorXY(v2,0,0)              );  // 10
 
    // .................................... array of vector 

    printf ( "\n --- vectorType(int,v3)[10]; " ) ;
 
    vectorType(int,v3)[10];    

    printf ( "\n --- vectorNew( v3[2] , 64 ); " ) ;

    vectorNew( v3[2] , 64 );

    printf ( "\n --- vectorPushBack( v3[2] ,123 ) ;" ) ;
    printf ( "\n --- vectorPushBack( v3[2] ,456 ) ;" ) ;
 
    vectorPushBack( v3[2] ,123 ) ;
    vectorPushBack( v3[2] ,456 ) ;
    
    printf ( "\nv3[2] :: size %d capacity %d.", (int)vectorSize(v3[2]) , (int)vectorCapacity(v3[2]) );   
    
    printf ( "\nv3[2] :: vectorAt(v3[2],0):=%d.", vectorAt(v3[2],0) );  // 123
    printf ( "\nv3[2] :: vectorAt(v3[2],1):=%d.", vectorAt(v3[2],1) );  // 456    

    // .................................... front back 

    printf ( "\n --- vectorFront(v3[2]);" ) ;
    printf ( "\n --- vectorBack(v3[2]);" ) ;

    printf ( "\nv3[2] :: vectorFront(v3[2]) :=%d."  , vectorFront(v3[2]) );  // 123
    printf ( "\nv3[2] :: vectorBack(v3[2])  :=%d."  , vectorBack (v3[2]) );  // 456    

    // .................................... clear

    printf ( "\n --- vectorClear(v1) ;" ) ;
    
    vectorClear(v1) ;
    
    // .................................... iterator
   
    for ( int i=0; i<10 ; i++)
    {
        vectorPushBack( v1, i*2 ) ;
    }

    printf ( "\n --- itVector(v1) itv1 ;" ) ;
    
    itVector(v1) itv1 ;
    
    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ;

    printf ( "\n" );
    for( itv1 = vectorRBegin(v1) ; itv1 != vectorREnd(v1); itv1-- ) printf ( "[%d]" ,*itv1 ) ;

    // .................................... shrink to fit

    printf ( "\n --- vectorShrinkToFit(v1);" ) ;
    
    vectorShrinkToFit(v1);

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );      

    // .................................... shrink to fit

    printf ( "\n --- vectorReserve(v1,16);" ) ;
    
    vectorReserve(v1,16);

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) ); 

    // .................................... insert At

    printf ( "\n --- vectorInsertAtVal(v1,3,12);" ) ;
  
    vectorInsertAtVal(v1,3,123);  
 
    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
    
    // .................................... erase At 

    printf ( "\n --- vectorEraseAt(v1,4);" ) ;
    
    vectorEraseAt(v1,4);

    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 

    // .................................... erase At N

    printf ( "\n --- vectorEraseAtN(v1,4,2);" ) ;
    
    vectorEraseAtN(v1,4,2);

    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 

    // .................................... erase At N

    printf ( "\n --- vectorResize(v1,16,0);" ) ;
    
    vectorResize(v1,16,0);

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );
    printf ( "\n" );    
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 

    // .................................... copy
     
    vectorCopy ( v3[2] , v1 ) ;
    
    printf ( "\n" ); 
    //for( unsigned int i=0; i<vectorSize(v3[2]) ; i++  )   printf ( "[%d]" ,v3[2].data[i] ) ; 
    for( unsigned int i=0; i<vectorSize(v3[2]) ; i++  )   printf ( "[%d]" ,vectorAt(v3[2],i) ) ; 

    // .................................... Append

    printf ( "\n --- vectorType(int,v4);" ) ;

    vectorType(int,v4);

    vectorNew( v4 , 128 );
    
    vectorAppend( v4,v1 ) ;
  
    itVector(v4) itv4; // vectorDataType ## ID* ... vectorDataTypev4 *itv4
    
    printf ( "\nv4 :: size %d capacity %d.", (int)vectorSize(v4) , (int)vectorCapacity(v4) );
    printf ( "\n" );    
    for( itv4 = vectorBegin(v4) ; itv4 != vectorEnd(v4); itv4++ )   printf ( "[%d]" ,*itv4 ) ; 
  
    // .................................... insert at vector

    printf ( "\n --- vectorInsertAtVector(v1, 2, v4 ) ;" ) ;
 
    vectorInsertAtVector(v1, 2, v4 ) ; 

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );
    printf ( "\n" );    
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
 
    // .................................... insert at vector from and for

    printf ( "\n --- vectorInsertAtVectorFromN(v1, 2, v4 ,2, 2) ;" ) ;
    
    vectorInsertAtVectorFromN(v1, 2, v4 ,2, 2) ;

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );
    printf ( "\n" );    
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
 
    // .................................... sort
    
    vectorSort(v1,gcCompareInt);

    printf ( "\n sort \n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
    
    // .................................... free

    printf ( "\n --- vectorFree( ... ) ;" ) ;

    vectorFree( v1 ) ;
    vectorFree( v2 ) ;    
    vectorFree( v3[2] ) ;   
    //vectorFree( v4 ) ;  

    /**/

    gcStop() ;

    printf ("\n");
    

 return 0 ;
}

/*
    claudio@ubuntu:~/cx$ valgrind --leak-check=full ./x
    ==30088== Memcheck, a memory error detector
    ==30088== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==30088== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==30088== Command: ./x
    ==30088== 

    ...

    ==30088== 
    ==30088== HEAP SUMMARY:
    ==30088==     in use at exit: 0 bytes in 0 blocks
    ==30088==   total heap usage: 17 allocs, 17 frees, 3,216 bytes allocated
    ==30088== 
    ==30088== All heap blocks were freed -- no leaks are possible
    ==30088== 
    ==30088== For counts of detected and suppressed errors, rerun with: -v
    ==30088== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/



/**/



