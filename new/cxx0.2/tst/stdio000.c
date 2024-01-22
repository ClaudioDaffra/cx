
#include "../src/cxx.h"

// clear ; gcc src/gc.c src/string.c src/stdio.c tst/stdio000.c -o bin/x -Wall -pedantic -Wextra

int main ( void ) 
{
    stdio_t stdio ;

    stdioSetUTF8( &stdio );

    char *fileInputName = "tst/file.utf8.txt" ;
    
    FILE *  pFileInput=gcFileOpenW ( fileInputName , "r","ccs=UTF-8") ;
    
    if ( pFileInput== NULL )
    {
        fwprintf ( stdout , L"?! File Not FOund." ) ;
        exit(-1);
    }
    fwprintf ( stdout, L"reading file : \n" );
    
    wchar_t wc;
    
   while (( wc = fgetwc(pFileInput)) != EOF)
   {
      fwprintf(stdout, L"[%lc]", wc);
   }

    fwprintf ( stdout,L"\n" );
    
    gcFileClose(pFileInput);

    return 0 ;
}