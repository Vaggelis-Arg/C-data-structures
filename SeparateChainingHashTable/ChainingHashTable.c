/* File: ChainingHashTable.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "ChainingHashTable.h"
#include "./LinkedLists/list.h"


#define MAX_LOAD_FACTOR 0.75

static int prime_numbers[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
	786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};


struct hashtable {
    size_t size;
    size_t table_capacity;
    List *table;
    CompareFunc compare; 
    PrintFunc print; 
    DestroyFunc destroy_key;
    DestroyFunc destroy_value;
    HashFunc hash_function;
};


// Create a new hashtable
Hashtable* hashtable_create(CompareFunc compare, PrintFunc print, DestroyFunc destroy_key, DestroyFunc destroy_value, HashFunc hash) {
    Hashtable *h = malloc(sizeof(Hashtable));
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
size_t hashtable_size(Hashtable *h) {
    if(h == NULL){
        fprintf(stderr, "Given hash table does not exist\n");
        return -1;
    }
    return h->size;
}


// Hash function : returns the hash value according to the given key 
static inline size_t hashtable_hash(Hashtable *h, void *key) {
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


// Resize the hashtable
static Hashtable* hashtable_resize(Hashtable* h) {
    // Save the old table and capacity of the array of the hash table
    List* old_table = h->table;
    size_t old_capacity = h->table_capacity;

    // Find the new capacity for the hashtable
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
            new_table[hashtable_hash(h, key)] = list_prepend(new_table[hashtable_hash(h, key)], key, value);
            list = list_get_next(list);
        }
        list_free(old_table[i], NULL, NULL);
    }

    // Free the old table and update the hashtable
    free(old_table);
    h->table = new_table;

    return h;
}


// Get the current load factor of the hash table
static inline float hashtable_get_load_factor(Hashtable* h) {
    return ((float) h->size) / ((float) (h->table_capacity));
}


// Function to insert an item with given key and value into the hash table
Hashtable *hashtable_insert(Hashtable *h, void *key, void *value) {
    size_t index = hashtable_hash(h, key);
    
    // Delete item with the same key if it exists in the hashtable
    // Current implementation is an ADTMap, so we do not want to
    // have duplicates
    h->table[index] = list_delete(h->table[index], key, h->compare, h->destroy_key, h->destroy_value);
    
    h->size++;
    // Add the new item in the start of the corresponding list
    // This saves us time, because inserting at sthe start needs
    // only O(1) complexity
    h->table[index] = list_prepend(h->table[index], key, value);

    if(hashtable_get_load_factor(h) > MAX_LOAD_FACTOR)
        return hashtable_resize(h);
    return h;
}


// Searches an item in the hashtable according to a specific key
void *hashtable_search(Hashtable *h, void *key) {
    if(h == NULL)
        return NULL;
    return list_search(h->table[hashtable_hash(h, key)], key, h->compare);
}


// Delete an item from the hash table
void hashtable_remove(Hashtable *h, void *key) {
    h->table[hashtable_hash(h, key)] = list_delete(h->table[hashtable_hash(h, key)], key, h->compare, h->destroy_key, h->destroy_value);
}


// De-allocate a hashtable
void hashtable_destroy(Hashtable *h) {
    for(size_t i = 0 ; i < h->table_capacity ; i++)
        list_free(h->table[i], h->destroy_key, h->destroy_value);
    free(h->table);
    free(h);
}


// Print the hashtable
void hashtable_print(Hashtable *h) {
    printf("\nHashtable format:\n");
    for(int i = 0 ; i < h->table_capacity ; i++) {
        printf("%d: ", i);
        list_print(h->table[i], h->print);
    }
}


// Get the number of empty buckets
size_t hashtable_get_num_empty(Hashtable* h) {
    size_t empty = 0;
    for (int i = 0 ; i < h->table_capacity ; i++) {
        if (h->table[i] == NULL)
            empty++;
    }
    return empty;
}


// Get the maximum list size
size_t hashtable_get_max_chain_size(Hashtable* h) {
    size_t max = 0;
    for (int i = 0 ; i < h->size ; i++) {
        size_t size = list_size(h->table[i]);
        if (size > max)
            max = size;
    }
    return max;
}