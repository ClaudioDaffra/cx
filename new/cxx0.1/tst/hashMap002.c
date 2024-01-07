#include "../src/cxx.h"


// gcc src/gc.c src/hashMap.c tst/hashMap002.c -o x  -Wall -pedantic -Wextra

int main ( void ) 
{
    gcStart();

    hashMap_t    *hm = gcMalloc( sizeof(hashMap_t) )  ;

    hashMapInit( hm , hmPtrHash, hmPtrEq, HM_DEFAULT_LEN, HM_DEFAULT_LOAD_FACTOR);

    hashMapPut        ( hm, (void*)1 , (void*)101, HM_FAST );
    hashMapPut        ( hm, (void*)2 , (void*)202, HM_FAST );
    hashMapPut        ( hm, (void*)3 , (void*)303, HM_FAST );
    hashMapPut        ( hm, (void*)4 , (void*)303, HM_FAST );

    void* value=NULL;

    value = hashMapGet ( hm, (void*)3, HM_FAST );
    printf ( "\nfound si [%d]",(int)value ) ;
 
    hashMapDrop       (hm, (void*)3, HM_FAST);

    value = hashMapGet ( hm, (void*)3, HM_FAST );
    printf ( "\nfound no [%d]",(int)value ) ;
 
    hashMapDestroy    (hm, HM_FAST);

    printf ( "\n" ) ;

    gcStop();
    
 return 0 ;
}