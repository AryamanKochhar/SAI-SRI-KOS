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

int Search(BstNode *root, int data)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (root->data == data)
    {
        return 1;
    }
    else if (data <= root->data)
    {
        return Search(root->left, data);
    }
    else
    {
        return Search(root->right, data);
    }
}

BstNode *findNode(BstNode *root, int data)
{
    if (root == NULL)
        return NULL;
    if (root->data == data)
        return root;
    else if (data < root->data)
        return findNode(root->left, data);
    else
        return findNode(root->right, data);
}

int findNodeHeight(BstNode *root, int data)
{
    BstNode *targetNode = findNode(root, data);
    if (targetNode == NULL)
        return -1;

    return findHeight(targetNode);
}

int findHeight(BstNode *root)
{
    if (root == NULL)
    {
        return -1;
    }

    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int findNodeDepth(BstNode *root, int data)
{
    int depth = 0;
    while (root != NULL)
    {
        if (root->data == data)
        {
            return depth;
        }
        else if (data < root->data)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
        depth++;
    }

    return -1;
}

int findMin(BstNode *root)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }

    while (root->left != NULL)
    {
        root = root->left;
    }

    return root->data;
}

int findMax(BstNode *root)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }

    while (root->right != NULL)
    {
        root = root->right;
    }

    return root->data;
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

// Queue Functions for Level Order Traversal
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

    int number;
    printf("Enter number to find its height and depth: ");
    scanf("%d", &number);

    if (Search(root, number) == 1)
    {
        int nodeHeight = findNodeHeight(root, number);
        if (nodeHeight != -1)
        {
            printf("Height of node with value %d: %d\n", number, nodeHeight);
        }

        int nodeDepth = findNodeDepth(root, number);
        if (nodeDepth != -1)
        {
            printf("Depth of node with value %d: %d\n", number, nodeDepth);
        }
    }
    else
    {
        printf("Node not found\n");
    }

    int minValue = findMin(root);
    printf("Minimum value in the tree: %d\n", minValue);

    int maxValue = findMax(root);
    printf("Maximum value in the tree: %d\n", maxValue);

    printf("\nIn-order Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("Level-order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}
