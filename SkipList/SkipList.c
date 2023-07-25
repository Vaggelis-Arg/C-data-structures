/* File: SkipList.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "SkipList.h"
// PUT AGAIN SRAND TIME NULL


struct skiplist_node {
    void *key;
    void *value;
    int level;
    link *forward;
};


struct skiplist {
    int level;
    int size;
    link header;
    CompareFunc compare;
    PrintFunc print;
    DestroyFunc destroy_key;
    DestroyFunc destroy_value;
};


// Create a new node
static inline link create_node(void *value, void *key, int level) {
    link new_node = malloc(sizeof(*new_node));
    new_node->value = value;
    new_node->key = key;
    new_node->level = level;
    new_node->forward = calloc(sizeof(link), new_node->level + 1);
    for(int i = 0 ; i <= level ; i++)
        new_node->forward[i] = NULL;
    return new_node;
}


// Function to initialize the skip list
skiplist *skiplist_initialize(CompareFunc compare, PrintFunc print, DestroyFunc destroy_key, DestroyFunc destroy_value) {
    // srand(time(NULL));
    skiplist *list = malloc(sizeof(*list));
    assert(list != NULL);
    list->header = create_node(NULL, NULL, SKIPLIST_MAX_LEVEL);
    list->level = list->size = 0;
    list->compare = compare;
    list->print = print;
    list->destroy_key = destroy_key;
    list->destroy_value = destroy_value;
    return list;
}


// Generate and return a random number
static int rand_level(void) {
    int level = 0;
    // We generate a new j-link node with probability 1/2^j
    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;
    return level;
}

// Returns the size ofthe list
size_t skiplist_get_size(skiplist *list) {
    return list->size;
}


// Returns the value of a link node of the skip list
void *link_get_value(link x) {
    return x->value;
}

// Function to insert a key and the corresponding value in the skiplist
void skiplist_insert(skiplist *list, void *key, void *value) {
    link update[SKIPLIST_MAX_LEVEL + 1], current = list->header;
    int i, level;
    // In a skip list we scan the levels in descending order
    for(i = list->level ; i >= 0 ; i--) {
        while(current->forward[i] != NULL && list->compare(current->forward[i]->key, key) < 0)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];

    if(current != NULL && !list->compare(key, current->key)) {
        // key already exists, so swap the old value with the new one
        if(list->destroy_value)
            list->destroy_value(current->value);
        if(list->destroy_key)
            list->destroy_key(key);
        current->value = value;
    }
    else {
        // key does not exist, so we should create a new node with the given key and value
        level = rand_level();
        if(level > list->level) {
            // if the new generated level is greater than every other level, we should update the level of the list
            for(i = list->level + 1 ; i <= level ; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }
        
        current = create_node(value, key, level);
        list->size++;

        // Insert the new node at the correct positions on each level using the 'update' array
        for(i = 0 ; i <= level ; i++) {
            current->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = current;
        }
    }
}


// Search a value into the skiplist according to the given key
void *skiplist_search(skiplist *list, void *key) {
    link x = list->header;
    for(int i = list->level ; i >= 0 ; i--) {
        while(x->forward[i] != NULL && list->compare(x->forward[i]->key, key) <= 0) {
            x = x->forward[i];
            if(x != NULL && list->compare(x->key, key) == 0)
                return x->value;
        }
    }
    return NULL;
}


// Delete the node -which holds the given key- from the skiplist
void *skiplist_delete(skiplist *list, void *key) {
    link update[SKIPLIST_MAX_LEVEL + 1], current = list->header;
    int i;
    // In a skip list we scan the levels in descending order
    for(i = list->level ; i >= 0 ; i--) {
        while(current->forward[i] != NULL && list->compare(current->forward[i]->key, key) < 0)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];

    if(current != NULL && !list->compare(key, current->key)) {
        
        for(i = 0 ; i <= list->level ; i++) {
            if(update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i];
        }
        
        list->size--;
        while (list->header->forward[list->level] == NULL && list->level > 0)
            list->level--;
        
        void *value = current->value;
        if(list->destroy_key)
            list->destroy_key(current->key);
        free(current->forward);
        free(current);
        
        return value;
    }
    return NULL;
}


// Display Skip List (node's are printed with their levels)
void skiplist_print(skiplist *list) {
    if(list == NULL || list->header == NULL)
        return;
    printf("Skip List:\n");
    for(int  i = 0 ; i <= list->level ; i++) {
        link current = list->header->forward[i];
        printf("Level %d: ", i);
        while(current != NULL) {
            list->print(current->value);
            printf(" ");
            current = current->forward[i];
        }
        printf("\n");
    }
}


// Function to merge two skiplists and return the new one
skiplist *skiplist_merge(skiplist *list1, skiplist *list2) {
    if (list1 == NULL && list2 == NULL)
        return NULL;
    else if (list1 == NULL)
        return list2;
    else if (list2 == NULL)
        return list1;
    link *update = calloc(SKIPLIST_MAX_LEVEL + 1, sizeof(link));
    int unflipped = 1;
    skiplist *list = skiplist_initialize(list1->compare, list1->print, list1->destroy_key, list1->destroy_value);
    list->level = (list1->level > list2->level) ? list1->level : list2->level;
    for (int i = 0; i <= list->level; i++)
        update[i] = list->header;
    while ((list1 != NULL && list1->header != NULL && list1->header->forward[0] != NULL) && (list2 != NULL && list2->header != NULL && list2->header->forward[0] != NULL)) {
        void *key1 = list1->header->forward[0]->key;
        void *key2 = list2->header->forward[0]->key;
        // assume w.l.g that key1 <= key2 (i.e. if key1 > key2 exchange list1 and list2, key1 and key2)
        if (list1->compare(key1, key2) > 0) {
            skiplist* temp = list1;
            list1 = list2;
            list2 = temp;
            void *temp_key = key1;
            key1 = key2;
            key2 = temp_key;
            unflipped = !unflipped;
        }
        // merge step: remove from list1 elements with keys <= key2 and connect them on the output list
        // for all lvl s.t. list1->header->forward[lvl]->key <= key2, connect output list to list1
        int lvl = 0;
        while (lvl < list->level && list1->header->forward[lvl] != NULL && list1->compare(list1->header->forward[lvl]->key, key2) <= 0) {
            update[lvl]->forward[lvl] = list1->header->forward[lvl];
            lvl++;
        }
        lvl--;
        //for each level attached to output list, find endpoint at that level (i.e. last element with key <= key2)
        link x = list1->header->forward[lvl];
        for (int i = lvl ; i >= 0; i--) {
            while (x->forward[i] != NULL) {
                if(list1->compare(x->forward[i]->key, key2) > 0)
                    break;
                x = x->forward[i];
                //x->key <= key2 < x->forward[i]->key
            }
            update[i] = x;
            list1->header->forward[i] = x->forward[i];
        }
        // x = last element moved to output list
        // if the element at the front of list2 is a duplicate of an element already moved to output list, eliminate it
        if (list1->compare(x->key, key2) == 0) {
            if (unflipped) {
                list1->destroy_value(x->value);
                x->value = list2->header->forward[0]->value;
            }
            else {
                list2->destroy_value(list2->header->forward[0]->value);
            }
            link y = list2->header->forward[0];
            free(list2->header->value);
            for (int i = 0 ; i <= y->level ; i++)
                list2->header->forward[i] = y->forward[i];
            list1->destroy_key(y->key);
            free(y->forward);
            free(y);
        }
    }
    skiplist *leftOver = NULL;
    if (list2->header->forward[0] == NULL)
        leftOver = list1;
    else
        leftOver = list2;
    for (int i = 0; i < leftOver->level; i++)
        update[i]->forward[i] = leftOver->header->forward[i];
    for (int i = leftOver->level ; i <= list->level ; i++)
        update[i]->forward[i] = NULL;
    while (list->header->forward[list->level] == NULL && list->level > 0)
        list->level--;
    free(list1->header->forward);
    free(list1->header);
    free(list1);
    free(list2->header->forward);
    free(list2->header);
    free(list2);
    free(update);
    return list;
}


// Free the memory which is allocated by the skip list
void skiplist_destroy(skiplist *list) {
    link curr = list->header, next;
    while(curr != NULL) {
        next = curr->forward[0];
        if(list->destroy_key)
            list->destroy_key(curr->key);
        if(list->destroy_value)
            list->destroy_value(curr->value);
        free(curr->forward);
        free(curr);
        curr = next;
    }
    free(list);
}