#include <iostream>
#include <stdlib.h>
#include <ctime>

int leftChild(int index){
	return index*2;
}
int rightChild(int index){
	return index*2 + 1;
}
int parent(int index){
	return index/2;	
}
void heapify(int arr[], int index){
	int size = arr[0];
	int largest = index;
	int left = leftChild(index);
	int right = rightChild(index);
	if(left <= size && arr[left] > arr[largest]) largest=left;
	if(right <= size && arr[right] > arr[largest]) largest=right;
	if(largest != index){
		std::swap(arr[largest], arr[index]);
		heapify(arr,largest);
	}
}
void buildHeap(int arr[], int n){
	arr[0]=n-1;
	for(int i = (n-1)/2; i>=1; i--){
		heapify(arr,i);
	}
}
int heapsort(int arr[], int n){
	buildHeap(arr, n);
	for(int i = n-1; i>1; i--){
		std::swap(arr[1], arr[i]);
		arr[0]--;
		heapify(arr,1);
	}
}
int extractmax(int arr[]){
	if(arr[0]==0) exit(1); //there are no elements in queue
	int result = arr[1];
	arr[1]=arr[arr[0]];
	arr[arr[0]]=0;
	arr[0]--;
	heapify(arr,1);
	return result;
}
void insert(int arr[], int n, int key){
	if(arr[0] == n-1) exit(1); //queue is full
	arr[++arr[0]]=key;
	int i = arr[0];
	while(i>1 && arr[i]>arr[parent(i)]){
		std::swap(arr[i], arr[parent(i)]);
		i=parent(i);
	}
}
void printProrityQueue(int arr[]){
	std::cout << "Prority queue: ";
	for(int i = 1; i <= arr[0]; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
int main(int argc, char** argv) {
	srand(time(NULL));
	//EXAMPLE USAGE OF ALGORITHM		
	int n = 5;
	int arr[n];
	arr[0] = 0; //in this place, a size of elements will be stored

	for(int i = 0; i < n-1; i++){
		int prority = rand();
		std::cout << "Inserting prority: " << prority << std::endl;
		insert(arr,n,prority);
		printProrityQueue(arr);
	}	
	for(int i = 0; i < n-1; i++){
		int extracted = extractmax(arr);
		std::cout << "Extracting: " << extracted << std::endl;
		printProrityQueue(arr);
	}

	return 0;
}
