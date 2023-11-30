/*
Linked List is a linear data structure of nodes (in heap memory) connected to each other through links/pointers.

Golden rule: In order to change the contents of a node in a linked list, you need the ptr to that node.

Note: Copying pointers allows you to access objects in memory irrespective of where
the copied pointers were defined in the program (the scope). For e.g., even if those copied pointers are defined inside functions,
and therefore are freed up once the function returns to the caller, those ptrs can be used to access, traverse and permanently modify
the contents of memory locations that can be reached using that copied ptr. Each object is located at a unique address,
so copying pointers (which copies addresses) allows you to access memory locations that could be accessed by the original ptr.


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
- given n, print data at nth position
- given n, return ptr to node at nth position

4. Search node (linear search)

5. Print the entire linked list data
- iteratively
- recursively
- recursively, in reverse order

6. Get length of a linked list (number of nodes)

7. Link nodes at positions n and m
- using positions n and m
- using ptrs to nodes at positions n and m

8. Reverse a linked list
- iteratively
- recursively

9. Swap data at node positions n and m



---EXTRA NOTES--- 
Deleting a series of nodes between (and including) positions n and m: In order to do this, we have to delete nodes one by one.
We cannot delete them all in one go. That is, we need to delete a node, reform the links, and repeat the process.
We need to do this repetitively because if we delete one node without relinking, we lose access/ptr to the next node to be deleted.
So we just use a loop to delete all nodes, ony by one, from position n to position m. At the end of the loop,
the ptr to nth node now equals the next ptr of mth node.
Note that this is different from deleting an array. There, we can just directly free the pointer to the array and
all memory corresponding to it is freed. One-by-one deletion is not required. This is possible because
arrays are stored in contiguous blocks of memory, unlike linked lists, which are stored in non-contiguous blocks (in the heap) connected to
each other by ptrs. Ptr arithmetic is then powerful for array manipulation, but useless for LLs.

To create multiple linked lists, we can create an array of head ptrs. Each head ptr represents a separate linked list.
The functions below are defined for a global head ptr (called head). If we want to make them flexible to use on any linked list,
we can modify each function by adding a new parameter of type node* that takes the head of a LL: e.g. node* func(..., node *head_LL),
and then replace all occurences of head inside the functions by head_LL. Note that since node *head_LL is local to the function
call stack, it will be cleared up after the function returns, and so we need the function's return type to also be of the type
node*. If we want to avoid returning redefined head ptrs to main (or another function) every time, we can simulate call-by-reference by
passing node** to functions instead. We do this in the doubly_linked_list.c file.

How to use a linked list to reverse a string, that is, an array of characters:
Declare 2 pointers: one that points to the beginning of char *
and another that points to the last char (the one before \0). Then dereference the pointers and swap the values.
Then increment the start ptr, and decrement the end ptr. Loop over this until start ptr <= end ptr. When the loop
ends, we will be left with a reversed string.
*/

#include <stdio.h>
#include <stdlib.h>
//#pragma pack(1)

// Node struct
typedef struct node {
    int data;
    struct node *next;
} node;

// Global variable that points to the first LL node
node *head;



// Print full LL
void printLL() {
    // print each data in LL
    // if head is NULL, LL is empty. Return immediately.
    if (head == NULL) {
        printf("Linked List is empty!\n");
        return;
    }
    // if head != NULL, create new temp node pointer to traverse LL
    // Traverse list and print each element
    node *temp = head;
    printf("\n--Start LL--\n");
    while (temp!=NULL) {
        printf("Data: %d\n", temp->data);
        temp = temp->next;
    }
    printf("--End LL--\n\n");
    
}


// Access/print data at node n>1
void print_data(int n) {
    // if head is NULL, LL is empty. Return immediately.
    if (head == NULL) {
        printf("Linked List is empty!\n");
        return;
    }
    // if head != NULL, create new temp node pointer to traverse LL
    int node_count = 0;
    node *temp = head;
    while (node_count < n-1) {
        temp = temp->next;
        if (temp==NULL) {
            printf("LL too small\n");
            return;
        }
        node_count++;
    }
    printf("Data at %dth position is %d\n", n, temp->data);
    
}


// Insert node at beginning of LL
void insert_beg (int x) {
    node* new_node = (node*)malloc(sizeof(node)); // allocate memory for new node
    new_node->data = x; // assign data
    new_node->next = head; // assign the next pointer of the new node to head, which is currently pointing to the 1st node
    head = new_node; // reassign head to the address of the new node. head now points to the new node
}


