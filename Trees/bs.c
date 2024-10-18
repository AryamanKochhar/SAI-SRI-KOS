#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *right;
    struct Node *left;
} Node;
    
Node *createNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Node *insert1(Node *root, int key)
{
    if (root == NULL)
        return createNode(key);

    Node *queue[100];
    int front = 0, rear = 0;
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

Node *insert2_sub(int arr[], Node *root, int n, int i)
{
    if(i < n)
    {
        root = createNode(arr[i]);
        root->left = insert2_sub(arr, root->left, n, 2*i+1);
        root->right = insert2_sub(arr, root->right, n, 2*i+2);
    }

    return root;
}

Node *insert2(int arr[], int n)
{
    int i = 0;
    Node* root = NULL;

    return insert2_sub(arr, root, n, i);
}

Node *insert3()
{
    int data;
    scanf("%d", &data);
    if(data == -1) return NULL;

    Node* root = createNode(data);
    root->left = insert3();
    root->right = insert3();

    return root;
}

bool Search(Node *root, int key)
{
    if (root == NULL)
    {
        return false;
    }
    if (root->data == key)
    {
        return true;
    }

    return (Search(root->right, key) || Search(root->left, key));
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

void kthSmallesttUtil(Node* root, int k, int *count, int *result)
{
    if(root == NULL || *result != -1)
        return;

    kthSmallesttUtil(root->left, k, count, result);

    (*count)++;
    if(*count == k)
    {
        *result = root->data;
        return;
    }

    kthSmallesttUtil(root->right, k, count, result);

}

int kthSmallestt(Node* root, int k)
{
    int count = 0;
    int result = -1;
    kthSmallesttUtil(root, k, &count, &result);

    return result;
}

void CNL(Node* root, int level, int* count)
{
    if(root == NULL)
        return;
    if(level == 1)
        (*count)++;
    else
    {
        CNL(root->left, level-1, count);
        CNL(root->right, level-1, count);
    }
}

int countNodesAtLevel(Node* root, int level)
{
    int count = 0;
    CNL(root, level, &count);
    return count;
}

void findMaxAtLevel(Node* root, int level, int *max)
{
    if(root == NULL)
        return;
    if(level == 1)
    {
        if(root->data > *max)
        {
            *max = root->data;
        }
    }
    else
    {
        findMaxAtLevel(root->left, level-1, max);
        findMaxAtLevel(root->right, level-1, max);
    }
}

int Height(Node *root)
{
    if(root == NULL)
        return 0;
    
    int left = Height(root->left);
    int right = Height(root->right);

    return (left < right ? left : right)+1;
}

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

void inOrder(Node* root)
{
    if(root == NULL)
        return;
    
    Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while(front < rear)
    {
        Node* current = queue[front++];
        printf("%d", current->data);

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

void inorderTraversal(Node *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void preOrderTraversal(Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    inorderTraversal(root->left);
    inorderTraversal(root->right);
}

void postOrderTraversal(Node *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    inorderTraversal(root->right);
    printf("%d ", root->data);
}

void delete(Node* root, int key)
{
    // Tree is empty
    if(root == NULL)
    {
        return;
    }
 
    // Tree having only one node
    if(root->left == NULL && root->right == NULL)
    {
        if(root->data == key)
        {
            root = NULL;
            printf("\n* Node with data %d was deleted", key);
            return;
        }
        else
        {
            return;
        }
    }
 
    // level order traversal using the queue
    struct Node* temp = NULL, *last_node = NULL, *key_node = NULL;
 
    struct Node* queue[100];
    int front = -1;
    int rear = -1;
 
    queue[front + 1] = root;
    front = rear = 0;
 
    // do level order traversal to find the deepest node
    while (front <= rear)
    {
        temp = queue[front];
        front++;
 
        if (temp->data == key)
        {
            key_node = temp;
        }
 
        if (temp->left != NULL)
        {
            last_node = temp;
            queue[++rear] = temp->left;
        }
 
        if (temp->right != NULL)
        {
            last_node = temp;
            queue[++rear] = temp->right;
        }
    }
 
    // if key is found in the binary tree
    if (key_node != NULL)
    {
        // replace the keynode data with the deepest node
        key_node->data = temp->data;
 
        // free the last node after updating its parent
        if (last_node->right == temp)
        {
            last_node->right = NULL;
        }
        else
        {
            last_node->left = NULL;
        }
        printf("\n* Node with data %d was deleted", key);
        free(temp);
        return;
    }
    printf("\n* Node with data %d was not found", key);
}