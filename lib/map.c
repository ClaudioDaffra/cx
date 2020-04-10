

#include "map.h"
#include "gc.h"

// ..................................................................... create

map_t* cdCreateMapNode( size_t _multi , size_t _order , int (*_compare)( const void* d1 , const void *d2 )  ) 
{
    map.cdMapMulti=_multi;
    map.cdMapOrder=_order;
    map.compare=_compare;
    return NULL;
}

// ..................................................................... new

struct cdMapNode *cdMapNewNode(void* first,void* second)
{
    struct cdMapNode *temp =  (struct cdMapNode *)gcMalloc(sizeof(struct cdMapNode));
    
    temp->first  = first;
    temp->second = second;
    
    temp->left = temp->right = NULL;
    return temp;
}

// ..................................................................... insert

struct cdMapNode* cdMapNodeInsert(struct cdMapNode* cdMapNode, void* first,void* second)  
{
    /* If the map is empty, return a new cdMapNode */
    if (cdMapNode == NULL) 
    { 
        map.cdMapNodeSize++ ; 
        return cdMapNewNode(first,second); 
    }
    else
    {
        // se non è un multimappa e l'elemento è già presente non allocarlo
        if ( map.compare(cdMapNode->first,first)==0     &&  map.cdMapMulti==0 ) return cdMapNode ;    

        /* Otherwise, recur down the map */
        if ( map.compare(cdMapNode->first,first)>0 ) 
            cdMapNode->left  = cdMapNodeInsert(cdMapNode->left, first,second);
        else
            cdMapNode->right = cdMapNodeInsert(cdMapNode->right, first,second);        
    }
    /* return the (unchanged) cdMapNode pointer */
    return cdMapNode;
}

// ..................................................................... gcFree NODE

void cdMapNodegcFree(map_t* root)
{
    if (root != NULL) 
    {
        cdMapNodegcFree(root->right);

        cdMapNodegcFree(root->left);

        gcFree(root);

        --map.cdMapNodeSize ;
    }
}
       
// ..................................................................... search
 
struct cdMapNode* cdMapNodeSearch(struct cdMapNode* root, void* first)
{
    if (root == NULL)
        return NULL;
    
    else if ( map.compare(root->first,first)==0 )
        return root;
    else 
    {
        struct cdMapNode*left = cdMapNodeSearch(root->left, first);
        return left ? left : cdMapNodeSearch(root->right, first);
    }
}

// ..................................................................... Min Value

struct cdMapNode * cdMapNodeMinValue(struct cdMapNode* cdMapNode)
{
    struct cdMapNode* current = cdMapNode;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

// ..................................................................... delete

struct cdMapNode* cdMapNodeDelete(struct cdMapNode* root, void* first)
{
    // base case
    if (root == NULL) return root;
 
    // If the first to be deleted is smaller than the root's first,
    // then it lies in left subtree
    
    if ( map.compare(first,root->first)<0 )  
        root->left = cdMapNodeDelete(root->left, first);
 
    // If the first to be deleted is greater than the root's first, then it lies in right subtree
    else if ( map.compare(first,root->first)>0 ) 
        root->right = cdMapNodeDelete(root->right, first);
 
