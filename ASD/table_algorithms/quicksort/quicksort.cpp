#include <iostream>
#include <stdlib.h>
#include <ctime>

/**
	Swaps array elements with indexes "i" and "j"
	
	@param A[] - array
	@param i - index of first element
	@param j - index of second element
*/
void swap(int A[], int i, int j){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

/**
	Takes pivot as element with index "r" and moves all elements less than "r"-th element on the left side.
	As a result pivot element is on right sorted position, less elements are on left side from pivot and higher elements are on right side.
	
	@param A[] - array to be partitioned
	@param p - index of first element
	@param r - index of last element
	
	@returns index of pivot
*/
int partition(int A[], int p, int r){
	int x = A[r];
	int i = p;
	for(int j = p; j <= r-1; j++){
		if(A[j]<=x){
			swap(A,i,j);
			i++;
		}
	}
	swap(A, i, r) ;
	return i;
}

/**
	Quicksorts array in selected range
	Example usage: to sort whole array quicksort(array, 0, array.length-1);
	
	@param A[] - array to be sorted
	@param p - index of first element to be sorted
	@param r - index of last element to be sorted
*/
void quicksort(int A[], int p, int r){
	if(p < r){
		int q = partition(A, p ,r);
		quicksort(A, p, q-1);
		quicksort(A, q+1, r);
	}

}

/**
	Quicksorts array in selected range
	Example usage: to sort whole array quicksort(array, 0, array.length-1);
	
	@param A[] - array
	@param n - size of array
*/
void printArray(int A[], int n){
	for(int i = 0; i < n; i++){
		std::cout << A[i] << " ";
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
	std::cout << std::endl << "ARRAY" << std::endl;

	printArray(tab,n);

	std::cout << std::endl << "SORTED ARRAY" << std::endl;
	quicksort(tab,0,n-1);
	printArray(tab,n);
	return 0;
}

