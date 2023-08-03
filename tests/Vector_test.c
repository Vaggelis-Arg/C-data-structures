#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/Vector/vector.h"


DECLARE_VECTOR_ALL(int)


static int compare_int(const int *a, const int *b) {
    return (*a - *b);
}

static void test_vector_push_back_and_at() {
    vector_int *vector = vector_int_create(2);
    TEST_CHECK(vector != NULL);
    
    int value1 = 10;
    vector_int_push_back(vector, value1);
    TEST_CHECK(vector_int_at(vector, 0) == value1);
    TEST_CHECK(vector_int_size(vector) == 1);
    TEST_CHECK(vector_int_capacity(vector) == 2);
    
    int value2 = 20;
    vector_int_push_back(vector, value2);
    TEST_CHECK(vector_int_at(vector, 0) == value1);
    TEST_CHECK(vector_int_at(vector, 1) == value2);
    TEST_CHECK(vector_int_size(vector) == 2);
    TEST_CHECK(vector_int_capacity(vector) == 2);
    
    int value3 = 30;
    vector_int_push_back(vector, value3);
    TEST_CHECK(vector_int_at(vector, 0) == value1);
    TEST_CHECK(vector_int_at(vector, 1) == value2);
    TEST_CHECK(vector_int_at(vector, 2) == value3);
    TEST_CHECK(vector_int_size(vector) == 3);
    TEST_CHECK(vector_int_capacity(vector) == 4);
    
    vector_int_free(vector, NULL);
}

static void test_vector_set_at() {
    vector_int *vector = vector_int_create(3);
    TEST_CHECK(vector != NULL);
    
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    
    vector_int_push_back(vector, value1);
    vector_int_push_back(vector, value2);
    vector_int_push_back(vector, value3);
    
    TEST_CHECK(vector_int_at(vector, 0) == value1);
    TEST_CHECK(vector_int_at(vector, 1) == value2);
    TEST_CHECK(vector_int_at(vector, 2) == value3);
    
    int new_value = 100;
    vector_int_set_at(vector, 1, new_value);
    TEST_CHECK(vector_int_at(vector, 1) == new_value);
    
    vector_int_free(vector, NULL);
}

static void test_vector_clear_at() {
    vector_int *vector = vector_int_create(3);
    TEST_CHECK(vector != NULL);
    
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    
    vector_int_push_back(vector, value1);
    vector_int_push_back(vector, value2);
    vector_int_push_back(vector, value3);
    
    TEST_CHECK(vector_int_size(vector) == 3);
    
    vector_int_clear_at(vector, 1, NULL);
    
    TEST_CHECK(vector_int_at(vector, 0) == value1);
    TEST_CHECK(vector_int_at(vector, 1) == value3);
    TEST_CHECK(vector_int_size(vector) == 2);
    
    vector_int_free(vector, NULL);
}

static void test_vector_delete() {
    vector_int *vector = vector_int_create(3);
    TEST_CHECK(vector != NULL);
    
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    
    vector_int_push_back(vector, value1);
    vector_int_push_back(vector, value2);
    vector_int_push_back(vector, value3);
    
    TEST_CHECK(vector_int_size(vector) == 3);
    
    vector_int_delete(vector, value2, NULL);
    
    TEST_CHECK(vector_int_at(vector, 0) == value1);
    TEST_CHECK(vector_int_at(vector, 1) == value3);
    TEST_CHECK(vector_int_size(vector) == 2);
    
    vector_int_free(vector, NULL);
}

static void test_vector_search() {
    vector_int *vector = vector_int_create(3);
    TEST_CHECK(vector != NULL);
    
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    
    vector_int_push_back(vector, value1);
    vector_int_push_back(vector, value2);
    vector_int_push_back(vector, value3);
    
    TEST_CHECK(vector_int_search(vector, value1, compare_int) == 0);
    TEST_CHECK(vector_int_search(vector, value2, compare_int) == 1);
    TEST_CHECK(vector_int_search(vector, value3, compare_int) == 2);
    
    int value4 = 40;
    TEST_CHECK(vector_int_search(vector, value4, compare_int) == -1);
    
    vector_int_free(vector, NULL);
}

static void test_vector_sort() {
    vector_int *vector = vector_int_create(3);
    TEST_CHECK(vector != NULL);
    
    int value1 = 30;
    int value2 = 10;
    int value3 = 20;
    
    vector_int_push_back(vector, value1);
    vector_int_push_back(vector, value2);
    vector_int_push_back(vector, value3);
    
    TEST_CHECK(vector_int_at(vector, 0) == value1);
    TEST_CHECK(vector_int_at(vector, 1) == value2);
    TEST_CHECK(vector_int_at(vector, 2) == value3);
    
    vector_int_sort(vector, compare_int);
    
    TEST_CHECK(vector_int_at(vector, 0) == value2);
    TEST_CHECK(vector_int_at(vector, 1) == value3);
    TEST_CHECK(vector_int_at(vector, 2) == value1);
    
    vector_int_free(vector, NULL);
}


TEST_LIST = {
    {"test_vector_push_back_and_at", test_vector_push_back_and_at},
    {"test_vector_set_at", test_vector_set_at},
    {"test_vector_clear_at", test_vector_clear_at},
    {"test_vector_delete", test_vector_delete},
    {"test_vector_search", test_vector_search},
    {"test_vector_sort", test_vector_sort},
    {NULL, NULL}
};