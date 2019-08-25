#ifndef cdsingleList
#define cdsingleList

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "gc.h"
 
// ......................................... [] main struct

struct singleList_s
{
    void* data;
    struct singleList_s *next;
} ;

typedef struct singleList_s* singleList_t ;

//

int (*singleListCompare)(const void*,const void*) ;

//

// ......................................... [] new

singleList_t singleListNew_( int(*singleListCompare_)(const void*,const void*) ) ;
#define singleListNew(singleList,...) singleList=singleListNew_(__VA_ARGS__) 

// ......................................... [] push back

singleList_t singleListPushBack_(singleList_t head, void* data) ;
#define singleListPushBack(singleList,...) singleList=singleListPushBack_(singleList,__VA_ARGS__) 
 
// ......................................... [] push front

singleList_t singleListPushFront_(singleList_t head, void* data) ;
#define singleListPushFront(singleList,...) singleList=singleListPushFront_(singleList,__VA_ARGS__) 
 
// ......................................... [] insert after

singleList_t singleListInsertAfter_(singleList_t head, void* value, void* data) ;
#define singleListInsertAfter(singleList,VALUE,DATA) singleList=singleListInsertAfter_(singleList,VALUE,DATA)

// ......................................... [] insert before

singleList_t singleListInsertBefore_(singleList_t head, void* value, void* data) ;
#define singleListInsertBefore(singleList,VALUE,DATA) singleList=singleListInsertBefore_(singleList,VALUE,DATA)
 
// ......................................... [internal] delete beginnig
singleList_t deleteBeginning(singleList_t head) ;
 
// ......................................... [v] remove

singleList_t singleListRemove_(singleList_t head, void* value) ;
#define singleListRemove(singleList,VALUE) singleList=singleListRemove_(singleList,VALUE)

// ......................................... [v] remove before

singleList_t singleListRemoveBefore_(singleList_t head, void* data) ;
#define singleListRemoveBefore(singleList,VALUE) singleList=singleListRemoveBefore_(singleList,VALUE)
 
// ......................................... [] remove after

singleList_t singleListRemoveAfter_(singleList_t head, void* data) ;
#define singleListRemoveAfter(singleList,VALUE) singleList=singleListRemoveAfter_(singleList,VALUE)
 
// ......................................... [] display
#define singleListDisplay(head,...) do {        \
    printf("\n");                               \
    singleList_t current = head;                \
    while(current){                             \
        printf( __VA_ARGS__ current->data);     \
        current = current->next;                \
    }                                           \
} while(0);

// ......................................... [] reverse
singleList_t singleListReverse_(singleList_t head) ;
#define singleListReverse(singleList) singleList=singleListReverse_(singleList)

// ......................................... [v] front
singleList_t singleListFront_(singleList_t head) ;
#define singleListFront(singleList) singleListFront_(singleList)
 
// ......................................... [v] back
singleList_t singleListBack_(singleList_t head) ;
#define singleListBack(singleList) singleListBack_(singleList)
 
// ......................................... [] iterator
singleList_t singleListBegin(singleList_t head) ;
 
singleList_t singleListEnd(void) ;
 
singleList_t singleListNext(singleList_t it) ;
  
// ......................................... [] empty
int singleListEmpty(singleList_t head) ;
 
// ......................................... [] size
int singleListSize(singleList_t head) ;
 
// ......................................... [v] singleListPopFront

singleList_t singleListPopFront_(singleList_t head) ;
#define singleListPopFront(singleList) singleList=singleListPopFront_(singleList)
 
// ......................................... [v] singleListPopBack

singleList_t singleListPopBack_(singleList_t head) ;
#define singleListPopBack(singleList) singleList=singleListPopBack_(singleList)
 
// ......................................... [v] sort

singleList_t singleListSort_(singleList_t head) ;
#define singleListSort(singleList) singleList=singleListSort_(singleList)

// ......................................... [] free
 
void singleListFree(singleList_t head) ;
 
#define singleListClear singleListFree

// ......................................... [] singleListCopy

singleList_t singleListCopy(singleList_t singleList) ;
 
// ......................................... [v] singleListCopy

singleList_t singleListSplice(singleList_t singleList,size_t from,size_t to) ;
 
singleList_t singleListAppend(singleList_t dest,singleList_t source)  ;

singleList_t singleListFind(singleList_t source,void* data) ;

// ----------------------------------------------------------------------------------
 
#define singleListType(ID)      singleList_t ID=NULL 
#define itSingleList(ID)        singleList_t ID 

// ----------------------------------------------------------------------------------
 
 
#endif
 
 
/**/

