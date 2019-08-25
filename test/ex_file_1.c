

#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"


/*

    cl  lib\gc.c lib\fs.c lib\stdio.c test\ex_file_1.c   /Fex.exe    /WX
    gcc lib\gc.c lib\fs.c lib\stdio.c test\ex_file_1.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/stdio.c test/ex_file_1.c   -o x        -Wall -Wextra -pedantic

*/

/*
    C:\cx>a.bat
    "cd test"
    [x][1][£][€][°][@][é][ç][§][安][吧][ラ][ド][ク][リ][フ][§][
    ]
     FILE 'data\utf8.txt'.
    200"cd .."

    C:\cx>
*/

/**
    mostra l'utilizzo basilare di WIDe
    
    :   file_t      ->  definizione e allocazione
    :   fopen       ->  apertura file con stream wide
    :   fileGetChar ->  lettura carattere (wide)
    :   slash       ->  gestione automatica / \\ a seconda del S.O.
    
*/

int main ( void )
{
    gcStart(); 

    //
    
    consoleSetUTF8() ;

    file_t* f = (file_t*) gcMalloc(sizeof(file_t));

    char* filename = gcStrDup("data/utf8.txt") ;

    f = fileOpen ( stream_wide , filename  , "r"  ) ;
   
    if ( !fileErr(f) )
    {
        wchar_t wc=L'@';

        while ( !fileEOF(f) ) 
        {
            fileGetChar(f,wc);

            fwprintf ( stdout,L"[%lc]",wc );
        } ;
        wprintf ( L"\n FILE '%ls'.",fileConvertStringToWString(filename) ) ;
    }
    else
    {
        wprintf ( L"\n FILE '%ls' NOT FOUND.",fileConvertStringToWString(filename) ) ;
    } ;
   
    wprintf ( L"\n%d",console_stream );
    
    //

    fileClose( f );

    gcStop() ;
 
    return 0 ;
}

/*

    claudio@ubuntu:~/cx$ sh b.sh 
    ==15404== Memcheck, a memory error detector
    ==15404== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==15404== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==15404== Command: ../x
    ==15404== 
    [x][1][£][€][°][@][é][ç][§][安][吧][ラ][ド][ク][リ][フ][§][
    ][]
     FILE 'data/utf8.txt'.
    200==15404== 
    ==15404== HEAP SUMMARY:
    ==15404==     in use at exit: 0 bytes in 0 blocks
    ==15404==   total heap usage: 47 allocs, 47 frees, 31,224 bytes allocated
    ==15404== 
    ==15404== All heap blocks were freed -- no leaks are possible
    ==15404== 
    ==15404== For counts of detected and suppressed errors, rerun with: -v
    ==15404== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/cx$

*/


