#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/PriorityQueue/PriorityQueue.h"

static int compare_ints(void *a, void *b) {
    return (*(int *)a) - (*(int *)b);
}

static void test_priority_queue_empty() {
    PriorityQueue pq = PQ_initialize(10, compare_ints, NULL, NULL);
    TEST_CHECK(PQ_empty(pq));

    PQ_insert(pq, (void *)&(int){5});
    TEST_CHECK(!PQ_empty(pq));

    PQ_destroy(pq);
}

static void test_priority_queue_size() {
    PriorityQueue pq = PQ_initialize(10, compare_ints, NULL, NULL);
    TEST_CHECK(PQ_size(pq) == 0);

    PQ_insert(pq, (void *)&(int){5});
    TEST_CHECK(PQ_size(pq) == 1);

    PQ_insert(pq, (void *)&(int){10});
    TEST_CHECK(PQ_size(pq) == 2);

    PQ_remove(pq);
    TEST_CHECK(PQ_size(pq) == 1);

    PQ_destroy(pq);
}

static void test_priority_queue_insert_and_remove() {
    PriorityQueue pq = PQ_initialize(10, compare_ints, NULL, NULL);

    PQ_insert(pq, (void *)&(int){5});
    PQ_insert(pq, (void *)&(int){10});
    PQ_insert(pq, (void *)&(int){3});

    TEST_CHECK(PQ_size(pq) == 3);

    int *val = PQ_remove(pq);
    TEST_CHECK(*val == 10);
    TEST_CHECK(PQ_size(pq) == 2);

    val = PQ_remove(pq);
    TEST_CHECK(*val == 5);
    TEST_CHECK(PQ_size(pq) == 1);

    val = PQ_remove(pq);
    TEST_CHECK(*val == 3);
    TEST_CHECK(PQ_empty(pq));

    PQ_destroy(pq);
}

TEST_LIST = {
    {"test_priority_queue_empty", test_priority_queue_empty},
    {"test_priority_queue_size", test_priority_queue_size},
    {"test_priority_queue_insert_and_remove", test_priority_queue_insert_and_remove},
    {NULL, NULL}
};
