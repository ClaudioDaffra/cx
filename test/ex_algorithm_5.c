
#include "../lib/gc.h"
#include "../lib/marray.h"
#include "../lib/malgorithm.h"
#include "../lib/mutility.h"
#include "../lib/miterator.h"
#include <time.h>

/*

    cl  lib\gc.c   lib\fs.c  test\ex_algorithm_5.c /Fex.exe
    gcc lib\gc.c   lib\fs.c  test\ex_algorithm_5.c -o   x.exe
    gcc lib/gc.c   lib/fs.c  test/ex_algorithm_5.c -o   x

*/

 
   
int main ( void )
{
    gcStart() ;

    // .................................... array a1

    printf ( "\n --- arrayType(uint32_t,a1); " );

    arrayType(uint32_t,a1);
    arrayNew( a1 , 16 );
    
    //  ......................................... generate
    
    srand(time(NULL));
    
    algorithm_generate(array,a1,arrayBegin(a1),arrayEnd(a1),rand() % 100 ); 
    
    a1.data[2] = 10 ;
    a1.data[3] = 10 ;
 
    //  ......................................... printf array a1
        
    printf ( "\n --- array a1 : \n" ); 
    for(uint32_t i=0;i<arraySize(a1);i++)   printf ( "[%d]",(uint32_t)a1.data[i] ); 

    //  ......................................... search N
    
    // trovami la posizione iniziale di 10 ripetuti 2 volte
    itArray(a1) ret ;
    algorithm_search_n(array,a1,arrayBegin(a1),arrayEnd(a1),2,10,ret ); 
    
    printf ("\n%p %d\n",ret,*ret );

    //  ......................................... array a2

    printf ( "\n --- arrayType(uint32_t,a2); " );

    arrayType(uint32_t,a2);
    arrayNew( a2 , 16 );

    //  ......................................... Fill
    
    algorithm_fill(array,a2,arrayBegin(a2),arrayEnd(a2),5 ) ;

    printf ( "\n --- array a2 : \n" ); 
    for(uint32_t i=0;i<arraySize(a2);i++)   printf ( "[%d]",(uint32_t)a2.data[i] ); 

    //  ......................................... swap
    
    printf ( "\n --- swap Range : \n" ); 
        

    algorithm_swap_range(array,a1,arrayBegin(a1)+1,arrayEnd(a1)-1,arrayBegin(a2)+1 ) ;

    printf ( "\n --- array a1 : \n" ); 
    for(uint32_t i=0;i<arraySize(a1);i++)   printf ( "[%d]",(uint32_t)a1.data[i] );     
    printf ( "\n --- array a2 : \n" ); 
    for(uint32_t i=0;i<arraySize(a2);i++)   printf ( "[%d]",(uint32_t)a2.data[i] );    

    //  ......................................... swap
    
    printf ( "\n --- swap Iter : \n" ); 

    algorithm_swap_iter(array,a2,arrayBegin(a2)+3,arrayBegin(a2)+5 ) ;
    
    printf ( "\n --- array a2 : \n" ); 
    for(uint32_t i=0;i<arraySize(a2);i++)   printf ( "[%d]",(uint32_t)a2.data[i] ); 
    
    //  ......................................... shuffle

    printf ( "\n --- shuffle: \n" ); 
    
    algorithm_shuffle(array,a2,arrayBegin(a2),arrayEnd(a2) ) ;
    
    printf ( "\n --- array a2 : \n" ); 
    for(uint32_t i=0;i<arraySize(a2);i++)   printf ( "[%d]",(uint32_t)a2.data[i] );    

    //  ......................................... Random shuffle

    printf ( "\n --- Random shuffle: \n" ); 
    
    algorithm_random_shuffle(array,a2,arrayBegin(a2),arrayEnd(a2), rand()%arraySize(a2) ) ;
    
    printf ( "\n --- array a2 : \n" ); 
    for(uint32_t i=0;i<arraySize(a2);i++)   printf ( "[%d]",(uint32_t)a2.data[i] );   
    
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}



/**/


    
