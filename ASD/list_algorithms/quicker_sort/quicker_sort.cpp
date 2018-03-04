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
    Splits list by selected value

    @param *head - pointer to first element of list
    @param x - value, by which lists will be sorted
    @param *&lessFirstNode - reference to pointer, where pointer of first list (elements less than x) will be stored
    @param *&exactlyFirstNode - reference to pointer, where pointer of first list (elements exactly than x) will be stored
    @param *&higherFirstNode - reference to pointer, where pointer of first list (elements higher than x) will be stored
*/
void partition(Node* head, int x, Node*& lessFirstNode, Node*& exactlyFirstNode, Node*& higherFirstNode)
{	
	Node* current = head;
	lessFirstNode = NULL;
	exactlyFirstNode=NULL;
	higherFirstNode = NULL;
	while(current!=NULL){
		Node* nodeToBePinned = current;
		current=current->next;
		if(nodeToBePinned->value < x){
			nodeToBePinned->next=lessFirstNode;
			lessFirstNode=nodeToBePinned;
		}
		else if(nodeToBePinned->value > x){
			nodeToBePinned->next=higherFirstNode;
			higherFirstNode=nodeToBePinned;	
		}
		else {
			nodeToBePinned->next=exactlyFirstNode;
			exactlyFirstNode=nodeToBePinned;
		}
	}
}
/**
    Adds list to list

    @param *list1 - pointer to first element of list, where elements will be added
    @param *list2 - pointer to first element of list, from where elements will be taken

    @return a pointer to last element of list1
*/
Node* addListToList(Node* list1, Node* list2){
	while(list2!=NULL){
		list1->next=list2;
		list2=list2->next;
		list1=list1->next;
	}
	return list1;
}
/**
    Merges three lists

    @param *list1 - pointer to first element of list1
    @param *list2 - pointer to first element of list2
    @param *list3 - pointer to first element of list3

    @return a pointer to merged list
*/
Node* mergeThreeLists(Node* list1, Node* list2, Node* list3){
	Node* guardian = new Node;
	guardian->next=NULL;
	Node* current = guardian;
	current=addListToList(current,list1);
	current=addListToList(current,list2);
	current=addListToList(current,list3);
	return guardian->next;
	
}
/**
    Quickly sorts 

    @param *list - pointer to first element of list

    @return a pointer to sorted list
*/
Node* quickersort(Node* list){
	if(list==NULL) return NULL;
	Node* lessFirstNode = NULL;
	Node* exactlyFirstNode=NULL;
	Node* moreFirstNode = NULL;
	partition(list,list->value,lessFirstNode,exactlyFirstNode,moreFirstNode);
	Node* list1 = quickersort(lessFirstNode);
	Node* list2 = quickersort(moreFirstNode);
	return mergeThreeLists(list1,exactlyFirstNode,list2);
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


int main(int argc, char** argv) {

	srand(time(NULL));
	//EXAMPLE OF ALGORITHM		
	Node* testList = new Node;
	testList->next=NULL; //must be NULL in order to detect end of list
	testList->value=rand();
	for(int i = 0; i < 10; i++){
		addNode(testList,rand());
	}
	printList(testList);

	std::cout << std::endl << "SORTED LIST" << std::endl;

	Node* sorted = quickersort(testList);
	printList(sorted);
	return 0;
}

