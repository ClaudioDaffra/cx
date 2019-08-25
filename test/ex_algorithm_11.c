
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/mdeque.h"
#include "../lib/marray.h"
#include "../lib/malgorithm.h"
#include "../lib/miterator.h" 
#include <time.h>
#include <stdlib.h> 

/*

    cl  lib\gc.c lib/fs.c lib\malgorithm.c   test\ex_algorithm_11.c /Fex.exe
    gcc lib\gc.c lib/fs.c lib\malgorithm.c   test\ex_algorithm_11.c -o   x.exe
    gcc lib/gc.c lib/fs.c lib/malgorithm.c   test/ex_algorithm_11.c -o   x

*/
    
int main ( void )
{
    gcStart() ;
 
    const int maxElement=10;
 
    // ................................................................................ partion / is_partitioned

    vectorType( int,v1  );
    vectorNew ( v1 , maxElement );
    
    iterator(vector,v1) point;    
    int flag=-1;    
    
    for(int i=1;i<maxElement;i++) vectorPushBack(v1,i); // 1 2 3 4 5 6 7 8 9
    puts("");for(int i=0;i<vectorSize(v1);i++) printf("(%d)",vectorAt(v1,i) ); 

    algorithm_is_partitioned(vector,v1,vectorBegin(v1),vectorEnd(v1),((*it%2)==1),flag ) ;
    printf("\n is partitioned ? %d.\n",flag);

    // ................................................................................ partion point
    
    algorithm_partition_point(vector,v1,vectorBegin(v1),vectorEnd(v1),((*it%2)==1),point ) ;
    if ( point!=vectorEnd(v1) ) printf("\n last partioned element ? %p %d.\n",point,*point);
  
    algorithm_partition(vector,v1,vectorBegin(v1),vectorEnd(v1),((*it%2)==1) ) ;

    puts("");for(int i=0;i<vectorSize(v1);i++) printf("(%d)",vectorAt(v1,i) ); 

    algorithm_is_partitioned(vector,v1,vectorBegin(v1),vectorEnd(v1),((*it%2)==1),flag ) ;
    printf("\n is partitioned ? %d.\n",flag);
 
    algorithm_partition_point(vector,v1,vectorBegin(v1),vectorEnd(v1),((*it%2)==1),point ) ;
    if ( point!=vectorEnd(v1) ) printf("\n last partioned element ? %p %d.\n",point,*point);

    // ................................................................................ partion copy

    vectorType( int,v2  );
    vectorNew ( v2 , maxElement );
    
    vectorType( int,v3  );
    vectorNew ( v3 , maxElement );
    
    algorithm_partition_copy(vector,v1,vectorBegin(v1),vectorEnd(v1),v2,v3,((*it%2)==1) ) ;    

    puts("\n v2 \n");for(int i=0;i<vectorSize(v2);i++) printf("(%d)",vectorAt(v2,i) ); 

    puts("\n v3 \n");for(int i=0;i<vectorSize(v3);i++) printf("(%d)",vectorAt(v3,i) ); 
    
    
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}

/*
v
*/



/**/


    
