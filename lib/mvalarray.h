#ifndef cdVALARRAY
#define cdVALARRAY

#include "gc.h"

#include <math.h>

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

// ........................................................... [] valArray(TYPE) 
#include <stdio.h>
#include <stdlib.h>

#define valArrayType(TYPE,ID)                       \
typedef TYPE valArrayDataType ## ID;                \
typedef struct TYPEOF ( valArray_s_ , ID )          \
{                                                   \
    TYPE*   data ;                                  \
    size_t  size        ;                           \
}  TYPEOF ( valArray_ , ID ) ;                      \
TYPEOF ( valArray_ , ID ) ID

// ........................................................... [] valArrayNew(ID,N) 
 
#define valArrayNew(ID,N)                                                    \
(ID).data = (valArrayDataType ## ID*) gcMalloc (  sizeof((ID).data) * N);    \
(ID).size      = N;

// ........................................................... [] ITERATOR 

#define itvalArray(ID)        valArrayDataType ## ID*  
#define itValArray(ID)        valArrayDataType ## ID* 
 
#define valArrayBegin(ID)       (((ID).data))
#define valArrayEnd(ID)         (((ID).data + (ID).size)) 
#define valArrayRBegin(ID)      ((ID).data  + (ID).size - 1)
#define valArrayREnd(ID)        ((ID).data  - 1)

// ........................................................... [] ARRAY INDEX

#define valArrayIndex(ID,lambda,X)\
for(size_t index=0;index<(ID).size;index++)\
{\
 if ( (lambda) ) (ID).data[index] = (X) ;\
}

// ........................................................... [] ARRAY ITERATOR

#define valArrayIterator(ID,lambda,X)\
for( valArrayDataType ## ID* it=valArrayBegin(ID);it!=valArrayEnd(ID);it++)\
{\
 if ( lambda ) *it = (X) ;\
}

// ........................................................... [] RESIZE
    
#define valArrayResize(ID, N, VAL) do {                                                             \
    (ID).data =  (valArrayDataType ## ID*) gcRealloc ( (ID).data ,  (N) * sizeof((ID).data)   );    \
    if ( (ID).size<(N) )                                                                            \
        for (int i = (ID).size; i < (N); ++i) (ID).data[i] = (VAL);                                 \
    (ID).size = (N);                                                                                \
} while (0)

// ........................................................... [] UNARY  -

#define valArrayUnaryOp(OP,ID)\
for( valArrayDataType ## ID* it=valArrayBegin(ID);it!=valArrayEnd(ID);it++)\
{\
  *it = OP*it;\
}

// ........................................................... [] BIN OP ARRAY

#define valArrayBinOpArray(ID,OP,VA2)\
if ( ID.size == VA2.size )\
    for(size_t index=0;index<(ID).size;index++)\
    {\
      (ID).data[index] = (ID).data[index] OP (VA2).data[index] ;\
    }

// ........................................................... [] BIN OP VAL
    
#define valArrayBinOpVal(ID,OP,VAL)\
    for(size_t index=0;index<(ID).size;index++)\
    {\
      (ID).data[index] = (ID).data[index] OP VAL ;\
    }
   
// ........................................................... [] CLEAR
#define valArrayClear(ID) do {  \
    (ID).size = 0;              \
} while (0)

// ........................................................... [] DATA

#define valArrayData(ID) (ID).data

// ........................................................... [] AT 

#define valArrayAt(ID, INDEX) (ID).data[INDEX]   

// ........................................................... [] FOREACH

#define valArrayForEach(ID,X)\
for( valArrayDataType ## ID* it=valArrayBegin(ID);it!=valArrayEnd(ID);it++)\
{\
 *it = (X) ;\
}

// ........................................................... [] SWAP

#define valArraySwap(ID,VA2)\
if ( ID.size == VA2.size )\
    for(size_t index=0;index<(ID).size;index++)\
    {\
      valArrayDataType ## ID temp ;\
      temp              = (ID).data[index]  ;\
      (ID).data[index]  = (VA2).data[index] ;\
      (VA2).data[index] = temp ;\
    }
// ........................................................... [] SUM 
   
#define valArraySum(ID,sum)\
do{\
    valArrayDataType ## ID* it=valArrayBegin(ID);\
    sum=*it++;\
    for( ; it!=valArrayEnd(ID) ; it++)   sum += *it;\
} while(0);

// ........................................................... [] MIN 

#define valArrayMin(ID,min)\
do{\
    valArrayDataType ## ID* it=valArrayBegin(ID);\
    min=*it++;\
    for( ; it!=valArrayEnd(ID) ; it++)   if (*it<min) min=*it;\
} while(0);

// ........................................................... [] MAX

#define valArrayMax(ID,max)\
do{\
    valArrayDataType ## ID* it=valArrayBegin(ID);\
    max=*it++;\
    for( ; it!=valArrayEnd(ID) ; it++)   if (*it>min) max=*it;\
} while(0);

// ........................................................... [] APPLAY 

#define valArrayApply(ID,lambda)\
for( valArrayDataType ## ID* it=valArrayBegin(ID);it!=valArrayEnd(ID);it++)\
{\
 *it = lambda ;\
}

// ........................................................... [] FREE 

#define valArrayFree(ID) do {                           \
    if ( (ID).data != NULL ) gcFree( (ID).data );       \
} while(0)
    
// ........................................................... [] SORT 

#define valArraySort(ID,CMP)  qsort((ID).data, (ID).size, sizeof( valArrayDataType ## ID), CMP )  

// ........................................................... [] Left Shift <<

#define valArrayLeftShift(ID,N,FILL)\
do{\
    for(size_t i=N          ;i<(ID).size  ;i++)\
    {\
       (ID).data[i-N] = (ID).data[i] ;\
    }\
    for(size_t i=(ID).size-N;i<(ID).size    ;i++)\
    {\
        (ID).data[i]=FILL;\
    }\
}while(0);    

// ........................................................... [] right Shift >>
 
#define valArrayRightShift(ID,N,FILL)\
do{\
    for(size_t i=0  ;   i<(ID).size-N   ;i++)\
    {\
       (ID).data[i+N] = (ID).data[i] ;\
    }\
    for(size_t i=0  ;   i<N             ;i++)\
    {\
        (ID).data[i]=FILL;\
    }\
}while(0); 

// ........................................................... [] Circular Left Shift <<

#define valArrayCLeftShift(ID,N)\
do{\
    size_t count=N;\
    while(count--)\
    {\
        valArrayDataType ## ID temp = (ID).data[0];\
        for(size_t i=1          ;i<(ID).size  ;i++)\
        {\
           (ID).data[i-1] = (ID).data[i] ;\
        }\
        (ID).data[(ID).size-1]=temp;\
    };\
}while(0);  

// ........................................................... [] Circular Right Shift >>

#define valArrayCRightShift(ID,N)\
do{\
    size_t count=N;\
    while(count--)\
    {\
        valArrayDataType ## ID temp = (ID).data[(ID).size-1];\
        for(size_t i=(ID).size-1          ;i>0  ;i--)\
        {\
           (ID).data[i] = (ID).data[i-1] ;\
        }\
        (ID).data[0]=temp;\
    };\
}while(0); 
 
// ................................................................. slice / gslice

#define sliceType(ID,...)   const unsigned int ID[]={__VA_ARGS__}
     

#define sliceX(s,x)             (x)    
#define sliceXY(s,x,y)          (x*s[1]+y)
#define sliceXYZ(s,x,y,z)       (x*s[2]*s[1] + (y*s[1]) + z)
#define sliceXYZW(s,x,y,z,w)    (x*s[3]*s[2]*s[1]   + y*s[2]*s[1] + (z*s[1]) + w)

#define gsliceX(ID,s,begin,x)              (*(((valArrayDataType ## ID*)begin) + (x)))    
#define gsliceXY(ID,s,begin,x,y)           (*(((valArrayDataType ## ID*)begin) + (x*s[1]+y)))
#define gsliceXYZ(ID,s,begin,x,y,z)        (*(((valArrayDataType ## ID*)begin) + (x*s[2]*s[1] + (y*s[1]) + z)))
#define gsliceXYZW(ID,s,begin,x,y,z,w)     (*(((valArrayDataType ## ID*)begin) + (x*s[3]*s[2]*s[1]   + y*s[2]*s[1] + (z*s[1]) + w)))


 
/**/



#endif


/**/


