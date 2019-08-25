
#include "../lib/gc.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

/*
    cl  lib\gc.c lib/fs.c test\ex_gc_1.c      /Fex.exe   /Ehsc /WX
    gcc lib\gc.c lib/fs.c test\ex_gc_1.c     -o x.exe    -Wall -Wextra -pedantic
    gcc lib/gc.c lib/fs.c test/ex_gc_1.c     -o x        -Wall -Wextra -pedantic
*/

//#include "../lib/gcWrapper.h"

int main ( void )
{
    gcStart();
      
    /**/
 
    char * temp1 = strdup("claudio") ;
    char * temp2 = strdup("daffra") ;
    char * temp3 = strdup("lorenzo") ;
    char * temp4 = strdup("michelle") ;

    void* x = (void*) gcMalloc( 128*sizeof(void*) )  ;
    x= gcRealloc( x,256*sizeof(void*) )  ;  
    x= gcRealloc( x,1*sizeof(void*) )  ;

    gcFree(temp3);

    // !!! #include "../lib/gcWrapper.h"    
    // free(temp2);
    
    /**/
    
    gcStop() ;
    printf ("\n");
    
 return 0 ;
}

/*

    claudio@ubuntu:~/c-$ valgrind --leak-check=full ./x

    ==11212== Memcheck, a memory error detector
    ==11212== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==11212== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==11212== Command: ./x
    ==11212== 

     size 4 capacity 128
    #DEBUG GC_POP::((2/0x522d050))

    #DEBUG gcStop.
    #DEBUG free::gc.pointer[0]::0x522d480.
    #DEBUG free::gc.pointer[1]::0x522d4d0.
    #DEBUG free::gc.pointer[2]::0x522d570.
    #DEBUG free::gc.pointer::0x522d480.
    ==11212== 
    ==11212== HEAP SUMMARY:
    ==11212==     in use at exit: 0 bytes in 0 blocks
    ==11212==   total heap usage: 6 allocs, 6 frees, 2,080 bytes allocated
    ==11212== 
    ==11212== All heap blocks were freed -- no leaks are possible
    ==11212== 
    ==11212== For counts of detected and suppressed errors, rerun with: -v
    ==11212== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    claudio@ubuntu:~/c-$

*/

