#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Adjacency list representation of the graph
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAX_VERTICES]; // Array of adjacency lists
bool visited[MAX_VERTICES]; // Visited array

// Function to create a new node in the adjacency list
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the undirected graph
void addEdge(int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;
    
    newNode = createNode(u);
    newNode->next = adj[v];
    adj[v] = newNode;
}

// Utility function to perform DFS and check for cycles
bool isCyclicUtil(int v, int parent) {
    visited[v] = true;
    
    Node* temp = adj[v];
    while (temp != NULL) {
        int neighbor = temp->vertex;
        
        // If the adjacent node is not visited, visit it recursively
        if (!visited[neighbor]) {
            if (isCyclicUtil(neighbor, v))
                return true;
        }
        // If an adjacent node is visited and is not the parent of the current node, there’s a cycle
        else if (neighbor != parent) {
            return true;
        }
        temp = temp->next;
    }
    
    return false;
}

// Function to check if the graph contains a cycle
bool isCyclic(int V) {
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    // Perform DFS for each unvisited node
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i, -1))
                return true;
        }
    }
    
    return false;
}

int main() {
    int V, E;
    scanf("%d", &V); // Number of vertices
    scanf("%d", &E); // Number of edges
    
    // Initialize adjacency list for each vertex
    for (int i = 0; i < V; i++)
        adj[i] = NULL;
    
    // Read edges and add them to the graph
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    
    // Check if the graph contains a cycle
    if (isCyclic(V))
        printf("1\n");
    else
        printf("0\n");
    
    return 0;
}
