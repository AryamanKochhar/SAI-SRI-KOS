// Highest elemnt in each level
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

void findMaxAtLevel(struct Node* root, int level, int* max) {
    if (root == NULL)
        return;
    if (level == 1)
        *max = (root->data > *max) ? root->data : *max;
    else {
        findMaxAtLevel(root->left, level - 1, max);
        findMaxAtLevel(root->right, level - 1, max);
    }
}

void printMaxAtEachLevel(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        int max = -1000000;
        findMaxAtLevel(root, i, &max);
        printf("Maximum element at level %d is %d\n", i, max);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = cBT(arr, n);
    
    printMaxAtEachLevel(root);
    
    return 0;
}