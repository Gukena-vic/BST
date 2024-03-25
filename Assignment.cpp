#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);

    return root;
}


struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


int height(struct Node* root) {
    if (root == NULL)
        return -1;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}


void printLevelHeight(struct Node* root, int key, int level) {
    if (root == NULL)
        return;

    if (root->data == key)
        printf("Node %d found at level %d and height %d\n", key, level, height(root));

    if (key < root->data)
        printLevelHeight(root->left, key, level + 1);
    else
        printLevelHeight(root->right, key, level + 1);
}


void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = NULL;

   
    for (int i = 0; i < n; i++)
        root = insertNode(root, arr[i]);

   
    printf("Inorder traversal of BST: ");
    inorderTraversal(root);
    printf("\n");

    
    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);
    printf("Inorder traversal after deleting %d: ", keyToDelete);
    inorderTraversal(root);
    printf("\n");

   
    printf("Height of BST: %d\n", height(root));

    
    int nodeToFind = 30;
    printLevelHeight(root, nodeToFind, 0);

    return 0;
}
