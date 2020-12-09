 
//------------------------------------------------------------
// c-- : HASH MAP
//------------------------------------------------------------

#include "hmap.h"
#include "../lib/gc.h"

void linked_list_init(linked_list *list, linked_list_destructor free_data) 
{
	// Allocate a sentinel node
	linked_list_node *sentinel = gcMalloc(sizeof(linked_list_node));
	sentinel->next = NULL;
	list->head = sentinel;

	list->free_data = free_data;

	list->size = 0;
}

linked_list_node *linked_list_head(linked_list *list) 
{
	return list->head->next;
}

void linked_list_append(linked_list *list, void *data) 
{
	linked_list_node *node = list->head;
	while (node->next) {
		node = node->next;
	}
	linked_list_node *new_node = gcMalloc(sizeof(linked_list_node));
	new_node->data = data;
	new_node->next = NULL;
	node->next = new_node;

	list->size++;
}

void linked_list_prepend(linked_list *list, void *data) 
{
	linked_list_node *new_node = gcMalloc(sizeof(linked_list_node));
	new_node->data = data;
	new_node->next = list->head->next;
	list->head->next = new_node;

	list->size++;
}

void linked_list_free(linked_list *list) 
{
	linked_list_node *previous_node = list->head;
	linked_list_node *current_node = previous_node->next;

	while (current_node != NULL) {
		if (list->free_data != NULL) 
        {
            gcPop(current_node->data);
			list->free_data(current_node->data);
		}
		gcFree(previous_node);
		previous_node = current_node;
		current_node = previous_node->next;
	}

	gcFree(previous_node);

	list->head = NULL;

	gcFree(list);
}

size_t linked_list_size(linked_list *list) 
{
	return list->size;
}

static inline int hash_map_default_comparator(const void *l, const void *r) 
{
	return *((unsigned long *) l) - *((unsigned long *) r);
}

static inline size_t hash_map_default_hash_func(const void *key, size_t capacity) 
{
	return *((size_t *) key) % capacity;
}

void hash_map_init(
    hash_map            *map, 
    size_t              capacity, 
    hash_map_comparator comparator, 
    hash_map_hash_func  hash_func
) 
{
	map->capacity = capacity;
	map->size = 0;

	map->table = (linked_list **) gcMalloc(sizeof(linked_list *) * map->capacity);
	memset(map->table, 0, sizeof(linked_list *) * map->capacity);

	if (comparator) {
		map->comparator = comparator;
	} else {
		map->comparator = hash_map_default_comparator;
	}

	if (hash_func) {
		map->hash_func = hash_func;
	} else {
		map->hash_func = hash_map_default_hash_func;
	}

	map->keys = (linked_list *) gcMalloc(sizeof(linked_list));
	// No free_data func here because keys will be free'd by linked_list_free for **table
	linked_list_init(map->keys, NULL);
}

void hash_map_free(hash_map *map) 
{
	for (size_t i = 0; i < map->capacity; i++) 
    {
		if (map->table[i]) 
        {
			linked_list_free(map->table[i]);
		}
	}

	linked_list_free(map->keys);

	gcFree(map->table);

	gcFree(map);
}

void *hash_map_get(hash_map *map, void *key) 
{
	linked_list *list = map->table[map->hash_func(key, map->capacity)];

	if (!list) 
    {
		return NULL;
	}

	linked_list_node *head = linked_list_head(list);

	while (head) 
    {
		hash_map_pair *pair = (hash_map_pair *) head->data;

		if (map->comparator(pair->key, key) == 0) 
        {
			return pair->value;
		}

		head = head->next;
	}

	return NULL;
}

void hash_map_put(hash_map *map, void *key, void *value) 
{
	linked_list *list = map->table[map->hash_func(key, map->capacity)];

	if (!list) 
    {
		list = (linked_list *) gcMalloc(sizeof(linked_list));
		linked_list_init(list, (linked_list_destructor) free ) ;
		map->table[map->hash_func(key, map->capacity)] = list;
	}

	linked_list_node *head = linked_list_head(list);

	while (head) 
    {
		hash_map_pair *pair = (hash_map_pair *) head->data;

		// if key already exists, update the value
		if (map->comparator(pair->key, key) == 0) 
        {
			pair->value = value;
			return;
		}

		head = head->next;
	}

	// or else insert new one

	hash_map_pair *pair = (hash_map_pair *) gcMalloc(sizeof(hash_map_pair));
	pair->key = key;
	pair->value = value;

	linked_list_prepend(list, pair);

	linked_list_append(map->keys, key);

	map->size++;
}

