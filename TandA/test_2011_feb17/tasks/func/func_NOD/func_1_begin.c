#include <stdio.h>

unsigned int nod(unsigned int a, unsigned int b);

int main()
{
	unsigned int x, y;
	scanf("%u", &x);
	scanf("%u", &y);
	printf("%u\n", nod(x,y));
	return 0;
}
