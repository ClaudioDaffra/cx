
#include "../lib/gc.h"
#include "../lib/marray.h"
#include "../lib/malgorithm.h"
#include "../lib/miterator.h" 
#include <time.h>
#include <stdlib.h> 

/*

    cl  lib\gc.c lib\fs.c  lib\malgorithm.c   test\ex_algorithm_8.c /Fex.exe
    gcc lib\gc.c lib\fs.c  lib\malgorithm.c   test\ex_algorithm_8.c -o   x.exe
    gcc lib/gc.c lib/fs.c  lib/malgorithm.c   test/ex_algorithm_8.c -o   x

*/
 
int main ( void )
{
    gcStart() ;

    // .................................... arrayType(char,v1);

    printf ( "\n--- arrayType(char,v1); \n" );

    arrayType( char,v1  );
    arrayNew ( v1 , 16 );
 
    strcpy ( v1.data , "abc" );
    
    arrayType( char,v2  );
    arrayNew ( v2 , 16 );
 
    strcpy ( v2.data , "abc" );
    
    int flag=0;

    // .................................... lexicographical_compare
    
    lexicographical_compare
    (array,v1,arrayBegin(v1),arrayEnd(v1),arrayBegin(v2),arrayEnd(v2),flag );
    
    printf ("\n........ lexicographical_compare=%d.\n",!flag);

    // .................................... next permutation
 
    puts("........ next permutation");
    
    puts( v1.data );
    while ( next_permutation(v1.data) )
    {
        puts( v1.data );
    }
 
    // .................................... prev permutation
     
    puts("........ prev permutation");

    puts( v1.data );
    while ( prev_permutation(v1.data) )
    {
        puts( v1.data );
    }
    
 /**/


 printf("\n");
 gcStop(); 
 return 0 ;
}

/*
    claudio@ubuntu:~/cx$ gcc lib/gc.c lib/malgorithm.c   test/ex_algorithm_8.c -o   x
    claudio@ubuntu:~/cx$ ./x

    --- arrayType(char,v1); 

    ........ lexicographical_compare=1.
    ........ next permutation
    abc
    acb
    bac
    bca
    cab
    cba
    ........ prev permutation
    cba
    cab
    bca
    bac
    acb
    abc

    claudio@ubuntu:~/cx$
*/



/**/


    
