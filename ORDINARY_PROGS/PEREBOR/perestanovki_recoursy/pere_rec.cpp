#include <conio.h>
#include <stdio.h>

char a[] = "abcde";
int m = 1;

void Print()
{
	m++;
	printf("%d:  ",m);
	
	for(int j = 0; j < sizeof(a)/sizeof(a[0])-1; ++j)
	{
		printf("%c",a[j]);
	}
	printf("\n");
}
	
void transpos(int n)
{
	char c;
	
	for(int i = 0; i < n; ++i)
	{
		c = a[n-1];
		for(int j = n - 1; j >= 0; --j)
		{
			a[j] = a[j-1];
		}
		a[0] = c;
		
		if (i < n - 1)
		{
			Print();
		}
		
		if (n - 1 > 1)
		{
			transpos(n - 1);
		}
	}
}

int main()
{
	printf("N: %d\n\n",sizeof(a)/sizeof(a[0])-1);
	printf("%d:  %s\n",m,a);
	transpos(sizeof(a)/sizeof(a[0])-1);
	
	_getch();	
	return 0;
}