#ifndef mstack
#define mstack

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

// ........................................................... [] stack(TYPE) 

// stack_v1_int    (int)
// stack_v1

#define stackType(TYPE,ID)                          \
typedef TYPE stackDataType ## ID;                   \
typedef struct TYPEOF ( stack_s_ , ID )             \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
}  TYPEOF ( stack_ , ID ) ;                         \
TYPEOF ( stack_ , ID ) ID

// ........................................................... [] stack def in struct 

#define stackDataType(TYPE,ID) typedef TYPE stackDataType ## ID;  

#define stackStruct(TYPE,ID)                        \
struct TYPEOF ( stack_s_ , ID )                     \
{                                                   \
    TYPE*   data        ;                           \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
}  ID 

// ........................................................... [] stackNew(ID,N) 
 
#define stackNew(ID,N)                                                      \
(ID).data = (void*) gcMalloc (  sizeof((ID).data) * N);                     \
(ID).size      = 0;                                                         \
(ID).capacity  = N;    

    
// ........................................................... [] SIZE
#define stackSize(ID) (ID).size

// ........................................................... [] CAPACITY
#define stackCapacity(ID) (ID).capacity

// ........................................................... EMPTY
#define stackEmpty(ID) ((ID).size == 0) 
 
// ........................................................... [] PUSH_BACK
#define stackPush(ID, VAL) do {                                                     \
    if ((ID).size + 1 > (ID).capacity) {                                            \
        size_t N = ((ID).capacity += (ID).capacity);                                \
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );          \
        (ID).capacity = (N);                                                        \
    } ;                                                                             \
    (ID).data[stackSize(ID)] = (VAL);                                               \
    ++(ID).size ;                                                                   \
} while (0)

 
// ........................................................... [] POP_BACK
#define stackPop(ID) do {  \
    if ((ID).size) --(ID).size; \
} while (0)

// ........................................................... [] TOP 
#define stackTop(ID) (ID).data[stackSize(ID) - 1]
 
// ........................................................... [] FREE 

#define stackFree(ID) do {                           \
    if ( (ID).data != NULL ) gcFree( (ID).data );    \
} while(0)
  
#endif


/**/

