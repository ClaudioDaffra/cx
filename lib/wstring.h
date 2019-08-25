#ifndef mwstring
#define mwstring

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#include <stdlib.h>
#include <wchar.h>
#include <stdint.h>
#include <stdarg.h>

#include "stdio.h"

// ........................................................... [v] TYPEOF
#define wstringDefaultAlloc  32
  
// ........................................................... [v] wstring(TYPE) 
#define wstr(ID) (ID).data
                    
typedef struct wstring_s            
{                                                  
    wchar_t*    data        ;                                   
    size_t      size        ;                           
    size_t      capacity    ;                           
} wstring_t ;  

#define wstringType(ID)  ;                                                          \
typedef wchar_t dataType_ ## ID ;                                                   \
wstring_t ID ;                                                                      \
(ID).data       = (wchar_t*) gcMalloc (   sizeof(wchar_t) * wstringDefaultAlloc );  \
(ID).size       = 0;                                                                \
(ID).capacity   = wstringDefaultAlloc;                                              \
(ID).data[0]    = 0;



// ........................................................... [v] NEW
void wstringNew_ ( wstring_t* ID , size_t N ) ;
#define wstringNew( ID,N ) wstringNew_( &ID,N );

// ........................................................... [v] SIZE
#define wstringSize(ID) (ID).size
#define wstringLength(ID) wcslen((ID).data)

// ........................................................... [v] CAPACITY
#define wstringCapacity(ID) (ID).capacity

// ........................................................... EMPTY
#define wstringEmpty(ID) ((ID).size == 0) 

// ........................................................... [v] PUSH BACK
void wstringPushBack_(wstring_t* ID, wchar_t VAL) ;
#define wstringPushBack( ID,N ) wstringPushBack_( &ID,N );

// ........................................................... [v] POP_BACK
#define wstringPopBack(ID) do { \
    if ((ID).size) { (ID).data[ (ID).size-1 ]=0; --(ID).size; }\
} while (0)

// ........................................................... CLEAR
#define wstringClear(ID) do { \
    (ID).size = 0; \
} while (0)

// ........................................................... [v] DATA
#define wstringData(ID) (ID).data

// ........................................................... [v] AT
#define wstringAt(ID, INDEX) (ID).data[INDEX]

// ........................................................... FRONT
#define wstringFront(ID) (ID).data[0]

// ........................................................... BACK 
#define wstringBack(ID) (ID).data[wstringSize(ID) - 1]
 
// ........................................................... FREE 
#define wstringFree(ID) do { \
    if ( (ID).data != NULL ) gcFree (   (ID).data ); \
} while(0)

// ........................................................... [] ITERATOR 

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef TYPEOF
#define TYPEOF(x,y)    CONCATENATE(x,y)
#endif

#ifndef iterator
#define iterator(ID)        TYPEOF(dataType_ ,ID)*  
#endif
#define itWString   iterator
 
#define wstringBegin(ID)     (ID).data
#define wstringEnd(ID)       (ID).data + (ID).size 

#define wstringRBegin(ID)    (ID).data + (ID).size -1
#define wstringREnd(ID)      (ID).data - 1    

// ........................................................... [v] SHRINK TO FIT
void wstringShrinkToFit_(wstring_t* ID) ;
#define wstringShrinkToFit(ID)   wstringShrinkToFit_(&ID)

// ........................................................... [v] RESERVE 

void wstringReserve_(wstring_t* ID, size_t N) ;
#define wstringReserve(ID,N) wstringReserve_(&ID,N)
   
// ........................................................... [v] wstringInsertAtVal     
        
void wstringInsertAtVal_(wstring_t* ID, size_t POS, wchar_t VAL ) ;
#define wstringInsertAtVal(ID,POS,VAL) wstringInsertAtVal_(&ID,POS,VAL) 

// ........................................................... [v] ERASE at
                
void wstringEraseAt_(wstring_t*ID, size_t POS) ;
#define  wstringEraseAt(ID,POS) wstringEraseAt_(&ID,POS)

// ........................................................... [v] ERASE N
        
void wstringEraseAtN_(wstring_t* ID, size_t POS, size_t N) ;
#define wstringEraseAtN( ID, POS, N) wstringEraseAtN_( &ID, POS, N)
 
// ........................................................... [v] RESIZE
    
void wstringResize_( wstring_t* ID, size_t N, wchar_t VAL) ;
#define wstringResize(ID,N,VAL) wstringResize_(&ID,N,VAL)

// ........................................................... COPY V1 V2 

void wstringCopy_( wstring_t*ID, wstring_t*PTR ) ;
#define wstringCopy(ID,PTR) wstringCopy_(&ID,&PTR)

// ........................................................... APPEND 
 
void wstringAppend_(wstring_t* ID, wstring_t*V2 ) ;
#define wstringAppend(ID,V2) wstringAppend_(&ID,&V2)

// ........................................................... insert wstring at

void wstringInsertAtwstring_(wstring_t*ID, size_t POS, wstring_t*PTR ) ;
#define wstringInsertAtwstring( ID, POS, PTR ) wstringInsertAtwstring_( &ID, POS, &PTR )

