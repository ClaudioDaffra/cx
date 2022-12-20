#include "gc.h"

// initialize a hash map structure 

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

short int hash_map_init    (
    hashMap_t* map                                          , 
    unsigned long int   (* hash_fn)    (void* key)          , 
    unsigned char       (* key_comp)   (void* p1, void* p2) , 
    unsigned long int    start_len                          , 
    float                load_factor
)
{
    map->table = calloc(start_len, sizeof(hmNode_t*));
    
    if(!map->table) return HM_ERR_ALLOC;
    
    map->hash_fn         = hash_fn;
    map->key_comp        = key_comp;
    map->size            = start_len;
    map->load_factor     = load_factor;
    map->count           = 0;

    return 0;
}

// add a key-value pair to a hash map, resizing and rehashing if necessary 

short int hash_map_put(hashMap_t* map, void* key, void* value, unsigned short int flags)
{
    hmNode_t* n_node,* s_node;
    unsigned long int node_idx,
    node_hash;

    // perform resize and rehash if necessary 
    if(((float)(++ map->count)) / map->size > map->load_factor)
    {
        unsigned long int i;

        size_t n_len = map->size << 1;
        hmNode_t** temp = calloc(n_len, sizeof(hmNode_t*));
        if(!temp)
        {
            map->count --;
            return HM_ERR_ALLOC;
        }

        // for each element in the table 
        for(i = 0; i < map->size; i ++)
        {
            // traverse down the linked list 
            hmNode_t    * current,
                    * next;

            // guard against empty elements 
            current = map->table[i];
            while(current)
            {
            unsigned long int npos;

            // prepare lookahead pointer 
            next = current->next;

            // rehash and copy each item 
            npos = (map->hash_fn(current->key)) % n_len;
            current->next = temp[npos];
            temp[npos] = current;

            // advance to next list element 
            current = next;
            }
        }

        free(map->table);
        map->table = temp;
        map->size = n_len;
    }

    // check whether item is already in map
    node_hash = (*map->hash_fn)(key);
    node_idx = node_hash % map->size;
    s_node = map->table[node_idx];
    while(s_node)
    {
        if(flags & HM_FAST ? ((map->hash_fn)(s_node->key) == node_hash) : ((map->key_comp)(s_node->key, key)))
        {
            map->count --;

            // deallocate existing value if necessary
            if(flags & HM_DESTROY)
            free(s_node->value);

            // update value and return if found
            s_node->value = value;
            return 0;
        }
        s_node = s_node->next;
    }

    // create a new hmNode_t to hold data 
    n_node = malloc(sizeof(hmNode_t));
    if(!n_node)
    {
        map->count --;
        return HM_ERR_ALLOC;
    }
    n_node->key = key;
    n_node->value = value;
    n_node->next = map->table[node_idx];

    // add new hmNode_t to table 
    map->table[node_idx] = n_node;

    return 0;
}

// get the value associated with a key returns NULL if key does not exist in map
 
void* hash_map_get(hashMap_t* map, void* key, unsigned short int flags)
{
    hmNode_t* current;
    unsigned long int k_hash;

    k_hash = (map->hash_fn)(key);
    current = map->table[k_hash % map->size];
    while(current)
    {
        if(flags & HM_FAST ? (k_hash == (map->hash_fn)(current->key)) : ((map->key_comp(key, current->key))))
        return current->value;

        current = current->next;
    }

    return NULL;
}

// .............................................. hash map at

void* hash_map_at_address(hashMap_t* map, void* key, unsigned short int flags)
{
    hmNode_t* current;
    unsigned long int k_hash;

    k_hash = (map->hash_fn)(key);
    current = map->table[k_hash % map->size];
    while(current)
    {
        if(flags & HM_FAST ? (k_hash == (map->hash_fn)(current->key)) : ((map->key_comp(key, current->key))))
        return &(current->value);

        current = current->next;
    }

    return NULL;
}

// removes an item from the hash map if present (else no-op)