// Insert node at end of LL
void insert_end (int x) {
    node* new_node = (node*)malloc(sizeof(node)); // allocate memory for new node
    new_node->data = x; // assign data
    new_node->next = NULL; // assign next pointer to NULL to indicate that this node should be at the end

    if (head == NULL) {
        head = new_node; // if head == NULL, head now points to the new node
        return; // return immediately to prevent potential segfault below
    }

    node *temp = head; // create a temp pointer to traverse the list

    // Check if the pointer to the pointer of temp is NULL.
    // If yes, end loop, and reassign the pointer to the pointer of temp to the new node to create a new link
    // Else, reassign the [temp pointer] to [the pointer to the temp pointer]. This way we traverse the list.
    while (temp->next!=NULL) temp = temp->next; // note that the condition in this while loop has the side effect of accessing temp_next->next to check if it's NULL. If temp_next=head and head==NULL, we will erroneously access forbidden memory (segfault). To prevent this invalid memory access, it is important to immediately return from the function upon finding that head==NULL
    temp->next = new_node;
}


// Delete node at beginning of LL
void delete_beg() {
    if (head == NULL) {
        printf("LL is empty. Nothing to delete.\n");
        return;
    }

    node *temp = head;
    head = head->next;
    free(temp);
    printf("First node deleted.\n");
}


// Delete node at end of LL
void delete_end() {
    if (head == NULL) {
        printf("LL is empty. Nothing to delete.\n");
        return;
    }
    else if (head->next == NULL) { // Edge case when only one node is present
        free(head);
        head = NULL;
        printf("Last node deleted.\n");
        return;
    }

    node *temp = head;
    
    while(temp->next->next!=NULL) temp = temp->next; //segfault can happen here. We cannot do temp->next->next if temp->next is itself NULL. So we need to first check for NULL at the first step before checking it at the second step. Or, just add another else if statement like above.
    node *last_node = temp->next;
    temp->next = NULL;
    free(last_node);

    printf("Last node deleted.\n");
    // Or we can do this:
    // free(temp->next);
    // temp->next = NULL;
}


// Get number of nodes in LL
int get_length() {
    int data_nodes = 0;
    if (head == NULL) return data_nodes;

    node *temp = head;
    while (temp!=NULL) {
        temp = temp->next;
        data_nodes++;
    }

    return data_nodes;
}


// Get pointer to node at nth position (n>0)
node* get_nodep(int n) {
    // if head is NULL, LL is empty. Return immediately.
    if (head == NULL) {
        printf("Linked List is empty!\n");
        return NULL;
    }
    
    // if head != NULL, create new temp node pointer to traverse LL
    int node_count = 0;
    node *temp = head;
    while (node_count < n-1) {
        //printf("Data: %d\n", temp->data);
        temp = temp->next;
        if (temp==NULL) {
            printf("LL too small\n");
            return NULL;
        }
        node_count++;
    }
    //printf("Data at %dth position is %d\n", n, temp->data);
    return temp;
}
// Question: What if someone accidentally inputs n=0 when calling get_nodep()? How to return from the function safely, and without returning a node ptr?


// Insert node at node n with the data x
void insert_node(int n, int x) {
    if (get_length() < n-1) {
        printf("LL too small for a node to be added at %dth position\n", n);
        return;
    }

    if (head==NULL && n>1) {
        printf("LL is empty. You are trying to insert a node at a position n>1. Please choose n=1\n");
        return;
    }

    //If LL is empty but we want to add a node at 1st position, then do it
    if (head==NULL && n==1) {
        insert_beg(x);
        return;
    }

    //If node is to be added at the end of the LL, then do it
    if (n == get_length() + 1) {
        insert_end(x);
        return;
    }

    // create new node, assign it a value, and point it to where the ptr to nth node was pointing
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = x;
    new_node->next = get_nodep(n);

    // Special case when n-1 = 0, because then to make head to point to the new node, we need the ptr to head, which does not exist.
    // Even if we create it, it won't matter, because head would still point to the original node and the LL will stay unchanged
    // (Also note that we traverse and print the elements of a list using head, and not using a (copy of) head that sits inside another node)
    if (n-1 == 0) head = new_node;
    else get_nodep(n-1)->next = new_node;
}


// Delete node at position n>1
void delete_node(int n) {
    // if head is NULL, LL is empty. Return immediately.
    if (head == NULL) {
        printf("Linked List is empty!\n");
        return;
    }

    if (get_length() < n) {
        printf("Cannot delete node at position %d for a LL of length %d", n, get_length());
        return;
    }

    // special case when the first node is to be deleted. We need to reassign head directly
    if (n==1) {
        node *temp = head;
        head = head->next;
        free(temp);
        return;
    }
    else {
        node *del_node = get_nodep(n);
        get_nodep(n-1)->next = del_node->next;
        free(del_node);
    }
}


