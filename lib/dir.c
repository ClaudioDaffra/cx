
#include "dir.h"

// .................................................................... path Replace Slash

static void pathReplaceSlash( char* dirName )
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

    for (uint32_t i=0 ; i<strlen(dirName) ; i++ )
    {
        if ( dirName[i]==search )
        { 
            dirName[i] = replace ;
        }
    }
}

// .................................................................... dir rename

int dirRename( char * _oldName,char * _newName )
{
    char* newName = gcStrDup(_newName);
    pathReplaceSlash( newName );

    char* oldName = gcStrDup(_oldName);
    pathReplaceSlash( oldName );
    
    return rename(oldName,newName);
}

// .................................................................... make dir

int dirMake( char* _name ) 
{
    char* name = gcStrDup(_name);
    pathReplaceSlash( name );
    
#ifdef __linux__
   return mkdir(name, 0777); 
#endif

#if defined(_WIN32) || defined(_WIN64)
   return _wmkdir(fileConvertStringToWString(name));
#endif

}

// .................................................................... remove dir

int dirRemove( char* _name ) 
{
    char* name = gcStrDup(_name);
    pathReplaceSlash( name );
    
    #ifdef __linux__
       return remove(name); 
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        return _wrmdir(fileConvertStringToWString(name));
    #endif
}

// .................................................................... dirRemoveAll

int remove_directory(const char *path)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          // Skip the names "." and ".." as we don't want to recurse on them.
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf)
          {
             struct stat statbuf;

             #if defined(_WIN32) || defined(_WIN64)  
             snprintf(buf, len, "%s\\%s", path, p->d_name);
             #else
             snprintf(buf, len, "%s/%s", path, p->d_name);             
             #endif

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = remove_directory(buf);
                }
                else
                {
                    remove(buf);
                    r2 = unlink(buf);
                }
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }

   if (!r)
   {
      r = rmdir(path);
   }

   return r;
}

int dirRemoveAll( char *path)
{
    return remove_directory(path);
}

// .................................................................... getFullPath
 
char* getFullPath(void)
{    
    char temp[MAX_FILE_PATH];
#if defined(_WIN32) || defined(_WIN64)
    GetCurrentDirectory(MAX_FILE_PATH,temp);
#endif
#if defined(__linux__) 
    getcwd(temp, sizeof(temp));
#endif    
  return gcStrDup(temp);     
}  

// .................................................................... getRealPath
 
char* getRealPath(char* _path )
{
    char buffer[MAX_FILE_PATH];

    char* path = gcStrDup( _path );
    fileReplaceSlash( path );
    
#if defined(_WIN32) || defined(_WIN64)
    TCHAR** lppPart={NULL};
    GetFullPathName(path,MAX_FILE_PATH,buffer,lppPart);
#endif

#if defined(__linux__)
    realpath( path ,buffer );
#endif

    return gcStrDup(buffer);
}

// .................................................................... dir exist

int dirExists( char* _szPath)
{
    char* szPath = gcStrDup( _szPath );
    fileReplaceSlash( szPath );

#if defined(_WIN32) || defined(_WIN64)
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#endif

#if defined(__linux__)
    DIR* dir = opendir(szPath);
    if (dir) 
    {
        closedir(dir);
        return 1 ;
    }
    return 0 ;
#endif

}

// .................................................................... isDir ?

int isDir(char* name)
{
  DIR *d;
  d = opendir(name);
  if(d) closedir(d);
  return d==NULL?0:1; 
}

// .................................................................... free space on drive

long freeSpaceOnDrive( char* _path )
{
    char* path = gcStrDup( _path );
    fileReplaceSlash( path );
    
#if defined(_WIN32) || defined(_WIN64)

    BOOL  fResult;
    unsigned __int64 i64FreeBytesToCaller   ;
    unsigned __int64 i64TotalBytes          ;
    unsigned __int64 i64FreeBytes           ;
    
    fResult = GetDiskFreeSpaceEx (
                 path,
                 (PULARGE_INTEGER)&i64FreeBytesToCaller ,
                 (PULARGE_INTEGER)&i64TotalBytes        ,
                 (PULARGE_INTEGER)&i64FreeBytes
             );
             
    if (fResult)
    {
        return i64FreeBytes / (1024*1024) ;    
    }
    return -1;     

#endif

#if defined(__linux__)
    struct statvfs stat;

    if (statvfs(path, &stat) != 0) 
    {
        // error happens, just quits here
        return -1;
    }
    // the available size is f_bsize * f_bavail
    return (stat.f_bsize * stat.f_bavail)/1024;
#endif   
 
}

// .......................................................... dir Open
    
dir_t   dirOpen( char * _dir )
{
    char* dir = gcStrDup( _dir );
    fileReplaceSlash( dir );
    return opendir (dir);
}
 
// .......................................................... dir change

int dirChange( char * _newName )
{
    char* newName = gcStrDup(_newName);
    pathReplaceSlash( newName );
    int ret=0;
#if defined(_WIN32) || defined(_WIN64)
    ret=SetCurrentDirectory(newName);
    return ret=0?0:1;
#endif
#if defined(__linux__)
    ret=chdir(newName);
    return ret==0?1:0;
#endif  
}


// .......................................................... file temp

#define cdFILETEMP  "fileTemp"
#define cdDIRTEMP   "dirTemp"

#if defined(_WIN32) || defined(_WIN64)
#define cdTEMPSLASH     "\\"
#endif
#if defined(__linux__)
#define  cdTEMPSLASH     "/"
#endif 

static char bufferDirTemp[filePathMax];
static int fbufferDirTemp=0;
static int kTemp=0;
 
FILE* fileTemp(void) // HEADER in file.h
{
    if  ( kTemp+1<fileTempMax) 
    {
        char bufferFileTemp[filePathMax];
        sprintf ( bufferFileTemp,"%s%s%s%d" ,cdDIRTEMP, cdTEMPSLASH,cdFILETEMP,++kTemp );
        
        if (fbufferDirTemp==0)
        {
            snprintf ( bufferDirTemp,filePathMax,"%s%s%s" ,getFullPath(),cdTEMPSLASH,cdDIRTEMP );
            dirMake(bufferDirTemp);
            fbufferDirTemp=1;
        }

        FILE* temp=fopen( bufferFileTemp , "w+" ) ;
        
        return temp ;
    }
    else
    {
        return NULL ;
    }
}

// ..........................................................  dir temp

char* dirTemp(void)
{
  return & bufferDirTemp [0] ; 
}

// rimuove la directory e tutti i file temporanei creati (INTERNAL USE)

void cdEraseTemp(void)
{
    if (fbufferDirTemp==0)
    {
    }
    else
    {
        dirRemoveAll(bufferDirTemp);
        rmdir(bufferDirTemp);
    }
}
 
/**/   
   
   
   
