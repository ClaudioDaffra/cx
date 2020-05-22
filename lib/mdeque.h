
#ifndef cddeque
#define cddeque

#ifdef __linux__
#define _GNU_SOURCE 
#endif

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

// ........................................................... [] deque(TYPE) 

// deque_v1_int    (int)
// deque_v1
// initial state
// [][][][].[][][][]
//         ^
//       start
//       stop

#define dequeType(TYPE,ID)                          \
typedef TYPE dequeDataType ## ID;                   \
typedef struct TYPEOF ( deque_s_ , ID )             \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
    size_t  start    ;                              \
    size_t  stop    ;                               \
}  TYPEOF ( deque_ , ID ) ;                         \
TYPEOF ( deque_ , ID ) ID

// ........................................................... [] deque def in struct

#define dequeDataType(TYPE,ID) typedef TYPE dequeDataType ## ID;  

#define dequeStruct(TYPE,ID)                       \
struct TYPEOF ( deque_s_ , ID )                    \
{                                                  \
    TYPE*   data ;                                 \
    size_t  size        ;                          \
    size_t  capacity    ;                          \
    size_t  start    ;                             \
    size_t  stop    ;                              \
}  ID 

// ........................................................... [] NEW
#define dequeNew(ID,N)                                      \
(ID).data = (void*) gcMalloc (  sizeof((ID).data) * N);     \
(ID).capacity  = N;                                         \
(ID).start     = N/2;                                       \
(ID).stop      = N/2; 
    
// ........................................................... [] SIZE
#define dequeSize(ID) ((ID).stop-(ID).start)

// ........................................................... [] CAPACITY
#define dequeCapacity(ID) (ID).capacity

// ........................................................... EMPTY
#define dequeEmpty(ID) ((ID).stop==(ID).start) 

// ........................................................... [] PUSH_BACK
#define dequePushBack(ID, VAL) do {                                                 \
    if (dequeSize(ID) + 1 > (ID).capacity) {                                        \
        size_t N = (((ID).capacity += (ID).capacity));                              \
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );          \
        (ID).capacity = (N);                                                        \
    } ;                                                                             \
    (ID).data[(ID).stop] = (VAL);                                                   \
    (ID).stop++;\
} while (0)

 
// ........................................................... [] POP_BACK
#define dequePopBack(ID) do {               \
    if ((ID).stop>(ID).start) --(ID).stop;  \
} while (0)    

// ........................................................... [] PUSH_Front
#define dequePushFront(ID, VAL) do {                                                                \
    if ((ID).start == 0) {                                                                          \
        size_t N = ((ID).capacity += (ID).capacity);                                                \
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );                          \
        (ID).capacity = (N);                                                                        \
        size_t halfCapacity = (ID).capacity/2;                                                      \
        memmove((ID).data + halfCapacity, (ID).data +0 , halfCapacity * sizeof((ID).data) );        \
        (ID).start = halfCapacity;                                                                  \
        (ID).stop += halfCapacity;                                                                  \
    } ;                                                                                             \
    (ID).start--;                                                                                   \
    (ID).data[(ID).start] = (VAL);                                                                  \
} while (0)

// ........................................................... [] POP_FRONT
#define dequePopFront(ID) do {                  \
    if ((ID).start<(ID).stop) ++(ID).start;      \
} while (0)   
    
// ........................................................... [] ERASE at
                
#define dequeEraseAt(ID, POS) do {                                                                  \
    if ( dequeSize(ID) ) {                                                                          \
    size_t pos0=((ID).start)+POS+1;                                                                 \
    memmove((ID).data+pos0-1,(ID).data+pos0,(dequeSize(ID)) * sizeof *(ID).data );                  \
    (ID).stop--;                                                                                    \
     } ;                                                                                            \
} while (0)

// ........................................................... [] ERASE at N
                
#define dequeEraseAtN(ID, POS , N) do {                                                             \
    if ( dequeSize(ID)-N>0 ) {                                                                      \
    size_t pos0=((ID).start)+POS+N;                                                                 \
    memmove((ID).data+pos0-N,(ID).data+pos0,(dequeSize(ID)) * sizeof *(ID).data );                  \
    (ID).stop--;                                                                                    \
    } ;                                                                                             \
} while (0)

// ........................................................... [] ITERATOR 
#define itDeque(ID)        dequeDataType ## ID*  
 
#define dequeBegin(ID)     ((ID).data + (ID).start)
#define dequeEnd(ID)       ((ID).data + (ID).stop) 

#define dequeRBegin(ID)    ((ID).data + (ID).stop-1)
#define dequeREnd(ID)      ((ID).data + (ID).start-1)    

// ........................................................... [] CLEAR
#define dequeClear(ID) do {                                     \
    (ID).start = (ID).stop = (ID).capacity /2 ;                 \
} while (0)

// ........................................................... [] DATA
#define dequeData(ID) ((ID).data+(ID).start)

// ........................................................... [] AT 
#define dequeAt(ID, INDEX) ((ID).data[(ID).start+INDEX])  

// ........................................................... [] dequeOfdeque ... X , XY , XYZ
    
#define dequeX(ID,NDX1)                dequeAt(ID,NDX1)
#define dequeXY(ID,NDX1,NDX2)          dequeAt(dequeAt(ID,NDX1),NDX2)
#define dequeXYZ(ID,NDX1,NDX2,NDX3)    dequeAt(dequeAt(dequeAt(ID,NDX1),NDX2),NDX3)

// ........................................................... [] FRONT
#define dequeFront(ID) ((ID).data[(ID).start])
// ........................................................... [] 
#define dequeLeft(ID) ((ID).data[(ID).start])

// ........................................................... [] BACK 
#define dequeBack(ID)   ((ID).data[(ID).stop-1])  
// ........................................................... []  
#define dequeRight(ID)  ((ID).data[(ID).stop-1])  

// ........................................................... [] MIDDLE 
#define dequeMiddle(ID)  ((ID).data[(ID).capacity/2+1])  

// ........................................................... [] FREE 
 
#define dequeFree(ID) do {                          \
    if ( (ID).data != NULL ) gcFree( (ID).data );   \
} while(0)
 
// ........................................................... [] SORT 

#define dequeSort(ID,CMP)  qsort((ID).data+(ID).start, dequeSize(ID) , sizeof(dequeDataType ## ID), CMP )

// ........................................................... [] vectorInsertAtVal     
        
#define dequeInsertAtVal(ID, POS, VAL) do {                                                 \
    while (dequeSize(ID) + 1 > (ID).capacity) {                                             \
        (ID).capacity *= 2;                                                                 \
        (ID).data = gcRealloc  ( (ID).data   , (ID).capacity * sizeof((ID).data)  );        \
    } ;                                                                                     \
    size_t pos0=((ID).start)+POS+1;                                                         \
    memmove((ID).data+pos0+1,(ID).data+pos0,(dequeSize(ID)) * sizeof *(ID).data );          \
    ++(ID).stop;                                                                            \
    (ID).data[(ID).start + POS] = VAL;                                                      \
} while (0)


    
/**/


#endif

   
/**/

