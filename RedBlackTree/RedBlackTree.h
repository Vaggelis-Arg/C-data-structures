/* File: RedBlackTree.h */
#ifndef RED_BLACK_TREES_H
#define RED_BLACK_TREES_H

#include <stdbool.h>


typedef struct RBTNode *RBTree;

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);

/* The red black tree should be initialized to NULL before starting to insert data */

// Insert the node into the red black tree
void RBT_insert(RBTree *root, void *data, CompareFunc compare);

// Remove node with given data from the red black tree
bool RBT_delete(RBTree *root, void *data, CompareFunc compare, DestroyFunc destroy);

// Search given data in the red black tree and return the data if it finds it, else return NULL
bool RBT_search(RBTree root, void *data, CompareFunc compare);

// Returns the data of the k-th item of in the red black tree
void *RBT_select_k_th_item(RBTree root, size_t k);

// Check if the red black tree is empty
bool RBT_empty(RBTree root);

// Inorder traversal and print of items in the red black tree
void RBT_inorder_traversal(RBTree root, PrintFunc print);

// Preorder traversal and print of items in the red black tree
void RBT_preorder_traversal(RBTree root, PrintFunc print);

// Postorder traversal and print of items in the red black tree
void RBT_postorder_traversal(RBTree root, PrintFunc print);

// Returns the number of items in the red black tree
size_t RBT_count_items(RBTree root);

// Find the minimum value of a red black tree
void *min_value(RBTree root);

// Find the maximum value of a red black tree
void *max_value(RBTree root);

// Function which is used to destroy a red black tree
void RBT_destroy(RBTree node, DestroyFunc destroy);

#endif