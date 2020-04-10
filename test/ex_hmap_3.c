
#include "../lib/gc.h"
#include "../lib/stdio.h"
#include "../lib/fs.h"
#include "../lib/hmap.h"
#include <stdio.h>
#include <stdint.h>


/*

    cl  lib\hmap.c test\ex_hmap_3.c lib\gc.c lib\fs.c   /Fex.exe /WX
    gcc lib\hmap.c test\ex_hmap_3.c lib\gc.c lib\fs.c   -o x.exe -Wall -Wextra  
    gcc lib/hmap.c test/ex_hmap_3.c lib/gc.c lib/fs.c   -o x     -Wall -Wextra  

*/

int main(void)
{
    gcStart();

    //
    
	whmapType(mappa) ; 
    
    mappa = whmapDef ( gcComparepWStrC );

    // Use of uninitialised value of size 8

	whmapInsert( mappa,  (void*)gcWcsDup(L"claudio")                    , (void*)gcIntDup(100)   );
	whmapInsert( mappa,  (void*)gcWcsDup(L"daffra")                     , (void*)gcIntDup(101)   ); 
	whmapInsert( mappa,  (void*)gcWcsDup(L"祝您有个美好的一天")          , (void*)gcIntDup(102)   );
	whmapInsert( mappa,  (void*)gcWcsDup(L"你好")                       , (void*)gcIntDup(103)   ); 
	whmapInsert( mappa,  (void*)gcWcsDup(L"precipitevolissimevolmente") , (void*)gcIntDup(104)   );
	whmapInsert( mappa,  (void*)gcWcsDup(L"/*")                         , (void*)gcIntDup(105)   );
	whmapInsert( mappa,  (void*)gcWcsDup(L"##")                         , (void*)gcIntDup(106)   );
	whmapInsert( mappa,  (void*)gcWcsDup(L"->")                         , (void*)gcIntDup(107)   );
	
    whmapType(x) ;
    
    x=  whmapFind(mappa, L"claudio" ) ;
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");

    x=  whmapFind(mappa, L"daffra" ) ;
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");

    x=  whmapFind(mappa, L"祝您有个美好的一天" ) ;
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");    

    x=  whmapFind(mappa, L"祝您有个美好的一天X" ) ; // NOT FOUND
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");    
    
    x=  whmapFind(mappa, L"你好" ) ;
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");   

    x=  whmapFind(mappa, L"precipitevolissimevolmente" ) ;
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");  

    x=  whmapFind(mappa, L"precipitevolissimevolmenteX" ) ;  // NOT FOUND
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");  

    x=  whmapFind(mappa, L"##" ) ; 
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");  

    x=  whmapFind(mappa, L"#" ) ;  // NOT FOUND
    if ( x != NULL ) wprintf ( L"\n key value = [%d].", *(int*) x  ) ; else wprintf (L"\nnot found");  
    
    //

    wprintf ( L"\n" );

    // hmapDelete ( mappa ) ; NO MORE MEMORY LEAK !
    
    gcStop() ;

  return 0;
}
	

/* test

==13857== Use of uninitialised value of size 8
==13857==    at 0x109574: hash_map_put (in /home/claudio/mc/mappa)
==13857==    by 0x109F3D: main (in /home/claudio/mc/mappa)
==13857== 
==13857== Use of uninitialised value of size 8
==13857==    at 0x1095D5: hash_map_put (in /home/claudio/mc/mappa)
==13857==    by 0x109F3D: main (in /home/claudio/mc/mappa)
==13857== 
==13857== Use of uninitialised value of size 8
==13857==    at 0x109574: hash_map_put (in /home/claudio/mc/mappa)
==13857==    by 0x109F74: main (in /home/claudio/mc/mappa)
==13857== 
==13857== Use of uninitialised value of size 8
==13857==    at 0x1095D5: hash_map_put (in /home/claudio/mc/mappa)
==13857==    by 0x109F74: main (in /home/claudio/mc/mappa)
==13857== 


*/


/*
    E:\c--\test>mappa.exe

     key value = value
     NO key value = (null)
     count = 2 / 1024
     ERASE key value = (null)
     count = 1 / empty ? 0
     begin a314d0
     end   0
     ((xxx,yyy))
     ((key1,value1))
     ((key2,value2))
     ((key3,value3))
     AT[2] ((key2))
     ((KEY::xxx VALUE::yyy))
     ((KEY::key1 VALUE::value1))
     ((KEY::key2 VALUE::value2))
     ((KEY::key3 VALUE::value3))
    E:\c--\test>

*/















