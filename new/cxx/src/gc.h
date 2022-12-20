#ifndef HASH_MAP
#define HASH_MAP

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <wchar.h>

// *****************
// typedef
// *****************

typedef void (*fCallBack_t)(void*ptr) ;

// *****************
// HASH MAP ROOT
// *****************

#define HM_ERR_ALLOC                 1
#define HM_NODE_NOTFOUND             2
#define HM_DEFAULT_LOAD_FACTOR       0.75
#define HM_DEFAULT_LEN               10
#define HM_NORMAL                    0
#define HM_FAST                      1
#define HM_DESTROY                   2
#define HM_noDESTROY                 3

#define HM_DEBUG_PRINTF(...)        //__VA_ARGS__
//#define HM_DEBUG_PRINTF(...)        __VA_ARGS__

struct hmNode_s
{
    void*            key;
    void*            value;
    struct hmNode_s* next;
};

typedef struct hmNode_s hmNode_t;

struct hashMap_s
{
    hmNode_t**              table                               ;
    unsigned long int       (*hash_fn)  (void* key)             ;
    unsigned char           (*key_comp) (void* p1, void* p2)    ;
    unsigned long int       size                                ;
    float                   load_factor                         ;
    unsigned long int       count                               ;
};

typedef struct hashMap_s hashMap_t;

short int             hash_map_init       (hashMap_t* map, unsigned long int(* hash_fn)(void* key), unsigned char (* key_comp)(void* p1, void* p2), unsigned long int start_len, float load_factor);
void                  hash_map_destroy    (hashMap_t* map, unsigned short int flags1,unsigned short int flags2 );
short int             hash_map_put        (hashMap_t* map, void* key, void* value, unsigned short int flags);
void*                 hash_map_get        (hashMap_t* map, void* key, unsigned short int flags);
short int             hash_map_drop       (hashMap_t* map, void* key, unsigned short int flags);

unsigned long int     hm_default_hash_fn       (void* key);
unsigned long int     hm_string_hash_fn        (void* key);
unsigned long int     hm_stringw_hash_fn       (void* key);

unsigned char         hm_default_key_comp       (void* p1, void* p2);
#define               hmCompareDefault          hm_default_key_comp

unsigned char         hm_string_hash_key_comp   (void* p1, void* p2);
#define               hmCompareString            hm_string_hash_key_comp

unsigned char         hm_stringw_key_comp       (void* p1, void* p2);
#define               hmCompareStringw           hm_stringw_hash_key_comp

//

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

short int hash_map_init    (
    hashMap_t* map, 
    unsigned long int           (* hash_fn)(void* key)                  , 
    unsigned char               (* key_comp)(void* p1, void* p2)        , 
    unsigned long int           start_len                               , 
    float                       load_factor
) ;

short int            hash_map_put                (hashMap_t* map, void* key, void* value, unsigned short int flags) ;
void*                hash_map_get                (hashMap_t* map, void* key, unsigned short int flags) ;
void*                hash_map_at_address         (hashMap_t* map, void* key, unsigned short int flags) ;
short int            hash_map_drop               (hashMap_t* map, void* key, unsigned short int flags) ;
void                 hash_map_destroy            (hashMap_t* map, unsigned short int flags1,unsigned short int flags2 ) ;

// *****************
// garbage collector
// *****************

typedef hashMap_t gc_t ;

gc_t *gc ;

#define gcStart(...)    gc=gcLocalStart(/*__VA_ARGS__*/)
#define gcStop(...)     gcLocalStop(gc/*__VA_ARGS__*/)

void                 gc_hash_map_destroy         ( hashMap_t* map, unsigned short int flags) ;
void                 gcFreeDtor                  ( void * ptr ) ;
void                 gcFCloseDtor                ( FILE * ptr ) ;
void*                gcLocalStart                ( void) ;
void*                gcLocalMalloc               ( gc_t *map , size_t SIZE ) ;
void*                gcLocalPush                 ( gc_t *map , void* ptr, size_t SIZE ) ;
FILE*                gcLocalFileOpen             ( gc_t *map , const char* fileName , const char* flag) ;
void*                gcLocalFree                 ( gc_t *map , void *ptr) ;
void*                gcLocalPop                  ( gc_t *map , void *ptr) ;
void*                gcLocalStop                 ( gc_t *map ) ;
void*                gcLocalRealloc              ( gc_t *map, void* P , size_t N ) ;

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

#define gcFileOpen(FILENAME,FILEATTR)             gcLocalFileOpen(gc,FILENAME,FILEATTR)
#define gcRealloc(PTR,SIZE)                       gcLocalRealloc(gc,PTR,SIZE)
#define gcFree(PTR)                               gcLocalFree(gc,(void*)PTR)

#define gcFileLocalClose(MAP,PTR)                 gcLocalFree(MAP,(void*)PTR)
#define gcFileClose(PTR)                          gcLocalFree(gc,(void*)PTR)

#endif


/* the end */

