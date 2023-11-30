/*
Queue - Linked List implementation

In order to have O(1) complexity for enqueue and dequeue operations, we need to create a pointer to
the front of the queue and a pointer to the back of the queue. Moreover, we have 2 options:
if we enqueue at the "front" of the LL and dequeue at the "tail", then enqueue is easily O(1) using
a singly linked list. For dequeue, however, we need to free the last element and the point the
tail pointer to the second last element, which essentially means that we need 2 pointers: a pointer
to the last element and another to the second last element. However, if we want to be able to free the last element
and shift the pointer to the second last element, we actually need to create a pointer
to point to the second last element, and another pointer to point to the third last element, and so on.
This is why singly linked list is not a good option here. This can, however, be easily done if we have
a doubly linked list.

For this reason, to have O(1) complexity for both enqueue and dequeue, we dequeue at the "head" of the LL,
and enqueue at the "tail".

--IMPLEMENTED OPERATIONS---

1. Enqueue
2. Dequeue
3. _front() - return element at the front of the queue
4. is_empty() - return true if queue is empty, else false
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Linked List node
typedef struct node {
    int data;
    struct node *next;
} node;


// Check if queue is empty. Return true if yes, false otherwise
bool is_empty(node **front) {
    if (*front == NULL) return true;
    else return false;
}


// Return element at the front of queue
int _front(node **front) {
    // Check if queue is empty
    if (is_empty(front) == 1) {
        printf("Queue is empty. Returning -1\n");
        return -1;
    }

    return (*front)->data;
}


// Delete node at the front of the queue
void dequeue(node **front, node **back) {
    // Check if queue is empty
    if (is_empty(front) == 1) {
        printf("Queue is empty. Nothing to dequeue\n");
        return;
    }

    node *first = *front;
    *front = first->next;
    free(first);

    // When queue is empty, put back ptr to NULL
    if (*front == NULL) *back = NULL; 
}


// Insert node at the back of the queue
void enqueue(node **front, node **back, int x) {
    // Create a new node
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = x; // Add data
    new_node->next = NULL; // Put address of last node's next ptr to NULL

    // Case when the first node is enqueued, and back ptr is NULL
    if (*back == NULL) {
        *front = new_node; // Connect front to the new node
        *back = new_node;
        return;
    }

    // In case queue is not empty, link the newly created node to the existing last node
    (*back)->next = new_node;
    *back = new_node; // Reassign back ptr to point to the last node
}



int main() {
    // In the beginning, queue is empty, so we initialize front and back ptrs to NULL
    node *front = NULL;
    node *back = NULL;

    int n; // Number of elements to enqueue
    int x; // Data to push

    printf("Enter the number of elements you want to enqueue to the queue: ");
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        printf("Enter data: ");
        scanf("%d", &x);
        enqueue(&front, &back, x);
    }

    printf("front: %d, back: %d\n", front->data, back->data);
    printf("Return element at front of queue: %d\n", _front(&front));
    printf("Dequeue one element...\n");
    dequeue(&front, &back);
    printf("front: %d, back: %d\n", front->data, back->data);
    printf("Dequeue one element...\n");
    dequeue(&front, &back);
    printf("Check if queue is empty...\n");
    printf("Is Queue empty? (0/1): %d\n", is_empty(&front));
}