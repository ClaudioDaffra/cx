
#include "string.h"
#include <stdio.h>
#include <stdint.h>
#include "gc.h"
#include <stdio.h>


// ...........................................................  [v] stringNew

void stringNew_ ( string_t* ID , size_t N )
{
    ID->data = (char*)  gcRealloc ( ID->data , N  * sizeof(char) ) ; 
    ID->size       = 0;         
    ID->capacity   = N;        
}

// ........................................................... [v] stringPushBack

void stringPushBack_(string_t* ID, char VAL)
{  
    if (ID->size + 1 > ID->capacity) 
    {  
        size_t n = ID->capacity * 2;  
        ID->data = (char*) gcRealloc (  ID->data, n * sizeof(char)  );  
        ID->capacity = n;  
    }  
    ID->data[ID->size]   = (VAL); 
    ID->data[ID->size+1] = 0;     
    ID->size += 1;  
}  

// ........................................................... [] SHRINK TO FIT

void stringShrinkToFit_(string_t* ID)
{                                                                          
    ID->data = (char*) gcRealloc (  ID->data, ID->size * sizeof(char) );   
    ID->capacity = ID->size;                                                                              
}

// ........................................................... [] RESERVE 

void stringReserve_(string_t* ID, size_t N)
{
    if (ID->capacity < N) 
    { 
        ID->data = (char*) gcRealloc (  ID->data , N * sizeof(char) ); 
        ID->capacity = N; 
    } 
}

// ........................................................... [] stringInsertAtVal     
        
void stringInsertAtVal_(string_t* ID, size_t POS, char VAL )
{
    char*  pNew ; 

    if (ID->size + 1 > ID->capacity) ID->capacity *= 2;
                                                                                     
    pNew = (char*) gcMalloc ( ID->capacity * sizeof(char)  );  
  
    memmove( pNew       , ID->data         , POS                * sizeof (VAL) );          
    memmove( pNew+POS+1 , ID->data + POS   , (ID->size - POS)   * sizeof (VAL) );  
 
    ++ID->size          ;                                                                                                    
    gcFree(ID->data)    ;
    ID->data = pNew     ; 
    ID->data[POS] = VAL ; 
                                               
}

// ........................................................... [v] ERASE at
                
void stringEraseAt_(string_t*ID, size_t POS)
{                                                        
    if ( ID->size ) 
    {                                                                      
        ID->size -= 1;                                                                         
        memmove(ID->data + POS, ID->data + POS + 1, (ID->size - POS) * sizeof *ID->data); 
        ID->data[ID->size ]=0;
    } ;                                                                                     
}

// ........................................................... [v] ERASE N
        
void stringEraseAtN_(string_t* ID, size_t POS, size_t N)
{                                                     
    if ( (ID->size-N)>0 ) 
    {                                                                
        ID->size -= N;                                                                         
        memmove(ID->data + POS, ID->data + POS + N, (ID->size - POS) * sizeof *ID->data); 
        ID->data[ID->size ]=0;        
    }                                                                                       
}
 
// ........................................................... [] RESIZE
    
