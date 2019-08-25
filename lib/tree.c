

#include "tree.h"
#include "gc.h"

// ..................................................................... create

tree_t* 
cdCreateTreeNode
(
    size_t _multi , 
    size_t _order , 
    int (*_compare)( const void* d1 , const void *d2 )  
) 
{
    tree.cdTreeMulti=_multi;
    tree.cdTreeOrder=_order;
    tree.compare=_compare;
    return NULL;
}

// ..................................................................... new

struct cdTreeNode *cdTreeNewNode(void* data)
{
    struct cdTreeNode *temp =  (struct cdTreeNode *)gcMalloc(sizeof(struct cdTreeNode));
    
    temp->data  = data;
    
    temp->left = temp->right = NULL;
    return temp;
}

// ..................................................................... insert

struct cdTreeNode* cdTreeNodeInsert(struct cdTreeNode* cdTreeNode, void* data )  
{
    /* If the tree is empty, return a new cdTreeNode */
    if (cdTreeNode == NULL) 
    { 
        tree.cdTreeNodeSize++ ; 
        return cdTreeNewNode(data); 
    }
    else
    {
        // se non è un multiTreepa e l'elemento è già presente non allocarlo
        if ( tree.compare(cdTreeNode->data,data)==0     &&  tree.cdTreeMulti==0 ) return cdTreeNode ;    

        /* Otherwise, recur down the tree */
        if ( tree.compare(cdTreeNode->data,data)>0 ) 
            cdTreeNode->left  = cdTreeNodeInsert(cdTreeNode->left, data);
        else
            cdTreeNode->right = cdTreeNodeInsert(cdTreeNode->right, data);        
    }
    /* return the (unchanged) cdTreeNode pointer */
    return cdTreeNode;
}

// ..................................................................... gcFree NODE

void cdTreeNodegcFree(tree_t* root)
{
    if (root != NULL) 
    {
        cdTreeNodegcFree(root->right);

        cdTreeNodegcFree(root->left);

        gcFree(root);

        --tree.cdTreeNodeSize ;
    }
}
       
// ..................................................................... search
 
struct cdTreeNode* cdTreeNodeSearch(struct cdTreeNode* root, void* data)
{
    if (root == NULL)
        return NULL;
    
    else if ( tree.compare(root->data,data)==0 )
        return root;
    else 
    {
        struct cdTreeNode*left = cdTreeNodeSearch(root->left, data);
        return left ? left: cdTreeNodeSearch(root->right, data);
    }
}

// ..................................................................... Min Value

struct cdTreeNode * cdTreeNodeMinValue(struct cdTreeNode* cdTreeNode)
{
    struct cdTreeNode* current = cdTreeNode;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

// ..................................................................... delete

struct cdTreeNode* cdTreeNodeDelete(struct cdTreeNode* root, void* data)
{
    // base case
    if (root == NULL) return root;
 
    // If the data to be deleted is smaller than the root's data,
    // then it lies in left subTree
    
    if ( tree.compare(data,root->data)<0 )  
        root->left = cdTreeNodeDelete(root->left, data);
 
    // If the data to be deleted is greater than the root's data, then it lies in right subTree
    else if ( tree.compare(data,root->data)>0 ) 
        root->right = cdTreeNodeDelete(root->right, data);
 
