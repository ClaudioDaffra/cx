#ifndef mvector
#define mvector

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

// ........................................................... [] vector(TYPE) 

// vector_v1_int    (int)
// vector_v1

#define vectorType(TYPE,ID)                         \
typedef TYPE vectorDataType ## ID;                  \
typedef struct TYPEOF ( vector_s_ , ID )            \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
}  TYPEOF ( vector_ , ID ) ;                        \
TYPEOF ( vector_ , ID ) ID

// ........................................................... [] vector def in struct 

#define vectorDataType(TYPE,ID) typedef TYPE vectorDataType ## ID;  

#define vectorStruct(TYPE,ID)                       \
struct TYPEOF ( vector_s_ , ID )                    \
{                                                   \
    TYPE*   data        ;                           \
    size_t  size        ;                           \
    size_t  capacity    ;                           \
}  ID 

// ........................................................... [] vectorNew(ID,N) 
 
#define vectorNew(ID,N)                                                     \
(ID).data = (void*) gcMalloc (  sizeof((ID).data) * N);                     \
(ID).size      = 0;                                                         \
(ID).capacity  = N;    
    
// ........................................................... [] SIZE
#define vectorSize(ID) (ID).size

// ........................................................... [] CAPACITY
#define vectorCapacity(ID) (ID).capacity

// ........................................................... EMPTY
#define vectorEmpty(ID) ((ID).size == 0) 
 
// ........................................................... [] PUSH_BACK
#define vectorPushBack(ID, VAL) do {                                                \
    if ((ID).size + 1 > (ID).capacity) {                                            \
        size_t N = ((ID).capacity += (ID).capacity);                                \
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );          \
        (ID).capacity = (N);                                                        \
    } ;                                                                             \
    (ID).data[vectorSize(ID)] = (VAL);                                              \
    ++(ID).size ;                                                                   \
} while (0)

 
// ........................................................... [] POP_BACK
#define vectorPopBack(ID) do {  \
    if ((ID).size) --(ID).size; \
} while (0)

   
// ........................................................... [] CLEAR
#define vectorClear(ID) do {    \
    (ID).size = 0;              \
} while (0)

// ........................................................... [] DATA
#define vectorData(ID) (ID).data

// ........................................................... [] AT 
#define vectorAt(ID, INDEX) (ID).data[INDEX]    

// ........................................................... [] vectorOfVector ... X , XY , XYZ
    
#define vectorX(ID,NDX1)                vectorAt(ID,NDX1)
#define vectorXY(ID,NDX1,NDX2)          vectorAt(vectorAt(ID,NDX1),NDX2)
#define vectorXYZ(ID,NDX1,NDX2,NDX3)    vectorAt(vectorAt(vectorAt(ID,NDX1),NDX2),NDX3)

// ........................................................... [] FRONT
#define vectorFront(ID) (ID).data[0]

// ........................................................... [] BACK 
#define vectorBack(ID) (ID).data[vectorSize(ID) - 1]

// ........................................................... [] ITERATOR 
#define itVector(ID)        vectorDataType ## ID*  
 
#define vectorBegin(ID)     (ID).data
#define vectorEnd(ID)       (ID).data + (ID).size 

#define vectorRBegin(ID)    (ID).data + (ID).size -1
#define vectorREnd(ID)      (ID).data - 1

// ........................................................... [] SHRINK TO FIT
#define vectorShrinkToFit(ID) do {                                                  \
    (ID).data = gcRealloc  ( (ID).data   , ((ID).size) * sizeof((ID).data)  );      \
    (ID).capacity = (ID).size;                                                      \
} while (0)    

// ........................................................... [] RESERVE 
#define vectorReserve(ID, N) do {                                                   \
    if ((ID).capacity < (N)) {                                                      \
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );          \
        (ID).capacity = (N);                                                        \
    } \
} while (0)

// ........................................................... [] vectorInsertAtVal     
        
#define vectorInsertAtVal(ID, POS, VAL) do {                                                \
    while ((ID).size + 1 > (ID).capacity) {                                                 \
        (ID).capacity *= 2;                                                                 \
        (ID).data = gcRealloc  ( (ID).data   , (ID).capacity * sizeof((ID).data)  );        \
    } ;                                                                                     \
    memmove((ID).data + POS + 1, (ID).data + POS, ((ID).size - POS) * sizeof((ID).data) );  \
    ++(ID).size;                                                                            \
    (ID).data[POS] = VAL;                                                                   \
} while (0)

// ........................................................... [] ERASE at
                
