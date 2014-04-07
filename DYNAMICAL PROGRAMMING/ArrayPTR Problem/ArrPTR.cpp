#include <conio.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//---------------------------------------------
int max(int* pA, int L, int R) {
	
	int max = pA[L];
	for(int i = L + 1; i <= R; ++i) {
		if (pA[i] > max) {
			max = pA[i];
		}
	}
	return max;
}
//---------------------------------------------


/*********************************************/
int main()
{
	int n;
	cin >> n;
	
	int* A = new int[n];
	for(int i = 0; i < n; ++i) {
		cin >> A[i];
	}
	
	cin.ignore();
	
	int m;
	cin >> m;
	
	char* P = new char[m];
	for(int i = 0; i < m; ++i) {
		cin >> P[i];
	}
//----------------------------------------
	
//	int* L = &A[0];
//	int* R = &A[0];
	int l = 0;
	int r = 0;
	
	for(int i = 0; i < m; ++i) {
		switch(P[i]) {
			case 'L':
//				++L;
				++l;
				cout << max(A, l, r) << " ";
				break;
			case 'R':
//				++R;
				++r;
				cout << max(A, l, r) << " ";
				break;
		}
	}
//----------------------------------------

	_getch();
	return 0;
}
/*********************************************/
// Teta(n*m);