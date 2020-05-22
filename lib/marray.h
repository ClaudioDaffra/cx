#ifndef marray
#define marray

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

// ........................................................... [] array(TYPE) 

// array_v1_int    (int)
// array_v1

#define arrayType(TYPE,ID)                          \
typedef TYPE arrayDataType ## ID;                   \
typedef TYPE arrayDataType_ ## TYPE;                \
typedef struct TYPEOF ( array_s_ , ID )             \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
}  TYPEOF ( array_ , ID ) ;                         \
TYPEOF ( array_ , ID ) ID

// ........................................................... [] array def in struct

#define arrayDataType(TYPE,ID) typedef TYPE arrayDataType ## ID;  

#define arrayStruct(TYPE,ID)                        \
struct TYPEOF ( array_s_ , ID )                     \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
}  ID 

// ........................................................... [] arrayNew(ID,N) 
 
#define arrayNew(ID,N)                                                      \
(ID).data = (void*) gcMalloc (  sizeof((ID).data) * N);                     \
(ID).size      = N;    

// ........................................................... [] arrayDim(TYPE,ID,N) 
#define arrayDim(TYPE,ID,N) \
arrayType(TYPE,ID);         \
arrayNew(ID,N);    

// ........................................................... [] SIZE
#define arraySize(ID) (ID).size

// ........................................................... EMPTY
#define arrayEmpty(ID) ((ID).size == 0) 
 
// ........................................................... [] CLEAR
#define arrayClear(ID) do {    \
    (ID).size = 0;             \
} while (0)

// ........................................................... [] DATA
#define arrayData(ID) (ID).data

// ........................................................... [] array pointer DATA
#define arrayPointerData(ID,NDX) *(ID.data[NDX])

// ........................................................... [] arrayPointerClone
#define arrayPointerClone(ID,ARR,N) do{\
for(size_t i=0;i<N;i++)\
{\
    (ID).data[i] = &ARR.data[i] ;\
}\
}while(0);

// ........................................................... [] arrayPointerVoidAt(ID,NDX1,NDX2)

#define arrayPointerVoidAt(ID,NDX1,NDX2) (* ((array_##ID*) ID[NDX1].data[NDX2])   )

// ........................................................... [] AT 
#define arrayAt(ID, INDEX) (ID).data[INDEX]    

// ........................................................... [] arrayOfarray ... X , XY , XYZ
    
#define arrayX(ID,NDX1)                arrayAt(ID,NDX1)
#define arrayXY(ID,NDX1,NDX2)          arrayAt(arrayAt(ID,NDX1),NDX2)
#define arrayXYZ(ID,NDX1,NDX2,NDX3)    arrayAt(arrayAt(arrayAt(ID,NDX1),NDX2),NDX3)

// ........................................................... [] FRONT
#define arrayFront(ID) (ID).data[0]

// ........................................................... [] BACK 
#define arrayBack(ID) (ID).data[arraySize(ID) - 1]

// ........................................................... [] ITERATOR 
#define itArray(ID)        arrayDataType ## ID*  
 
#define arrayBegin(ID)     (ID).data
#define arrayEnd(ID)       (ID).data + (ID).size 

#define arrayRBegin(ID)    (ID).data + (ID).size -1
#define arrayREnd(ID)      (ID).data - 1

// ........................................................... [] COPY V1 V2 
 
#define arrayCopy(ID, PTR ) do {                                                \
    (ID).data = gcRealloc ( (ID).data , (PTR).size * sizeof((ID).data)   );     \
    for (unsigned i = 0; i < (PTR).size; i++)                                   \
        (ID).data[0 + i] = (PTR).data[0 + i];                                   \
    (ID).size = (PTR).size;                                                     \
} while (0)

// ........................................................... [] FILL 
 
#define arrayFill(ID, VAL ) do {                    \
    for (unsigned i = 0; i < (ID).size; i++)        \
        (ID).data[i] = VAL;                         \
} while (0)
    
// ........................................................... [] FREE 

#define arrayFree(ID) do {                          \
    if ( (ID).data != NULL ) gcFree( (ID).data );   \
} while(0)


// ........................................................... [] SORT 

#define arraySort(ID,CMP)  qsort((ID).data, (ID).size, sizeof(arrayDataType ## ID), CMP )


/**/

   
#endif


/**/

