#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RedBlackTree.h"


typedef enum { RED, BLACK } Color;

typedef struct RBTNode RBTNode;


struct RBTNode {
    void *data;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
    Color color;
};


// Dummy (leaf) node - NIL
static RBTNode NIL = { .data = NULL, .left = NULL, .right = NULL, .parent = NULL, .color = BLACK };


// Static - Local funtions
static void RBT_left_rotate(RBTNode **root, RBTNode *x);
static void RBT_right_rotate(RBTNode **root, RBTNode *x);
static RBTNode *binary_search_tree_insert(RBTNode *root, RBTNode *node, CompareFunc compare);
static RBTNode *find_successor(RBTNode *node);
static void RBT_delete_fixup(RBTNode **root, RBTNode **node);
static void *RBT_select(RBTNode *root, size_t k);


// Create a red node
static RBTNode *create_node(void *data) {
    RBTNode *node = malloc(sizeof(RBTNode));
    assert(node != NULL);
    node->data = data;
    node->left = node->right = &NIL;
    node->color = RED;
    node->parent = &NIL;
    return node;
}


// Insert the node into the binary search tree
static RBTNode *binary_search_tree_insert(RBTNode *root, RBTNode *new_node, CompareFunc compare) {
    if(root == &NIL)
        return new_node;
    if(compare(new_node->data, root->data) < 0) {
        root->left = binary_search_tree_insert(root->left, new_node, compare);
        root->left->parent = root;
    }
    else if(compare(new_node->data, root->data) > 0) {
        root->right = binary_search_tree_insert(root->right, new_node, compare);
        root->right->parent = root;
    }
    return root;
}


// Insert the node into the red black tree
/* Firstly we insert the node as it is a simple binary search tree and then make changes to
fix the violations of the red black tree */
void RBT_insert(RBTree *root, void *data, CompareFunc compare) {
    if(*root == NULL) {
        // case0: root is the only node in the tree and thus it must be colored black
        *root = create_node(data);
        (*root)->color = BLACK;
        (*root)->parent = NULL;
        return;
    }
    assert(compare != NULL);
    RBTNode *node = create_node(data);
    *root = binary_search_tree_insert(*root, node, compare);
    while(node != *root && node->parent->color == RED) {
        RBTNode *grandparent = node->parent->parent;
        if(node->parent == grandparent->left) { // parent is the left child of grandparent
            RBTNode *uncle = grandparent->right;

            // case 1: nodes's uncle is red
            // We should recolor node's parent, grandparent and uncle
            if(uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }

            // case2 : node's uncle is black
            // We should rotate node's grandparent in the opposite direction of the node
            // Then we should recolor the original parent and the grandparent
            else{
                if(node == node->parent->right) {
                    // case2i: node is the right sibling and node's parent is the left sibling
                    // We do Left - Right rotation
                    // This case graphically means that node, parent and grandparent form a triangle
                    node = node->parent;
                    RBT_left_rotate(root, node);
                }
                // case 2ii: node is the left sibling and node's parent is the also left sibing
                // We just do a right rotation
                // This case graphically means that node, parent and grandparent are in the same line
                // This lines will also be executed when node, parent and grandparent form a triangle (in case 2i)
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RBT_right_rotate(root, grandparent);
            }
        }
        else { // parent is the right child of grandparent
            RBTNode *uncle = grandparent->left;

            // case 1
            if(uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }

            // case2
            else {
                if(node == node->parent->left) {
                    // case2i: node is the left sibling and node's parent is the right sibling
                    // We do Right - Left rotation
                    node = node->parent;
                    RBT_right_rotate(root, node);
                }
                // case2ii: node is the right sibling and node's parent is also the right sibling
                // This lines will be also executed in case2i
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RBT_left_rotate(root, grandparent);
            }
        }
    }
    // the root of the tree is always black
    (*root)->color = BLACK;
    (*root)->parent = NULL;
}


// Function which returns the successor of a given node
static RBTNode *find_successor(RBTNode *node) {
    RBTNode *successor = node->right;
    while(successor->left != &NIL)
        successor = successor->left;
    return successor;
}


