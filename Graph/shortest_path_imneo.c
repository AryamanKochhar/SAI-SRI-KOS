#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

#define MAX_VERTICES 7

// Adjacency matrix representation of the graph
int adj[MAX_VERTICES][MAX_VERTICES];

// Function to perform BFS and find the shortest path
int bfs(int start, int goal, int n, int* path) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int parent[MAX_VERTICES] = {-1};

    visited[start] = 1;
    queue[rear++] = start;

    while (front != rear) {
        int curr = queue[front++];
        if (curr == goal) {
            // Reconstruct the path
            int i = goal, idx = 0;
            while (i != -1) {
                path[idx++] = i;
                i = parent[i];
            }
            return idx;
        }

        for (int i = 0; i < n; i++) {
            if (adj[curr][i] && !visited[i]) {
                visited[i] = 1;
                parent[i] = curr;
                queue[rear++] = i;
            }
        }
    }

    return -1; // Path not found
}

int main() {
    int n, start, goal;
    scanf("%d", &n);

    // Read the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    // Read the source and goal vertices
    scanf("%d %d", &start, &goal);

    // Perform BFS and find the shortest path
    int path[MAX_VERTICES];
    int length = bfs(start, goal, n, path);

    if (length == -1) {
        printf("Not found\n");
    } else {
        printf("%d\n", length - 1);
        for (int i = length - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    }

    return 0;
}