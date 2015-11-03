#include <stdio.h>
#include <stdlib.h>

struct Node { //struct created to form the nodes in the linkedList. It contains an integer and a reference to the next node in sequence
	int pageFrame;
	struct Node *next;
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
    newNode->next = NULL;
    head = curr = newNode;
    return newNode;
}

void addFirstNode(int num) { //adds a node with the given num value as its data to the front. Concatenates all existing nodes after the newNode
	
	printf("\nAdding first node: %d", num);

	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
	
	temp = head; //stores head of list as a temp variable
	
	newNode->data = num;
	newNode->next = temp; //old head is now placed after the new node
	
	head = newNode; //new node is now set as the head of the list
}

void addLastNode(int num) { //attaches the newNode to the end of the list
	
	printf("\nAdding last node: %d", num);
	//iterates to the end of the list, and then adds a node there
	curr = head;
	while (curr -> next != NULL) {
		curr = curr->next;
		
	}
	//curr is at the last node. Function creates a new node with the given value and adds it to the end of the list
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = num;
	newNode->next = NULL;
	curr->next = newNode;
	
}

int searchNode(int num) {
	//iterates through the list, if a node with data that matches the parameter num, return 1 for true. If none found, return 0 for false
	curr = head;
	while (curr != NULL) {
		if (curr->data == num) {
			return 1; //found matching node
		}
		curr = curr->next;
	}
	return 0; //did not find matching node
}  

void deleteNode(int num) { //removes all nodes the have data values matching the given num
	
	printf("\nDeleting all nodes with value: %d", num);
	if (searchNode(num) == 0) {
	 	printf("\nNode with following data does not exist: %d", num);
	}
	 else {
	 	if (head->data == num) { //if head has matching input data, it shifts the head node to the right once
	 		head= head->next;
	 	}
	 	else {
	 		curr = head;
			while (curr -> next != NULL) { //iterates through entire list until it finds a node with the data that needs to be deleted
				if (curr->next->data == num) {
					curr->next = curr -> next -> next;
					curr = head; //after removing node, list iterates from head again to find duplicate entries of nodes with the same data
				}
				curr = curr->next;
			}
	 	}
	}
}

void countNodes() { //counts the number of nodes in the list
	int count = 0;
	curr = head;
	while (curr != NULL) {
		count++;
		curr=curr->next;
	}
	printf("\nNumber of nodes in list: %d", count);
	
}

void printList() { //prints the list to the console
	curr = head;
	printf("\n\nPrinted List:   ");
	while (curr != NULL) {
		printf("%d-----> ", curr->data);
		curr=curr->next;
	}
	printf("NULL\n");
	
}


void main() {
	
	createList(2);
	addLastNode(3);
	addFirstNode(1);
	addLastNode(2);
	printList();
	countNodes();
	printf("\nSearch for 1: %d", searchNode(1));
	printf("\nSearch for 4: %d", searchNode(4));
	deleteNode(2);
	printList();

}
