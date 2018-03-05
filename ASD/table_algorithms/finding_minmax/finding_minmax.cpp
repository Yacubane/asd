#include <iostream>

using namespace std;

/**
    Finds and prints min and max value from table with only 3/2 * n "if" operations
    
    @param tab[] - array
    @param n - size of array
*/
void findMinAndMax(int tab[], int n){
	int min = tab[0];
	int max = tab[0];
	
	for(int i = n%2; i < n; i+=2){ //n%2 for even and odd array size
		if(tab[i] > tab[i+1]){
			if(tab[i] > max) max = tab[i];
			if(tab[i+1] < min) min = tab[i+1];
		}
		else {
			if(tab[i+1] > max) max = tab[i+1];
			if(tab[i] < min) min = tab[i];
		}
	}
	cout << "MIN: " << min << endl;
	cout << "MAX: " << max << endl;
}
int main(int argc, char** argv) {
	int tab[] = {9,3,6,2,4,8};
	findMinAndMax(tab,6);
	return 0;
}
