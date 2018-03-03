#include <iostream>
#include <stdlib.h>

/**
	Structure of linked-list
*/
struct Node{
    int value;
    Node *next;
};

/**
    Returns size of list (number of elements)

    @param *list - pointer to first element of list
    
    @return an integer with number of elements
*/
int getSizeOfList(Node* list){
	int counter = 0;
	while(list != NULL){
		counter++;
		list=list->next;
	}
	return counter;
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

    @param *list - pointer to first element of list
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

/**
    Merges two sorted lists (without guardian)

    @param *list1 - pointer to first element of first list
    @param *list2 - pointer to first element of second list
    
    @return a first pointer of new sorted list
*/
Node* mergeSortedLists(Node *list1, Node *list2){
	Node* first=new Node; //first guardian of sorted final list (temporary)
	Node* current=first; //current node in final list
	while(list1!=NULL || list2!=NULL){
		if(list1!=NULL && list2==NULL){
			current->next = list1;
			current=current->next;
			list1=list1->next;
		}
		else if(list1==NULL && list2!=NULL){
			current->next = list2;
			current=current->next;
			list2=list2->next;
		}
		else {
			if(list1->value < list2->value){
				current->next=list1;
				current=current->next;
				list1=list1->next;
			}
			else {
				current->next=list2;
				current=current->next;
				list2=list2->next;
			}
		}
		
	}
	return first->next; //returns next element after guardian
}

/**
    Splits lists using "Tortoise and Hare Algorithm".
	Pointer in function argument will be a pointer of first "splited" list.

    @param *list - pointer to first element of list
    
    @return a pointer of second list
*/
Node* splitList(Node* list){
	Node* slow = list;
	Node* fast = list;
	while(fast->next != NULL && fast->next->next !=NULL){
		slow=slow->next;
		fast=fast->next->next;
	}
	Node* secondListPtr = slow->next;
	slow->next=NULL;
	return secondListPtr;
}

/**
    Sorts list (without guardian) using a recursive merge sort algorithm

    @param *list1 - pointer to first element of list
    
    @return a pointer to sorted list
*/
Node* mergeSort(Node* list1){
	if(getSizeOfList(list1)>1){
		Node* list2 = splitList(list1);
		Node* sortedList1 = mergeSort(list1);
		Node* sortedList2 = mergeSort(list2);
		return mergeSortedLists(sortedList1,sortedList2);
	}
	return list1;
}

int main(int argc, char** argv) {

	//EXAMPLE OF ALGORITHM		
	Node* testList = new Node;
	testList->next=NULL; //must be NULL in order to detect end of list
	testList->value=0;
	for(int i = 0; i < 100; i++){
		addNode(testList,rand());
	}

	Node* finalList = mergeSort(testList);
	printList(finalList);

	return 0;
}

