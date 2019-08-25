
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/mdeque.h"
#include "../lib/marray.h"
#include "../lib/malgorithm.h"
#include "../lib/miterator.h" 
#include <time.h>
#include <stdlib.h> 

/*

    cl  lib\gc.c lib/fs.c lib\malgorithm.c   test\ex_algorithm_10.c /Fex.exe
    gcc lib\gc.c lib/fs.c lib\malgorithm.c   test\ex_algorithm_10.c -o   x.exe
    gcc lib/gc.c lib/fs.c lib/malgorithm.c   test/ex_algorithm_10.c -o   x

*/

int main ( void )
{
    gcStart() ;
 
    const int maxElement=5;
 
    // ................................................................................ vector
 
    vectorType( int,v1  );
    vectorNew ( v1 , maxElement );
    for(int i=0;i<maxElement;i++) vectorPushBack(v1,i);

    vectorType( int,v2  );
    vectorNew ( v2 , maxElement );
    for(int i=0;i<maxElement;i++) vectorPushBack(v2,i*10);

    vectorType( int,v3  );
    vectorNew ( v3 , maxElement*2 );

    algorithm_merge(vector,v3,vectorBegin(v1),vectorEnd(v1),vectorBegin(v2),vectorEnd(v2)  );
    
    puts("");for(int i=0;i<maxElement*2;i++) printf("(%d)",vectorAt(v3,i) ); 
 
    // ................................................................................ deque
 
    dequeType( int,d1  );
    dequeNew ( d1 , maxElement );
    for(int i=0;i<maxElement;i++) dequePushBack(d1,i);

    dequeType( int,d2  );
    dequeNew ( d2 , maxElement );
    for(int i=0;i<maxElement;i++) dequePushBack(d2,i*10);

    dequeType( int,d3  );
    dequeNew ( d3 , maxElement*2 );

    algorithm_merge(deque,d3,dequeBegin(d1),dequeEnd(d1),dequeBegin(d2),dequeEnd(d2)  );
    
    puts("");for(int i=0;i<maxElement*2;i++) printf("(%d)",dequeAt(d3,i) ); 

    // ................................................................................ array
     
    arrayType( int,a1  );
    arrayNew ( a1 , maxElement );
    for(int i=0;i<maxElement;i++) arrayAt(a1,i)=i;

    arrayType( int,a2  );
    arrayNew ( a2 , maxElement );
    for(int i=0;i<maxElement;i++) arrayAt(a2,i)=i*10;

    arrayType( int,a3  );
    arrayNew ( a3 , maxElement*2 );

    algorithm_merge(array,a3,arrayBegin(a1),arrayEnd(a1),arrayBegin(a2),arrayEnd(a2)  );
    
    puts("");for(int i=0;i<maxElement*2;i++) printf("(%d)",arrayAt(a3,i) ); 

    // ................................................................................ includes
    
    int result=-1;
    
    algorithm_includes(array,a3,arrayBegin(a3),arrayEnd(a3),arrayBegin(a2),arrayEnd(a2),result  );
    
    printf("\n a2 is includes in a3 ? %d.\n",result);

    // ................................................................................ clear
    
    vectorClear(v1);
    vectorPushBack(v1, 5);
    vectorPushBack(v1,10);
    vectorPushBack(v1,15);
    vectorPushBack(v1,20);
    vectorPushBack(v1,25); 
    vectorSort(v1,gcCompareInt);    
    puts("");for(int i=0;i<vectorSize(v1);i++) printf("(%d)",vectorAt(v1,i) ); 
    
    vectorClear(v2);    
    vectorPushBack(v2,50);
    vectorPushBack(v2,40);
    vectorPushBack(v2,30);
    vectorPushBack(v2,20);
    vectorPushBack(v2,10); 
    vectorSort(v2,gcCompareInt);    
    puts("");for(int i=0;i<vectorSize(v2);i++) printf("(%d)",vectorAt(v2,i) ); 

    // ................................................................................ set intersection

    vectorClear(v3);
    
    algorithm_set_insersection
    (vector,v3,vectorBegin(v1),vectorEnd(v1),vectorBegin(v2),vectorEnd(v2),vectorBegin(v3)   );    
    
    puts("");for(int i=0;i<vectorSize(v3);i++) printf("(%d)",vectorAt(v3,i) ); 

    // ................................................................................ set difference
    
    vectorClear(v3);
    
    algorithm_set_difference
    (vector,v3,vectorBegin(v1),vectorEnd(v1),vectorBegin(v2),vectorEnd(v2),vectorBegin(v3)   );    
    
    puts("");for(int i=0;i<vectorSize(v3);i++) printf("(%d)",vectorAt(v3,i) );

    // ................................................................................ set symmetric difference

    vectorClear(v3);
    
    algorithm_set_symmetric_difference
    (vector,v3,vectorBegin(v1),vectorEnd(v1),vectorBegin(v2),vectorEnd(v2),vectorBegin(v3)   );    
    
    puts("");for(int i=0;i<vectorSize(v3);i++) printf("(%d)",vectorAt(v3,i) );

    // ................................................................................ set union

    vectorClear(v3);
    
    algorithm_set_union
    (vector,v3,vectorBegin(v1),vectorEnd(v1),vectorBegin(v2),vectorEnd(v2),vectorBegin(v3)   );    
    
    puts("");for(int i=0;i<vectorSize(v3);i++) printf("(%d)",vectorAt(v3,i) );
    
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}

/*
v
*/



/**/


    
