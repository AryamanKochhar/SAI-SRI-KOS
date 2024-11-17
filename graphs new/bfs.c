#include <stdio.h>
#include <stdbool.h>
#define MAX 100

void bfs(int adj[MAX][MAX], int n, int s)
{
    int q[MAX], front = 0, rear = 0;
    q[rear++] = s;
    bool visited[MAX] = {false};
    visited[s] = true;

    while(front < rear)
    {
        int curr = q[front++];
        printf("%d", curr);

        for(int i = 0; i < n; i++)
        {
            if(adj[curr][i] == 1 && !visited[i])
            {
                visited[i] = true;
                q[rear++] = i;
            }
        }
    }
}

void adjEdge(int adj[MAX][MAX], int u, int v)
{
    adj[u][v] = 1;
    adj[v][u] = 1;
}
