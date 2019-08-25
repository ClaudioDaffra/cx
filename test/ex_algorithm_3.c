
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include "../lib/malgorithm.h"
#include "../lib/mutility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

    cl  lib\gc.c   lib\fs.c   test\ex_algorithm_3.c /Fex.exe
    gcc lib\gc.c   lib\fs.c   test\ex_algorithm_3.c -o   x.exe
    gcc lib/gc.c   lib/fs.c   test/ex_algorithm_3.c -o   x

*/

int main ( void )
{
    gcStart() ;

    // .................................... vector

    printf ( "\n --- vectorType(char,v1); " );
    vectorType(char,v1);
    vectorNew( v1 , 128 );
    
    vectorPushBack( v1, 'a' ) ;
    vectorPushBack( v1, 'b' ) ;
    vectorPushBack( v1, 'b' ) ;
    vectorPushBack( v1, 'c' ) ;
    vectorPushBack( v1, 'd' ) ;
    vectorPushBack( v1, 'e' ) ;

    printf ( "\n" ); for(int i=0;i<vectorSize(v1);i++)   printf ( "[%c]",v1.data[i] ); 
    
    // .................................... v2
    
    printf ( "\n --- vectorType(char,v2); " );    
    vectorType(char,v2);
    vectorNew( v2 , 64 );
    
    //  ......................................... replace copy
    
    algorithm_replace_copy(vector,v1,vectorBegin(v1),vectorEnd(v1),v2,'b','x' ); 

    printf ( "\n#2 replace copy \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] ); 
  
    //  ......................................... replace copy if
    
    algorithm_replace_copy_if(vector,v1,vectorBegin(v1),vectorEnd(v1),v2,((*it>='a')&&(*it<='c')),(*it+=1) ); 

    printf ( "\n#2 replace copy if\n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] ); 
 
        
    //  ......................................... fill
    
    algorithm_fill(vector,v2,vectorBegin(v2),vectorEnd(v2),'*' ); 

    printf ( "\n#2 fill \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] ); 
 
    //  ......................................... fill
    
    algorithm_fill_n(vector,v2,vectorBegin(v2)+1,'#',2 ); 

    printf ( "\n#2 fill \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] ); 
 

    //  ......................................... remove 
 
    algorithm_remove(vector,v2,vectorBegin(v2),vectorEnd(v2),'#' ); 

    printf ( "\n#2 remove \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] ); 
    
    vectorPushBack(v2,'a');
    vectorPushBack(v2,'b');    
    vectorPushBack(v2,'c');    

    //  ......................................... remove if
 
    algorithm_remove_if(vector,v2,vectorBegin(v2),vectorEnd(v2),( (*it>'a') && (*it< 'c') ) ); 

    printf ( "\n#2 remove if\n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] );     


    //  ......................................... remove copy
 
    algorithm_remove_copy(vector,v2,vectorBegin(v2),vectorEnd(v2),v1,'*' ); 

    printf ( "\n#1 remove copy\n" ); for(int i=0;i<vectorSize(v1);i++)   printf ( "[%c]",v1.data[i] ); 

    //  ......................................... remove copy if
 
    algorithm_remove_copy_if(vector,v2,vectorBegin(v2),vectorEnd(v2),v1,(*it=='c') ); 

    printf ( "\n#1 remove copy if\n" ); for(int i=0;i<vectorSize(v1);i++)   printf ( "[%c]",v1.data[i] ); 
    
    //  ......................................... generate
    srand(time(NULL));
    
    algorithm_generate(vector,v2,vectorBegin(v2),vectorEnd(v2),'a'+rand() % 26 ); 

    printf ( "\n#2 generate \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] ); 
    

    algorithm_generate_n(vector,v2,vectorBegin(v2),'a'+rand() % 26,3 ); 

    printf ( "\n#2 generate N \n" ); for(int i=0;i<vectorSize(v2);i++)   printf ( "[%c]",v2.data[i] ); 
    
    
 /**/
 
 printf("\n");
 gcStop(); 
 return 0 ;
}



/**/


    
