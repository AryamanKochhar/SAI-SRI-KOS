#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node
{
    int data;          // Data part of the node
    struct Node *next; // Pointer to the next node in the list
    struct Node *prev; // Pointer to the previous node in the list
};

// Function to create a new node
struct Node *createNode(int new_data)
{
    // Allocate memory for a new node
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    // Initialize the node's data and set its next and prev pointers to NULL
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;

    // Return the newly created node
    return new_node;
}

// Function to insert a node at the beginning of the list
struct Node *insertAtBeginning(struct Node *head_ref, int new_data)
{
    // Create a new node with the provided data
    struct Node *new_node = createNode(new_data);

    // Make the new node point to the current head of the list
    new_node->next = head_ref;

    // If the list is not empty, update the previous pointer of the old head
    if (head_ref != NULL)
        head_ref->prev = new_node;

    // Set the new node as the new head of the list
    head_ref = new_node;

    // Return the new head pointer
    return head_ref;
}

// Function to insert a node after a given previous node
void insertAfter(struct Node *prev_node, int new_data)
{
    // If the previous node is NULL, print an error and return
    if (prev_node == NULL)
    {
        printf("prev_node cannot be NULL");
        return;
    }

    // Create a new node with the provided data
    struct Node *new_node = createNode(new_data);

    // Set the new node's next pointer to point to the previous node's next
    new_node->next = prev_node->next;

    // Set the new node's prev pointer to the previous node
    new_node->prev = prev_node;

    // If the previous node's next is not NULL, update its prev pointer
    if (prev_node->next != NULL)
        prev_node->next->prev = new_node;

    // Set the previous node's next pointer to the new node
    prev_node->next = new_node;
}

// Function to insert a node at the end of the list
struct Node *insertAtEnd(struct Node *head_ref, int new_data)
{
    // Create a new node with the provided data
    struct Node *new_node = createNode(new_data);

    // If the list is empty, set the new node as the head and return
    if (head_ref == NULL)
    {
        head_ref = new_node;
        return head_ref;
    }

    // Traverse to the last node of the list
    struct Node *last = head_ref;
    while (last->next != NULL)
    {
        last = last->next;
    }

    // Set the last node's next pointer to the new node
    last->next = new_node;

    // Set the new node's prev pointer to the last node
    new_node->prev = last;

    // Return the head pointer
    return head_ref;
}

// Function to delete a node with a given key (data value)
struct Node *deleteNode(struct Node *head_ref, int key)
{
    // Start from the head of the list
    struct Node *temp = head_ref;

    // Search for the node that contains the key
    while (temp != NULL && temp->data != key)
    {
        temp = temp->next;
    }

    // If the key was not found, return the head as is
    if (temp == NULL)
        return head_ref;

    // Update the previous node's next pointer if the node to delete is not the head
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head_ref = temp->next; // Update head if the node to delete is the head

    // Update the next node's prev pointer if the node to delete is not the last
    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    // Free the memory of the node to delete
    free(temp);

    // Return the head pointer
    return head_ref;
}

struct Node *insertAtIndex(struct Node *head_ref, int index, int data)
{
    struct Node *new_node = createNode(data);
    struct Node *temp = head_ref;

    // Case 1: Insertion at the head (index 0)
    if (index == 0)
    {
        new_node->next = head_ref;
        if (head_ref != NULL)
        {
            head_ref->prev = new_node; // Update the previous head's prev pointer
        }
        head_ref = new_node;
        return head_ref;
    }

    // Traverse the list to find the position to insert
    int i = 0;
    while (temp != NULL && i < index - 1)
    {
        temp = temp->next;
        i++;
    }

    // Case 2: Index is out of bounds (greater than list length)
    if (temp == NULL)
    {
        printf("Index is out of bounds.\n");
        free(new_node);
        return head_ref;
    }

    // Case 3: Insertion in the middle or end
    new_node->next = temp->next; // Set the new node's next to temp's next node
    new_node->prev = temp;       // Set the new node's prev to the current node (temp)

    if (temp->next != NULL)
    { // If the next node exists, update its prev pointer
        temp->next->prev = new_node;
    }

    temp->next = new_node; // Update the current node's next pointer to the new node

    return head_ref;
}

// Function to print the doubly linked list
void printLL(struct Node *head_ref)
{
    // Start from the head of the list
    struct Node *temp = head_ref;

    // Traverse the list and print each node's data
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n"); // New line at the end of the list
}

// Function to remove a node from a doubly linked list based on the index
struct Node *removeNodeAtIndex(struct Node *head_ref, int index)
{
    // If the list is empty or the index is invalid
    if (head_ref == NULL || index < 0)
    {
        printf("Invalid index or empty list.\n");
        return head_ref;
    }

    struct Node *temp = head_ref;
    int count = 0;

    // Traverse the list to find the node at the given index
    while (temp != NULL && count < index)
    {
        temp = temp->next;
        count++;
    }

    // If the index is greater than the number of nodes in the list
    if (temp == NULL)
    {
        printf("Index out of bounds.\n");
        return head_ref;
    }

    // If the node to be deleted is the head node
    if (temp == head_ref)
    {
        head_ref = temp->next; // Move the head to the next node
        if (head_ref != NULL)
            head_ref->prev = NULL; // Update the new head's prev pointer
    }
    else
    {
        // Adjust the previous node's next pointer
        if (temp->prev != NULL)
            temp->prev->next = temp->next;

        // Adjust the next node's prev pointer
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
    }

    // Free the memory of the removed node
    free(temp);

    return head_ref;
}

// Function to reverse the doubly linked list
struct Node *reverseLL(struct Node *head_ref)
{
    struct Node *temp = NULL;        // Temporary pointer to help in swapping
    struct Node *current = head_ref; // Start from the head

    // Traverse the list and swap the next and prev pointers of each node
    while (current != NULL)
    {
        temp = current->prev;          // Store the previous node
        current->prev = current->next; // Swap the prev and next pointers
        current->next = temp;          // Complete the swap
        current = current->prev;       // Move to the next node in the original order
    }

    // After reversing, temp points to the previous head (new tail), so move back once
    if (temp != NULL)
        head_ref = temp->prev; // Update the head pointer to the new head

    return head_ref; // Return the new head of the reversed list
}

// Function to join two doubly linked lists
struct Node *joinLL(struct Node* list1, struct Node* list2) {
    // If list1 is empty, return list2
    if (list1 == NULL) {
        return list2;
    }

    // If list2 is empty, return list1
    if (list2 == NULL) {
        return list1;
    }

    // Traverse to the last node of the first list
    struct Node* temp1 = list1;
    while (temp1->next != NULL) {
        temp1 = temp1->next;
    }

    // Connect the last node of the first list to the head of the second list
    temp1->next = list2;

    // Update the second list's head's prev pointer to the last node of the first list
    list2->prev = temp1;

    // Return the combined list's head (head of list1)
    return list1;
}


int main()
{
    struct Node *head = NULL; // Initialize the head pointer

    // Insert nodes at the end of the list
    for (int i = 0; i < 10; i++)
    {
        head = insertAtEnd(head, i); // Insert values 0 to 9 at the end
    }

    printLL(head); // Print the list

    // Reverse the list and print
    struct Node *rev = reverseLL(head); // Reverse the list
    printLL(rev);                       // Print the reversed list

    struct Node *joined = joinLL(head, rev); 
    printLL(joined);                         

    rev = insertAtIndex(rev, 1, 2);
    printLL(rev);
    return 0;
}
