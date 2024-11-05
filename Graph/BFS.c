#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 7

// Queue structure for BFS
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear < MAX_VERTICES - 1) {
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    if (q->front <= q->rear) {
        return q->items[q->front++];
    }
    return -1;
}

bool isEmpty(Queue* q) {
    return q->front > q->rear;
}

int main()
{
    Queue q;
    q.size = 400;
    initQueue(&q);

    int node;
    int i = 0;
    int v = 1;
    scanf("%d", &v);
    
    int visited[v] = {0};

    int a[v][v]
}