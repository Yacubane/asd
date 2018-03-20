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

void iterativeQuicksort(int A[], int n){
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
int pow(int a, int b){ //a^b
	int res = 1;
	for(int i = 0; i < b; i++){
		res*=a;
	}
	return res;
}
void zad3(std::string s, int k){
	int n = s.length();
	int counterSize = pow(2,k);
	int counter[counterSize];
	for(int i = 0; i < counterSize; i++) counter[i]=0;
	for(int i = 0; i < (n-k+1); i++){
		int sum = 0;
		int exp=1;
		for(int j = i+k-1; j >= i; j--){
			sum+=exp*(s[j]-'a');
			exp*=2;
		}
		counter[sum]++;
		std::cout << std::endl;
	}
	int maxCounterID = 0;
	for(int i = 0; i < counterSize; i++)
		if(counter[i]>counter[maxCounterID]) maxCounterID = i;
	
	std::string output;
	int maxCounterIDtmp = maxCounterID;
	for(int i = 0; i < k; i++){
		output+=maxCounterIDtmp%2+'a';
		maxCounterIDtmp/=2;
	}
	std::cout << "Szukany ci¹g to " << output << ", liczba wystapien:" << counter[maxCounterID];
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
	iterativeQuicksort(tab,n);
	printArray(tab,n);
	
	
	zad3("ababaaabb",3);
	return 0;
}

