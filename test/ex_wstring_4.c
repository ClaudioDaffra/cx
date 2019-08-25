
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/type.h"
#include "../lib/string.h"
#include "../lib/mvector.h"
#include <stdio.h>
#include <stdint.h>


/*

    cl  lib\gc.c lib\fs.c lib\string.c test\ex_string_4.c /Fex.exe   /WX  /EHsc 
    gcc lib\gc.c lib\fs.c lib\string.c test\ex_string_4.c -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/string.c test/ex_string_4.c -o x       -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart();

    /**/
 
    // ...................................................... stringType
    
    wprintf ("\n\n --- vector of array of string ; \n");   

    wstringType(s1);
    wstringFromStrC( s1 , "claudio" );    

    wstringType(s2);
    wstringFromStrC( s2 , "daffra" );


    vectorType( string_t , v1 )[2] ;
 
    vectorNew( v1[1] , 128 );

    vectorPushBack( v1[1] , s1 ) ;
    vectorPushBack( v1[1] , s2 ) ;
 
    wprintf ( "\n [%s]",wstr(vectorAt(v1[1],0)) );
    wprintf ( "\n [%s]",wstr(vectorAt(v1[1],1)) );

    /**/

    gcStop();

    printf ("\n");
    return 0 ;
}
    
