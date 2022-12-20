#ifndef marray
#define marray

//.................................................... [] array(TYPE) 

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

// arrayTypeDef(TYPE,ID)

/*
    array_ID_d            :   TYPE
    ID_d                   :   TYPE
    array_ID_s            :   struct array_ID_s
    array_ID_t            :   array_ID_s
    array_ID_p            :   array_ID_t*
*/

#define arrayTypeDef(TYPE,ID)                          \
typedef TYPE MERGE ( MERGE ( array_ , ID )  , _d );    \
typedef TYPE MERGE ( ID  , _d );                       \
typedef struct MERGE ( MERGE ( array_ , ID )  , _s )   \
{                                                      \
    TYPE*   data ;                                     \
    size_t  size        ;                              \
}  MERGE ( MERGE ( array_ , ID )  , _t ) ;             \
typedef MERGE ( MERGE ( array_ , ID )  , _t ) * MERGE ( MERGE ( array_ , ID )  , _p )

// arrayType(TYPE,ID) :  generic array

#define arrayType(TYPE)    arrayTypeDef(TYPE,TYPE)

// ........................................................... [] arrayAlloc(ID,N) 
 
#define arrayAlloc(ID,N)                                   \
(ID).data = (void*) gcMalloc ( sizeof((ID).data) * N );    \
assert((ID).data!=NULL);                                   \
(ID).size      = N;

  
// ........................................................... [] SIZE

#define arraySize(ID) ((ID).size)

// ........................................................... [] EMPTY

#define arrayEmpty(ID) ((ID).size == 0) 

// ........................................................... [] CLEAR

#define arrayClear(ID) do {     \
    (ID).size = 0;              \
} while (0)

// ........................................................... [] DATA

#define arrayData(ID) (ID).data

// ........................................................... [] get AT 

#define arrayGetAt(ID, INDEX) (ID).data[INDEX]

// ........................................................... [] set AT 

#define arraySetAt(ID, INDEX) ID.data[INDEX]

// ........................................................... [] arrayOfarray ... X , XY , XYZ

#define arrayAt(ID, INDEX) (ID).data[INDEX]

#define arrayX(ID,NDX1)                arrayAt(ID,NDX1)
#define arrayXY(ID,NDX1,NDX2)          arrayAt(arrayAt(ID,NDX1),NDX2)
#define arrayXYZ(ID,NDX1,NDX2,NDX3)    arrayAt(arrayAt(arrayAt(ID,NDX1),NDX2),NDX3)

// ........................................................... [] FRONT

#define arrayFront(ID) (ID).data[0]

// ........................................................... [] BACK 

#define arrayBack(ID) (ID).data[arraySize(ID) - 1]

// ........................................................... [] ITERATOR 

#define itArray(ID)        MERGE ( MERGE ( array_ , ID )  , _d )*  
 
#define arrayBegin(ID)     (ID).data
#define arrayEnd(ID)       ((ID).data+(ID).size) 

#define arrayRBegin(ID)    ((ID).data + (ID).size - 1)
#define arrayREnd(ID)      ((ID).data - 1 )


// ........................................................... [] PRINTF

#define arrayPrintf(FORMAT,ID) do {                                                  \
for ( size_t i = 0 ; i < (ID).size ; i++)  printf ( FORMAT , (ID).data[i] ) ;        \
}while(0);

// ........................................................... [] FREE 

#define arrayDealloc(ID) do {                         \
    if ( (ID).data != NULL ) gcFree( (ID).data );     \
} while(0)

// ........................................................... [] SORT 

#define arraySort(TYPE,ID,CMP)  qsort((ID).data, (ID).size, sizeof(TYPE), CMP )  

// ........................................................... [] BINARY SEARCH 

#define arrayBinarySearch(TYPE,ID,CMP,KEY)  bsearch (&KEY, (ID).data, (ID).size , sizeof (TYPE), CMP) 

// ........................................................... [] FILL 
 
#define arrayFill(ID, VAL ) do {                    \
    for (unsigned i = 0; i < (ID).size; i++)        \
        (ID).data[i] = VAL;                         \
} while (0)

#endif

// ........................................................... [] COPY V1 V2 
 
#define arrayCopy(ID, PTR ) do {                                                \
    (ID).data = gcRealloc ( (ID).data , (PTR).size * sizeof((ID).data)   );     \
    for (unsigned i = 0; i < (PTR).size; i++)                                   \
        (ID).data[0 + i] = (PTR).data[0 + i];                                   \
    (ID).size = (PTR).size;                                                     \
} while (0)
 
/**/


