
#include "singleList.h"

// ......................................... [v] new

singleList_t singleListNew_( int(*singleListCompare_)(const void*,const void*) )
{
    singleListCompare = singleListCompare_ ;
    return NULL;
}

// ......................................... [v] createNew_


singleList_t singleListCreateNew(singleList_t prev,void* data)
{
    singleList_t head = gcMalloc(sizeof(struct singleList_s));
    head->data = data;
    head->next = NULL;

    return head;
}
 
// ......................................... [v] push back

singleList_t singleListPushBack_(singleList_t head, void* data)
{
    if ( head==NULL)
    {
        return head = singleListCreateNew(NULL,data);
    }
    else
    {
        singleList_t current = head;
        
        singleList_t newnode = gcMalloc(sizeof(struct singleList_s));
        
        newnode->data = data;
        newnode->next = NULL;
        
        while(current->next)
            current = current->next;

        current->next = newnode;

        
        return head;        
    }
    return head ;
}

// ......................................... [v] push front

singleList_t singleListPushFront_(singleList_t head, void* data)
{
    if (head==NULL)
    {
        return head = singleListCreateNew(NULL,data);
    }
    else
    {
        singleList_t newnode = gcMalloc(sizeof(struct singleList_s));
        

        newnode->data = data;
        newnode->next = head;

        
        head = newnode;//first singleList_t should be head
        return head;
    }
    
}

// ......................................... [v] insert after 

singleList_t singleListInsertAfter_(singleList_t head, void* value, void* data)
{
    singleList_t current = head;

    if  (current!=NULL)
    {
        while( singleListCompare (current->data , value) != 0)
        {
            current = current->next;
            if ( current==NULL) break ;
        }
    }

    if  (current!=NULL)
    {
        if ( current->next == NULL ) // se è l'ultimo elemento
        {
            singleListPushBack_(current,data);
        }
        else
        {    
            singleList_t newnode = gcMalloc(sizeof(struct singleList_s));

            newnode->data = data;
            newnode->next = current->next;
 
            current->next       = newnode ; 
        }  
    }        
    return head; 
    
}
 
// ......................................... [v] insert before 

// ......................................... [v] insert before 

singleList_t singleListInsertBefore_(singleList_t head, void* value, void* data)
{
    if ( head==NULL )
    {
        singleList_t head = gcMalloc(sizeof(struct singleList_s));
        head->data = data;
        head->next = NULL;
        return head;        
    }
    else
    {
        if(value == head->data)
        {
            head = singleListPushFront(head, data);
            return head;
        }
        singleList_t current = head;
        singleList_t previous;
        
        while( singleListCompare (current->data , value) != 0)
        {
            previous = current;
            current = current->next;
        }
        singleList_t newnode = gcMalloc(sizeof(struct singleList_s));
        newnode->data = data;
        newnode->next = current;
        previous->next = newnode;
        
        return head;
    }
}

// ......................................... [internal] delete beginnig
singleList_t deleteBeginning(singleList_t head)
{
    singleList_t current = head;
    current = current->next;
    gcFree(head);
    return current;
}

// ......................................... [v] remove 

singleList_t singleListRemove_(singleList_t head, void* value)
{
    if( singleListCompare(value , head->data)==0  )
    {
        head = deleteBeginning(head);
        return head;
    }
    singleList_t current = head;
    singleList_t previous;

    if (current!=NULL)
    {
        while( singleListCompare (current->data , value) != 0)
        {
            previous = current;
            current = current->next;
            if ( current == NULL ) break ; // data inesistente.
        }
    }

    if (current!=NULL)
    {
        previous->next       = current->next;
  
        gcFree(current);
    }
    
    return head;
}

// ......................................... [v] remove before 

singleList_t singleListRemoveBefore_(singleList_t head, void* data)
{
    singleList_t current = head;
    singleList_t previous, previousOfPrevious;
    
    if ( current != NULL )
    {
        while( singleListCompare (current->data , data) != 0)
        {
            previousOfPrevious = previous;
            previous = current;
            current = current->next;
            if ( current==NULL ) break ; // elemento non trovato
        }
    }
    
    if ( current != NULL )
    {
        if ( singleListCompare (previous->data , head->data) == 0)
        {
            head = deleteBeginning(head);
            return head;
        }

        previousOfPrevious->next = previous->next;

        
        gcFree(previous);
    }
    return head;
}
 
// ......................................... [v] remove after 

