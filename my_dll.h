// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
// - Do NOT just replace this file with your DLL file - some of the 
//     signatures have changed data types! Our data is now a void*
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

#include  <stdlib.h>

// Create a node data structure. 
// NOTE THE CHANGES from your original node - we are using a 
// void pointer for data so that we can use the same dll 
// but we're not storing integers anymore.
typedef struct node {
    void* data;
    struct node* next;
    struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
    int count;              // count keeps track of how many items are in the DLL.
    node_t* head;           // head points to the first node in our DLL.
    node_t* tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){

	//malloc space for DoubleLinkedList
	dll_t* myDLL = (dll_t*)malloc(sizeof(dll_t));

	if(myDLL == NULL){
		return NULL;
	}
	else{
		//initialize DLL fields
		myDLL->count = 0;
		myDLL->head = NULL;
		myDLL-> tail = NULL;
	}
	return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Exits if the DLL is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){

    //if DLL is NULL return -1
	if(l == NULL){
		return -1;
	}
	//if count is zero return true 
	else if(l->count == 0){
		return 1;
	}
	//if count is greater then 0, return false 
	else{
		return 0;
	}
}

// push a new item to the front of the DLL ( before the first node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
    // check if list is NULL
	if(l == NULL){
		return 0;
	}
	else{
		//malloc a new node
		node_t* newNode = (node_t*)malloc(sizeof(node_t));
		
		//check if new node malloc was sucessful
		if(newNode == NULL){
			return 0;
		}
        //put item in node
        newNode->data = item;
		// is list is empty?
		if(dll_empty(l) == 1){
			l->head = newNode;
            l->tail = newNode;
            newNode->previous = NULL;
            newNode->next = NULL;
		}

		else{
			l->head->previous = newNode;
			newNode->next = l->head;
			//rewire head
			l->head = newNode;
			//set head node previous pointer to null
			newNode->previous = NULL;

		}
		//increment count 
		l->count ++;
		//return success
		return 1;
	}
	return 0;
}

// push a new item to the end of the DLL (after the last node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
    //check if list is NULL
	if(l == NULL){
		return 0;
	}
	else{
		//malloc a new node
		node_t* newNode = (node_t*)malloc(sizeof(node_t));

		//check if new node malloc was sucessful
		if(newNode == NULL){
			return 0;
		}
        newNode->data = item;
		//check if list is empty
		if(dll_empty(l) == 1){
			l->head = newNode;
			l->tail = newNode;
            newNode->previous = NULL;
            newNode->next = NULL;
   
		}
		else{
			newNode->previous = l->tail;
			l->tail->next = newNode;
			//rewire tail
			l->tail = newNode;
			//set last element to null
			l->tail->next = NULL;
		}
		//increment count
		l->count++;
		return 1;
	}
	return 0;
}

// Returns the first item in the DLL and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){
    //if dll is null return -1
	if(t == NULL){
		exit(1);
	}
	//the list has nothing to pop, return NULL
	if(dll_empty(t) == 1){
		return NULL;
	}
	//otherwise,
	//create variable to store data that will be returned 
	//and a temp node pointer to store the node that will be popped off
	void* tempData = t->head->data;
	node_t* tempHead = t->head;
	//if there are more than one node 
	if(t->count > 1){
	 	//move curr head ptr to next pos
		t->head = t->head->next;
		t->head->previous = NULL;
	}
	//if there is only one node in the list
	else{
		//set head and tail to NULL value
		t->head = NULL;
		t->tail = NULL;
	}
	//free memory in tempHead
	free(tempHead);
	//de-increment count 
	t->count--;
	//return data stored in previous node that was popped off
	return tempData;
}

// Returns the last item in the DLL, and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* t){
    //check if dll is null, if yes, exit program
	if(t == NULL){
		exit(1);
	}
	//if there is nothing in the list, return NULL to indicate faliure
	if(dll_empty(t) == 1){
		return NULL;
	}
	//create temp node to store data that will be popped off
	void* tempData = t->tail->data;
	//create a temp node to hold curr tail pos
	node_t* tempTail = t->tail;
	//if there is more than one node in the list
	if(t->count > 1){
		//rewire tail to tail's previous node in the list
		t->tail = t->tail->previous;
		//set tail next to null
		t->tail->next = NULL;
	}
	//if there is only one node in the list
	else{
		//set the head and the tail to NULL
		t->tail = NULL;
		t->head = NULL;
	}
	//free memory in tempTail
	free(tempTail);
	//de-increment count 
	t->count--;
	//return data stored in previous node that was popped off
	return tempData;
}

