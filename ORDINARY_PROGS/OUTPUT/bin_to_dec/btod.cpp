#include <conio.h>
#include <stdio.h>
#include "btod.h"

int main()
{
	unsigned long B;
	unsigned long N;
	
	printf("Enter binary number: ");
	scanf("%ld",&B);
	printf("\n");
	
	N = btod(B);
	
	printf("Decimal number: %ld",N);
	_getch();
}