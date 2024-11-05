#include <stdio.h>
#include <stdlib.h>

void DFS(int i, int n, int** A, int* visited) {
    printf("%d ", i);
    visited[i] = 1;
    for (int j = 0; j < n; j++) {
        if (A[i][j] == 1 && !visited[j]) {
            DFS(j, n, A, visited);
        }
    }
}

int main() {
    int n = 7;
    
    // Dynamically allocate the adjacency matrix A
    int** A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        A[i] = (int*)malloc(n * sizeof(int));
    }

    // Define the adjacency matrix
    int tempA[7][7] = {
        {0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0}, 
        {1, 1, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}
    };

    // Copy the values from tempA to the dynamically allocated A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = tempA[i][j];
        }
    }

    // Dynamically allocate the visited array
    int* visited = (int*)calloc(n, sizeof(int));

    // Perform DFS starting from node 4
    DFS(4, n, A, visited);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(visited);

    return 0;
}
