#ifndef mstring
#define mstring

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#include "stdio.h"

// ........................................................... [v] TYPEOF
#define stringDefaultAlloc  32
  
// ........................................................... [v] string(TYPE) 
#define str(ID) (ID).data
                    
typedef struct string_s            
{                                                  
    char*   data ;                                   
    size_t  size        ;                           
    size_t  capacity    ;                           
} string_t ;  

#define stringType(ID)  ;                                                       \
typedef char dataType_ ## ID ;                                                  \
string_t ID ;                                                                   \
(ID).data       = (char*) gcMalloc (   sizeof(char) * stringDefaultAlloc );     \
(ID).size       = 0;                                                            \
(ID).capacity   = stringDefaultAlloc;                                           \
(ID).data[0]=0;



// ........................................................... [v] NEW
void stringNew_ ( string_t* ID , size_t N ) ;
#define stringNew( ID,N ) stringNew_( &ID,N );

// ........................................................... [v] SIZE
#define stringSize(ID)   (ID).size
#define stringLength(ID) strlen((ID).data)

// ........................................................... [v] CAPACITY
#define stringCapacity(ID) (ID).capacity

// ........................................................... EMPTY
#define stringEmpty(ID) ((ID).size == 0) 

// ........................................................... [v] PUSH BACK
void stringPushBack_(string_t* ID, char VAL) ;
#define stringPushBack( ID,N ) stringPushBack_( &ID,N );

// ........................................................... [v] POP_BACK
#define stringPopBack(ID) do { \
    if ((ID).size) { (ID).data[ (ID).size-1 ]=0; --(ID).size; }\
} while (0)

// ........................................................... CLEAR
#define stringClear(ID) do { \
    (ID).size = 0; \
} while (0)

// ........................................................... [v] DATA
#define stringData(ID) (ID).data

// ........................................................... [v] AT
#define stringAt(ID, INDEX) (ID).data[INDEX]

// ........................................................... FRONT
#define stringFront(ID) (ID).data[0]

// ........................................................... BACK 
#define stringBack(ID) (ID).data[stringSize(ID) - 1]
 
// ........................................................... [v] FREE 
#define stringFree(ID) do { \
    if ( (ID).data != NULL ) gcFree (   (ID).data ); \
} while(0)

// ........................................................... [v] ITERATOR 

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef TYPEOF
#define TYPEOF(x,y)    CONCATENATE(x,y)
#endif

#ifndef iterator
#define iterator(ID)        TYPEOF(dataType_ ,ID)*  
#endif
#define itString    iterator
  
#define stringBegin(ID)     (ID).data
#define stringEnd(ID)       (ID).data + (ID).size 

#define stringRBegin(ID)    (ID).data + (ID).size -1
#define stringREnd(ID)      (ID).data - 1    

// ........................................................... [v] SHRINK TO FIT
void stringShrinkToFit_(string_t* ID) ;
#define stringShrinkToFit(ID)   stringShrinkToFit_(&ID)

// ........................................................... [v] RESERVE 

void stringReserve_(string_t* ID, size_t N) ;
#define stringReserve(ID,N) stringReserve_(&ID,N)
   
// ........................................................... [v] stringInsertAtVal     
        
void stringInsertAtVal_(string_t* ID, size_t POS, char VAL ) ;
#define stringInsertAtVal(ID,POS,VAL) stringInsertAtVal_(&ID,POS,VAL) 

// ........................................................... [v] ERASE at
                
void stringEraseAt_(string_t*ID, size_t POS) ;
#define  stringEraseAt(ID,POS) stringEraseAt_(&ID,POS)

// ........................................................... [v] ERASE N
        
void stringEraseAtN_(string_t* ID, size_t POS, size_t N) ;
#define stringEraseAtN( ID, POS, N) stringEraseAtN_( &ID, POS, N)
 
// ........................................................... [v] RESIZE
    
void stringResize_( string_t* ID, size_t N, char VAL) ;
#define stringResize(ID,N,VAL) stringResize_(&ID,N,VAL)

// ........................................................... [v] COPY V1 V2 

void stringCopy_( string_t*ID, string_t*PTR ) ;
#define stringCopy(ID,PTR) stringCopy_(&ID,&PTR)

// ........................................................... [v] APPEND 
 
void stringAppend_(string_t* ID, string_t*V2 ) ;
#define stringAppend(ID,V2) stringAppend_(&ID,&V2)

// ........................................................... [v] insert string at

void stringInsertAtString_(string_t*ID, size_t POS, string_t*PTR ) ;
#define stringInsertAtString( ID, POS, PTR ) stringInsertAtString_( &ID, POS, &PTR )

// ........................................................... [v] stringInsertAtstringFromN(v1, POS1, v2 , POS2 , N)

