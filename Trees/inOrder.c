#include <stdio.h>
#include <stdlib.h>

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
    if (i >= n)
        return NULL;

    node *root = newNode(arr[i]);
    root->left = insertLevelOrder(arr, n, 2 * i + 1);
    root->right = insertLevelOrder(arr, n, 2 * i + 2);
    return root;
}

void inorderTraversal(node *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main()
{
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int arr[100];
    printf("Enter %d integers for the tree nodes:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    node *root = insertLevelOrder(arr, n, 0);
    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    free(root);
    return 0;
}