void stringResize_( string_t* ID, size_t N, char VAL)
{                                                                 
    if (N > ID->capacity)
    {                                                                              
        ID->data = (char*) gcRealloc (  ID->data, N * sizeof(char) +1  ); 
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

void stringCopy_( string_t*ID, string_t*PTR )
{                                                                                 
    ID->data = (char*) gcRealloc ( ID->data, PTR->size * sizeof(char)  ); 
                                                                
    memmove(ID->data  , PTR->data , ID->size * sizeof (char) );  
                   
    for (size_t i = 0; i < PTR->size; i++) 
    {                                                                      
        ID->data[i] = PTR->data[i];   
    } 
                                                       
    ID->size        = PTR->size;
    ID->capacity    = PTR->capacity;                                                                                         
}

// ........................................................... [] APPEND 
 
void stringAppend_(string_t* ID, string_t*V2 )
{                                                                                  
    unsigned V1z = ID->size ;                                                                                      
    unsigned V2z = V2->size ;                                                                                      
    if (ID->capacity < (V1z+V2z)) 
    {                                                                                
        ID->data = (char*) gcRealloc (  ID->data, (V1z + V2z ) *  sizeof(char)  );  
    }                                                                                                               
    ID->capacity = V1z + V2z ;                                                                                     
    while (V2z > 0) 
    {                                                                                               
        ID->data[ (V1z + V2z - 1) ] = V2->data[V2z-1];                                                            
        --V2z ;                                                                                                     
    }                                                                                                               
    ID->size = ID->capacity ;                                                                                     
}
 
// ........................................................... [] insert string at

void stringInsertAtString_(string_t*ID, size_t POS, string_t*PTR )
{                                                                          
    while (ID->size + PTR->size > ID->capacity) 
    {                                                                
        ID->capacity *= 2;                                                                                         
        ID->data = (char*) gcRealloc (  ID->data, ID->capacity *  sizeof(char)   );
    }                                                                                                               
    memmove(ID->data + POS + PTR->size, ID->data + POS, (ID->size - POS) * sizeof *ID->data);                  
    for (unsigned i = 0; i < PTR->size; i++) 
    {                                                                      
        ID->data[POS + i] = PTR->data[0 + i];    
    }                                                                 
    ID->size += PTR->size; 
    ID->data[ID->size] = 0;    
}
 
// ........................................................... [] stringInsertAtstringFromN(v1, POS1, v2 , POS2 , N)

void stringInsertAtStringFromN_(string_t*ID, size_t POS, string_t*PTR , size_t POS2 , size_t N)
{                                                     
    while (ID->size + N > ID->capacity) 
    {                                                                         
        ID->capacity *= 2;                                                                                         
        ID->data = (char*) gcRealloc (  ID->data, ID->capacity *  sizeof(char)  ); 
    } ;                                                                                                             
    memmove(ID->data + POS + N, ID->data + POS, (ID->size - POS) * sizeof *ID->data);                           
    for (unsigned i = 0; i < N; i++) 
    {                                                                               
        ID->data[POS + i] = PTR->data[POS2 + i];
    }                                                                  
    ID->size += N;
    ID->data[ID->size] = 0;       
}
 

// ........................................................... [v] stringFindChar (0 = no) , (size_t-1 = pos)

size_t stringFindChar_(string_t*ID, char VAL )
{                                                     
  for (size_t i=0;i<(ID)->size;i++)
        if ( ID->data[i] == VAL ) return i+1 ;
  return 0 ;
}
 
// ........................................................... [v] stringFromStrC

size_t stringFromStrC_(string_t*ID, const char *strc )
{                                                     
    ID->size=0;
    for ( size_t i = 0 ; i < strlen(strc) ; i++ )
    {
        stringPushBack_(ID, strc[i] ) ;
    }
    stringPushBack_(ID, '\0' ) ;
    --ID->size;
    return ID->size ;
}

// ........................................................... [v] stringToStrC

char* stringToStrC_(string_t*ID)
{
    return ID->data ;
}

// ........................................................... [v] (iterator) <- stringFindString 

char* stringFindStrC_(string_t*ID,char*str2)
{                                                     
    char* ret  = strstr(ID->data,str2) ;

    return ret ;
}

// ........................................................... [v] stringFindString (iterator)

char* stringFindString_(string_t*s1,string_t*s2)
{
    char* ret  = strstr(s1->data,s2->data) ; 

    return ret ;
}

// ........................................................... [] stringReplace

// https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/

char *stringReplace_( const char *s, const char *oldW,const char *newW ) 
{ 
    char *result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 

    if ( strlen(s)==0       ) return NULL;  
    if ( strlen(oldW)==0    ) return NULL;

    // Counting the number of times old word occur in the string
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
    // Making new string of enough length 
    result = (char *) malloc(  i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
        {
            result[i++] = *s++;
        }            
    } 
    result[i] = '\0'; 
    
    return result; 
}
 
 
void stringReplaceStrC_     ( string_t* ID, const char *oldW,const char *newW) 
{
    char* result    = stringReplace_ ( ID->data,oldW,newW ) ;
    stringFromStrC_(ID,result);
    free(result);
}

 
void stringReplaceString_   ( string_t* ID, string_t* oldW,string_t* newW) 
{
    char* result    = stringReplace_ (ID->data,oldW->data,newW->data ) ;
    stringFromStrC_(ID,result);
    free(result);    
}

// ........................................................... [] stringPrint

void stringPrint_  ( string_t* ID ) 
{
    printf("%s",ID->data);
}



#if defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER)

    void stringFormat_( string_t* ID,const char* format,...) 
    {
        va_list args ;
        va_start (args , format );

        // calcola la lunghezza della stringa            
        size_t size = vsnprintf(NULL,  0,format, args );  

        (ID)->data = gcRealloc ( ID->data , (size+2)*sizeof(char) ); 
        
        // formattala
        vsnprintf( ID->data,size+1,format, args ); 
        (ID)->size        = size ;                                            
        (ID)->capacity    = size ;                                            
        (ID)->data[size+1]=0;  
        
        va_end (args);
    }

#endif


#if defined(__linux__) 

    void stringFormat_( string_t* ID,const char* format,...) 
    {
        va_list args,a2 ;

        va_start (args , format );
        va_start (a2 , format );

        // calcola la lunghezza della stringa            
        size_t size = vsnprintf(NULL,  0,format, args );  

        (ID)->data = gcRealloc ( ID->data , (size+2)*sizeof(char) ); 
        
        // formattala
        vsnprintf( ID->data,size+1,format, a2 ); 

        (ID)->size        = size ;                                            
        (ID)->capacity    = size ;                                            
        (ID)->data[size+1]=0;  
        
        va_end (args);
        va_end (a2);
    }

#endif


 
/**/


