#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *right;
    struct Node *left;
} Node;

Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

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

void inOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void preOrder(Node *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    inOrder(root->left);
    inOrder(root->right);
}

void postOrder(Node *root)
{
    if (root == NULL)
        return;

    inOrder(root->left);
    inOrder(root->right);
    printf("%d ", root->data);
}

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

int main()
{
    Node* root = NULL;

    for(int i = 0; i < 10; i++)
    {
        root = Insert(root, i);
    }

    inOrder(root);
    printf("\n");
    levelOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");
    preOrder(root);

    printf("\n");
    printf("%d", searchDFS(root, 11));
}