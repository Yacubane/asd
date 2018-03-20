#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <limits.h>
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
	Merges sorted sub-arrays. Based on Cormen's implementation.
	
	@param A[] - array
	@param p - index of first element
	@param q - index of middle element
	@param r - index of last element
*/
void merge(int A[], int p, int q, int r){
	int n1 = q - p + 1;
	int n2 = r - q;
	int left[n1+1];
	int right[n2+1];
	for(int i = 0; i < n1; i++){
		left[i] = A[p+i];
	}
	
	for(int i = 0; i < n2; i++){
		right[i] = A[q+i+1];
	}
	
	left[n1]  = INT_MAX;
	right[n2] = INT_MAX;
	int i = 0, j = 0;
	for(int k = p; k <= r;k++){
		if(left[i] <= right[j]){
			A[k] = left[i++];
		}
		else{
			A[k] = right[j++];
		}
	}
}


/**
	Sorts array. Based on Cormen's implementation.
	
	@param A[] - array
	@param p - index of first element
	@param r - index of last element
*/
void mergeSort(int A[], int p, int r){
	if(p < r){
		int q = (p+r)/2;
		mergeSort(A, p, q);
		mergeSort(A, q+1, r);
		merge(A, p, q, r);
	}
}

/**
	Prints whole array
	
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
	mergeSort(tab,0,n-1);
	printArray(tab,n);
	return 0;
}
