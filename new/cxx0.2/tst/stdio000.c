
#include "../src/cxx.h"

// clear ; gcc src/gc.c src/string.c src/stdio.c tst/stdio000.c -o bin/x -Wall -pedantic -Wextra
// cls & cl src\gc.c src\string.c src\stdio.c tst\stdio000.c /Febin\x.exe /WX /utf-8

int main ( void ) 
{
	stdio_t stdio ;

	stdioSetUTF8( &stdio );

	char *fileInputName = "tst/file.utf8.txt" ;

	FILE *  pFileInput=gcFileOpenW ( fileInputName , "r","ccs=UTF-8") ;

	if ( pFileInput != NULL )
	{
		fwprintf ( stdout, L"reading file : \n" );

		wchar_t wc;

		while (( wc = fgetwc(pFileInput)) != (wchar_t)WEOF)
		{
			fwprintf(stdout, L"[%lc]", wc);
		}
		
		fwprintf ( stdout,L"\n" );

		gcFileClose(pFileInput);
	}
	else
	{
		fwprintf ( stdout , L"?! File Not Found.\n") ;
		exit(-1);
	}
	
	return 0 ;
}