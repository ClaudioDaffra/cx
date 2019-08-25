#ifndef cdDir
#define cdDir

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#include "gc.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string.h>
 
#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
    #include "dirent.h"
#endif

#if defined(__linux__) 
    #include <dirent.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <sys/statvfs.h>
#endif

// ..................................................... rename dir

int dirRename( char * _oldName,char * _newName ) ;

// ..................................................... make dir

int dirMake( char* _name )   ;

// ..................................................... remove dir

int dirRemove( char* _name ) ;

// ..................................................... dir remove all

int dirRemoveAll( char *path) ;

// ..................................................... getFullPath

char* getFullPath(void) ;

// ..................................................... getRealPath

char* getRealPath(char* path) ;

// ..................................................... dirExists

int dirExists( char* szPath) ;
#define dirExist dirExists

// ..................................................... isDir ?

int isDir(char* name) ;

// ..................................................... free space on drive

long freeSpaceOnDrive( char* _path ) ;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

typedef DIR*                dir_t;
typedef struct dirent *     itDir_t; 

#define dirType(ID) DIR *ID
#define itDir(ID)   struct dirent *ID

// .......................................................... dir Open
    
dir_t   dirOpen( char * _dir ) ;

// .......................................................... dir Close

#define dirClose    closedir

// .......................................................... iterator

#define dirBegin(ID)    readdir (ID) 
#define dirEnd(...)     NULL /*__VA_ARGS__*/
#define dirNext(ID)     readdir (ID) 

// .......................................................... dir change

int dirChange( char * _newName ) ;

// .......................................................... internal

void cdEraseTemp(void) ;

// ..........................................................  dir temp

char* dirTemp(void) ;
 
    
/**/


#endif


/**/



