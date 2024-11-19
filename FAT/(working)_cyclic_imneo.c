#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of vertices
#define MAX_VERTICES 100

// Adjacency list representation of the graph
int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int parent[MAX_VERTICES];

// Function to add an edge to the graph
void addEdge(int u, int v)
{
    adj[u][v] = 1;
    adj[v][u] = 1;
}

// Depth-First Search (DFS) to detect a cycle
int dfs(int start, int v, int n)
{
    visited[v] = 1;

    for (int i = 0; i < n; i++)
    {
        if (adj[v][i])
        {
            if (!visited[i])
            {
                parent[i] = v;
                if (dfs(v, i, n))
                    return 1;
            }
            else if (i != parent[v])
            {
                return 1; // Cycle found
            }
        }
    }

    return 0;
}

int main()
{
    int V, E;
    scanf("%d %d", &V, &E);

    // Initialize the graph
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            adj[i][j] = 0;
        }
        visited[i] = 0;
        parent[i] = -1;
    }

    // Add edges to the graph
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // Perform DFS to detect a cycle
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, i, V))
            {
                printf("1\n");
                return 0;
            }
        }
    }

    printf("0\n");
    return 0;
}