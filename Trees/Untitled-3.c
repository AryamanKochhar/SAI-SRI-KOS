// kth smallest and largest
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
struct Node* cN(int v){
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->data=v;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}//inserting the Nodes in level order
struct Node* insertl(int arr[],struct Node* root,int i,int n){
    if (i<n){
        root=cN(arr[i]);
        root->left=insertlo(arr,root->left,2*i+1,n);
        root->right=insertlo(arr,root->right,2*i+2,n);       
        }
    return root;
}
void countNodeatlevel(struct Node* root,int level,int* count){
    if(root==NULL){
        return;
    }
    if(level==1){
        (*count)++;
    }
    else{
        countNodeatlevel(root->left,level-1,count);
        countNodeatlevel(root->left,level-1,count);
    }
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
struct Node *Insert(struct * root,int data){
    if(root==NULL){
        root=cN(data);
    }
    else if(data<=root->data){
        root->left=Insert(root->left,data);
    }
    else{
        root->right=Insert(root->right,data);
    }
}
