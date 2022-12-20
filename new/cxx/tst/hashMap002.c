#include "../src/gc.h"
#include "../src/hashMap.h"


// clear    ; gcc src/gc.c tst/hashMap002.c     -o bin/x    -Wall -Wextra  -pedantic
// cls      & cl src\gc.c  tst\hashMap002.c     /Febin\x.exe   /WX /utf-8

int main(void)
{
    gcStart();
    
        hashMap_t       *hm = hmNew();
        
        hm->hash_fn     = hm_stringw_hash_fn ;
        hm->key_comp    = hm_stringw_key_comp ;
        
        wchar_t *key = gcWcsDup(L"claudio") ;
      
        hmInsert(   hm,  key      , (void*)0xff );
        hmInsert(   hm, L"daffra" , (void*)0x16 ); 

        void* res=NULL;
        
        res = hmFind( hm , L"claudio" );
        if (res!=NULL) wprintf ( L" claudio -> %p\n ", res );   
        
        res = hmFind( hm , L"barbara" );
        
        if (res!=NULL) wprintf ( L" barbara -> %p\n ", res );   
        else wprintf ( L" not found barbara -> %p\n ", NULL );

        hmDelete(hm);

    gcStop();
    
    wprintf ( L"\n") ;
    
    return 0;
}