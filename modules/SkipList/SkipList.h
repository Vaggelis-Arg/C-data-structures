/*File: SkipList.h */
#ifndef SKIPLIST_H
#define SKIPLIST_H


#define SKIPLIST_MAX_LEVEL 6

typedef struct skiplist skiplist;


// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);


// Function to initialize the skip list
skiplist *skiplist_initialize(CompareFunc compare, PrintFunc print, DestroyFunc destroy_key, DestroyFunc destroy_value);

// Returns the size ofthe list
size_t skiplist_get_size(skiplist *list);

// Function to insert a key and the corresponding value in the skiplist
void skiplist_insert(skiplist *list, void *key, void *value);

// Search a value into the skiplist according to the given key
void *skiplist_search(skiplist *list, void *key);

// Delete the node -which holds the given key- from the skiplist
void *skiplist_delete(skiplist *list, void *key);

// Display Skip List (node's are printed with their levels)
void skiplist_print(skiplist *list);

// Function to merge two skiplists and return the new one
skiplist *skiplist_merge(skiplist *list1, skiplist *list2);

// Free the memory which is allocated by the skip list
void skiplist_destroy(skiplist *list);

#endif