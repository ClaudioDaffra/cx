
#include "gc.h"
#include "file.h"
#include <stdarg.h>
#include <time.h>

wchar_t*  fileConvertStringToWString ( char* _ansi_string )
{
    if (_ansi_string != NULL )
    {
        if ( strlen(_ansi_string) > MAX_FILE_PATH )
        {
            return NULL ;
        }
        wchar_t  ws[MAX_FILE_PATH];
        
        ws[0]=0;
        
        #if defined(_MSC_VER) || defined(__linux__)
        swprintf(ws, MAX_FILE_PATH, L"%hs", _ansi_string);
        #endif
        
        #if defined(__MINGW32__) || defined(__MINGW64__)
        __mingw_swprintf(ws,  L"%hs", _ansi_string);
        #endif

        return gcWcsDup ( ws ) ;         
    }

    return NULL ;
}

// .................................................................... fileReplace /

void fileReplaceSlash( char* fileName )
{
    char search ='?'    ;
    char replace='?'    ;
    
    #ifdef __linux__
        search  = '\\'  ; 
        replace = '/'   ;
    #endif
    
    #if defined(_WIN32) || defined(_WIN64)
        search  = '/'   ;
        replace = '\\'  ;    
    #endif

    for (uint32_t i=0 ; i<strlen(fileName) ; i++ )
    {
        if ( fileName[i]==search )
        { 
            fileName[i] = replace ;
        }
    }
}

// .................................................................... fileOpen

file_t* fileOpen(
    stream_t    ccs         ,    
    char*       fileName    ,
    char*       flag        
) 
{
    // ................................................ def. file struct

    file_t* f ; // struttura file 
    
    f = (file_t*) gcMalloc ( sizeof(struct file_s) );

    f->name     = gcStrDup(fileName)  ;
    f->stream   = ccs               ;
    f->err      = file_err_no_err   ;

    // ................................................ check err
    
    if (  strlen(f->name)==0 )
    {
        f->err = file_err_filename_null;
        return f ;
    }
    if (  strlen(flag)==0 )
    {
        f->err = file_err_flag_null;
        return f ;
    }   
    if ( strlen(f->name) >= MAX_FILE_PATH  )
    {
        f->err = file_err_max_file_path ;    
        return f ;
    }

    
#if defined(__linux__)

    fileReplaceSlash( f->name );

    f->pointer = fopen ( f->name, flag ) ;

    if ( f->pointer==NULL )
    {
        f->err = file_err_max_file_path ;
        return f ;        
    }
  

#endif 

#if defined(_WIN32) || defined(_WIN64)

    fileReplaceSlash( f->name ); 

    errno_t err ;

    if ( ccs == stream_ansi )
    {
        char buffer[MAX_FILE_PATH+MAX_ATTR+1] ;
        buffer[0]=L'\0';   
        
        char _ccs[MAX_ATTR+1] ;
        _ccs[0]=L'\0';        

        switch  ( ccs )
        {
            case stream_ansi     :  strcpy ( _ccs , "" );            break ;
            case stream_wide     :  strcpy ( _ccs , "UTF-8" );       break ;
            case stream_utf8     :  strcpy ( _ccs , "UTF-8" );       break ;
            case stream_unicode  :  strcpy ( _ccs , "UNICODE" );     break ;    
            case stream_utf816le :  strcpy ( _ccs , "UTF-16LE" );    break ;
        }

        strcat (buffer,flag);
        
        if ( ccs!=stream_ansi)
        {
            strcat (buffer,",ccs=");
            strcat (buffer,_ccs);
        }

        err=fopen_s( &(f->pointer),f->name , buffer  );

    }
    else
    {
        wchar_t buffer[MAX_FILE_PATH+MAX_ATTR+1] ;
        buffer[0]=L'\0';  
        
        wchar_t _ccs[MAX_ATTR+1] ;
        _ccs[0]=L'\0';
        
        wchar_t* _fileName  = fileConvertStringToWString ( f->name  ) ;
        wchar_t* _flag      = fileConvertStringToWString ( flag  ) ;

        switch  ( ccs )
        {
            case stream_ansi     :  wcscpy ( _ccs , L"" );            break ;
            case stream_wide     :  wcscpy ( _ccs , L"UTF-8" );       break ;
            case stream_utf8     :  wcscpy ( _ccs , L"UTF-8" );       break ;
            case stream_unicode  :  wcscpy ( _ccs , L"UNICODE" );     break ;    
            case stream_utf816le :  wcscpy ( _ccs , L"UTF-16LE" );    break ;
        }

        wcscat (buffer,_flag);
        if ( ccs!=stream_ansi)
        {        
            wcscat (buffer,L",ccs=");
            wcscat (buffer,_ccs);        
        }
        
        err=_wfopen_s( &(f->pointer),_fileName , buffer  );
        
        gcFree( _fileName ) ;    
        gcFree( _flag ) ;    
    }

    if ( err )
    {
        f->err = file_err_open_file ;  
    }        
    
#endif

    strcpy ( fileName , f->name );
    return f ;
}