    // if data is same as root's data, then This is the cdTreeNode to be deleted
    else
    {
        // cdTreeNode with only one child or no child
        if (root->left == NULL)
        {
            struct cdTreeNode *temp = root->right;
            gcFree(root);
            --tree.cdTreeNodeSize ;
            return temp;
        }
        else if (root->right == NULL)
        {
            struct cdTreeNode *temp = root->left;
            gcFree(root);
            --tree.cdTreeNodeSize ;            
            return temp;
        }
 
        // cdTreeNode with two children: Get the cdTreeInOrder successor (smallest in the right subTree)
        struct cdTreeNode* temp = cdTreeNodeMinValue(root->right);
 
        // Copy the cdTreeInOrder successor's content to this cdTreeNode
        root->data = temp->data;
 
        // Delete the cdTreeInOrder successor
        root->right = cdTreeNodeDelete(root->right, temp->data);
    }
    return root;
}

// ..................................................................... max value

tree_t* cdTreeNodeMax(tree_t* root)
{
    if(root == NULL)
        return NULL;
    if (root->right == NULL)
        return root;
    else
        return cdTreeNodeMax(root->right);
}
tree_t* cdTreeNodeMin(tree_t* root)
{
    if(root == NULL)
        return NULL;
    if (root->left == NULL)
        return root;
    else
        return cdTreeNodeMax(root->left);
}

// ..................................................................... height

uint32_t cdTreeNodeFindHeight(tree_t* root) // Distance from Root
{
    if (root == NULL) 
    {
        return -1;
    }

    uint32_t lefth  = cdTreeNodeFindHeight(root->left);
    uint32_t righth = cdTreeNodeFindHeight(root->right);

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

size_t cdTreeNodeSize(struct cdTreeNode *root) 
{
    return tree.cdTreeNodeSize;
}

// ..................................................................... inorder

void cdTreeInOrder(struct cdTreeNode *root, void (*cb)(void*x) )
{
    if (root != NULL)
    {
        cdTreeInOrder(root->left,cb);
        
        cb( root ) ;
        
        cdTreeInOrder(root->right,cb);
    }
}
// ..................................................................... preorder

void cdTreePreOrder(struct cdTreeNode *root, void (*cb)(void*x) )
{
    if (root != NULL)
    {
        cdTreePreOrder(root->left,cb);
        
        cb( root ) ;
        
        cdTreePreOrder(root->right,cb);
    }
}

// ..................................................................... main struct

struct Tree_s tree =
{
    0                            ,   // elementi Max dell'iterator
    0                            ,   // iteratore
    0                            ,   // 0 tree , 1 multiTree
    0                            ,   // 0 Order , 1 unOrder
    0                            ,   // numero di elementi dell'albero
    NULL                         ,   // compare function
    cdCreateTreeNode             ,   // new
    cdTreeNodeInsert             ,   // insert
    cdTreeNodegcFree             ,   // delete
    cd_iteratorTreeBegin         ,   // begin
    cd_iteratorTreeNext          ,   // next
    cdTreeNodeSearch             ,   // find
    cdTreeNodeDelete             ,   // remove
    cdTreeNodeMax                ,   // Max    
    cdTreeNodeMin                ,   // Min
    cdTreeNodeFindHeight         ,   // distance from root
    cdTreeNodeSize               ,   // numero di nodi
    cdTreeInOrder                ,   // walk traversa with call back inOrder    :    
    cdTreePreOrder                   // walk traversa with call back unOrder
} ;
 

// ierator

iteratorTree_t* cd_iteratorTreeNew(iteratorTree_t* it)
{
    const int defaultAllocSize=128 ;
    
    it->ptr         = (void*) gcMalloc ( sizeof( void* ) * defaultAllocSize ) ;
    it->size        = 0 ;
    it->capacity    = defaultAllocSize ;
    return it ;
}
void cd_iteratorTreePushBack( iteratorTree_t* it,void* ptr )
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

void cd_iteratorTreeBegin_(iteratorTree_t* it, tree_t *root)  
{
    if (root != NULL)
    {
        if ( tree.cdTreeOrder==1   ) cd_iteratorTreePushBack( it , root ) ;  // unOrder

        cd_iteratorTreeBegin_(it,root->left);

        if ( tree.cdTreeOrder==0   ) cd_iteratorTreePushBack( it , root ) ; // order

        cd_iteratorTreeBegin_(it,root->right);
    }
} 

size_t cd_iteratorTreeBegin(iteratorTree_t* it,tree_t *root) 
{
    it->size=0;
    cd_iteratorTreeBegin_( it,root);

    return 0 ;
}

size_t cd_iteratorTreeEnd(iteratorTree_t* it , size_t ndx )
{
    return ndx<it->size; 
}

size_t cd_iteratorTreeNext(size_t *ndx )
{
    return ++(*ndx) ;
}


/**/

