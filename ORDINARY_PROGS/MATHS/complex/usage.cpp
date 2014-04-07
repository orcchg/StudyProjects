#include "complex.h"
#include <conio.h>
#include <stdio.h>

int main()
{
	complex_type x = {1,2};
	complex_type y = {3,4};
	complex_type z = c_sum(x,y);
	complex_type m = c_mul(x,y);
	complex_type n = c_div(x,y);
	complex_type inf = c_div(x,zero);
	printf("z = (%lf, %lf)\n", z.a, z.b);
	printf("m = (%lf, %lf)\n", m.a, m.b);
	printf("n = (%lf, %lf)\n", n.a, n.b);
	printf("inf = (%lf, %lf)\n", inf.a, inf.b);
	
	_getch();
}