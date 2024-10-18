#include <stdio.h>
#include <stdlib.h>

typedef struct BstNode
{
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

typedef struct QueueNode
{
    BstNode *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

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
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
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

Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, BstNode *node)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->treeNode = node;
    newNode->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
}

BstNode *dequeue(Queue *queue)
{
    if (queue->front == NULL)
        return NULL;

    QueueNode *temp = queue->front;
    BstNode *treeNode = temp->treeNode;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    free(temp);
    return treeNode;
}

int isQueueEmpty(Queue *queue)
{
    return queue->front == NULL;
}

void levelOrderTraversal(BstNode *root)
{
    if (root == NULL)
        return;

    Queue *queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue))
    {
        BstNode *currentNode = dequeue(queue);
        printf("%d ", currentNode->data);

        if (currentNode->left != NULL)
            enqueue(queue, currentNode->left);

        if (currentNode->right != NULL)
            enqueue(queue, currentNode->right);
    }

    free(queue);
}

int main()
{
    BstNode *root = NULL;

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
    inorderTraversal(root);
    printf("\n");

    int k = 3;
    int resultMin = -1;
    findKthMin(root, &k, &resultMin);
    if (resultMin != -1)
        printf("3rd Minimum element: %d\n", resultMin);
    else
        printf("Not enough elements in the tree.\n");

    k = 3;
    int resultMax = -1;
    findKthMax(root, &k, &resultMax);
    if (resultMax != -1)
        printf("3rd Maximum element: %d\n", resultMax);
    else
        printf("Not enough elements in the tree.\n");

    printf("Level-order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    root = Delete(root, 10);
    printf("After deletion of 10, In-order Traversal: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}