#include <stdio.h>

void revers(char a[], int n);

int main()
{
	int n, b, e, i;
	char a[80];
	
	scanf("%d", &n);
	for(i=0; i<=n; i++)
		a[i] = i;
	scanf("%d", &b);
	scanf("%d", &e);
	revers(a+b,e-b+1);
		
	scanf("%d", &b);
	scanf("%d", &e);
	revers(a+b,e-b+1);

	for(i=0; i<=n; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
