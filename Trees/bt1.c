#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int maxx(int a, int b) {
    return (a > b) ? a : b;
}

int height(node *root) {
    if (root == NULL) {
        return 0;
    }
    return maxx(height(root->left), height(root->right)) + 1;
}

void insert(node **root, int data) {
    if (*root == NULL) {
        *root = newNode(data);
        return;
    }
    int front = 0, rear = 0;
    node *queue[100]; // Fixed-size array for the queue
    queue[rear++] = *root;
    while (front < rear) {
        node *temp = queue[front++];
        if (temp->left == NULL) {
            temp->left = newNode(data);
            break;
        } else {
            queue[rear++] = temp->left;
        }
        if (temp->right == NULL) {
            temp->right = newNode(data);
            break;
        } else {
            queue[rear++] = temp->right;
        }
    }
}

void inorder(node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void findMinMax(node *root, int *min, int *max) {
    if (root == NULL) return;

    if (root->data < *min) *min = root->data;
    if (root->data > *max) *max = root->data;

    findMinMax(root->left, min, max);
    findMinMax(root->right, min, max);
}

bool search(node *root, int key) {
    if (root == NULL)
        return false;
    if (root->data == key)
        return true;
    return search(root->left, key) || search(root->right, key);
}

int main() {
    int a;
    scanf("%d", &a);
    node *root = NULL;

    for (int i = 0; i < a; i++) {
        int d;
        scanf("%d", &d);
        insert(&root, d);
    }

    int min = root->data, max = root->data;
    findMinMax(root, &min, &max);

    inorder(root);
    printf("\nMin: %d, Max: %d\n", min, max);

    return 0;
}
