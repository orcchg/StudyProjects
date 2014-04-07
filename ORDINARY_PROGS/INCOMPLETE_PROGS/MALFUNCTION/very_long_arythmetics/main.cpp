#include <conio.h>
#include "vlongar.h"

int main()
{
	int i = 0, drop = 0;
	long e;
	char c;
	char* a_str, *b_str;
	lnum a, b;
	
	printf("Write the long number a: ");
	while((c=getchar())!='\n' || c!=' ' || c!='\t')
	{
		if (c >= '0' && c <= '9')
		{
			a_str[i++] = c;
		}
	}
	Read(a_str, a);
	
	printf("Write the long number b: ");
	while((c=getchar())!='\n' || c!=' ' || c!='\t')
	{
		if (c >= '0' && c <= '9')
		{
			b_str[i++] = c;
		}
	}
	Read(b_str, b);
	
	printf("\n\nLong number a: ");
	Print(a);
	printf("\n\nLong number b: ");
	Print(b);
	
	printf("Sum a + b: ");
	Sum(a, b);
	Print(a);
	
	printf("Subtr (a + b) - b: ");
	Subtract(a, b);
	Print(a);
	
	printf("\n\nWrite the short number e: ");
	scanf("%ld", &e);
	fflush(stdin);
	
	printf("\n\nMult on short: a * e: ");
	MultOnShort(a, e);
	Print(a);
	
	printf("Mult on Long: (a * e) * b: ");
	Mult(a, b);
	Print(a);
	
	printf("\n\nDivision (a * e * b) / e: ");
	drop = DivOnShort(a, e);
	Print(a);
	printf("\n\nResidue: %d", drop);
	
	_getch();
	return 0;
}