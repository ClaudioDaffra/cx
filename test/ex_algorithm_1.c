
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/malgorithm.h"
#include "../lib/mutility.h"
#include <stdio.h>
 

/*

    cl  lib\gc.c lib\fs.c test\ex_algorithm_1.c /Fex.exe
    gcc lib\gc.c lib\fs.c test\ex_algorithm_1.c -o   x.exe
    gcc lib/gc.c lib/fs.c test/ex_algorithm_1.c -o   x

*/
 
int main ( void )
{
    gcStart() ;

    // .................................... vector

    printf ( "\n --- vectorType(int,v1); " );

    vectorType(int,v1);

    printf ( "\n --- vectorNew( v1 , 128 ); " );

    vectorNew( v1 , 128 );

    printf ("\n");

    vectorPushBack( v1, 1 ) ;
    vectorPushBack( v1, 2 ) ;
    vectorPushBack( v1, 5 ) ;    
    vectorPushBack( v1, 3 ) ;
    vectorPushBack( v1, 3 ) ;    
    vectorPushBack( v1, 4 ) ;

    //
    itVector(v1) vi;     
    int flag=0;

    algorithm_all_of(vector,v1,vectorBegin(v1),vectorEnd(v1) , *it % 2 == 0  ,&flag  );
                    printf("\nAllOf [%d]",flag); // all are % of 2
    
    algorithm_any_of(vector,v1,vectorBegin(v1),vectorEnd(v1) , *it == 3      ,&flag  );
                    printf("\nAnyOf [%d]",flag); // al least one is 3

    algorithm_none_of(vector,v1,vectorBegin(v1),vectorEnd(v1) , *it < 0      ,&flag  );
                    printf("\nNoneOf [%d]",flag); // no negative number
 
    itVector(v1) found=NULL;
    
    //
    
    algorithm_find(vector,v1,vectorBegin(v1),vectorEnd(v1)   ,      3       , found );
                    printf("\nFind [%p %d]",found,*found); // value found at *it 
 
    algorithm_find_if(vector,v1,vectorBegin(v1),vectorEnd(v1) ,  (*it%2)==1   ,found );
                    printf("\nFindIf first odd value is [%d]",*found); // first odd value is 

    algorithm_find_if_not(vector,v1,vectorBegin(v1),vectorEnd(v1) ,  (*it%2)==1   ,found );
                    printf("\nFindIfNot first even value is [%d]",*found); // first even value is 
  
    algorithm_find_end(vector,v1,vectorBegin(v1),vectorEnd(v1),vectorBegin(v1)+1,vectorEnd(v1)-1,found);
                    printf ( "\nFindEnd %p %d",found,*found );
  
    algorithm_find_first_of(vector,v1,vectorBegin(v1),vectorEnd(v1),vectorBegin(v1)+1,vectorEnd(v1)-1,found);
                    if ( found == vectorEnd(v1) )
                    {
                        printf ( "\nFindFirstOf found nothing" );
                    }
                    else
                    {
                        printf ( "\nFindFirstOf %p %d",found,*found );
                    }
    // 125334
    algorithm_adjacent_find(vector,v1,vectorBegin(v1),vectorEnd(v1),found);
                    printf ( "\nAdjacentFind %p %d %d",found,*found,*(found+1) );

    int count=0;
    algorithm_count(vector,v1,vectorBegin(v1),vectorEnd(v1),3,count);
                    printf ( "\nCount num : %d .",count );

    int result=0;
    algorithm_count_if(vector,v1,vectorBegin(v1),vectorEnd(v1),(*it%2)==1,result);
                    printf ( "\nCountIf dispari : %d .",result );

    
    algorithm_equal(vector,v1,vectorBegin(v1),vectorEnd(v1),vectorBegin(v1)+3,vectorEnd(v1)+4,result);
                    printf ( "\nEqual true/false : %d .",result );


    // 125334   ----34  
    
    pairType(int,int,p);
    
    algorithm_mismatch(vector,v1,vectorBegin(v1),vectorEnd(v1),vectorBegin(v1)+3,p);
                    printf ( "\nMismatch %d %d.",p.first,p.second );
                    
    //
    
 /**/
 
 printf("\n");
 gcStop(); 
 return 0 ;
}



/**/


