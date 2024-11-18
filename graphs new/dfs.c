#include <stdio.h>
#include <stdlib.h>

void dfs(int **adj, int *visited, int s, int n)
{
    printf("%d ", s);
    visited[s] = 1;

    for(int i = 0; i < n; i++)
    {
        if(adj[s][i] == 1 && !visited[i])
        {
            dfs(adj, visited, i, n);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int** adj = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++)
    {
        adj[i] = (int*)malloc(n * sizeof(int));
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    int* visited = (int*)calloc(n,sizeof(int));
    
    dfs(adj, visited, 4, n);
}