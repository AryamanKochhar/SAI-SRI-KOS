#include <stdio.h>
#define MAX 5

typedef struct a
{
    int items[MAX];
    int front;
    int rear;
}circularQueue;

void innit(circularQueue *cq)
{
    cq->front = -1;
    cq->rear = -1;
}
