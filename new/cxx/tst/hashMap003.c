#include "../src/cxx.h"


//  gcc src/gc.c src/hashMap.c tst/hashMap003.c -o x -Wall -pedantic -Wextra


int main ( void ) 
{
    gcStart();

    //hashMap_t    *hm = gcMalloc( sizeof(hashMap_t) )  ;
    hmNew(hm);

    //hashMapInit( hm , hmStringHash, hmStringEq, HM_DEFAULT_LEN, HM_DEFAULT_LOAD_FACTOR);
    hmInitString(hm)

    //hashMapPut        ( hm, gcStrDup("claudio") , gcStrDup("123"), HM_NORMAL );
    hmPutString(hm,gcStrDup("claudio"),gcStrDup("123"));
    
    //hashMapPut        ( hm, gcStrDup("daffra")  , gcStrDup("456"), HM_NORMAL );
    hmPutString(hm,gcStrDup("daffra"),gcStrDup("456"));
    
    void* value=NULL;

    //value = hashMapGet        ( hm, gcStrDup("claudio"), HM_NORMAL );
    value = hmGetString(hm,gcStrDup("claudio"));
    
    printf ( "\nfound si [%s]",(char*)value ) ;

    //hashMapDrop       (hm, gcStrDup("claudio"), HM_NORMAL);
    hmDropString(hm,gcStrDup("claudio"));

    //value = hashMapGet        ( hm, gcStrDup("claudio"), HM_NORMAL );
    value = hmGetString(hm,gcStrDup("claudio"));
    
    printf ( "\nfound no [%s]",(char*)value ) ;
    
    //hashMapDestroy    (hm, HM_NORMAL);
    hmDestroy(hm);

    printf ( "\n" ) ;
    
    gcStop();
    
 return 0 ;
}