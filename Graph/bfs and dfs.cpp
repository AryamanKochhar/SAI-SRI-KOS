#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of nodes
#define MAX_NODES 100

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the graph (adjacency list)
void addEdge(Node* adj[], int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = adj[src];
    adj[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

// BFS Function
void bfs(int startNode, Node* adj[], int visited[], int V, int result[], int* resultSize) {
    int queue[MAX_NODES], front = -1, rear = -1;

    visited[startNode] = 1;
    queue[++rear] = startNode;

    while (front != rear) {
        front++;
        int node = queue[front];
        result[(*resultSize)++] = node;

        Node* temp = adj[node];
        while (temp) {
            int neighbor = temp->vertex;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[++rear] = neighbor;
            }
            temp = temp->next;
        }
    }
}

// DFS Function
void dfs(int node, Node* adj[], int visited[], int result[], int* resultSize) {
    visited[node] = 1;
    result[(*resultSize)++] = node;

    Node* temp = adj[node];
    while (temp) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, result, resultSize);
        }
        temp = temp->next;
    }
}

int main() {
    int V = 10;
    
    // Create adjacency list for the graph
    Node* adj[MAX_NODES] = {0}; // Initialize all to NULL
    
    // Adding edges to the graph (Undirected)
    for(int i = 0; i < 13; i++)
    {   
        int n1,n2;
        scanf("%d", &n1);
        scanf("%d", &n2);
        addEdge(adj, n1, n2);
    }

    // BFS and DFS result arrays
    int bfsResult[MAX_NODES] = {0};
    int dfsResult[MAX_NODES] = {0};

    int bfsSize = 0, dfsSize = 0;

    // Visited arrays
    int visited[MAX_NODES] = {0}; // For BFS
    int visitedDFS[MAX_NODES] = {0}; // For DFS

    // Perform BFS from node 0
    bfs(1, adj, visited, V, bfsResult, &bfsSize);

    // Perform DFS from node 0
    dfs(1, adj, visitedDFS, dfsResult, &dfsSize);

    // Print BFS result
    printf("The BFS traversal of the graph is: ");
    for (int i = 0; i < bfsSize; i++) {
        printf("%d ", bfsResult[i]);
    }
    printf("\n");

    // Print DFS result
    printf("The DFS traversal of the graph is: ");
    for (int i = 0; i < dfsSize; i++) {
        printf("%d ", dfsResult[i]);
    }
    printf("\n");

    return 0;
}
