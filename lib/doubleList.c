
#include "doubleList.h"

// ......................................... [v] new

doubleList_t doubleListNew_( int(*doubleListCompare_)(const void*,const void*) )
{
    doubleListCompare = doubleListCompare_ ;
    return NULL;
}

// ......................................... [v] createNew_


doubleList_t doubleListCreateNew(doubleList_t prev,void* data)
{
    doubleList_t head = gcMalloc(sizeof(struct doubleList_s));
    head->data = data;
    head->next = NULL;
    head->prev = prev;
    return head;
}
 
// ......................................... [v] push back

doubleList_t doubleListPushBack_(doubleList_t head, void* data)
{
    if ( head==NULL)
    {
        return head = doubleListCreateNew(NULL,data);
    }
    else
    {
        doubleList_t current = head;
        
        doubleList_t newnode = gcMalloc(sizeof(struct doubleList_s));
        
        newnode->data = data;
        newnode->next = NULL;
        
        while(current->next)
            current = current->next;

        current->next = newnode;
        newnode->prev = current;
        
        return head;        
    }
    return head ;
}

// ......................................... [v] push front

doubleList_t doubleListPushFront_(doubleList_t head, void* data)
{
    if (head==NULL)
    {
        return head = doubleListCreateNew(NULL,data);
    }
    else
    {
        doubleList_t newnode = gcMalloc(sizeof(struct doubleList_s));
        
        head->prev = newnode ;
        newnode->data = data;
        newnode->next = head;
        newnode->prev = NULL; 
        
        head = newnode;//first doubleList_t should be head
        return head;
    }
    
}

// ......................................... [v] insert after 

doubleList_t doubleListInsertAfter_(doubleList_t head, void* value, void* data)
{
    doubleList_t current = head;

    if  (current!=NULL)
    {
        while( doubleListCompare (current->data , value) != 0)
        {
            current = current->next;
            if ( current==NULL) break ;
        }
    }

    if  (current!=NULL)
    {
        if ( current->next == NULL ) // se è l'ultimo elemento
        {
            doubleListPushBack_(current,data);
        }
        else
        {    
            doubleList_t newnode = gcMalloc(sizeof(struct doubleList_s));

            newnode->data = data;
            newnode->next = current->next;
            newnode->prev = current ;

            current->next->prev = newnode; 
            current->next       = newnode ; 
        }  
    }        
    return head; 
    
}
 
// ......................................... [v] insert before 

doubleList_t doubleListInsertBefore_(doubleList_t head, void* value, void* data)
{
    if ( head==NULL ) return NULL ;

    doubleList_t current = head;
    doubleList_t previous;

    if  (current!=NULL)
    {
        while( doubleListCompare (current->data , value) != 0)
        {
            previous = current;
            current = current->next;
            if ( current==NULL ) break ; // elemento non trovato
        }
    }

    if  (current!=NULL)
    {        
        doubleList_t newnode = gcMalloc(sizeof(struct doubleList_s));

        if ( current->prev == NULL ) // se è il primo elemento
        {
            head=doubleListPushFront_(current,data);
        }
        else
        {    
            newnode->data = data;
            newnode->prev = current->prev ;       
            newnode->next = current;

            current->prev->next = newnode ;        
            current->prev       = newnode ;
        }
    }
    
    return head;

}

// ......................................... [internal] delete beginnig
doubleList_t deleteBeginning(doubleList_t head)
{
    doubleList_t current = head;
    current = current->next;
    gcFree(head);
    return current;
}

// ......................................... [v] remove 

doubleList_t doubleListRemove_(doubleList_t head, void* value)
{
    if( doubleListCompare(value , head->data)==0  )
    {
        head = deleteBeginning(head);
        return head;
    }
    doubleList_t current = head;
    doubleList_t previous;

    if (current!=NULL)
    {
        while( doubleListCompare (current->data , value) != 0)
        {
            previous = current;
            current = current->next;
            if ( current == NULL ) break ; // data inesistente.
        }
    }

    if (current!=NULL)
    {
        previous->next       = current->next;
        current->next->prev  = previous;
        gcFree(current);
    }
    
    return head;
}

// ......................................... [v] remove before 

doubleList_t doubleListRemoveBefore_(doubleList_t head, void* data)
{
    doubleList_t current = head;
    doubleList_t previous, previousOfPrevious;
    
    if ( current != NULL )
    {
        while( doubleListCompare (current->data , data) != 0)
        {
            previousOfPrevious = previous;
            previous = current;
            current = current->next;
            if ( current==NULL ) break ; // elemento non trovato
        }
    }
    
    if ( current != NULL )
    {
        if ( doubleListCompare (previous->data , head->data) == 0)
        {
            head = deleteBeginning(head);
            return head;
        }

        previousOfPrevious->next = previous->next;
        current->prev            = previousOfPrevious ;
        
        gcFree(previous);
    }
    return head;
}
 
// ......................................... [v] remove after 

