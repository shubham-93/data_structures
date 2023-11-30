/*
Queue - Array implementation

--IMPLEMENTED OPERATIONS---

1. Enqueue
2. Dequeue
3. _front() - return element at the front of the queue
4. is_empty() - return true if queue is empty, else false
5. is_full() - return true if queue is full, false otherwise
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
void enqueue(int **arr, int arr_size, int *front, int *back, int data) {
    if (is_full(front, back, arr_size) == true) {
        printf("Queue is full. Cannot enqueue more.\n");
        return;
    }

    if (is_empty(front, back) == 1) {
        *front = 0;
        *back = 0;
    }
    else *back = (*back + 1) % arr_size;
    
    (*arr)[*back] = data;
}

// Dequeue one element
void dequeue(int **arr, int arr_size, int *front, int *back) {
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
int _front(int **arr, int *front) {
    if (*front == -1) {
        printf("Queue empty. No front element. Returning -1\n");
        return -1;
    }

    return (*arr)[*front];
}


int main() {
    int arr_size = 5;
    int arr[arr_size];

    int *parr = arr;
    int **pparr = &parr;

    int front = -1; // front index of the queue, initially -1 to indicate an empty queue
    int back = -1; // back index of the queue, initially -1 to indicate an empty queue

    int n; // Number of elements to enqueue
    int x; // Data to push

    printf("Enter the number of elements you want to enqueue to the queue: ");
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        printf("Enter data: ");
        scanf("%d", &x);
        enqueue(pparr, arr_size, &front, &back, x);
    }

    printf("front: %d, back: %d\n", front, back);
    printf("Return element at front of queue: %d\n", _front(pparr, &front));
    printf("Dequeue one element...\n");
    dequeue(pparr, arr_size, &front, &back);
    printf("front: %d, back: %d\n", front, back);
    printf("Dequeue one element...\n");
    dequeue(pparr, arr_size, &front, &back);
    printf("front: %d, back: %d\n", front, back);
    printf("Check if queue is empty...\n");
    printf("Is Queue empty? (0/1): %d\n", is_empty(&front, &back));
}