#include "struct.h"

void Sift(member* pA, int L, int R) {
	
	int i = L;
	int j = 2*i + 1;
	int x = pA[i].key;
	type_el y = pA[i].info;
	
	if ( (j < R) && (pA[j].key < pA[j+1].key) ) {
		++j;
	}
	
	while ( (j <= R) && (x < pA[j].key) ) {
		pA[i].key = pA[j].key;
		pA[i].info = pA[j].info;
		i = j;
		j = 2*j + 1;
	
		if ( (j < R) && (pA[j].key < pA[j+1].key) ) {
			++j;
		}
	}
	
	pA[i].key = x;
	pA[i].info = y;
}

void Heap_Sort(member* pA, int L, int R) {

	int x;
	type_el y;
	
	L = (R - L + 1) / 2;
	
	while (L > 0) {
		--L;
		Sift(pA, L, R);
	}
	
	while (R > 0) {
		x = pA[0].key;
		y = pA[0].info;
		
		pA[0].key = pA[R].key;
		pA[0].info = pA[R].info;
		
		pA[R].key = x;
		pA[R].info = y;
		
		--R;
		Sift(pA, L, R);
	}
}