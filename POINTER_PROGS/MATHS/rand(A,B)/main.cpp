#include <stdio.h>
#include <conio.h>
#include "rand.h"

int main()
{
	int A,B,N;
	char* str = new char();
	printf("Enter N,A,B: ");
	scanf("%d %d %d",&N,&A,&B);
	printf("\n");
	fflush(stdin);
	
	str = Rand(N,A,B);
	printf("\n%s",str);
	
	delete str;
	
	_getch();
}