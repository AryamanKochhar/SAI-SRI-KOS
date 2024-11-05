#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

#define MAX_VERTICES 7

int adj[MAX_VERTICES][MAX_VERTICES];

int bfs(int start, int goal, int n, int *path)
{
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int parent[MAX_VERTICES] = {-1};

    visited[start] = 1;
    queue[rear++] = start;

    while (front != rear)
    {
        int curr = queue[front++];
        if (curr == goal)
        {
            int i = goal, idx = 0;
            while (i != -1)
            {
                path[idx++] = i;
                i = parent[i];
            }
            return idx;
        }

        for (int i = 0; i < n; i++)
        {
            if (adj[curr][i] && !visited[i])
            {
                visited[i] = 1;
                parent[i] = curr;
                queue[rear++] = i;
            }
        }
    }

    return -1;
}

int main()
{
    int n, start, goal;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    scanf("%d %d", &start, &goal);

    int path[MAX_VERTICES];
    int length = bfs(start, goal, n, path);

    if (length == -1)
    {
        printf("Not found\n");
    }
    else
    {
        printf("%d\n", length - 1);
        for (int i = length - 1; i >= 0; i--)
        {
            printf("%d ", path[i]);
        }
        printf("\n");
    }

    return 0;
}