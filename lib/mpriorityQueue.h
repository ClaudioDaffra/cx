#ifndef mpriorityQueue
#define mpriorityQueue

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#include "gc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <wchar.h>


#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

// ........................................................... TYPEOF

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef TYPEOF
#define TYPEOF(x,y)    CONCATENATE(x,y)
#endif

#ifndef MERGE
#define MERGE    TYPEOF
#endif

// ........................................................... [] priorityQueue(TYPE) 

// priorityQueue_v1_int    (int)
// priorityQueue_v1

#define priorityQueueType(TYPE,ID)                  \
typedef TYPE priorityQueueDataType ## ID;           \
typedef struct TYPEOF ( priorityQueue_s_ , ID )     \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
    int     (*compare)  (const void*,const void*) ; \
}  TYPEOF ( priorityQueue_ , ID ) ;                 \
TYPEOF ( priorityQueue_ , ID ) ID
 
// ........................................................... [] priorityQueueNew(ID,N) 
 
#define priorityQueueNew(ID,N)                                  \
(ID).data = (void*) gcMalloc (  sizeof((ID).data) * N);         \
(ID).size      = 0;                                             \
(ID).capacity  = N;    

    
// ........................................................... [] SIZE
#define priorityQueueSize(ID) (ID).size

// ........................................................... [] CAPACITY
#define priorityQueueCapacity(ID) (ID).capacity

// ........................................................... [] EMPTY
#define priorityQueueEmpty(ID) ((ID).size == 0) 
 
// ........................................................... [] TOP

#define priorityQueueTop(ID) (ID).data[(ID).size-1]

// ........................................................... [] POP

#define priorityQueuePop(ID) if((ID).size>0)(ID).size-=1

// ........................................................... [] priorityQueueInsertAtVal
    
#define priorityQueueInsertAtVal_(ID, POS, VAL) do {                                        \
    while ((ID).size + 1 > (ID).capacity) {                                                 \
        (ID).capacity *= 2;                                                                 \
        (ID).data = gcRealloc  ( (ID).data   , (ID).capacity * sizeof((ID).data)  );        \
    } ;                                                                                     \
    memmove((ID).data + POS + 1, (ID).data + POS, ((ID).size - POS) * sizeof((ID).data) );  \
    ++(ID).size;                                                                            \
    (ID).data[POS] = VAL;                                                                   \
} while (0)

// ........................................................... [] priorityQueuePush
    
#define priorityQueuePush(ID,VAL)   \
priorityQueueInsertAtVal_(ID,0,VAL); \
qsort( (ID).data , (ID).size , sizeof(priorityQueueDataType##ID) , ID.compare ) ;

// ........................................................... [] FREE 

#define priorityQueueFree(ID) do {                  \
    if ( (ID).data != NULL ) gcFree( (ID).data );   \
} while(0)
  
#endif


/**/

