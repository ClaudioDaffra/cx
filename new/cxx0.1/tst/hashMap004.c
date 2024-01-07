#include "../src/cxx.h"


// gcc src/gc.c src/hashMap.c tst/hashMap004.c -o x  -Wall -pedantic -Wextra

int main ( void ) 
{
    gcStart();

    hashMap_t    *hm = gcMalloc( sizeof(hashMap_t) )  ;

    //hashMapInit( hm , hmPtrHash, hmPtrEq, HM_DEFAULT_LEN, HM_DEFAULT_LOAD_FACTOR);
    hmInitPtr(hm);
    
/*
    hashMapPut        ( hm, (void*)1 , (void*)101, HM_FAST );
    hashMapPut        ( hm, (void*)2 , (void*)202, HM_FAST );
    hashMapPut        ( hm, (void*)3 , (void*)303, HM_FAST );
    hashMapPut        ( hm, (void*)4 , (void*)303, HM_FAST );
*/
    hmPutPtr(hm,1,101);
    hmPutPtr(hm,2,102);
    hmPutPtr(hm,3,103);
    hmPutPtr(hm,4,104);
 
    void* value=NULL;

    //value = hashMapGet ( hm, (void*)3, HM_FAST );
    value = hmGetPtr(hm,3);
    
    printf ( "\nfound si [%d]",(int)value ) ;

    //hashMapDrop       (hm, (void*)3, HM_FAST);
    hmDropPtr(hm,3) ;

   // value = hashMapGet ( hm, (void*)3, HM_FAST );
    value = hmGetPtr ( hm, 3 );
    printf ( "\nfound no [%d]",(int)value ) ;
    

    hmDestroy(hm);

    printf ( "\n" ) ;

    gcStop();
    
 return 0 ;
}