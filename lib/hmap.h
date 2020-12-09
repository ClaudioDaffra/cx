#ifndef cdHMAP
#define cdHMAP

#ifdef __linux__
#define _GNU_SOURCE 
#endif

//------------------------------------------------------------ 
// HASH MAP
//------------------------------------------------------------


#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdint.h>
#include <stdbool.h>

#include "../lib/gc.h"

/**
 * Function to deallocate data pointers. For automatically allocated
 * memory, pass in `NULL` to call nothing. For memory allocated with
 * `malloc`, pass in `free`.
 */
typedef void (*linked_list_destructor)(const void *data);

/**
 * Linked list node structure
 */
typedef struct _linked_list_node 
{
	/** Pointer to the next node */
	struct _linked_list_node *next;
	/** Pointer to data */
	void *data;
} linked_list_node;

/**
 * Linked list object
 */
typedef struct 
{
	/** Pointer to sentinel node */
	linked_list_node *head;
	/** Function used to free data */
	linked_list_destructor free_data;
	/** Size of the linked_list */
	size_t size;
} linked_list;

/**
 * Initialize a linked list.
 * @param list linked list structure
 * @param comparator data comparator function
 * @param free_list data de-allocation function
 */
void linked_list_init(linked_list *list, linked_list_destructor free_list);

/**
 * Get the first linked list node.
 * @param list linked list structure
 * @return first linked list node
 */
linked_list_node *linked_list_head(linked_list *list);

/**
 * Append data to the list.
 * @param list linked list structure
 * @param data data to append
 */
void linked_list_append(linked_list *list, void *data);

/**
 * Prepend data to the list.
 * @param list linked list structure
 * @param data data to prepend
 */
void linked_list_prepend(linked_list *list, void *data);

/**
 * Free the linked list and all its nodes and data. Uses @ref
 * linked_list_destructor function passed to @ref linked_list_init
 * @param list linked list structure
 */
void linked_list_free(linked_list *list);

/**
 * Returns size of the linked list.
 * @param list linked list structure
 * @return size of list
 */
size_t linked_list_size(linked_list *list);

/**
 * Comparator function to determine whether `*l` and `*r` are equal.
 * @return Negative if `*l` is less than `*r`; zero if `*l` is equal 
 *         to `*r`; positive if `*l` is greater than `*r`.
 */
typedef int (*hash_map_comparator)(const void *l, const void *r);

/**
 * Hash function
 * @param key key to hash
 * @param capacity maximum size of the map
 * @return an offset within the range `[0, capacity)`
 */
typedef size_t (*hash_map_hash_func)(const void *key, size_t capacity);


/*********************************
 * Hash map object
**********************************/

typedef struct 
{
	/** Maximum size of hash table */
	size_t capacity;
	/** Size of hash table */
	size_t size;
	/** Hash table */
	linked_list **table;
	/** Key comparator function */
	hash_map_comparator comparator;
	/** Key hash function */
	hash_map_hash_func hash_func;
	/** Keys */
	linked_list *keys;
} hash_map;

/*********************************
 * Key/value pair
 *********************************/
 
typedef struct 
{
	/** Key */
	void *key;
	/** Value */
	void *value;
} hash_map_pair;

/**
 * Initialize the hash map.
 * @param map hash map structure
 * @param capacity maximum size of the hash map
 * @param comparator key comparator function
 * @param hash_func key hash function
 */
void 
hash_map_init
(
    hash_map            *map, 
    size_t              capacity, 
    hash_map_comparator comparator, 
    hash_map_hash_func  hash_func
);

/**
 * Free the hash map.
 * This function will also free the table of internal linked lists.
 * @param map hash map structure
 */
void hash_map_free(hash_map *map);

/**
 * Get the value for the given key.
 * @param map hash map structure
 * @param key key for value to fetch
 * @return pointer to the value
 */
void *hash_map_get(hash_map *map, void *key);

/**
 * Insert the value into the map.
 * @param map hash map structure
 * @param key key associated with value
 * @param value value associated with key
 */
void hash_map_put(hash_map *map, void *key, void *value);

