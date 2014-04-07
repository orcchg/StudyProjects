#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "quicksort.h"
#include "mergesort.h"
using namespace std;

int main()
{
	int N;
	
	cin >> N;
	srand(N % 1000);
	
	int* A = new int[N];
	for(int i = 0; i < N; ++i)
	{
		A[i] = 200000*(double)rand()/RAND_MAX - 100000;
//		cout << A[i] << endl;
	}
	
	Quick_Sort(A, N);
//	A = Merge_Sort(A, N);
	
	for(int i = 0; i < N; ++i)
	{
		cout << A[i] << endl;
	}
	
	_getch();
	return 0;
}