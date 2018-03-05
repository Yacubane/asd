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
    Adds list to list

    @param *list1 - pointer to any element of list, where elements will be added
    @param *list2 - pointer to first element of list, from where elements will be taken

    @return a pointer to last element of list1
*/
Node* addListToList(Node* list1, Node* list2){
	while(list1->next!=NULL){
		list1=list1->next;
	}
	list1->next=list2;
	return list1;
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
	testList->value=rand();
	for(int i = 0; i < 5; i++){
		addNode(testList,rand());
	}
	std::cout << std::endl << "LIST1" << std::endl;
	printList(testList);
	
	Node* testList2 = new Node;
	testList2->next=NULL; //must be NULL in order to detect end of list
	testList2->value=rand();
	for(int i = 0; i < 5; i++){
		addNode(testList2,rand());
	}
	std::cout << std::endl << "LIST2" << std::endl;
	printList(testList2);

	std::cout << std::endl << "LIST 1 + 2" << std::endl;

	Node* sorted = addListToList(testList,testList2);
	printList(testList);
	return 0;
}

