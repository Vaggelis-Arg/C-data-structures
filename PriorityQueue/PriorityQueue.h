/* File: PriorityQueue.h */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);


/* The priority queue of this file is implemented using a max-heap */

typedef struct priority_queue *PriorityQueue;

// Initialize the priority queue
PriorityQueue PQ_initialize(size_t capacity, CompareFunc compare, DestroyFunc destroy, PrintFunc print);

// Check if the priority queue is empty
bool PQ_empty(const PriorityQueue PQ);

// Function to return the current size of the priority queue
size_t PQ_size(const PriorityQueue PQ);

// Insert an item into the priority queue
bool PQ_insert(PriorityQueue PQ, void *data);

// Remove the item with the highest priority from the priority queue
void *PQ_remove(PriorityQueue PQ);

// Print the items of the priority queue as they are located in the heap 
void PQ_print(const PriorityQueue PQ);

// Destroy priority queue
void PQ_destroy(PriorityQueue PQ);

#endif