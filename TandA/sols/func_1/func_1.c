int power(int a, unsigned int n)
{
	int k = n, c = a, b = 1;
	while(k) {
		if(k % 2 == 0) {
			c *= c;
			k /= 2;
		} else {
			b *= c;
			--k;
		}
	}
	
	return b;
}