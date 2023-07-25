/* File: Stack.h*/
#ifndef STACK_H
#define STACK_H

typedef struct stack *Stack;

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *); 

// Create a stack
Stack stack_create(PrintFunc, DestroyFunc);

// Push the given item at the top of the stack
void stack_push(Stack, void *);

// Pop the top item from the stack and return it. If the stack is empty, the function returns NULL
void *stack_pop(Stack);

// Print stack
void stack_print(Stack);

// Return size of stack
unsigned int stack_size(Stack);

// Return top item of stack
void *stack_top(Stack);

// Return n-th item of stack (n is the second parameter). If stack size is less than n, the function returns NULL
void *stack_n_th_item(Stack, unsigned int);

// Free the stack
void stack_destroy(Stack);

// Create a new stack, copy the given stack to the one we created and return the new one
Stack stack_copy(const Stack);

#endif