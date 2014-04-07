#include <conio.h>
#include <iostream>
using namespace std;

void swap(int*,int*);
void swap(int&,int&);

int main() {

	int A,B;
	cout << "Enter A: ";
	cin >> A;
	cout << endl << "Enter B: ";
	cin >> B;
	cout << endl;
	
	swap(&A,&B); //int* a,b; a=&A; b=&B; swap(a,b);
	cout << A << " " << B << endl;
	
	swap(A,B); //int& a,b; a=A; b=B; swap(a,b);
	cout << A << " " << B << endl;
	
	_getch();
}

void swap(int* pA, int* pB){

	int temp;
	
	temp=*pA;
	*pA=*pB;
	*pB=temp;
	
	cout << "Pointer SWAP: ";
}

void swap(int& rA, int& rB){

	int temp;
	
	temp=rA;
	rA=rB;
	rB=temp;
	
	cout << "Reference SWAP: ";
}

	