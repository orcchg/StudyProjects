#include <stdio.h>
#include <conio.h>
#include <math.h>

int main()
{
	__int64 N, K, M = 0, G = 1;
	
	scanf("%I64d%I64d", &N, &K);
	
	//----------------------------------------------------------
	--N;
	
	while( (N > 0) && (G < K) )
	{
		N -= G;
		++M;
		G *= 2;
	}
	
	if (N > 0)
	{
		M += (N % K) ? (N / K + 1) : N / K;
	}
	
	printf("%I64d", M);
	
//	_getch();
	return 0;
}