#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

node *newNode(int data)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node *insertLevelOrder(int arr[], int n, int i)
{
    node *root = NULL;
    if (i < n)
    {
        root = newNode(arr[i]);
        root->left = insertLevelOrder(arr, n, 2 * i + 1);
        root->right = insertLevelOrder(arr, n, 2 * i + 2);
    }

    return root;
}

void levelOrderTraversal(node* root)
{
    if(root == NULL) return;

    node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while(front < rear)
    {
        node* current = queue[front++];

        printf("%d ", current->data);

        if(current->left != NULL)
        {
            queue[rear++] = current->left;
        } 

        if(current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int arr[10];

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    node* root = insertLevelOrder(arr, n, 0);

    levelOrderTraversal(root);
    printf("\n");

    return 0;
}