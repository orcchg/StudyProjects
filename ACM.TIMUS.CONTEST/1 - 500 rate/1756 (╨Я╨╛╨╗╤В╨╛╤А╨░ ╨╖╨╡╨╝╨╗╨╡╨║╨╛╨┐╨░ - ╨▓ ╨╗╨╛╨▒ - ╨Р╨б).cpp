#include <stdio.h>
#include <conio.h>

int main()
{

	__int64 m, d1, d2;
	__int64 T;
	
	scanf("%I64d%I64d%I64d", &m, &d1, &d2);
	T = m * d1;
	
	__int64* Array = new __int64[d2+1];
	
	if ( T <= d2 )
	{
		for(__int64 i = 1; i <= T; ++i)
		{
			printf("%d ", 1);
		}
		
		__int64 Y = d2 - T;
		while(Y > 0)
		{
			printf("%d ", 0);
			--Y;
		}
	}
	else
	{
		__int64 a, b;
		
		a = T / d2;
		b = T % d2;
		
		for(__int64 i = 1; i <= d2; ++i)
		{
			Array[i-1] = a;
		}
		
		__int64 k = 0;
		while(b > 0)
		{
			Array[d2-1-k] += 1;
			--b;
			++k;
		}
		
		for(__int64 i = 0; i < d2; ++i)
		{
			printf("%I64d ", Array[i]);
		}
	}
	
//	_getch();
	return 0;
}