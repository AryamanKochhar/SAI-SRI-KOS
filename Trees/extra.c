#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For INT_MIN and INT_MAX

typedef struct Node
{
    int data;
    struct Node *right;
    struct Node *left;
} Node;

// Function to create a new node
Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

// Level order insertion
Node *Insert(Node *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }

    Node *queue[100] = {NULL};
    int rear = 0, front = 0;
    queue[rear++] = root;

    while (front < rear)
    {
        Node *temp = queue[front++];

        if (temp->left == NULL)
        {
            temp->left = createNode(key);
            break;
        }
        else
        {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL)
        {
            temp->right = createNode(key);
            break;
        }
        else
        {
            queue[rear++] = temp->right;
        }
    }

    return root;
}

// Inorder Traversal
void inOrder(Node *root)
{
    if (root == NULL)
        return;
    
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

// Preorder Traversal
void preOrder(Node *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

// Postorder Traversal
void postOrder(Node *root)
{
    if (root == NULL)
        return;

    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}

// Level-order Traversal
void levelOrder(Node *root)
{
    if (root == NULL)
        return;

    Node *queue[100] = {NULL};
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear)
    {
        Node *temp = queue[front++];

        printf("%d ", temp->data);
        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }
}

// Search an element using DFS
int searchDFS(Node* root, int value)
{
    if(root == NULL)
        return 0;
    
    if(root->data == value)
        return 1;

    int left_res = searchDFS(root->left, value);
    int right_res = searchDFS(root->right, value);

    return left_res || right_res;
}

// Find the height of the tree (or height of a particular node)
int findHeight(Node *root)
{
    if (root == NULL)
        return -1;  // Height of an empty tree is -1
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Find the depth of a particular node
int findDepth(Node *root, int value, int depth)
{
    if (root == NULL)
        return -1;

    if (root->data == value)
        return depth;

    int leftDepth = findDepth(root->left, value, depth + 1);
    if (leftDepth != -1)
        return leftDepth;

    return findDepth(root->right, value, depth + 1);
}

// Find the minimum element in the tree
int findMin(Node *root)
{
    if (root == NULL)
        return INT_MAX;  // Use INT_MAX for empty node

    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);

    return (root->data < leftMin ? (root->data < rightMin ? root->data : rightMin) : (leftMin < rightMin ? leftMin : rightMin));
}

// Find the maximum element in the tree
int findMax(Node *root)
{
    if (root == NULL)
        return INT_MIN;  // Use INT_MIN for empty node

    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);

    return (root->data > leftMax ? (root->data > rightMax ? root->data : rightMax) : (leftMax > rightMax ? leftMax : rightMax));
}

// Store elements in the array using InOrder traversal for kth element finding
void storeInOrder(Node *root, int *arr, int *index)
{
    if (root == NULL)
        return;

    storeInOrder(root->left, arr, index);
    arr[(*index)++] = root->data;
    storeInOrder(root->right, arr, index);
}

// Find the kth minimum element
int findKthMin(Node *root, int k)
{
    int arr[100] = {0};  // Array to store the elements
    int index = 0;

    storeInOrder(root, arr, &index);

    if (k <= index)
        return arr[k-1];  // k-1 because array is 0-indexed

    return -1;  // k is out of bounds
}

// Find the kth maximum element
int findKthMax(Node *root, int k)
{
    int arr[100] = {0};  // Array to store the elements
    int index = 0;

    storeInOrder(root, arr, &index);

    if (k <= index)
        return arr[index - k];  // index - k because array is 0-indexed

    return -1;  // k is out of bounds
}

// Main function
int main()
{
    Node* root = NULL;

    for(int i = 0; i < 10; i++)
    {
        root = Insert(root, i);
    }

    printf("Inorder Traversal: ");
    inOrder(root);
    printf("\n");

    printf("Level Order Traversal: ");
    levelOrder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postOrder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preOrder(root);
    printf("\n");

    printf("Search for 11: %d\n", searchDFS(root, 11));

    printf("Tree Height: %d\n", findHeight(root));

    printf("Depth of node with value 4: %d\n", findDepth(root, 4, 0));

    printf("Minimum element: %d\n", findMin(root));

    printf("Maximum element: %d\n", findMax(root));

    int k = 3;
    printf("3rd Minimum element: %d\n", findKthMin(root, k));
    printf("3rd Maximum element: %d\n", findKthMax(root, k));

    return 0;
}