doubleList_t doubleListRemoveAfter_(doubleList_t head, void* data)
{
    doubleList_t current = head;

    if ( current != NULL )
    {
        while( doubleListCompare (current->data , data) != 0)
        {
            current = current->next;
            if ( current==NULL ) break ; // not found.
        }
    }
    if ( current != NULL )
    {
        doubleList_t nodeToBeDeleted;  

        if ( current->next != NULL )
        {
            
            if ( current->next->next != NULL )
            {
         
                nodeToBeDeleted      = current->next;
                current->next        = current->next->next;
                current->next->prev  = current;
                gcFree(nodeToBeDeleted);
            }            
            else
            {
                doubleListPopBack( head ) ;
            }
        }
        else
        {
            doubleListPopBack( head ) ;
        }
        

    }
    return head;
}

// ......................................... [v] reverse 

doubleList_t doubleListReverse_(doubleList_t head)  
{  
    doubleList_t    temp    = NULL;  
    doubleList_t    current = head;  
      
    // swap next and prev for all nodes of  doubly linked list 
    while (current != NULL)  
    {  
        temp = current->prev;  
        current->prev = current->next;  
        current->next = temp;              
        current = current->prev;  
    }  
      
    // Before changing head, check for the cases like empty  
    // list and list with only one node 
    if(temp != NULL )  
        head = temp->prev;  
}  

// ......................................... [v] front

doubleList_t doubleListFront_(doubleList_t head)
{
    return head;
}

// ......................................... [v] back

doubleList_t doubleListBack_(doubleList_t head)
{
    doubleList_t current = head;
    
    while(current->next)
        current = current->next;
    
    return current;
}

// ......................................... [] iterator

doubleList_t doubleListBegin(doubleList_t head)
{
    return head;
}
doubleList_t doubleListEnd(void)
{
    return NULL;
}
doubleList_t doubleListNext(doubleList_t it)
{
    doubleList_t current = it;

    current = current->next;

    return it=current;
}

// ......................................... [] reverse iterator

doubleList_t doubleListRBegin(doubleList_t head)
{ 
    doubleList_t current = head;
    
    while(current->next)
        current = current->next;
    
    return current;
}

doubleList_t doubleListRNext(doubleList_t it)
{
    doubleList_t current = it;

    current = current->prev;

    return current;
}

// ......................................... [] empty

int doubleListEmpty(doubleList_t head)
{
    return head==NULL ? 1 : 0;
}
 
// ......................................... [] size

int doubleListSize(doubleList_t head)
{
    int count=0;
    doubleList_t current = head;
    
    while(current->next)
    {
        current = current->next;
        ++count;
    }
    
    return ++count;
}
 
// ......................................... [v] doubleListPopFront

doubleList_t doubleListPopFront_(doubleList_t head)
{
     doubleList_t ret = head->next ;
     
     ret->prev = NULL ;
     
     gcFree(head);
     
     return ret ;
}

// ......................................... [v] doubleListPopBack

doubleList_t doubleListPopBack_(doubleList_t head)
{
    doubleList_t current = head;
    doubleList_t prev = head; 
    
    while(current->next)
    {
        prev = current ;
        current = current->next;
    }
    prev->next = NULL ;
    
    return head;
}
 
// ......................................... [] sort 

void doubleListSort(doubleList_t head) // bubble sort
{ 
    int swapped, i; 
    doubleList_t ptr1; 
    doubleList_t lptr = NULL; 
  
    if (head == NULL) return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = head; 
  
        while (ptr1->next != lptr) 
        { 
            if    ( doubleListCompare (ptr1->data , ptr1->next->data) > 0)
            { 
                // swap
                void* temp = ptr1->data ;
                ptr1->data = ptr1->next->data ;
                ptr1->next->data = temp ;
                
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped);
    
} 

// ......................................... [] gcFree

void doubleListFree(doubleList_t head)
{
    doubleList_t current, tmp;
 
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
#define doubleListClear doubleListFree
 
// ......................................... [] doubleListCopy

doubleList_t doubleListCopy(doubleList_t doubleList) 
{
    if (doubleList == NULL) return NULL;

    doubleList_t copy = gcMalloc(sizeof(struct doubleList_s));
    
    copy->data = doubleList->data;
    copy->prev = doubleList->prev;    
    copy->next = doubleList->next;
    
    doubleListCopy(doubleList->next);
    
    return copy;
}
 
// ......................................... [] doubleListCopy

doubleList_t doubleListSplice(doubleList_t doubleList,size_t from,size_t to) 
{
    size_t counter=0;
    
    if (doubleList == NULL) return NULL;

    doubleList_t copy=NULL;

    for ( doubleList_t it=doubleListBegin(doubleList) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        if ( counter >= from && counter <= to )
        {
            doubleListPushBack(copy,it->data);
        }
        ++counter ;
    } 
    return copy ;
}
// ......................................... [] doubleListAppend

doubleList_t doubleListAppend(doubleList_t dest,doubleList_t source) 
{
    doubleList_t temp=source;
    for (int i=0;i<doubleListSize(source);i++)
    {
        doubleListPushBack(dest, source->data );
        source = source->next ;
    }
    source=temp ; 
}

// ......................................... [] doubleListFind

doubleList_t doubleListFind(doubleList_t source,void* data) 
{
    doubleList_t temp=source;

    while(temp != NULL)
    {
        if ( doubleListCompare ( temp->data , data) == 0 ) return temp ;            
        temp = temp->next;
    }
        
    return NULL ;
}

/**/

