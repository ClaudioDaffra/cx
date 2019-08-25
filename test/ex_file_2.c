
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"

/*

    cl  lib\gc.c lib\fs.c lib\stdio.c test\ex_file_2.c   /Fex.exe    /WX
    gcc lib\gc.c lib\fs.c lib\stdio.c test\ex_file_2.c   -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c lib/stdio.c test/ex_file_2.c   -o x        -Wall -Wextra -pedantic

*/

/*
    C:\cx>a.bat
    "cd test"
    [a][b][c][d][e][f][g][1][2][3][4][5][6][7][8][9][
    ]
    "cd .."

    C:\cx>
*/

/**
    mostra l'utilizzo basilare di ANSI
    
    :   file_t      ->  definizione e allocazione
    :   fopen       ->  apertura file con stream wide
    :   slash       ->  gestione automatica / \\ a seconda del S.O.
    
    :   f->pointer  -> gestione diretto puntatore al file
    :   c != EOF    -> gestione diretta EOF
*/


int main ( void )
{
    gcStart(); 

    //

    file_t* f = (file_t*) gcMalloc(sizeof(file_t));

    f = fileOpen ( stream_ansi , gcStrDup("data\\ansi.txt") , gcStrDup("r")  ) ;

   
    if ( f->err == file_err_no_err )
    {
        char c='@';

        while ( c != EOF ) 
        {
            c = fgetc (f->pointer);
            fprintf ( stdout,"[%c]",c );
        } ;
    }
    else
    {
        printf ( "\n FILE 'data\\ansi.txt' NOT FOUND." ) ;
    } ;
   
    printf ( "\n" );
    
    //

    fileClose( f );

    gcStop() ;
 
    return 0 ;
}


/*

    claudio@ubuntu:~/cx$ sh b.sh
    ==16821== Memcheck, a memory error detector
    ==16821== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==16821== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==16821== Command: ../x
    ==16821== 
    [a][b][c][d][e][f][g][1][2][3][4][5][6][7][8][9][
    ][
    ][�]
    ==16821== 
    ==16821== HEAP SUMMARY:
    ==16821==     in use at exit: 0 bytes in 0 blocks
    ==16821==   total heap usage: 13 allocs, 13 frees, 5,950 bytes allocated
    ==16821== 
    ==16821== All heap blocks were freed -- no leaks are possible
    ==16821== 
    ==16821== For counts of detected and suppressed errors, rerun with: -v
    ==16821== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/cx$

*/



