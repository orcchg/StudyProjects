#if !defined(POWER)

#define POWER

long power(long n, long a) {

	long k = n, c = a, b = 1;
	
	while(k) {
		if (k % 2 == 0) {
			c *= c;
			k /= 2;
		} else {
			b *= c;
			k--;
		}
	}
	return b;
}

#endif