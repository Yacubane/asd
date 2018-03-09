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

int main(int argc, char** argv) {
	srand(time(NULL));
	//EXAMPLE USAGE OF ALGORITHM		
	int n = 10;
	int tab[n];
	
	for(int i = 0; i < n; i++){
		tab[i]=rand();
	}
	std::cout << "Printing non-sorted array" << std::endl;
	for(int i = 1; i < n; i++){
		std::cout << tab[i] << " ";
	}
	std::cout<<std::endl;
	heapsort(tab,n);
	std::cout << "Printing array" << std::endl;
	for(int i = 1; i < n; i++){
		std::cout << tab[i] << " ";
	}
	return 0;
}
