#include <stdio.h>
#include <conio.h>

typedef unsigned long long ULONG;

const ULONG MAXLEN = 10000000;

//-------------------------------------------
bool is_simple(ULONG N)
{
	ULONG k = N,l = 2;
	
	while(l != N) {
		if(k % l == 0) {
			return false;
		} else {
			l++;
		}
	}
	return (l == N);
}
//-------------------------------------------

int main()
{
	int K;
	ULONG n = 0, j = 0;
	
	scanf("%d", &K);
	
	int* A = new int[K];
	
	for(int i = 0; i < K; ++i)
	{
		scanf("%d", &A[i]);
	}
	
	for(int i = 0; i < K; ++i)
	{
		for(j = 2; n != A[i]; ++j)
		{		
			if (is_simple(j))
			{
				++n;
			}
		}
		--j; 
		printf("%lld\n", j);
		n = 0;
	}
	
//	_getch();
	return 0;
}