singleList_t singleListRemoveAfter_(singleList_t head, void* data)
{
    singleList_t current = head;

    if ( current != NULL )
    {
        while( singleListCompare (current->data , data) != 0)
        {
            current = current->next;
            if ( current==NULL ) break ; // not found.
        }
    }
    if ( current != NULL )
    {
        singleList_t nodeToBeDeleted;  

        if ( current->next != NULL )
        {
            
            if ( current->next->next != NULL )
            {
         
                nodeToBeDeleted      = current->next;
                current->next        = current->next->next;
   
                gcFree(nodeToBeDeleted);
            }            
            else
            {
                singleListPopBack( head ) ;
            }
        }
        else
        {
            singleListPopBack( head ) ;
        }
        

    }
    return head;
}

// ......................................... [v] reverse

singleList_t singleListReverse_(singleList_t head)
{
    singleList_t current = head, prev = NULL, next = NULL;
    
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}
// ......................................... [v] front

singleList_t singleListFront_(singleList_t head)
{
    return head;
}

// ......................................... [v] back

singleList_t singleListBack_(singleList_t head)
{
    singleList_t current = head;
    
    while(current->next)
        current = current->next;
    
    return current;
}

// ......................................... [] iterator

singleList_t singleListBegin(singleList_t head)
{
    return head;
}
singleList_t singleListEnd(void)
{
    return NULL;
}
singleList_t singleListNext(singleList_t it)
{
    singleList_t current = it;

    current = current->next;

    return it=current;
}

// ......................................... [] empty

int singleListEmpty(singleList_t head)
{
    return head==NULL ? 1 : 0;
}
 
// ......................................... [] size

int singleListSize(singleList_t head)
{
    int count=0;
    singleList_t current = head;
    
    while(current->next)
    {
        current = current->next;
        ++count;
    }
    
    return ++count;
}
 
// ......................................... [v] singleListPopFront

singleList_t singleListPopFront_(singleList_t head)
{
     singleList_t ret = head->next ;

     gcFree(head);
     
     return ret ;
}

// ......................................... [v] singleListPopBack

singleList_t singleListPopBack_(singleList_t head)
{
    singleList_t current = head;
    singleList_t prev = head; 
    
    while(current->next)
    {
        prev = current ;
        current = current->next;
    }
    
    prev->next = NULL ;
    
    return head;
}

 

// ......................................... [] sort 

// https://www.zentut.com/c-tutorial/c-linked-singleList/
// #Sort_a_linked_singleList_using_insertion_sort

singleList_t singleListSort_(singleList_t head)
{
    singleList_t x ;
    singleList_t y ;
    singleList_t e;
    
    x = head;
    head = NULL;
 
    while(x != NULL)
    {
        e = x;
        x = x->next;
        if (head != NULL)
        {
            if ( singleListCompare (e->data , head->data) > 0)
            {
                y = head;
                while (
                        (y->next != NULL) 
                        && 
                        ( singleListCompare (e->data , y->next->data) > 0)
                )
                {
                    y = y->next;
                }
                e->next = y->next;
                y->next = e;
            }
            else
            {
                e->next = head;
                head = e ;
            }
        }
        else
        {
            e->next = NULL;
            head = e ;
        }
    }
    return head;
}

// ......................................... [] gcFree

void singleListFree(singleList_t head)
{
    singleList_t current, tmp;
 
    if(head != NULL)
    {
        current = head->next;
        head->next = NULL;
        
        while(current != NULL)
        {
            tmp = current->next;
            gcFree(current);
            current = tmp;
        }
    }
}
#define singleListClear singleListFree
 
// ......................................... [] singleListCopy

singleList_t singleListCopy(singleList_t singleList) 
{
    if (singleList == NULL) return NULL;

    singleList_t copy = gcMalloc(sizeof(struct singleList_s));
    
    copy->data = singleList->data;
    
    copy->next = singleList->next;
    
    singleListCopy(singleList->next);
    
    return copy;
}
 
// ......................................... [] singleListCopy

singleList_t singleListSplice(singleList_t singleList,size_t from,size_t to) 
{
    size_t counter=0;
    
    if (singleList == NULL) return NULL;

    singleList_t copy=NULL;

    for ( singleList_t it=singleListBegin(singleList) ; it != singleListEnd(); it = singleListNext(it)  )
    {
        if ( counter >= from && counter <= to )
        {
            singleListPushBack(copy,it->data);
        }
        ++counter ;
    } 
    return copy ;
}
// ......................................... [] singleListAppend

singleList_t singleListAppend(singleList_t dest,singleList_t source) 
{
    singleList_t temp=source;
    for (int i=0;i<singleListSize(source);i++)
    {
        singleListPushBack(dest, source->data );
        source = source->next ;
    }
    source=temp ; 
}

// ......................................... [] singleListFind

singleList_t singleListFind(singleList_t source,void* data) 
{
    singleList_t temp=source;

    while(temp != NULL)
    {
        if ( singleListCompare ( temp->data , data) == 0 ) return temp ;            
        temp = temp->next;
    }
        
    return NULL ;
}

/**/

