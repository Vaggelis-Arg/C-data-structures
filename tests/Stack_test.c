#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/Stack/Stack.h"


static void test_stack_push_and_pop() {
    Stack stack = stack_create(NULL, free);

    TEST_CHECK(stack_size(stack) == 0);

    int values[] = {1, 2, 3, 4, 5};
    int num_elements = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_elements; i++) {
        int *value = (int *)malloc(sizeof(int));
        *value = values[i];
        stack_push(stack, value);
        TEST_CHECK(stack_size(stack) == i + 1);
    }

    TEST_CHECK(stack_size(stack) == num_elements);

    for (int i = num_elements - 1; i >= 0; i--) {
        int *value = (int *)stack_pop(stack);
        TEST_CHECK(value != NULL);
        TEST_CHECK(*value == values[i]);
        free(value);
        TEST_CHECK(stack_size(stack) == i);
    }

    TEST_CHECK(stack_size(stack) == 0);

    // Pop from an empty stack, should return NULL
    void *value = stack_pop(stack);
    TEST_CHECK(value == NULL);

    stack_destroy(stack);
}


static void test_stack_top() {
    Stack stack = stack_create(NULL, free);

    TEST_CHECK(stack_top(stack) == NULL);

    int values[] = {1, 2, 3, 4, 5};
    int num_elements = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_elements; i++) {
        int *value = (int *)malloc(sizeof(int));
        *value = values[i];
        stack_push(stack, value);
        void *top = stack_top(stack);
        TEST_CHECK(*(int *)top == *value);
    }

    stack_destroy(stack);
}


static void test_stack_n_th_item() {
    Stack stack = stack_create(NULL, free);

    TEST_CHECK(stack_n_th_item(stack, 1) == NULL);

    int values[] = {1, 2, 3, 4, 5};
    int num_elements = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_elements; i++) {
        int *value = (int *)malloc(sizeof(int));
        *value = values[i];
        stack_push(stack, value);
    }

    for (int i = 0; i < num_elements; i++) {
        void *value = stack_n_th_item(stack, i);
        TEST_CHECK(value != NULL);
        TEST_CHECK(*(int *)value == values[i]);
    }

    // Get item beyond the stack size, should return NULL
    void *value = stack_n_th_item(stack, num_elements + 1);
    TEST_CHECK(value == NULL);

    stack_destroy(stack);
}


static void test_stack_size() {
    Stack stack = stack_create(NULL, free);

    TEST_CHECK(stack_size(stack) == 0);

    int values[] = {1, 2, 3, 4, 5};
    int num_elements = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_elements; i++) {
        int *value = (int *)malloc(sizeof(int));
        *value = values[i];
        stack_push(stack, value);
        TEST_CHECK(stack_size(stack) == i + 1);
    }

    TEST_CHECK(stack_size(stack) == num_elements);

    for (int i = num_elements - 1; i >= 0; i--) {
        void *value = stack_pop(stack);
        TEST_CHECK(stack_size(stack) == i);
        free(value);
    }

    TEST_CHECK(stack_size(stack) == 0);

    stack_destroy(stack);
}

static void test_stack_copy() {
    Stack stack1 = stack_create(NULL, free);

    int values[] = {1, 2, 3, 4, 5};
    int num_elements = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_elements; i++) {
        int *value = (int *)malloc(sizeof(int));
        *value = values[i];
        stack_push(stack1, value);
    }

    Stack stack2 = stack_copy(stack1);

    TEST_CHECK(stack_size(stack1) == stack_size(stack2));

    while (stack_size(stack1) != 0) {
        int *value1 = (int *)stack_pop(stack1);
        int *value2 = (int *)stack_pop(stack2);
        TEST_CHECK(*value1 == *value2);
        free(value1);
        free(value2);
    }

    stack_destroy(stack1);
    stack_destroy(stack2);
}


TEST_LIST = {
    {"test_stack_push_and_pop", test_stack_push_and_pop},
    {"test_stack_top", test_stack_top},
    {"test_stack_n_th_item", test_stack_n_th_item},
    {"test_stack_size", test_stack_size},
    {"test_stack_copy", test_stack_copy},
    {NULL, NULL}
};