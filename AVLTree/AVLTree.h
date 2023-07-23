/* File: AVLTree.h */
#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdbool.h>

typedef struct avl_node *AVLTree;

// Compare functions for the different data type
typedef int (*CompareFunc)(void *, void *);

//Functions to destroy values inserted in the hash table
typedef void (*DestroyFunc)(void *);

// Functions to visit nodes printing their data
typedef void (*PrintFunc)(void *);

/* The AVL tree should be initialized to NULL before starting to insert data */

// Function to insert a node in an AVL tree
AVLTree AVLTree_insert(AVLTree node, void *data, CompareFunc compare);

// Remove given item (if it exists) from the AVL tree and return a boolean value which demonstrates if the deletion occurred
AVLTree AVLTree_delete(AVLTree avl, void *data, CompareFunc compare, DestroyFunc destroy);

// Search given data in the AVL tree and returns a corresponding boolean value if it finds it or not
bool AVLTree_search(AVLTree avl, void *data, CompareFunc compare);

// Inorder traversal and print of items in the AVL tree
void AVLTree_inorder_traversal(AVLTree avl, PrintFunc print);

// Preorder traversal and print of items in the AVL tree
void AVLTree_preorder_traversal(AVLTree avl, PrintFunc print);

// Postorder traversal and print of items in the AVL tree
void AVLTree_postorder_traversal(AVLTree avl, PrintFunc print);

// Returns the data of the k-th item of in the AVL tree
void *AVLTree_select_k_th_item(AVLTree avl, int k);

// Check if the AVL tree is empty
bool AVLTree_empty(AVLTree avl);

// Returns the number of items in the AVL tree
int AVL_count_items(AVLTree avl);

// Find the minimum value of an AVL tree
void *AVLTree_min_value(AVLTree avl);

// Find the maximum value of an AVL tree
void *AVLTree_max_value(AVLTree avl);

// Function to destroy an AVL tree
void AVLTree_destroy(AVLTree node, DestroyFunc destroy);

#endif