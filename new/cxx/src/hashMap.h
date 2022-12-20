

#ifndef CD_HASH_MAP
#define CD_HASH_MAP

// *****************
// hash map
// *****************

unsigned long int     hm_default_hash_fn           ( void* key) ;
unsigned long int     hm_string_hash_fn            ( void* key) ;
unsigned long int     hm_stringw_hash_fn           ( void* key) ;
unsigned char         hm_default_key_comp          ( void* p1, void* p2) ;
unsigned char         hm_string_hash_key_comp      ( void* p1, void* p2) ;
unsigned char         hm_stringw_key_comp          ( void* p1, void* p2) ;
void*                 hmNew                        ( void) ;
void                  hmDelete                     ( hashMap_t *hm ) ;
void                  hmDeleteKey                  ( hashMap_t *hm ) ;
void                  hmDeleteKeyValue             ( hashMap_t *hm ) ;
void*                 hmFind                       ( hashMap_t *hm , void* key ) ;
void                  hmIterator                   ( hashMap_t* map , void* (*cb)(void*) ) ;
void*                 hmPrintValueCB               ( void * value ) ;
hashMap_t*            hm_hash_map_clear            ( hashMap_t* hm) ;

#define hmInsert(HM,KEY,VALUE)      hash_map_put( HM, KEY , VALUE, HM_FAST)
#define hmReplace(HM,KEY,VALUE)     hash_map_put( HM, KEY , VALUE, HM_FAST)
#define hmErase(MAP,PTR)            hash_map_drop( MAP,PTR ,  HM_FAST);
#define hmEmpty(MAP)                (!(MAP->count))
#define hmCount(MAP)                (MAP->count)
#define hmSize(MAP)                 (MAP->size)
#define hmAt(MAP,KEY)               hash_map_at_address( MAP , KEY , HM_FAST )
#define hmAssign( ADDRESS,TYPE )    *( (TYPE*) ADDRESS )
#define hmClear(MAP)                MAP=hm_hash_map_clear(MAP)

#define hmItForEach(hm)\
    for(int i = 0; i < hm->size; i++)\
    {\
        hmNode_t* it = hm->table[i] , *next;\
        while(it)\
        {\

#define hmItNext(hm)\
            next = it->next;\
            it = next;\
        }\
    }     
        
#endif


/**/


