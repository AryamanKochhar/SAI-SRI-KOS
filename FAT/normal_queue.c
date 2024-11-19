#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

int isFull()
{
    return (rear == MAX-1);
}

int isEmpty()
{
    return (front == -1 || front > rear);
}

void enqueue(int value)
{
    if (isFull)
    {
        printf("Queue is full");
        return;
    }
    else
    {
        if(front == -1)
        {
            front = 0;
        }
        rear++;
        queue[rear] = value;
        printf("Added %d", value);
    }
}

int dequeue()
{
    int element;
    if(isEmpty)
    {
        printf("Queue is empty");
        return -1;
    }
    else
    {
        element = queue[front];
        if(front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front++;
        }

        return element;
    }
}

int peek()
{
    if(isEmpty())
    {
        printf("Queue is empty");
        return -1;
    }
    else
    {
        return queue[front];
    }
}

void display()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        printf("Queue elements are: ");
        for (int i = front; i <= rear; i++)
        {
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}