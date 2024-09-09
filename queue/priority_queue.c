#include <stdio.h>

#define MAX_SIZE 10

int queue[MAX_SIZE];
int front = 0;
int rear = 0;

// Priority queue array
int priorityQueue[MAX_SIZE];
int priorityRear = 0;

void enqueue(int value) {
    if (rear == MAX_SIZE) {
        printf("Queue is full!\n");
        return;
    }
    queue[rear] = value;
    rear++;
}

void dequeue() {
    if (front == rear) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Dequeued: %d\n", queue[front]);
    front++;
}

void display() {
    if (front == rear) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i < rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

// Priority enqueue function
void priorityEnqueue(int value, int priority) {
    if (priorityRear == MAX_SIZE) {
        printf("Priority queue is full!\n");
        return;
    }
    int i;
    for (i = priorityRear - 1; i >= 0 && priority > priorityQueue[i]; i--) {
        priorityQueue[i + 1] = priorityQueue[i];
    }
    priorityQueue[i + 1] = value;
    priorityRear++;
}

// Priority dequeue function
void priorityDequeue() {
    if (priorityRear == 0) {
        printf("Priority queue is empty!\n");
        return;
    }
    printf("Priority dequeued: %d\n", priorityQueue[0]);
    for (int i = 0; i < priorityRear - 1; i++) {
        priorityQueue[i] = priorityQueue[i + 1];
    }
    priorityRear--;
}

// Priority display function
void priorityDisplay() {
    if (priorityRear == 0) {
        printf("Priority queue is empty!\n");
        return;
    }
    printf("Priority queue: ");
    for (int i = 0; i < priorityRear; i++) {
        printf("%d ", priorityQueue[i]);
    }
    printf("\n");
}

int main() {
    enqueue(1);
    enqueue(2);
    enqueue(3);
    display();  // prints: Queue: 1 2 3
    dequeue();  // prints: Dequeued: 1
    display();  // prints: Queue: 2 3

    priorityEnqueue(1, 1);
    priorityEnqueue(2, 3);
    priorityEnqueue(3, 2);
    priorityDisplay();  // prints: Priority queue: 2 3 1
    priorityDequeue();  // prints: Priority dequeued: 2
    priorityDisplay();  // prints: Priority queue: 3 1

   return 0;
}