#include <conio.h>
#include <stdio.h>
#include <math.h>

#define EPS 1e-10

double f(double x){

	return exp(x) - 2 - x;
}

int main(){

	double l = 0, r = 2, c;
	long count=0;
	
	while( r - l > EPS){
		c = (l+r)/2;
		printf("%ld\n",++count);
		if( f(c)*f(r) < 0 ) l = c;
		else r = c;
	}
	printf("\n%.10lf", (l+r)/2);
	_getch();
}