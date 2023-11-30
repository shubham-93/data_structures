/*
Binary search tree(BST)

A BST is a non-linear, tree data structure that allows for fast O(log n) average time complexity for
insertion, deletion and search. (In the worst case (when the tree is heavily unbalanced),
these three operations are O(n), and we would need to have a balanced BST in order to achieve
O(log n) complexity). This speedup is an improvement over Linked Lists, which have O(n) time
complexity for insertion and deletion (after including overhead for accessing) and also for search.
For similar reasons, BSTs are also better than arrays.

The complexity of O(log n) appears because each of the above 3 operations are recursively
performed on subtrees of a parent tree, where each subtree has only half the number of elements
compared to the full tree. This way, we split the access/search space by half every successive step.

A BST can also be seen as a non-linear structure for visualizing/implementing a binary search over
a sorted list: for a given root, all nodes in its left subtree are smaller than it and all nodes in its
right subtree are larger than it. This root is then the midpoint in a binary search. The root of the 
left/right subtree is the midpoint in the subsequent search, and so on.

Many problems using BST can be solved recursively: in particular, any algorithm applied on the root
of the tree can be applied to the roots of its subtrees, and so on.

---IMPLEMENTED OPERATIONS---
1. Insert
2. Find maximum or minimum element
3. Find height of the tree (this works for a binary tree, not just a BST)
4. Find number of elements (we call it size) in a binary tree
5. Check if a binary tree is balanced, that is, if the difference in heights of its left and right subtrees is not more than 1
6. Depth-first traversal
    - In-order traversal
    - Pre-order traversal
    - Post-order traversal
7. Breadth-first traversal - Use the queue function implemented before (appropriately modified to store node* instead of int in queue). Include the "queue.h" header in the current directory
8. Check if a binary tree is a binary search tree
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"


#ifndef NODE_STRUCT
#define NODE_STRUCT
// Binary Search Tree node
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;
#endif


// Create a new BST node and add data to it
void create(node **root, int data) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    *root = new_node;
}


// Insert data into BST
void insert(node **root, int data) {
    // If BST is empty, create the root node
    if (*root == NULL) {
        create(root, data);
    }
    else if (data <= (*root)->data) insert(&((*root)->left), data); // If input data is less than (or equal to) data in root node, then go to left subtree and try inserting there
    else insert(&((*root)->right), data); // If input data is greater than data in root node, then go to right subtree and try inserting there
}


// Get minimum element in BST
int get_min(node **root) {
    if (*root == NULL) {
        printf("Empty BST, returning -1\n");
        return -1;
    }

    if ((*root)->left == NULL) return (*root)->data;
    return get_min(&((*root)->left));
}


// Get maximum element in BST
int get_max(node **root) {
    if (*root == NULL) {
        printf("Empty BST, returning -1\n");
        return -1;
    }

    if ((*root)->right == NULL) return (*root)->data;
    return get_max(&((*root)->right));
}


// Return maximum of 2 integers
int max(int x, int y) {
    return (x>=y)?x:y;
}


// Get height of binary tree
int get_height(node **root) {
    if (*root == NULL) return -1; // Returns -1 when tree is empty, or when node is a leaf

    int height_left_subtree, height_right_subtree;
    height_left_subtree = get_height(&((*root)->left)); // Find height of left subtree
    height_right_subtree = get_height(&((*root)->right)); // Find height of right subtree
    return 1 + max(height_left_subtree, height_right_subtree); // Find height of tree as max(height of left subtree, height of right subtree) + 1
}


// Get number of elements in a binary tree
int get_size(node **root) {
    if (*root == NULL) return 0; // Returns 0 when tree is empty, or when node is a leaf

    int size_left_subtree, size_right_subtree;
    size_left_subtree = get_size(&((*root)->left));
    size_right_subtree = get_size(&((*root)->right));
    return 1 + size_left_subtree + size_right_subtree;
}


// Check if binary tree is balanced
bool is_balanced(node **root) {
    // A tree is balanced if its left and right subtrees are balanced
    if (*root == NULL) return true; // Empty tree is always balanced
    bool is_left_subtree_balanced = is_balanced(&((*root)->left)); // Check if left subtree is balanced
    bool is_right_subtree_balanced = is_balanced(&((*root)->right)); // Check if right subtree is balanced
    // The above 2 conditions to check if left and right subtrees are balanced allow us to traverse the binary
    // tree from root to the leaf, and then go up one node at a time and check if each node corresponds to a
    // balanced tree. If any of these trees is unbalanced, false is propagated from bottom to top. The downside
    // of this algorithm is that each node it is O(n^?) because each height-checking is done 

    int height_left_subtree = get_height(&((*root)->left)); // Find height of left subtree
    int height_right_subtree = get_height(&((*root)->right)); // Find height of right subtree

    int height_diff_subtrees = abs(height_left_subtree - height_right_subtree); // Absolute value of difference of left and right subtree heights

    if ((is_left_subtree_balanced) && (is_right_subtree_balanced) && (height_diff_subtrees <= 1)) return true;
    else return false;
}


// In-order traversal (depth-first)
void in_order(node **root) {
    if (*root == NULL) return; // Return when node is leaf (or when tree is empty)
    in_order(&((*root)->left));
    printf("%d\n", (*root)->data);
    in_order(&((*root)->right));
}


// Pre-order traversal (depth-first)
void pre_order(node **root) {
    if (*root == NULL) return; // Return when node is leaf (or when tree is empty)
    printf("%d\n", (*root)->data);
    pre_order(&((*root)->left));
    pre_order(&((*root)->right));
}


// Post-order traversal (depth-first)
void post_order(node **root) {
    if (*root == NULL) return; // Return when node is leaf (or when tree is empty)
    post_order(&((*root)->left));
    post_order(&((*root)->right));
    printf("%d\n", (*root)->data);
}


// Breadth-first traversal (level order). Use queue to store node*
void level_order(node **root) {
    if (*root == NULL) return; // Return when tree is empty
    
    int arr_size = 20;
    node* arr[arr_size];

    node **parr = arr;
    node ***pparr = &parr;

    int front = -1; // front index of the queue, initially -1 to indicate an empty queue
    int back = -1; // back index of the queue, initially -1 to indicate an empty queue

    enqueue(pparr, arr_size, &front, &back, (*root)); // Enqueue root node of tree

    // Run loop until all elements in queue are dequeued
    while (!is_empty(&front, &back)) {
        node *front_node = _front(pparr, &front); // Get node at front of queue
        printf("%d\n", front_node->data); // Print data in front node
        if (front_node->left != NULL) enqueue(pparr, arr_size, &front, &back, front_node->left); // Check if left subtree's root node is NULL. If not, push the node to queue
        if (front_node->right != NULL) enqueue(pparr, arr_size, &front, &back, front_node->right); // Check if right subtree's root node is NULL. If not, push the node to queue
        dequeue(pparr, arr_size, &front, &back);
    }
}


// Check if binary tree is binary search tree or not. To be used within is_BST()
bool is_BST_utility(node **root, int min_lim, int max_lim) {
    // In order to check if a binary tree is a BST or not, we check if a node has its data in the
    // appropriate limits according to the structure of a BST, and also check if the left and 
    // right subtrees are also BSTs.
    if (*root == NULL) return true;

    if (   ((*root)->data > min_lim)
        && ((*root)->data <= max_lim) // <= instead of < because duplicate data elements are added to the left child node in our implementation (see the insert() function)
        && (is_BST_utility(&((*root)->left), min_lim, (*root)->data))
        && (is_BST_utility(&((*root)->right), (*root)->data, max_lim))
    ) return true;
    else return false;

}

// Check if binary tree is binary search tree or not, using is_BST_utility()
bool is_BST(node **root) {
    return is_BST_utility(root, INT32_MIN, INT32_MAX); // The initial minimum and maximum limits are the smallest and largest possible values of int32
}



int main() {
    // int arr_size = 20;
    // int arr[arr_size];

    // int *parr = arr;
    // int **pparr = &parr;

    // int front = -1; // front index of the queue, initially -1 to indicate an empty queue
    // int back = -1; // back index of the queue, initially -1 to indicate an empty queue
    //enqueue(pparr, arr_size, &front, &back, 10);
    //printf("Element at front of queue is %d\n", _front(pparr, &front));
    
    
    // Root ptr of BST
    node *root;
    root = NULL; // Initialized to NULL because BST is empty when program starts

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 500);

    printf("%d, %d, %d\n", root->data, root->left->data, root->right->data);
    insert(&root, -500);
    insert(&root, 20);
    insert(&root, -600);
    printf("Max element is: %d\n", get_max(&root));
    printf("Height of tree is: %d\n", get_height(&root));
    printf("Size of tree is: %d\n", get_size(&root));
    printf("Is tree balanced (0/1): %d\n", is_balanced(&root));

    printf("In-order traversal:\n");
    in_order(&root);

    printf("Pre-order traversal:\n");
    pre_order(&root);

    printf("Post-order traversal:\n");
    post_order(&root);

    printf("Level-order traversal:\n");
    level_order(&root);

    printf("Is BST?: %d\n", is_BST(&root));

    return EXIT_SUCCESS;
}