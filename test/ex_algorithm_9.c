
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/malgorithm.h"

#include "../lib/mutility.h"

#include <stdlib.h> 

/*

    cl  lib\gc.c lib\fs.c lib\malgorithm.c   test\ex_algorithm_9.c /Fex.exe
    gcc lib\gc.c lib\fs.c lib\malgorithm.c   test\ex_algorithm_9.c -o   x.exe
    gcc lib/gc.c lib/fs.c lib/malgorithm.c   test/ex_algorithm_9.c -o   x

*/

    
int main ( void )
{
    gcStart() ;

    // .................................... vectorType(int,v1);

    printf ( "\n--- vectorType( int,v1  ); \n" );

    int myints[] = {10,20,30,5,15};

    vectorType( int,v1  );
    vectorNew ( v1 , 16 );

    for ( int i =0;i<5;i++) vectorPushBack( v1,myints[i] );
 
    printf ("\n");  for ( int i =0;i<vectorSize(v1);i++) printf ("(%d)",vectorAt(v1,i) );

    // .................................... make heap
    
    make_heap(vector,v1,vectorBegin(v1),vectorEnd(v1));

    printf ("\n");  for ( int i =0;i<vectorSize(v1);i++) printf ("(%d)",vectorAt(v1,i) );

    // .................................... is heap ?
    
    int flag=0;
    
    is_heap( vector,v1,vectorBegin(v1),vectorEnd(v1),flag);
    
    printf ( "\n is heap ? %d.",flag );
    
    // .................................... pop heap
          
    pop_heap(vector,v1, vectorBegin(v1),vectorEnd(v1) );

    printf ("\n");  for ( int i =0;i<vectorSize(v1);i++) printf ("(%d)",vectorAt(v1,i) );

    // .................................... push heap
              
    push_heap(vector,v1, vectorBegin(v1),vectorEnd(v1),99 );

    printf ("\n");  for ( int i =0;i<vectorSize(v1);i++) printf ("(%d)",vectorAt(v1,i) );

    // .................................... sort heap
          
    sort_heap(vector,v1, vectorBegin(v1),vectorEnd(v1),gcCompareInt );

    printf ("\n");  for ( int i =0;i<vectorSize(v1);i++) printf ("(%d)",vectorAt(v1,i) );

    // .................................... is heap until
           
    iterator(vector,v1) it;
    
    algorithm_shuffle(vector,v1,vectorBegin(v1),vectorEnd(v1));
    
    printf ("\n");  for ( int i =0;i<vectorSize(v1);i++) printf ("(%d)",vectorAt(v1,i) );
    
    is_heap_until(vector,v1, vectorBegin(v1),vectorEnd(v1),it ); 
    
    size_t dist ;

    itDistance ( vector,v1,vectorBegin(v1),it,dist);
    
    printf ( "\nis heap until : %d %d",(int)dist,*it );  


    // .................................... is heap ?

    is_heap( vector,v1,vectorBegin(v1),vectorEnd(v1),flag);
    
    printf ( "\n is heap ? %d.",flag );
          
          
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}

/*
 
*/



/**/


    
