#include <conio.h>
#include <math.h>
#include <stdio.h>
#include "factorial.h"

double Series(double,int);

int main()
{
	int N;
	double X;
	
	printf("Enter N and X: ");
	scanf("%d %lf",&N,&X);
	printf("\n");
	fflush(stdin);
	
	printf("\nSum: %lf",Series(X,N));
	printf("\nSin: %lf",sin(X));
	_getch();
}

double Series(double X, int N)
{
	double S = 0;
	
	for(int i = 0; i <= N; i++) {
		S += pow(-1,i)*pow(X,2*i+1)/(double)fact(2*i+1);
	}
	
	return S;
}