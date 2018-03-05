#include <iostream>

using namespace std;
struct Node{
	int value;
	Node* next;
};
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
void printList(Node* list){
	while(list!=NULL){
		cout << list->value;
		cout << " ";
		list = list->next;
	}
}
Node* getReverseList(Node* first){
	Node* current = first;
	current=current->next;
	first->next=NULL;
	while(current != NULL){
		Node* tmp = current;
		current=current->next;
		tmp->next = first;
		first=tmp;	
	}
	return first;
}
int main(int argc, char** argv) {
	Node* list = new Node;
	list->value=0;
	list->next=NULL;
	for(int i = 1; i < 10; i++)
		addNode(list, i);
	Node* list2 = getReverseList(list);

	printList(list2);


	return 0;
}
