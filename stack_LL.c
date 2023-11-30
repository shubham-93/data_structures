/*
Stack - Linked List implementation

In order to ensure that push(), pop() and top() functions have time complexity of O(1), we can use a
linked list with insertion and deletion at the beginning of the list to implement a stack. This insertion
and deletion was already implemented in the original C code for linked lists

---IMPLEMENTED OPERATIONS---

1. push
2. pop
3. top() - returns the element at the top of the stack
4. is_empty() - returns true if stack is empty, else false
*/

#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct node {
    int data;
    struct node *next;
} node;


// Push element on top of stack
void push(node **top, int x) {
    node* new_node = (node*)malloc(sizeof(node)); //allocate memory for new node
    new_node->data = x; //assign data
    new_node->next = *top; //assign the next pointer of the new node to top, which is currently pointing to the 1st node
    *top = new_node; //reassign top to the address of the new node. top now points to the new node
}


// Pop first element off the stack
void pop(node **top) {
    if (*top == NULL) {
        printf("Stack is empty! Nothing to pop\n");
        return;
    }

    node *first = *top;
    *top = first->next;
    free(first);
}


// Return true if stack is empty, false otherwise
bool is_empty(node **top) {
    if (*top == NULL) return true;
    else return false;
}


// Return element at the top of the stack
int _top(node **top) {
    if (*top == NULL) {
        printf("Stack is empty. Returning -1.\n");
        return -1;
    }
    
    return (*top)->data;
}

int main() {
    // Initialize top node ptr to NULL. This means that, initially, the stack is empty and top doesn't point to a valid node.
    node *top = NULL;
    int num_elements, x;

    printf("Enter the number of elements to add to stack: ");
    scanf("%d", &num_elements);
    for (int i=0; i<num_elements; i++) {
        printf("Enter number to add: ");
        scanf("%d", &x);
        push(&top, x);
    }

    printf("\nPopping...\n");
    pop(&top);
    printf("Popping again...\n");
    pop(&top);

    printf("\nThe element at the top of the stack is: %d\n", _top(&top));
    printf("Is the stack empty? Answer: %d\n", is_empty(&top));

    return EXIT_SUCCESS;
}