#include <conio.h>
#include <iostream>
using namespace std;

int MAX(int,int*);

int main()
{
	int N,m1,m2,m3;
	cout << "Enter N: ";
	cin >> N;
	cout << endl;
	cout << "Enter numbers: " << endl;
	
	int A[N];
	int* ptr = A;
	
	for(int i = 0; i < N; i++) {
		cout << (i+1) << ": ";
		cin >> A[i];
		cout << endl;
	}
	
	m1 = MAX(N/3,ptr);
	m2 = MAX(N/3,ptr+1+N/3);
	m3 = MAX(N/3,ptr+1+2*N/3);
	
	cout << m1 << " " << m2 << " " << m3 << endl;
	_getch();
}

int MAX(int N,int* A)
{
	int max = *A;
	for(int i = 1; i < N; i++) {
		if(A[i] > max) {
			max = A[i];
		}
	}
	
	return max;
}
	