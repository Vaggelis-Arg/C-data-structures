#ifndef HASHTABLE_H
#define HASHTABLE_H


typedef struct hashtable Hashtable;

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);

// Function which returns a hash value according to the given key
typedef size_t (*HashFunc)(void *);

// Create and initialize hash table
Hashtable *hashtable_create(CompareFunc compare, DestroyFunc destroy_key, DestroyFunc destroy_value, PrintFunc print, HashFunc hash, HashFunc hash2);

// Function which returns the size of the hash table (how many items does it currently store) or -1 if given hash table does not exist
size_t hashtable_size(Hashtable *h);

// Inserts a [key - value] pair into the hash table (Implementing ADT Map)
// If the key already exists in the hashtable, we are just replaing the value with thw new one (the old value gets lost)
Hashtable *hashtable_insert(Hashtable *h, void *key, void *value);

// Function which searches a value according to the given key and returns the value if it finds the key, otherwise it returns NULL 
void *hashtable_search(Hashtable *h, void *key);

// Deletes node with given key from the hash table
bool hashtable_remove(Hashtable *h, void *key);

// Function which prints the values of the hash table
void hashtable_print(Hashtable *h);

// Destroy hash table - free the memory which is allocated by the hash table
void hashtable_destroy(Hashtable *h);

#endif