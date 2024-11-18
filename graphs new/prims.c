#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int minKey(bool mstSet[], int key[], int v)
{
    int min = INT_MAX, min_index;

    for(int i = 0; i < v; i++)
    {
        if(mstSet[i] == false && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

int prims(int **graph, int v)
{
    int *parent = (int*)malloc(v*sizeof(int));
    int *key = (int*)malloc(v*sizeof(int));
    bool *mstSet = (bool*)malloc(v*sizeof(bool));

    for(int i = 0; i < v; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for(int i = 0; i < v; i++)
    {
        int u = minKey(key, mstSet, v);
        mstSet[u] = true;
        for(int j = 0; j < v; j++)
        {
            if(graph[u][j] && mstSet[j] == false && graph[u][j] < key[j])
            {
                parent[j] = u;
                key[j] = graph[u][j];
            }
        }
    }

    int totalCost = 0;

    for(int i = 0; i < v; i++)
    {
        totalCost += graph[i][parent[i]];
    }

    return totalCost
}

