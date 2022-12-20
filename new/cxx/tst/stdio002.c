
#include "../src/cxx.h"

/*
    // cls      &   cl  src\gc.c src\string.c src\stdio.c tst\stdio002.c /Febin\x.exe /utf-8 /WX

    // clear    ;   gcc src/gc.c src/string.c src/stdio.c tst/stdio002.c -o bin/x   -Wall -Wextra -pedantic
*/


int main() 
{
    gcStart();
     
    stdio_t stdio ;
    
    stdioSetMBS( &stdio );
     
     FILE *    pFileInput=NULL ;
    
    // TODO switch \ / windows linux
    
    //char *fileInputName = "..\\tst\\file.utf8.txt" ;

    char *fileInputName = "tst/file.utf8.txt" ;
     
     
     // TODO stdFileOPEN
     // switch stream
     
     // TODO put file in Garbage Collector
     
    stdFileWOpen ( &pFileInput , fileInputName , "r","ccs=UTF-8") ;

   while ( 1 )
   {
     // TODO stdFileGetChar
     // switch stream       
     wchar_t c = fgetwc ( pFileInput ) ; // reading the file
     
     // TODO stdFileGetChar
     // switch stream
     
     if ( c == _WEOF )  break ;
     
     fPrints(stdout,"(%lc)", c ) ;
     
   }
         
    fclose(pFileInput);
    
    gcStop();
    
    return 0; 
} 
