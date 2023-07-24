/* File: ChainingHashTable.h */
#ifndef CHAINING_HASH_TABLE_H
#define CHAINING_HASH_TABLE_H

typedef struct hashtable Hashtable;

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);

// Function which returns a hash value according to the given key
typedef size_t (*HashFunc)(void *);

// Create a new hashtable
Hashtable* hashtable_create(CompareFunc compare, PrintFunc print, DestroyFunc destroy_key, DestroyFunc destroy_value, HashFunc hash);

// Function which returns the size of the hash table (how many items does it currently store) or -1 if given hash table does not exist
size_t hashtable_size(Hashtable *h);

// Function to insert an item with given key and value into the hash table
Hashtable *hashtable_insert(Hashtable *h, void *key, void *value);

// Searches an item in the hashtable according to a specific key
void *hashtable_search(Hashtable *h, void *key);

// Delete an item from the hash table
void hashtable_remove(Hashtable *h, void *key);

// De-allocate a hashtable
void hashtable_destroy(Hashtable *h);

// Print the hashtable
void hashtable_print(Hashtable *h);

// Get the number of empty buckets
size_t hashtable_get_num_empty(Hashtable* h);

// Get the maximum list size
size_t hashtable_get_max_chain_size(Hashtable* h);

#endif