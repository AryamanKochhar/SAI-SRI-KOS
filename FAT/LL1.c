#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct node
{
    int data;
    struct node *next;
} L;

// Create a new node
L *newNode(int data)
{
    L *temp = (L *)malloc(sizeof(L));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Traverse and print the linked list
void traverse(L *head)
{
    L *curr = head;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Insert a node at a given position
L *insert(L *head, int pos, int data)
{
    if (pos < 1)
    {
        printf("INVALID POSITION\n");
        return head;
    }

    // Insert at the beginning
    if (pos == 1)
    {
        L *temp = newNode(data);
        temp->next = head;
        return temp;
    }

    // Traverse to the position
    L *current = head;
    int i = 1;
    while (current != NULL && i < pos - 1)
    {
        current = current->next;
        i++;
    }

    if (current == NULL)
    {
        printf("POSITION OUT OF RANGE\n");
        return head;
    }

    // Insert the new node
    L *temp = newNode(data);
    temp->next = current->next;
    current->next = temp;
    return head;
}

// Delete a node at a given position
L *deleten(L *head, int pos)
{
    if (head == NULL || pos < 1)
    {
        printf("INVALID POSITION\n");
        return head;
    }

    // Delete the first node
    if (pos == 1)
    {
        L *temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    // Traverse to the position
    L *curr = head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++)
    {
        curr = curr->next;
    }

    if (curr == NULL || curr->next == NULL)
    {
        printf("POSITION OUT OF RANGE\n");
        return head;
    }

    // Delete the node
    L *temp = curr->next;
    curr->next = curr->next->next;
    free(temp);
    return head;
}

// Bubble sort for linked list
void bubbleSort(L *head)
{
    int swapped;
    L *curr;
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        curr = head;

        // Traverse the list and swap data if needed
        while (curr->next != NULL)
        {
            if (curr->data > curr->next->data)
            {
                int temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
                swapped = 1;
            }
            curr = curr->next;
        }
    } while (swapped);
}

// Main function
int main()
{
    L *head = NULL;
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("No elements to process.\n");
        return 0;
    }

    printf("Enter the elements:\n");
    for (int i = 1; i <= n; i++)
    {
        int element;
        scanf("%d", &element);
        head = insert(head, i, element);
    }

    printf("Original list: ");
    traverse(head);

    head = deleten(head, n);
    printf("After deleting the last element: ");
    traverse(head);

    bubbleSort(head);
    printf("Sorted list: ");
    traverse(head);

    return 0;
}
