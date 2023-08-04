#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/DoubleLinkedList/DoubleLinkedList.h"


// Sample data structure for testing
typedef struct {
    int id;
    char name[50];
} TestData;

// Helper function to create test data
TestData *create_test_data(int id, const char *name) {
    TestData *data = malloc(sizeof(TestData));
    if (data) {
        data->id = id;
        strcpy(data->name, name);
    }
    return data;
}

// Helper function to destroy test data
void destroy_test_data(void *data) {
    free(data);
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

void test_double_linked_list_operations() {
    Listptr head = NULL;
    Listptr tail = NULL;
    DLL_Create(&head, &tail);

    // Check if the list is empty
    TEST_CHECK(DLL_IsEmpty(head) == true);

    // Insert some test data into the list
    TestData *data1 = create_test_data(1, "John");
    TestData *data2 = create_test_data(2, "Jane");
    TestData *data3 = create_test_data(3, "Bob");

    DLL_AddFirst(&head, &tail, data1);
    DLL_AddLast(&tail, &head, data2);
    DLL_AddAfter(&head, data3, &tail);

    // Check the size of the list
    TEST_CHECK(DLL_Size(head, tail) == 3);

    // Get the first and last elements of the list
    TestData *first_data = DLL_GetFirst(head);
    TestData *last_data = DLL_GetLast(tail);
    TEST_CHECK(first_data == data1);
    TEST_CHECK(last_data == data2);

    // Search for data in the list
    Listptr found_node = DLL_GetNode(head, data2, compare_test_data);
    TestData *found_data = found_node ? (TestData *)DLL_GetData(found_node) : NULL;
    TEST_CHECK(found_data == data2);

    // Remove data from the list
    DLL_Remove(&head, &tail, data1, compare_test_data, destroy_test_data);
    DLL_Remove(&head, &tail, data2, compare_test_data, destroy_test_data);

    // Check the size of the list after removal
    TEST_CHECK(DLL_Size(head, tail) == 1);

    // Clean up
    DLL_freelist(head, tail, destroy_test_data);
}

TEST_LIST = {
    {"test_double_linked_list_operations", test_double_linked_list_operations},
    {NULL, NULL} // marks the end of the test list
};