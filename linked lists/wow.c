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

    if (temp == NULL)
    {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void deleteAtIndex(struct Node **head_ref, int index)
{
    struct Node *temp = (*head_ref);
    struct Node *prev;

    if(index == 0)
    {
        (*head_ref) = temp->next;
        free(temp);
        return;
    }

    for(int i = 0; i < index && temp != NULL; i++)
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

int serachNode(struct Node **head_ref, int key)
{
    struct Node *current = *head_ref;

    while (current != NULL)
    {
        if(current->data != key)
        {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

struct Node *reversedLL(struct Node **head_ref)
{
    struct Node *temp = *head_ref;
    struct Node *reversed = NULL;

    while(temp != NULL)
    {
        insertAtBeginning(&reversed, temp->data);
        temp = temp->next;
    }

    return reversed;
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

struct Node *joinLL(struct Node **head, struct Node **tail)
{
    struct Node *temp1 = *head;
    struct Node *temp2 = *tail;
    struct Node *temp3 = NULL;

    while(temp1 != NULL)
    {
        insertAtEnd(&temp3, temp1->data);
        temp1 = temp1->next;
    }

    while(temp2 != NULL)
    {
        insertAtEnd(&temp3, temp2->data);
        temp2 = temp2->next;
    }

    return temp3;
}

int main()
{
    struct Node *head = NULL;
    
    for(int i = 0; i < 10; i++)
    {
        insertAtBeginning(&head, i);
    }

    struct Node *rev = reversedLL(&head);

    printList(head);
    printList(rev);

    struct Node *newLL = joinLL(&head, &rev);
    printList(newLL);
    struct Node *newwLL = joinLL(&head, &newLL);
    struct Node *revv = reversedLL(&newwLL);
    printList(revv);
}