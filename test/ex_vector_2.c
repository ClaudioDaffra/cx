
#include "../lib/gc.h"
#include "../lib/mvector.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/*
   cl  lib\gc.c lib\fs.c test\ex_vector_2.c      /Fex.exe    /EHsc /WX
   gcc lib\gc.c lib\fs.c test\ex_vector_2.c -o   x.exe       -Wall -Wextra -pedantic
   gcc lib/gc.c lib\fs.c test/ex_vector_2.c -o   x           -Wall -Wextra -pedantic

*/

struct errLog_s
{
    int                 sender      ;
    int                 type        ;
    int                 action      ;
    int                 errMessage  ;
    uint32_t            rowTok      ;
    uint32_t            colTok      ;
    const wchar_t*      fileInput   ;
    const wchar_t*      extra       ;
} ;

typedef struct errLog_s * errLog_t ;

vectorType(errLog_t,vErrLog);

size_t pushErrLog
(
    int                 sender         ,
    int                 type           ,
    int                 action         ,
    int                 errMessage     ,
    uint32_t            rowTok         ,
    uint32_t            colTok         ,
    const wchar_t*      fileInput      ,
    const wchar_t*      extra        
)
{
    errLog_t err = gcMalloc( sizeof(struct errLog_s) ) ;

    static int fErroLogInit=0; // vector Error Log
    if ( fErroLogInit==0 )
    {
        fErroLogInit=1;
        vectorNew( vErrLog , 16 ); 
    }    

    err->sender          = sender    ;
    err->type            = type      ;
    err->action          = action    ;
    err->errMessage      = errMessage;
    err->rowTok          = rowTok    ;
    err->colTok          = colTok    ;
    err->fileInput       = fileInput ;
    err->extra           = extra     ;
    
    vectorPushBack( vErrLog ,err ) ;

    return vectorSize(vErrLog);
}
// ................................................... print err log

