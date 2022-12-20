#include "../src/cxx.h"
 

/*
	// cls      &   cl  src\gc.c src\stdio.c src\string.c tst\string004.c   /Febin\x.exe /utf-8     /WX
	// clear    ;   gcc src/gc.c src/stdio.c src/string.c tst/string004.c   -o bin/x    -Wall   -Wextra -pedantic
*/


int main() 
{
    gcStart();
    
	stdio_t stdio ;
 
	stdioSetUTF8( &stdio );
    
    //.......................... typedef def alloc

    wstringTypeDef(wchar_t,s1) ;

    wstring_s1_t s1 ;

    wstringAlloc(s1,8);

    //.......................... init
    
    wprintf (L"\n");
    
    wstringClear(s1);
    
    wprintf ( L"s1 clear s1:[%ls] len(%zu).\n",s1.data,wcslen(s1.data));

    //.......................... from wchar_t*
    
    wstringFromWS ( s1 , L"precipitevolissimevolmente" ) ;

    wprintf ( L"%ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) ) ;

    //.......................... from char*

    const char* temp = "Claudio Daffra" ;
    wstringFromS8 ( s1 , temp ) ;

    wprintf ( L"%ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) ) ;

  
    //.......................... push Back "Claudio Daffra" + L'X' + L'Y'
    
    wstringPushBack( s1 , L'X' ) ;
    wstringPushBack( s1 , L'Y' ) ;    
    
    wprintf ( L"after push back XY s1 [%ls].\n",wstringData(s1) ) ;

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;

    wstringPopBack(s1); 
    
    wprintf ( L"after pop back s1 [%ls].\n",wstringData(s1) ) ;

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
        
    //..........................  front back at

    wprintf ( L"front [%lc] back [%lc] at[3]==[%lc].\n",wstringFront(s1),wstringBack(s1),wstringAt(s1,3) ) ;
    
    //..........................  shrink to fit , reserve
    
    wstringShrinkToFit(s1);

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    wstringReserve(s1,32);
    
    //..........................  append

    wstringTypeDef(char,s2) ;

    wstring_s1_t s2 ;

    wstringAlloc(s2,8);

    wstringFromWS ( s2 , L"ABC你好吗DEF" ) ;

    wprintf ( L"[s2] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s2.data,wstringSize(s2),wstringCapacity(s2),wstringEmpty(s2),wstringLen(s2) )   ;
      
    wstringAppend( s1 , s2 ) ;

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
     
    //..........................  string insert at string
    
    wstringInsertAtWString(s1,3,s2);

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    //..........................  string erase at
    
    wstringEraseAt(s1,3);

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    //..........................  string erase at N
    
    wstringEraseAtN(s1,3,5);

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;

    //..........................  string resize
    
    wstringResize(s1,32, L'=');

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    //..........................  string copy
    
    wstringCopy(s1,s2);

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    //..........................  insert at val
    
    wstringInsertAtVal(s1,2,L'Q');

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    //.......................... iterator
    
    for ( itWString(s1) it = wstringBegin(s1); it < wstringEnd(s1) ; it++ )
    {
        wprintf(L"[%lc]",*it);
    }
    wprintf(L"\n");

    for ( itWString(s1) it = wstringRBegin(s1); it >= wstringREnd(s1) ; it-- )
    {
        wprintf(L"[%lc]",*it);
    }
    wprintf(L"\n");

    //..........................  insert string from N
   
    wstringFromWS(s1,L"claudio"); // cl-audio
    wstringFromWS(s2,L"DAFFRA");  // DA-FFR-A
                                  // clAFFaudio
    
    wprintf(L"%ls.\n",s1.data);
    wprintf(L"%ls.\n",s2.data);   
    
    wstringInsertAtStringFromN(s1,2,s2,1,3); // inserisce dalla posizioni 3 delle stringhe 3 caratteri da s2 in s1

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;

    //.......................... vettori di stringhe

            typedef wchar_t wchar ;
            
            wstringType( wchar ) ;
            
            // [OK] vectorTypeDef( char_d , vString ) ;
            typedef wstring_wchar_t* pStringWChar_t ;
            
            vectorTypeDef( pStringWChar_t , vpString ) ; // <-- need data type
            
            vector_vpString_t v1s ; 
            vectorAlloc(v1s,4);
          
            pStringWChar_t ps = NULL ;
            
            ps=new(wstring_wchar_t);
            wstringAlloc(*ps,8);
            wstringFromWS( *ps , L"Claudio" ) ; 
            vectorPushBack( v1s , ps ) ;

            ps=new(wstring_wchar_t);
            wstringAlloc(*ps,8);
            wstringFromWS( *ps , L"Daffra" ) ; 
            vectorPushBack( v1s , ps ) ;
            
            wprintf ( L"\n" ) ;    
            wprintf ( L"1) wstring :: [%ls]\n",v1s.data[0]->text ) ;
            wprintf ( L"2) wstring :: [%ls]\n",v1s.data[1]->text ) ;            

    // ......................... replace all
    
    wstringFromWS(s1,L"Claudio Daffra");
    
    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;

    wstringReplaceAll( s1 , L"a" , L"XYZ" ) ;
 
    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    // ......................... wstring formatn

	wchar_t* x = wsFormat( L"%f" , 1.2 ) ;

	wprintf ( L"--> %ls.\n",x) ;

	//
	
	wstringFormat( s1,L"%f" , 3.4 ) ;

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.text,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        	
    // .........................  compare

	wprintf ( L"compare s1,s2 [%ls] ?= [%ls] -> [%d] \n",s1.data,s2.data,!wstringCompare(s1,s2) ) ;
	wprintf ( L"compare s1,s2 [%ls] ?= [%ls] -> [%d] \n",s1.data,s1.data,!wstringCompareN(s1,s1,3) ) ;
		
    // ......................... 
    	    
    wstringDealloc(s1);

    wstringDealloc(s2);
    
	gcStop();
    
    return 0; 
} 

