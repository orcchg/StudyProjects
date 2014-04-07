#include <stdio.h>
#include <conio.h>
#include <math.h>

int main()
{
	__int64 N, K, M = 0;
	
	scanf("%I64d%I64d", &N, &K);
	__int64 A = N;
	
	if (N == 1)
	{
		printf("%d", 0);
		return 0;
	}
	
	if (K == 1)
	{
		printf("%I64d", N - 1);
		return 0;
	}
	//------------------------------------------------
	
	if (N/K < 2)
	{
		while(A > 1)
		{
			++M;
			A /= 2;
		}
		if (N > (__int64)pow(2.0, (int)M))
		{
			++M;
		}
		printf("%I64d", M);
		return 0;
	}
	//------------------------------------------------
	__int64 G = K, C;
	A = N - 2;	
	C = N - A;
	M = 1;

	while(A > 0)
	{
		if (G >= C)
		{
			A -= C;
			C += C;
			++M;
		}
		else
		{
			A -= G;
			C += G;
			++M;
		}
	}
	
	printf("%I64d", M);
	
//	_getch();
	return 0;
}