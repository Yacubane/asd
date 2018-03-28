/**
Dana jest struktura opisuj¹ca listê jednokierunkow¹ dla liczb rzeczywistych:
struct Node{ Node* next; double value; }
Proszê zaimplementowaæ funkcjê void Sort( Node* list ), która otrzymuje na wejœciu listê
liczb rzeczywistych (z wartownikiem), wygenerowan¹ zgodnie z rozk³adem jednostajnym na
przedziale [0,10) i sortuje jej zawartoœæ w kolejnoœci niemalej¹cej. Funkcja powinna byæ mo¿liwie
jak najszybsza (bior¹c pod uwagê warunki zadania). Proszê oszacowaæ z³o¿onoœæ
zaimplementowanej funkcji.
*/

#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <ctime>


/**
	Structure of linked-list
*/
struct Node{
    double value;
    Node *next;
};
struct List{
	Node* first;
};

/**
	Initalizes new list
	
	@param list - list to be initalized
*/
void initList(List &list){
	list.first=new Node;
	list.first->next=NULL;
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
	Adds element on start of list
	Warning, this function needs sentinel at start of list!

	@param list - list, where element will be added
	@param Node - node to be added
*/
void addToList(List &list, Node* node){
	node->next=list.first->next;
	list.first->next=node;
}
/**
    Adds element at the end of list

    @param *list - pointer to first element of list
    @param *value - value, that will be added to last element
*/
void addNode(Node* list, double value){
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
	Adds node to sorted list. List remains sorted
	Warning, this function needs sentinel at start of list!
	
	@param list - list, where element will be added
	@param node - element to be added
*/
void addToSortedList(Node* list, Node* node){
	while(list->next!=NULL){
		if(list->next->value > node->value){
			node->next=list->next;
			list->next=node;
			return;
		}
		list=list->next;
	}
	node->next=NULL;
	list->next=node;
	return;
}
/**
	Sorts list with insert sort algorithm.
	Warning, this function needs sentinel at start of list!
	
	@param list - list
*/
void insertSort(List &list){
	Node* secondList = list.first;
	Node* node = secondList->next;
	secondList->next=NULL;
	while(node!=NULL){
		Node* tmp = node;	
		node=node->next;
		addToSortedList(secondList,tmp);	
	}
}

/**
	Bucket sort
*/
void sort(Node*& list){
	int k = 0; //size of list
	Node* node = list;
	while(node!=NULL){
		k++;
		node=node->next;
	}
	
	List buckets[k];
	for (int i=0; i<k; i++) initList(buckets[i]);
	while(list!=NULL){
		Node* tmp = list;
		list=list->next;
		addToList(buckets[(int)(tmp->value)],tmp);
	}
	for (int i=0; i<k; i++) insertSort(buckets[i]);
	
	int j = 0;
	
	Node* listHead = buckets[0].first;
	Node* currentList = listHead;
	while(currentList->next!=NULL){
		currentList=currentList->next;
	}
	for(int i = 1; i < k; i++){
		currentList->next=buckets[i].first->next;
		while(currentList->next!=NULL){
			currentList=currentList->next;
		}
	}
	list = listHead->next;
	for(int i = 0; i < k; i++){
		Node* node = buckets[i].first;
		delete node;
	}
}

double generateRandomNumber(){
	return 10.0*rand()/(RAND_MAX+1);
}
int main(int argc, char** argv) {

	srand(time(NULL));
	//EXAMPLE OF ALGORITHM		
	Node* testList = new Node;
	testList->next=NULL; //must be NULL in order to detect end of list
	testList->value=generateRandomNumber();
	for(int i = 0; i < 10; i++){
		addNode(testList,generateRandomNumber());
	}
	printList(testList);
	sort(testList);
	std::cout << std::endl << "SORTED LIST" << std::endl;
	printList(testList);

	return 0;
}

