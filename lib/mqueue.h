#ifndef mqueue
#define mqueue

#include "gc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// ........................................................... [] queue(TYPE) 

// queue_v1_int    (int)
// queue_v1

#define queueType(TYPE,ID)                          \
typedef TYPE queueDataType ## ID;                   \
typedef struct TYPEOF ( queue_s_ , ID )             \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
}  TYPEOF ( queue_ , ID ) ;                         \
TYPEOF ( queue_ , ID ) ID

// ........................................................... [] queue def in struct

#define queueDataType(TYPE,ID) typedef TYPE queueDataType ## ID;  

#define queueStruct(TYPE,ID)                        \
struct TYPEOF ( queue_s_ , ID )                     \
{                                                   \
    TYPE*   data        ;                           \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
}  ID 

// ........................................................... [] queueNew(ID,N) 
 
#define queueNew(ID,N)                                                      \
(ID).data = (void*) gcMalloc (  sizeof((ID).data) * N);                     \
(ID).size      = 0;                                                         \
(ID).capacity  = N;    

    
// ........................................................... [] SIZE
#define queueSize(ID) (ID).size

// ........................................................... [] CAPACITY
#define queueCapacity(ID) (ID).capacity

// ........................................................... [] EMPTY
#define queueEmpty(ID) ((ID).size == 0) 
 
// ........................................................... [] TOP

#define queueTop(ID) (ID).data[(ID).size-1]

// ........................................................... [] POP

#define queuePop(ID) (ID).size-=1

// ........................................................... [] PUSH     
        
#define queueInsertAtVal_(ID, POS, VAL) do {                                                \
    while ((ID).size + 1 > (ID).capacity) {                                                 \
        (ID).capacity *= 2;                                                                 \
        (ID).data = gcRealloc  ( (ID).data   , (ID).capacity * sizeof((ID).data)  );        \
    } ;                                                                                     \
    memmove((ID).data + POS + 1, (ID).data + POS, ((ID).size - POS) * sizeof((ID).data));   \
    ++(ID).size;                                                                            \
    (ID).data[POS] = VAL;                                                                   \
} while (0)

#define queuePush(ID,VAL) queueInsertAtVal_(ID,0,VAL)

// ........................................................... [] FREE 

#define queueFree(ID) do {                           \
    if ( (ID).data != NULL ) gcFree( (ID).data );    \
} while(0)
  
#endif


/**/

