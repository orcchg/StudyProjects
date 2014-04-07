#include <iostream>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;

//--------------------------------------------
struct Cube {
	int a;
	int b;
	int c;
};
//--------------------------------------------

//--------------------------------------------
bool is_include(Cube* C, int i, int j) {
	
	return ( (C[i].a < C[j].a) && (C[i].b < C[j].b) && (C[i].c < C[j].c) );
}
//--------------------------------------------

//--------------------------------------------
int max(Cube* C, int* m, int L, int R) {
	
	int max = 0;
	for(int j = L; j < R; ++j) {
		if (is_include(C, j, R)) {
			if (m[j] > max) {
				max = m[j];
			}
		}
	}
	return max;
}
//--------------------------------------------


/********************************************/
int main()
{
	int n;
	cin >> n;
	
	Cube* C = new Cube[n];
	for(int i = 0; i < n; ++i) {
		cin >> C[i].a >> C[i].b >> C[i].c;
	}
//--------------------------------

	int* m = new int[n];
	for(int i = 0; i < n; ++i) {
		m[i] = 0;
	}
	m[0] = 1;
	
	for(int i = 1; i < n; ++i) {
		m[i] = max(C, m, 0, i) + 1;
	}
	
	cout << endl << "M:  ";
	for(int i = 0; i < n; ++i) {
		cout << m[i] << " ";
	}
	cout << endl;
	
	int ans = m[0];
	for(int i = 1; i < n; ++i) {
		if (m[i] > ans) {
			ans = m[i];
		}
	}
	
	cout << ans << endl;
//--------------------------------

	_getch();
	return 0;
}
/********************************************/