#include <iostream>
//#include <iomanip>
#include <conio.h>
#include <stdio.h>
using namespace std;

int main()
{

	int N;
	double M = 0;
	
	cin >> N;
	
	int* P = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> P[i];
		M += P[i];
	}
	
	M /= N;
	
//	cout << setprecision(7);
//	cout << M;
	printf("%.6lf", M);
//	_getch();
	return 0;
}