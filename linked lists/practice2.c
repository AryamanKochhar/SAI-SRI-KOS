#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void insertAtBeginning(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void insertAfter(struct Node *prev_node, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    if (prev_node == NULL)
    {
        return;
    }

    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void insertAtEnd(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = (*head_ref);

    new_node->data = new_data;
    new_node->next = NULL;

    if ((*head_ref) == NULL)
    {
        (*head_ref) = new_node;
        return;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = new_node;
}

void deleteNode(struct Node **head_ref, int key)
{
    struct Node *temp = (*head_ref);
    struct Node *prev;

    if (temp != NULL && temp->data == key)
    {
        (*head_ref) = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    free(temp);
}

void sortLL(struct Node **head_ref)
{
    if ((*head_ref) == NULL)
    {
        return;
    }

    struct Node *current = (*head_ref);
    struct Node *index = NULL;
    int temp;

    while (current != NULL)
    {
        index = current->next;
        while (index != NULL)
        {
            if (current->data > index->data)
            {
                int temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

void reverseLL(struct Node **head_ref)
{
    struct Node *curr = (*head_ref);
    struct Node *next = NULL;
    struct Node *prev = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }

    (*head_ref) = prev;
}

void printList(struct Node *node)
{
    // Traverse and print each node's data
    while (node != NULL)
    {
        printf(" %d ", node->data); // Print the data of the current node
        node = node->next;          // Move to the next node
    }
    printf("\n");
}

int main()
{
    struct Node *head = NULL;

    for (int i = 0; i < 10; i++)
    {
        insertAtBeginning(&head, i);
    }
    printList(head);

    reverseLL(&head);

    printList(head);
}