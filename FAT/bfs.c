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

void addEdge(int adj[MAX][MAX], int u, int v)
{
    adj[u][v] = 1;
    adj[v][u] = 1;
}

int main()
{
    int v = 6;
    scanf("%d", &v);
    int adj[MAX][MAX] = {0};

    for (int i = 0; i < 7; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(adj, x, y);
    }

    printf("BFS starting from 0:\n");
    bfs(adj, v, 0);

    return 0;
}
