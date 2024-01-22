
#include "../src/cxx.h"

// clear ; gcc src/gc.c src/string.c src/stdio.c tst/stdio001.c -o bin/x -Wall -pedantic -Wextra

int main ( void ) 
{
    stdio_t stdio ;

    stdioSetUTF8( &stdio );

    char *fileInputName = "tst/file.utf8.txt" ;
    
    FILE *  pFileInput=gcFileOpenW ( fileInputName , "r","ccs=UTF-8") ;
    
    if ( pFileInput== NULL )
    {
        fprintf ( stdout , "?! File Not FOund." ) ;
        exit(-1);
    }
    fprintf ( stdout, "reading file : \n" );
    
    wchar_t wc;
    
   while (( wc = fgetwc(pFileInput)) != _WEOF)
   {
      fprintf(stdout, "[%lc]", wc);
   }

    fprintf ( stdout,"\n" );
    
    gcFileClose(pFileInput);

    return 0 ;
}