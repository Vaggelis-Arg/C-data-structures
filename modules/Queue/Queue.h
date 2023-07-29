/* File: Queue.h */
#ifndef QUEUE_H
#define QUEUE_H


#include <stdbool.h>

typedef struct queue *Queue;

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);

// Create a Queue
Queue Queue_create(const DestroyFunc destroy, const PrintFunc print);

// Return the number of items that the Queue holds
unsigned int Queue_size(Queue Q);

// Returns a boolean variable which demonstrates whether the Queue is empty or not
bool Queue_empty(Queue Q);

// Insert given data into the Queue
void Queue_insert(Queue Q, void *data);

// Remove the front item from the Queue
void *Queue_remove(Queue Q);

// Print the items in the Queue
void Queue_print(Queue Q);

// Free the Queue
void Queue_destroy(Queue Q);

#endif