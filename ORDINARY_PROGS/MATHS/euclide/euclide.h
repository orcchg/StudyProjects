long HOD(long a, long b, long& rx, long& ry)
{
	long m = a,n = b,p = 1,q = 0,r = 0,s = 1,d = 0;
	
	while(m > 0 && n > 0) {
		if (m >= n) {
			m -= n;
			p -= r;
			q -= s;
		} else {
			n -= m;
			r -= p;
			s -= q;
		}
	}
	
	if (m == 0) {
		d = n;
		rx = r;
		ry = s;
	} else if (n == 0) {
		d = m;
		rx = p;
		ry = q;
	}
	
	return d;
}

long HOK(long a, long b)
{
	long m = a,n = b,u = b,v = a,z = 0;
	
	while(m > 0 && n > 0) {
		if (m >= n) {
			m -= n;
			v += u;
		} else {
			n -= m;
			u += v;
		}
	}
	
	if (m == 0) {
		z = v;
	} else if (n == 0) {
		z = u;
	}
	
	return (z/2);
}