#define vectorEraseAt(ID, POS) do {                                                         \
    if ( (ID).size ) {                                                                      \
    (ID).size -= 1;                                                                         \
    memmove((ID).data + POS, (ID).data + POS + 1, ((ID).size - POS) * sizeof *(ID).data);   \
    } ;                                                                                     \
} while (0)

    // ........................................................... [] ERASE N
        
#define vectorEraseAtN(ID, POS, N) do {                                                         \
    if ( ((ID).size-(N))>0 ) {                                                                  \
    (ID).size -= (N);                                                                           \
    memmove((ID).data + POS, (ID).data + POS + (N), ((ID).size - POS) * sizeof *(ID).data );    \
    }                                                                                           \
} while (0)

// ........................................................... [] RESIZE
    
#define vectorResize(ID, N, VAL) do {                                       \
    if ((N) > (ID).capacity)                                                \
        (ID).data = gcRealloc ( (ID).data ,  (N) * sizeof((ID).data)   );   \
    if ( (ID).size<(N) )                                                    \
        for (int i = (ID).size; i < (N); ++i) (ID).data[i] = (VAL);         \
    (ID).size = (N);                                                        \
} while (0)

// ........................................................... [] COPY V1 V2 
 
#define vectorCopy(ID, PTR ) do {                                                               \
    while ((ID).size + (PTR).size > (ID).capacity) {                                            \
        (ID).capacity *= 2;                                                                     \
        (ID).data = gcRealloc ( (ID).data , (ID).capacity * sizeof((ID).data)   );              \
    } ;                                                                                         \
    memmove((ID).data + 0 + (PTR).size, (ID).data + 0, ((ID).size - 0) * sizeof *(ID).data);    \
    for (unsigned i = 0; i < (PTR).size; i++)                                                   \
        (ID).data[0 + i] = (PTR).data[0 + i];                                                   \
    (ID).size = (PTR).size;                                                                     \
} while (0)

// ........................................................... [] APPEND 
 
#define vectorAppend(ID, V2 ) do {                                                      \
    unsigned V1z = (ID).size ;                                                          \
    unsigned V2z = (V2).size ;                                                          \
    if ((ID).capacity < (V1z+V2z)) {                                                    \
        (ID).data = gcRealloc ( (ID).data , (V1z + V2z ) *  sizeof((ID).data) ) ;       \
    }                                                                                   \
    (ID).capacity = V1z + V2z ;                                                         \
    while (V2z > 0) {                                                                   \
        (ID).data[ (V1z + V2z - 1) ] = (V2).data[V2z-1];                                \
        --V2z ;                                                                         \
    }                                                                                   \
    (ID).size = (ID).capacity ;                                                         \
} while (0)

// ........................................................... [] insert vector at

#define vectorInsertAtVector(ID, POS, PTR ) do {                                                    \
    while ((ID).size + (PTR).size > (ID).capacity) {                                                \
        (ID).capacity *= 2;                                                                         \
        (ID).data = gcRealloc ( (ID).data , (ID).capacity *  sizeof((ID).data)   );                 \
    }                                                                                               \
    memmove((ID).data + POS + (PTR).size, (ID).data + POS, ((ID).size - POS) * sizeof *(ID).data);  \
    for (unsigned i = 0; i < (PTR).size; i++)                                                       \
        (ID).data[POS + i] = (PTR).data[0 + i];                                                     \
    (ID).size += (PTR).size;                                                                        \
} while (0)


// ........................................................... [] vectorInsertAtVectorFromN( v1, POS1, v2 , POS2 , N )

#define vectorInsertAtVectorFromN(ID, POS, PTR , POS2 , N) do {                                     \
    while ((ID).size + (N) > (ID).capacity) {                                                       \
        (ID).capacity *= 2;                                                                         \
        (ID).data = gcRealloc ( (ID).data , (ID).capacity *  sizeof((ID).data)  );                  \
    } ;                                                                                             \
    memmove((ID).data + POS + (N), (ID).data + POS, ((ID).size - POS) * sizeof *(ID).data);         \
    for (unsigned i = 0; i < (N); i++)                                                              \
        (ID).data[POS + i] = (PTR).data[POS2 + i];                                                  \
    (ID).size += (N);                                                                               \
} while (0)
    
// ........................................................... [] FREE 

#define vectorFree(ID) do {                           \
    if ( (ID).data != NULL ) gcFree( (ID).data );     \
} while(0)
    
// ........................................................... [] SORT 

#define vectorSort(ID,CMP)  qsort((ID).data, (ID).size, sizeof(vectorDataType ## ID), CMP )  


/**/


#endif

 
/**/

