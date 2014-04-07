#include <conio.h>
#include <stdio.h>
#include "issimple.h"

int main()
{
	long N;
	bool flag = false;
	
	printf("Enter N: ");
	scanf("%ld",&N);
	fflush(stdin);
	
	flag = is_simple(N);
	
	if(flag) {
		printf("Yes!");
	} else {
		printf("No!");
	}
	
	_getch();
}
