

#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/hmap.h"
#include <stdio.h>
#include <stdint.h>


/*

    cl  lib\hmap.c lib\stdio.c test\ex_whmap_2.c lib\gc.c lib\fs.c  /Fex.exe /WX /EHsc
    gcc lib\hmap.c lib\stdio.c test\ex_whmap_2.c lib\gc.c lib\fs.c  -o x.exe -Wall -Wextra -pedantic
    gcc lib/hmap.c lib/stdio.c test/ex_whmap_2.c lib/gc.c lib/fs.c  -o x     -Wall -Wextra -pedantic

*/

/*
    E:\c--\test>x.exe

     key value = (null)
     NO key value = (null)
     count = 2 / 1024
     ERASE key value = (null)
     count = 2 / empty ? 0
     begin 191640
     end   0
     ((さようなら,Sayonara))
     ((Sayonara,Arrivederci / Ciao))
     ((key1,value1))
     ((key2,value2))
     ((key3,value3))
     AT[2] ((key1))
     ((KEY::さようなら VALUE::Sayonara))
     ((KEY::Sayonara VALUE::Arrivederci / Ciao))
     ((KEY::key1 VALUE::value1))
     ((KEY::key2 VALUE::value2))
     ((KEY::key3 VALUE::value3))
    E:\c--\test>

*/

//------------------------------------------------------------
// MAIN
//------------------------------------------------------------

int main(void)
{
    gcStart() ;

    //

    // file.c
    consoleSetUTF8();
    
    // hmap.c
 
	whmapType(x) ;
 
    whmapNew(x);
 
    //


	whmapInsert( x, L"さようなら", L"Sayonara");
	whmapInsert( x, L"Sayonara", L"Arrivederci / Ciao");

	wprintf ( L"\n key value = %ls  ", (wchar_t *) whmapFind(x, L"key") ) ;
	
	wprintf ( L"\n NO key value = %ls  ", (wchar_t *) whmapFind(x, L"null") ) ;
	
	wprintf ( L"\n count = %lu / %lu ",   (long unsigned)whmapSize(x)	, (long unsigned)whmapMaxSize(x)	) ;	

	// ERASE	
	
	whmapErase(x, L"key" );	

	wprintf ( L"\n ERASE key value = %ls  ", (wchar_t *) whmapFind(x, L"key") ) ;	
	
	wprintf ( L"\n count = %lu / empty ? %d ",   (long unsigned)whmapSize(x)	, whmapEmpty(x)	) ;	
 
	// INSERT	
	  
	whmapInsert(x, L"key1", L"value1" );
	whmapInsert(x, L"key2", L"value2" );
	whmapInsert(x, L"key3", L"value3" );

	// ITERATOR

	wprintf ( L"\n begin %p " , whmapBegin(x) ) ;
	wprintf ( L"\n end   %p " , whmapEnd(x) ) ;

	for ( whmapIt_t* it=whmapBegin(x) ; it != whmapEnd(x) ; whmapNext(x,it) )  
	{
		wprintf ( L"\n ((%ls,%ls)) ", whmapData(it) , (const wchar_t*)whmapFind(x, whmapData(it) ) );
	}

	// AT
    
	wprintf ( L"\n AT[2] ((%ls)) ", (wchar_t*)whmapAt(x,2) ) ;	

	// COPY

	whmapType(y) ;
 
    whmapNew(y);

    //

	whmapCopy ( y , x ) ;

	for ( whmapIt_t* it=whmapBegin(y) ; it != whmapEnd(y) ; it = whmapNext(y,it) )  
	{
		wprintf ( L"\n ((KEY::%ls VALUE::%ls)) ", 
            (const wchar_t*)it->data , (const wchar_t*)whmapFind(x, (wchar_t*)it->data) );
	}

	// GET ITERATOR FROM KEY
	
	// whmapIt_t* it = whmapIterator ( x , L"key1" ); // OLD
       whmapIt_t* it = itWHmap ( x , L"key1" );  // NEW
    
	// CLEAR 	

	whmapClear ( x ) ;	

	// DELETE	

	whmapDelete ( y ) ;	
 	
	//whmapDelete ( x ) ; NO MORE MEMORY LEAK !
    
    //

    gcStop() ;

  return 0;
}
	
/* OK

==13879== 
==13879== HEAP SUMMARY:
==13879==     in use at exit: 0 bytes in 0 blocks
==13879==   total heap usage: 44 allocs, 44 frees, 18,176 bytes allocated
==13879== 
==13879== All heap blocks were freed -- no leaks are possible
==13879== 
==13879== For counts of detected and suppressed errors, rerun with: -v
==13879== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


*/















