#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"


struct listnode{
    void *data;
    Listptr next;
    Listptr prev;
};

//Initialize list (and return the pointers of the head and the tail of it)
void DLL_Create(Listptr *head, Listptr *tail) {
   *head = *tail = NULL;
}


//returns size of the list
int DLL_Size(Listptr head, Listptr tail) {
    int count = 0;
    while((head != tail) && (head->prev != tail)) { /*Careful! The tail and the head can meet up either in the middle element (if the number of nodes is odd), so we should count it afterwards, or never meet up because when the one increases the other decreases*/
        count += 2;
        head = head->next;
        tail = tail->prev;
    }
    if((head == tail) && (head != NULL)) { /*We have not counted this single element*/
        count++;
    }
    return count;
}


//Check if list is empty and return 0 if not, otherwise return 1
bool DLL_IsEmpty(Listptr list) {
    return list == NULL;
}


//returns the item of the first node of the list
void *DLL_GetFirst(Listptr head) {
    if(DLL_IsEmpty(head)) {
        printf("List is empty. The is no element inside the list.\n");
        return 0;
    }
    return head->data;
}


//returns the item of the last node of the list
void *DLL_GetLast(Listptr tail) {
    if(DLL_IsEmpty(tail)) {
        printf("List is empty. The is no element inside the list.\n");
        return 0;
    }
    return tail->data;
}


//returns a pointer to the first node of the list which contains the item "i"
Listptr DLL_GetNode(Listptr head, void *i, CompareFunc compare) {
    while(head != NULL) { /*Cross the list from the beginning*/
        if(compare(head->data, i) == 0)
            return head; /*Found the first element with data i :) , return it*/
        head = head->next;
    }
    return NULL; /*Did not found it :(*/
}


//returns the data of the given node
void *DLL_GetData(Listptr node) {
    return node->data;
}



//returns the item of the previous node from the given node 
void *DLL_GetPrev(Listptr node) {
    if(node->prev == NULL) {
        printf("No previous element of the given node.\n");
        return 0;
    }
    return (node->prev)->data;
}


//returns the item of the next node from the given node
void *DLL_GetNext(Listptr node) {
    if(node->next == NULL) {
        printf("No next element of the given node.\n");
        return 0;
    }
    return (node->next)->data;
}


//add a node with data i before the given node
void DLL_AddBefore(Listptr *node, void *i, Listptr *head) {
    if(*node == NULL) { /*The given node is not appropriate*/
        fprintf(stderr, "Fail to add the node");
        return;
    }
    Listptr new_node = malloc(sizeof(struct listnode));
    if(new_node == NULL) { /*The given node is not appropriate*/
        fprintf(stderr, "Error while allocating memory\n");
        return;
    }
    new_node->data = i;
    new_node->next = *node; 
    new_node->prev = (*node)->prev;
    if((*node)->prev != NULL) { /*Only if node is not the head of the list, we will deal with the previous node's next pointer*/
        (((*node)->prev)->next) = new_node; /*Linking the new node with its previous node*/
    }
    (*node)->prev = new_node; /*Linking the current node with the new node*/
    if(*node == *head) { /*Adding before current head. The head must still point to the first element of the list so it changes*/
        *head = new_node;
    }
}


//add a node with data i after the given node
void DLL_AddAfter(Listptr *node, void *i, Listptr *tail) {
    if(*node == NULL) { /*The given node is not appropriate*/
        fprintf(stderr, "Fail to add the node. The given node does not exists.\n");
        return;
    }
    Listptr new_node = malloc(sizeof(struct listnode));
    if(new_node == NULL) { /*The given node is not appropriate*/
        fprintf(stderr, "Error while allocating memory\n");
        return;
    }
    new_node->data = i;
    new_node->prev = *node; /*Link the new node with the current node*/
    new_node->next = (*node)->next;
    if((*node)->next != NULL) { /*Only if node is not the tail of the list, we will deal with the previous node's next pointer*/
        (((*node)->next)->prev = new_node);
    }
    (*node)->next = new_node;
    if(*node == *tail) { /*If an element is added before the current tail, the tail of the list should change*/
        *tail = new_node;
    }
}


