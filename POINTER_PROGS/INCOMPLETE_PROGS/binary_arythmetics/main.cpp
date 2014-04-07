#include <conio.h>
#include <stdio.h>
#include "binaryth.h"

int main()
{
	char* A = new char[5];
	char* B = new char[5];
	char* C = new char[6];
	
/*	printf("Enter binary A and B: ");
	scanf("%s",A);
	fflush(stdin);
	scanf("%s",B);
	fflush(stdin);
	printf("\n");*/
	
	for(int i = 0; i < 5; i++) {
		A[i] = '1';
	}
	for(int i = 0; i < 4; i++) {
		B[i] = '1';
	}

	C = sum(A,B);
	
	for(int i = 0; i <= 5; i++) {
		printf("%c",C[i]);
	}
	_getch();
}