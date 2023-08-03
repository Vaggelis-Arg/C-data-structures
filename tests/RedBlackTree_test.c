#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/RedBlackTree/RedBlackTree.h"

static int compare_ints(void *a, void *b) {
    return (*(int *)a) - (*(int *)b);
}

static void test_red_black_tree_empty() {
    RBTree root = NULL;
    TEST_CHECK(RBT_empty(root));

    RBT_insert(&root, (void *)&(int){5}, compare_ints);
    TEST_CHECK(!RBT_empty(root));

    RBT_destroy(root, NULL);
}

static void test_red_black_tree_insert_and_search() {
    RBTree root = NULL;
    int values[] = {5, 10, 3, 15, 7};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        RBT_insert(&root, (void *)&values[i], compare_ints);
    }

    TEST_CHECK(RBT_search(root, (void *)&values[0], compare_ints));
    TEST_CHECK(RBT_search(root, (void *)&values[1], compare_ints));
    TEST_CHECK(RBT_search(root, (void *)&values[2], compare_ints));
    TEST_CHECK(RBT_search(root, (void *)&values[3], compare_ints));
    TEST_CHECK(RBT_search(root, (void *)&values[4], compare_ints));

    int non_existing_value = 20;
    TEST_CHECK(!RBT_search(root, (void *)&non_existing_value, compare_ints));

    RBT_destroy(root, NULL);
}

static void test_red_black_tree_delete() {
    RBTree root = NULL;
    int values[] = {5, 10, 3, 15, 7};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        RBT_insert(&root, (void *)&values[i], compare_ints);
    }

    int value_to_delete = 3;
    TEST_CHECK(RBT_delete(&root, (void *)&value_to_delete, compare_ints, NULL));

    TEST_CHECK(RBT_search(root, (void *)&values[0], compare_ints));
    TEST_CHECK(RBT_search(root, (void *)&values[1], compare_ints));
    TEST_CHECK(!RBT_search(root, (void *)&values[2], compare_ints));
    TEST_CHECK(RBT_search(root, (void *)&values[3], compare_ints));
    TEST_CHECK(RBT_search(root, (void *)&values[4], compare_ints));

    RBT_destroy(root, NULL);
}


static void test_red_black_tree_select_k_th_item() {
    RBTree root = NULL;
    int values[] = {5, 10, 3, 15, 7};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        RBT_insert(&root, (void *)&values[i], compare_ints);
    }

    int *selected_value = (int *)RBT_select_k_th_item(root, 1);
    TEST_CHECK(*selected_value == 3);
    selected_value = (int *)RBT_select_k_th_item(root, 2);
    TEST_CHECK(*selected_value == 5);
    selected_value = (int *)RBT_select_k_th_item(root, 3);
    TEST_CHECK(*selected_value == 7);
    selected_value = (int *)RBT_select_k_th_item(root, 4);
    TEST_CHECK(*selected_value == 10);
    selected_value = (int *)RBT_select_k_th_item(root, 5);
    TEST_CHECK(*selected_value == 15);

    RBT_destroy(root, NULL);
}


static void test_red_black_tree_count_items() {
    RBTree root = NULL;
    int values[] = {5, 10, 3, 15, 7};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        RBT_insert(&root, (void *)&values[i], compare_ints);
    }

    TEST_CHECK(RBT_count_items(root) == size);

    RBT_destroy(root, NULL);
}

static void test_red_black_tree_min_and_max_values() {
    RBTree root = NULL;
    int values[] = {5, 10, 3, 15, 7};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        RBT_insert(&root, (void *)&values[i], compare_ints);
    }

    int *min_value = (int *)RBT_min_value(root);
    int *max_value = (int *)RBT_max_value(root);

    TEST_CHECK(*min_value == 3);
    TEST_CHECK(*max_value == 15);

    RBT_destroy(root, NULL);
}


TEST_LIST = {
    {"test_red_black_tree_empty", test_red_black_tree_empty},
    {"test_red_black_tree_insert_and_search", test_red_black_tree_insert_and_search},
    {"test_red_black_tree_delete", test_red_black_tree_delete},
    {"test_red_black_tree_select_k_th_item", test_red_black_tree_select_k_th_item},
    {"test_red_black_tree_count_items", test_red_black_tree_count_items},
    {"test_red_black_tree_min_and_max_values", test_red_black_tree_min_and_max_values},
    {NULL, NULL}
};