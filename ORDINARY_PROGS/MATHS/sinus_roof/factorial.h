long fact(long n){
	
	if(n == 0) return 1;
	if(n < 0) return -1;
	else { n*=fact(n-1);
		return n;
	}
}