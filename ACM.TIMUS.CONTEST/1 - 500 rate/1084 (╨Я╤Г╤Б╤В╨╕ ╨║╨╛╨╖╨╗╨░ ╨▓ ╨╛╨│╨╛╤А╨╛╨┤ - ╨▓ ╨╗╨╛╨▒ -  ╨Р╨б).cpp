#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdio.h>
using namespace std;

const double pi = 3.141592653589793238462643383279502884197169399375;

int main()
{
	int N, L;
	double S = 0.0, fi = 0.0, a = 0.0, M = 0.0;
	
	cin >> N >> L;
	
	if (N >= 2*L)
	{
		S = pi*(double)L*L;
	}
	else if ((double)L >= (double)N*sqrt(2.0)/2)
	{
		S = (double)N*N;
	}
	else
	{
		M = L*L - N*N*0.25;
		a = sqrt(M);
		fi = pi*0.5 - 2*atan( (2*a/N) );
		S = 4 * ( a*0.5*N + 0.5*L*L*fi );
	}
	
	printf("%.3lf", S);
	
//	_getch();
	return 0;
}