
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/malgorithm.h"
#include "../lib/mutility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
/*

    cl  lib\gc.c  lib\fs.c test\ex_algorithm_4.c /Fex.exe
    gcc lib\gc.c  lib\fs.c test\ex_algorithm_4.c -o   x.exe
    gcc lib/gc.c  lib/fs.c test/ex_algorithm_4.c -o   x

*/

int main ( void )
{
    gcStart() ;

    // .................................... vector

    printf ( "\n --- vectorType(uint32_t,v1); " );

    vectorType(uint32_t,v1);
    vectorNew( v1 , 128 );
    
    vectorPushBack( v1, 1 ) ;
    vectorPushBack( v1, 1 ) ;
    vectorPushBack( v1, 2 ) ;
    vectorPushBack( v1, 3 ) ;
    vectorPushBack( v1, 3 ) ;
    vectorPushBack( v1, 4 ) ;
    vectorPushBack( v1, 4 ) ;
    vectorPushBack( v1, 5 ) ;
    
    //  ......................................... pruint32_t vector v1
        
    printf ( "\n --- vector v1 : \n" ); for(uint32_t i=0;i<vectorSize(v1);i++)   printf ( "[%d]",(uint32_t)v1.data[i] ); 

    //  ......................................... vector v2    
    
    printf ( "\n --- vectorType(uint32_t,v2); \n" );
    vectorType(uint32_t,v2);
    vectorNew( v2 , 128 );

    //  ......................................... unque copy   
    
    algorithm_unique_copy(vector,v1,vectorBegin(v1),vectorEnd(v1),v2 );
    
    printf ( "\n --- unique copy v2 :\n" ); for(uint32_t i=0;i<vectorSize(v2);i++)   printf ( "[%d]",(uint32_t)v2.data[i] ); 
   
    //  ......................................... unique v1
  
    algorithm_unique(vector,v1,vectorBegin(v1),vectorEnd(v1) );
    
    printf ( "\n --- unique v1 : \n" ); for(uint32_t i=0;i<vectorSize(v1);i++)   printf ( "[%d]",(uint32_t)v1.data[i] );  


    //  ......................................... reverse
  
    algorithm_reverse(vector,v1,vectorBegin(v1),vectorEnd(v1) );
    
    printf ( "\n --- reverse v1 : \n" ); for(uint32_t i=0;i<vectorSize(v1);i++)   printf ( "[%d]",(uint32_t)v1.data[i] );  


    //  ......................................... reverse copy
  
    algorithm_reverse_copy(vector,v1,vectorBegin(v1),vectorEnd(v1),v2 );
   
    printf ( "\n --- rev.copy v2 : \n" ); for(uint32_t i=0;i<vectorSize(v2);i++)   printf ( "[%d]",(uint32_t)v2.data[i] );  

     
    //  ......................................... rotate   
    
    vectorClear(v1);
    for (uint32_t i=1; i<10; ++i) vectorPushBack(v1,(uint32_t)i); // 1 2 3 4 5 6 7 8 9

    printf("\n");
    for(uint32_t i=0;i<vectorSize(v1);i++)   printf ( "[%d]",(uint32_t)v1.data[i] );   
            
    algorithm_rotate(vector,v1,vectorBegin(v1),vectorBegin(v1)+3,vectorEnd(v1) );

    printf ( "\n --- rotate // 4 5 6 7 8 9 1 2 3 : \n" ); 
    printf("\n v1 : ");    
    for(uint32_t i=0;i<vectorSize(v1);i++)   printf ( "[%d]",(uint32_t)v1.data[i] );  

    //  ......................................... rotate copy 

    printf("\n\nrotate copy\n");
    
    vectorClear(v1);
    for (uint32_t i=1; i<10; ++i) vectorPushBack(v1,(uint32_t)i); // 1 2 3 4 5 6 7 8 9

    printf("\n v1 : ");
    for(uint32_t i=0;i<vectorSize(v1);i++)   printf ( "[%d]",(uint32_t)v1.data[i] );   

    algorithm_rotate_copy(vector,v1,vectorBegin(v2),vectorBegin(v2)+3,vectorEnd(v2),v2 );

    printf("\n v2 : ");
    for(uint32_t i=0;i<vectorSize(v2);i++)   printf ( "[%d]",(uint32_t)v2.data[i] );  
    
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}



/**/


    
