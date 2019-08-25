
#include "../lib/gc.h"
#include "../lib/wstring.h"
#include <stdio.h>
#include <wchar.h>
#include <stdint.h>


/*

    cl  lib\gc.c lib\fs.c lib\wstring.c test\ex_wstring_2.c /Fex.exe /WX    /EHsc   
    gcc lib\gc.c lib\fs.c lib\wstring.c test\ex_wstring_2.c -o x.exe -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/wstring.c test/ex_wstring_2.c -o x     -Wall -Wextra -pedantic

*/


int main ( void )
{
    gcStart();

    /**/

    // no more memory leak #1 , check with valgrind.

    wchar_t* temp2=gcMalloc( sizeof(wchar_t)*10 );
    wchar_t* temp3=gcMalloc( sizeof(wchar_t)*10 );
    wcscpy ( temp3, L"claudio" );
    temp2 = wcsdup (  temp3 ) ; // WRAPPER gcWcsDup
 
    // ...................................... wstringFromStrC

    wprintf ( L"\n\n --- wstringType(s1) ; \n") ;
    wstringType(s1) ;

    wprintf ( L"\n\n --- wstringNew(s1,128); \n") ;    
    wstringNew(s1,128);
   
    wprintf ( L"\n\n --- wstringFromStrC ( s1 , L\"claudio Daffra\" ) ; \n") ;
    wstringFromStrC ( s1 , L"claudio Daffra" ) ;
    wchar_t* temp1 = wstringToStrC(s1)  ; // no more LEAK #2

    wprintf ( L"\nwstring     s1          size[%d] "      ,   (int)s1.size        );
    wprintf ( L"\nwchar_t*    temp1 [%ls]"                ,   temp1               );
    wprintf ( L"\nwchar_t*    temp1       size [%d]"      ,   (int)(int)wcslen(temp1)  );
    wprintf ( L"\nDEBUG s3 [%d] [%ls]",(int)wcslen(wstr(s1)),wstr(s1) );

    // ...................................... wstringFromStrC

    wprintf ( L"\n\n --- wstringFindChar; \n") ;    
    wprintf ( L"\nfind %c = pos %d",'c' , (int)wstringFindChar(s1,L'c') );
    wprintf ( L"\nfind %c = pos %d",'x' , (int)wstringFindChar(s1,L'x') );
 
    // ...................................... wstringFindStrC
    // ...................................... wstringFindwstring
  
    wstringType(s2);

    wstringFromStrC ( s2 , L"Daffra" ) ;

    wprintf ( L"\nfind 'daffra' in 'claudio Daffra' = %p",wstringFindStrC(s1,L"Daffra")    );
    wprintf ( L"\nfind 'daffra' in 'claudio Daffra' = %p",wstringFindwstring(s1,s2)        );

    wstringFromStrC ( s2 , L"xxx" ) ;
    wprintf ( L"\nfind 'xxx' in 'claudio Daffra' = %p", wstringFindStrC(s1,L"xxx")   );
    wprintf ( L"\nfind 'xxx' in 'claudio Daffra' = %p", wstringFindwstring(s1,s2)  );
 
    // ...................................... wstringReplaceStrC

    wprintf ( L"\n\n --- wstringReplaceStrC(ID,\"a\",\"@\") ;\n") ; 

    wstringReplaceStrC(s1,L"a",L"@") ;
    wprintf ( L"\ns1 = [%ls]\n",wstringToStrC(s1) ) ;
    
    // ...................................... wstringReplaceWString
    
    wprintf ( L"\n\n --- wstringReplaceWString(ID,\"@\",\"*\") ;\n") ; 

    wstringType(pattern) ;
    wstringFromStrC(pattern,L"@") ;
  
    wstringType(replace) ;
    wstringFromStrC(replace, L"*") ;

    wstringReplaceWString( s1 , pattern , replace  );
  
    wprintf ( L"\ns1 = [" );
    wstringPrint(s1);
    wprintf ( L"]\n" );

    // ...................................... free
    
    //free(temp1);
    gcFree(temp2);
    //free(temp3);
    //free(temp4);
     

    gcStop();

    wprintf (L"\n");
      
    return 0 ;
}
