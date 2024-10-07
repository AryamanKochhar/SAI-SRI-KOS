#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data)
{
    Node* temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Node* insertLevelOrder(int arr[], int n, int i)
{
    if(i >= n)
        return NULL;
    
    Node *root = createNode(arr[i]);
    root->left = insertLevelOrder(arr, n, 2*i+1);
    root->right = insertLevelOrder(arr, n, 2*i+2);

    return root;
}

