unsigned degree( unsigned x, int d) /* x**d */ {
	int k;
	unsigned xd = 1;
	
	for (k = 0; k < d; k++) {
		xd *= x;
		if (x == 0 && k > 0) {
			xd = 0;
		}
	}
	return xd;
}

int find_next(unsigned * p, int n, unsigned x, int d, int * brk) {
	int i;
       	unsigned xd;

	for ( i = 0; i < n; i++, p++) {
		xd = degree( x, d);
		if (*p > xd ) {
			*brk = 0;
		}
		if (*p == xd ) {
			return i;
		}
	}
	return -1;
}

int count(unsigned * p, int N, unsigned x) {
	int r = 0, d, brk, i;
	
	for (d = 0; d < sizeof( unsigned) * 8; d++) {
		if ((( d == 1) && (x == 1)) || (( d == 2) && (x == 0))) /* special cases */ {
			break;
		}
		if (( d > 1 ) && ((degree( x, d) / degree (x, d-1)) != x)) /* overflow */ {
			break;
		}
		brk = 1;
		i = find_next(p, N, x, d, &brk);
		while (i != -1) {
			r++;
			i = find_next(p+i+1, N-i-1, x, d, &brk);
		}
		if (brk && x != 0) /* special case: 0**0 > 0**1 */ {
			break;
		}
	}
	return r;
}
