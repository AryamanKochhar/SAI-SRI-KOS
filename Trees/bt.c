#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int d)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = d;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the binary tree
struct Node *insert(struct Node *root, int key)
{
    if (root == NULL)
        return createNode(key);

    // Create a queue for level order traversal
    struct Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear)
    {
        struct Node *temp = queue[front++];

        // If left child is empty, insert the new node here
        if (temp->left == NULL)
        {
            temp->left = createNode(key);
            break;
        }
        else
        {
            queue[rear++] = temp->left;
        }

        // If right child is empty, insert the new node here
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

// In-order DFS: Left, Root, Right
void inOrderDFS(struct Node *node)
{
    if (node == NULL)
        return;
    inOrderDFS(node->left);
    printf("%d ", node->data);
    inOrderDFS(node->right);
}

// Pre-order DFS: Root, Left, Right
void preOrderDFS(struct Node *node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preOrderDFS(node->left);
    preOrderDFS(node->right);
}

// Post-order DFS: Left, Right, Root
void postOrderDFS(struct Node *node)
{
    if (node == NULL)
        return;
    postOrderDFS(node->left);
    postOrderDFS(node->right);
    printf("%d ", node->data);
}

// BFS: Level order traversal
void BFS(struct Node *root)
{
    if (root == NULL)
        return;
    struct Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear)
    {
        struct Node *node = queue[front++];
        printf("%d ", node->data);
        if (node->left)
            queue[rear++] = node->left;
        if (node->right)
            queue[rear++] = node->right;
    }
}

// Function to search for a value in the binary tree using DFS
int searchDFS(struct Node *root, int value)
{
    if (root == NULL)
        return 0;

    if (root->data == value)
        return 1;

    int left_res = searchDFS(root->left, value);
    int right_res = searchDFS(root->right, value);
    return left_res || right_res;
}

// Function to delete a node from the binary tree
struct Node *deleteNode(struct Node *root, int val)
{
    if (root == NULL)
        return NULL;

    struct Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    struct Node *target = NULL;

    while (front < rear)
    {
        struct Node *curr = queue[front++];

        if (curr->data == val)
        {
            target = curr;
            break;
        }
        if (curr->left)
            queue[rear++] = curr->left;
        if (curr->right)
            queue[rear++] = curr->right;
    }
    if (target == NULL)
        return root;

    struct Node *lastNode = NULL;
    struct Node *lastParent = NULL;
    struct Node *queue1[100];
    int front1 = 0, rear1 = 0;
    queue1[rear1++] = root;
    struct Node *parents[100];
    parents[rear1 - 1] = NULL;

    while (front1 < rear1)
    {
        struct Node *curr = queue1[front1];
        struct Node *parent = parents[front1++];

        lastNode = curr;
        lastParent = parent;

        if (curr->left)
        {
            queue1[rear1] = curr->left;
            parents[rear1++] = curr;
        }
        if (curr->right)
        {
            queue1[rear1] = curr->right;
            parents[rear1++] = curr;
        }
    }

    target->data = lastNode->data;

    if (lastParent)
    {
        if (lastParent->left == lastNode)
            lastParent->left = NULL;
        else
            lastParent->right = NULL;
        free(lastNode);
    }
    else
    {
        free(lastNode);
        return NULL;
    }

    return root;
}

// Function to free allocated memory for the tree
void freeTree(struct Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    struct Node *root = createNode(2);
    root->left = createNode(3);
    root->right = createNode(4);
    root->left->left = createNode(5);

    printf("Inorder traversal before insertion: ");
    inOrderDFS(root);
    printf("\n");

    int key = 6;
    root = insert(root, key);

    printf("Inorder traversal after insertion: ");
    inOrderDFS(root);
    printf("\n");

    // Demonstrate BFS
    printf("BFS Level order traversal: ");
    BFS(root);
    printf("\n");

    // Demonstrate search
    int searchValue = 5;
    printf("Searching for %d: %s\n", searchValue, searchDFS(root, searchValue) ? "Found" : "Not Found");

    // Demonstrate deletion
    int deleteValue = 3;
    root = deleteNode(root, deleteValue);
    printf("Inorder traversal after deletion of %d: ", deleteValue);
    inOrderDFS(root);
    printf("\n");

    // Free allocated memory
    freeTree(root);

    return 0;
}
