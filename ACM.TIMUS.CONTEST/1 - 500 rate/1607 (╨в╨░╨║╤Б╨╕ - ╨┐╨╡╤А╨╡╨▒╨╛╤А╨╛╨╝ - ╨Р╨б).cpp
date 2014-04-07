#include <stdio.h>
#include <conio.h>

int main()
{
	int a, b, c, d;
	int s = a;
	
	scanf("%d%d%d%d", &a, &b, &c, &d); // 1 <= a, b, c, d <= 10000
	
	if ( a >= c)
	{
		printf("%d", a);
		return 0;
	}
	
	while ( a + b <= c - d )
	{
		a += b;
		c -= d;
	}
	
	if (a + b >= c) 
	{
		printf("%d", c);
	}
	else
	{
		printf("%d", a + b);
	}
	
//	_getch();
	return 0;
}