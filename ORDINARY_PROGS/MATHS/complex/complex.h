#include <float.h>

typedef struct {
				double a,b;
		} complex_type;
		
const complex_type infinity = {DBL_MAX, DBL_MAX};
const complex_type zero = {0,0};
const complex_type im_i = {0,1};

complex_type c_sum(complex_type x, complex_type y);
complex_type c_mul(complex_type x, complex_type y);
complex_type c_div(complex_type x, complex_type y);