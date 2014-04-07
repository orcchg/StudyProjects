void Q_S(int*, int, int);

void Quick_Sort(int* pA, int n){

	Q_S(pA,0,n-1);
}

void Q_S(int* sequence, int p, int r) {

	int i = p;
	int j = r;
	int temp;
	int m = p + (r - p) / 2;
	int x = sequence[m];
	
	while (i <= j) {
		while (sequence[i] < x) {
			++i;
		}
		while (x < sequence[j]) {
			--j;
		}
		
		if (i <= j) {
			temp = sequence[i];
			sequence[i] = sequence[j];
			sequence[j] = temp;
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