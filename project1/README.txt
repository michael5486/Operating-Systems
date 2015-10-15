Michael Esposito
Operating Systems, Project 1

Every different data structure we were assigned to create is a separate .c file. To compile, run gcc SinglyLinkedList.c, gcc DoublyLinkedList.c, gcc PriorityQueue.c etc. Then ./a.out. I left in my comments and code used to debug the programs, they will be helpful for you in determining how the code works. Each function we were assigned to do has an individual method associated with it.


SinglyLinkedList.c
    1. To create a list, call createList(int num) with num being the data value you would like to add.
    2. From here, you can call the other methods like addFirstNode, addLastNode, countNodes, printList, deleteNode.
    3. Example method calls I used to test:
    
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
    --------the output for this code------------------------
    
Creating list with the head node: 2
Adding last node: 3
Adding first node: 1
Adding last node: 2

Printed List:   1-----> 2-----> 3-----> 2-----> NULL

Number of nodes in list: 4
Search for 1: 1
Search for 4: 0
Deleting all nodes with value: 2

Printed List:   1-----> 3-----> NULL





DoublyLinkedList.c

Uses the same methods as SinglyLinkedList. Commands used to test the program: 

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
----------Output for this code-----------

Creating list with the head node: 2
Adding last node: 3
Adding first node: 1
Adding last node: 2
Adding last node: 4

Printed List:  NULL <--- 1 <-----> 2 <-----> 3 <-----> 2 <-----> 4 <-----> NULL

Number of nodes in list: 5
Search for 1: 1
Search for 5: 0
Deleting all nodes with value: 2

Printed List:  NULL <--- 1 <-----> 3 <-----> 4 <-----> NULL
	




CircularLinkedList.c

Similar to the singlyLinkedList, except that the list has a tail that wraps around and points back to the head. 

1. To create a list, call createList(int num) with num being the data value you would like to add.
2. From here, you can call the other methods like addFirstNode, addLastNode, countNodes, printList, deleteNode.
3. Example method calls I used to test:

	
	createList(2);
	addLastNode(3);
	printList();
	addLastNode(2);
	printList();
	countNodes();
	printf("\nSearch for 1: %d", searchNode(1));
	printf("\nSearch for 2: %d", searchNode(2));
	deleteNode(2);
	printList();
------Output from this code-------

Creating list with the head node: 2
Adding last node: 3

Printed List:   2-----> 3-----> NULL

Adding last node: 2

Printed List:   2-----> 3-----> 2-----> NULL

Number of nodes in list: 0
Search for 1: 0
Search for 2: 0
Deleting all nodes with value: 2
Node with following data does not exist: 2

Printed List:   2-----> 3-----> 2-----> NULL






BinarySearchTree.c

1. Call insert method with the int you want as the root to create the BST
2. Call insert again to add any desired nodes, insert finds the right spot to attach nodes to the tree
3. From here on, you can call methods like print, countNodes, deleteNode, searchNode
4. Code I used to test my program: 

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
-------Output---------------

Creating list with the head node: 17
Inserted: 12
Inserted: 35
Inserted: 6
Inserted: 14
Inserted: 32
Inserted: 40
Inorder traversal of tree:  6  12  14  17  32  35  40 
Number of nodes: 7 
Search for 32: 1
Search for 10: 0
Deleted 6
Inorder traversal of tree:  0  12  14  17  32  35  40







Priority Queue.c

1. My priority queue is a linkedList to allow for the easy adding of new processes and altering of priority.
2. Call insert to create the priority queue. Insert will find the correct location for any new process as determined by its priority.
3. From here you can add nodes with insert, extractMax, increase, change, and printQueue.
4. Other methods exist, but they are helper methods and are called by the methods listed above.
5. Code used to test my priority queue:

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
-----Output from code------------

Added process: [ 5, 18 ]
Added process: [ 7, 16 ]
Added process: [ 10, 8 ]
Added process: [ 9, 10 ]
Added process: [ 6, 18 ]
Added process: [ 11, 6 ]
Added process: [ 13, 2 ]
Queue [pid, priority] [ 5, 18 ][ 6, 18 ][ 7, 16 ][ 9, 10 ][ 10, 8 ][ 11, 6 ][ 13, 2 ]
Max [pid, priority]: [ 5, 18 ]
Increased [ 13, 2 ] to [ 13, 7 ]
Queue [pid, priority] [ 5, 18 ][ 6, 18 ][ 7, 16 ][ 9, 10 ][ 10, 8 ][ 13, 7 ][ 11, 6 ]
Changed [ 5, 18 ] to [ 5, 20 ]
Queue [pid, priority] [ 5, 20 ][ 6, 18 ][ 7, 16 ][ 9, 10 ][ 10, 8 ][ 13, 7 ][ 11, 6 ]