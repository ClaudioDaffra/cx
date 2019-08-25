
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/malgorithm.h"
#include "../lib/mutility.h"
#include <stdio.h>
 
/*

    cl  lib\gc.c  lib\fs.c  test\ex_algorithm_2.c /Fex.exe
    gcc lib\gc.c  lib\fs.c  test\ex_algorithm_2.c -o   x.exe
    gcc lib/gc.c  lib/fs.c  test/ex_algorithm_2.c -o   x

*/
 
int main ( void )
{
    gcStart() ;

    // .................................... vector

    printf ( "\n --- vectorType(float,v1); " );
    vectorType(float,v1);

    printf ( "\n --- vectorNew( v1 , 128 ); " );
    vectorNew( v1 , 128 );

    vectorPushBack( v1, 1.1 ) ;
    vectorPushBack( v1, 2.2 ) ;
    vectorPushBack( v1, 5.5 ) ;    
    vectorPushBack( v1, 3.3 ) ;
    vectorPushBack( v1, 3.3 ) ;    
    vectorPushBack( v1, 4.1 ) ;
    
    printf ( "\n --- vectorType(float,v1); " );
    vectorType(float,v2);

    printf ( "\n --- vectorNew( v1 , 128 ); " );
    vectorNew( v2 , 128 );

    vectorPushBack( v2, 1.1 ) ;
    vectorPushBack( v2, 5.5 ) ;    
    vectorPushBack( v2, 3.3 ) ;    
    vectorPushBack( v2, 4.1 ) ;
    vectorPushBack( v2, 2.2 ) ;
    vectorPushBack( v2, 3.3 ) ;

    //  ......................................... is permutation
    
    printf ( "\n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] ); 

    printf("\n");

    int fPermutation=0;

    algorithm_is_permutation(vector,v1,v2,fPermutation,gcCompareInt);

    printf ( "\n permutation %d.",fPermutation ); 

    //  ......................................... search

    itVector(v1) ret ;
    
    algorithm_search(vector,v1,vectorBegin(v1),vectorEnd(v1),vectorBegin(v1)+1,vectorEnd(v1)-1,ret);
    printf ("\nSearch::{%p}%g",ret,*ret);

    // search N

    //  ......................................... copy

    algorithm_copy(vector,v2,v1);
    
    printf ( "\n#1      \n" ); for(int i=0;i<vectorSize(v1);i++)   printf ( "[%g]",v1.data[i] ); 
    printf ( "\n#2 copy \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] );     

    //  ......................................... copy if
        
    algorithm_copy_if(vector,v2,v1,(*it>1.0&&*it<4.0) ); // copia con condizione

    printf ( "\n#2 copy if \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] );   

    //  ......................................... copy N
    
    algorithm_copy_n(vector,v2,v1,3 ); 

    printf ( "\n#2 copy n \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] );       
    
    //  ......................................... copy backward
    
    algorithm_backward(vector,v2,v1 ); 

    printf ( "\n#2 backward \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] ); 


    //  ......................................... swap range

    //

    //  ......................................... tranform
    
    algorithm_transform(vector,v2,vectorBegin(v2),vectorEnd(v2),*it*=2.0 ); 

    printf ( "\n#2 tranform \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] ); 

    //  ......................................... replace
    
    algorithm_replace(vector,v2,vectorBegin(v2),vectorEnd(v2),6.6,3.1 ); 

    printf ( "\n#2 replace \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] ); 

    //  ......................................... replaceIF
    
    algorithm_replace_if(vector,v2,vectorBegin(v2),vectorEnd(v2),(*it>=3.0&&*it<=3.5),(*it*=2.1) ); 

    printf ( "\n#2 replaceIf \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%g]",v2.data[i] ); 
  

 /**/
 
 printf("\n");
 gcStop(); 
 return 0 ;
}



/**/


