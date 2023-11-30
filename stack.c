/*
Stack - Array implementation

---IMPLEMENTED OPERATIONS---

1. push
2. pop
3. top() - returns the element at the top of the stack
4. is_empty() - returns true if stack is empty, else false
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ARRAY_SIZE 100

// Push element on top of stack
void push(int **arr, int *top, int data, int *arr_size) {
    // Some temporary notes below:
    // if (*top == MAX_ARRAY_SIZE - 1) {
    //     printf("Stack overflow.\n");
    //     return;
    //     // Add code here to create a new array of 2x the size, copy elements from old to new array, and then
    //     // somehow return the new array for use in main(). Since push is a void fn, we cannot return, so look for other options.
    //     // How to dynamically increase the size of an array based on a condition? Shall we use VLA?

    //     // Simpler way: Pass (address of) size of array as a local variable instead of using a macro. If there is a stack overflow, 
    //     // then double the size. We don't need to pass this argument in other stack functions.        
    // }

    // Current implementation of the push() function starts below:

    if (*top == *(arr_size) - 1) {
        printf("Stack overflow. Increasing size of array.\n");
        int new_arr[(*arr_size)*2]; // Define a new array double the size of the old one
        memcpy(new_arr, *arr, sizeof(int)*(*arr_size)); // Copy bytes from smaller to bigger array
        *arr = new_arr; // Change pointer to point to the new, bigger array
        (*top)++;
        (*arr)[*top] = data;
        return;
    }

    (*top)++;
    (*arr)[*top] = data;
}


// Pop first element off the stack
void pop(int *top) {
    if (*top == -1) {
        printf("Empty stack. Nothing to pop.\n");
        return;
    }
    (*top)--;
}


// Return true if stack is empty, false otherwise
bool is_empty(int *top) {
    if (*top == -1) return true;
    else return false;
}


// Return top element from stack
int _top(int **arr, int *top) {
    if (*top == -1) {
        printf("Empty stack. No top element.\n");
        return -1; // return special value of -1 if stack is empty. We need another check in main() to verify that -1 is not the value of the topmost stack element
    }

    return (*arr)[*top];
}



int main() {
    int arr_size = 2;
    int arr[arr_size];

    int *parr = arr;
    int **pparr = &parr;

    int top = -1;
    int n; // Number of elements to push
    int x; // Data to push
    printf("Enter the number of elements you want to push to the stack: ");
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        printf("Enter data: ");
        scanf("%d", &x);
        push(pparr, &top, x, &arr_size);
    }
    
    printf("\nTop element: %d\n", _top(pparr, &top));
    printf("Popping top element...\n");
    pop(&top);
    printf("Top element is (if not -1): %d\n", _top(pparr, &top));
    printf("Is the stack empty: %d\n", is_empty(&top));

    return EXIT_SUCCESS;
}