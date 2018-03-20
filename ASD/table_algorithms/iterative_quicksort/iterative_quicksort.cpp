#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string.h>

struct stos {
	int* t;
	int size;
};
void init(stos &st, int size) {
	st.t = new int[size];
	st.size=0; 
}
void push(stos &st, int el) { st.t[st.size++]=el; }
int pop(stos &st) { return st.t[--st.size]; }
bool empty(stos &st) { return (st.size==0); }


void swap(int A[], int i, int j){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

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

void iterative_quicksort(int A[], int n){
	int l,p;
	stos st;
	init(st,n);
	push(st,0); push(st,n-1);
	while(!empty(st)){
		p=pop(st); l=pop(st);

		int q = partition(A,l,p);

		if(l<q-1){				
			push(st,l); push(st,q-1);
		} 
		if(p>q+1){
			push(st,q+1); push(st,p);
		} 
	}
	delete [] st.t;
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
	iterative_quicksort(tab,n);
	printArray(tab,n);
	
	return 0;
}

