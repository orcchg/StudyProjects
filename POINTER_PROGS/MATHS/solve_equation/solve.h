#include <math.h>

const double eps = 1e-10;

double solve(double A, double B, double (*f)(double))
{
	double x = 0, a, b;
	double len = fabs(A - B);
	a = (B > A) ? A : B;
	b = (B > A) ? B : A;
	
	while(len > eps)
	{
		x = a + (b - a)/2;
		
		if (f(x) > 0)
		{
			a = x;
			len = fabs(b - x);
		}
		else if (f(x) < 0)
		{
			b = x;
			len = fabs(x - a);
		}
		else
		{
			break;
		}
	}
	
	return x;
}