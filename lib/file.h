#ifndef cdFile
#define cdFile

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>


#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define MAX_FILE_PATH   MAX_PATH
    #define filePathMax     MAX_PATH
#endif

#ifdef  __linux__
    #define MAX_FILE_PATH 4096 
    #define filePathMax   4096 
    #include <sys/file.h> 
    #include <unistd.h> 
    #include <errno.h>  
#endif

#define MAX_ATTR 15 


// ......................................... stream

typedef enum stream_e
{
    stream_ansi     ,
    stream_wide     ,
    stream_utf8     ,
    stream_unicode  ,    
    stream_utf816le
    
} stream_t ;

// ......................................... stream err

typedef enum file_err_e
{
    file_err_no_err=0       ,
    file_err_filename_null  ,
    file_err_flag_null      ,
    file_err_max_file_path  ,
    file_err_open_file
    
} file_errno_t ;

// ......................................... file struct

struct file_s
{
    FILE*           pointer ;
    stream_t        stream  ;
    file_errno_t    err     ;    
    char*           name    ;
};

typedef struct file_s  file_t ;

// ......................................... fileOpen

file_t* fileOpen(
    stream_t    ccs         ,    
    char*       fileName    ,
    char*       flag        
) ;

// ......................................... fileClose
     
void fileClose( file_t *pf);

// .................................................................... file get char

#define fileGetChar(pf,x);\
    switch( pf->stream )\
    {\
        case stream_ansi :\
            x = fgetc (pf->pointer);\
            break ;\
        case stream_wide :\
            x = fgetwc(pf->pointer);\
            break ;\
    }

// .................................................................... file end

#define  fileEOF(pf)    feof(pf->pointer)

// .................................................................... file err
 
#define  fileErr(pf)    (pf->err!=file_err_no_err)

// ....................................................................  fileReplaceSlash / .

void        fileReplaceSlash                ( char* fileName ) ;

// .................................................................... fileConvertStrintrgToWString / .

wchar_t*    fileConvertStringToWString    ( char* _ansi_string ) ;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

// ........................................................... TYPEOF

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef TYPEOF
#define TYPEOF(x,y)    CONCATENATE(x,y)
#endif

#ifndef MERGE
#define MERGE    TYPEOF
#endif

// ........................................................... fileType

#define fileType(TYPE,ID)\
file_t* ID;\
typedef TYPE fileDataType ## ID;

// ........................................................... fileNew

#define fileNew(ID)    ID=(file_t*)gcMalloc(sizeof(file_t))

// ........................................................... iterator

// posiziona all'inizio
#define fileBegin(f)    fseek( f->pointer, 0, SEEK_SET )

// posiziona all'ultimo data
#define fileEnd(f)      fseek( f->pointer, -((long)sizeof(fileDataType##f)) , SEEK_END ) 

// posiziona al prossimo
#define fileNext(f)     do{ fileDataType##f X; fread ( &X , sizeof(fileDataType##f), 1, f->pointer); } while(0); 

// leggi un dato
#define fileRead(f,X)   fread ( &X , sizeof(fileDataType##f), 1, f->pointer)  

// scrivi un dato
#define fileWrite(f,X)  fwrite ( &X , 1, sizeof(fileDataType##f), f->pointer)  

// posiziona At 
#define fileAt(f,POS)   fseek( f->pointer, sizeof(fileDataType##f)*POS , SEEK_SET ) 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ..................................................... type position

#define filePos_t   fpos_t

// ..................................................... set pos

#define fileSetPos(f,POS)\
    do{\
        long pos=POS;\
        fseek(f->pointer, pos, SEEK_SET);\
    }while(0);

// ..................................................... get pos

#define fileGetPos(f,POS)\
do{\
    fgetpos(f->pointer,&POS);\
} while(0);

// ..................................................... begin pos

#define fileBeginPos(f,POS)\
    do{ rewind(f->pointer); fgetpos (f->pointer,&POS); }while(0);

// ..................................................... end pos

