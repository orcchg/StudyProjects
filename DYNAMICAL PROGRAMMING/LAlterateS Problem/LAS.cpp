#include <iostream>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;


//------------------------------------------------------
int max_L(int* up, int* down, int length) {

	int L = up[length - 1];
	int temp = 0;
	
	for(int i = length - 1; i >= 0; --i) {
		temp = (up[i] > down[i]) ? up[i] : down[i];
		L = (L > temp) ? L : temp;
	}
	return L;
}
//------------------------------------------------------

//------------------------------------------------------
int max_Up(int* pA, int* Dw, int L, int R) {
	
	int max = 0;
	for(int j = R; j > L; --j) {
		if (pA[j] > pA[L]) {
			if (Dw[j] > max) {
				max = Dw[j];
			}
		}
	}
	return max;
}
//------------------------------------------------------

//------------------------------------------------------
int max_Dw(int* pA, int* Up, int L, int R) {
	
	int max = 0;
	for(int j = R; j > L; --j) {
		if (pA[j] < pA[L]) {
			if (Up[j] > max) {
				max = Up[j];
			}
		}
	}
	return max;
}
//------------------------------------------------------


/*******************************************************/
int main()
{
	int n;
	cin >> n;
	
	int* A = new int[n];
	for (int i = 0; i < n; ++i) {
		cin >> A[i];
	}
//----------------------------------------
	
	int* up = new int[n];
	int* down = new int[n];
	for (int i = 0; i + 1 < n; ++i) {
		up[i] = down[i] = 0;
	}
	
	up[n-1] = down[n-1] = 1;
	
	for(int i = n - 2; i >= 0; --i) {
		up[i] = max_Up(A, down, i, n - 1) + 1;
		down[i] = max_Dw(A, up, i, n - 1) + 1;
	}
	
	for(int i = 0; i < n; ++i) {
		cout << up[i] << " ";
	}
	cout << "    :UP\n";
	
	for(int i = 0; i < n; ++i) {
		cout << down[i] << " ";
	}
	cout << "  :DOWN\n";
	
	int L;
	L = max_L(up, down, n);
	
	cout << endl << "L:  " << L << endl;
//----------------------------------------
	
	int* ans = new int[L];
	if (up[0] >= down[0]) {
		for(int i = 0; i < n; ++i) {
			if (up[i] == L) {
				ans[0] = i;
				break;
			}
		}
		
		int K = L, index = 0;
		while (K > 0) {
			--K;
			for(int i = ans[index] + 1; i < n; ++i) {
				if (down[i] == K && A[i] > A[ans[index]]) {
					ans[++index] = i;
					break;
				}
			}
			
			--K;
			if (K == 0) {
				break;
			}
			
			for(int i = ans[index] + 1; i < n; ++i) {
				if (up[i] == K && A[i] < A[ans[index]]) {
					ans[++index] = i;
					break;
				}
			}
		}
	//------------------------------	
	
	} else {
		for(int i = 0; i < n; ++i) {
			if (down[i] == L) {
				ans[0] = i;
				break;
			}
		}
		
		int K = L, index = 0;
		while (K > 0) {
			--K;
			for(int i = ans[index] + 1; i < n; ++i) {
				if (up[i] == K && A[i] < A[ans[index]]) {
					ans[++index] = i;
					break;
				}
			}
			
			--K;
			if (K == 0) {
				break;
			}
			
			for(int i = ans[index] + 1; i < n; ++i) {
				if (down[i] == K && A[i] > A[ans[index]]) {
					ans[++index] = i;
					break;
				}
			}
		}
	}
	//------------------------------
	
	cout << "ANS:  ";
	for(int i = 0; i < L; ++i) {
		cout << A[ans[i]] << " ";
	}
			
//----------------------------------------	

	_getch();
	return 0;
}
/*******************************************************/