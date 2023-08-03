/* File: PriorityQueue.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "PriorityQueue.h"


struct priority_queue {
    void **array;
    size_t capacity;
    size_t size;
    CompareFunc compare;
    PrintFunc print;
    DestroyFunc destroy;
};


// Initialize the priority queue
PriorityQueue PQ_initialize(size_t capacity, CompareFunc compare, DestroyFunc destroy, PrintFunc print) {
    
    PriorityQueue PQ = malloc(sizeof(*PQ));
    assert(PQ != NULL);
    
    PQ->capacity = capacity + 1;
    
    PQ->array = calloc(PQ->capacity, sizeof(*PQ->array));
    assert(PQ->array != NULL);

    PQ->size = 0;
    PQ->compare = compare;
    PQ->print = print;
    PQ->destroy = destroy;
    
    return PQ;
}


// Check if the priority queue is empty
bool PQ_empty(const PriorityQueue PQ) {
    assert(PQ != NULL);
    return PQ->size == 0;
}


// Function to return the current size of the priority queue
size_t PQ_size(const PriorityQueue PQ) {
    assert(PQ != NULL);
    return PQ->size;
}


// Insert an item into the priority queue
bool PQ_insert(PriorityQueue PQ, void *new_data) {
    assert((PQ != NULL) && (new_data != NULL));

    PQ->size++;
    if (PQ->size == PQ->capacity) {
        fprintf(stderr, "Priority Queue is full. Given item cannot be inserted.\n");
        return false;
    }

    // Start from the leaf nodes and go up to find the right position to insert the data
    size_t ChildLoc = PQ->size;
    size_t ParentLoc = ChildLoc / 2;

    while (ParentLoc != 0) { // While root has not been reached
        if (PQ->compare(new_data, PQ->array[ParentLoc]) <= 0) {
            // If the given data is considered to be less than or equal to the data in the position ParentLoc of the PQarray,
            // then we found the right position for the data
            PQ->array[ChildLoc] = new_data;
            return true;
        }
        else {
            // Otherwise, we move the item in the Parent location down, and the new positions where we are supposed to
            // insert the new data become the current parent location
            PQ->array[ChildLoc] = PQ->array[ParentLoc];
            ChildLoc = ParentLoc;
            ParentLoc /= 2;
        }
    }
    PQ->array[ChildLoc] = new_data;
    return true;
}



// Remove the item with the highest priority from the priority queue
void *PQ_remove(PriorityQueue PQ) {
    
    assert(PQ != NULL);

    if(PQ_empty(PQ))
        return NULL;

    void *ItemToReturn = PQ->array[1], *ItemToPlace = PQ->array[PQ->size];

    PQ->size--;

    // By removing the root-item a problem is occured in the priority queue. We should fix this problem by
    // finding the location of the ItemToPlace (which initially is the last item into the priority queue) 
    // To to this we should swap it with data that have greater values so as to put it in the right position.

    size_t CurrentLoc = 1;
    size_t ChildLoc = 2 * CurrentLoc;

    while(ChildLoc <= PQ->size) {
        if(ChildLoc < PQ->size)
            // if there is a right child, compare it to the left child and choose the one with the larger value
            if(PQ->compare(PQ->array[ChildLoc], PQ->array[ChildLoc + 1]) < 0)
                ChildLoc++;

        if(PQ->compare(PQ->array[ChildLoc], ItemToPlace) <= 0) {
            // If the child has a smaller or equal value than ItemToPlace then place ItemToPlace at the
            // current location and return the removed item
            PQ->array[CurrentLoc] = ItemToPlace;
            return ItemToReturn;
        }
        else {
            // If the child has a larger value than ItemToPlace swap it 
            // with its parent and make the child location as the new current location 
            PQ->array[CurrentLoc] = PQ->array[ChildLoc];
            CurrentLoc = ChildLoc;
            ChildLoc = 2 * CurrentLoc;
        }
    }
    PQ->array[CurrentLoc] = ItemToPlace;

    return ItemToReturn;
}


// Print the items of the priority queue as they are located in the heap 
void PQ_print(const PriorityQueue PQ) {
    assert((PQ != NULL) && (PQ->print != NULL));
    for(size_t i = 1 ; i <= PQ->size ; i++)
        if(PQ->array[i] != NULL)
            PQ->print(PQ->array[i]);
}


// Destroy priority queue
void PQ_destroy(PriorityQueue PQ) {
    assert(PQ != NULL);
    for(int i = 1 ; i <= PQ->size ; i++)
        if(PQ->destroy)
            PQ->destroy(PQ->array[i]);
    free(PQ->array);
    free(PQ);
}