#include <iostream>
#include <stdlib.h>
#include <ctime>
struct Node{
	float value;
	Node* next;
};
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
void printList(Node* list){
	while(list!=NULL){
		std::cout << list->value;
		std::cout << " ";
		list = list->next;
	}
}
/**
	Quicksorts array in selected range
	Example usage: to sort whole array quicksort(array, 0, array.length-1);
	
	@param A[] - array to be sorted
	@param p - index of first element to be sorted
	@param r - index of last element to be sorted
*/
void initList(List &lista){
	lista.first=new Node;
	lista.first->next=NULL;
}

void addToSortedList(List &lista, float val ){
	Node* node = lista.first;
	while(node->next!=NULL){
		if(node->next->value > val){
			Node* newNode = new Node;
			newNode->value=val;
			newNode->next=node->next;
			node->next=newNode;
			return;
		}
		node=node->next;
	}
	Node* newNode = new Node;
	newNode->value=val;
	newNode->next=NULL;
	node->next=newNode;
	return;
}

void bucketsort(double A[], int n, int k){
	List buckets[k];
	for (int i=0; i<k; i++) initList(buckets[i]);
	for (int i=0; i<n; i++) addToSortedList(buckets[(int)(A[i]*k)],A[i]);
	
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
		tab[i]=rand() /(double) RAND_MAX;
	}
	std::cout << std::endl << "ARRAY" << std::endl;

	printArray(tab,n);

	bucketsort(tab, n, 10);

	std::cout << std::endl << "SORTED ARRAY" << std::endl;
	printArray(tab,n);
	return 0;
}

