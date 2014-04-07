int* Min_el(int*,int,int);

void Selection_Sort(int* pA,int n){

	int min=0,k=n;
	int* ptr=pA;
	int temp;
	
	for(int j=0; j<n-1; j++){
		k = n - j;
		ptr = Min_el(pA,k,j);
		temp = *ptr;
		*ptr = pA[j];
		pA[j] = temp;
	}
}

int* Min_el(int* pA,int n,int pos){

	int* pMin = &pA[pos];
	
	for(int i=pos+1; i<n; i++){
		if(pA[i] < *pMin)
			pMin = &pA[i];
	}
	
	return pMin;
}