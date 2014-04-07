long power(long n, long a)
{
	long k=n, b=1, c=a;
	while(k) {
		if(k % 2 == 0) {
			c*=c;
			k/=2;
		} else {
			b*=c;
			k--;
		}
	}
	return b;
}
	