// Inserts a new node before the node at the specified position.
// Exits if the DLL is NULL
// Returns 1 on success
// Returns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, void* item){
   //if list is null, exit program
	if(l == NULL){
		exit(1);
	}
	//malloc a new node
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	//add data into new node
	newNode->data = item;
	//if memory could not be allocated, return 0
	if(newNode == NULL){
		return 0;
	}
	//if position of insert is greater then the number of nodes in the list
	//or position of insert is negative
	// return 0 to indicate faliure
	if(pos > l->count || pos < 0){
		return 0;
	}
	//if position of insert is equivalent to the number of nodes in the list
	//insert node to the back of list
    //return 1 to indicate success
	if(pos == l->count){
		//call push back
		dll_push_back(l, item);
		return 1;
	}
	if(pos == 0){
		//call push front
		dll_push_front(l, item);
		return 1;
	}
	//create pointers to hold the positions of the node before insertion 
	//and the node after insertion
	//set the node after insert to the head node
	node_t* nodeAfterInsert = l->head;
	node_t* nodeBeforeInsert;
	//create itr variable to iterate to position of node to insert infront
	int itr = 0;
	//while itr is less than position of insert, move node to next node, increment itr
	while(itr < pos){
		nodeAfterInsert = nodeAfterInsert->next;
		itr++;
	}
	//nodeAfterInsert is now pointing to node to insert in front of 
	//set nodeBeforeInsert to previous of nodeAfterInsert 
	nodeBeforeInsert = nodeAfterInsert->previous;
	//rewire nodeBeforeInsert to new node
	nodeBeforeInsert->next = newNode;
	//wire new node previous to node before insert
	newNode->previous = nodeBeforeInsert;
	//rewire node after insert to new node
	nodeAfterInsert->previous = newNode;
	//wire new node next to node after insert
	newNode->next = nodeAfterInsert;
	//increment dll node count 
	l->count++;
	//return 1 to indicate success 
	return 1;

}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
    //if there is nothing in the list, exit program
	if(l == NULL){
		exit(1);
	}
	//if position is past the size of the list or position is negative
	//return 0 to indicate faliure
	if(pos >= l->count || pos < 0){
		return NULL;
	}
	//if we get here, then position must be valid
	//declare variable and pointer to keep track of position of target node 
	int jump = 0;
	node_t* iterator = l->head;
	//cycle until iterator has reached target node
	while(jump < pos){
		iterator = iterator->next;
		jump++;
	}
	//return the data from target node
	return iterator->data;
}

//This helper function finds the position of a node in the dll
//Return Null if DLL is Null
//Return position of node in DLL
//Return -1 to indicate faliure
int dll_get_pos(dll_t* l, int item){
    //if there is nothing in the list, exit program
	if(l == NULL){
		exit(1);
	}
	//declare variable and pointer to keep track of position of target node 
	int jump = -1;
	node_t* itr = l->head;
	//cycle until iterator has reached target node
	while(itr != NULL){
		if(item != *(int*)itr->data){
			itr = itr->next;
			jump++;
		}
		else{
			return jump;
		}
	}
	return -1;
}
// This is a helper function
// Check if a given item is present in the DLL
// Returns 1 if found, 0 otherwise
// Exits if the DLL is NULL.
int dll_contains(dll_t* l, int item) {
    // check if list is NULL
    if (l == NULL) {
        exit(1);
    }

    // traverse the list to find the item
    node_t* current = l->head;
    while (current != NULL) {
        if (*(int*)current->data == item) {
            // item found
            return 1;
        }
        current = current->next;
    }

    // item not found
    return 0;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
    //if dll is is null, exit program
    if(l == NULL){
        exit(1);
    }
    //if position is unreachable (past the size of the list)
	if(pos >= l->count){
		return NULL;
	}
	//if position is the first node, call pop_front
	if(pos == 0){
		return dll_pop_front(l);
	}
	//if position is last node, call pop_back
	else if(pos == l->count -1){
		return dll_pop_back(l);
	}
	//iterate through list until target node is reached 
	else{
		int jump = 0;
		//create a temp node
		node_t* iterator = l->head;
		while(jump < pos){
			iterator = iterator->next;
			jump++;
		}
		//when we get here, target node has been reached
		//store iterator data
		void* tempData = iterator->data;
		//rewire nodes surrounding iterator node, disconnect iterator
		iterator->previous->next = iterator->next;
		iterator->next->previous = iterator->previous;
		//free data from iterator node
		free(iterator);
		//de-increment dll node count
		l->count --;
		//return temp data
		return tempData;
	}
}

// DLL Size
// Exits if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
    if(t == NULL){
		exit(1);
	}
	else if(dll_empty(t)== 1){
		return 0;
	}
	else{
		return t->count;
	}
}

// Free DLL
// Exits if the DLL is NULL.
// Removes a DLL and all of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t* t){
    if(t == NULL){
		exit(1);
	}
	else{
		//create a temp node t
		node_t* temp = t->head;
		//for each node in the list, free the data from memory
		while(t->head != NULL){
			temp = t->head;
			t->head = t->head->next;
			free(temp);
		}
		free(t);
	}
}

#endif