void printErrLog(void)
{
    itVector(vErrLog) itv ;

    for( itv = vectorBegin(vErrLog) ; itv != vectorEnd(vErrLog); itv++ )   
    {
        fwprintf ( stderr , L"\n"                                               ) ; 

        if ( (*itv)->fileInput != NULL )
        {
        fwprintf ( stderr , L"[%ls] : "         , (*itv)->fileInput                ) ;
        fwprintf ( stderr , L"%03d / %03d : "   , (*itv)->rowTok,(*itv)->colTok       ) ;
        }
        fwprintf ( stderr , L"%d : "        , (*itv)->sender ) ; 
        fwprintf ( stderr , L"%d : "        , (*itv)->type ) ;
        fwprintf ( stderr , L"%d : "        , (*itv)->action ) ;
        fwprintf ( stderr , L"%d : "        , (*itv)->errMessage ) ;
        if ( (*itv)->extra != NULL )
        {
        fwprintf ( stderr , L": (%ls)"          , (*itv)->extra                    ) ; 
        }
  
        fwprintf ( stderr , L"." ) ;         
    }
    fwprintf (stderr,L"\n");
}
int main ( void )
{
    gcStart() ;
    
    // .................................... vector
 
    wprintf ( L"\n --- vectorType(errLog_t,v); " );
    wprintf ( L"\n --- vectorNew( v , 16 ); " );

    pushErrLog( 11 ,2,3,4,100,101,gcWcsDup(L"claudio1"),NULL) ;
    pushErrLog( 12,2,3,4,100,102,gcWcsDup(L"claudio2"),NULL) ;
    pushErrLog( 13,2,3,4,100,103,gcWcsDup(L"claudio3"),NULL) ;
    pushErrLog( 14,2,3,4,100,104,gcWcsDup(L"claudio4"),NULL) ;
    pushErrLog( 15,2,3,4,100,105,gcWcsDup(L"claudio5"),NULL) ;
    pushErrLog( 16,2,3,4,100,106,gcWcsDup(L"claudio6"),NULL) ;
    pushErrLog( 17,2,3,4,100,107,gcWcsDup(L"claudio7"),NULL) ;
    pushErrLog( 18,2,3,4,100,108,gcWcsDup(L"claudio8"),NULL) ;
    pushErrLog( 21,2,3,4,100,109,gcWcsDup(L"claudio1"),NULL) ;
    pushErrLog( 22,2,3,4,100,110,gcWcsDup(L"claudio2"),NULL) ;
    pushErrLog( 23,2,3,4,100,111,gcWcsDup(L"claudio3"),NULL) ;
    pushErrLog( 14,2,3,4,100,112,gcWcsDup(L"claudio4"),NULL) ;
    pushErrLog( 15,2,3,4,100,113,gcWcsDup(L"claudio5"),NULL) ;
    pushErrLog( 16,2,3,4,100,114,gcWcsDup(L"claudio6"),NULL) ;
    pushErrLog( 17,2,3,4,100,115,gcWcsDup(L"claudio7"),NULL) ;
    pushErrLog( 18,2,3,4,100,116,gcWcsDup(L"daffra8"),NULL) ;
    pushErrLog( 1,2,3,4,100,117,gcWcsDup(L"daffra1"),NULL) ;
    pushErrLog( 12,2,3,4,100,101,gcWcsDup(L"daffra2"),NULL) ;
    pushErrLog( 13,2,3,4,100,101,gcWcsDup(L"daffra3"),NULL) ;
    pushErrLog( 14,2,3,4,100,101,gcWcsDup(L"daffra4"),NULL) ;
    pushErrLog( 15,2,3,4,100,101,gcWcsDup(L"daffra5"),NULL) ;
    pushErrLog( 16,2,3,4,100,101,gcWcsDup(L"daffra6"),NULL) ;
    pushErrLog( 17,2,3,4,100,101,gcWcsDup(L"daffra7"),NULL) ;
    pushErrLog( 18,2,3,4,100,101,gcWcsDup(L"claudio8"),gcWcsDup(L"lorenzo1")) ;
    pushErrLog( 1,2,3,4 ,100,101,gcWcsDup(L"claudio1"),gcWcsDup(L"lorenzo2")) ;
    pushErrLog( 12,2,3,4,100,101,gcWcsDup(L"claudio2"),gcWcsDup(L"lorenzo3")) ;
    pushErrLog( 13,2,3,4,100,101,gcWcsDup(L"claudio3"),gcWcsDup(L"lorenzo4")) ;
    pushErrLog( 14,2,3,4,100,101,gcWcsDup(L"claudio4"),gcWcsDup(L"lorenzo5")) ;
    pushErrLog( 15,2,3,4,100,101,gcWcsDup(L"claudio5"),gcWcsDup(L"lorenzo6")) ;
    pushErrLog( 16,2,3,4,100,101,gcWcsDup(L"claudio6"),gcWcsDup(L"lorenzo7")) ;
    pushErrLog( 17,2,3,4,100,101,gcWcsDup(L"claudio7"),gcWcsDup(L"lorenzo8")) ;
    pushErrLog( 18,2,3,4,100,101,gcWcsDup(L"claudio8"),gcWcsDup(L"lorenzo9")) ;
 
    printErrLog();

    wprintf (L"\n vector size [%d]::",vectorSize(vErrLog) );
    
    /**/

    gcStop() ;

    wprintf (L"\n");
    

 return 0 ;
}

/*
    claudio@ubuntu:~/cx$ valgrind --leak-check=full ./x
    ==30088== Memcheck, a memory error detector
    ==30088== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==30088== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==30088== Command: ./x
    ==30088== 

    ...

    ==30088== 
    ==30088== HEAP SUMMARY:
    ==30088==     in use at exit: 0 bytes in 0 blocks
    ==30088==   total heap usage: 17 allocs, 17 frees, 3,216 bytes allocated
    ==30088== 
    ==30088== All heap blocks were freed -- no leaks are possible
    ==30088== 
    ==30088== For counts of detected and suppressed errors, rerun with: -v
    ==30088== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/



/**/



