
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/malgorithm.h"
#include "../lib/miterator.h" 
#include <time.h>
#include <stdlib.h> 

/*

    cl  lib\gc.c   lib\fs.c  test\ex_algorithm_7.c /Fex.exe
    gcc lib\gc.c   lib\fs.c  test\ex_algorithm_7.c -o   x.exe
    gcc lib/gc.c   lib/fs.c  test/ex_algorithm_7.c -o   x

*/

int main ( void )
{
    gcStart() ;

    // .................................... deque q1

    printf ( "\n --- vectorType(int,v1); " );

    vectorType( int,v1  );
    vectorNew ( v1 , 16 );

    //               0   1   2   3   4   5   6   7
    int myints[] = {10 ,20, 30, 30, 20, 10, 10, 20};
    
    for(int i=0;i<8;i++) vectorPushBack(v1,myints[i]);

    printf ( "\n v1 : " ); for(int i=0;i<vectorSize(v1);i++)   printf ( "[%d]",v1.data[i] ); 
    
    itVector(v1) itpos ;
    int dist=0;  

    // .................................... lower bound
    
    algorithm_lower_bound(vector,v1,vectorBegin(v1),vectorEnd(v1),20,itpos);
    itDistance(vector,v1,vectorBegin(v1),itpos,dist);
    printf ( "\n lower bound %p %d pos (%d)=1.",itpos,*itpos,dist );

    // .................................... upper bound
    
    algorithm_upper_bound(vector,v1,vectorBegin(v1),vectorEnd(v1),20,itpos);
    itDistance(vector,v1,itpos,vectorEnd(v1),dist);
    printf ( "\n upper bound %p %d pos (%d)=7.",itpos,*(itpos),dist );

    // .................................... equal range

    int from,to;
    algorithm_equal_range(vector,v1,vectorBegin(v1),vectorEnd(v1),20,from,to);
    printf ( "\n equal range from %d to %d ",from,to ); 
 
    // .................................... sort

    algorithm_sort(vector,v1,vectorBegin(v1),vectorEnd(v1),gcCompareInt);

    printf ( "\n v1 : " ); for(int i=0;i<vectorSize(v1);i++)   printf ( "[%d]",v1.data[i] ); 
       
       
    int flag=0;

    // .................................... binary search
    
    algorithm_binary_search(vector,v1,vectorBegin(v1),vectorEnd(v1),30,flag);
    printf ( "\n found 30 ? %d: ",flag );     

    algorithm_binary_search(vector,v1,vectorBegin(v1),vectorEnd(v1),45,flag);
    printf ( "\n found 45 ? %d: ",flag );     

    
    int min,max;
    
    
    printf ("\n range \n");
    
        algorithm_minmax_element(vector,v1,vectorBegin(v1),vectorEnd(v1),min,max);
        printf ("\n min %d , max %d",min,max);
        
        algorithm_min_element(vector,v1,vectorBegin(v1),vectorEnd(v1),min);
        printf ("\n min %d",min);  

        algorithm_max_element(vector,v1,vectorBegin(v1),vectorEnd(v1),max);
        printf ("\n max %d",max);  

    printf ("\n\n object \n");
    
        algorithm_minmax(vector,v1,min,max);
        printf ("\n min %d , max %d",min,max);  

        algorithm_min(vector,v1,min);
        printf ("\n min %d",min); 

        algorithm_max(vector,v1,max);
        printf ("\n max %d",max); 
        
    
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}



/**/


    
