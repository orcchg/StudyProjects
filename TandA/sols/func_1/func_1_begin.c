#include <stdio.h>
#include <conio.h>

int power(int a, unsigned int n);

int main()
{
	unsigned int a, n;
	scanf("%d", &a);
	scanf("%u", &n);
	printf("%d\n", power(a,n));
	_getch();
	return 0;
}

int power(int a, unsigned int n)
{
	int k = n, c = a, b = 1;
	while(k) {
		if(k % 2 == 0) {
			c *= c;
			k /= 2;
		} else {
			b *= c;
			--k;
		}
	}
	
	return b;
}