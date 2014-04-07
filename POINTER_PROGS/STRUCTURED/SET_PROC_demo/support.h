#include "unsgnlong.h"

bool is_simple(ULONG N)
{
	ULONG k = N,l = 2;
	
	while(l != N) {
		if(k % l == 0) {
			return false;
		} else {
			l++;
		}
	}
	return (l == N);
}

ULONG simple_dividor(ULONG N,ULONG P[])
{
	ULONG k = N,l = 2,i = 0;
	
	while(k != 1) {
		l = 2;
		while(k % l != 0) {
			l++;
		}
	P[i++] = l;
	k /= l;
	}
	
	if(i) {
		return i;
	} else {
		return 1;
	}
}

bool is_perfect(ULONG N,ULONG D[],ULONG len) {

	ULONG SUM = 0;
	for(ULONG i = 0; i < len; i++) {
		SUM += D[i];
	}
	
	return (SUM == N);
}