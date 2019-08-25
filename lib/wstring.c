#include "wstring.h"
#include <stdio.h>
#include <stdint.h>
#include "gc.h"
#include <stdio.h>

// ........................................................... [] wstringNew

void wstringNew_ ( wstring_t* ID , size_t N )
{
    ID->data = (wchar_t*)  gcRealloc ( ID->data , N  * sizeof(wchar_t)  ) ; 
    ID->size       = 0;         
    ID->capacity   = N;        
}

// ........................................................... [] wstringPushBack

void wstringPushBack_(wstring_t* ID, wchar_t VAL)
{
    if (ID->size + 2 > ID->capacity) 
    {  
        size_t n = ID->capacity * 2;  
        ID->data = (wchar_t*) gcRealloc (  ID->data, n * sizeof(wchar_t) +2  );  
        ID->capacity = n;  
    }  
    ID->data[ID->size]     = (VAL); 
    ID->data[ID->size+1]   = L'\0';     
    ID->size += 1;  
}  

// ........................................................... [] SHRINK TO FIT

void wstringShrinkToFit_(wstring_t* ID)
{                                                                          
    ID->data = (wchar_t*) gcRealloc (  ID->data, ID->size * sizeof(wchar_t) );   
    ID->capacity = ID->size;                                                                              
}

// ........................................................... [] RESERVE 

void wstringReserve_(wstring_t* ID, size_t N)
{
    if (ID->capacity < N) 
    { 
        ID->data = (wchar_t*) gcRealloc (  ID->data , N * sizeof(wchar_t) ); 
        ID->capacity = N; 
    } 
}

// ........................................................... [] wstringInsertAtVal     
        
void wstringInsertAtVal_(wstring_t* ID, size_t POS, wchar_t VAL )
{
    wchar_t*  pNew ; 

    if (ID->size + 1 > ID->capacity) ID->capacity *= 2;
                                                                                     
    pNew = (wchar_t*) gcMalloc ( ID->capacity * sizeof(wchar_t)  );  
  
    memmove( pNew       , ID->data         , POS                * sizeof (VAL) );          
    memmove( pNew+POS+1 , ID->data + POS   , (ID->size - POS)   * sizeof (VAL) );  
 
    ++ID->size          ;                                                                                                    
    gcFree(ID->data)    ;
    ID->data = pNew     ; 
    ID->data[POS] = VAL ; 
                                               
}

// ........................................................... [] ERASE at
                
void wstringEraseAt_(wstring_t*ID, size_t POS)
{                                                        
    if ( ID->size ) 
    {                                                                      
        ID->size -= 1;                                                                         
        memmove(ID->data + POS, ID->data + POS + 1, (ID->size - POS) * sizeof *ID->data); 
        ID->data[ID->size ]=0;        
    } ;                                                                                     
}

// ........................................................... [] ERASE N
        
void wstringEraseAtN_(wstring_t* ID, size_t POS, size_t N)
{                                                     
    if ( (ID->size-N)>0 ) 
    {                                                                
        ID->size -= N;                                                                         
        memmove(ID->data + POS, ID->data + POS + N, (ID->size - POS) * sizeof *ID->data);
        ID->data[ID->size ]=0;          
    }                                                                                       
}
 
// ........................................................... [X] RESIZE
    
void wstringResize_( wstring_t* ID, size_t N, wchar_t VAL)
{                                                                 
    if (N > ID->capacity)
    {                                                                              
        ID->data = (wchar_t*) gcRealloc (  ID->data, N * sizeof(wchar_t) +1  ); 
    }
    if ( ID->size<N ) 
    {                                                                                 
        for (size_t i = ID->size; i < N; ++i) ID->data[i] = (VAL);  
    }                                    
    ID->size = N; 
    ID->data[N]=0; 
    ID->capacity=N;   
}

// ........................................................... [] COPY V1 V2 

