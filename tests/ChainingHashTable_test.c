#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acutest/acutest.h"
#include "../modules/SeparateChainingHashTable/ChainingHashTable.h"


// Hash functions
long unsigned int DJB2_hash(void *k) {
    char *key = (char *)k;
    unsigned int hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

long unsigned int SDBM_hash(void *k) {
    char *key = (char *)k;
    unsigned int hash = 0;
    int c;

    while ((c = *key++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

static int compare_strings(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

// static void *copy_int(void *data) {
//     int *new_data = (int *)malloc(sizeof(int));
//     if (new_data) {
//         *new_data = *(int *)data;
//     }
//     return new_data;
// }

static void mock_print(void *data) {
    // Implement a mock print function to capture the printed output
    // In this example, we won't check the output, only if the function was called.
}

static void test_separate_chaining_hash_table_insert_and_search() {
    SCHashtable *hash_table = SChashtable_create(compare_strings, mock_print, free, NULL, DJB2_hash);

    char *keys[] = {"key1", "key2", "key3", "key4", "key5"};
    int values[] = {100, 200, 300, 400, 500};
    int num_elements = sizeof(keys) / sizeof(keys[0]);

    // Insert key-value pairs
    for (int i = 0; i < num_elements; i++) {
        char *key_copy = (char *)malloc(strlen(keys[i]) + 1);
        strcpy(key_copy, keys[i]);
        SChashtable_insert(hash_table, key_copy, &values[i]);
    }

    // Search for inserted key-value pairs
    for (int i = 0; i < num_elements; i++) {
        void *value = SChashtable_search(hash_table, keys[i]);
        TEST_CHECK(*(int *)value == values[i]);
    }

    // Search for non-existing key
    char *non_existing_key = "key6";
    void *value = SChashtable_search(hash_table, non_existing_key);
    TEST_CHECK(value == NULL);

    SChashtable_destroy(hash_table);
}


static void test_separate_chaining_hash_table_remove() {
    SCHashtable *hash_table = SChashtable_create(compare_strings, mock_print, free, NULL, SDBM_hash);

    char *keys[] = {"key1", "key2", "key3", "key4", "key5"};
    int values[] = {100, 200, 300, 400, 500};
    int num_elements = sizeof(keys) / sizeof(keys[0]);

    // Insert key-value pairs
    for (int i = 0; i < num_elements; i++) {
        char *key_copy = (char *)malloc(strlen(keys[i]) + 1);
        strcpy(key_copy, keys[i]);
        SChashtable_insert(hash_table, key_copy, &values[i]);
    }

    // Remove key-value pairs
    SChashtable_remove(hash_table, "key1");
    SChashtable_remove(hash_table, "key3");
    SChashtable_remove(hash_table, "key5");

    // Search for removed key-value pairs
    void *value = SChashtable_search(hash_table, "key1");
    TEST_CHECK(value == NULL);

    value = SChashtable_search(hash_table, "key3");
    TEST_CHECK(value == NULL);

    value = SChashtable_search(hash_table, "key5");
    TEST_CHECK(value == NULL);

    // Search for existing key-value pairs
    value = SChashtable_search(hash_table, "key2");
    TEST_CHECK(*(int *)value == 200);

    value = SChashtable_search(hash_table, "key4");
    TEST_CHECK(*(int *)value == 400);

    SChashtable_destroy(hash_table);
}


TEST_LIST = {
    {"test_separate_chaining_hash_table_insert_and_search", test_separate_chaining_hash_table_insert_and_search},
    {"test_separate_chaining_hash_table_remove", test_separate_chaining_hash_table_remove},
    {NULL, NULL}
};
