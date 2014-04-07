#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

int main()
{
	int N, K, nStr;
	
	cin >> N >> K;
	
	int* pA = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> pA[i];
	}
	
	if (N % K == 0) 
	{
		nStr = N / K;
	} 
	else 
	{
		nStr = (N - N % K) / (K - 1);
	}
	
//	cout << nStr << "  " << N % K;
	
	int j = 0, lam;
	lam = N - (K - 1)*nStr;
	
	while(j < nStr)
	{
		for(int i = 0; i < K + lam - 1; ++i)
		{
			printf("%4d", pA[j + nStr*i]);
		}
		--lam;
		++j;
		cout << endl;

		if (lam <= 0)
		{
			lam = 0;
			continue;
		}
	}
	
//	_getch();
	return 0;
}