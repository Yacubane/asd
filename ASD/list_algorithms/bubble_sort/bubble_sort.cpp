#include <iostream>

using namespace std;

struct Node{
	Node* next; 
	double value;
};
void addNode(Node* node, int val){
	while(node!=NULL){
		if(node->next == NULL){
			Node* newNode = new Node;
			newNode->value = val;
			newNode->next = NULL;
			node->next = newNode;
			return;
		}
		node = node->next;
	}
	
}
void printList(Node* node){
	node = node->next;
	while(node!=NULL){
		cout << node->value;
		cout << " ";
		node = node->next;
	}
}
int getNumberOfElements(Node* node){
	int size = 0;
	node=node->next;
	while(node!=NULL){
		node=node->next;
		size++;
	}
	return size;
}

bool oneIterateBubbleSort(Node* first){
	bool changed=false;
	Node* prev_prevNode = first;
	Node* prevNode = first->next;
	if(prevNode == NULL) return false;
	Node* nextNode = prevNode->next;
	while(nextNode!=NULL){
		if(prevNode->value > nextNode->value){
			prev_prevNode->next = nextNode;
			prevNode->next=nextNode->next;
			nextNode->next = prevNode;
			
			Node* prevNodeCopy = prevNode;
			prevNode=nextNode;
			nextNode=prevNodeCopy;
			
			prev_prevNode=prev_prevNode->next;
			prevNode=prevNode->next;
			nextNode=nextNode->next;
			changed=true;
		}
		else {
			prev_prevNode=prev_prevNode->next;
			prevNode=prevNode->next;
			nextNode=nextNode->next;
		}
		
	}
	return changed;
}
void bubbleSort(Node* node){
    //Note - this function must have guardian as first node
	bool changed=true;
	while(changed){
		changed = oneIterateBubbleSort(node);
	}
}
int main(int argc, char** argv) {
    
    //Example usage of algorithm
	Node* node = new Node;
	node->next=NULL;
	addNode(node,9);
	addNode(node,5);
	addNode(node,6);
	addNode(node,10);
	addNode(node,6);

	printList(node);
	bubbleSort(node);
	cout << endl;
	printList(node);

	return 0;
}