// ........................................................... wstringInsertAtwstringFromN(v1, POS1, v2 , POS2 , N)

void wstringInsertAtwstringFromN_(wstring_t*ID, size_t POS, wstring_t*PTR , size_t POS2 , size_t N) ;
#define wstringInsertAtwstringFromN( ID,  POS, PTR , POS2 ,  N) wstringInsertAtwstringFromN_( &ID,  POS, &PTR , POS2 ,  N)    

/**/

// ........................................................... wstringFindChar 0...size_t pos , -1 no

size_t wstringFindChar_(wstring_t*ID, wchar_t VAL ) ;
#define wstringFindChar( ID,VAL ) (wstringFindChar_(&ID,VAL)-1)

// ........................................................... wstringFromStrC

size_t wstringFromStrC_(wstring_t*ID, const wchar_t *strc ) ;
#define wstringFromStrC(ID,VAL) wstringFromStrC_(&ID,VAL)
  
// ........................................................... wstringToStrC

wchar_t* wstringToStrC_(wstring_t*ID) ;
#define wstringToStrC(ID) wstringToStrC_(&ID) 

// ........................................................... wstringFindStrC (iterator)

wchar_t* wstringFindStrC_(wstring_t*ID,wchar_t*s2) ;
#define wstringFindStrC(s1,s2) wstringFindStrC_(&s1,s2)
 
// ........................................................... wstringFindwstring 

wchar_t* wstringFindwstring_(wstring_t*s1,wstring_t*s2) ;
#define wstringFindwstring(s1,s2) wstringFindwstring_(&s1,&s2)

// ........................................................... wstringReplace

void wstringReplaceStrC_     ( wstring_t* ID, const wchar_t *oldW,const wchar_t *newW) ;
#define wstringReplaceStrC(ID,OLD,NEW) wstringReplaceStrC_(&ID,OLD,NEW)
 
 
void wstringReplaceWString_   ( wstring_t* ID, wstring_t* oldW,wstring_t* newW) ;
#define wstringReplaceWString(ID,OLD,NEW) wstringReplaceWString_(&ID,&OLD,&NEW) 

// ........................................................... wstringPrint
 
void wstringPrint_   ( wstring_t* ID ) ;
#define wstringPrint(ID) wstringPrint_(&ID)

// ........................................................... wstringCompare
#define wstringCompare(ID1,ID2) wcscmp(ID1.data,ID2.data)

// ........................................................... wstringNCompareN
#define wstringCompareN(ID1,ID2,n) wcsncmp(ID1.data,ID2.data,n)


// ........................................................... [] string From

/*  WSTRING

    qui il problema è triplice :
    1) visual studio gestisce i long double come double
    2) per sopperire a questo MINGW32 ha scritto delle proprie routine
    3) snwprintf/snprintf , swprintf/snprintf implementazione non standard
    
    per tanto a seconda che ci troviamo su windows/linux o su cl/gcc/mingw
    dovremo per tanto gestire la situazione diversamente.
*/

#if defined(__USE_MINGW_ANSI_STDIO)

    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)

        #define wstringFromNumber(ID,suffix,val) do {                           \
            size_t size = snwprintf(NULL,0,L"" suffix, val );                   \
            (ID).data = gcRealloc ( (ID).data , (size+2)*sizeof(wchar_t) );     \
            snwprintf( (ID).data, size+1, L"" suffix, val );                    \
            (ID).size        = size ;                                           \
            (ID).capacity    = size ;                                           \
            (ID).data[size+1]=0;                                                \
        } while(0); 

    #endif

#else

    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)

        #define wstringFromNumber(ID,suffix,val) do {                           \
            size_t size = swprintf(NULL, 0 ,L"" suffix, val );                  \
            (ID).data = gcRealloc ( (ID).data , (size+1)*sizeof(wchar_t) );     \
            swprintf( (ID).data, size+1, L"" suffix, val );                     \
            (ID).size        = size ;                                           \
            (ID).capacity    = size ;                                           \
            (ID).data[size]=0;                                                  \
        } while(0); 

    #endif

#endif


#if defined(__linux__) 

    #define wstringFromNumber(ID,suffix,val) do {                                       \
        if ((ID).capacity<128) (ID).data=gcRealloc( (ID).data , 128*sizeof(wchar_t) );  \
        size_t size=swprintf( (ID).data, 128 , L"" suffix, val );                       \
        (ID).data = gcRealloc ( (ID).data , (size+2)*sizeof(wchar_t) );                 \
        (ID).size        = size ;                                                       \
        (ID).capacity    = size  ;                                                      \
        (ID).data[size]=0;                                                              \
    } while(0);

#endif

void wstringFormat_( wstring_t* ID,const wchar_t* format,...) ; 
#define wstringFormat(ID,FORMAT,...) wstringFormat_( &ID , L"" FORMAT , __VA_ARGS__ );

#define wstringToSigned( ID , BASE ) wcstoll( (ID).data , NULL , BASE )
#define wstringToInteger wstringToSigned

#define wstringToUnsigned( ID , BASE ) wcstoull( (ID).data , NULL , BASE )

#define wstringToReal( ID )  wcstold( (ID).data , NULL )

#endif /* mwstring */



/**/


