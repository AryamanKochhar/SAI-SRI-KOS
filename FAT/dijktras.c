#include <stdio.h>
#define INFINITY 9999
#define MAX 10

void dijkstra(int graph[MAX][MAX], int n, int start)
{
    int cost[MAX][MAX], pred[MAX], visited[MAX], distance[MAX];
    int count, mindistance, nextnode;

    // Create the cost matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == 0 && i != j)
            {
                cost[i][j] = INFINITY;
            }
            else
            {
                cost[i][j] = graph[i][j];
            }
        }
    }

    // Initialize arrays
    for (int i = 0; i < n; i++)
    {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0; // Distance to itself is 0
    visited[start] = 1;  // Mark the start node as visited
    count = 1;

    // Dijkstra's Algorithm
    while (count < n)
    {
        mindistance = INFINITY;

        // Find the next node with the smallest distance
        for (int i = 0; i < n; i++)
        {
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        // Mark the node as visited
        visited[nextnode] = 1;

        // Update distances of the neighbors
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && cost[nextnode][i] != INFINITY)
            {
                if (distance[nextnode] + cost[nextnode][i] < distance[i])
                {
                    distance[i] = distance[nextnode] + cost[nextnode][i];
                    pred[i] = nextnode;
                }
            }
        }
        count++;
    }

    // Print results
    for (int i = 0; i < n; i++)
    {
        if (i != start)
        {
            printf("\nDistance from node %d to %d: %d", start, i, distance[i]);
            printf("\nPath: %d", i);

            int j = i;
            while (j != start)
            {
                j = pred[j];
                printf(" <- %d", j);
            }
        }
    }
    printf("\n");

}

int main()
{
    int Graph[MAX][MAX], n, start;

    n = 7;

    // Example adjacency matrix
    int GraphExample[MAX][MAX] = {
        {0, 0, 1, 2, 0, 0, 0},
        {0, 0, 2, 0, 0, 3, 0},
        {1, 2, 0, 1, 3, 0, 0},
        {2, 0, 1, 0, 0, 0, 1},
        {0, 0, 3, 0, 0, 2, 0},
        {0, 3, 0, 0, 2, 0, 1},
        {0, 0, 0, 1, 0, 1, 0}};

    // Copy example graph to the input graph
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Graph[i][j] = GraphExample[i][j];
        }
    }

    start = 0; // Starting node
    dijkstra(Graph, n, start);

    return 0;
}