void hash_map_remove(hash_map *map, void *key) 
{
	size_t offset = map->hash_func(key, map->capacity);
	linked_list *list = map->table[offset];

	if (!list) 
    {
		return;
	}

	// The variable previous_node is set to the sentinel node, NOT the
	// head item of the list.
	linked_list_node *previous_node = list->head;
	linked_list_node *current_node = previous_node->next;
	while (true) 
    {
		// Is the first node a match?
		if (map->comparator(((hash_map_pair *)current_node->data)->key, key) == 0) 
        {
			// Delete the node and relink.
			previous_node->next = current_node->next;
			if (list->free_data) 
            {
                gcPop(current_node->data);
				list->free_data(current_node->data);
			}
			gcFree(current_node);
			// Decrement structure sizes
			list->size--;
			map->size--;
			return;
		}
		// Exit when we are at the end.
		if (current_node->next == NULL) 
        {
			break;
		}
		// Increment
		previous_node = current_node;
		current_node = current_node->next;
	}
}

size_t hash_map_size(hash_map *map) 
{
	return map->size;
}

linked_list *hash_map_keys(hash_map *map) 
{
	return map->keys;
}

void hash_map_clear(hash_map *map) 
{
	for (size_t i = 0; i < map->capacity; i++) 
    {
		linked_list *list = map->table[i];

		if (list) 
        {
			linked_list_free(list);
			map->table[i] = NULL;
		}
	}

	map->size = 0;
}

bool hash_map_contains_key(hash_map *map, void *key) 
{
	linked_list *list = map->table[map->hash_func(key, map->capacity)];

	if (!list) 
    {
		return false;
	}

	linked_list_node *head = linked_list_head(list);

	while (head) 
    {
		hash_map_pair *pair = (hash_map_pair *) head->data;

		if (map->comparator(pair->key, key) == 0) 
        {
			return true;
		}

		head = head->next;
	}

	return false;
}
// GNU GCC 9.2 : lib/hmap.c:299:39: warning: 
// ISO C forbids conversion of object pointer to function pointer type [-Wpedantic] C11
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif
hmap_t* cd_map_def(void* cmp ) 
{
	hmap_t* map = gcMalloc(sizeof(hash_map));
	hash_map_init(map, cd_map_max_size , (hash_map_comparator) cmp , NULL);
	return map ;
}

hmap_t* cd_map_new(void) 
{
	hmap_t* map = gcMalloc(sizeof(hash_map));
	hash_map_init(map, cd_map_max_size , (hash_map_comparator) strcmp, NULL);
	return map ;
}

