/* File: list.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


struct listnode {
    void *key;
    void *value;
    List next;
};


// Function to add an element at the end of the list
List list_append(List list, void *key, void *value) {
    
    List node = malloc(sizeof(*node));
    assert(node != NULL);
    
    node->next = NULL;
    node->key = key;
    node->value = value;

    if(list == NULL)
        list = node;
    else {
        List cur = list;
        while(cur->next != NULL)
            cur = cur->next;
        cur->next = node;
    }
    return list;
}


// Function to add an element at the start of the list
List list_prepend(List list, void *key, void *value) {
    
    List node = malloc(sizeof(*node));
    assert(node != NULL);

    node->key = key;
    node->value = value;
    node->next = list;

    return node;
}


// Function to search an item into the list and return a boolean value which demonstrates whether it exists or not
void *list_search(List list, void *key, CompareFunc compare) {
    List cur = list;

    while(cur != NULL) {
        if(!compare(cur->key, key))
            return cur->value;
        cur = cur->next;
    }
    
    return NULL;
}


// Function to delete an item from the list
List list_delete(List list, void *key, CompareFunc compare, DestroyFunc destroy_key, DestroyFunc destroy_value) {
    List cur = list;
    List prev = NULL;
    while(cur != NULL) {
        if(!compare(cur->key, key)) {
            if(prev == NULL) {
                List next = cur->next;
                if(destroy_key)
                    destroy_key(cur->key);
                if(destroy_value)
                    destroy_value(cur->value);
                free(cur);
                return next;
            }
            else {
                prev->next = cur->next;
                if(destroy_key)
                    destroy_key(cur->key);
                if(destroy_value)
                    destroy_value(cur->value);
                free(cur);
                return list;
            }
        }
        prev = cur;
        cur = cur->next;
    }
    return list;
}


// Function to return the size of a list
size_t list_size(List list) {
    List cur = list;
    size_t count = 0;

    while(cur != NULL) {
        count++;
        cur = cur->next;
    }
    
    return count;
}


// Function de-allocate a list
void list_free(List list, DestroyFunc destroy_key, DestroyFunc destroy_value) {
    while(list != NULL) {
        List temp = list;
        list = list->next;
        if(destroy_key != NULL)
            destroy_key(temp->key);
        if(destroy_value != NULL)
            destroy_value(temp->value);
        free(temp);
    }
}


// Helper function to print a list
void list_print(List list, PrintFunc print) {
    printf("[");
    while(list != NULL) {
        print(list->value);
        list = list->next;
    }
    printf("]\n");
}


// Function to merge two lists
List list_merge(List list1, List list2) {
    List temp = list1;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = list2;
    return list1;
}


// Get the key of the given node
void *listnode_get_key(List node) {
    return node->key;
}


// Get the value of the given node
void *listnode_get_value(List node) {
    return node->value;
}


// Get next list node
List list_get_next(List list) {
    return list->next;
}


// Get first node of the given list
List list_get_first(List list) {
    return list;
}


// Get last node of the given list
List list_get_last(List list) {
    if(list == NULL)
        return NULL;
    while(list->next != NULL)
        list = list->next;
    return list;
}