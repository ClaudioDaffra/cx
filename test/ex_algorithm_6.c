
#include "../lib/gc.h"
#include "../lib/mdeque.h"
#include "../lib/malgorithm.h"
#include "../lib/miterator.h" 
#include <time.h>
#include <stdlib.h> 
/*

    cl  lib\gc.c  lib\fs.c  test\ex_algorithm_6.c /Fex.exe
    gcc lib\gc.c  lib\fs.c  test\ex_algorithm_6.c -o   x.exe
    gcc lib/gc.c  lib/fs.c  test/ex_algorithm_6.c -o   x

*/

int main ( void )
{
    gcStart() ;

    // .................................... deque q1

    printf ( "\n --- dequeType(float,q1); " );

    dequeType(float,q1);
    dequeNew( q1 , 16 );

    dequePushBack(q1,1.1);
    dequePushFront(q1,2.2);
    dequePushBack(q1,3.3);
    dequePushFront(q1,4.4);
    dequePushBack(q1,5.5);
    dequePushFront(q1,6.6);
    
    //  ......................................... printf deque q1
        
    printf ( "\n ---  dequeue q1 : \n" ); 
    
    itDeque(q1) itq1;
    
    printf("\n q1 : ");
    for(itq1=dequeBegin(q1);itq1!=dequeEnd(q1);itq1++)   printf ( "[%.3f]",*itq1 );  

    //  ......................................... sort
        
    printf ( "\n ---  sort q1 : \n" ); 
    
    algorithm_sort(deque,q1,dequeBegin(q1),dequeEnd(q1),gcCompareFloat)

    printf("\n q1 : ");   
    for(itq1=dequeBegin(q1);itq1!=dequeEnd(q1);itq1++)   printf ( "[%.3f]",*itq1 );  

    //  ......................................... is sorted ?
    int sorted;

    // .................................... is sorted    
    sorted=0;
    algorithm_is_sorted(deque,q1,dequeBegin(q1),dequeEnd(q1),sorted);
    printf ( "\n\n is sorted %d\n",sorted );;

    //  ......................................... binary search
    
    
    //  ......................................... generate
 
    printf("\n ---  generate\n");  
    
    srand(time(NULL));
    
    algorithm_generate(deque,q1,dequeBegin(q1),dequeEnd(q1),rand() / 12345.6    ) ;

    //  ......................................... Stable sort

    printf("\n ---  Stable sort\n");  
    
    algorithm_stable_sort(deque,q1,dequeBegin(q1),dequeEnd(q1),gcCompareFloatAsInt);
    
    printf("\n q1 : ");   
    for(itq1=dequeBegin(q1);itq1!=dequeEnd(q1);itq1++)   printf ( "[%.3f]",*itq1 );  
 
    //  ......................................... Partial sort

    printf("\n ---  Partial sort\n");  
    
    algorithm_generate(deque,q1,dequeBegin(q1),dequeEnd(q1),rand() / 12345.6    ) ;

    printf("\n q1 : ");  
    for(itq1=dequeBegin(q1);itq1!=dequeEnd(q1);itq1++)   printf ( "[%.3f]",*itq1 );
    
    algorithm_partial_sort(deque,q1,dequeBegin(q1),dequeBegin(q1)+3,dequeEnd(q1),gcCompareFloat);
    
    printf("\n q1 : ");    
    for(itq1=dequeBegin(q1);itq1!=dequeEnd(q1);itq1++)   printf ( "[%.3f]",*itq1 ); 

    // .................................... deque q2

    printf ( "\n\n --- dequeType(float,q2); \n" );

    dequeType(float,q2);
    dequeNew( q2 , 16 );

    algorithm_partial_sort_copy(deque,q1,dequeBegin(q2),dequeBegin(q2)+3,dequeEnd(q2),q2,gcCompareFloat);
    
    printf("\n q2 : ");    
    for(itq1=dequeBegin(q2);itq1!=dequeEnd(q2);itq1++)   printf ( "[%.3f]",*itq1 ); 

    // .................................... is sorted
    sorted=0;
    algorithm_is_sorted(deque,q1,dequeBegin(q1),dequeEnd(q1),sorted);
    printf ( "\n\n is sorted %d\n",sorted );
 
    printf("\n q2 : ");    
    for(itq1=dequeBegin(q2);itq1!=dequeEnd(q2);itq1++)   printf ( "[%.3f]",*itq1 ); 
 
    // .................................... is sorted until
        
    itDeque(q2) itsorted;
    
    algorithm_is_sorted_until(deque,q1,dequeBegin(q1),dequeEnd(q1),itsorted);
    printf ( "\n\n is itsorted %p %.3f\n",itsorted,*itsorted );
 
    printf("\n q2 : ");
    itDeque(q2) itq2;    
    for(itq2=dequeBegin(q2);itq2!=dequeEnd(q2);itq2++)   printf ( "[%.3f]",*itq2 ); 
   
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}



/**/


    
