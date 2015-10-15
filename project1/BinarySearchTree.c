#include <stdio.h>
#include <stdlib.h>

struct Node { //this struct had an int value, and two references to other nodes so the left and right branches of the tree can be created
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;

struct Node* createList(int num) { //creates the root of the tree, which has the given num as data and two branches pointing to NULL
    
    printf("\nCreating list with the head node: %d", num);
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == newNode) {
        printf("\nNode creation failed\n");
        return NULL;
    }
    newNode->data = num;
    newNode->left = NULL;
    newNode->right = NULL;
    root = newNode;
    return newNode;
    
}


struct Node* insert(struct Node* node, int data) { //recursively finds the correct location for the given data, and inserts it into the BST
    if (node == NULL) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data ;
        newNode->left = NULL;
        newNode->right = NULL;
        printf("\nInserted: %d", data);
        return(newNode);
    }
    else {
        if (data <= node->data) {
            node->left = insert(node->left, data);
        }
        else {
            node->right = insert(node->right, data);
        }
        return node;
    }
}

void printTree(struct Node *node) { //recursively iterates through the BST, performing an inorder traversal of the nodes and printing each one out
    if (node == NULL) {
    } 
    else {
        printTree(node->left);
        printf(" %d ", node->data);
        printTree(node->right);
    }
}

int countNodes(struct Node* node) { //recursively traverses each node in the BST, incrementing a counter with each node traversed
    int count = 1;
    if (node == NULL) {
        return 0;
    } 
    else {
        count += countNodes(node->left);
        count += countNodes(node->right);
        return count;
    }
}

int searchNode(struct Node* node, int num) { //recursively traverses the BST, returning 1 if a node with data matching the given num is found. Returns 0 if no such node is found
    if(node == NULL)
        return 0;
    else {
        if (node->data== num)
            return 1;
        int temp;
        temp = searchNode(node->left, num);
        if (temp == 1)
            return temp;
        temp = searchNode(node->right, num);
        if (temp)
            return temp;
    }
    //value not found in BST
    return 0;
}

/*struct Node* findParent(struct Node* node, int num, struct Node* parent) { //couldn't get this to work, kept giving a segmentation fault. Would have been used to remove the pointers pointing to the nodes being removed
        
    if (node == NULL) { 
        printf("base case");
        return NULL;
    }
    if (num < node->data) {
       findParent(node->left, num, node);
    }
    else if (num > node->data) {
        findParent(node->right, num, node);
    }
    else {
        //found parent, returns pointer to that node
        return parent;
    }
    
}*/

struct Node* minValueNode(struct Node* node) //finds the leftmost leaf, used in deleteNode method
{
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void deleteNode(struct Node* node, int num) { //deletes the selected node, covers all three possible cases (no children, one child, two children)
    
    if (node == NULL) { 
        printf("base case");
    }
    if (num < node->data) {
       deleteNode(node->left, num);
    }
    else if (num > node->data) {
        deleteNode(node->right, num);
    }
    else {
         if (node->left == NULL && node->right != NULL) { //one child
             struct Node* temp = node->right;
             node->right = NULL;
             node = temp;
         }
         else if (node -> left == NULL && node->right == NULL) { //no children
             free(node);
             
         }
         else { //two children
             struct Node* temp = minValueNode(node->right); //replaces node with the minimum value on the node's right brance
             node->data = temp->data;
             deleteNode(node->right, temp->data);
         }
    }
}

void print() { //sets up the actual print method
    printf("\nInorder traversal of tree: ");
    printTree(root);
}


void main() {
    createList(17);
    insert(root, 12);
    insert(root, 35);
    insert(root, 6);
    insert(root, 14);
    insert(root, 32);
    insert(root, 40);
    print();
    printf("\nNumber of nodes: %d ", countNodes(root));
    printf("\nSearch for 32: %d", searchNode(root, 32));
    printf("\nSearch for 10: %d", searchNode(root, 10));
    printf("\nDeleted 6");
    deleteNode(root, 6);
    print();
}