// .................................................................... fileClose
     
void fileClose( file_t *pf )
{
    fclose( pf->pointer );
    gcFree( pf );
}

// .................................................................... file delete
     
int fileDelete( char * _fileName )
{
    char* fileName = gcStrDup(_fileName);
    
    fileReplaceSlash( fileName );

    return remove(fileName);
}

// .................................................................... file rename

int fileRename( char * _oldName,char * _newName )
{
    char* newName = gcStrDup(_newName);
    fileReplaceSlash( newName );

    char* oldName = gcStrDup(_oldName);
    fileReplaceSlash( oldName );
    
    return rename(oldName,newName);
}

// .................................................................... file size

size_t fileSize( file_t* f )
{
    size_t prev=ftell(f->pointer);
    fseek(f->pointer, 0L, SEEK_END);
    size_t sz=ftell(f->pointer);
    fseek(f->pointer,prev,SEEK_SET);
    
    return sz;
}

// .................................................................... file exists
int fileExists( char* _szPath )
{
    char* szPath = gcStrDup( _szPath );
    fileReplaceSlash( szPath );
    
#if defined(_WIN32) || defined(_WIN64)
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#endif

#if defined(__linux__) 

    FILE *file;
    file = fopen( szPath, "r") ;
    
    if ( file )
    {
        fclose(file);
        return 1;
    }
    return 0;
#endif

}

// ..................................................... file Exstention

char *fileExt( char *_filename ) 
{
    char* filename = gcStrDup( _filename );
    fileReplaceSlash( filename );
    
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return NULL;
    ++dot;
    return dot ;
}

// ..................................................... is dir is fil

extern int isDir(char* name) ;

int isFile(char* name)
{
  return !isDir(name) ;
}


// .......................................................... file Lock

int fileLock( FILE* f )
{
    int ret=0;
#if defined(_WIN32) || defined(_WIN64)
    OVERLAPPED overlapvar = { 0 };
    ret=LockFileEx( f, LOCKFILE_EXCLUSIVE_LOCK | LOCKFILE_FAIL_IMMEDIATELY,
                        0, MAXDWORD, MAXDWORD, &overlapvar);
    return (ret!=0?1:0);                        
#endif

#if defined(__linux__) 
    ret=flock(  fileno(f), FILE_LOCK_SHARED | FILE_LOCK_EXCLUSIVE);
    return (ret==0?1:0);
#endif
}

// .......................................................... file unlock
 
int fileUnLock( FILE* f )
{
    int ret=0;
#if defined(_WIN32) || defined(_WIN64)
    OVERLAPPED overlapvar = { 0 };
    ret=UnlockFileEx(   f,0, MAXDWORD, MAXDWORD, &overlapvar  ); 
    return (ret!=0?1:0);
#endif

#if defined(__linux__) 
    ret=flock(  fileno(f), FILE_LOCK_UNLOCK);
    return (ret==0?1:0);   
#endif
}

// .......................................................... file copy
 
int fileCopy( char * _dest, char *_source )
{
    char* dest = gcStrDup( _dest );
    fileReplaceSlash( dest );
    char* source = gcStrDup( _source );
    fileReplaceSlash( source );
    
#if defined(_WIN32) || defined(_WIN64)
    BOOL flag=0;
    CopyFileA ( source,dest, flag ) ;
    return (int)flag;
#endif

#if defined(__linux__)

    //https://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c

    int fd_to, fd_from;
    char buf[4096];
    ssize_t nread;
    int saved_errno;

    fd_from = open(source, O_RDONLY);
    if (fd_from < 0)
        return -1;

    fd_to = open(dest, O_WRONLY | O_CREAT | O_EXCL, 0666 );
    if (fd_to < 0)
        goto out_error;

    while (nread = read(fd_from, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            nwritten = write(fd_to, out_ptr, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR)
            {
                goto out_error;
            }
        } while (nread > 0);
    }

    if (nread == 0)
    {
        if (close(fd_to) < 0)
        {
            fd_to = -1;
            goto out_error;
        }
        close(fd_from);

        /* Success! */
        return 0;
    }

  out_error:
    saved_errno = errno;

    close(fd_from);
    if (fd_to >= 0)
        close(fd_to);

    errno = saved_errno;
    return -1;
#endif   
}

/**/



