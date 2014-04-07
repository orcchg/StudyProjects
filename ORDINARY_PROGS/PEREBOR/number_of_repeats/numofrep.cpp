#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
	int N,k=0,i=0;
	cout << "Enter N: "; cin >> N; cout << endl;
	cout << endl << "Enter numbers: " << endl;
	
	/*int* A = new int[N];
	int* B = new int[N];
	int* C = new int[N];*/
	int A[N],B[N],C[N];
	
	for(int i = 0; i < N; i++) {
		cout << (i+1) << ": ";
		cin >> A[i];
		cout << endl;
	}
	
	for(int i = 0; i < N; i++) {
		C[i] = 1;
	}
	
	while(i < N-1){
		if(A[i] != -999) {
			for(int j = i+1; j < N; j++) {
				if(A[i] == A[j]) {
					B[k] = A[j];
					A[j] = -999;
					C[k] = C[k] + 1;
					k++;
				} 
			}
			//k++; 
			i++;
		} else { 
			i++; 
		}
	}
	cout << "k = " << k << endl;
	
	for(int i = 0; i < k; i++) {
		cout << C[i] << ":  " << B[i] << endl;
	}
	
	_getch();
}