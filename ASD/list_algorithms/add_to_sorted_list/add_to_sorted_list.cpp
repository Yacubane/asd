#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <ctime>


/**
	Structure of linked-list
*/
struct Node{
    int value;
    Node *next;
};

/**
    Adds element to sorted list (and list remains sorted)
    
    @param *list - pointer to first element to list
    @param *node - pointer to element, which you want to be added

*/
void addElementToSortedList(Node*& list, Node* node){
	Node* guard = new Node;
	guard->next=list;	
	list=guard;
	while(list->next!=NULL){
		if(list->next->value > node->value){
			node->next=list->next;
			list->next=node;
			list=guard->next;
			delete guard;
			return;
		}
		list=list->next;
	}
	list->next=node;
	list=guard->next;
	delete guard;
}

/**
    Prints all values from list

    @param *list - pointer to first element of list
*/
void printList(Node* list){
	while(list!=NULL){
		std::cout << list->value;
		std::cout << " ";
		list = list->next;
	}
}

/**
    Adds element at the end of list

    @param *list - pointer to any element of list (in most usages - head element)
    @param *value - value, that will be added to last element
*/
void addNode(Node* list, int value){
	while(list!=NULL){
		if(list->next == NULL){
			Node* newNode = new Node;
			newNode->value = value;
			newNode->next = NULL;
			list->next = newNode;
			return;
		}
		list = list->next;
	}
}


int main(int argc, char** argv) {

	srand(time(NULL));
	//EXAMPLE OF ALGORITHM		
	Node* testList = new Node;
	testList->next=NULL; //must be NULL in order to detect end of list
	testList->value=2;
	addNode(testList,3);
	addNode(testList,5);
	addNode(testList,6);
	addNode(testList,7);
	addNode(testList,8);
	
	Node* newElement = new Node;
	newElement->value=4;
	newElement->next=NULL;
	
	addElementToSortedList(testList,newElement);
	printList(testList);
	return 0;
}

