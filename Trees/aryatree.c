#include <stdio.h>
#include <stdlib.h>
struct Node{
    int data;
    struct Node* right;
    struct Node* left;
};
void inorderTraversal(struct Node* root){
    //base case
    if(root==NULL) return;
    inorderTraversal(root->left);
    printf("%d",root->data);
    inorderTraversal(root->right);
}
// postorderTraversal traversal
void postorderTraversal(struct Node* root) {
  if (root == NULL) return;
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  printf("%d ->", root->item);
}
struct Node* createNode(int data){
    struct  node* newNode=()
    
}
