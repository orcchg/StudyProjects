#include <conio.h>
#include <stdio.h>
#include <math.h>

#define EPS 0.5e-10

double f(double x){

	return exp(x) - 2 - x;
}

double df(double x){

	return exp(x) - 1;
}

int main(){

	double c=1,y0=0,x=0;
	long count=0;
	
	do {
		printf("%ld\n",++count);
		y0 = f(c);
		x = c;
		c = c - y0/df(c);
	} while( fabs(c-x) > EPS);
	
	printf("\n%.10lf", x);
	_getch();
}