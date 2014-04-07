int* Merge(int* pL, int* pR, int l, int r){

	int* pResult;
	int n = 0;
	
	pResult = new int[l+r]; //alloc(l+r);
	
	while(l > 0 && r > 0){
		if(*pL < *pR){
			//APPEND LEFT[0] to Result[]
			pResult[n] = *pL;
			pL++;
			l--;
		} else {
			pResult[n] = *pR;
			pR++;
			r--;
		}
		
		n++;
	}
	
	if(l == 0){
		for(int i = 0; i < r; i++)
			pResult[n++] = *pR++; //*(pR++);
	}
	
	if(r == 0){		
		for(int i = 0; i < l; i++)
			pResult[n++] = *pL++;
	}
	
	return pResult;
}

int* Merge_Sort(int* pA, int n){

	int* pLeft = new int[n / 2 + 1];//alloc(n/2 + 1);
	int* pRight = new int[n / 2 + 1];//alloc(n/2 + 1);
	int* pResult;
	
	if(!pLeft || !pRight)
		//Not enough memory
		return NULL;
		
	if(n < 2){
		delete [] pLeft; //free(pLeft);
		delete [] pRight; //free(pRight);
		return pA;
		
	} else {
		
		int q = n/2;
		
		for(int i = 0; i < q; i++)
			pLeft[i] = pA[i];
			
		for(int i = q; i < n; i++)
			pRight[i-q] = pA[i];

		pLeft = Merge_Sort(pLeft, q);
		pRight = Merge_Sort(pRight, n - q);
		
		pResult = Merge(pLeft, pRight, q, n - q);
		
		delete [] pLeft; //free(pLeft);
		delete [] pRight; //free(pRight);
		
		return pResult;
	}
}