long HOD(long a, long b)
{
	long m = a, n = b, d = 0;
	
	while(m > 0 && n > 0) {
		if (m >= n) {
			m -= n;
		} else {
			n -= m;
		}
	}
	
	if (m == 0) {
		d = n;
	} else if (n == 0) {
		d = m;
	}
	
	return d;
}