//add a node with data-item "i" at the beginning of the list
void DLL_AddFirst(Listptr *head, Listptr *tail, void *i) {
    Listptr templist = *head; /*Save the head of the list*/
    *head = malloc(sizeof(struct listnode));
    if(*head == NULL) { /*The given node is not appropriate*/
        fprintf(stderr, "Error while allocating memory\n");
        return;
    }
    (*head)->data = i;
    (*head)->prev = NULL; 
    (*head)->next = templist; /*Link the new head with the other nodes of the list*/
    if(templist != NULL) {
        templist->prev = *head;
    }
    else {
        *tail = *head;
    }
}


//add a node with data-item "i" at the end of the list
void DLL_AddLast(Listptr *tail, Listptr *head, void *i) {
    Listptr templist = *tail;
    *tail = malloc(sizeof(struct listnode));
    if(*tail == NULL) {
        fprintf(stderr, "Error while allocating memory\n");
        return;
    }
    (*tail)->data = i;
    (*tail)->next = NULL;
    (*tail)->prev = templist; /*Link the new tail with all the other elements of the list*/
    if(templist != NULL) {
        templist->next = *tail;
    }
    else {
        *head = *tail;
    }
}

//delete given node from the double linked list
static inline void DLL_delete_node(Listptr node, DestroyFunc destroy) {
    if (node->prev) {
        node->prev->next = node->next; /* update the previous node's next pointer */
    }
    if (node->next) {
        node->next->prev = node->prev; /* update the next node's previous pointer */
    }
    if (destroy) {
        destroy(node->data);
    }
    free(node); /* free the memory allocated for the node */
}


//removes all the nodes with data "i" from the list
void DLL_Remove(Listptr *head, Listptr *tail, void *i, CompareFunc compare, DestroyFunc destroy) {
    Listptr tempnode;
    bool onlyonenode = true;
    while((*head != *tail) && (*head != NULL) && ((*head)->prev != *tail)) {
        onlyonenode = false;
        if((*head)->data == i) {
            if((*head)->prev == NULL) {
                tempnode = *head;
                *head = (*head)->next;
                tempnode->next->prev = NULL; /*update the next node's previous pointer*/
                if(destroy)
                    destroy(tempnode->data);
                free(tempnode); /*free the memory allocated for the node*/
            }
            else {
                tempnode = *head;
                head = &((*head)->next);
                DLL_delete_node(tempnode, destroy);
            }
        }
        else {
            head = &((*head)->next);
        }
        if((*tail)->data == i) {
            if((*tail)->next == NULL) {
                tempnode = *tail;
                *tail = (*tail)->prev;
                tempnode->prev->next = NULL; /*update the previous node's next pointer*/
                if(destroy)
                    destroy(tempnode->data);
                free(tempnode); /*free the memory allocated for the node*/
            }
            else {
                tempnode = *tail;
                tail = &((*tail)->prev);
                DLL_delete_node(tempnode, destroy);
            }
        }
        else {
            tail = &((*tail)->prev);
        }
    }
    if(*head == *tail) {
        if((*head)->data == i) {
            if(onlyonenode) {
                if(destroy)
                    destroy((*head)->data);
                free(*head);
                *head = *tail = NULL;
            }
            else {
                tempnode = *head;
                head = &((*head)->next);
                DLL_delete_node(tempnode, destroy);
            }
        }
    }
}


//print the items of the list from the first one to the last one
void DLL_print(Listptr head, PrintFunc print) {
    if(DLL_IsEmpty(head)) {
        printf("List is empty\n");
        return;
    }
    printf("[");
    while(head != NULL) {
        print(head->data);
        head = head->next;
        if (head != NULL) 
            printf(", ");
    }
    printf("]\n");
}


//free the double linked list
void DLL_freelist(Listptr head, Listptr tail, DestroyFunc destroy) {
    while((head != tail) && (head->prev != tail)) {
        Listptr temp = head;
        head = head->next;
        if(destroy)
            destroy(temp->data);
        free(temp);
        temp = tail;
        tail = tail->prev;
        if(destroy)
            destroy(temp->data);
        free(temp);
    }
}