
#include "../lib/gc.h"
#include "../lib/type.h"
#include "../lib/stdio.h"
#include "../lib/wstring.h"
#include <stdio.h>
#include <stdint.h> 

/*

    cl  lib\gc.c lib\fs.c lib\wstring.c test\ex_wstring_3.c /Fex.exe /WX    /EHsc 
    gcc lib\gc.c lib\fs.c lib\wstring.c test\ex_wstring_3.c -o x.exe -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/wstring.c test/ex_wstring_3.c -o x     -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart();

    /**/
 
    // ...................................................... wstringType
    
    wprintf (L"\n\n --- stringType(s1); \n");   
    wstringType(s1);
    
    // ...................................................... wstringFromNumber
    
    wstringFromNumber( s1 , $i8() , _i8(123) ) ;
    
    iterator(s1) its1 ;  
 
    for ( its1=wstringBegin(s1);its1!=wstringEnd(s1);its1++) wprintf ( L"(%c)",*its1 );    
    wprintf ( L"\nDEBUG [%d] [%ls] :: ",(int)wcslen(wstr(s1)),wstr(s1) );
    for(size_t i=0;i<wstringSize(s1);i++) wprintf ( L"(%d)",(int)wstr(s1)[i] );
    
    // ...................................................... stringCompare
    
    wstringType(s2);
    wstringFromStrC(s2,L"123");
    wprintf ( L"\n s1==s2 %d.\n",wstringCompare ( s1,s2 ) );
    wprintf ( L"\n s1==s2 N %d.\n",wstringCompareN ( s1,s2,1 ) ); 

    // ...................................................... stringLength
    wprintf ( L"\n s1 %d == %d.\n",wstringSize(s1),wstringLength(s1) );
   
    // ...................................................... stringFormat
        
    wstringType(s3) ;

    wstringFormat ( s3 , L"%lf %e %d" , 123.456 , 123.456 , 789 );

    wprintf ( L"\n wstr [%ls/%d]\n",wstr(s3),(int)wcslen(wstr(s3)) );

    // ...................................................... stringFormat

    wstringFormat ( s3 , $i64() , _i64(-12) );

    wprintf ( L"\n wstr [%ls/%d]\n",wstr(s3),(int)wcslen(wstr(s3)) );    

    // ...................................................... stringToNumber
    
    wstringFromStrC ( s1 , L"-123" );
    wprintf ( L"\n wstr = -123     -> [%d] ",(int)   wstringToInteger (s1,10)   );
    
    wstringFromStrC ( s1 , L"123" );    
    wprintf ( L"\n wstr = 123     -> [%d] " ,(int)   wstringToUnsigned(s1,10)   );
    
    wstringFromStrC ( s1 , L"-123.456" );      
    wprintf ( L"\n wstr = -123.456 -> [%f] ",(float) wstringToReal    (s1)      );

    // ...................................................... string free
    
    wstringFree(s1);
//    wstringFree(s2);
    wstringFree(s3);
    
    /**/

    gcStop();

    wprintf (L"\n");
    return 0 ;
}
    
