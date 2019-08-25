
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"

/*

    cl  lib\gc.c lib\fs.c lib\stdio.c test\ex_file_4.c   /Fex.exe    /WX
    gcc lib\gc.c lib\fs.c lib\stdio.c test\ex_file_4.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/stdio.c test/ex_file_4.c   -o x        -Wall -Wextra -pedantic

*/

/*
    C:\cx>a.bat
    "cd test"

    (0).
    (19).
    {f}
    {1}
    
    "cd .."
    C:\cx>
*/

/**
    questo programma dimostra l'utilizzo degli iteratori di posizionamento
    :   fileBeginPos
    :   fileEndPos
    :   fileGetPos
    :   fileSetPos
    :   fileNextPos
*/

/**/

int main ( void )
{
    gcStart(); 

    //

    fileType(char,f);
    
    fileNew(f);

    f = fileOpen ( stream_ansi , gcStrDup("data\\ansi.txt") , gcStrDup("r")  ) ;

    // ...................................... file position
    
    filePos_t pos;

    // ...................................... file get pos

    fileGetPos(f,pos);

    // ...................................... begin

    fileBeginPos(f,pos);

    // ...................................... end
    
    fileEndPos(f,pos);

    // ...................................... set pos
    
    fileSetPos(f,5);

    // ...................................... read
     
    char buffer;
    
    fileRead(f,buffer);
    
    printf ( "\n{%c}",buffer);

    // ...................................... next pos

    fileNextPos(f) // prossimo g

    fileRead(f,buffer); // salta g
    
    printf ( "\n{%c}",buffer); // legge 1

    // ...................................... file size
    
    printf ( "\n file size %d." , (int)fileSize(f) ) ;

    
    fileClose( f );   
    
    /**/
    
    printf("\n fileBufferSize %d.", fileBufferSize  );
    printf("\n fileNameMax    %d.", fileNameMax     );
    printf("\n fileNameMin    %d.", fileNameMin     );
    printf("\n fileOpenMax    %d.", fileOpenMax     );
    printf("\n fileTempMax    %d.", fileTempMax     );
    printf("\n filePathMax    %d.", filePathMax     );
    
    /**/

    gcStop() ;
 
    return 0 ;
}

/*

    claudio@ubuntu:~/cx$ sh b.sh 
    ==17910== Memcheck, a memory error detector
    ==17910== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==17910== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==17910== Command: ../x
    ==17910== 

    {f}
    {1}
    
    ==17910== 
    ==17910== HEAP SUMMARY:
    ==17910==     in use at exit: 0 bytes in 0 blocks
    ==17910==   total heap usage: 13 allocs, 13 frees, 5,950 bytes allocated
    ==17910== 
    ==17910== All heap blocks were freed -- no leaks are possible
    ==17910== 
    ==17910== For counts of detected and suppressed errors, rerun with: -v
    ==17910== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/cx$ 

*/


