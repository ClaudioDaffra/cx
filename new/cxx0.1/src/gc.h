#ifndef CD_GARBAGE_COLLECTOR
#define CD_GARBAGE_COLLECTOR

// https://github.com/peterr-s/hash_map

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <wchar.h>

// *****************
// GARBAGE_COLLECTOR
// *****************

#define GC_ERR_ALLOC                 1
#define GC_NODE_NOTFOUND             2
#define GC_DEFAULT_LOAD_FACTOR       0.75
#define GC_DEFAULT_LEN               10
#define GC_NORMAL                    0
#define GC_FAST                      1
#define GC_DESTROY                   2
#define GC_NODESTROY                 3

//#define gcMap_DEBUG_PRINTF(...)        //__VA_ARGS__
//#define gcMap_DEBUG_PRINTF(...)        __VA_ARGS__

typedef void (*gcDtorCallBack_t)(void*ptr) ;

struct gcNode_s
{
    void*                       ptr ;
    gcDtorCallBack_t            dtor;
    struct gcNode_s*            next;
};

typedef struct gcNode_s gcMapNode_t;

struct gcMap_s
{
    gcMapNode_t**   table                               ;
    size_t          (*gcHashFN)  (void* ptr)            ;
    unsigned char   (*gcPtrCMP)  (void* p1, void* p2)   ;
    size_t          size                                ;
    float           load_factor                         ;
    size_t          count                               ;
};

typedef struct gcMap_s gcMap_t;

short int             gcMapInit       ( gcMap_t* gc, size_t(* gcHashFN)(void* ptr), unsigned char (* gcPtrCMP)(void* p1, void* p2), size_t start_len, float load_factor);
void                  gcMapDestroy    ( gcMap_t* gc, unsigned short int flags1,unsigned short int flags2 );
short int             gcMapPut        ( gcMap_t* gc, void* ptr, gcDtorCallBack_t dtor, unsigned short int flags);
gcDtorCallBack_t*     gcMapGet        ( gcMap_t* gc, void* ptr, unsigned short int flags);
short int             gcMapDrop       ( gcMap_t* gc, void* ptr, unsigned short int flags);

size_t     gcDefaultHashFN       (void* ptr);
//size_t     gcMap_string_hash_fn        (void* ptr);
//size_t     gcMap_stringw_hash_fn       (void* ptr);

unsigned char         gcDefaultPtrCMP       (void* p1, void* p2);
#define               gcCompareDefault          gcDefaultPtrCMP

/*
unsigned char         gcMap_string_hash_key_comp   (void* p1, void* p2);
#define               gcMapCompareString            gcMap_string_hash_key_comp

unsigned char         gcMap_stringw_key_comp       (void* p1, void* p2);
#define               gcMapCompareStringw           gcMap_stringw_hash_key_comp
*/

int                 gcCompareStrC               ( const void * a, const void * b ) ;
int                 gcCompareWStrC              ( const void * a, const void * b ) ;
int                 gcComparepStrC              ( const void * a, const void * b ) ;
int                 gcComparepWStrC             ( const void * a, const void * b ) ;
int                 gcCompareInt                ( const void * a, const void * b ) ;
int                 gcCompareFloat              ( const void * a, const void * b ) ;
int                 gcCompareDouble             ( const void * a, const void * b ) ;
int                 gcCompareFloatAsInt         ( const void * a, const void * b ) ;
int                 gcCompareDoubleAsInt        ( const void * a, const void * b ) ;

//

short int gcMapInit    (
    gcMap_t*        gc, 
    size_t          (* gcHashFN)(void* ptr)                  , 
    unsigned char   (* gcPtrCMP)(void* p1, void* p2)         , 
    size_t          start_len                                , 
    float           load_factor
) ;

void*                gcMapAtAddress    ( gcMap_t* gc, void* ptr, unsigned short int flags) ;

// *****************
// garbage collector
// *****************

typedef gcMap_t gc_t ;

extern gc_t *gc ;

#define gcStart(...)    gc=gcLocalStart(/*__VA_ARGS__*/)
#define gcStop(...)     gcLocalStop(gc/*__VA_ARGS__*/)

void                 gcHashMapDestroy         ( gcMap_t* gc, unsigned short int flags) ;

void                 gcFreeDtor                  ( void * ptr ) ;
void                 gcFCloseDtor                ( void * ptr ) ;
void*                gcLocalStart                ( void ) ;
void*                gcLocalMalloc               ( gc_t *gc , size_t SIZE ) ;
void*                gcLocalPush                 ( gc_t *gc , void* ptr, size_t SIZE ) ;
FILE*                gcLocalFileOpen             ( gc_t *gc , const char* fileName , const char* flag) ;
void*                gcLocalFree                 ( gc_t *gc , void *ptr ) ;
void*                gcLocalPop                  ( gc_t *gc , void *ptr ) ;
void*                gcLocalStop                 ( gc_t *gc ) ;
void*                gcLocalRealloc              ( gc_t *gc, void* P , size_t N ) ;

char*                gcStrLocalDup               ( gc_t* gc,char* str) ;
wchar_t*             gcWcsLocalDup               ( gc_t* gc,wchar_t* str) ;
int*                 gcIntLocalDup               ( gc_t* gc,int val ) ;
double*              gcDoubleLocalDup            ( gc_t* gc,double val ) ;

#define gcStrDup(STR)                             gcStrLocalDup(gc,STR)    
#define gcWcsDup(STR)                             gcWcsLocalDup(gc,STR)
#define gcIntDup(STR)                             gcIntLocalDup(gc,STR)    
#define gcDoubleDup(STR)                          gcDoubleLocalDup(gc,STR)

#define gcMalloc(SIZE)                            gcLocalMalloc(gc,SIZE)

#define gcCalloc(SIZEOF,SIZE)                     gcMalloc(SIZEOF*SIZE);
#define gcLocalCalloc(GC,SIZEOF,SIZE)             gcLocalMalloc(GC,SIZEOF*SIZE);

#define gcRealloc(PTR,SIZE)                       gcLocalRealloc(gc,PTR,SIZE)

#define gcFree(PTR)                               gcLocalFree(gc,(void*)PTR)

#define gcFileOpen(FILENAME,FILEATTR)             gcLocalFileOpen(gc,FILENAME,FILEATTR)

#define gcFileLocalClose(GC,PTR)                  gcLocalFree(GC,(void*)PTR)
#define gcFileClose(PTR)                          gcLocalFree(gc,(void*)PTR)


int gcCompareInt(const void* a, const void* b) ;

//int gcCompare_uint64_t(const uint64_t* a, const uint64_t* b) ;

#endif


/* the end */