hmap_t* cd_mapw_new(void) 
{
	hmap_t* map = gcMalloc(sizeof(hash_map));
	hash_map_init(map, cd_map_max_size , (hash_map_comparator) wcscmp, NULL);
	return map ;
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
size_t cd_map_count(hmap_t* map) 
{
	return map->size ;
}

size_t cd_map_capacity(hmap_t* map) 
{
	return map->capacity ;
}

bool cd_map_empty(hmap_t* map) 
{
	if (  map->size == 0 ) return true;
	return false ;
}

void* cd_map_get_begin( hmap_t* x )
{
	linked_list *keys_list = hash_map_keys(x);
	linked_list_node *node = linked_list_head(keys_list);
	
	do	{
		if ( hash_map_get( x , node->data )!=NULL )	return node ; 
		node = node->next;		
	} while ( node->next!=NULL ) ;
	
	return NULL ;
}
void* cd_map_get_end( hmap_t* x )
{
	linked_list *keys_list = hash_map_keys(x);
	linked_list_node *node = linked_list_head(keys_list);
	
	do	{
		node = node->next;		
	} while ( node->next!=NULL ) ;
	
	return node->next ;
}


hmapIterator_t* cd_map_get_next( hmap_t* x,hmapIterator_t* it )
{
	// questo perchè nella lista sono presenti tutte le chiave anche quelle eliminate 
	hmapIterator_t* end = cd_map_get_end( x ) ;

	do {
	   it = it->next ;
	   if ( it == end ) return end ;		
	} 
	while ( (hash_map_get(x, (char*)it->data)==0 ) ) ;

	return it ;
}


hmapIterator_t* cd_wmap_get_next( whmap_t* x,hmapIterator_t* it )
{
	// questo perchè nella lista sono presenti tutte le chiave anche quelle eliminate 
	hmapIterator_t* end = cd_map_get_end( x ) ;

	do {
	   it = it->next ;
	   if ( it == end ) return end ;		
	} 
	while ( (hash_map_get(x, (wchar_t*)it->data)==0 ) ) ;

	return it ;
}

void* cd_map_get_at( hmap_t* x,size_t k )
{
	size_t i=0;
	size_t max = cd_map_count(x);
	
 	for ( hmapIterator_t* it=cd_map_get_begin(x) ; it != cd_map_get_end(x) ; it = cd_map_get_next(x,it) )  
	{
		if ( i>max) return NULL ;
		if ( i==k) return it->data ;
		++i;
	}
	return NULL ;
}

hmap_t* cd_map_get_copy( hmap_t* to,hmap_t* x    )
{
	hash_map_clear ( to ) ;
	
  	for ( hmapIterator_t* it=cd_map_get_begin(x) ; it != cd_map_get_end(x) ; it = cd_map_get_next(x,it) )  
	{
		const char * value = (const char*)	hash_map_get(x,it->data) ;
		hash_map_put ( to , it->data , (void*) value ) ;
	}   
	return NULL ;
}

hmap_t* cd_wmap_get_copy( hmap_t* to,hmap_t* x    )
{
	hash_map_clear ( to ) ;
	
  	for ( hmapIterator_t* it=cd_map_get_begin(x) ; it != cd_map_get_end(x) ; it = cd_map_get_next(x,it) )  
	{
		const wchar_t * value = (const wchar_t*)	hash_map_get(x,it->data) ;
		hash_map_put ( to , it->data , (void*) value ) ;
	}   
	return NULL ;
}

hmap_t* cd_map_swap( hmap_t* x,hmap_t* y  )
{
 	hash_map* temp = cd_map_new();
	
	cd_map_get_copy ( temp , x ) ;
	hash_map_clear ( x ) ;	
    
	cd_map_get_copy ( x , y ) ;	
	hash_map_clear ( y ) ;	
	
	cd_map_get_copy ( y, temp ) ;
	hash_map_free(temp);
	
	return NULL ;
}

hmapIterator_t* cd_map_get_iterator( hmap_t* x,char *_key )
{
  	for ( hmapIterator_t* it=cd_map_get_begin(x) ; it != cd_map_get_end(x) ; it = cd_map_get_next(x,it) )  
	{
		 if ( strcmp ( _key , (char*)it->data )==0 ) return it ;
	}   
	return NULL ;
}

hmapIterator_t* cd_wmap_get_iterator( hmap_t* x,wchar_t *_key )
{
  	for ( hmapIterator_t* it=cd_map_get_begin(x) ; it != cd_map_get_end(x) ; it = cd_map_get_next(x,it) )  
	{
		 if ( wcscmp ( _key , (wchar_t*)it->data )==0 ) return it ;
	}   
	return NULL ;
}

struct hmap_n hmap = 
{
    // string
	cd_map_new          ,       //  .new
	hash_map_put        ,       //  .insert
	hash_map_get        ,       //  .find
	hash_map_free       ,       //  .delete
	cd_map_count        ,       //  .size
	cd_map_capacity     ,       //  .capacity
	cd_map_capacity     ,       //  .max_size	
	hash_map_remove     ,       //  .erase
	cd_map_empty        ,       //  .empty
	cd_map_empty        ,       //  .empty
	hash_map_clear      ,       //  .celar
	cd_map_get_begin    ,       //  .begin	
	cd_map_get_end      ,       //  .end
	cd_map_get_next     ,       //  .next
	cd_map_get_at       ,       //  .at
	cd_map_get_copy     ,       //  .copy
	cd_map_swap         ,       //  .swap
	cd_map_get_iterator ,       //  iterator
	cd_map_get_iterator ,       //  iterator	
	cd_map_get_iterator ,       //  iterator
    cd_map_def	        ,       //  def ( comparator ) 
} ;
	
 
struct whmap_n whmap =
{
    // wstring
	cd_mapw_new             , 
	hash_map_put            ,
	hash_map_get            ,
	hash_map_free           ,
	cd_map_count            ,
	cd_map_capacity         ,
	cd_map_capacity         ,	
	hash_map_remove         ,
	cd_map_empty            ,
	cd_map_empty            ,
	hash_map_clear          ,
	cd_map_get_begin        ,	
	cd_map_get_end          ,
	cd_wmap_get_next        ,   
	cd_map_get_at           ,
	cd_wmap_get_copy        ,    
	cd_map_swap             ,
	cd_wmap_get_iterator    ,  
	cd_wmap_get_iterator    ,  	
	cd_wmap_get_iterator    ,  	
    // no comparator
} ;

 
/**/