// Function which fixes the violations that might occur when we delete an item from the red black tree
static void RBT_delete_fixup(RBTNode **root, RBTNode **node) {
    while(((*node)->parent != NULL) && ((*node)->color == BLACK)) {
        RBTNode *node_sibling;
        if(*node == (*node)->parent->left) {
            // node is the left sibling of it's parent
            node_sibling = (*node)->parent->right;

            if(node_sibling == &NIL)
                break;

            if(node_sibling->color == RED) {
                // Case1: When the sibling color is RED, we should recolor sibling and parent and rotate left the parent
                // The new sibling of the node is one of their sibling's children and it is black. Thus we have converted case 1
                // into a 2, 3 or 4 case
                node_sibling->color = BLACK;
                (*node)->parent->color = RED;
                RBT_left_rotate(root, (*node)->parent);
                node_sibling = (*node)->parent->right;
            }

            if((node_sibling->left->color == BLACK) && (node_sibling->right->color == BLACK)) {
                // Case2: When the sibling node is black and both of it's children are black we should recolor sibling
                // and set given node to it's parent. Then we fix up the parent of given node
                node_sibling->color = RED;
                node = &((*node)->parent);
            }
            else {
                if(node_sibling->right->color == BLACK) {
                    // Case3: When only the right child of sibling is black, we also set the left child black, we set the sibling
                    // to be red and we do a right rotation to sibling node. The new sibling of the node is now a black node with two red children.
                    // Thus, we have transformed this case into case 4
                    node_sibling->left->color = BLACK;
                    node_sibling->color = RED;
                    RBT_right_rotate(root, node_sibling);
                    node_sibling = (*node)->parent->right;
                }
                // Case4: When right child of the sibling are red we set node's parent black as well as siblings right child,
                // we do a left rotation on node's parent and set given node to be the root of the tree
                node_sibling->color = (*node)->parent->color;
                (*node)->parent->color = BLACK;
                node_sibling->right->color = BLACK;
                RBT_left_rotate(root, (*node)->parent);
                (*node) = *root;
            }
        }
        else {
            // node is the right child of it's parent
            // Cases are handled accordingly
            node_sibling = (*node)->parent->left;

            if(node_sibling == &NIL)
                break;

            if(node_sibling->color == RED) {
                // Case1
                node_sibling->color = BLACK;
                (*node)->parent->color = RED;
                RBT_right_rotate(root, (*node)->parent);
                node_sibling = (*node)->parent->left;
            }

            if((node_sibling->left->color == BLACK) && (node_sibling->right->color == BLACK)) {
                // Case2
                node_sibling->color = RED;
                node = &((*node)->parent);
            }
            else {
                if(node_sibling->left->color == BLACK) {
                    // Case3
                    node_sibling->right->color = BLACK;
                    node_sibling->color = RED;
                    RBT_left_rotate(root, node_sibling);
                    node_sibling = (*node)->parent->left;
                }
                // Case4
                node_sibling->color = (*node)->parent->color;
                (*node)->parent->color = BLACK;
                node_sibling->left->color = BLACK;
                RBT_right_rotate(root, (*node)->parent);
                *node = *root;
            }
        } 
    }
    (*node)->color = BLACK;
    (*root)->parent = NULL;
}