    // if first is same as root's first, then This is the cdMapNode to be deleted
    else
    {
        // cdMapNode with only one child or no child
        if (root->left == NULL)
        {
            struct cdMapNode *temp = root->right;
            gcFree(root);
            --map.cdMapNodeSize ;
            return temp;
        }
        else if (root->right == NULL)
        {
            struct cdMapNode *temp = root->left;
            gcFree(root);
            --map.cdMapNodeSize ;            
            return temp;
        }
 
        // cdMapNode with two children: Get the cdMapInOrder successor (smallest in the right subtree)
        struct cdMapNode* temp = cdMapNodeMinValue(root->right);
 
        // Copy the cdMapInOrder successor's content to this cdMapNode
        root->first = temp->first;
 
        // Delete the cdMapInOrder successor
        root->right = cdMapNodeDelete(root->right, temp->first);
    }
    return root;
}

// ..................................................................... max value

map_t* cdMapNodeMax(map_t* root)
{
    if(root == NULL)
        return NULL;
    if (root->right == NULL)
        return root;
    else
        return cdMapNodeMax(root->right);
}
map_t* cdMapNodeMin(map_t* root)
{
    if(root == NULL)
        return NULL;
    if (root->left == NULL)
        return root;
    else
        return cdMapNodeMax(root->left);
}

// ..................................................................... height

uint32_t cdMapNodeFindHeight(map_t* root) // Distance from Root
{
    if (root == NULL) 
    {
        return -1;
    }

    uint32_t lefth  = cdMapNodeFindHeight(root->left);
    uint32_t righth = cdMapNodeFindHeight(root->right);

    if (lefth > righth) 
    {
        return lefth + 1;
    } 
    else 
    {
        return righth + 1;
    }
}

// ..................................................................... size

size_t cdMapNodeSize(struct cdMapNode *root) 
{
    return map.cdMapNodeSize;
}

// ..................................................................... inorder

void cdMapInOrder(struct cdMapNode *root, void (*cb)(void*x) )
{
    if (root != NULL)
    {
        cdMapInOrder(root->left,cb);
        
        cb( root ) ;
        
        cdMapInOrder(root->right,cb);
    }
}
// ..................................................................... preorder

void cdMapPreOrder(struct cdMapNode *root, void (*cb)(void*x) )
{
    if (root != NULL)
    {
        cdMapPreOrder(root->left,cb);
        
        cb( root ) ;
        
        cdMapPreOrder(root->right,cb);
    }
}

// ..................................................................... main struct

struct map_s map =
{
    0                           ,   // elementi Max dell'iterator
    0                           ,   // iteratore
    0                           ,   // 0 map , 1 multimap
    0                           ,   // 0 Order , 1 unOrder
    0                           ,   // numero di elementi dell'albero
    NULL                        ,   // compare function
    cdCreateMapNode             ,   // new
    cdMapNodeInsert             ,   // insert
    cdMapNodegcFree               ,   // delete
    cd_iteratorMapBegin         ,   // begin
    cd_iteratorMapNext          ,   // next
    cdMapNodeSearch             ,   // find
    cdMapNodeDelete             ,   // remove
    cdMapNodeMax                ,   // Max    
    cdMapNodeMin                ,   // Min
    cdMapNodeFindHeight         ,   // distance from root
    cdMapNodeSize               ,   // numero di nodi
    cdMapInOrder                ,   // walk traversa with call back inOrder    :    
    cdMapPreOrder                   // walk traversa with call back unOrder
} ;
 

// ierator

iteratorMap_t* cd_iteratorMapNew(iteratorMap_t* it)
{
    const int defaultAllocSize=128 ;
    
    it->ptr         = (void*) gcMalloc ( sizeof( void* ) * defaultAllocSize ) ;
    it->size        = 0 ;
    it->capacity    = defaultAllocSize ;
    return it ;
}
void cd_iteratorMapPushBack( iteratorMap_t* it,void* ptr )
{
    if ( it->size > it->capacity )
    {
       size_t n = it->capacity*2 ;
       it->ptr         = (void*) gcRealloc ( it->ptr , sizeof( void* ) *  n ) ;    
       it->capacity = n ;
    }
    it->ptr [ it->size ] = ptr ;
    it->size += 1 ;
}

void cd_iteratorMapBegin_(iteratorMap_t* it, map_t *root)  
{
    if (root != NULL)
    {
        if ( map.cdMapOrder==1   ) cd_iteratorMapPushBack( it , root ) ;  // unOrder

        cd_iteratorMapBegin_(it,root->left);

        if ( map.cdMapOrder==0   ) cd_iteratorMapPushBack( it , root ) ; // order

        cd_iteratorMapBegin_(it,root->right);
    }
} 

size_t cd_iteratorMapBegin(iteratorMap_t* it,map_t *root) 
{
    it->size=0;
    cd_iteratorMapBegin_( it,root);

    return 0 ;
}

size_t cd_iteratorMapEnd(iteratorMap_t* it , size_t ndx )
{
    return ndx<it->size; 
}

size_t cd_iteratorMapNext(size_t *ndx )
{
    return ++(*ndx) ;
}


/**/

