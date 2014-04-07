#include "struct.h"

void Q_S(member*, int, int);

void Quick_Sort(member* pA, int n){

	Q_S(pA,0,n-1);
}

void Q_S(member* sequence, int p, int r) {

	int i = p;
	int j = r;
	int temp = 0;
	type_el temp_info = ZERO;
	int m = p + (r - p) / 2;
	int x = sequence[m].key;
	
	while (i <= j) {
		while (sequence[i].key < x) {
			++i;
		}
		while (x < sequence[j].key) {
			--j;
		}
		
		if (i <= j) {
			temp = sequence[i].key;
			temp_info = sequence[i].info;
			
			sequence[i].key = sequence[j].key;
			sequence[i].info = sequence[j].info;
			
			sequence[j].key = temp;
			sequence[j].info = temp_info;
			
			++i;
			--j;
		}
	}
	
	if (p < j) {
		Q_S(sequence, p, j);
	}
	if (i < r) {
		Q_S(sequence, i, r);
	}
}