/**
 * Remove the mapping from the map if this key exists. Calling this on
 * a key for which there is no mapping does nothing (does not error).
 * @param map hash map structure
 * @param key key for mapping to remove
 */
void hash_map_remove(hash_map *map, void *key);

/**
 * Returns number of key-value pairs in the map
 * @param map hash map structure
 * @return size of the hash map
 */
size_t hash_map_size(hash_map *map);

/**
 * Returns a linked list that contains all keys in the map
 * @param map hash map structure
 * @return a linked list containing all keys
 */
linked_list *hash_map_keys(hash_map *map);

/**
 * Removes all key/value pairs from the map
 * @param map hash map structure
 */
void hash_map_clear(hash_map *map);

/**
 * Check if the map contains the given key
 * @param map hash map structure
 * @param key the key to check
 * @return true if map contains key
 */
bool hash_map_contains_key(hash_map *map, void *key);


#define hmap_t          hash_map 
#define hmapIterator_t  linked_list_node 
#define hmapIt_t        linked_list_node 

#define whmap_t         hash_map 
#define whmapIterator_t linked_list_node 
#define whmapIt_t       linked_list_node 

// valore di default inizializzazione mappa

#define cd_map_max_size 1024

hmap_t* cd_map_new  (void) ;
hmap_t* cd_mapw_new (void) ;
 
size_t          cd_map_count        (hmap_t*    map             );
size_t          cd_map_capacity     (hmap_t*    map             );
bool            cd_map_empty        (hmap_t*    map             );
void*           cd_map_get_begin    (hmap_t*    x               );
void*           cd_map_get_end      (hmap_t*    x               );
void*           cd_map_get_at       (hmap_t*    x   ,size_t k   );
hmap_t*         cd_map_get_copy     (hmap_t*    to  ,hmap_t* x  );
hmap_t*         cd_wmap_get_copy    (whmap_t*   to  ,hmap_t* x  );
hmap_t*         cd_map_swap         (hmap_t*    x   ,hmap_t* y  );
hmap_t*         cd_map_def          (void* cmp ) ;

hmapIterator_t* cd_map_get_iterator (hmap_t*    x   ,char *         _key    );
hmapIterator_t* cd_wmap_get_iterator(hmap_t*    x   ,wchar_t *      _key    );
hmapIterator_t* cd_map_get_next     (hmap_t*    x   ,hmapIterator_t* it     );
hmapIterator_t* cd_wmap_get_next    (whmap_t*   x   ,hmapIterator_t* it     );


struct hmap_n
{
    // string
	hmap_t* 		(*new)			(void);
	void 			(*insert)		(hash_map * map , void *key, void *value    ); 
	void *			(*find)			(hash_map * map , void *key                 ); 
	void 			(*delete)		(hash_map * map                             );  
	size_t 			(*size)			(hmap_t*    map                             );	
	size_t 			(*capacity)		(hmap_t*    map                             );	
	size_t 			(*max_size)		(hmap_t*    map                             );		
	void 			(*erase)		(hash_map * map , void *key                 );	
	bool 			(*empty)		(hmap_t*    map                             );
	bool 			(*is_empty)		(hmap_t*    map                             );
	void 			(*clear)		(hash_map * map                             );
	void* 			(*begin)		(hmap_t*    x                               );
	void* 			(*end) 			(hmap_t*    x                               );
	hmapIterator_t* (*next)			(hmap_t*    x   ,hmapIterator_t*    it      );
	void* 			(*at)			(hmap_t*    x   ,size_t             k       );
	hmap_t* 		(*copy)			(hmap_t*    to  ,hmap_t*            x       );
	hmap_t* 		(*swap)			(hmap_t*    x   ,hmap_t*            y       );
	hmapIterator_t* (*iterator)		(hmap_t*    x   ,char *             _key    );
	hmapIterator_t* (*lower_bound)	(hmap_t*    x   ,char *             _key    );
	hmapIterator_t* (*upper_bound)	(hmap_t*    x   ,char *             _key    );
    hmap_t*         (*def)          (void* cmp ) ;   
} ;

