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
    if (prev_node == NULL)
    {
        printf("Node cannot be null");
        return;
    }

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void insertAtEnd(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = (*head_ref);

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_node;
}

void deleteNode(struct Node **head_ref, int key)
{
    struct Node *temp = *head_ref;
    struct Node *prev;

    if(temp != NULL && temp == key)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void deleteNodeAtIndex(struct Node **head_ref, int key)
{
    
}