#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Deque
{
    int items[MAX];
    int front;
    int rear;
};

void initDeque(struct Deque *dq)
{
    dq->front = -1;
    dq->rear = -1;
}

int isFull(struct Deque *dq)
{
    return (dq->front == 0 && dq->rear == MAX - 1) || (dq->front == dq->rear + 1);
}

int isEmpty(struct Deque *dq)
{
    return dq->front == -1;
}

void insertFront(struct Deque *dq, int value)
{
    if (isFull(dq))
    {
        printf("Deque is full\n");
        return;
    }
    if (dq->front == -1)
    {
        dq->front = dq->rear = 0;
    }
    else if (dq->front == 0)
    {
        dq->front = MAX - 1;
    }
    else
    {
        dq->front--;
    }
    dq->items[dq->front] = value;
}

void insertRear(struct Deque *dq, int value)
{
    if (isFull(dq))
    {
        printf("Deque is full\n");
        return;
    }
    if (dq->front == -1)
    {
        dq->front = dq->rear = 0;
    }
    else if (dq->rear == MAX - 1)
    {
        dq->rear = 0;
    }
    else
    {
        dq->rear++;
    }
    dq->items[dq->rear] = value;
}

int deleteFront(struct Deque *dq)
{
    if (isEmpty(dq))
    {
        printf("Deque is empty\n");
        return -1;
    }
    int value = dq->items[dq->front];
    if (dq->front == dq->rear)
    {
        dq->front = dq->rear = -1;
    }
    else if (dq->front == MAX - 1)
    {
        dq->front = 0;
    }
    else
    {
        dq->front++;
    }
    return value;
}

int deleteRear(struct Deque *dq)
{
    if (isEmpty(dq))
    {
        printf("Deque is empty\n");
        return -1;
    }
    int value = dq->items[dq->rear];
    if (dq->front == dq->rear)
    {
        dq->front = dq->rear = -1;
    }
    else if (dq->rear == 0)
    {
        dq->rear = MAX - 1;
    }
    else
    {
        dq->rear--;
    }
    return value;
}

void printDeque(struct Deque *dq)
{
    if (isEmpty(dq))
    {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements: ");
    if (dq->front <= dq->rear)
    {
        for (int i = dq->front; i <= dq->rear; i++)
        {
            printf("%d ", dq->items[i]);
        }
    }
    else
    {
        for (int i = dq->front; i < MAX; i++)
        {
            printf("%d ", dq->items[i]);
        }
        for (int i = 0; i <= dq->rear; i++)
        {
            printf("%d ", dq->items[i]);
        }
    }
    printf("\n");
}

int main()
{
    struct Deque dq;
    initDeque(&dq);

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertRear(&dq, 30);

    printDeque(&dq);

    printf("Deleted from front: %d\n", deleteFront(&dq));
    printf("Deleted from rear: %d\n", deleteRear(&dq));

    printDeque(&dq);

    return 0;
}
