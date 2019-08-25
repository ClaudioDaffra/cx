#ifndef cdTree
#define cdTree

//*****************
//    Tree
//*****************

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct cdTreeNode
{
    void* data;
    struct cdTreeNode *left, *right;
    
} tree_t;


typedef struct iteratorTree_S
{
    void**  ptr         ;
    size_t  size        ;
    size_t  capacity    ;
    
} iteratorTree_t ;

iteratorTree_t*  cd_iteratorTreeNew       ( iteratorTree_t* it ) ;
void             cd_iteratorTreePushBack  ( iteratorTree_t* it , void* ptr  ) ;
void             cd_iteratorTreeBegin_    ( iteratorTree_t* it , tree_t *root) ; 
size_t           cd_iteratorTreeBegin     ( iteratorTree_t* it , tree_t *root) ;
size_t           cd_iteratorTreeEnd       ( iteratorTree_t* it , size_t ndx ) ;
size_t           cd_iteratorTreeNext      ( size_t *ndx ) ;


#define TreeIt_t tree_t


tree_t*     cdCreateTreeNode         ( size_t _multi , size_t _order , int32_t (*_compare)( const void* d1 , const void *d2 )  )  ;

tree_t*     cdTreeNewNode            ( void* data ) ;
tree_t*     cdTreeNodeInsert         ( struct cdTreeNode* cdTreeNode, void* data )   ;
void        cdTreeNodefree           ( tree_t* root) ;

tree_t*     cdTreeNodeSearch         ( struct cdTreeNode* root, void* data)    ; 
tree_t*     cdTreeNodeDelete         ( struct cdTreeNode* root, void* data) ; 

tree_t*     cdTreeNodeMinValue       ( struct cdTreeNode* cdTreeNode) ;

tree_t*     cdTreeNodeMax            ( tree_t* root) ; 
tree_t*     cdTreeNodeMin            ( tree_t* root) ; 

uint32_t    cdTreeNodeFindHeight     ( tree_t* root) ;
size_t      cdTreeNodeSize           ( struct cdTreeNode *root) ;
void        cdTreeInOrder            ( struct cdTreeNode *root, void (*cb)(void*x) ) ;
void        cdTreePreOrder           ( struct cdTreeNode *root, void (*cb)(void*x) ) ;
    


struct Tree_s
{
    // private

    size_t    cdItMax       ;   // elementi Max dell'iteratore
    size_t    cdItNode      ;   // iteratore
    size_t    cdTreeMulti    ;   // 0 Tree , 1 multiTree
    size_t    cdTreeOrder    ;   // 0 Order , 1 unOrder  
    size_t    cdTreeNodeSize ;   // numero di elementi dell'albero    
    
    // public    
    
    int32_t     (*compare)      ( const void* d1 , const void *d2 ) ; 
    tree_t*     (*new)          ( size_t _multi , size_t _order , int32_t (*_compare)( const void* d1 , const void *d2 )  ) ; 
    tree_t*     (*insert)       ( struct cdTreeNode* cdTreeNode, void* data )   ;     
    void        (*delete)       ( tree_t* root) ;    
    size_t      (*begin)        ( iteratorTree_t* it , tree_t *root) ;
    size_t      (*next)         ( size_t *ndx ) ;
    tree_t*     (*find)         ( struct cdTreeNode* root, void* data)    ; 
    tree_t*     (*remove)       ( struct cdTreeNode* root, void* data)    ; 
    tree_t*     (*Max)          ( tree_t* root) ;
    tree_t*     (*Min)          ( tree_t* root) ;
    uint32_t    (*height)       ( tree_t* root) ;    
    size_t      (*size)         ( struct cdTreeNode *root) ;
    void        (*inOrder)      ( struct cdTreeNode *root, void (*cb)(void*data) ) ;
    void        (*unOrder)      ( struct cdTreeNode *root, void (*cb)(void*data) ) ;    
} ;

extern struct Tree_s tree ;

#define treeOrdered     0
#define treeUnOrdered   1 
#define treeSingleKey   0
#define treeMultiKey    1

#define treeType(ID)                           tree_t * ID 	
#define treeSingleOrderedNew(ID,CMP)           ID = tree.new ( treeSingleKey, treeOrdered , CMP ) ; 
#define treeSingleUnOrderedNew(ID,CMP)         ID = tree.new ( treeSingleKey, treeUnOrdered , CMP ) ;
#define treeMultiOrderedNew(ID,CMP)            ID = tree.new ( treeMultiKey, treeOrdered , CMP ) ; 
#define treeMultiUnOrderedNew(ID,CMP)          ID = tree.new ( treeMultiKey, treeUnOrdered , CMP ) 

#define itTree(ID)               iteratorTree_t (ID) ; cd_iteratorTreeNew(&(ID));
 
#define treeBegin(ID,ROOT)     size_t ID##ndx = cd_iteratorTreeBegin(&(ID),ROOT)
#define treeEnd(ID)            cd_iteratorTreeEnd(&(ID),ID##ndx)
#define treeNext(ID)           ID##ndx=cd_iteratorTreeNext(&ID##ndx)

#define itTreedata(ID)          ((( tree_t*)(ID).ptr[ID##ndx])->data)

#define treeData(p)             (((tree_t*)(p))->data) 


   
#endif  /* cdTree */



/**/


