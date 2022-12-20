
#include "../src/cxx.h"


//    clear  ; gcc  src/gc.c tst/hashMap001.c   -o bin/x    -Wall -Wextra  -pedantic
//    cls   &  cl   src\gc.c tst\hashMap001.c   /Febin\x.exe /WX /utf-8

int main(void)
{
    gcStart();

     // ........................................ inzializza mappa
         
    hashMap_t *hm     = hmNew();
    hm->hash_fn     = hm_string_hash_fn ;
    hm->key_comp     = hm_string_hash_key_comp ;
 
    void* res    =    NULL;   
    char *key     =     gcStrDup("claudio") ;
 
     printf ( "\n element count %lu size %lu empty %d \n",hmCount(hm),hmSize(hm),hmEmpty(hm) );
       
     // ........................................ inserisce elementi
     
    hmInsert(   hm,  key      , (void*)0x1605 );
    hmInsert(   hm, "daffra"  , (void*)0x1606 ); 

    hmInsert(   hm, "daffra1" , (void*)0x1601 ); 
    hmInsert(   hm, "daffra2" , (void*)0x1602 ); 
    hmInsert(   hm, "daffra3" , (void*)0x1603 ); 
    hmInsert(   hm, "daffra4" , (void*)0x1604 ); 
 

     // ........................................ iterator callback
     
    printf("\n");    
    hmIterator(hm,hmPrintValueCB); 

     // ........................................ iterator for each
     
    printf("\n");
    hmItForEach(hm);
    
    printf ( "(((%p)))",it->value) ;
    
    hmItNext(hm);
    
    printf("\n");
        
     // ........................................ trova elemento 'daffra'  presente    ,    inserito
     // ........................................ trova elemento 'claudio' presente    ,    inserito 
     
    res= hmFind( hm , "daffra" );
    if (res!=NULL) printf ( " daffra -> %p\n ", res );   
    
     printf ( "\n element count %lu size %lu empty %d \n",hmCount(hm),hmSize(hm),hmEmpty(hm) );
   
    res = hmFind( hm , "claudio" );
    if (res!=NULL) printf ( " claudio -> %p\n ", res );   
 
      // ........................................ trova elemento 'claudio' non presente , non inserito
         
    res = hmFind( hm , "barbara" );;
    if (res!=NULL) printf ( " barbara -> %p\n ", res );   
    else printf ( " not found barbara -> %p\n ", NULL );

      // ........................................ cancella elemento 'claudio'
      
    res = hmFind( hm , "claudio" );
    if (res!=NULL) printf ( " before erase claudio -> %p\n ", res );      
     
      hmErase ( hm , "claudio" );

    res= hmFind( hm , "claudio" );
    if (res!=NULL) printf ( " after erase 'claudio' -> %p\n ", res );   
    else  printf ( " after erase non present 'claudio' \n ");


      // ........................................ at
      
    void *address = hmAt( hm , "daffra"  ) ;
      
    printf ( "\n ### adrress of value of 'daffra' = %p.\n",address );

      // ........................................ assign

    hmAssign( address , int ) = 0x1234 ;

    hmAssign( hmAt( hm , "daffra" ) , int ) = 0x5678 ;

    res= hmFind( hm , "daffra" );
    if (res!=NULL) printf ( " after at 'daffra' -> %p\n ", res );   
    else  printf ( " after at non present 'daffra' \n ");
        

      // ........................................ cancella elementi
      
    hmClear( hm );
     
    printf ( "\n !!! CLEAR -> element count %lu size %lu empty %d \n",hmCount(hm),hmSize(hm),hmEmpty(hm) );
                            
    // ........................................ cancella mappa
      
    hmDelete(hm);

    gcStop();
    
    printf ( "\n") ;
    
    return 0;
}