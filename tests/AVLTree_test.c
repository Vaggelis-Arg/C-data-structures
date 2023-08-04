#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/AVLTree/AVLTree.h"

/* Helper function to create a sample integer value */
int *create_int(int value) {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = value;
    return ptr;
}


/* Helper function to compare integers */
int compare_ints(void *a, void *b) {
    return *(int *)a - *(int *)b;
}

void test_avl_tree_insert_and_search() {
    AVLTree avl = NULL;

    // Insert and search for elements in the AVL tree
    avl = AVLTree_insert(avl, create_int(5), compare_ints);
    AVLTree_insert(avl, create_int(3), compare_ints);
    AVLTree_insert(avl, create_int(7), compare_ints);

    int *search_item = create_int(5);
    TEST_CHECK(AVLTree_search(avl, search_item, compare_ints));
    free(search_item);
    search_item = create_int(3);
    TEST_CHECK(AVLTree_search(avl, search_item, compare_ints));
    free(search_item);
    search_item = create_int(7);
    TEST_CHECK(AVLTree_search(avl, search_item, compare_ints));
    free(search_item);
    search_item = create_int(2);
    TEST_CHECK(!AVLTree_search(avl, search_item, compare_ints));
    free(search_item);

    // Clean up
    AVLTree_destroy(avl, free);
}

void test_avl_tree_delete() {
    AVLTree avl = NULL;

    // Insert and delete elements from the AVL tree
    int *insert_item = create_int(5);
    avl = AVLTree_insert(avl, insert_item, compare_ints);
    TEST_CHECK(AVLTree_search(avl, insert_item, compare_ints));
    insert_item = create_int(3);
    avl = AVLTree_insert(avl, insert_item, compare_ints);
    TEST_CHECK(AVLTree_search(avl, insert_item, compare_ints));
    insert_item = create_int(7);
    avl = AVLTree_insert(avl, insert_item, compare_ints);
    TEST_CHECK(AVLTree_search(avl, insert_item, compare_ints));

    int *delete_item = create_int(5);
    avl = AVLTree_delete(avl, delete_item, compare_ints, free);
    TEST_CHECK(!AVLTree_search(avl, delete_item, compare_ints));
    free(delete_item);
    delete_item = create_int(3);
    avl = AVLTree_delete(avl, delete_item, compare_ints, free);
    TEST_CHECK(!AVLTree_search(avl, delete_item, compare_ints));
    free(delete_item);
    delete_item = create_int(7);
    avl = AVLTree_delete(avl, delete_item, compare_ints, free);
    TEST_CHECK(!AVLTree_search(avl, delete_item, compare_ints));
    free(delete_item);
    
    TEST_CHECK(AVLTree_empty(avl));

    // Clean up
    AVLTree_destroy(avl, free);
}

void test_avl_tree_select_k_th_item() {
    AVLTree avl = NULL;

    // Insert elements into the AVL tree
    avl = AVLTree_insert(avl, create_int(5), compare_ints);
    avl = AVLTree_insert(avl, create_int(3), compare_ints);
    avl = AVLTree_insert(avl, create_int(7), compare_ints);

    // Test selecting k-th item
    TEST_CHECK(*(int *)AVLTree_select_k_th_item(avl, 1) == 3);
    TEST_CHECK(*(int *)AVLTree_select_k_th_item(avl, 2) == 5);
    TEST_CHECK(*(int *)AVLTree_select_k_th_item(avl, 3) == 7);

    // Clean up
    AVLTree_destroy(avl, free);
}

void test_avl_tree_count_items() {
    AVLTree avl = NULL;

    // Insert and delete elements from the AVL tree
    avl = AVLTree_insert(avl, create_int(5), compare_ints);
    avl = AVLTree_insert(avl, create_int(3), compare_ints);
    avl = AVLTree_insert(avl, create_int(7), compare_ints);

    // Test counting items in the AVL tree
    TEST_CHECK(AVL_count_items(avl) == 3); // Corrected the macro to TEST_CHECK

    // Clean up
    AVLTree_destroy(avl, free);
}

void test_avl_tree_min_max_values() {
    AVLTree avl = NULL;

    // Insert elements into the AVL tree
    avl = AVLTree_insert(avl, create_int(5), compare_ints);
    avl = AVLTree_insert(avl, create_int(3), compare_ints);
    avl = AVLTree_insert(avl, create_int(7), compare_ints);

    // Test finding min and max values
    TEST_CHECK(*(int *)AVLTree_min_value(avl) == 3);
    TEST_CHECK(*(int *)AVLTree_max_value(avl) == 7);

    // Clean up
    AVLTree_destroy(avl, free);
}

TEST_LIST = {
    {"test_avl_tree_insert_and_search", test_avl_tree_insert_and_search},
    {"test_avl_tree_delete", test_avl_tree_delete},
    {"test_avl_tree_select_k_th_item", test_avl_tree_select_k_th_item},
    {"test_avl_tree_count_items", test_avl_tree_count_items},
    {"test_avl_tree_min_max_values", test_avl_tree_min_max_values},
    {NULL, NULL} // Terminate the test list
};
