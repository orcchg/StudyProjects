bool is_simple(long N)
{
	long k = N,l = 2;
	
	while(l != N) {
		if(k % l == 0) {
			return false;
		} else {
			l++;
		}
	}
	return (l == N);
}