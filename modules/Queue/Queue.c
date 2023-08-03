/* File: Queue.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Queue.h"


typedef struct qnode queue_node;

struct qnode {
    void *data;
    queue_node *next;
};


struct queue {
    queue_node *head;
    queue_node *tail;
    unsigned int size;
    PrintFunc print;
    DestroyFunc destroy;
};


// Create a Queue
Queue Queue_create(const DestroyFunc destroy, const PrintFunc print) {
    Queue Q = malloc(sizeof(*Q));
    assert(Q != NULL);
    Q->head = Q->tail = NULL;
    Q->size = 0;
    Q->print = print;
    Q->destroy = destroy;
    return Q;
}


// Return the number of items that the Queue holds
unsigned int Queue_size(Queue Q) {
    if(Q == NULL)
        return 0;
    return Q->size;
}


// Returns a boolean variable which demonstrates whether the Queue is empty or not
bool Queue_empty(Queue Q) {
    if(Q == NULL)
        return true;
    return Q->size == 0;
}


// Insert given data into the Queue
void Queue_insert(Queue Q, void *data) {
    if(Q == NULL) {
        fprintf(stderr, "Cannot insert an item into a Queue which is not initialized\n");
        return;
    }

    queue_node *new_node = malloc(sizeof(*new_node));
    assert(new_node != NULL);

    new_node->data = data;
    new_node->next = NULL;
    
    Q->size++;
    
    if(Q->head == NULL)
        Q->head = Q->tail = new_node;
    else {
        Q->tail->next = new_node;
        Q->tail = new_node;
    }
}


// Remove the front item from the Queue
void *Queue_remove(Queue Q) {
    if(Queue_empty(Q))
        return NULL;
    queue_node *data = Q->head->data;
    if(Q->size == 1) {
        free(Q->head);
        Q->head = Q->tail = NULL;
    }
    else {
        queue_node *temp = Q->head;
        Q->head = Q->head->next;
        free(temp);
    }
    Q->size--;
    return data;
}


// Print the items in the Queue
void Queue_print(Queue Q) {
    queue_node *temp = Q->head;
    printf("Queue is: [");
    while(temp != NULL) {
        Q->print(temp->data);
        if(temp->next != NULL)
            printf(", ");
        temp = temp->next;
    }
    printf("]\n");
}



// Free the Queue
void Queue_destroy(Queue Q) {
    if(Q == NULL)
        return;
    while(Q->head != NULL) {
        queue_node *temp = Q->head;
        Q->head = Q->head->next;
        if(Q->destroy)
            Q->destroy(temp->data);
        free(temp);
    }
    free(Q);
}