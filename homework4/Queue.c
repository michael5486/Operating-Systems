/*Queue - Linked List implementation*/
#include<stdio.h>
#include<stdlib.h>
struct Node {
	int data;
	struct Node* next;
};
// Two glboal variables to store address of front and rear nodes. 
struct Node* front = NULL;
struct Node* rear = NULL;

// To Dequeue an integer.
int Dequeue() {
	struct Node* temp = front;
	int temp2;
	if(front == NULL) {
		printf("Queue is Empty\n");
		return;
	}
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		temp2 = front->data;
		front = front->next;
	}
	free(temp);
	printf("Dequeued: %d   ", temp2);
}

// To Enqueue an integer
void Enqueue(int x) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	
	if (calcLength() < 3) {
	
		temp->data =x; 
		temp->next = NULL;
		if(front == NULL && rear == NULL){
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp; 
	}
	else {
		Dequeue();
				temp->data =x; 
		temp->next = NULL;
		if(front == NULL && rear == NULL){
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp; 
	}
}

int calcLength() {
	struct Node* temp = front;
	int length = 0;	
	while(temp != NULL) {
		length++;
		temp = temp->next;
	}
	return length;
}

void Print() {
	struct Node* temp = front;
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("Length: %d \n", calcLength());
}

int main(){
	/* Drive code to test the implementation. */
	// Printing elements in Queue after each Enqueue or Dequeue 
	Enqueue(7); Print(); 
	Enqueue(0); Print();
	Enqueue(1); Print();
//	Dequeue();  Print();
	Enqueue(2); Print();
	Enqueue(3); Print();
	Enqueue(0); Print();
	Enqueue(4); Print();
	

}