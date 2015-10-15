#include <stdio.h>
#include <stdlib.h>

struct Node { //This struct defines each process. It has a unique process ID, priority level, and pointer to the next node in sequence
  int pid;
  int priority;
  struct Node* next;
};

struct Node *head = NULL;
struct Node *curr = NULL;

void insert(int pid, int priority) {
    
    printf("\nAdded process: [ %d, %d ]", pid, priority);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->pid = pid;
    newNode->priority = priority;
    newNode->next = NULL; //makes a new node to insert
    
    if (head == NULL) { //if no new node is present, makes newNode the head
        head = newNode;
        return;
    }
    
    curr = head;    //iterates through linkedlist, finding proper spot for node
    while (curr->next != NULL && curr->next->priority > priority) {
        curr = curr->next;
    }
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp = curr -> next;
    curr -> next = newNode;
    newNode->next = temp;
}

void extractMax() { //returns the first node, since the linkedList is kept in order. The first node will have the highest priority
    printf("\nMax [pid, priority]: [ %d, %d ]", head->pid, head->priority);
}


void swap(struct Node* curr) { //used to keep the queue ordered by priority. This method is called after increase and change methods, because in each one the priority of a process has been changed and the queue needs reordering
    int temppid;
    int temppriority;
    temppid = curr->pid;
    temppriority = curr->priority;
    curr->pid = curr->next->pid;
    curr->priority = curr->next->priority;
    curr->next->pid = temppid;
    curr->next->priority = temppriority;
}

void sort() { //calls the swap method in order to keep the queue in descending order of priority
    curr = head;
    while (curr -> next != NULL) {
        if (curr -> priority < curr->next->priority) { //must swap the two nodes
            swap(curr);
        }
        curr = curr->next;
    }
}

void increase(int pid, int priority, int a) { //finds the given process, increases its priority by the given amount. Then calls sort to find the altered processes' new location in the queue
    curr = head;
    while (curr != NULL) {
        if (curr->pid == pid && curr->priority == priority) {
            break;
        }
        curr=curr->next;
    }
    curr->priority = curr->priority + a;
    printf("\nIncreased [ %d, %d ] to [ %d, %d ]", pid, priority, pid, priority + a);
    sort();
}

void change(int pid, int priority, int a) { //finds the given process, changes its priority to the given amount. Then calls sort to find the altered processes' new location in the queue
    
    curr = head;
    while (curr != NULL) {
        if (curr->pid == pid && curr->priority == priority) {
            break;
        }
        curr=curr->next;
    }
    curr->priority = a;
    printf("\nChanged [ %d, %d ] to [ %d, %d ]", pid, priority, pid, a);
    sort();
}

void printQueue() { //prints all the nodes in the queue in sequential order
    printf("\nQueue [pid, priority] ");
    curr = head;
    while (curr != NULL) {
        printf("[ %d, %d ]", curr->pid, curr->priority);
        curr = curr->next;
    }
}

void main() {
    insert(5, 18);
    insert(7, 16);
    insert(10, 8);
    insert(9, 10);
    insert(6, 18);
    insert(11, 6);
    insert(13, 2);
    printQueue();
    extractMax();
    increase(13, 2, 5);
    printQueue();
    change(5, 18, 20);
    printQueue();
}