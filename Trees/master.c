#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 25
#define max(a, b) a>b ? a : b
 
struct TreeNode
{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
 
// global root declaration
struct TreeNode* root = NULL;
 
// function prototyping
void insert(int);
void delete(int);
int search(int);
int height(struct TreeNode*);
void inorder(struct TreeNode*);
void preorder(struct TreeNode*);
void postorder(struct TreeNode*);
void levelorder();
 
int main()
{
    int user_choice, node_data;
    char user_active = 'Y';
 
    while(user_active == 'Y' || user_active == 'y')
    {
        printf("\n\n--- Binary Tree --\n\n");
        printf("\n1. Insert ");
        printf("\n2. Delete");
        printf("\n3. Search");
        printf("\n4. Height");
        printf("\n5. Inorder Traversal");
        printf("\n6. Preorder Traversal");
        printf("\n7. Postorder Traversal");
        printf("\n8. Level order Traversal");
        printf("\n9. Exit");
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &user_choice);
 
        printf("\n");
        switch(user_choice)
        {
            case 1:
                printf("Enter data for new node: ");
                scanf("%d", &node_data);
                insert(node_data);
                break;
 
            case 2:
                printf("Enter node data: ");
                scanf("%d", &node_data);
                delete(node_data);
                break;
 
            case 3: 
                printf("Enter node data: ");
                scanf("%d", &node_data);
                int has_found = search(node_data);
 
                if(has_found == -1) {
                    printf("\nNode was not found!");
                } else {
                    printf("\nNode was found");
                }
                break;
 
            case 4: 
                printf("height of the tree is: %d", height(root));
                break;
 
            case 5: 
                printf("Inorder Traversal\n\n");
                inorder(root);
                break;
 
            case 6: 
                printf("Preorder Traversal\n\n");
                preorder(root);
                break;
 
            case 7: 
                printf("Postorder Traversal\n\n");
                postorder(root);
                break;
 
            case 8:
                printf("Level order Traversal\n\n");
                levelorder();
                break;
 
            case 9:
                printf("Program is terminating...\n\n");
                exit(0);
 
            default:
                printf("Invalid choice");
        }
 
        fflush(stdin);
        printf("\n\n\nDo you want to continue? (Y/N) ");
        scanf("%c", &user_active);
    }
    return 0;
}
 
struct TreeNode* create(int data)
{
    struct TreeNode* new_node = (struct TreeNode*) malloc (sizeof(struct TreeNode));    
    if(new_node == NULL)
    {
        printf("\nMemory can't be allocated for new node\n");
        return NULL;
    }
 
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->val = data;
 
    return new_node;
}
 
// inserts a new node in the tree
void insert(int data)
{
    if(root == NULL)
    {
        struct TreeNode* new_node = create(data);
        if(new_node)
        {
            root = new_node;
            printf("\n * Node with data %d was inserted", data);
        }
        return;
    }
 
    struct TreeNode* queue[MAX_SIZE];
    struct TreeNode* new_node = NULL;
    int front = -1;
    int rear = -1;
    queue[front+1] = root;
    front = rear = 0;
 
    while(front <= rear)
    {
        struct TreeNode* temp = queue[front];
        front++;
 
        if(temp->left != NULL)
        {
            queue[++rear] = temp->left;
        }
        else
        {
            new_node = create(data);
            if(new_node)
            {
                temp->left = new_node;
                printf("\n* Node with data %d was inserted", data);
            }
            return;
        }
 
        if(temp->right != NULL)
        {
            queue[++rear] = temp->right;
        }
        else
        {
            new_node = create(data);
            if(new_node)
            {
                temp->right = new_node;
                printf("\n* Node with data %d was inserted", data);
            }
            return;
        }
    }
}
 
void delete(int key)
{
    // Tree is empty
    if(root == NULL)
    {
        return;
    }
 
    // Tree having only one node
    if(root->left == NULL && root->right == NULL)
    {
        if(root->val == key)
        {
            root = NULL;
            printf("\n* Node with data %d was deleted", key);
            return;
        }
        else
        {
            return;
        }
    }
 
    // level order traversal using the queue
    struct TreeNode* temp = NULL, *last_node = NULL, *key_node = NULL;
 
    struct TreeNode* queue[MAX_SIZE];
    int front = -1;
    int rear = -1;
 
    queue[front + 1] = root;
    front = rear = 0;
 
    // do level order traversal to find the deepest node
    while (front <= rear)
    {
        temp = queue[front];
        front++;
 
        if (temp->val == key)
        {
            key_node = temp;
        }
 
        if (temp->left != NULL)
        {
            last_node = temp;
            queue[++rear] = temp->left;
        }
 
        if (temp->right != NULL)
        {
            last_node = temp;
            queue[++rear] = temp->right;
        }
    }
 
    // if key is found in the binary tree
    if (key_node != NULL)
    {
        // replace the keynode data with the deepest node
        key_node->val = temp->val;
 
        // free the last node after updating its parent
        if (last_node->right == temp)
        {
            last_node->right = NULL;
        }
        else
        {
            last_node->left = NULL;
        }
        printf("\n* Node with data %d was deleted", key);
        free(temp);
        return;
    }
    printf("\n* Node with data %d was not found", key);
}   
 
int search(int key)
{
    if (root == NULL)
    {
        return -1;
    }
    struct TreeNode* queue[MAX_SIZE];
    int front = -1;
    int rear = -1;
 
    queue[front + 1] = root;
    front = rear = 0;
 
    // do level order traversal to find the deepest node
    while (front <= rear)
    {
        struct TreeNode* temp = queue[front];
        front++;
 
        if (temp->val == key)
        {
            return 1;
        }
 
        if (temp->left != NULL)
        {
            queue[++rear] = temp->left;
        }
 
        if (temp->right != NULL)
        {
            queue[++rear] = temp->right;
        }
    }
    return -1;
}
 
int height(struct TreeNode* root)
{
    if (root == NULL)
    {
        return 0;
    }
 
    int left = height(root->left);
    int right = height(root->right);
 
    if(left > right)
    {
        return left + 1;
    }
    else
    {
        return right + 1;
    }
}
 
// inorder traversal
void inorder(struct TreeNode* root)
{
    if(root == NULL) return;
 
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}
 
// preorder traversal
void preorder(struct TreeNode* root)
{
    if(root == NULL) return;
 
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}
 
// postorder traversal
void postorder(struct TreeNode* root)
{
    if(root == NULL) return;
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}
 
// level order traversal
void levelorder()
{
    if (root == NULL)
    {
        printf("Tree is Empty!");
        return;
    }
 
    struct TreeNode* queue[MAX_SIZE];
    int front = -1;
    int rear = -1;
 
    queue[front + 1] = root;
    front = rear = 0;
 
    // do level order traversal to find the deepest node
    while (front <= rear)
    {
        struct TreeNode* temp = queue[front];
        front++;
 
        printf("%d ", temp->val);
 
        if (temp->left != NULL)
        {
            queue[++rear] = temp->left;
        }
 
        if (temp->right != NULL)
        {
            queue[++rear] = temp->right;
        }
    }
}