struct whmap_n
{
    // wstring
	hmap_t* 		(*new)			(void);
	void 			(*insert)		(hash_map * map ,   void *key, void *value  ); 
	void *			(*find)			(hash_map * map ,   void *key               ); 
	void 			(*delete)		(hash_map * map                             );  
	size_t 			(*size)			(hmap_t*    map                             );	
	size_t 			(*capacity)		(hmap_t*    map                             );	
	size_t 			(*max_size)		(hmap_t*    map                             );		
	void 			(*erase)		(hash_map * map ,   void *key               );	
	bool 			(*empty)		(hmap_t*    map                             );
	bool 			(*is_empty)		(hmap_t*    map                             );
	void 			(*clear)		(hash_map * map                             );
	void* 			(*begin)		(hmap_t*    x                               );
	void* 			(*end) 			(hmap_t*    x                               );
	hmapIterator_t* (*next)			(hmap_t*    x   ,   hmapIterator_t* it      );
	void* 			(*at)			(hmap_t*    x   ,   size_t k                );
	hmap_t* 		(*copy)			(hmap_t*    to  ,   hmap_t* x               );
	hmap_t* 		(*swap)			(hmap_t*    x   ,   hmap_t* y               );
	hmapIterator_t* (*iterator)		(hmap_t*    x   ,   wchar_t *_key           );
	hmapIterator_t* (*lower_bound)	(hmap_t*    x   ,   wchar_t *_key           );
	hmapIterator_t* (*upper_bound)	(hmap_t*    x   ,   wchar_t *_key           );
} ;

extern struct hmap_n  hmap ;
extern struct whmap_n whmap ;
 
#define hmapType(ID)    hmap_t* ID
#define hmapNew(ID)	    ID=hmap.new() 

#define hmapInsert	    hash_map_put 
#define hmapFind	    hash_map_get  
#define hmapDelete	    hash_map_free 
#define hmapSize	    cd_map_count 
#define hmapCapacity	cd_map_capacity 
#define hmapMaxSize	    cd_map_capacity 
#define hmapErase   	hash_map_remove 
#define hmapEmpty	    cd_map_empty 
#define hmapEmpty	    cd_map_empty 
#define hmapClear	    hash_map_clear 
#define hmapBegin	    cd_map_get_begin 
#define hmapEnd     	cd_map_get_end 
#define hmapAt	        cd_map_get_at
#define hmapCopy        cd_map_get_copy 
#define hmaSwap	        cd_map_swap 
#define hmapIterator	cd_map_get_iterator
#define hmapIterator    cd_map_get_iterator 
#define hmapIterator    cd_map_get_iterator 
#define itHmap          hmapIterator
 
#define whmapType(ID)    whmap_t* ID 
#define whmapNew(ID)     ID = whmap.new()  
 
#define whmapInsert	    hash_map_put 
#define whmapFind	    hash_map_get  
#define whmapDelete	    hash_map_free 
#define whmapSize	    cd_map_count 
#define whmapCapacity	cd_map_capacity 
#define whmapMaxSize    cd_map_capacity 
#define whmapErase   	hash_map_remove 
#define whmapEmpty	    cd_map_empty 
#define whmapEmpty	    cd_map_empty 
#define whmapClear	    hash_map_clear 
#define whmapBegin	    cd_map_get_begin 
#define whmapEnd     	cd_map_get_end 
#define whmapAt	        cd_map_get_at
#define whmapCopy       cd_wmap_get_copy 
#define whmaSwap	    cd_map_swap 

#define whmapIterator	cd_wmap_get_iterator
#define whmapIterator   cd_wmap_get_iterator 
#define whmapIterator   cd_wmap_get_iterator
#define itWHmap         whmapIterator

#define hmapNext(x,it)      (it)=cd_map_get_next(x,(it)) 
#define hmapData(it)        (const char*)(it)->data  
#define whmapNext(x,it)     (it)=cd_wmap_get_next((x),(it)) 
#define whmapData(it)       (wchar_t*)(it)->data       

// hmap with comparator 

#define hmapDef(CMP)     cd_map_def(CMP) 
#define whmapDef(CMP)    cd_map_def(CMP) 
    
#endif /* cdHMAP */



/**/


