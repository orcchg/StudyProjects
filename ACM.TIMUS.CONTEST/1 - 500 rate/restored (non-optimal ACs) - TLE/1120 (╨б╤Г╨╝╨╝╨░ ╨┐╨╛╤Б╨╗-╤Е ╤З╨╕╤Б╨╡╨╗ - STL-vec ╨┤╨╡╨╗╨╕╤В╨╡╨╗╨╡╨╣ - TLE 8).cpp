#include <stdio.h>
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

int main()
{
	int N, P, A, N2;
	
	scanf("%d", &N);
	
	N2 = 2*N;
	
	vector<int> D;
	D.clear();
	
	for(int i = 1; i <= N; ++i) 
	{ 
		if (N2 % i == 0) 
		{
			D.push_back(i);
		}
	}
	
	int l = D.size() - 1;
	P = D[l];
	A = 1;
//	printf("%d %d\n", A, P);
	
	for(P = D[l] ; ; P = D[--l])
	{
		A = N2 / P + 1 - P;
		A /= 2;
//		printf("%d %d\n", A, P);
		if (A > 0 && (2*A + P - 1)*P == N2)
		{
			break;
		}
	}
	P = D[l];
	
	printf("%d %d", A, P);
//	_getch();
	return 0;
}