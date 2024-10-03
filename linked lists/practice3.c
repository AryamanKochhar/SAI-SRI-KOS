#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *createNode(int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

struct Node *insertAtBeginning(struct Node *head_ref, int new_data)
{
    struct Node *new_node = createNode(new_data);

    
}