#include "complex.h"

complex_type c_sum(complex_type x, complex_type y)
{
	complex_type t;
	t.a = x.a + y.a;
	t.b = x.b + y.b;
	return t;
}

complex_type c_mul(complex_type x, complex_type y)
{
	complex_type t;
	t.a = x.a * y.a - x.b * y.b;
	t.b = x.a * y.b + x.b * y.a;
	return t;
}

complex_type c_div(complex_type x, complex_type y)
{
	complex_type t;
	
	if((y.a * y.a + y.b * y.b)==0) return infinity;
	else {
	t.a = (x.a * y.a + x.b * y.b)/(y.a * y.a + y.b * y.b);
	t.b = (x.b * y.a - x.a * y.b)/(y.a * y.a + y.b * y.b);
	return t;
	}
}