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

node *insertLevelOrder(int arr[], node *root, int i, int n) {
    if (i < n) {
        node *temp = newNode(arr[i]);
        root = temp;
        root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);
        root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
    }
    return root;
}

int sumRightChildren(node *root) {
    if (root == NULL) return 0;
    int sum = 0;
    if (root->right != NULL) {
        sum += root->right->data;
    }
    sum += sumRightChildren(root->left);
    sum += sumRightChildren(root->right);
    return sum;
}

void freeTree(node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    printf("Enter the number of nodes in the binary tree: ");
    scanf("%d", &n);

    int arr[100];
    printf("Enter the values of the nodes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    node *root = insertLevelOrder(arr, root, 0, n);
    
    int sum = sumRightChildren(root);
    printf("%d\n", sum);

    freeTree(root);
    return 0;
}
