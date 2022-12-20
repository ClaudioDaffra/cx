
#include "../src/cxx.h"

/*
	// cls      &  cl  src\gc.c src\string.c src\stdio.c tst\stdio001.c /Febin\x.exe    /utf-8 /WX

	// clear    ;  gcc src/gc.c src/string.c src/stdio.c tst/stdio001.c -o bin/x        -Wall -Wextra -pedantic
*/


int main() 
{
    gcStart();

    stdio_t stdio ;

    stdioSetUTF8( &stdio );

    //char *fileInputName = "..\\tst\\file.utf8.txt" ;

    char *fileInputName = "tst/file.utf8.txt" ;

    FILE *	pFileInput=gcFileOpenW ( fileInputName , "r","ccs=UTF-8") ;;


    // TODO stdFileOPEN
    // switch stream

    // TODO put file in Garbage Collector

    if ( pFileInput != NULL )
    {
        while ( 1 )
        {
            // TODO stdFileGetChar
            // switch stream   
            wchar_t c = fgetwc ( pFileInput ) ; // reading the file

            // TODO stdFileGetChar
            // switch stream

            if ( c == _WEOF )
            break ;

            fPrintw( stdout, L"(%lc)", c ) ;
        }
    } 
    else
    {
        fPrintw( stdout, L"%ls", L"FILE OPEN ERROR\n");
    }
    
    gcFileClose(pFileInput);

    gcStop();

    return 0; 
} 
