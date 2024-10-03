#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
} L;

L *newNode(int data)
{
    L *temp = (L *)malloc(sizeof(L));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void traverse(L *head)
{
    L *curr = head;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
}

L *insert(L *head, int pos, int data)
{
    if (pos < 1)
    {
        printf("INVALID\n");
        return head;
    }
    if (pos == 1)
    {
        L *temp = newNode(data);
        temp->next = head;
        return temp;
    }
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
    L *temp = newNode(data);
    temp->next = current->next;
    current->next = temp;
    return head;
}

L *deleten(L *head, int pos)
{
    if (head == NULL || pos < 1)
    {
        return head;
    }
    if (pos == 1)
    {
        L *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    L *curr = head;
    for (int i = 1; i < pos - 1 && curr != NULL; i++)
    {
        curr = curr->next;
    }
    if (curr == NULL || curr->next == NULL)
    {
        return head;
    }
    L *temp = curr->next;
    curr->next = curr->next->next;
    free(temp);
    return head;
}

void bubbleSort(L *head)
{
    int swapped;
    L *curr;
    L *nextNode;
    if (head == NULL)
        return;
    do
    {
        swapped = 0;
        curr = head;
        while (curr->next != NULL)
        {
            if (curr->data >= curr->next->data)
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

int main()
{
    L *head = NULL;
    int a;
    scanf("%d", &a);
    for (int i = 1; i <= a; i++)
    {
        int element;
        scanf("%d", &element);
        head = insert(head, i, element);
    }
    head = deleten(head, a);
    bubbleSort(head);
    traverse(head);

    return 0;
}