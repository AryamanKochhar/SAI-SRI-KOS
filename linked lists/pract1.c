#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *createNode(int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;

    return new_node;
}

struct Node *insertAtBeginning(struct Node* head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = head_ref;
    head_ref = new_node;

    return head_ref;
}

void insertAfter(struct Node *prev_node, int new_data)
{
    if(prev_node == NULL)
    {
        printf("prev_node cannot be NULL");
    }

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

struct Node *insertAtEnd(struct Node *head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if(head_ref == NULL)
    {
        head_ref = new_node;
        return head_ref;
    }

    while(last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_node;

    return head_ref;
}

struct Node *deleteNode(struct Node *head_ref, int key)
{
    struct Node *prev = NULL; 
    struct Node *temp = head_ref;

    if(temp != NULL && temp->data == key)
    {
        head_ref = temp->next;
        free(temp);
        return head_ref;
    }

    while(temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return head_ref;
    }

    prev->next = temp->next;
    free(temp);

    return head_ref;
}

struct Node *deleteNodeAtIndex(struct Node *head_ref, int index)
{
    struct Node *prev = NULL; 
    struct Node *temp = head_ref;

    if(index == 0)
    {
        head_ref = temp->next;
        free(temp);
        return head_ref;
    }

    for(int i = 0; i < index && temp != NULL; i++)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return head_ref;
    }

    prev->next = temp->next;
    free(temp);

    return head_ref;
}

struct Node *sortLL(struct Node *head_ref)
{
    if(head_ref == NULL)
    {
        return head_ref;
    }

    struct Node *current = (struct Node *)malloc(sizeof(struct Node));
    struct Node *index = NULL;

    while(current != NULL)
    {
        index = current->next;

        while(index != NULL)
        {
            if(current->data > index->data)
            {
                int temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current->next;
    }   

    return head_ref;
}

void printLL(struct Node *head_ref)
{
    struct Node *temp = head_ref;

    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

struct Node *reverseLL(struct Node *head_ref)
{
    struct Node *temp = head_ref;
    struct Node *rev = NULL;

    while(temp != NULL)
    {
        rev = insertAtBeginning(rev, temp->data);
        temp = temp->next;
    }

    return rev;
}

struct Node *joinLL(struct Node *list1, struct Node *list2)
{
    struct Node *temp3 = NULL;

    while(list1 != NULL)
    {
        temp3 = insertAtEnd(temp3, list1->data);
        list1 = list1->next;
    }

    while(list2 != NULL)
    {
        temp3 = insertAtEnd(temp3, list2->data);
        list2 = list2->next;
    }

    return temp3;
}

int main()
{
    struct Node *head = NULL;

    for(int i = 0; i < 10; i++)
    {
        head = insertAtEnd(head, i);
    }

    printLL(head);

    struct Node *rev = reverseLL(head);
    printLL(rev);

    struct Node *joined = joinLL(head, rev);
    printLL(joined);
}