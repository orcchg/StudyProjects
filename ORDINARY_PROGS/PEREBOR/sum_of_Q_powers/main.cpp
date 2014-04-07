#include <conio.h>
#include <stdio.h>
#include "power.h"

const unsigned long MAXLEN = 1000;

unsigned long q_nary_reverse(unsigned long, unsigned long[], unsigned long);
unsigned long ternary_sign(unsigned long, unsigned long[]);

int main()
{
	unsigned long q,N, i = 0, temp;
	unsigned long A[MAXLEN],P[MAXLEN];
	
	printf("Enter N and q: ");
	scanf("%ld %ld",&N,&q);
	printf("\n");
	fflush(stdin);
	
	i = q_nary_reverse(N,A,q);
	printf("\nN: %ld = ",N);
	for(unsigned long j = 0; j < i; j++) {
		temp = A[j]*power(j,q);
			if(temp) {
				printf("%ld",temp);
				printf(" + ");
			}
	}
	printf("\nN: %ld = ",N);
	for(unsigned long j = 0; j < i; j++) {
		temp = A[j]*power(j,q);
			if(temp) {
				if (A[j] == 1) {
					printf("%ld",temp);
					printf(" + ");
				} else {
					printf("%ld*%ld",A[j],power(j,q));
					printf(" + ");
				}
			}
	}
	
	_getch();
}

unsigned long q_nary_reverse(unsigned long N, unsigned long A[], unsigned long q)
{
	unsigned long i = 0, C = N;
	
	while(C) {
		A[i] = C % q;
		C /= q;
		i++;
	}
	
	return i;
}

unsigned long ternary_sign(unsigned long N, unsigned long A[])
{
	unsigned long i = 0, C = N, P[MAXLEN];
	
	i = q_nary_reverse(C,P,3);
	for(unsigned long j = 0; j < i; j++) {
		/////////////////////////////////
		C = power(i+1,3) - C;
		
		i = q_nary_reverse(C,P,3);
	
	return i;
}