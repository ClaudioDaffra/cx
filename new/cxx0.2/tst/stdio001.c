
#include "../src/cxx.h"

// clear ; gcc src/gc.c src/string.c src/stdio.c tst/stdio001.c -o bin/x -Wall -pedantic -Wextra
// cls & cl src\gc.c src\string.c src\stdio.c tst\stdio001.c /Febin\x.exe /WX /utf-8

int main ( void ) 
{
	stdio_t stdio ;

	stdioSetMBS( &stdio );

	char *fileInputName = "tst/file.utf8.txt" ;

	FILE *  pFileInput=gcFileOpenW ( fileInputName , "r","ccs=UTF-8") ;

	if ( pFileInput== NULL )
	{
		fprintf ( stdout , "?! File Not Found." ) ;
		exit(-1);
	}
	fprintf ( stdout, "reading file : \n" );

	wchar_t wc;

	while (( wc = fgetwc(pFileInput)) != WEOF)
	{
	  fprintf(stdout, "[%lc]", wc);
	}

	fprintf ( stdout,"\n" );

	gcFileClose(pFileInput);

	return 0 ;
}