short int hash_map_drop(hashMap_t* map, void* key, unsigned short int flags)
{
    hmNode_t* current,
    * parent = NULL;
    
    unsigned long int k_hash,
    idx;

    k_hash = (map->hash_fn)(key);
    idx = k_hash % map->size;

    current = map->table[idx];
    while(current)
    {
        if(flags & HM_FAST ? ((map->hash_fn)(current->key) == k_hash) : ((map->key_comp)(key, current->key)))
        {
            // redirect the hmNode_t chain around it, then destroy 
            if(parent)
            parent->next = current->next;
            else
            map->table[idx] = current->next;
            if(flags & HM_DESTROY)
            free(current->value);     // key can be freed from calling code; would be too messy to add that here  
            free(current);             // nodes are always malloc'ed  

            // perform resize and rehash if necessary  
            if((map->size > 10) && (-- map->count) / (map->size << 1) < map->load_factor)
            {
                unsigned long int i;

                size_t n_len = map->size >> 1;
                hmNode_t** temp = calloc(n_len, sizeof(hmNode_t*));
                if(!temp)
                {
                    map->count --;
                    return HM_ERR_ALLOC;
                }

                // for each element in the table 
                for(i = 0; i < map->size; i ++)
                {
                    // traverse down the linked list 
                    hmNode_t* current,
                    * next;

                    // guard against empty elements  
                    current = map->table[i];
                    while(current)
                    {
                        unsigned long int npos;

                        // prepare lookahead pointer 
                        next = current->next;

                        // rehash and copy each item  
                        npos = (map->hash_fn(current->key)) % n_len;
                        current->next = temp[npos];
                        temp[npos] = current;

                        // advance to next list element  
                        current = next;
                    }
                }

                free(map->table);
                map->table = temp;
                map->size = n_len;
            }

            // stop looking since hmNode_t was found  
            return 0;
        }

        parent = current;
        current = current->next;
    }

    return HM_NODE_NOTFOUND;
}

// destroys a hash map (does not touch pointed data) 

void hash_map_destroy(hashMap_t* map, unsigned short int flags1,unsigned short int flags2 )
{
    unsigned long int i;
    hmNode_t* current,* next;

    // goes down each list, deleting all nodes  
    for(i = 0; i < map->size; i++)
    {
        current = map->table[i];
        while(current)
        {
            next = current->next;

            if(flags1==HM_DESTROY) free(current->key);
            if(flags2==HM_DESTROY) free(current->value);
    
            free(current);
            current = next;
        }
    }

    // deletes the table  
    free(map->table);
}


// .............................................. gc map hash clear

void gc_hash_map_destroy(hashMap_t* map, unsigned short int flags)
{
    unsigned long int i;
    hmNode_t    * current,* next;

    // goes down each list, deleting all nodes
    
    for(i = 0; i < map->size; i++)
    {
        current = map->table[i];
        while(current)
        {
            next = current->next;
            if(flags & HM_DESTROY)
            {

                fCallBack_t *cb = (fCallBack_t*) &current->value ;

                HM_DEBUG_PRINTF ( "gc_hash_map_destroy free ptr %p dtor %p %p\n"
                                    ,current->key,current->value , *cb );

                (*cb)(current->key);
            }
            free(current);
            current = next;
        }
    }

    // deletes the table 
    free(map->table);
}



// simple "hash" function (uses pointer as hash code) 

unsigned long int hm_default_hash_fn(void* key)
{
    return (unsigned long int) key;
}

// ......................................................     simple string hash function 

unsigned long int hm_string_hash_fn(void* key)
{
    unsigned long int hash = 0;
    char* string = key;

    while(*string)
    {
        hash += *string; 
        // addition followed by multiplication makes collisions of 
        // scrambled strings with the same characters less likely 
        hash *= 7;
        string ++;
    }

    return hash;
}

unsigned long int hm_stringw_hash_fn(void* key)
{
    unsigned long int hash = 0;
    wchar_t* string = key;

    while(*string)
    {
        hash += *string; 
        // addition followed by multiplication makes collisions of 
        // scrambled strings with the same characters less likely
        hash *= 7;
        string ++;
    }

    return hash;
}


// ......................................................    HM simple equality checker hash map

unsigned char  hm_default_key_comp(void* p1, void* p2)
{
    return p1 == p2;
}

unsigned char  hm_string_hash_key_comp(void* p1, void* p2)
{
    return !strcmp((char*)p1, (char*)p2);
}

unsigned char  hm_stringw_key_comp(void* p1, void* p2)
{
    return !wcscmp((wchar_t*)p1, (wchar_t*)p2);
}

// ......................................................    GC simple equality checker  qsort

