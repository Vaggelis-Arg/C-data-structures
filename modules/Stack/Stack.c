/* File: Stack.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Stack.h"

typedef struct snode stack_node;

struct snode{
    void *data;
    stack_node *next;
};



struct stack{
    stack_node *top;
    unsigned int size;
    PrintFunc print;
    DestroyFunc destroy;
};


// Create a stack
Stack stack_create(PrintFunc print, DestroyFunc destroy) {
    Stack stack = malloc(sizeof(*stack));
    assert(stack != NULL);
    
    stack->top = NULL;
    stack->size = 0;

    stack->print = print;
    stack->destroy = destroy;
    
    return stack;
}


// Push the given item at the top of the stack
void stack_push(Stack stack, void *new_item) {
    if(stack == NULL) {
        fprintf(stderr, "Stack should be initialized first\n");
        return;
    }
    stack_node *new_node = malloc(sizeof(*new_node));
    assert(new_node != NULL);

    new_node->data = new_item;
    new_node->next = stack->top;
    stack->size++;
    stack->top = new_node;
}


// Pop the top item from the stack and return it. If the stack is empty, the function returns NULL
void *stack_pop(Stack stack) {
    if(stack == NULL || stack->size == 0) {
        fprintf(stderr, "Cannot pop an item from empty stack\n");
        return NULL;
    }
    void *item = stack->top->data;
    stack_node *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return item;
}


// Return size of stack
unsigned int stack_size(Stack stack) {
    if(stack == NULL)
        return 0;
    return stack->size;
}


// Return top item of stack
void *stack_top(Stack stack) {
    return stack->top->data;
}


//This function does not appear in the interface file. It is used to help us copy one stack to an other
static Stack stack_reverse_copy(Stack stack) {
    if(stack == NULL || stack->top == NULL)
        return NULL;
    Stack new_stack = stack_create(stack->print, stack->destroy);
    stack_node *temp = stack->top;
    while(temp != NULL) {
        void *cpy_data = malloc(sizeof(void *));
        memcpy(cpy_data, temp->data, sizeof(void *));
        stack_push(new_stack, cpy_data);
        temp = temp->next;
    }
    return new_stack;
}


// Create a new stack, copy the given stack to the one we created and return the new one
Stack stack_copy(const Stack stack) {
    Stack tempstack = stack_reverse_copy(stack);
    Stack new_stack =  stack_reverse_copy(tempstack);
    stack_destroy(tempstack);
    return new_stack;
}


// Print stack
void stack_print(Stack stack) {
    if(stack == NULL || stack->top == NULL)
        return;
    stack_node *top = stack->top;
    printf("Stack is: [");
    while (top != NULL) {
        stack->print(top->data);
        if(top->next != NULL)
            printf(", ");
        top = top->next;
    }
    printf("]\n");
}


// Return n-th item of stack (n is the second parameter). If stack size is less than n, the function returns NULL
void *stack_n_th_item(Stack stack, unsigned int n) {
    if(stack == NULL)
        return NULL;
    int i, count = stack_size(stack);
    if(n >= count)
        return NULL;
    stack_node *item= stack->top;
    for(i = 0 ; i < count ; i++) {
        if(i == count - n - 1)
            return item->data;
        item = item->next;
    }
    return NULL;
}


// Free the stack
void stack_destroy(Stack stack) {
    if(stack == NULL)
        return;
    stack_node *top = stack->top;
    while(top != NULL) {
        stack_node *temp = top;
        top = top->next;
        stack->destroy(temp->data);
        free(temp);
    }
    free(stack);
}