#define fileEndPos(f,POS)\
do{\
    fseek( f->pointer, -((long)sizeof(fileDataType##f)) , SEEK_END );\
    fgetpos (f->pointer,&POS);\
}while(0);

// ..................................................... next pos

#define fileNextPos(f)  fileNext(f)

    
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ..................................................... load file from 

#define fileLoad(f,source)\
do{\
    fseek(f->pointer, 0L, SEEK_END);\
    long bufsize = ftell(f->pointer);\
    assert(bufsize!=-1L);\
    rewind(f->pointer);\
    source = gcMalloc( sizeof(sizeof(fileDataType##f)) * (bufsize+1));\
    fread(source, sizeof(sizeof(fileDataType##f)), bufsize, f->pointer);\
    source[bufsize]=0;\
}while(0);

// ..................................................... save file to

#define fileSave(f,dest,len)  fwrite(dest,len,sizeof(wchar_t),f->pointer);

// ..................................................... file binary save/load

    #define fileBinarySave(f,stream,filename,text,_len)\
    do{\
        size_t len=_len;\
        f = fileOpen ( stream , gcStrDup(filename) , gcStrDup("wb+")  ) ;\
        fileSave(f,dest,len);\
        fileClose(f);\
    } while(0);
 
    // EX : fileBinarySave( f , stream_wide , "data\\prova.bin" , dest, wcslen(dest) );

    #define fileBinaryLoad(f,stream,filename,dest)\
    do{\
        f = fileOpen ( stream , gcStrDup(filename) , gcStrDup("rb")  ) ;\
        fileLoad(f,dest);\
        fileClose(f);\
    } while(0);
 
    // EX : fileRename("data/prova.txt","data\\ok.txt");

// ..................................................... file text save/load

    #define fileTextSave(f,stream,filename,text,_len)\
    do{\
        size_t len=_len;\
        f = fileOpen ( stream , gcStrDup(filename) , gcStrDup("w+")  ) ;\
        fileSave(f,dest,len);\
        fileClose(f);\
    } while(0);

    // EX : fileTextSave( f , stream_wide , "data\\prova.txt" , dest, wcslen(dest) );

    #define fileTextLoad(f,stream,filename,dest)\
    do{\
        f = fileOpen ( stream , gcStrDup(filename) , gcStrDup("r")  ) ;\
        fileLoad(f,dest);\
        fileClose(f);\
    } while(0);

    // EX : fileTextLoad(f , stream_wide , "data\\prova.txt" , source );
    
// ..................................................... file delete

int fileDelete( char * _fileName ) ;

// ..................................................... file rename

int fileRename( char * _oldName,char * _newName ) ;

// ..................................................... file size

size_t fileSize( file_t* f ) ;
 
// ..................................................... un/get - char , push/pop - char

#define filePopw(f)     fgetwc(f->pointer)
#define filePushw(f,wc) ungetwc(wc,f->pointer)

#define filePop(f)      fgetc(f->pointer)
#define filePush(f,c)   ungetc(c,f->pointer) 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#define fileBufferSize  BUFSIZ
#define fileNameMax     FILENAME_MAX
#define fileNameMin     L_tmpnam
#define fileOpenMax     FOPEN_MAX
#define fileTempMax     TMP_MAX

// ..................................................... orientation

#define fileWideOriented        (-1)
#define fileByteOtiented        (+1)
#define fileNotOriented         ( 0)

#define filecheckOrientation(f,flag)\
do{\
    int ret = fwide (f->poitner,0);\
    flag=fileNotOriented;\
    if ( ret<0 ) flag=fileWide;\
    if ( ret>0 ) flag=fileByte;\
}while(0);

// ..................................................... fileExists

int fileExists( char* _szPath ) ;
#define fileExist fileExists

// ..................................................... file Exstention

char *fileExt( char *_filename ) ;

// ..................................................... isFile

int isFile(char* name) ;

// ..................................................... file lock
// ..................................................... file unlock

#define   FILE_LOCK_SHARED          LOCK_SH     
#define   FILE_LOCK_EXCLUSIVE       LOCK_EX     
#define   FILE_LOCK_DO_NOT_BLOCK    LOCK_NB     
#define   FILE_LOCK_UNLOCK          LOCK_UN 

int fileLock( FILE* f ) ;

int fileUnLock( FILE* f ) ;

// ..................................................... fileCopy

int fileCopy( char * _dest, char *_source ) ;

// ..................................................... fileTemp

FILE* fileTemp(void) ;

/**/



#endif



/**/


