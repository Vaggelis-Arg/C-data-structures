#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/SkipList/SkipList.h"

// Compare function for integer keys
static int compare_ints(void *a, void *b) {
    return *(int *)a - *(int *)b;
}


static void test_skiplist_insert_and_search() {
    skiplist *list = skiplist_initialize(compare_ints, NULL, free, free);

    // Insert key-value pairs
    int keys[] = {3, 1, 5, 2, 4};
    int values[] = {300, 100, 500, 200, 400};
    int num_elements = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_elements; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys[i];

        int *value = (int *)malloc(sizeof(int));
        *value = values[i];

        skiplist_insert(list, key, value);
    }

    // Search for inserted values
    for (int i = 0; i < num_elements; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys[i];

        int *value = (int *)skiplist_search(list, key);
        TEST_CHECK(value != NULL);
        TEST_CHECK(*value == values[i]);
        free(key);
    }

    // Search for non-existing key
    int non_existing_key = 10;
    int *value = (int *)skiplist_search(list, &non_existing_key);
    TEST_CHECK(value == NULL);

    skiplist_destroy(list);
}

static void test_skiplist_delete() {
    skiplist *list = skiplist_initialize(compare_ints, NULL, free, free);

    // Insert key-value pairs
    int keys[] = {3, 1, 5, 2, 4};
    int values[] = {300, 100, 500, 200, 400};
    int num_elements = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_elements; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys[i];

        int *value = (int *)malloc(sizeof(int));
        *value = values[i];

        skiplist_insert(list, key, value);
    }

    // Delete key-value pairs
    int keys_to_delete[] = {3, 1, 5};
    int num_keys_to_delete = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);

    for (int i = 0; i < num_keys_to_delete; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys_to_delete[i];

        int *value = (int *)skiplist_delete(list, key);
        TEST_CHECK(value != NULL);
        TEST_CHECK(*value == values[i]);

        free(key);
        free(value);
    }

    // Search for deleted keys
    for (int i = 0; i < num_keys_to_delete; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys_to_delete[i];

        int *value = (int *)skiplist_search(list, key);
        TEST_CHECK(value == NULL);
        free(key);
    }

    // Search for existing keys
    for (int i = 3 ; i <= 4 ; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys[i];

        int *value = (int *)skiplist_search(list, key);
        TEST_CHECK(value != NULL);
        TEST_CHECK(*value == values[i]);
        free(key);
    }

    skiplist_destroy(list);
}

static void test_skiplist_get_size() {
    skiplist *list = skiplist_initialize(compare_ints, NULL, free, free);

    TEST_CHECK(skiplist_get_size(list) == 0);

    int keys[] = {3, 1, 5, 2, 4};
    int values[] = {300, 100, 500, 200, 400};
    int num_elements = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_elements; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys[i];

        int *value = (int *)malloc(sizeof(int));
        *value = values[i];

        skiplist_insert(list, key, value);
        TEST_CHECK(skiplist_get_size(list) == i + 1);
    }

    skiplist_destroy(list);
}

static void test_skiplist_merge() {
    skiplist *list1 = skiplist_initialize(compare_ints, NULL, free, free);
    skiplist *list2 = skiplist_initialize(compare_ints, NULL, free, free);

    // List 1: 1 -> 2 -> 3 -> 4
    int keys1[] = {1, 2, 3, 4};
    int values1[] = {100, 200, 300, 400};
    int num_elements1 = sizeof(keys1) / sizeof(keys1[0]);

    // List 2: 3 -> 4 -> 5 -> 6
    int keys2[] = {3, 4, 5, 6};
    int values2[] = {300, 400, 500, 600};
    int num_elements2 = sizeof(keys2) / sizeof(keys2[0]);

    for (int i = 0; i < num_elements1; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys1[i];

        int *value = (int *)malloc(sizeof(int));
        *value = values1[i];

        skiplist_insert(list1, key, value);
    }

    for (int i = 0; i < num_elements2; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = keys2[i];

        int *value = (int *)malloc(sizeof(int));
        *value = values2[i];

        skiplist_insert(list2, key, value);
    }

    skiplist *merged_list = skiplist_merge(list1, list2);

    // The merged list should contain elements from both lists, with duplicates removed
    TEST_CHECK(skiplist_get_size(merged_list) == 6);

    int expected_keys[] = {1, 2, 3, 4, 5, 6};
    int expected_values[] = {100, 200, 300, 400, 500, 600};

    for (int i = 0; i < 6; i++) {
        int *key = (int *)malloc(sizeof(int));
        *key = expected_keys[i];

        int *value = (int *)skiplist_search(merged_list, key);
        TEST_CHECK(value != NULL);
        TEST_CHECK(*value == expected_values[i]);
        free(key);
    }

    skiplist_destroy(merged_list);
}

// Add more test cases for other functions if needed

TEST_LIST = {
    {"test_skiplist_insert_and_search", test_skiplist_insert_and_search},
    {"test_skiplist_delete", test_skiplist_delete},
    {"test_skiplist_get_size", test_skiplist_get_size},
    {"test_skiplist_merge", test_skiplist_merge},
    {NULL, NULL}
};