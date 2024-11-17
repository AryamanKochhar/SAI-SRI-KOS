#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Node* createNode(int v);
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
Queue* createQueue();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int isEmpty(Queue* q);
int isCyclic(Graph* graph);

int main() {
    int V, E;
    scanf("%d", &V);
    scanf("%d", &E);

    Graph* graph = createGraph(V);

    for (int i = 0; i < E; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int result = isCyclic(graph);
    printf("%d\n", result);

    return 0;
}

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}

int isEmpty(Queue* q) {
    return q->rear == -1;
}

int bfsCheckCycle(Graph* graph, int start) {
    Queue* q = createQueue();
    int* parent = (int*)malloc(graph->numVertices * sizeof(int));
    
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
    }
    
    enqueue(q, start);
    graph->visited[start] = 1;

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        
        Node* temp = graph->adjLists[currentVertex];
        
        while (temp) {
            int adjVertex = temp->vertex;

            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
                parent[adjVertex] = currentVertex;
            } else if (parent[currentVertex] != adjVertex) {
                free(parent);
                return 1;
            }

            temp = temp->next;
        }
    }

    free(parent);
    return 0;
}

int isCyclic(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            if (bfsCheckCycle(graph, i)) {
                return 1;
            }
        }
    }
    return 0;
}
