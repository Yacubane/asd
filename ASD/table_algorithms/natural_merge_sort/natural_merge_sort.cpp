#include <iostream>
#include <stdlib.h>
#include <ctime>

void printArray(int A[], int n){
	for(int i = 0; i < n; i++){
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;
}
int find_ser(int t[], int j, int n){
	for(int i=j+1; i<n; i++){
		if(t[i] < t[i-1]){
			return i;
		}
	}
	return n;
}
void merge(int t1[], int t2[], int p1, int k1, int p2, int k2){
	int i = p1;
	int i1 = p1;
	int i2 = p2;
	while(i1 < k1 && i2 < k2){
		if(t1[i1] < t1[i2]){
			t2[i++]=t1[i1++];
		}
		else {
			t2[i++]=t1[i2++];
		}
	}
	while(i1 < k1) t2[i++]=t1[i1++];
	while(i2 < k2) t2[i++]=t1[i2++];
}
void natural_merge_sort(int t[], int n){
	int *t2 = new int[n];
	int p1,p2,k1,k2;
	p1=0;
	
	while(true){
		k1=find_ser(t,p1,n);
		if(p1==0 && k1==n) break;
		p2=k1;
		if(p2==n) k2=n; else k2 = find_ser(t,p2,n);
		merge(t,t2,p1,k1,p2,k2);
		if(k2 == n){
			for(int i = 0; i < n; i++){
				t[i]=t2[i];
			}
			p1=0;
		}
		else {
			p1=k2;
		}
	}
	delete [] t2;
}
int main(int argc, char** argv) {
	srand(time(NULL));
	//EXAMPLE USAGE OF ALGORITHM		
	int n = 10;
	int tab[n];
	
	for(int i = 0; i < n; i++){
		tab[i]=rand();
	}
	std::cout << std::endl << "ARRAY " << std::endl;
	printArray(tab,n);

	std::cout << std::endl << "SORTED ARRAY" << std::endl;
	natural_merge_sort(tab,n);
	printArray(tab,n);
	return 0;
}

