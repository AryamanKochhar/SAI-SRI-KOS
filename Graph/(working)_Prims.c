#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int minKey(int key[], bool mstSet[], int v)
{
    int min = INT_MAX, min_index;

    for (int i = 0; i < v; i++)
    {
        if (mstSet[i] == false && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

int findMinimimumCost(int **graph, int v)
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

    for (int count = 0; count < v; count++)
    {
        int u = minKey(key, mstSet, v);
        mstSet[u] = true;

        for (int i = 0; i < v; i++)
        {
            if (graph[u][i] && mstSet[i] == false && graph[u][i] < key[i])
            {
                parent[i] = u;
                key[i] = graph[u][i];
            }
        }
    }

    int totalCost = 0;

    for (int i = 1; i < v; i++)
    {
        totalCost += graph[i][parent[i]];
    }

    return totalCost;
}

int main()
{
    int v, e;
    scanf("%d %d", &v, &e);
    int **graph = (int **)malloc(v * sizeof(int *));
    for (int i = 0; i < v; i++)
    {
        graph[i] = (int *)calloc(v, sizeof(int));
    }

    for (int i = 0; i < e; i++)
    {
        int src, dest, cost;
        scanf("%d %d %d", &src, &dest, &cost);
        graph[src][dest] = cost;
        graph[dest][src] = cost;
    }

    int result = findMinimimumCost(graph, v);
    printf("%d\n", result);

    return 0;
}