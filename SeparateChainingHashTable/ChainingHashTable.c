/* File: ChainingSCHashTable.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "ChainingHashTable.h"
#include "./LinkedLists/list.h"


#define MAX_LOAD_FACTOR 0.75

static int prime_numbers[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
	786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};


/* Separate chaining hash table */
struct SChashtable {
    size_t size;
    size_t table_capacity;
    List *table;
    CompareFunc compare; 
    PrintFunc print; 
    DestroyFunc destroy_key;
    DestroyFunc destroy_value;
    HashFunc hash_function;
};


// Create a new SChashtable
SCHashtable* SChashtable_create(CompareFunc compare, PrintFunc print, DestroyFunc destroy_key, DestroyFunc destroy_value, HashFunc hash) {
    SCHashtable *h = malloc(sizeof(SCHashtable));
    assert(h != NULL);
    h->table_capacity = prime_numbers[0];
    h->size = 0;
    h->table = calloc(h->table_capacity, sizeof(List));
    assert(h->table != NULL);
    h->compare = compare;
    h->print = print;
    h->destroy_key = destroy_key;
    h->destroy_value = destroy_value;
    h->hash_function = hash;
    return h;
}


// Function which returns the size of the hash table (how many items does it currently store) or -1 if given hash table does not exist
size_t SChashtable_size(SCHashtable *h) {
    if(h == NULL){
        fprintf(stderr, "Given hash table does not exist\n");
        return -1;
    }
    return h->size;
}


// Hash function : returns the hash value according to the given key 
static inline size_t SChashtable_hash(SCHashtable *h, void *key) {
    return h->hash_function(key) % h->table_capacity;
}


// Check if given number is prime 
static bool isprime(size_t n) {
	if((n % 2 == 0 && n != 2) || (n % 3 == 0 && n != 3))
		return false;
	int divisor;
	for(divisor = 5 ; divisor*divisor <= n ; divisor += 6)
		if((n % divisor == 0) || (n % (divisor + 2) == 0))
			return false;
	return true;
}


// Resize the SChashtable
static SCHashtable* SChashtable_resize(SCHashtable* h) {
    // Save the old table and capacity of the array of the hash table
    List* old_table = h->table;
    size_t old_capacity = h->table_capacity;

    // Find the new capacity for the SChashtable
    size_t new_capacity = 0;
    int primes = sizeof(prime_numbers) / sizeof(int);
    for (int i = 0; i < primes ; i++)
        if (prime_numbers[i] > old_capacity) {
            new_capacity = prime_numbers[i];
            break;
        }
    if (new_capacity == 0) {
        new_capacity = old_capacity * 2;
        while (!isprime(++new_capacity));
    }

    // Create a new table with the new capacity
    h->table_capacity = new_capacity;
    List* new_table = calloc(h->table_capacity, sizeof(*new_table));
    assert(new_table != NULL);
    
    // Rehash and insert all elements from the old table to the new table
    for(int i = 0 ; i < old_capacity ; i++) {
        List list = old_table[i];
        while(list != NULL) {
            void *key = listnode_get_key(list);
            void *value = listnode_get_value(list);
            new_table[SChashtable_hash(h, key)] = list_prepend(new_table[SChashtable_hash(h, key)], key, value);
            list = list_get_next(list);
        }
        list_free(old_table[i], NULL, NULL);
    }

    // Free the old table and update the SChashtable
    free(old_table);
    h->table = new_table;

    return h;
}


// Get the current load factor of the hash table
static inline float SChashtable_get_load_factor(SCHashtable* h) {
    return ((float) h->size) / ((float) (h->table_capacity));
}


// Function to insert an item with given key and value into the hash table
SCHashtable *SChashtable_insert(SCHashtable *h, void *key, void *value) {
    size_t index = SChashtable_hash(h, key);
    
    // Delete item with the same key if it exists in the SChashtable
    // Current implementation is an ADTMap, so we do not want to
    // have duplicates
    h->table[index] = list_delete(h->table[index], key, h->compare, h->destroy_key, h->destroy_value);
    
    h->size++;
    // Add the new item in the start of the corresponding list
    // This saves us time, because inserting at sthe start needs
    // only O(1) complexity
    h->table[index] = list_prepend(h->table[index], key, value);

    if(SChashtable_get_load_factor(h) > MAX_LOAD_FACTOR)
        return SChashtable_resize(h);
    return h;
}


// Searches an item in the SChashtable according to a specific key
void *SChashtable_search(SCHashtable *h, void *key) {
    if(h == NULL)
        return NULL;
    return list_search(h->table[SChashtable_hash(h, key)], key, h->compare);
}


// Delete an item from the hash table
void SChashtable_remove(SCHashtable *h, void *key) {
    h->table[SChashtable_hash(h, key)] = list_delete(h->table[SChashtable_hash(h, key)], key, h->compare, h->destroy_key, h->destroy_value);
}


// De-allocate a SChashtable
void SChashtable_destroy(SCHashtable *h) {
    for(size_t i = 0 ; i < h->table_capacity ; i++)
        list_free(h->table[i], h->destroy_key, h->destroy_value);
    free(h->table);
    free(h);
}


// Print the SChashtable
void SChashtable_print(SCHashtable *h) {
    printf("\nSCHashtable format:\n");
    for(int i = 0 ; i < h->table_capacity ; i++) {
        printf("%d: ", i);
        list_print(h->table[i], h->print);
    }
}


// Get the number of empty buckets
size_t SChashtable_get_num_empty(SCHashtable* h) {
    size_t empty = 0;
    for (int i = 0 ; i < h->table_capacity ; i++) {
        if (h->table[i] == NULL)
            empty++;
    }
    return empty;
}


// Get the maximum list size
size_t SChashtable_get_max_chain_size(SCHashtable* h) {
    size_t max = 0;
    for (int i = 0 ; i < h->size ; i++) {
        size_t size = list_size(h->table[i]);
        if (size > max)
            max = size;
    }
    return max;
}