/* File: list.h */
#ifndef LIST_H
#define LIST_H

typedef struct listnode *List;

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);


// Function to add an element at the end of the list
List list_append(List list, void *key, void *value);

// Function to add an element at the start of the list
List list_prepend(List list, void *key, void *value);

// Function to search an item into the list and return a boolean value which demonstrates whether it exists or not
void *list_search(List list, void *key, CompareFunc compare);

// Function to delete an item from the list
List list_delete(List list, void *key, CompareFunc compare, DestroyFunc destroy_key, DestroyFunc destroy_value);

// Function to return the size of a list
size_t list_size(List list);

// Function de-allocate a list
void list_free(List list, DestroyFunc destroy_key, DestroyFunc destroy_value);

// Helper function to print a list
void list_print(List list, PrintFunc print);

// Function to merge two lists
List list_merge(List list1, List list2);

// Get the key of the given node
void *listnode_get_key(List node);

// Get the value of the given node
void *listnode_get_value(List node);

// Get next list node
List list_get_next(List list);

// Get first node of the given list
List list_get_first(List list);

// Get last node of the given list
List list_get_last(List list);

#endif