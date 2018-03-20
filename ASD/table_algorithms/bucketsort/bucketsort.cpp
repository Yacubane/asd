#include <iostream>
#include <stdlib.h>
#include <ctime>
/**
	Structure of list node
*/
struct Node{
	float value;
	Node* next;
};
/**
	Structure of linked list
*/
struct List{
	Node* first;
};
/**
	Prints whole array
	
	@param A[] - array
	@param n - size of array
*/
void printArray(double A[], int n){
	for(int i = 0; i < n; i++){
		std::cout << A[i] << " ";
	}
}
/**
	Initalizes new list
	
	@param list - list to be initalized
*/
void initList(List &list){
	list.first=new Node;
	list.first->next=NULL;
}
/**
	Adds element on start of list
	Warning, this function needs sentinel at start of list!

	@param list - list, where element will be added
	@param value - value to be added
*/
void addToList(List &list, double value){
	Node* node = new Node;
	node->value=value;
	node->next=list.first->next;
	list.first->next=node;
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
	Sorts array of size n with k buckets
	
	@param A[] - array to be sorted
	@param n - size of array
	@param k - number of buckets

*/
void bucketsort(double A[], int n, int k){
	List buckets[k];
	for (int i=0; i<k; i++) initList(buckets[i]);
	for (int i=0; i<n; i++) addToList(buckets[(int)(A[i]*k)],A[i]);
	for (int i=0; i<k; i++) insertSort(buckets[i]);

	int j = 0;
	for(int i = 0; i < k; i++){
		Node* node = buckets[i].first;
		while(node->next!=NULL){
			A[j]=node->next->value;
			j++;
			Node* toDelete = node;
			node=node->next;
			delete toDelete;
		}
		delete node;
	}
}

int main(int argc, char** argv) {
	srand(time(NULL));
	//EXAMPLE USAGE OF ALGORITHM		
	int n = 10;
	double tab[n];
	
	for(int i = 0; i < n; i++){
		tab[i]=rand() /(double) (RAND_MAX+1);
	}
	std::cout << std::endl << "ARRAY" << std::endl;

	printArray(tab,n);

	bucketsort(tab, n, 5);

	std::cout << std::endl << "SORTED ARRAY" << std::endl;
	printArray(tab,n);
	return 0;
}

