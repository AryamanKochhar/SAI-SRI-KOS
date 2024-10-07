#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

node *newNode(int data) {
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node *insert() {
    int data;
    scanf("%d", &data);
    if (data == -1) return NULL;

    node *root = newNode(data);
    printf("Enter left child of %d: ", data);
    root->left = insert();
    printf("Enter right child of %d: ", data);
    root->right = insert();
    
    return root;
}

void inorderTraversal(node *root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void freeTree(node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    printf("Enter the root: ");
    node *root = insert();

    printf("In-order traversal of binary tree is: ");
    inorderTraversal(root);
    printf("\n");

    freeTree(root);
    return 0;
}