int gc_int_key_comp (const void * a, const void * b)
{
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
  return 1;
}
int gcCompareStrC ( const void * a, const void * b ) 
{
    const char **pa = (const char **)a;
    const char **pb = (const char **)b;
    return strcmp(*pa, *pb);   
    
}
int gcCompareWStrC ( const void * a, const void * b ) 
{
    const wchar_t **pa = (const wchar_t **)a;
    const wchar_t **pb = (const wchar_t **)b;
    return wcscmp(*pa, *pb);  
}
int gcComparepStrC ( const void * a, const void * b ) 
{
    const char *pa = (const char *)a;
    const char *pb = (const char *)b;
    return strcmp(pa, pb);   
    
}
int gcComparepWStrC ( const void * a, const void * b ) 
{
    const wchar_t *pa = (const wchar_t *)a;
    const wchar_t *pb = (const wchar_t *)b;
    return wcscmp(pa, pb);  
}
int gcCompareInt(const void* a, const void* b)
{
  int va = *(const int*) a;
  int vb = *(const int*) b;
  return (va > vb) - (va < vb);
}

int gcCompareFloat (const void * a, const void * b)
{
  float fa = *(const float*) a;
  float fb = *(const float*) b;
  return (fa > fb) - (fa < fb);
}

int gcCompareDouble (const void * a, const void * b)
{
  double fa = *(const double*) a;
  double fb = *(const double*) b;
  return (fa > fb) - (fa < fb);
}

int gcCompareFloatAsInt (const void * a, const void * b)
{
  float _fa = *(const float*) a;
  float _fb = *(const float*) b;
  int fa = (int)_fa;
  int fb = (int)_fb;
  return (fa > fb) - (fa < fb);
}
int gcCompareDoubleAsInt (const void * a, const void * b)
{
  double _fa = *(const double*) a;
  double _fb = *(const double*) b;
  int fa = (int)_fa;
  int fb = (int)_fb;  
  return (fa > fb) - (fa < fb);
}
// ....................................................................... gcallback gcFreeDtor

void gcFreeDtor( void * ptr )
{
    if (ptr!=NULL) free(ptr) ;
}

// ....................................................................... gcallback gcFCloseDtor

void gcFCloseDtor( FILE * ptr )
{
    if (ptr!=NULL) fclose(ptr);
}

// ....................................................................... gcLocalStart

void* gcLocalStart(void)
{
    gc_t *map = (hashMap_t*)malloc ( sizeof(hashMap_t) ) ;
    hash_map_init ( map , hm_default_hash_fn , hm_default_key_comp , HM_DEFAULT_LEN , HM_DEFAULT_LOAD_FACTOR ) ;
    
    return map ;
}

// ....................................................................... gcLocalMalloc

void* gcLocalMalloc(gc_t *map , size_t SIZE )
{
    void* ptr= (void*) malloc ( SIZE );
    
    hash_map_put(   map, ptr , (void*)gcFreeDtor, HM_FAST);
    HM_DEBUG_PRINTF ( "gcMalloc ptr==%p , dtor==%p \n",ptr,gcFreeDtor ) ;
    
    return ptr ;
}

// ....................................................................... gcLocalPush

void* gcLocalPush(gc_t *map , void* ptr, size_t SIZE )
{
    hash_map_put( map, ptr , (void*)gcFreeDtor, HM_FAST );
    
    HM_DEBUG_PRINTF ( "gcPush ptr==%p , dtor==%p \n",ptr,gcFreeDtor ) ;
    
    return ptr ;
}

// ....................................................................... gcLocalOpen

FILE* gcLocalFileOpen(gc_t *map , const char* fileName , const char* flag)
{
    FILE* ptr= fopen ( fileName , flag ) ;
    hash_map_put(   map, (void*)ptr , (void*)gcFCloseDtor, HM_FAST);
    HM_DEBUG_PRINTF ( "gcOpen ptr==%p , dtor==%p \n",ptr,gcFCloseDtor ) ;
    
    return ptr ;
}

// ....................................................................... gcLocalFree

void* gcLocalFree(gc_t *map , void *ptr)
{
    if (ptr==NULL)
    {
            HM_DEBUG_PRINTF ( "gcFree ptr==NULL \n") ;
            return NULL ;
    } ;
    // recupera il distruttore
   void *dtor = hash_map_get ( map , ptr , HM_FAST ) ;
   
   // chiama il distrutore
   if (dtor!=NULL)
   {
        fCallBack_t *cb = (fCallBack_t*) &dtor ;

        (*cb)(ptr);

        HM_DEBUG_PRINTF ( "gcFree ptr==%p , dtor==%p %p \n",ptr,dtor,*cb ) ;
   }
   else
   {
        HM_DEBUG_PRINTF ( "gcFree dtor==NULL \n") ;
        
        return NULL ;  
   }
   
   // libera lo spazio
   hash_map_drop(   map, ptr ,  HM_NORMAL);
   
   return ptr;
}

