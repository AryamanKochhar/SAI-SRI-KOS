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

node *insertLevelOrder(int arr[], int n, int i) {
    if (i >= n) return NULL;

    node *root = newNode(arr[i]);
    root->left = insertLevelOrder(arr, n, 2 * i + 1);
    root->right = insertLevelOrder(arr, n, 2 * i + 2);
    return root;
}

void postorderTraversal(node* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

int calculateSum(node* root) {
    if (root == NULL) return 0;
    return root->data + calculateSum(root->left) + calculateSum(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    node* root = insertLevelOrder(arr, n, 0);
    
    postorderTraversal(root);
    printf("\n");

    int totalValue = calculateSum(root);
    printf("%d\n", totalValue);

    // Free memory (not implemented here for simplicity)
    
    return 0;
}
