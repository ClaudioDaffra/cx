
#include "../lib/gc.h"
#include "../lib/hmap.h"
#include <stdio.h>
#include <stdint.h>

/*

    cl  lib\hmap.c test\ex_hmap_2.c lib\gc.c lib\fs.c    /Fex.exe /WX
    gcc lib\hmap.c test\ex_hmap_2.c lib\gc.c lib\fs.c    -o x.exe -Wall -Wextra  
    gcc lib/hmap.c test/ex_hmap_2.c lib/gc.c lib/fs.c    -o x     -Wall -Wextra  

*/

int main(void)
{
    gcStart();

    //
    
	hmapType(x) ; 
    
    x = hmapDef ( gcCompareInt );

    // Use of uninitialised value of size 8

	hmapInsert( x, (void*)gcIntDup(100) , (void*)gcDoubleDup(12.3) );
	hmapInsert( x, (void*)gcIntDup(200) , (void*)gcDoubleDup(45.6) ); 
	
    int val=100 ;
	printf ( "\n key value = [%e].", *(double*) hmapFind(x, &val ) ) ;
    
    //

    printf ( "\n" );

    // hmapDelete ( x ) ; NO MORE MEMORY LEAK !
    
    gcStop() ;

  return 0;
}
	

/* test

==13857== Use of uninitialised value of size 8
==13857==    at 0x109574: hash_map_put (in /home/claudio/mc/x)
==13857==    by 0x109F3D: main (in /home/claudio/mc/x)
==13857== 
==13857== Use of uninitialised value of size 8
==13857==    at 0x1095D5: hash_map_put (in /home/claudio/mc/x)
==13857==    by 0x109F3D: main (in /home/claudio/mc/x)
==13857== 
==13857== Use of uninitialised value of size 8
==13857==    at 0x109574: hash_map_put (in /home/claudio/mc/x)
==13857==    by 0x109F74: main (in /home/claudio/mc/x)
==13857== 
==13857== Use of uninitialised value of size 8
==13857==    at 0x1095D5: hash_map_put (in /home/claudio/mc/x)
==13857==    by 0x109F74: main (in /home/claudio/mc/x)
==13857== 


*/


/*
    E:\c--\test>x.exe

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















