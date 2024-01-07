#include "../src/cxx.h"


// gcc src/gc.c src/hashMap.c tst/hashMap001.c -o x -Wall -pedantic -Wextra

int main ( void ) 
{
    gcStart();

    hashMap_t    *hm = gcMalloc( sizeof(hashMap_t) )  ;

    hashMapInit( hm , hmStringHash, hmStringEq, HM_DEFAULT_LEN, HM_DEFAULT_LOAD_FACTOR);

    hashMapPut        ( hm, gcStrDup("claudio") , gcStrDup("123"), HM_NORMAL );
    hashMapPut        ( hm, gcStrDup("daffra")  , gcStrDup("456"), HM_NORMAL );

    void* value=NULL;

    value = hashMapGet        ( hm, gcStrDup("claudio"), HM_NORMAL );
    printf ( "\nfound si [%s]",(char*)value ) ;

    hashMapDrop       (hm, gcStrDup("claudio"), HM_NORMAL);

    value = hashMapGet        ( hm, gcStrDup("claudio"), HM_NORMAL );
    printf ( "\nfound no [%s]",(char*)value ) ;
    
    hashMapDestroy    (hm, HM_NORMAL);

    printf ( "\n" ) ;
    
    gcStop();
    
 return 0 ;
}