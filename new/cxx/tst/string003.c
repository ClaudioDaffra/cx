#include "../src/cxx.h"


/*
	// cls       &  cl  src\gc.c src\stdio.c src\string.c tst\string003.c    /Febin\x.exe /utf-8    /WX
	// clear    ;   gcc src/gc.c src/stdio.c src/string.c tst/string003.c    -o bin/x                -Wall   -Wextra -pedantic
*/


int main() 
{
    gcStart();

	stdio_t stdio ;
 
	stdioSetMBS( &stdio );

	//.......................... typedef def alloc

    stringTypeDef(char,s1) ;
     
	//..........................  mbs

    string_s1_t mbs ;
    
    stringAlloc(mbs,8);
   
    // multi byte string

    stringFromWS ( mbs , L"你好吗" ) ;

    printf ( "\n[mbs] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,mbs.data
		,stringSize(mbs)
		,stringCapacity(mbs)
		,stringEmpty(mbs)
		,mbstringLen(mbs) 
	) ;  

    //
    //  p.s.
    //   
    //  per le stringhe multi byte occorre ( le operazione sono lente sui multibyte ) :
    //  1) convertirle in wstring ed utilizzare la libreria per poi riconvertirle ;
    //  2) adottarsi di una libreria esterna .
    //      
 
	//..........................  string
	
    string_s1_t s1 ;

    stringAlloc(s1,8);

    //.......................... init
    
    printf ("\n");
    
    stringClear(s1);
    printf ( "s1 clear [%s] len(%zu).\n",s1.data,strlen(s1.data));

    //.......................... from char*
 
    stringFromS8 ( s1 , "precipitevolissimevolmente" ) ;

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) ) ;

    const char* temp = "Claudio Daffra" ;
    stringFromS8 ( s1 , temp ) ;

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;

    //.......................... push Back "Claudio Daffra" + 'X' + 'Y'
    
    stringPushBack( s1 , 'X' ) ;
    stringPushBack( s1 , 'Y' ) ;    
    
    printf ( "after push back XY s1 [%s].\n",stringData(s1) ) ;

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;

    stringPopBack(s1);
    
    printf ( "after pop back s1 [%s].\n",stringData(s1) ) ;

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        
    //..........................  front back at

    printf ( "front [%c] back [%c] at[3]==[%c].\n",stringFront(s1),stringBack(s1),stringAt(s1,3) ) ;
    
    //..........................  shrink to fit , reserve
    
    stringShrinkToFit(s1);

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        
    stringReserve(s1,32);

    //..........................  append

    stringTypeDef(char,s2) ;

    string_s1_t s2 ;

    stringAlloc(s2,8);

    stringFromS8 ( s2 , "ABC" ) ;

    printf ( "[s2] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s2.data,stringSize(s2),stringCapacity(s2),stringEmpty(s2),stringLen(s2) )   ;
      
    stringAppend( s1 , s2 ) ;

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;

    //..........................  string insert at string
    
    stringInsertAtString(s1,3,s2);

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        
    //..........................  string erase at
    
    stringEraseAt(s1,3);

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        
    //..........................  string erase at N
 
    stringEraseAtN(s1,3,5);

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;

    //..........................  string resize
    
    stringResize(s1,12,'a');

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        
    //..........................  string copy
    
    stringCopy(s1,s2);

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        
    //..........................  insert at val
    
    stringInsertAtVal(s1,2,'Q');

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        
    //.......................... iterator
    
    for ( itString(s1) it = stringBegin(s1); it < stringEnd(s1) ; it++ )
    {
        printf("[%c]",*it);
    }
    printf("\n");
   
    for ( itString(s1) it = stringRBegin(s1); it >= stringREnd(s1) ; it-- )
    {
        printf("[%c]",*it);
    }
    printf("\n"); 

    //..........................  insert string from N
  
    stringFromS8(s1,"claudio"); // cl-audio
    stringFromS8(s2,"DAFFRA");  // DA-FFR-A
                                // clAFFaudio
    
    printf("%s.\n",s1.data);
    printf("%s.\n",s2.data);   
    
    stringInsertAtStringFromN(s1,2,s2,1,3); // inserisce dalla posizioni 3 delle stringhe 3 caratteri da s2 in s1

    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;

    //.......................... vettori di stringhe string 

            stringType( char ) ;
            
            // [OK] stringTypeDef( char_d , vString ) ;
            typedef string_char_t* pStringchar_t ;
            
            stringTypeDef( pStringchar_t , vpString ) ; // <-- need data type
            
            string_vpString_t v1s ; 
            stringAlloc(v1s,4);
          
            pStringchar_t ps = NULL ;
            
            ps=new(string_char_t);
            
            stringAlloc(*ps,8);
            stringFromS8( *ps , "Claudio" ) ; 
            stringPushBack( v1s , ps ) ;
	

            ps=new(string_char_t);
            
            stringAlloc(*ps,8);
            stringFromS8( *ps , "Daffra" ) ; 
            stringPushBack( v1s , ps ) ;
            
            printf ( "\n" ) ;    
            printf ( "1) string :: [%s]\n",v1s.data[0]->text ) ;
            printf ( "2) string :: [%s]\n",v1s.data[1]->text ) ;            

    //.......................... vector string

        stringTypeDef( char 	   , x1 ) ;	// string_x1_t
        
        string_x1_t x1,x2  ;

        stringAlloc( x1 , 8 ) ;
        stringAlloc( x2 , 8 ) ;    

        //
     
        vectorTypeDef( string_x1_t , v1 ) ;	// vector_v1_t     
        
        vector_v1_t v1 ;
        
        vectorAlloc( v1 , 8 ) ;

        //
        
        stringFromS8( x1 , "CLAUDIO" );    
        vectorPushBack( v1 , x1 ) ;
        
        stringFromS8( x2 , "DAFFRA" );    
        vectorPushBack( v1 , x2 ) ;
        
        printf ( "\n0] %s." , v1.data[0].text );
        printf ( "\n1] %s." , v1.data[1].text );
        printf ( "\n"  );   

    // ......................... replace all

    stringFromS8(s1,"Claudio Daffra");
    
    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;

    stringReplaceAll( s1 , "a" , "XYZ" ) ; 
 
    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
    
    // ......................... wstring formatn

	char* x = s8Format( "%f" , 1.2 ) ;

	printf ( "--> %s.\n",x) ;

	//
	
	stringFormat( s1,"%f" , 3.4 ) ;
	
    printf ( "[s1] %s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.text,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) )   ;
        	
    // .........................  compare

	printf ( "compare s1,s2 [%s] ?= [%s] -> [%d] \n",s1.data,s2.data,!stringCompare(s1,s2) ) ;
	printf ( "compare s1,s2 [%s] ?= [%s] -> [%d] \n",s1.data,s1.data,!stringCompareN(s1,s1,3) ) ;
		
    // ......................... 
      
	stringDealloc(s1);

	stringDealloc(s2);
  
    gcStop();
  
    return 0; 
} 

