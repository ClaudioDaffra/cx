
#include "../src/cxx.h"

/*
	// cls      &   cl  src\gc.c src\stdio.c src\string.c tst\string001.c /Febin\x.exe       /utf-8 /WX

	// clear    ;   gcc src/gc.c src/stdio.c src/string.c tst/string001.c -o bin/x           -Wall   -Wextra -pedantic
*/


int main() 
{
    gcStart();
     
	stdio_t stdio ;
 
	stdioSetMBS( &stdio );
		
    char* str3 = "claudio daffra";
 
	// convert
    
	fprintf ( stdout,"\n" );
	
	fprintf ( stdout,"(%s)\n",cnvR64toS8(DBL_MAX) ) ;
	fprintf ( stdout,"(%s)\n",cnvR32toS8(FLT_MAX) ) ;

	fprintf ( stdout,"(%s)\n",cnvPTRtoS8(str3) ) ;
 
	fprintf ( stdout,"(%s)\n",cnvI80toS8(LLONG_MAX) ) ;
	fprintf ( stdout,"(%s)\n",cnvI64toS8(LONG_MAX)  ) ;
 
	fprintf ( stdout,"(%s)\n",cnvI32toS8(INT_MAX)   ) ;
	
	fprintf ( stdout,"(%s)\n",cnvI16toS8(SHRT_MAX)  ) ;

    char* x = cnvWStoS8(L"你好吗") ;
    fprintf ( stdout,"[%s]\n",x ) ;

    printf("\nthat's al folks ! (  string001.c ) \n");
    
    gcStop();
    
    return 0; 
} 
