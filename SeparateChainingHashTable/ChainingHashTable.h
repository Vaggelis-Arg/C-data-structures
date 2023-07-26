#ifndef CHAINING_HASH_TABLE_H
#define CHAINING_HASH_TABLE_H

typedef struct SChashtable SCHashtable;

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);

// Function which returns a hash value according to the given key
typedef size_t (*HashFunc)(void *);

// Create a new SChashtable
SCHashtable* SChashtable_create(CompareFunc compare, PrintFunc print, DestroyFunc destroy_key, DestroyFunc destroy_value, HashFunc hash);

// Function which returns the size of the hash table (how many items does it currently store) or -1 if given hash table does not exist
size_t SChashtable_size(SCHashtable *h);

// Function to insert an item with given key and value into the hash table
SCHashtable *SChashtable_insert(SCHashtable *h, void *key, void *value);

// Searches an item in the SChashtable according to a specific key
void *SChashtable_search(SCHashtable *h, void *key);

// Delete an item from the hash table
void SChashtable_remove(SCHashtable *h, void *key);

// De-allocate a SChashtable
void SChashtable_destroy(SCHashtable *h);

// Print the SChashtable
void SChashtable_print(SCHashtable *h);

// Get the number of empty buckets
size_t SChashtable_get_num_empty(SCHashtable* h);

// Get the maximum list size
size_t SChashtable_get_max_chain_size(SCHashtable* h);

#endif