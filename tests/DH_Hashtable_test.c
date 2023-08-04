#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "acutest/acutest.h"
#include "../modules/DoubleHashingHashTable/DoubleHashingHashTable.h"

// Define some sample data types for testing purposes
typedef struct {
    int id;
    char name[50];
} TestData;


long unsigned int SDBM_hash(void *k) {
    char *key = (char *)k;
    unsigned int hash = 0;
    int c;

    while ((c = *key++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

long unsigned int h1(void *k) {
    char *key = (char *)k;
    unsigned int hash = 0;
    int c;

    while ((c = *key++))
        hash += c;

    return hash;
}

// Helper function to create test data
TestData *create_test_data(int id, const char *name) {
    TestData *data = malloc(sizeof(TestData));
    if (data) {
        data->id = id;
        strcpy(data->name, name);
    }
    return data;
}

// Helper function to print test data
void print_test_data(void *data) {
    TestData *tdata = (TestData *)data;
    printf("ID: %d, Name: %s\n", tdata->id, tdata->name);
}

// Helper function to compare test data based on their IDs
int compare_test_data(void *data1, void *data2) {
    TestData *tdata1 = (TestData *)data1;
    TestData *tdata2 = (TestData *)data2;

    if (tdata1->id < tdata2->id) return -1;
    if (tdata1->id > tdata2->id) return 1;
    return 0;
}

void test_hash_table_operations() {
    DHHashtable *table = DHhashtable_create(compare_test_data, NULL, NULL, print_test_data, SDBM_hash, h1);
    TEST_CHECK(table != NULL);

    // Check the size of the hash table (it should be empty)
    TEST_CHECK(DHhashtable_size(table) == 0);

    // Insert some test data into the hash table
    TestData *data1 = create_test_data(1, "John");
    TestData *data2 = create_test_data(2, "Jane");
    TestData *data3 = create_test_data(3, "Bob");

    DHhashtable_insert(table, &data1->id, data1);
    DHhashtable_insert(table, &data2->id, data2);
    DHhashtable_insert(table, &data3->id, data3);

    // Check the size of the hash table after insertion
    TEST_CHECK(DHhashtable_size(table) == 3);

    // Search for data in the hash table
    TestData *found_data1 = DHhashtable_search(table, &data1->id);
    TestData *found_data2 = DHhashtable_search(table, &data2->id);
    TestData *found_data3 = DHhashtable_search(table, &data3->id);

    TEST_CHECK(found_data1 == data1);
    TEST_CHECK(found_data2 == data2);
    TEST_CHECK(found_data3 == data3);

    // Remove data from the hash table
    TEST_CHECK(DHhashtable_remove(table, &data1->id) == true);
    TEST_CHECK(DHhashtable_remove(table, &data2->id) == true);
    TEST_CHECK(DHhashtable_remove(table, &data3->id) == true);

    // Check the size of the hash table after removal
    TEST_CHECK(DHhashtable_size(table) == 0);

    // Clean up
    free(data1);
    free(data2);
    free(data3);
    DHhashtable_destroy(table);
}

void test_hash_table_collision() {
    // This test checks for hash table collision handling
    DHHashtable *table = DHhashtable_create(compare_test_data, NULL, NULL, NULL, SDBM_hash, h1);
    TEST_CHECK(table != NULL);

    // Insert two data items with the same hash value (should handle collision)
    TestData *data1 = create_test_data(1, "John");
    TestData *data2 = create_test_data(1, "Jane"); // same ID as data1

    DHhashtable_insert(table, &data1->id, data1);
    DHhashtable_insert(table, &data2->id, data2);

    // Check the size of the hash table (it should be 1 due to collision handling)
    TEST_CHECK(DHhashtable_size(table) == 1);

    // Search for data in the hash table (should return data2 as it overwrote data1)
    TestData *found_data = DHhashtable_search(table, &data1->id);
    TEST_CHECK(found_data == data2);

    // Clean up
    free(data1);
    free(data2);
    DHhashtable_destroy(table);
}

TEST_LIST = {
    {"test_hash_table_operations", test_hash_table_operations},
    {"test_hash_table_collision", test_hash_table_collision},
    {NULL, NULL} // marks the end of the test list
};