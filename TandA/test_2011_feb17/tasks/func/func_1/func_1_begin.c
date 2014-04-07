#include <stdio.h>

int power(int a, unsigned int n);

int main()
{
	unsigned int a, n;
	scanf("%d", &a);
	scanf("%u", &n);
	printf("%d\n", power(a,n));
	return 0;
}
