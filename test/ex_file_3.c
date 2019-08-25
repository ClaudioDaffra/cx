
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"

/*

    cl  lib\gc.c lib\fs.c lib\stdio.c test\ex_file_3.c   /Fex.exe    /WX
    gcc lib\gc.c lib\fs.c lib\stdio.c test\ex_file_3.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/stdio.c test/ex_file_3.c   -o x        -Wall -Wextra -pedantic

*/

/*
    (ク)(3)(§)(2)
    [ク][リ][フ][§][1][2][3]
     {{{17,﻿claudio daffraᰀr}}}
*/

/**
    mostra l'utilizzo dei file binary (ansi/wide)
    
    :   fileType    ->  definizione tipo
    :   fileNew     ->  allocazione tipo
    :   iterator    ->  fileBegin , fileEnd , fileNext
    :   read/write  ->  fileRead , fileWrite
    
*/

int main ( void )
{
    gcStart(); 

    //
    
    consoleSetUTF8() ;

    // ................................................. file type
    
    fileType(wchar_t,f);

    // ................................................. file new
    
    fileNew(f);


    f = fileOpen ( stream_wide , gcStrDup("data/cd.bin") , gcStrDup("rb")  ) ;

    wchar_t buffer;

    wprintf (L"\n"); 

    // ................................................. file begin
    
    fileBegin(f);

    fileRead(f,buffer);
    
    wprintf ( L"(%lc)",buffer ) ;

    // ................................................. file end
    
    fileEnd(f);
    
    fileRead(f,buffer);
    wprintf ( L"(%lc)",buffer ) ;
 
    // ................................................. file at
    
    fileAt(f,3);
    fileRead(f,buffer);
    wprintf ( L"(%lc)",buffer ) ;

    // ................................................. file next
    
    fileNext(f);

    fileRead(f,buffer);
    wprintf ( L"(%lc)",buffer ) ;

    // ................................................. file load begin
    
    wprintf (L"\n"); 
    fileBegin(f);
    while ( fileRead(f,buffer) )
    {
        wprintf ( L"[%lc]",buffer ) ;
    }
 
    fileClose( f );

    // ................................................. file save

    f = fileOpen ( stream_wide , gcStrDup("data/cd.bin") , gcStrDup("wb+")  ) ;  

    wchar_t dest[] = L"claudio daffra";

    fileSave(f,dest,wcslen(dest));
    
    fileClose( f );

    // ................................................. file save
 
    f = fileOpen ( stream_wide , gcStrDup("data/cd.bin") , gcStrDup("rb")  ) ;  

    wchar_t*  dest2;

    fileLoad(f,dest2);
 
    wprintf ( L"\n dest2::[%ls]\n",dest2 ) ;
   
    fileClose( f );

    /** look at
    
    :   fileBinarySave
    :   fileBinaryLoad
    :   fileTextSave
    :   fileTextLoad
    :   fileDelete
    :   fileRename

    */

    gcStop() ;
 
    return 0 ;
}

/*

    claudio@ubuntu:~/cx$ sh v.sh 
    ==18369== Memcheck, a memory error detector
    ==18369== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==18369== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==18369== Command: ../x
    ==18369== 

    (c)(a)(u)(i)
    [c][l][a][u][d][i][o][ ][d][a][f][f][r][a]
     dest2::[==18369== Conditional jump or move depends on uninitialised value(s)
    ==18369==    at 0x4C37AE9: wcslen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==18369==    by 0x4EA5DD6: vfwprintf (vfprintf.c:1643)
    ==18369==    by 0x4EBEBC5: wprintf (wprintf.c:32)
    ==18369==    by 0x109B89: main (in /home/claudio/cx/x)
    ==18369== 
    claudio daffra]
    ==18369== 
    ==18369== HEAP SUMMARY:
    ==18369==     in use at exit: 0 bytes in 0 blocks
    ==18369==   total heap usage: 68 allocs, 68 frees, 24,998 bytes allocated
    ==18369== 
    ==18369== All heap blocks were freed -- no leaks are possible
    ==18369== 
    ==18369== For counts of detected and suppressed errors, rerun with: -v
    ==18369== Use --track-origins=yes to see where uninitialised values come from
    ==18369== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/cx$ 

*/


