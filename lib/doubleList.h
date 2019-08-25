#ifndef cddoubleList
#define cddoubleList

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "gc.h"
 
// ......................................... [] main struct

struct doubleList_s
{
    void* data;
    struct doubleList_s *next;
    struct doubleList_s *prev;    
} ;

typedef struct doubleList_s* doubleList_t ;

//

int (*doubleListCompare)(const void*,const void*) ;

//

// ......................................... [] new

doubleList_t doubleListNew_( int(*doubleListCompare_)(const void*,const void*) ) ;
#define doubleListNew(doubleList,...) doubleList=doubleListNew_(__VA_ARGS__) 

// ......................................... [] push back

doubleList_t doubleListPushBack_(doubleList_t head, void* data) ;
#define doubleListPushBack(doubleList,...) doubleList=doubleListPushBack_(doubleList,__VA_ARGS__) 
 
// ......................................... [] push front

doubleList_t doubleListPushFront_(doubleList_t head, void* data) ;
#define doubleListPushFront(doubleList,...) doubleList=doubleListPushFront_(doubleList,__VA_ARGS__) 
 
// ......................................... [] insert after

doubleList_t doubleListInsertAfter_(doubleList_t head, void* value, void* data) ;
#define doubleListInsertAfter(doubleList,VALUE,DATA) doubleList=doubleListInsertAfter_(doubleList,VALUE,DATA)

// ......................................... [] insert before

doubleList_t doubleListInsertBefore_(doubleList_t head, void* value, void* data) ;
#define doubleListInsertBefore(doubleList,VALUE,DATA) doubleList=doubleListInsertBefore_(doubleList,VALUE,DATA)
 
// ......................................... [internal] delete beginnig
doubleList_t deleteBeginning(doubleList_t head) ;
 
// ......................................... [v] remove

doubleList_t doubleListRemove_(doubleList_t head, void* value) ;
#define doubleListRemove(doubleList,VALUE) doubleList=doubleListRemove_(doubleList,VALUE)

// ......................................... [v] remove before

doubleList_t doubleListRemoveBefore_(doubleList_t head, void* data) ;
#define doubleListRemoveBefore(doubleList,VALUE) doubleList=doubleListRemoveBefore_(doubleList,VALUE)
 
// ......................................... [] remove after

doubleList_t doubleListRemoveAfter_(doubleList_t head, void* data) ;
#define doubleListRemoveAfter(doubleList,VALUE) doubleList=doubleListRemoveAfter_(doubleList,VALUE)
 
// ......................................... [] display
#define doubleListDisplay(head,...) do {        \
    printf("\n");                               \
    doubleList_t current = head;                \
    while(current){                             \
        printf( __VA_ARGS__ current->data);     \
        current = current->next;                \
    }                                           \
} while(0);
 
// ......................................... [] reverse
doubleList_t doubleListReverse_(doubleList_t head) ;
#define doubleListReverse(doubleList) doubleList=doubleListReverse_(doubleList)
 
// ......................................... [v] front
doubleList_t doubleListFront_(doubleList_t head) ;
#define doubleListFront(doubleList) doubleListFront_(doubleList)
 
// ......................................... [v] back
doubleList_t doubleListBack_(doubleList_t head) ;
#define doubleListBack(doubleList) doubleListBack_(doubleList)
 
// ......................................... [] iterator
doubleList_t doubleListBegin(doubleList_t head) ;
 
doubleList_t doubleListEnd(void) ;
 
doubleList_t doubleListNext(doubleList_t it) ;
 
// ......................................... [] reverse iterator
doubleList_t doubleListRBegin(doubleList_t head) ;

doubleList_t doubleListRNext(doubleList_t it) ;
  
// ......................................... [] empty
int doubleListEmpty(doubleList_t head) ;
 
// ......................................... [] size
int doubleListSize(doubleList_t head) ;
 
// ......................................... [v] doubleListPopFront

doubleList_t doubleListPopFront_(doubleList_t head) ;
#define doubleListPopFront(doubleList) doubleList=doubleListPopFront_(doubleList)
 
// ......................................... [v] doubleListPopBack

doubleList_t doubleListPopBack_(doubleList_t head) ;
#define doubleListPopBack(doubleList) doubleList=doubleListPopBack_(doubleList)
 
// ......................................... [v] sort

void doubleListSort(doubleList_t start) ;

// ......................................... [] free
 
void doubleListFree(doubleList_t head) ;
 
#define doubleListClear doubleListFree

// ......................................... [] doubleListCopy

doubleList_t doubleListCopy(doubleList_t doubleList) ;
 
// ......................................... [v] doubleListCopy

doubleList_t doubleListSplice(doubleList_t doubleList,size_t from,size_t to) ;
 
doubleList_t doubleListAppend(doubleList_t dest,doubleList_t source)  ;

doubleList_t doubleListFind(doubleList_t source,void* data) ;

// ----------------------------------------------------------------------------------
 
#define doubleListType(ID)      doubleList_t ID=NULL 
#define itDoubleList(ID)        doubleList_t ID 

// ----------------------------------------------------------------------------------
 
 
#endif
 
 
/**/

