

#include "../lib/gc.h"
#include "../lib/hmap.h"
#include "../lib/stdio.h"
#include <stdio.h>
#include <stdint.h>

 
/*

    cl  lib\hmap.c lib\stdio.c lib\gc.c  lib\fs.c test\ex_whmap_1.c  /Fex.exe     /EHsc /WX
    gcc lib\hmap.c lib\stdio.c lib\gc.c  lib\fs.c test\ex_whmap_1.c  -o x.exe     -Wall -Wextra -pedantic
    gcc lib/hmap.c lib/stdio.c lib/gc.c  lib\fs.c test/ex_whmap_1.c  -o x         -Wall -Wextra -pedantic

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
    gcStart();

    //

    // file.c
    consoleSetUTF8();
    
    // hmap.c

	//whmap_t* x = whmap.new();

    whmapType(x);

    whmapNew(x);    

    //

	whmap.insert( x, L"さようなら", L"Sayonara");
	whmap.insert( x, L"Sayonara", L"Arrivederci / Ciao");

	wprintf ( L"\n key value = %ls  ", (wchar_t *) whmap.find(x, L"key") ) ;
	
	wprintf ( L"\n NO key value = %ls  ", (wchar_t *) whmap.find(x, L"null") ) ;
	
	wprintf ( L"\n count = %lu / %lu ",   (long unsigned)whmap.size(x)	, (long unsigned)whmap.max_size(x)	) ;	

	// ERASE	
	
	whmap.erase(x, L"key" );	

	wprintf ( L"\n ERASE key value = %ls  ", (wchar_t *) whmap.find(x, L"key") ) ;	
	
	wprintf ( L"\n count = %lu / empty ? %d ",   (long unsigned)whmap.size(x)	, whmap.empty(x)	) ;	
 
	// INSERT	
	  
	whmap.insert(x, L"key1", L"value1" );
	whmap.insert(x, L"key2", L"value2" );
	whmap.insert(x, L"key3", L"value3" );

	// ITERATOR

	wprintf ( L"\n begin %p " , whmap.begin(x) ) ;
	wprintf ( L"\n end   %p " , whmap.end(x) ) ;

	for ( whmapIt_t* it=whmap.begin(x) ; it != whmap.end(x) ; it = whmap.next(x,it) )  
	{
		wprintf ( L"\n ((%ls,%ls)) ", (const wchar_t*)it->data , (const wchar_t*)whmap.find(x, (wchar_t*)it->data) );
	}

	// AT
    
	wprintf ( L"\n AT[2] ((%ls)) ", (wchar_t*)whmap.at(x,2) ) ;	

	// COPY
		
	whmap_t* y = whmap.new();

	whmap.copy ( y , x ) ;

	for ( whmapIt_t* it=whmap.begin(y) ; it != whmap.end(y) ; it = whmap.next(y,it) )  
	{
		wprintf ( L"\n ((KEY::%ls VALUE::%ls)) ", 
            (const wchar_t*)it->data , (const wchar_t*)whmap.find(x, (wchar_t*)it->data) );
	}

	// GET ITERATOR FROM KEY
	
	whmapIt_t* it = whmap.iterator ( x , L"key1" );

	// CLEAR DELETE	

	whmap.clear ( x ) ;	

	//whmap.delete ( y ) ;	NO MORE MEMORY LEAK !
 	
	whmap.delete ( x ) ;
    
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















