#include <stdio.h>

#define MAX_NODES 100  // Define maximum number of vertices

void DFS(int i, int n, int A[MAX_NODES][MAX_NODES], int visited[MAX_NODES]) {
    printf("%d ", i);
    visited[i] = 1;
    for (int j = 0; j < n; j++) {
        if (A[i][j] == 1 && !visited[j]) {
            DFS(j, n, A, visited);
        }
    }
}

void BFS(int start, int n, int A[MAX_NODES][MAX_NODES]) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    printf("%d ", start);
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int node = queue[front++];
        for (int j = 0; j < n; j++) {
            if (A[node][j] == 1 && !visited[j]) {
                printf("%d ", j);
                visited[j] = 1;
                queue[rear++] = j;
            }
        }
    }
}

int main() {
    int n, e;
    int A[MAX_NODES][MAX_NODES] = {0};  // Initialize adjacency matrix
    int visited[MAX_NODES] = {0};       // Initialize visited array

    // Input the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &e);

    // Input edges and populate adjacency matrix
    printf("Enter each edge in the format 'u v' where u and v are vertices:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        A[u][v] = 1;
        A[v][u] = 1;  // For undirected graph
    }

    // Display adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    // Perform DFS and BFS starting from vertex 0
    printf("\nDFS Traversal starting from vertex 0:\n");
    DFS(0, n, A, visited);

    printf("\n\nBFS Traversal starting from vertex 0:\n");
    BFS(0, n, A);

    return 0;
}
