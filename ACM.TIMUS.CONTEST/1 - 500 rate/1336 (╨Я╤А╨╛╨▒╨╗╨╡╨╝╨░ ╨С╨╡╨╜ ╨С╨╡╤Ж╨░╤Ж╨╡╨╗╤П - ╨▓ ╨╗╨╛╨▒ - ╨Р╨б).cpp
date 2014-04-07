#include <stdio.h>
#include <conio.h>
#include <math.h>

int main()
{
	__int64 n, m = 1, k = 1;
	double j = 1;
	
	scanf("%I64d", &n);
	
	if (n == 0)
	{
		m = 0;
		k = 0;
		printf("%I64d\n", m);
		printf("%I64d", k);
		return 0;
	}
	
	while( modf(sqrt((long double)n*k*k*k),&j)!=0)
	{
		++k;
	}
	
	m = (__int64)sqrt((long double)n*k*k*k);
	
/*	k = n;
	m = n*n;
*/	
	printf("%I64d\n", m);
	printf("%I64d", k);
	
//	_getch();
	return 0;
}