void wstringCopy_( wstring_t*ID, wstring_t*PTR )
{                                                                                 
    ID->data = (wchar_t*) gcRealloc ( ID->data, PTR->size * sizeof(wchar_t)  ); 
                                                                
    memmove(ID->data  , PTR->data , ID->size * sizeof (wchar_t) );  
                   
    for (size_t i = 0; i < PTR->size; i++) 
    {                                                                      
        ID->data[i] = PTR->data[i];   
    } 
                                                       
    ID->size        = PTR->size;
    ID->capacity    = PTR->capacity;                                                                                         
}

// ........................................................... [] APPEND 
 
void wstringAppend_(wstring_t* ID, wstring_t*V2 )
{                                                                                  
    unsigned V1z = ID->size ;                                                                                      
    unsigned V2z = V2->size ;                                                                                      
    if (ID->capacity < (V1z+V2z)) 
    {                                                                                
        ID->data = (wchar_t*) gcRealloc (  ID->data, (V1z + V2z ) *  sizeof(wchar_t)  );  
    }                                                                                                               
    ID->capacity = V1z + V2z ;                                                                                     
    while (V2z > 0) 
    {                                                                                               
        ID->data[ (V1z + V2z - 1) ] = V2->data[V2z-1];                                                            
        --V2z ;                                                                                                     
    }                                                                                                               
    ID->size = ID->capacity ;                                                                                     
}
 
// ........................................................... [] insert wstring at

void wstringInsertAtwstring_(wstring_t*ID, size_t POS, wstring_t*PTR )
{                                                                          
    while (ID->size + PTR->size > ID->capacity) 
    {                                                                
        ID->capacity *= 2;                                                                                         
        ID->data = (wchar_t*) gcRealloc (  ID->data, ID->capacity *  sizeof(wchar_t)   );
    }                                                                                                               
    memmove(ID->data + POS + PTR->size, ID->data + POS, (ID->size - POS) * sizeof *ID->data);                  
    for (unsigned i = 0; i < PTR->size; i++) 
    {                                                                      
        ID->data[POS + i] = PTR->data[0 + i];    
    }                                                                 
    ID->size += PTR->size;
    ID->data[ID->size] = 0;     
}
 
// ........................................................... [] wstringInsertAtwstringFromN(v1, POS1, v2 , POS2 , N)

void wstringInsertAtwstringFromN_(wstring_t*ID, size_t POS, wstring_t*PTR , size_t POS2 , size_t N)
{                                                     
    while (ID->size + N > ID->capacity) 
    {                                                                         
        ID->capacity *= 2;                                                                                         
        ID->data = (wchar_t*) gcRealloc (  ID->data, ID->capacity *  sizeof(wchar_t)  ); 
    } ;                                                                                                             
    memmove(ID->data + POS + N, ID->data + POS, (ID->size - POS) * sizeof *ID->data);                           
    for (unsigned i = 0; i < N; i++) 
    {                                                                               
        ID->data[POS + i] = PTR->data[POS2 + i];
    }                                                                  
    ID->size += N;  
    ID->data[ID->size] = 0;     
}
 

// ........................................................... [] wstringFindChar (0 = no) , (size_t-1 = pos)

size_t wstringFindChar_(wstring_t*ID, wchar_t VAL )
{                                                     
  for (size_t i=0;i<(ID)->size;i++)
        if ( ID->data[i] == VAL ) return i+1 ;
  return 0 ;
}
 
// ........................................................... [] wstringFromStrC

size_t wstringFromStrC_(wstring_t*ID, const wchar_t *strc )
{                                                     
    ID->size=0;
    for ( size_t i = 0 ; i < wcslen(strc) ; i++ )
    {
        wstringPushBack_(ID, strc[i] ) ;
    }
    wstringPushBack_(ID, L'\0' ) ;
    --ID->size;    
    return ID->size ;
}

// ........................................................... [] wstringToStrC

wchar_t* wstringToStrC_(wstring_t*ID)
{
    return ID->data ;
}