void stringInsertAtStringFromN_(string_t*ID, size_t POS, string_t*PTR , size_t POS2 , size_t N) ;
#define stringInsertAtStringFromN( ID,  POS, PTR , POS2 ,  N) stringInsertAtStringFromN_( &ID,  POS, &PTR , POS2 ,  N)    

/**/

// ........................................................... [v] stringFindChar 0...size_t pos , -1 no

size_t stringFindChar_(string_t*ID, char VAL ) ;
#define stringFindChar( ID,VAL ) (stringFindChar_(&ID,VAL)-1)

// ........................................................... [v] stringFromStrC

size_t stringFromStrC_(string_t*ID, const char *strc ) ;
#define stringFromStrC(ID,VAL) stringFromStrC_(&ID,VAL)
  
// ........................................................... [v] stringToStrC

char* stringToStrC_(string_t*ID) ;
#define stringToStrC(ID) stringToStrC_(&ID) 

// ........................................................... stringFindStrC (iterator)

char* stringFindStrC_(string_t*ID,char*s2) ;
#define stringFindStrC(s1,s2) stringFindStrC_(&s1,s2)
 
// ........................................................... stringFindString 

char* stringFindString_(string_t*s1,string_t*s2) ;
#define stringFindString(s1,s2) stringFindString_(&s1,&s2)

// ........................................................... stringReplace

void stringReplaceStrC_     ( string_t* ID, const char *oldW,const char *newW) ;
#define stringReplaceStrC(ID,OLD,NEW) stringReplaceStrC_(&ID,OLD,NEW)
 
 
void stringReplaceString_   ( string_t* ID, string_t* oldW,string_t* newW) ;
#define stringReplaceString(ID,OLD,NEW) stringReplaceString_(&ID,&OLD,&NEW) 

// ........................................................... stringPrint
 
void stringPrint_   ( string_t* ID ) ;
#define stringPrint(ID) stringPrint_(&ID)

// ........................................................... stringCompare
#define stringCompare(ID1,ID2) strcmp(ID1.data,ID2.data)

// ........................................................... stringNCompareN
#define stringCompareN(ID1,ID2,n) strncmp(ID1.data,ID2.data,n)

// ........................................................... [] string From

/*  STRING

    qui il problema è triplice :
    1) visual studio gestisce i long double come double
    2) per sopperire a questo MINGW32 ha scritto delle proprie routine
    3) snwprintf/snprintf , swprintf/snprintf implementazione non standard
    
    per tanto a seconda che ci troviamo su windows/linux o su cl/gcc/mingw
    dovremo per tanto gestire la situazione diversamente.
*/

#if defined(__USE_MINGW_ANSI_STDIO)

    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)

        #define stringFromNumber(ID,suffix,val) do {                            \
            size_t size = snprintf(NULL,  0,suffix, val );                      \
            (ID).data = gcRealloc ( (ID).data , (size+2)*sizeof(char) );        \
            snprintf( (ID).data,size+1,suffix, val );                           \
            (ID).size        = size ;                                           \
            (ID).capacity    = size ;                                           \
            (ID).data[size+1]=0;                                                \
        } while(0);

    #endif

#else

    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)

        #define stringFromNumber(ID,suffix,val) do {                            \
            size_t size = snprintf(NULL,  0,suffix, val );                      \
            (ID).data = gcRealloc ( (ID).data , (size+1)*sizeof(char) );        \
            snprintf( (ID).data,size+1,suffix, val );                           \
            (ID).size        = size ;                                           \
            (ID).capacity    = size ;                                           \
            (ID).data[size]=0;                                                  \
        } while(0);

    #endif

#endif


#if defined(__linux__) 

    #define stringFromNumber(ID,suffix,val) do {                        \
        size_t size = snprintf(NULL,  0,suffix, val );                  \
        (ID).data = gcRealloc ( (ID).data , (size+2)*sizeof(char) );    \
        snprintf( (ID).data,size+1,suffix, val );                       \
        (ID).size        = size ;                                       \
        (ID).capacity    = size ;                                       \
        (ID).data[size+1]=0;                                            \
    } while(0);

#endif
 
void stringFormat_( string_t* ID,const char* format,...) ;
#define stringFormat(ID,FORMAT,...)  stringFormat_( &ID , FORMAT , __VA_ARGS__ );
 
 
#define stringToSigned( ID , BASE ) strtoll( (ID).data , NULL , BASE )
#define stringToInteger stringToSigned

#define stringToUnsigned( ID , BASE ) strtoull( (ID).data , NULL , BASE )

#define stringToReal( ID )  strtold( (ID).data , NULL )
 
 
#endif /* mstring */


/**/