// ....................................................................... gcLocalPop

void* gcLocalPop(gc_t *map , void *ptr)
{
    if (ptr==NULL)
    {
        HM_DEBUG_PRINTF ( "gcPop ptr==NULL \n") ;
        return NULL ;
    } ;
    
    // recupera il distruttore
   void *dtor = hash_map_get ( map , ptr , HM_FAST ) ;
   
   // chiama il distrutore
   if (dtor!=NULL)
   {
       fCallBack_t *cb = (fCallBack_t*) &dtor ;

       HM_DEBUG_PRINTF ( "gcPop ptr==%p , dtor==%p %p \n",ptr,dtor,*cb ) ;
   }
   else
   {
        HM_DEBUG_PRINTF ( "gcPop dtor==NULL \n") ;
        
        return NULL ;  
   }
   // libera lo spazio
   hash_map_drop( map, ptr ,  HM_NORMAL );
   
   return ptr ;
}

// ....................................................................... gcLocalStop

void* gcLocalStop(gc_t *map )
{
    gc_hash_map_destroy(map,HM_DESTROY);
    free(map);
    return map=NULL;
}


// ....................................................................... gcLocalRealloc

void* gcLocalRealloc( gc_t *map, void* P , size_t N )
{
    if (P==NULL) return gcLocalMalloc(map,N);

    void* old=P;
    P = (void*) realloc ( P,N ) ;

    //gcPop(old);
   
    gcLocalPop ( map,old ) ;
   
    //gcPush(P) ;
   
    gcLocalPush ( map,P,N ) ;
   
    assert ( P != NULL ) ;
   
    return P ;
}

// ....................................................................... hmNew

void* hmNew(void)
{
    gc_t *map = (hashMap_t*)malloc ( sizeof(hashMap_t) ) ;
    
    hash_map_init ( map , hm_default_hash_fn , hm_default_key_comp , HM_DEFAULT_LEN , HM_DEFAULT_LOAD_FACTOR ) ;
    
    return map ;
}

// ....................................................................... hmDelete

void hmDelete( hashMap_t *hm )
{
    hash_map_destroy(hm,HM_noDESTROY,HM_noDESTROY);
    free(hm);
}
void hmDeleteKey( hashMap_t *hm )
{
    hash_map_destroy(hm,HM_DESTROY,HM_noDESTROY);
    free(hm);
}
void hmDeleteKeyValue( hashMap_t *hm )
{
    hash_map_destroy(hm,HM_DESTROY,HM_DESTROY);
    free(hm);
}

// ......................................................     hash clear
 
hashMap_t* hm_hash_map_clear(hashMap_t* hm)
{
    void * hmKeyComp     = hm->key_comp ;
    void * hmHash        = hm->hash_fn  ;
    hmDelete(hm);

    hm   = hmNew();
    
    hm->hash_fn     = hmKeyComp ;
    hm->key_comp    = hmHash ;
    
    return hm ;
}

void* hmFind( hashMap_t *hm , void* key )
{
    return hash_map_get( hm , key , HM_FAST ) ;
}

// ....................................................................... gc Dup

char* gcStrLocalDup( gc_t* gc,char* str)
{
    char *tmp=strdup(str);
    hash_map_put(   gc, (void*)tmp , (void*)gcFreeDtor, HM_FAST);
    return tmp ;
}

wchar_t* gcWcsLocalDup( gc_t* gc,wchar_t* str)
{
    wchar_t *tmp=wcsdup(str);
    hash_map_put(   gc, (void*)tmp , (void*)gcFreeDtor, HM_FAST);
    return tmp ;
}

// ................................................................... intDup

int* gcIntLocalDup( gc_t* gc,int val)
{
    int* p=(int*)  gcMalloc ( sizeof(int) );
    *p=val;
    return p ;
}

// ................................................................... doubleDup

double* gcDoubleLocalDup( gc_t* gc, double val )  
{
    double* p = (double*) gcMalloc ( sizeof(double) );
    *p=val;
    return p ;
}

// ........................................................................ gc hash map iterator

void hmIterator(hashMap_t* map , void* (*cb)(void*) )
{
    unsigned long int i;
    hmNode_t* current,* next;

    for(i = 0; i < map->size; i++)    // iterate all node
    {
        current = map->table[i];
        while(current)
        {
            (*cb)(current->value);
            next = current->next;
            current = next;
        }
    }

}

// ........................................................................ test hm

void* hmPrintValueCB( void * value )
{
    printf ( "{{{%p}}}",value) ;
    return NULL ;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#endif

/**/

