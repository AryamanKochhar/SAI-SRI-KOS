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

void kthSmallestUtil(Node* root, int k, int *count, int *result)
{
    if(root == NULL || *result != -1)
        return;
    
    kthSmallestUtil(root->left, k, count, result);

    (*count)++;
    if(*count == k)
    {
        *result = root->data;
        return;
    }

    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(Node* root, int k)
{
    int count = 0;
    int result = -1;
    kthSmallestUtil(root, k, &count, &result);

    return result;
}

void kthLargestUtil(Node* root, int k, int *count, int *result)
{
    if(root == NULL || *result != -1)
        return;
    
    kthLargestUtil(root->right, k, count, result);

    (*count)++;
    if(*count == k)
    {
        *result = root->data;
        return;
    }

    kthLargestUtil(root->left, k, count, result);
}

int kthLargest(Node* root, int k)
{
    int count = 0;
    int result = -1;
    kthLargestUtil(root, k, &count, &result);

    return result;
}

int main()
{
    Node* root = NULL;

    int arr[5] = {2,5,1,6,4};
    root = insertLevelOrder(arr, 5, 0);
    
    printf("%d", kthSmallest(root, 1));
    printf("\n");
    printf("%d", kthLargest(root, 1));

}

