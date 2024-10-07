#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int findMaxLevel(struct TreeNode* root, int level, int* result) {
    if (!root) return level;
    
    if (level >= 10000) return level;
    
    if (result[level] < root->val) {
        result[level] = root->val;
    }
    
    int leftMax = findMaxLevel(root->left, level + 1, result);
    int rightMax = findMaxLevel(root->right, level + 1, result);
    
    return leftMax > rightMax ? leftMax : rightMax;
}

struct TreeNode* buildTree(char* input) {
    struct TreeNode* nodes[10000] = {NULL};
    int values[10000];
    int nullFlags[10000] = {0};
    int nodeCount = 0;
    
    char* token = strtok(input, ",");
    while (token != NULL && nodeCount < 10000) {
        if (strcmp(token, "null") == 0) {
            nullFlags[nodeCount] = 1;
            values[nodeCount] = 0;
        } else {
            values[nodeCount] = atoi(token);
        }
        nodeCount++;
        token = strtok(NULL, ",");
    }
    
    if (nodeCount == 0 || nullFlags[0]) return NULL;
    
    nodes[0] = createNode(values[0]);
    for (int i = 0; i < nodeCount / 2; i++) {
        if (nodes[i]) {
            int leftIdx = 2 * i + 1;
            int rightIdx = 2 * i + 2;
            
            if (leftIdx < nodeCount && !nullFlags[leftIdx]) {
                nodes[leftIdx] = createNode(values[leftIdx]);
                nodes[i]->left = nodes[leftIdx];
            }
            
            if (rightIdx < nodeCount && !nullFlags[rightIdx]) {
                nodes[rightIdx] = createNode(values[rightIdx]);
                nodes[i]->right = nodes[rightIdx];
            }
        }
    }
    
    return nodes[0];
}

void freeTree(struct TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char input[10000];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        
        struct TreeNode* root = buildTree(input);
        
        int result[10000];
        for (int i = 0; i < 10000; i++) {
            result[i] = -2147483648;
        }
        
        int maxLevel = findMaxLevel(root, 0, result);
        
        printf("[");
        for (int i = 0; i < maxLevel; i++) {
            printf("%d%s", result[i], i < maxLevel - 1 ? ", " : "");
        }
        printf("]\n");
        
        freeTree(root);
    }
    return 0;
}