#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->right = NULL;
    temp->left = NULL;

    return temp;
}

Node* Insert()
{
    int data;
    scanf("%d", &data);
    if(data == -1) return NULL;

    Node* root = newNode(data);
    root->left = Insert();
    root->right = Insert();

    return root;
}