// Remove node with given data from the red black tree
bool RBT_delete(RBTree *root, void *data, CompareFunc compare, DestroyFunc destroy) {
    assert((compare != NULL) && (destroy != NULL));
    RBTNode *old_node, *next_node, *node = *root;
    while(node != &NIL) {
        if(compare(data, node->data) == 0) {
            // Found the node with the data we want to delete 
            if((node->left == &NIL) || (node->right == &NIL))
                // if the node has not two children then it is the one we are deleting
                old_node = node;
            else{
                // Otherwise we find it's successor which is going to be the one we will delete (successor is a leaf node)
                old_node = find_successor(node);
                // in case that the node has two children we should replace the old data with the successor's data because we do not want them to get lost
                destroy(node->data);
                node->data = old_node->data;
            }
            
            // Find the next node of the one we are deleting
            if(old_node->left != &NIL)
                next_node = old_node->left;
            else
                next_node = old_node->right;
            
            // Update next node's parent
            next_node->parent = old_node->parent;

            // Update parent of the old node
            if(old_node == *root)
                *root = next_node;
            else if(old_node == old_node->parent->left)
                old_node->parent->left = next_node;
            else
                old_node->parent->right = next_node;
            
            if(old_node->color == BLACK)
                // Violations occur, when we delete a black node. When the node we delete is red there is nothing to do
                RBT_delete_fixup(root, &node);
            
            free(old_node);
            
            return true;
        }
        else if(compare(data, node->data) < 0) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return false;
}


// Search given data in the red black tree and return the data if it finds it, else return NULL
bool RBT_search(RBTree root, void *data, CompareFunc compare) {
    assert(compare != NULL);
    if((root == &NIL) || (root == NULL))
        return false;
    else if(compare(root->data, data) == 0)
        return true;
    else if(compare(root->data, data) > 0)
        return RBT_search(root->left, data, compare);
    else
        return RBT_search(root->right, data, compare);
}


static void *RBT_select(RBTNode *root, size_t k) {
    if((root == NULL) || (root == &NIL))
        return NULL;
    int count_left_subtree = RBT_count_items(root->left);
    if(count_left_subtree > k)
        return RBT_select(root->left, k);
    if(count_left_subtree < k)
        return RBT_select(root->right, k - count_left_subtree - 1);
    return root->data;
}


// Returns the data of the k-th item of in the red black tree
void *RBT_select_k_th_item(RBTree root, size_t k) {
    return RBT_select(root, k-1);
}


// Check if the red black tree is empty
bool RBT_empty(RBTree root) {
    return RBT_count_items(root) == 0;
}


// Inorder traversal and print of items in the red black tree
void RBT_inorder_traversal(RBTree root, PrintFunc print) {
    if((root == &NIL) || (root == NULL))
        return;
    RBT_inorder_traversal(root->left, print);
    print(root->data);
    RBT_inorder_traversal(root->right, print);
}


// Preorder traversal and print of items in the red black tree
void RBT_preorder_traversal(RBTree root, PrintFunc print) {
    if((root == &NIL) || (root == NULL))
        return;
    print(root->data);
    RBT_preorder_traversal(root->left, print);
    RBT_preorder_traversal(root->right, print);
}


// Returns the number of items in the red black tree
size_t RBT_count_items(RBTree root) {
    if((root == &NIL) || (root == NULL))
        return 0;
    return 1 + RBT_count_items(root->left) + RBT_count_items(root->right);
}


// Postorder traversal and print of items in the red black tree
void RBT_postorder_traversal(RBTree root, PrintFunc print) {
    if((root == &NIL) || (root == NULL))
        return;
    RBT_postorder_traversal(root->left, print);
    RBT_postorder_traversal(root->right, print);
    print(root->data);
}


// Find the minimum value of a red black tree
void *min_value(RBTree root) {
    if(root == NULL)
        return NULL;
    if(root->left == &NIL)
        return root->data;
    return min_value(root->left);
}


// Find the maximum value of a red black tree
void *max_value(RBTree root) {
    if(root == NULL)
        return NULL;
    if(root->right == &NIL)
        return root->data;
    return max_value(root->right);
}


// Left rotate given node
static void RBT_left_rotate(RBTNode **root, RBTNode *x) {
    if(x->right == &NIL)
        return;
    RBTNode *y = x->right;
    x->right = y->left;
    if(y->left != &NIL)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL){
        *root = y;
        (*root)->parent = NULL;
    }
    else 
        if(x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    y->left = x;
    x->parent = y;
}


// Right rotate given node
static void RBT_right_rotate(RBTNode **root, RBTNode *x) {
    if(x->left == &NIL)
        return;
    RBTNode *y = x->left;
    x->left = y->right;
    if(y->right != &NIL)
        y->right->parent = x;
    if(x->parent == NULL){
        *root = y;
        (*root)->parent = NULL;
    }
    else
        if(x->parent->right == x)
            x->parent->right = y;
        else
            x->parent->left = y;
    y->right = x;
    x->parent = y;
}


// Function which is used to destroy a red black tree
void RBT_destroy(RBTree node, DestroyFunc destroy) {
    if(node != &NIL) {
        RBT_destroy(node->left, destroy);
        RBT_destroy(node->right, destroy);
        destroy(node->data);
        free(node);
    }
}