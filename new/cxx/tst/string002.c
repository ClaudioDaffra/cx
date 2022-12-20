
#include "../src/cxx.h"

/*
	// cls  &   cl  src\gc.c src\stdio.c src\string.c tst\string002.c /Febin\x.exe      /utf-8 /WX

	// clear ;  gcc src/gc.c src/stdio.c src/string.c tst/string002.c -o bin/x          -Wall   -Wextra -pedantic
*/

#include <stdlib.h>
#include <uchar.h>
#include <wchar.h>

int main() // 
{
    gcStart();
    
	stdio_t stdio ;
 
	stdioSetUTF8( &stdio );
/*
   char16_t* str16 = u"s16) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; // WIN ERR
 
   fwprintf ( stdout,L"%ls\n", cnvS8toWS( convS16toMBS( str16 ) ) ) ;


// char32_t* str32 = U"s32) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; // WIN ERR
   
//  fwprintf ( stdout,L"%ls\n", cnvS8toWS( convS32toMBS( str32 ) ) ) ;

//  convS16toMBS( str16 );

//  convS32toMBS( str32 );
 
*/

// ...............................................

    char* str3 = "claudio daffra";

    fwprintf ( stdout, L"3) %ls\n",cnvS8toWS(str3) ) ;

	// convert
	fwprintf ( stdout,L"\n" );
	
	fwprintf ( stdout,L"(%ls)\n",cnvR64toWS(DBL_MAX) ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvR32toWS(FLT_MAX) ) ;

	//fwprintf ( stdout,L"(%ls)\n",cnvPTRtoWS(str32) ) ;
	
	fwprintf ( stdout,L"(%ls)\n",cnvI80toWS(LLONG_MAX)  ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvI64toWS(LONG_MAX)   ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvI32toWS(INT_MAX)    ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvI16toWS(SHRT_MAX)   ) ;


    char* x = cnvWStoS8(L"你好吗") ;
    fwprintf ( stdout,L"[%ls]\n",cnvS8toWS(x) ) ;

    fwprintf(stdout,L"\nthat's al folks ! ( string002.c ) \n");
  
    gcStop();
    
    return 0; 
} 
