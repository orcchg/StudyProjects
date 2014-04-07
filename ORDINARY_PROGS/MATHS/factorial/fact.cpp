#include <conio.h>
#include <stdio.h>
#include <cmath>

#define EPS 0.5e-10

double f(double x, double t){

	return x*log(x) - t*log(2);
}

double df(double x, double t){

	return log(x) + 1 - t*log(2);
}

long long fact(long long n){
	
	if(n == 0) return 1;
	if(n < 0) return -1;
	else { n*=fact(n-1);
		return n;
	}
}

int main(){

	long N;
	double x=0;
	
	while(scanf("%ld",&N)==1 && N!=0){
		x = N*log(N)/log(2);
		printf("%lf\n", x);
	}
	
		
	_getch();
}