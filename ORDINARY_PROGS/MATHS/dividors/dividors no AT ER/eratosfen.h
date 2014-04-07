#include "unsgnlong.h"

ULONG eratosphen(ULONG N,ULONG P[],ULONG& rp)
{
	ULONG p = 0,count = N-1;
	bool A[N];
	
	for(ULONG j = 0; j < N; j++) {
		A[j] = true;
	}
	A[0]=A[1]=false;
	
	for(ULONG i = 2; i*i <= N; i++) {
		if (A[i]) {
			for(ULONG j = i*i; j <= N; j += i) {
				if (A[j]) {
					A[j] = false;
					count -= 1;
				}
			}
		}
	}
	
	for(ULONG i = 0; i < N; i++) {
		if (A[i]) {
			P[p] = i;
			p++;
		}
	}
	rp = p;
	
	return count;
} //O(NloglogN);