#include <stdio.h>
#include <conio.h>
#include <math.h>

/*
 * Let x[n] be n-th element of given sequence.
 * Following formula for x[n] can be simply proved:
 * x[n] = 2/3 + (1/3)/(2^(n-1)) if n - odd
 * x[n] = 2/3 - (1/3)/(2^(n-1)) if n - even
 * Let delta = (1/3)/(2^(n-1)) = 0.000XXXX.. (X - any digit)
 * We can simply find number of leading zeroes after
 * decimal point (befor XXX..) as:
 * k = floor[ Log10(3*2^(n-1)) ] or
 * k = floor[ Log10(3) + (n-1)*Log10(2) ]
 * Obviously answer always will be k or k-1.
 * Consider (k-1)-cases:
 * [1] N - odd (add delta):
 * A = (1/3)/(10^k) = 0.0003333... (repeat 0 k times)
 * If A <= delta - then addition will affect k-th digit
 * and answer will be k-1.
 * [2] N - even (subtract delta):
 * A = (2/3)/(10^k) = 0.0006666... (repeat 0 k times)
 * If A <= delta - then subtraction will affect k-th digit
 * and answer will be k-1.
 * Compare logarithms instead of comparing values themself. 
 */

int main()
{
	int n; // 2 <= n <= 100000;
	
	scanf("%d", &n);
	
	double k;
	
	{
		modf(log10(3.0) + (n - 1)*log10(2.0), &k);
	}
	
	if (n % 2 == 1)
	{
		double A = - (log10(3.0) + k);
		double D = log10(3.0) + (n - 1)*log10(2.0);
		
		if (fabs(A) > fabs(D))
		{
			--k;
		}
	}
	else
	{
		double A = log10(2.0) - (log10(3.0) + k);
		double D = log10(3.0) + (n - 1)*log10(2.0);
		
		if (fabs(A) > fabs(D))
		{
			--k;
		}
	}
	
	printf("%d", (int)k);

//	_getch();
	return 0;
}
