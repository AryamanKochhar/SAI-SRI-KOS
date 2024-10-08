// No of nodes in each level
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* cN(int v) {
    struct Node* t = (struct Node*)malloc(sizeof(struct Node));
    t->data = v;
    t->left = NULL;
    t->right = NULL;
    return t;
}

struct Node* insertlo(int arr[], struct Node* root, int i, int n) {
    if (i < n) {
        root = cN(arr[i]);
        root->left = insertlo(arr, root->left, 2 * i + 1, n);
        root->right = insertlo(arr, root->right, 2 * i + 2, n);
    }
    return root;
}

struct Node* cBT(int arr[], int n) {
    return insertlo(arr, NULL, 0, n);
}

int height(struct Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void countNodesAtLevel(struct Node* root, int level, int* count) {
    if (root == NULL)
        return;
    if (level == 1)
        (*count)++;
    else {
        countNodesAtLevel(root->left, level - 1, count);
        countNodesAtLevel(root->right, level - 1, count);
    }
}

void printNodesAtEachLevel(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        int count = 0;
        countNodesAtLevel(root, i, &count);
        printf("Level %d has %d nodes\n", i, count);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5,6,7};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = cBT(arr, n);
    
    printNodesAtEachLevel(root);
    
    return 0;
}