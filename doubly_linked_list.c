/*
Doubly Linked List (DLL) in C

---IMPLEMENTED OPERATIONS---

1. Insert node:
- at the beginning
- at the end
- at nth position

2. Delete node:
- at the beginning
- at the end
- at nth position

3. Access node:
- given n, return ptr to node at nth position

4. Search node (linear search)

5. Print the entire doubly linked list data
- iteratively
- iteratively, in reverse order

6. Get length of a doubly linked list (number of nodes)



---EXTRA NOTES---
Reversing a doubly linked list is easy. First get the length of the DLL using get_length(). Then pass that into
get_nodep() to get the ptr to the last node, and assign the return value to *head (where head is of type node**).
*/


#include <stdio.h>
#include<stdlib.h>

// Doubly Linked List node
typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node;



// Print Doubly Linked List
void printLL(node *head) {
    if (head == NULL) {
        printf("DLL is empty!\n");
        return;
    }

    node *temp = head;
    printf("\n--Start LL--\n");
    while (temp!=NULL) {
        printf("Data: %d\n", temp->data);
        temp = temp->next;
    }
    printf("--End LL--\n\n");
}



// Print Doubly Linked List in reverse order
void reverse_printLL(node *head) {
    if (head == NULL) {
        printf("DLL is empty!\n");
        return;
    }

    node *temp = head;
    while (temp->next!=NULL) {
        temp = temp->next;
    }
    
    printf("\n--Start LL in reverse order--\n");
    while (temp!=NULL) {
        printf("Data: %d\n", temp->data);
        temp = temp->prev;
    }
    printf("--End LL--\n\n");
}


// Insert node at the beginning
void insert_beg(node **head, int x) {
    node* new_node = (node*)malloc(sizeof(node)); //allocate memory for new node
    new_node->data = x; //assign data
    new_node->next = *head; //assign the next pointer of the new node to head, which is currently pointing to the 1st node
    new_node->prev = NULL;
    *head = new_node; //reassign head to the address of the new node. head now points to the new node

    // Reassign prev ptr of the node next to the new node if >=1 nodes are already present
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }
}


// Insert node at the end
void insert_end(node **head, int x) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = x;
    new_node->next = NULL;

    // Add the new node and return immediately if LL is empty
    if (*head == NULL) {
        *head = new_node;
        new_node->prev = NULL;
        return;
    }

    // If LL is not empty, then proceed to add new node and fix links
    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}


// Delete node at the beginning
void del_beg(node **head) {
    if (*head == NULL) {
        printf("DBL is empty! Nothing to delete\n");
        return;
    }

    node *first = *head;
    *head = first->next;
    if (first->next != NULL) {
        node *second = first->next;
        second->prev = NULL;
    }
    free(first);
}


// Delete node at the end
void del_end(node **head) {
    if (*head == NULL) {
        printf("DBL is empty! Nothing to delete\n");
        return;
    }
    else if ((*head)->next == NULL) { //Edge case when only one node is present
        free(head);
        head = NULL;
        printf("Last node deleted.\n");
        return;
    }

    node *temp = *head;
    while(temp->next->next!=NULL) temp = temp->next;
    node *last_node = temp->next;
    temp->next = NULL;
    free(last_node);

    printf("Last node deleted.\n");
    // Or we can do this:
    // free(temp->next);
    // temp->next = NULL;
}


// Get pointer to node at n>1
node* get_nodep(node **head, int n) {
    if (*head == NULL) {
        printf("DBL is empty!\n");
        return NULL;
    }

    // if *head != NULL, create new temp node pointer to traverse LL
    int node_count = 0;
    node *temp = *head;
    while (node_count < n-1) {
        //printf("Data: %d\n", temp->num);
        temp = temp->next;
        if (temp == NULL) {
            printf("LL too small\n");
            return NULL;
        }
        node_count++;
    }
    //printf("Data at %dth position is %d\n", n, temp->num);
    return temp;
}


// Linear search
node* search_data(node *head, int num) {
    if (head == NULL) {
        printf("LL empty!\n");
        return NULL;
    }

    node *temp = head;
    while (temp!=NULL) {
        if (temp->data == num) return temp; // return ptr to node if data found
        temp = temp->next;
    }

    return temp; // return NULL (which is what temp will be here) if data not found
}


// Get length of DLL, that is, number of nodes
int get_length(node *head) {
    int num_nodes = 0;
    if (head == NULL) return num_nodes;

    node *temp = head;
    while (temp != NULL) {
        temp = temp->next;
        num_nodes++;
    }

    return num_nodes;
}


// Insert node at nth position with the data x
void insert_node(node **head, int n, int x) {
    if (get_length(*head) < n-1) {
        printf("LL too small for a node to be added at %dth position\n", n);
        return;
    }

    if (*head==NULL && n>1) {
        printf("LL is empty. You are trying to insert a node at a position n>1. Please choose n=1\n");
        return;
    }

    //If LL is empty but we want to add a node at 1st position, then do it
    if (*head==NULL && n==1) {
        insert_beg(head, x);
        return;
    }

    //If node is to be added at the end of the LL, then do it
    if (n == get_length(*head) + 1) {
        insert_end(head, x);
        return;
    }

    // create new node, assign it a value, and point it to where the ptr to nth node was pointing
    node *nth_node = get_nodep(head, n);
    node *new_node = (node*)malloc(sizeof(node));

    new_node->data = x;
    new_node->next = nth_node;
    node *n_minus_one_node = nth_node->prev;
    nth_node->prev = new_node;

    // Special case when n-1 = 0, because then to make head to point to the new node, we need the ptr to head, which does not exist.
    // Even if we create it, it won't matter, because head would still point to the original node and the LL will stay unchanged
    // (Also note that we traverse and print the elements of a list using head, and not using a (copy of) head that sits inside another node)
    if (n == 1) {
        *head = new_node;
        new_node->prev = NULL;
    }    
    else {
        n_minus_one_node->next = new_node;
        new_node->prev = n_minus_one_node;
    }
}


// Delete node at nth position
void delete_node(node **head, int n) {
    //delete node at nth position (n=1,2,3,...)
    // if head is NULL, LL is empty. Return immediately.
    if (*head == NULL) {
        printf("Linked List is empty!\n");
        return;
    }

    if (get_length(*head) < n) {
        printf("Cannot delete node at position %d for a LL of length %d", n, get_length(*head));
        return;
    }

    // special case when the first node is to be deleted. We need to reassign head directly
    if (n==1) {
        node *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
        return;
    }
    else {
        node *del_node = get_nodep(head, n);
        del_node->prev->next = del_node->next;
        del_node->next->prev = del_node->prev;
        free(del_node);
    }
}


int main() {
    // Initialize head node ptr to NULL. This means that, initially, the LL is empty and the head doesn't point to a valid node.
    node *head = NULL;
    int num_elements, x;

    printf("Enter the number of elements to add to DLL: ");
    scanf("%d", &num_elements);
    for (int i=0; i<num_elements; i++) {
        printf("Enter number to add: ");
        scanf("%d", &x);
        //insert_beg(&head, x);
        insert_end(&head, x);
    }

    printLL(head);

    insert_node(&head,3,99);

    printLL(head);
    reverse_printLL(head);

    // node *test_ptr;
    // test_ptr = get_nodep(&head, 2);
    // printf("Data at node 2 is %d\n", test_ptr->data);
}