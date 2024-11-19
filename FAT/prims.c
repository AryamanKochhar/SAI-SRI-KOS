#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int minKey(bool mstSet[], int key[], int v)
{
    int min = INT_MAX, min_index;

    for (int i = 0; i < v; i++)
    {
        if (!mstSet[i] && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

// Function implementing Prim's Algorithm
int prims(int **graph, int v)
{
    int *parent = (int *)malloc(v * sizeof(int));    
    int *key = (int *)malloc(v * sizeof(int));    
    bool *mstSet = (bool *)malloc(v * sizeof(bool)); 

    for (int i = 0; i < v; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;     
    parent[0] = -1; 

    // Construct MST with v-1 edges
    for (int count = 0; count < v - 1; count++)
    {
        int u = minKey(mstSet, key, v); 
        mstSet[u] = true;               

        for (int j = 0; j < v; j++)
        {
            if (graph[u][j] && !mstSet[j] && graph[u][j] < key[j])
            {
                parent[j] = u;
                key[j] = graph[u][j];
            }
        }
    }

    int totalCost = 0;
    for (int i = 1; i < v; i++)
    {
        totalCost += graph[i][parent[i]];
    }

    free(parent);
    free(key);
    free(mstSet);

    return totalCost;
}

int main()
{
    int v;

    // Input number of vertices
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &v);

    // Dynamically allocate memory for the adjacency matrix
    int **graph = (int **)malloc(v * sizeof(int *));
    for (int i = 0; i < v; i++)
    {
        graph[i] = (int *)malloc(v * sizeof(int));
    }

    // Input the adjacency matrix
    printf("Enter the adjacency matrix of the graph (use 0 for no edge):\n");
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    // Call Prim's algorithm
    int totalCost = prims(graph, v);

    // Output the result
    printf("The total cost of the Minimum Spanning Tree is: %d\n", totalCost);

    // Free the adjacency matrix
    for (int i = 0; i < v; i++)
    {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
