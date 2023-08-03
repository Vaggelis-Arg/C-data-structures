#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/Queue/Queue.h"

static void test_queue_empty() {
    Queue q = Queue_create(NULL, NULL);
    TEST_CHECK(Queue_empty(q));

    Queue_insert(q, (void *)&(int){5});
    TEST_CHECK(!Queue_empty(q));

    Queue_destroy(q);
}

static void test_queue_size() {
    Queue q = Queue_create(NULL, NULL);
    TEST_CHECK(Queue_size(q) == 0);

    Queue_insert(q, (void *)&(int){5});
    TEST_CHECK(Queue_size(q) == 1);

    Queue_insert(q, (void *)&(int){10});
    TEST_CHECK(Queue_size(q) == 2);

    Queue_remove(q);
    TEST_CHECK(Queue_size(q) == 1);

    Queue_destroy(q);
}

static void test_queue_insert_and_remove() {
    Queue q = Queue_create(NULL, NULL);

    Queue_insert(q, (void *)&(int){5});
    Queue_insert(q, (void *)&(int){10});
    Queue_insert(q, (void *)&(int){3});

    TEST_CHECK(Queue_size(q) == 3);

    int *val = Queue_remove(q);
    TEST_CHECK(*val == 5);
    TEST_CHECK(Queue_size(q) == 2);

    val = Queue_remove(q);
    TEST_CHECK(*val == 10);
    TEST_CHECK(Queue_size(q) == 1);

    val = Queue_remove(q);
    TEST_CHECK(*val == 3);
    TEST_CHECK(Queue_empty(q));

    Queue_destroy(q);
}


TEST_LIST = {
    {"test_queue_empty", test_queue_empty},
    {"test_queue_size", test_queue_size},
    {"test_queue_insert_and_remove", test_queue_insert_and_remove},
    {NULL, NULL}
};