// Linear search a linked list
node* search_data(int data) {
    if (head == NULL) {
        printf("LL empty!\n");
        return NULL;
    }

    node *temp = head;
    while (temp!=NULL) {
        if (temp->data == data) return temp; // return ptr to node if data found
        temp = temp->next;
    }

    return temp; // return NULL (which is what temp will be here) if data not found
}


// Join 2 nodes at start and end positions. Node at start points to node at end to form a loop
void join_nodes(int start, int end) {
    node *nodep_start = get_nodep(start);
    node *nodep_end = get_nodep(end);
    if (nodep_start==NULL || nodep_end==NULL) {
        printf("Start or end node is invalid (either because LL is empty or too small)");
        return;
    }
    nodep_start->next = nodep_end;
}


//join 2 nodes, given the pointers to these start and end nodes
void join_nodesp(node *nodep_start, node *nodep_end) {
    if (nodep_start==NULL || nodep_end==NULL) {
        printf("Invalid node join. This can happen because LL is too small for the operation you want to perform, or the LL is empty, or the node pointers you supplied are invalid.");
        return;
    }
    nodep_start->next = nodep_end;
}


// Reverse LL
void reverseLL() {
    if (head==NULL) {
        printf("LL is empty. Nothing to reverse\n");
        return;
    }
    // Create 3 node ptrs: prev, cur, and next. They point to the previous, current, and next node in the LL, respectively.
    node *prev, *cur, *next;
    prev = NULL;
    cur = head;
    while (cur!=NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
}


// Print LL using recursion
void recursive_print(node *temp_head) { // temp_head is a temp node ptr used to traverse the LL
    if (head == NULL) {
        printf("LL is empty!\n");
        return;
    }

    if (temp_head==head){
        printf("\n--Start LL--\n");
    }

    if (temp_head==NULL){
        printf("--End LL--\n\n");
        return;
    }

    printf("Data: %d\n", temp_head->data);
    recursive_print(temp_head->next);
}


// Reverse LL using recursion
void recursive_reverse_print(node *temp_head) {
    // temp_head is a local variable here, that initially has the value of (global) head

    // The idea is to first traverse until the end of the LL, using recursion, and then return the called functions one by one (pop the function call stacks), printing the data every time before returning
    if (temp_head == NULL) return;

    recursive_reverse_print(temp_head->next);
    printf("Data: %d\n", temp_head->data);    
}


// Reverse LL using recursion. Uses the same idea as the function recursive_reverse_print() above
void recursive_reverseLL(node *temp_head) {
    if (temp_head == NULL) {
        printf("LL is empty!\n");
        return;
    }

    if (temp_head->next == NULL) {
        head = temp_head;
        return;
    }

    recursive_reverseLL(temp_head->next);
    node *next_node = temp_head->next; // Get ptr to the node next to the current node being pointed to by temp_head in the function call
    next_node->next = temp_head; // Link the next node to the current node, effectively reversing the link
    temp_head->next = NULL; // Assign the next ptr of the current temp_head *node to NULL. 
    // This is safe to do, and we do not lose any link to the next node (because it was just linked in reverse order)
    // or to the previous node (because the previous node still points to the current node).
    // We also assign NULL because the last node in the recursive call will be the original first node, whose next ptr we anyway want to assign to NULL to 
    // indicate the end of the linked list.
}


// Swap data at nodes n and m
void swap_data(int n, int m) {
    if (head == NULL) {
        printf("LL is empty!\n");
        return;
    }

    int temp;
    temp = get_nodep(n)->data;
    get_nodep(n)->data = get_nodep(m)->data;
    get_nodep(m)->data = temp;
}



int main() {
    head = NULL;
    int data_elements;
    int x;
    printf("Enter number of elements to add to LL: ");
    scanf("%d", &data_elements);
    for(int i=0; i<data_elements; i++){
        printf("Enter number to add to end of LL: ");
        scanf("%d", &x);
        insert_end(x);
        //insert_beg(x);
        printLL();
    }

    //delete_end();
    //delete_node(2);
    //printLL();
    printf("LL has %d nodes\n", get_length());
    //print_data(3);
    //node *third_node;
    //third_node = get_nodep(3);
    //if (third_node != NULL) printf("Node at nth position has data: %d\n", third_node->data);
    
    //join_nodes(3,1) gives a circularly-connected LL
    //join_nodes(1,3) gives a list that jumps from 1 to 3 (and beyond). The node at 2 is skipped. But the memory it corresponds to is not yet freed!
    //join_nodes(3,1);
    //printLL();
    
    //join_nodesp(get_nodep(4), get_nodep(2));
    //insert_node(2,7);
    //delete_node(3);
    //reverseLL();
    //printLL();
    //swap_data(2,4);
    //recursive_print(head);

    insert_node(2, 99);
    printLL();
    recursive_reverseLL(head);
    printLL();
    return EXIT_SUCCESS;
}