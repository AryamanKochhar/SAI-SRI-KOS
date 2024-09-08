#include <stdio.h>

class ArrayQueue {
public:
    int* a;        // Dynamic array for queue elements
    int maxSize;    // Maximum size of the queue
    int front;      // Front index of the queue
    int rear;       // Rear index of the queue
    
    // Constructor
    ArrayQueue(int s = 1000) {
        maxSize = s;            // Initialize maxSize member variable
        front = -1;             // Initialize front
        rear = -1;              // Initialize rear
        a = new int[maxSize];   // Allocate memory for the queue
    }
    
    // Destructor to free memory
    ~ArrayQueue() {
        delete[] a;
    }

    // Push an element into the queue
    void push(int x) {
        if (rear >= maxSize - 1) {   // Check if the queue is full
            printf("Queue is full\n");
            return;
        }
        if (front == -1) {           // If pushing the first element, set front to 0
            front = 0;
        }
        a[++rear] = x;               // Increment rear and add element
    }
    
    // Pop an element from the queue
    int pop() {
        if (isEmpty()) {             // Check if the queue is empty
            printf("Queue is empty\n");
            return -1;               // Return an error value if empty
        }
        int result = a[front];
        if (front == rear) {         // If only one element is left, reset the queue
            front = rear = -1;
        } else {
            front++;                 // Otherwise, move the front forward
        }
        return result;
    }
    
    // Peek at the front element of the queue
    int peek() {
        if (isEmpty()) {             // Check if the queue is empty
            printf("Queue is empty\n");
            return -1;               // Return an error value if empty
        }
        return a[front];             // Return the front element
    }
    
    // Check if the queue is empty
    bool isEmpty() {
        return front == -1;          // Queue is empty if front is -1
    }
    
    // Check if the queue is full
    bool isFull() {
        return rear >= maxSize - 1;  // Queue is full if rear reaches maxSize-1
    }
};
