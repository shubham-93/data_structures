// This header file contains the definitions of the queue-related functions defined in the queue.c source file.
// We just include this header file in other .c source files that need to use these functions.
// For example, we use a queue in the breadth-first traversal approach of a binary tree.


#ifndef NODE_STRUCT
#define NODE_STRUCT
// Binary Search Tree node
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;
#endif

// Return true if queue is empty, false otherwise
bool is_empty(int *front, int *back) {
    if (*front == -1 && *back == -1) return true;
    else return false;
}

// Return true if queue is full, false otherwise
bool is_full(int *front, int *back, int arr_size) {
    if ((*back + 1) % arr_size == *front) return true;
    else return false;
}

// Add element to the back of queue
void enqueue(node ***arr, int arr_size, int *front, int *back, node *node) {
    if (is_full(front, back, arr_size) == true) {
        printf("Queue is full. Cannot enqueue more.\n");
        return;
    }

    if (is_empty(front, back) == 1) {
        *front = 0;
        *back = 0;
    }
    else *back = (*back + 1) % arr_size;
    
    (*arr)[*back] = node;
}

// Dequeue one element
void dequeue(node ***arr, int arr_size, int *front, int *back) {
    if (is_empty(front, back) == 1) {
        printf("Queue is empty. Nothing to dequeue. \n");
        return;
    }
    else if (*front == *back) {
        *front = -1;
        *back = -1;
        return;
    }

    *front = (*front + 1) % arr_size;
}

// Return element at front of queue
node* _front(node ***arr, int *front) {
    if (*front == -1) {
        printf("Queue empty. No front element. Returning NULL\n");
        return NULL;
    }

    return (*arr)[*front];
}
