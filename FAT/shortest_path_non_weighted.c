#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            int idx = 0, i = goal;
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

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("Enter the start and goal nodes: ");
    scanf("%d %d", &start, &goal);

    if (start < 0 || start >= n || goal < 0 || goal >= n)
    {
        printf("Invalid start or goal node.\n");
        return 1;
    }

    if (start == goal)
    {
        printf("0\n%d\n", start);
        return 0;
    }

    int path[MAX_VERTICES];
    int length = bfs(start, goal, n, path);

    if (length == -1)
    {
        printf("Path not found\n");
    }
    else
    {
        printf("Shortest path length: %d\n", length - 1);
        printf("Path: ");
        for (int i = length - 1; i >= 0; i--)
        {
            printf("%d ", path[i]);
        }
        printf("\n");
    }

    return 0;
}
