#ifndef cdMap
#define cdMap

#ifdef __linux__
#define _GNU_SOURCE 
#endif

//*****************
//    map
//*****************

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct cdMapNode
{
    void* first;
    void* second;    
    struct cdMapNode *left, *right;
    
} map_t;


typedef struct iteratorMap_S
{
    void**  ptr         ;
    size_t  size        ;
    size_t  capacity    ;
    
} iteratorMap_t ;

iteratorMap_t*  cd_iteratorMapNew       ( iteratorMap_t* it ) ;
void            cd_iteratorMapPushBack  ( iteratorMap_t* it , void* ptr  ) ;
void            cd_iteratorMapBegin_    ( iteratorMap_t* it , map_t *root) ; 
size_t          cd_iteratorMapBegin     ( iteratorMap_t* it , map_t *root) ;
size_t          cd_iteratorMapEnd       ( iteratorMap_t* it , size_t ndx ) ;
size_t          cd_iteratorMapNext      ( size_t *ndx ) ;


#define mapIt_t map_t


map_t*      cdCreateMapNode         ( size_t _multi , size_t _order , int (*_compare)( const void* d1 , const void *d2 ) ) ;

map_t*      cdMapNewNode            ( void* first , void* second ) ;
map_t*      cdMapNodeInsert         ( struct cdMapNode* cdMapNode, void* first,void* second)   ;
void        cdMapNodefree           ( map_t* root) ;

map_t*      cdMapNodeSearch         ( struct cdMapNode* root, void* first)    ; 
map_t*      cdMapNodeDelete         ( struct cdMapNode* root, void* first) ; 

map_t*      cdMapNodeMinValue       ( struct cdMapNode* cdMapNode) ;

map_t*      cdMapNodeMax            ( map_t* root) ; 
map_t*      cdMapNodeMin            ( map_t* root) ; 

uint32_t    cdMapNodeFindHeight     ( map_t* root) ;
size_t      cdMapNodeSize           ( struct cdMapNode *root) ;
void        cdMapInOrder            ( struct cdMapNode *root, void (*cb)(void*x) ) ;
void        cdMapPreOrder           ( struct cdMapNode *root, void (*cb)(void*x) ) ;
    


struct map_s
{
    // private

    size_t    cdItMax       ;   // elementi Max dell'iteratore
    size_t    cdItNode      ;   // iteratore
    size_t    cdMapMulti    ;   // 0 map , 1 multimap
    size_t    cdMapOrder    ;   // 0 Order , 1 unOrder  
    size_t    cdMapNodeSize ;   // numero di elementi dell'albero    
    
    // public    
    
    int         (*compare)      ( const void* d1 , const void *d2 ) ; 
    map_t*      (*new)          ( size_t _multi , size_t _order , int (*_compare)( const void* d1 , const void *d2 )  )   ; 
    map_t*      (*insert)       ( struct cdMapNode* cdMapNode, void* first,void* second)   ;     
    void        (*delete)       ( map_t* root) ;    
    size_t      (*begin)        ( iteratorMap_t* it , map_t *root) ;
    size_t      (*next)         ( size_t *ndx ) ;
    map_t*      (*find)         ( struct cdMapNode* root, void* first)    ; 
    map_t*      (*remove)       ( struct cdMapNode* root, void* first)    ; 
    map_t*      (*Max)          ( map_t* root) ;
    map_t*      (*Min)          ( map_t* root) ;
    uint32_t    (*height)       ( map_t* root) ;    
    size_t      (*size)         ( struct cdMapNode *root) ;
    void        (*inOrder)      ( struct cdMapNode *root, void (*cb)(void*first) ) ;
    void        (*unOrder)      ( struct cdMapNode *root, void (*cb)(void*first) ) ;    
} ;

extern struct map_s map ;

#define mapOrdered     0
#define mapUnOrdered   1 
#define mapSingleKey   0
#define mapMultiKey    1

#define mapType(ID)                           map_t * ID 	
#define mapSingleOrderedNew(ID,CMP)           ID = map.new ( mapSingleKey  , mapOrdered    , CMP ) ; 
#define mapSingleUnOrderedNew(ID,CMP)         ID = map.new ( mapSingleKey  , mapUnOrdered  , CMP ) ;
#define mapMultiOrderedNew(ID,CMP)            ID = map.new ( mapMultiKey   , mapOrdered    , CMP ) ; 
#define mapMultiUnOrderedNew(ID,CMP)          ID = map.new ( mapMultiKey   , mapUnOrdered  , CMP ) ;

#define itMap(ID)               iteratorMap_t ID ; cd_iteratorMapNew(&(ID));
 
#define mapBegin(ID,ROOT)       size_t ID##ndx = cd_iteratorMapBegin(&(ID),ROOT)
#define mapEnd(ID)              cd_iteratorMapEnd(&(ID),ID##ndx)
#define mapNext(ID)             ID##ndx=cd_iteratorMapNext(&ID##ndx)

#define itMapFirst(ID)          ((( map_t*)(ID).ptr[ID##ndx])->first)
#define itMapSecond(ID)         ((( map_t*)(ID).ptr[ID##ndx])->second)

#define mapFirst(p)             (((map_t*)(p))->first) 
#define mapSecond(p)            (((map_t*)(p))->second) 



#endif /* cdMap */



/**/


