#include <stdio.h>  // Standard input/output library for printf and other functions
#include <stdlib.h> // Standard library for dynamic memory allocation (malloc)

// Define the structure of a node in the linked list
struct Node
{
    int data;            // Stores the data (integer) for each node
    struct Node *next;   // Pointer to the next node in the list
};

// Function to insert a new node at the beginning of the list
void insertAtBeginning(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node)); // Allocate memory for new node

    new_node->data = new_data; // Assign the data to the new node

    new_node->next = (*head_ref); // Point the new node to the current head

    (*head_ref) = new_node; // Update the head to point to the new node
}

// Function to insert a new node after a given previous node
void insertAfter(struct Node *prev_node, int new_data)
{
    // Check if the previous node is NULL
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node)); // Allocate memory for new node
    new_node->data = new_data;      // Assign the data to the new node
    new_node->next = prev_node->next; // Set the new node's next to the previous node's next
    prev_node->next = new_node;     // Link the previous node to the new node
}

// Function to insert a node at the end of the list
void insertAtEnd(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node)); // Allocate memory for new node
    struct Node *last = *head_ref;  // Initialize a pointer to traverse the list, starting at the head

    new_node->data = new_data;      // Assign the data to the new node
    new_node->next = NULL;          // New node will be the last node, so set its next to NULL

    // If the linked list is empty, set the new node as the head
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    // Traverse the list until the last node
    while (last->next != NULL)
        last = last->next;

    last->next = new_node; // Set the next of the last node to the new node
}

// Function to delete a node by its data value
void deleteNode(struct Node **head_ref, int key)
{
    struct Node *temp = *head_ref, *prev; // Pointers to traverse the list, temp to point to the current node and prev to track the previous node

    // If the head node contains the key, update the head and free the node
    if (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next; // Update the head
        free(temp);             // Free the memory of the old head
        return;
    }

    // Traverse the list to find the node to be deleted, keeping track of the previous node
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    // If the key is not found in the list, return
    if (temp == NULL)
        return;

    // Unlink the node to be deleted from the list
    prev->next = temp->next;

    free(temp); // Free the memory of the deleted node
}

// Function to delete a node by its index in the list
void deleteNodeAtIndex(struct Node **head_ref, int index)
{
    // If the linked list is empty, return
    if (*head_ref == NULL)
        return;

    // Store the head node
    struct Node *temp = *head_ref;

    // If the head needs to be deleted (index 0)
    if (index == 0)
    {
        *head_ref = temp->next; // Update the head
        free(temp);             // Free the old head
        return;
    }

    // Traverse the list to find the node at the given index
    struct Node *prev = NULL;
    for (int i = 0; temp != NULL && i < index; i++)
    {
        prev = temp;
        temp = temp->next;
    }

    // If the index is out of bounds, return
    if (temp == NULL)
        return;

    // Unlink the node from the list
    prev->next = temp->next;

    free(temp); // Free the memory of the node to be deleted
}

// Function to search for a node by its data value
int searchNode(struct Node **head_ref, int key)
{
    struct Node *current = *head_ref; // Initialize a pointer to traverse the list

    // Traverse the list to find the node containing the key
    while (current != NULL)
    {
        if (current->data == key) // If key is found, return true (1)
            return 1;
        current = current->next;  // Move to the next node
    }
    return 0; // If key is not found, return false (0)
}

// Function to sort the linked list in ascending order
void sortLinkedList(struct Node **head_ref)
{
    struct Node *current = *head_ref, *index = NULL;
    int temp;

    // If the list is empty, return
    if (head_ref == NULL)
    {
        return;
    }
    else
    {
        // Traverse the list with two pointers (current and index)
        while (current != NULL)
        {
            index = current->next;

            // Compare each node with all subsequent nodes and swap if necessary
            while (index != NULL)
            {
                if (current->data > index->data)
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

// Function to print the linked list
void printList(struct Node *node)
{
    // Traverse and print each node's data
    while (node != NULL)
    {
        printf(" %d ", node->data); // Print the data of the current node
        node = node->next;          // Move to the next node
    }
}

// Main function to demonstrate linked list operations
int main()
{
    struct Node *head = NULL; // Initialize the head of the list to NULL

    // Insert nodes at different positions
    insertAtEnd(&head, 1);           // Insert 1 at the end
    insertAtBeginning(&head, 2);     // Insert 2 at the beginning
    insertAtBeginning(&head, 3);     // Insert 3 at the beginning
    insertAtEnd(&head, 4);           // Insert 4 at the end
    insertAfter(head->next, 5);      // Insert 5 after the second node

    // Print the current list
    printf("Linked list: ");
    printList(head);

    // Delete a node by value (3) and print the updated list
    printf("\nAfter deleting an element: ");
    deleteNode(&head, 3);
    printList(head);

    // Search for a value (3) in the list
    int item_to_find = 3;
    if (searchNode(&head, item_to_find))
    {
        printf("\n%d is found", item_to_find); // Print if the item is found
    }       
    else
    {
        printf("\n%d is not found", item_to_find); // Print if the item is not found
    }

    // Sort the linked list and print the sorted list
    sortLinkedList(&head);
    printf("\nSorted List: ");
    printList(head);

    return 0; // Return 0 to indicate successful program termination
}
