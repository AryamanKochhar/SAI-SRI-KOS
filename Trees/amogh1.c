// kth smallest and largest
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

void kthSmallestUtil(struct Node* root, int k, int* count, int* result) {
    if (root == NULL || *result != -1)
        return;
    
    kthSmallestUtil(root->left, k, count, result);
    
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    
    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(struct Node* root, int k) {
    int count = 0;
    int result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}

void kthLargestUtil(struct Node* root, int k, int* count, int* result) {
    if (root == NULL || *result != -1)
        return;
    
    kthLargestUtil(root->right, k, count, result);
    
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    
    kthLargestUtil(root->left, k, count, result);
}

int kthLargest(struct Node* root, int k) {
    int count = 0;
    int result = -1;
    kthLargestUtil(root, k, &count, &result);
    return result;
}

int main() {
    int arr[] = {20, 8, 22, 4, 12, 10, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = cBT(arr, n);
    
    int k; 
    scanf("%d",&k);

    int kthSmallestElem = kthSmallest(root, k);
    int kthLargestElem = kthLargest(root, k);

    printf("%d-th smallest element is %d\n", k, kthSmallestElem);
    printf("%d-th largest element is %d\n", k, kthLargestElem);

    return 0;
}