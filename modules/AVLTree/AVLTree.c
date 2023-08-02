/* File: AVLTree.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "AVLTree.h"
#define MAX(A, B) ((A) > (B)) ? (A) : (B)

struct avl_node {
    void *data;
    AVLTree left;
    AVLTree right;
    int height;
};


// Static - Local functions
static AVLTree avl_create_node(void *data);
static AVLTree avl_right_rotate(AVLTree y);
static AVLTree avl_left_rotate(AVLTree x);
static int avl_balance(AVLTree node);
static int avl_height(AVLTree avl);


// Function to insert a node in an AVL tree
AVLTree AVLTree_insert(AVLTree node, void *data, CompareFunc compare) {
    assert(compare != NULL);
    if(node == NULL)
        // Found the place to insert the node
        return avl_create_node(data);
    if(compare(data, node->data) > 0)
        // The data we want to insert is greater than
        // current node's data, so we should look for it
        // in the right subtree of the node
        node->right = AVLTree_insert(node->right, data, compare);
    else if(compare(data, node->data) < 0)
        // The data we want to insert is smaller than
        // current node's data, so we should look for it
        // in the left subtree of the node
        node->left = AVLTree_insert(node->left, data, compare);
    else
        // Found node with the same data, just return it
        return node;
    // Update node's height
    node->height = 1 + MAX(avl_height(node->right), avl_height(node->left));
    // Get balance of the node (it is valid that |Balance| <= 1)
    int balance = avl_balance(node);
    // Fix the balance of the avl tree by rotating the nodes that have wrong balance
    
    // There are 4 cases
    if(balance > 1 && compare(data, node->left->data) < 0)
        // Left-Left case
        return avl_right_rotate(node);
    else if(balance > 1 && compare(data, node->left->data) > 0) {
        // Left-Right case
        node->left = avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }
    else if(balance < -1 && compare(data, node->right->data) > 0)
        // Right-Right Case
        return avl_left_rotate(node);
    else if(balance < -1 && compare(data, node->right->data) < 0) {
        // Right-Left Case
        node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }
    return node;
}

// Helper function to find the node with the maximum value in an AVL tree
static AVLTree AVLTree_max_node(AVLTree avl) {
    if (avl == NULL)
        return NULL;

    while (avl->right != NULL)
        avl = avl->right;

    return avl;
}

AVLTree AVLTree_delete(AVLTree avl, void *data, CompareFunc compare, DestroyFunc destroy) {
    if (avl == NULL)
        return NULL;

    if (compare(data, avl->data) < 0)
        avl->left = AVLTree_delete(avl->left, data, compare, destroy);
    else if (compare(data, avl->data) > 0)
        avl->right = AVLTree_delete(avl->right, data, compare, destroy);
    else {
        if ((avl->left == NULL) || (avl->right == NULL)) {
            AVLTree temp = avl->left ? avl->left : avl->right;

            if (temp == NULL) {
                // No child case
                if (destroy)
                    destroy(avl->data);
                free(avl);
                avl = NULL;
            } else {
                // One child case
                if (destroy)
                    destroy(avl->data);
                *avl = *temp;
                free(temp);
            }
        } else {
            // node with two children: Get the inorder predecessor (the maximum value in the left subtree)
            AVLTree tempNode = AVLTree_max_node(avl->left);

            // Swap the data between avl and tempNode
            void *tempData = avl->data;
            avl->data = tempNode->data;
            tempNode->data = tempData;

            avl->left = AVLTree_delete(avl->left, data, compare, destroy);
        }
    }

    if (avl == NULL)
        return NULL;

    // Update node's height
    avl->height = 1 + MAX(avl_height(avl->right), avl_height(avl->left));

    // Get balance of the node (it is valid that |Balance| <= 1)
    int balance = avl_balance(avl);

    // Fix the balance of the AVL tree by rotating the nodes that have wrong balance
    if (balance > 1 && avl_balance(avl->left) >= 0)
        // Left-Left case
        return avl_right_rotate(avl);
    else if (balance > 1 && avl_balance(avl->left) < 0) {
        // Left-Right case
        avl->left = avl_left_rotate(avl->left);
        return avl_right_rotate(avl);
    } else if (balance < -1 && avl_balance(avl->right) <= 0)
        // Right-Right Case
        return avl_left_rotate(avl);
    else if (balance < -1 && avl_balance(avl->right) > 0) {
        // Right-Left Case
        avl->right = avl_right_rotate(avl->right);
        return avl_left_rotate(avl);
    }

    return avl;
}


// Search given data in the AVL tree and returns a corresponding boolean value if it finds it or not
bool AVLTree_search(AVLTree avl, void *data, CompareFunc compare) {
    assert(compare != NULL);
    if(avl == NULL)
        return false;
    else if(compare(avl->data, data) == 0)
        return true;
    else if(compare(avl->data, data) > 0)
        return AVLTree_search(avl->left, data, compare);
    else
        return AVLTree_search(avl->right, data, compare);
}


// Inorder traversal and print of items in the AVL tree
void AVLTree_inorder_traversal(AVLTree avl, PrintFunc print) {
    if(avl == NULL)
        return;
    AVLTree_inorder_traversal(avl->left, print);
    print(avl->data);
    AVLTree_inorder_traversal(avl->right, print);
}


// Preorder traversal and print of items in the AVL tree
void AVLTree_preorder_traversal(AVLTree avl, PrintFunc print) {
    if(avl == NULL)
        return;
    print(avl->data);
    AVLTree_preorder_traversal(avl->left, print);
    AVLTree_preorder_traversal(avl->right, print);
}


// Postorder traversal and print of items in the AVL tree
void AVLTree_postorder_traversal(AVLTree avl, PrintFunc print) {
    if(avl == NULL)
        return;
    AVLTree_postorder_traversal(avl->left, print);
    AVLTree_postorder_traversal(avl->right, print);
    print(avl->data);
}


static void *avl_select(AVLTree avl, int k) {
    if(avl == NULL)
        return NULL;
    int count_left_subtree = AVL_count_items(avl->left);
    if(count_left_subtree > k)
        return avl_select(avl->left, k);
    if(count_left_subtree < k)
        return avl_select(avl->right, k - count_left_subtree - 1);
    return avl->data;
}


// Returns the data of the k-th item of in the AVL tree
void *AVLTree_select_k_th_item(AVLTree avl, int k) {
    return avl_select(avl , k-1);
}


// Check if the AVL tree is empty
bool AVLTree_empty(AVLTree avl) {
    return (avl == NULL) || (AVL_count_items(avl) == 0);
}


// Returns the number of items in the AVL tree
int AVL_count_items(AVLTree avl) {
    if(avl == NULL)
        return 0;
    return 1 + AVL_count_items(avl->left) + AVL_count_items(avl->right);
}


// Find the minimum value of an AVL tree
void *AVLTree_min_value(AVLTree avl) {
    if(avl == NULL)
        return NULL;
    if(avl->left == NULL)
        return avl->data;
    return AVLTree_min_value(avl->left);
}


// Find the maximum value of an AVL tree
void *AVLTree_max_value(AVLTree avl) {
    if(avl == NULL)
        return NULL;
    if(avl->right == NULL)
        return avl->data;
    return AVLTree_max_value(avl->right);
}


// A function to create a new node
// Height of node is initially 1, since the simple bst insertion, inserts the node as a leaf
static AVLTree avl_create_node(void *data) {
    AVLTree node = malloc(sizeof(*node));
    assert(node != NULL);
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}


// Return the height of a node
static int avl_height(AVLTree avl) {
    if(avl == NULL)
        return 0;
    return avl->height;
}


// Function to perform a right rotation on a node
static AVLTree avl_right_rotate(AVLTree y) {
    if(y->left == NULL)
        return y;
    AVLTree x = y->left;
    AVLTree T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 +  MAX(avl_height(y->left), avl_height(y->right));
    x->height = 1 + MAX(avl_height(x->left), avl_height(x->right));
    return x;
}


// Function to perform a left rotation on a node
static AVLTree avl_left_rotate(AVLTree x) {
    if(x->right == NULL)
        return x;
    AVLTree y = x->right;
    AVLTree T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + MAX(avl_height(x->left), avl_height(x->right));
    y->height = 1 + MAX(avl_height(y->left), avl_height(y->right));
    return y;
}


// Return the balance of a current node
static int avl_balance(AVLTree node) {
    if (node==NULL) return 0;
    return avl_height(node->left) - avl_height(node->right);
}


// Function to destroy an AVL tree
void AVLTree_destroy(AVLTree node, DestroyFunc destroy) {
    if(node != NULL) {
        AVLTree_destroy(node->left, destroy);
        AVLTree_destroy(node->right, destroy);
        destroy(node->data);
        free(node);
    }
}