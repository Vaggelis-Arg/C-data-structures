/*File: DoubleLinkedList.h*/
#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef struct listnode *Listptr;

#include <stdbool.h>

typedef struct {
    Listptr head;
    Listptr tail;
} DLlist;

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);

//Initialize list (and return the pointers of the head and the tail of it)
void DLL_Create(Listptr *head, Listptr *tail);

//returns size of the list
int DLL_Size(Listptr head, Listptr tail);

//Check if list is empty and return 0 if not, otherwise return 1
bool DLL_IsEmpty(Listptr list);

//returns the item of the first node of the list
void *DLL_GetFirst(Listptr head);

//returns the item of the last node of the list
void *DLL_GetLast(Listptr tail);

//returns a pointer to the first node of the list which contains the item "i"
Listptr DLL_GetNode(Listptr head, void *i, CompareFunc compare);

//returns the data of the given node
void *DLL_GetData(Listptr node);

//returns the item of the previous node from the given node 
void *DLL_GetPrev(Listptr node);

//returns the item of the next node from the given node
void *DLL_GetNext(Listptr node);

//add a node with data i before the given node
void DLL_AddBefore(Listptr *node, void *i, Listptr *head);

//add a node with data i after the given node
void DLL_AddAfter(Listptr *node, void *i, Listptr *tail);

//add a node with data-item "i" at the beginning of the list
void DLL_AddFirst(Listptr *head, Listptr *tail, void *i);

//add a node with data-item "i" at the end of the list
void DLL_AddLast(Listptr *tail, Listptr *head, void *i);

//removes all the nodes with data "i" from the list
void DLL_Remove(Listptr *head, Listptr *tail, void *i, CompareFunc compare, DestroyFunc destroy);

//print the items of the list from the first one to the last one
void DLL_print(Listptr head, PrintFunc print);

//free the double linked list
void DLL_freelist(Listptr head, Listptr tail, DestroyFunc destroy);

#endif