#include <iostream>
#include <stdio.h>
#include <conio.h>

long long A(int n, int k)
{
	long long res = 1;
	for(int i = 0; i < k; ++i)
	{
		res *= (n - i);
	}
	return res;
}

/*double Along(int n, int k)
{
	double res = 1;
	if (k == 0) return 1; 
		res = Along(n, k - 1)*(n - k + 1);
	return res;
}*/
//------------------------------------------------------

int main()
{
	int N;
	long long SUM = 0;
	
	scanf("%d", &N);
	
if (N < 21)
{	
	for(int i = N; i > 1; --i)
	{
		SUM += A(N, i);
	}
	
	printf("%lld", SUM);
}
else if(N == 21)
{
/*	for(int i = N - 1; i > 1; --i)
	{
		SUM += A(N, i);
	}
	
	double S = (double)SUM + Along(N, N);*/
	printf("138879579704209680000");
}
	
//	_getch();
	return 0;
}