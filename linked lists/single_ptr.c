#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node* insertAtBeginning(struct Node *head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = head_ref;
    head_ref = new_node;

    return head_ref;
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

struct Node* insertAtEnd(struct Node *head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last = head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (head_ref == NULL)
    {
        head_ref = new_node;
        return head_ref;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_node;

    return head_ref;
}

struct Node* deleteNode(struct Node *head_ref, int key)
{
    struct Node *temp = head_ref;
    struct Node *prev = NULL;

    if (temp != NULL && temp->data == key)
    {
        head_ref = temp->next;
        free(temp);
        return head_ref;
    }

    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return head_ref;
    }

    prev->next = temp->next;
    free(temp);

    return head_ref;
}

struct Node* deleteAtIndex(struct Node *head_ref, int index)
{
    struct Node *temp = head_ref;
    struct Node *prev = NULL;

    if (index == 0)
    {
        head_ref = temp->next;
        free(temp);
        return head_ref;
    }

    for (int i = 0; temp != NULL && i < index; i++)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return head_ref;
    }

    prev->next = temp->next;
    free(temp);

    return head_ref;
}

int searchNode(struct Node *head_ref, int key)
{
    struct Node *current = head_ref;

    while (current != NULL)
    {
        if (current->data == key)
        {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

struct Node* reversedLL(struct Node *head_ref)
{
    struct Node *temp = head_ref;
    struct Node *reversed = NULL;

    while (temp != NULL)
    {
        reversed = insertAtBeginning(reversed, temp->data);
        temp = temp->next;
    }

    return reversed;
}

void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
    printf("\n");
}

struct Node* joinLL(struct Node *head1, struct Node *head2)
{
    struct Node *temp1 = head1;
    struct Node *temp2 = head2;
    struct Node *newList = NULL;

    while (temp1 != NULL)
    {
        newList = insertAtEnd(newList, temp1->data);
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        newList = insertAtEnd(newList, temp2->data);
        temp2 = temp2->next;
    }

    return newList;
}

struct Node* sortLL(struct Node *head_ref)
{
    struct Node *current = head_ref, *index = NULL;
    int temp;

    if (head_ref == NULL)
    {
        return head_ref;
    }

    while (current != NULL)
    {
        index = current->next;

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

    return head_ref;
}

// Uncomment if needed for future use
// struct Node* removeDuplicates(struct Node *head_ref)
// {
//     if (head_ref == NULL)
//         return head_ref;

//     struct Node *current = head_ref;
//     struct Node *next_next;

//     while (current->next != NULL)
//     {
//         if (current->data == current->next->data)
//         {
//             next_next = current->next->next;
//             free(current->next);
//             current->next = next_next;
//         }
//         else
//         {
//             current = current->next;
//         }
//     }

//     return head_ref;
// }

int main()
{
    struct Node *head = NULL;
    
    for (int i = 0; i < 10; i++)
    {
        head = insertAtBeginning(head, i);
    }

    struct Node *rev = reversedLL(head);

    printList(head);
    printList(rev);

    struct Node *newLL = joinLL(head, rev);
    printList(newLL);

    struct Node *newwLL = joinLL(head, newLL);
    struct Node *revv = reversedLL(newwLL);
    printList(revv);

    struct Node *t = head;

    int n = 5;
    while (t->next != NULL)
    {
        if (t->next->data == n)
        {
            insertAfter(t->next, 69);
        }
        t = t->next;
    }

    printList(head);

    // Uncomment if needed in the future
    // head = removeDuplicates(head);
    printList(head);

    head = insertAtBeginning(head, 69);
    printList(head);

    return 0;
}
