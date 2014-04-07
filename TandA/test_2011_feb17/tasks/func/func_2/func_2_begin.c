#include <stdio.h>
#include <ctype.h>

#define N 80
int my_atoi(char a[]);

#undef atoi
void atoi(void) { }

int main()
{
	char a[N];
	fgets(a,N,stdin);
	printf("%d\n", my_atoi(a));
	return 0;
}
