#include <stdio.h>
#include <stdlib.h>

struct Node { //struct created to form the nodes in the linkedList. It contains an integer and references to the next node in sequence and the previous node
	int data;
	struct Node *left;
	struct Node *right;
};

struct Node *head = NULL;
struct Node *curr = NULL;

struct Node* createList(int num) { //creates a list, with the initial node having a data value of the given int
	
	printf("\nCreating list with the head node: %d", num);
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == newNode) {
        printf("\nNode creation failed\n");
        return NULL;
    }
    
    newNode->data = num;
    newNode->left = NULL;
    newNode->right = NULL;

    head = curr = newNode;
    return newNode;

}

void addFirstNode(int num) { //adds a node with the given num value as its data to the front. Concatenates all existing nodes after the newNode
	
	printf("\nAdding first node: %d", num);

	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
	
	temp = head; //stores head of list as a temp variable
	temp->left = newNode;
	newNode->data = num;
	newNode->left = NULL;
	newNode->right = temp; //old head is now placed after the new node
	
	head = newNode; //new node is now set as the head of the list
}

void addLastNode(int num) { //attaches the newNode to the end of the list
	
	printf("\nAdding last node: %d", num);
	//iterates to the end of the list, and then adds a node there
	curr = head;
	while (curr -> right != NULL) {
		curr = curr->right;
		
	}
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = num;
	newNode->left = curr;
	newNode->right = NULL;
	curr->right = newNode;
	
}

int searchNode(int num) {
	//iterates through the list, if a node with data that matches the parameter num, return 1 for true. If none found, return 0 for false
	curr = head;
	while (curr != NULL) {
		if (curr->data == num) {
			return 1; //found matching node
		}
		curr = curr->right;
	}
	return 0; //did not find matching node
}  

void deleteNode(int num) { //removes all nodes with the given value from the linkedList
	
	printf("\nDeleting all nodes with value: %d", num);
	if (searchNode(num) == 0) {
	 	printf("\nNode with following data does not exist: %d", num);
	}
	 else {
	 	curr = head;
	 	while(curr != NULL) {
	 		if (curr->data == num) {
	 			if (curr->left == NULL) { //node to be removed is head
	 				head = head->right;
	 				head->left = NULL;
					curr = head;
	 			} 
	 			if (curr->right == NULL) { //node to be removed is tail
	 				curr->left->right = NULL;
	 				curr = head;
	 			}
	 			else { //node to be removed is neither head nor tail
	 				curr->left->right = curr->right;
	 				curr->right->left = curr->left;
	 				curr = head;
	 			}
	 		}
	 		curr=curr->right;
	 	}
	 }
}

void countNodes() { //counts the number of nodes in the list and prints it to the console
	int count = 0;
	curr = head;
	while (curr != NULL) {
		count++;
		curr=curr->right;
	}
	printf("\nNumber of nodes in list: %d", count);
	
}

void printList() { //prints the nodes in the linkedList to the console in order
	curr = head;
	printf("\n\nPrinted List:  NULL <--- ");
	while (curr != NULL) {
		printf("%d <-----> ", curr->data);
		curr=curr->right;
	}
	printf("NULL\n");
	
}


void main() {
	
	createList(2);
	addLastNode(3);
	addFirstNode(1);
	addLastNode(2);
	addLastNode(4);
	printList();
	countNodes();
	printf("\nSearch for 1: %d", searchNode(1));
	printf("\nSearch for 5: %d", searchNode(5));
	deleteNode(2);
	printList();

}