// ........................................................... [v] (iterator) <- wstringFindwstring 

wchar_t* wstringFindStrC_(wstring_t*ID,wchar_t*str2)
{
    wchar_t* ret  = wcsstr(ID->data,str2) ;
    return ret ;
}

// ........................................................... [v] wstringFindwstring (iterator)

wchar_t* wstringFindwstring_(wstring_t*s1,wstring_t*s2)
{
    wchar_t* ret  = wcsstr(s1->data,s2->data) ;
    return ret ;
}

// ........................................................... [] wstringReplace

// https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/

wchar_t *wstringReplace_( const wchar_t *s, const wchar_t *oldW,const wchar_t *newW ) 
{ 
    wchar_t *result; 
    int i, cnt = 0; 
    int newWlen = wcslen(newW); 
    int oldWlen = wcslen(oldW); 

    if ( wcslen(s)==0       ) return NULL;  
    if ( wcslen(oldW)==0    ) return NULL;

    // Counting the number of times old word occur in the wstring
    for (i = 0; s[i] != L'\0'; i++) 
    { 
        if (wcsstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
    // Making new wstring of enough length 
    result = (wchar_t *) malloc(  (i + cnt * (newWlen - oldWlen) + 1)*sizeof(wchar_t) ); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the subwstring with the result 
        if (wcsstr(s, oldW) == s) 
        { 
            wcscpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
        {
            result[i++] = *s++;
        }            
    } 
    result[i] = L'\0'; 
    
    return result; 
}
 
 
void wstringReplaceStrC_     ( wstring_t* ID, const wchar_t *oldW,const wchar_t *newW) 
{
    wchar_t* result    = wstringReplace_ ( ID->data,oldW,newW ) ;
    wstringFromStrC_(ID,result);
    free(result);   // deallocati da lib wstring.h      
}

 
void wstringReplaceWString_   ( wstring_t* ID, wstring_t* oldW,wstring_t* newW) 
{
    wchar_t* result    = wstringReplace_ (ID->data,oldW->data,newW->data ) ;
    wstringFromStrC_(ID,result);
    free(result);   // deallocati da lib wstring.h 
}

// ........................................................... [] wstringPrint

void wstringPrint_  ( wstring_t* ID ) 
{
    wprintf ( L"%ls",ID->data );
}


#if defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER)

    #ifdef _MSC_VER
        #define vsnwprintf _vsnwprintf
    #endif

    void wstringFormat_( wstring_t* ID,const wchar_t* format,...) 
    {
        va_list args ;
        va_start (args , format );

        // calcola la lunghezza della stringa 
        size_t size = vsnwprintf(NULL,0,format, args ); 
        (ID)->data = gcRealloc ( ID->data , (size+2)*sizeof(wchar_t) );
        
        // formattala
        vsnwprintf( ID->data, size+1, format, args );                    
        (ID)->size        = size ;                                   
        (ID)->capacity    = size ;                                   
        (ID)->data[size+1]=0;  
        
        va_end (args);            
    }

#endif


#if defined(__linux__) 
 
    void wstringFormat_( wstring_t* ID,const wchar_t* format,...) 
    {
        va_list args,a2 ;
        va_start (args  , format );
        va_start (a2    , format );

        // calcola la lunghezza della stringa 
        const size_t BUFFER_MAX = 4096 ;
        wchar_t buffer[BUFFER_MAX];

        int result = vswprintf(buffer,BUFFER_MAX,format, args ); 
        size_t len = wcslen(buffer) ;

        (ID)->data = gcRealloc ( ID->data , (len+2)*sizeof(wchar_t) );
        
        // formattala
        vswprintf( ID->data, len+1, format, a2 );     

        (ID)->size        = len ;                                   
        (ID)->capacity    = len ;                                   
        (ID)->data[len+1]=0;  
        
        va_end (args);
        va_end (a2);           
    }

#endif

/**/


 
 
