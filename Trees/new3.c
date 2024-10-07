#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(Node* node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void printLevel(Node* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

Node* insertLevelOrder(int arr[], int i, int n) {
    Node* root = NULL;
    if (i < n) {
        root = newNode(arr[i]);
        root->left = insertLevelOrder(arr, 2 * i + 1, n);
        root->right = insertLevelOrder(arr, 2 * i + 2, n);
    }
    return root;
}

void reverseLevelOrder(Node* root) {
    int h = height(root);
    for (int i = h; i >= 1; i--) {
        printLevel(root, i);
    }
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    
    if (n < 1 || n > 15) return 1;
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] < 1 || arr[i] > 100) {
            free(arr);
            return 1;
        }
    }
    
    Node* root = insertLevelOrder(arr, 0, n);
    
    reverseLevelOrder(root);
    printf("\n");
    
    free(arr);
    freeTree(root);
    
    return 0;
}