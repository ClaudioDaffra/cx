
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/type.h"
#include "../lib/string.h"
#include <stdio.h>
#include <stdint.h>

/*

    cl  lib\gc.c lib\fs.c lib\string.c test\ex_string_3.c /Fex.exe   /WX  /EHsc
    gcc lib\gc.c lib\fs.c lib\string.c test\ex_string_3.c -o x.exe   -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/string.c test/ex_string_3.c -o x       -Wall -Wextra -pedantic

*/



int main ( void )
{
    gcStart();

    /**/
 
    // ...................................................... stringType
    
    printf ("\n\n --- stringType(s1); \n");   
    stringType(s1);
    
    // ...................................................... stringFromNumber
    
    stringFromNumber( s1 , $i8() , _i8(123) ) ;

    iterator(s1) its1 ; 
    
    for ( its1=stringBegin(s1);its1!=stringEnd(s1);its1++) printf ( "(%c)",*its1 );    
    printf ( "\nDEBUG [%d] [%s] :: ",(int)strlen(str(s1)),str(s1) );
    for(size_t i=0;i<stringSize(s1);i++) printf ( "(%d)",(int)str(s1)[i] );

    // ...................................................... stringCompare
    
    stringType(s2);
    stringFromStrC(s2,"123");
    printf ( "\n s1==s2 %d.\n",stringCompare ( s1,s2 ) );
    printf ( "\n s1==s2 N %d.\n",stringCompareN ( s1,s2,1 ) );

    // ...................................................... stringLength
    printf ( "\n s1 %d == %d.\n",(int)stringSize(s1),(int)stringLength(s1) );
    
    /**/

    // ...................................................... stringFormat
        
    stringType(s3) ;

    stringFormat ( s3 , "%lf %e %d" , 123.456 , 123.456 , 789 );

    printf ( "\n str [%s/%d]\n",str(s3),(int)strlen(str(s3)) );

    // ...................................................... stringFormat

    stringFormat ( s3 , $i16() , -12 );

    printf ( "\n str [%s/%d]\n",str(s3),(int)strlen(str(s3)) );

    // ...................................................... stringToNumber
    
    stringFromStrC ( s1 , "-123" );
    printf ( "\n -123     -> [%d] ",(int)   stringToInteger (s1,10)   );
    
    stringFromStrC ( s1 , "123" );    
    printf ( "\n  123     -> [%d] ",(int)   stringToUnsigned(s1,10)    );
    
    stringFromStrC ( s1 , "-123.456" );      
    printf ( "\n -123.456 -> [%f] ",(float) stringToReal    (s1)  );

    // ...................................................... string free
    
    stringFree(s1);
//    stringFree(s2);
    stringFree(s3);
    
    /**/

    gcStop();

    printf ("\n");
    return 0 ;
}
    
