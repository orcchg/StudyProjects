#include <stdio.h>
#include <conio.h>
#include <math.h>

const double pi = 3.141592653589793238;

double EllSegmVol(double a, double b, double h)
{
	// Returns segment volume; if h = b, then returns Half-volume of ellipse (a, b);
	// Here are: a - half-small axis, b - half-big axis;
	
	return pi*a*a*b/3.0*(2.0 + h*h*h/b/b/b - 3.0*h/b);
}

int main()
{
	double A, B, a, b;
	int N, n;
	
	scanf("%lf%lf%d", &A, &B, &N);
	
	a = A / 2.0;	b = B / 2.0;
	
	double V = 4.0 * pi * b / 3.0 * a * a; 	// Volume
	double V2 = EllSegmVol(a, b, 0); 	// Half - Volume
	double h = B / N; 						// Height of Ell-segment
	
	double temp = 0.0;
	double res = 0.0;
	double* Stock = new double[N];
	
	if (N % 2 == 0)
	{
		for(int i = N/2 - 1; i >= 0; --i)
		{
			temp = EllSegmVol(a, b, h*i) - res;
			res += temp;
			Stock[i] = temp;
			printf("%.6lf\n", Stock[i]);
		}
		for(int i = 0; i < N/2; ++i)
		{
			printf("%.6lf\n", Stock[i]);
		}
	}
	else
	{
		n = N - 1;
		for(int i = n/2 - 1; i >= 0; --i)
		{
			temp = EllSegmVol(a, b, h / 2.0 + h*i) - res;
			res += temp;
			Stock[i] = temp;
			printf("%.6lf\n", Stock[i]);
		}
		
		temp = EllSegmVol(a, b, 0);
		for(int i = n/2 - 1; i >= 0; --i)
		{
			temp -= Stock[i];
		}
		temp *= 2.0;
		
			printf("%.6lf\n", temp);
		
		for(int i = 0; i < n/2; ++i)
		{
			printf("%.6lf\n", Stock[i]);
		}
		
	}
	
//	printf("%.6lf", V2);
	
//	_getch();
	return 0;
}