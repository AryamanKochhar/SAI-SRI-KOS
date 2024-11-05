#include <stdio.h>
#include <stdlib.h>

typedef struct BstNode
{
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

BstNode *createNewNode(int data)
{
    BstNode *new_node = (BstNode *)malloc(sizeof(BstNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

BstNode *Insert(BstNode *root, int data)
{
    if (root == NULL)
    {
        root = createNewNode(data);
    }
    else if (data <= root->data)
    {
        root->left = Insert(root->left, data);
    }
    else
    {
        root->right = Insert(root->right, data);
    }
    return root;
}

BstNode *findMinNode(BstNode *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

BstNode *findMaxNode(BstNode *root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

int isBSTUtil(BstNode *node, int minValue, int maxValue)
{
    if (node == NULL)
        return 1;

    if (node->data < minValue || node->data > maxValue)
        return 0;

    return isBSTUtil(node->left, minValue, node->data - 1) &&
           isBSTUtil(node->right, node->data + 1, maxValue);
}

int isBST(BstNode *root)
{
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

BstNode *Delete(BstNode *root, int data)
{
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = Delete(root->left, data);
    else if (data > root->data)
        root->right = Delete(root->right, data);
    else
    {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        // Case 2: One child
        else if (root->left == NULL)
        {
            BstNode *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            BstNode *temp = root;
            root = root->left;
            free(temp);
        }
        // Case 3: Two children
        else
        {
            BstNode *temp = findMinNode(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

void inorderTraversal(BstNode *root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(BstNode *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(BstNode *root)
{
    if (root == NULL)
        return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

void findKthMin(BstNode *root, int *k, int *result)
{
    if (root == NULL || *result != -1)
        return;

    findKthMin(root->left, k, result);

    (*k)--;
    if (*k == 0)
    {
        *result = root->data;
        return;
    }

    findKthMin(root->right, k, result);
}

void findKthMax(BstNode *root, int *k, int *result)
{
    if (root == NULL || *result != -1)
        return;

    findKthMax(root->right, k, result);

    (*k)--;
    if (*k == 0)
    {
        *result = root->data;
        return;
    }

    findKthMax(root->left, k, result);
}

void LevelOrder(BstNode *root)
{
    if (root == NULL)
        return;

    BstNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear)
    {
        BstNode *current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}

int LCA(BstNode *root, int q, int r)
{
    if (root == NULL)
        return NULL;
    if (root->data < q && root->data < r)
    {
        return LCA(root->right, q, r);
    }
    if (root->data > q && root->data > r)
    {
        return LCA(root->left, q, r);
    }

    return root->data;
}

int main()
{
    BstNode *root = NULL;

    // Insert elements
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 8);
    root = Insert(root, 12);
    root = Insert(root, 7);
    root = Insert(root, 9);
    root = Insert(root, 11);
    root = Insert(root, 13);

    printf("In-order Traversal: ");
    preorderTraversal(root);
    printf("\n");

    // Find k-th minimum element
    int k = 3; // Change k for different results
    int resultMin = -1;
    findKthMin(root, &k, &resultMin);
    if (resultMin != -1)
        printf("3rd Minimum element: %d\n", resultMin);
    else
        printf("Not enough elements in the tree.\n");

    // Find k-th maximum element
    k = 3;
    int resultMax = -1;
    findKthMax(root, &k, &resultMax);
    if (resultMax != -1)
        printf("3rd Maximum element: %d\n", resultMax);
    else
        printf("Not enough elements in the tree.\n");

    // Level-order traversal
    printf("Level-order Traversal: ");
    LevelOrder(root);
    printf("\n");
    // Delete element
    inorderTraversal(root);
    printf("\n");
    
    printf("%d", LCA(root, 7, 13));

    return 0;
}