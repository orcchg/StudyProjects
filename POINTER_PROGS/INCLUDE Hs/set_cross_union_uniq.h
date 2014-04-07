#if !defined(ULONG_T)

#define ULONG_T
typedef unsigned long ULONG;

const ULONG errval = 9999999;
#endif

ULONG set_cross(ULONG,ULONG,ULONG [],ULONG [],ULONG []);
ULONG set_union(ULONG,ULONG,ULONG [],ULONG [],ULONG []);
ULONG* set_uniq(ULONG,ULONG [],ULONG&);

/************* QUICK SORT *************************/
void Q_S(ULONG*, ULONG, ULONG);

void Quick_Sort(ULONG* pA, ULONG n){

	Q_S(pA,0,n-1);
}

void Q_S(ULONG* pA, ULONG p, ULONG r){

	int i,j,q,temp;
	
	i = p;
	j = r;
	q = (p+r)/2;
	
	do {
		while((pA[i] < pA[q]) && (i < r))
			i++;
		while((pA[q] < pA[j]) && (j > p))
			j--;
		
		if(i <= j){
			temp = pA[i];
			pA[i] = pA[j];
			pA[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	
	if(p < j)
		Q_S(pA,p,j);
	if(i < r)
		Q_S(pA,i,r);
}
/******************************************************/

ULONG* Merge(ULONG* pL, ULONG* pR, ULONG l, ULONG r){

	ULONG* pResult;
	ULONG n = 0;
	
	pResult = new ULONG[l+r]; //alloc(l+r);
	
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
		for(ULONG i = 0; i < r; i++)
			pResult[n++] = *pR++; //*(pR++);
	}
	
	if(r == 0){		
		for(ULONG i = 0; i < l; i++)
			pResult[n++] = *pL++;
	}
	
	return pResult;
}

ULONG* Merge_Sort(ULONG* pA, ULONG n){

	ULONG* pLeft = new ULONG[n / 2 + 1];//alloc(n/2 + 1);
	ULONG* pRight = new ULONG[n / 2 + 1];//alloc(n/2 + 1);
	ULONG* pResult;
	
	if(!pLeft || !pRight)
		//Not enough memory
		return NULL;
		
	if(n < 2){
		delete [] pLeft; //free(pLeft);
		delete [] pRight; //free(pRight);
		return pA;
		
	} else {
		
		ULONG q = n/2;
		
		for(ULONG i = 0; i < q; i++)
			pLeft[i] = pA[i];
			
		for(ULONG i = q; i < n; i++)
			pRight[i-q] = pA[i];

		pLeft = Merge_Sort(pLeft, q);
		pRight = Merge_Sort(pRight, n - q);
		
		pResult = Merge(pLeft, pRight, q, n - q);
		
		delete [] pLeft; //free(pLeft);
		delete [] pRight; //free(pRight);
		
		return pResult;
	}
}

/**********************************************************************/
ULONG set_cross(ULONG L_a,ULONG L_b,ULONG A[],ULONG B[],ULONG AB[])
{
	ULONG k = 0;
	for(ULONG i = 0; i < L_a; i++) {
		for(ULONG j = 0; j < L_b; j++) {
			if(B[j] == A[i]) {
				AB[k] = B[j];
				k++;
				break;
			}
		}
	}
	return k;
}

/**********************************************************************/
ULONG set_union(ULONG L_a,ULONG L_b,ULONG A[],ULONG B[],ULONG AB[])
{
	ULONG k = 0,L_M,L_m,count=0;
	L_M = (L_a > L_b) ? L_a : L_b;
	L_m = (L_a > L_b) ? L_b : L_a;
	
	if(L_M == L_a) {
		for(ULONG i = 0; i < L_M; i++) {
			AB[i] = A[i];
		}
		for(ULONG j = 0; j < L_m; j++) {
			for(ULONG i = 0; i < L_M; i++) {
				if(B[j]!=A[i]) {
					count++;
				} else {
					count = 0;
					break;
				}
			}
			if(count == L_M) {
				AB[L_M+k] = B[j];
				k++;
				count = 0;
			}
		}
	} else if (L_M == L_b) {
		for(ULONG i = 0; i < L_M; i++) {
			AB[i] = B[i];
		}
		for(ULONG j = 0; j < L_m; j++) {
			for(ULONG i = 0; i < L_M; i++) {
				if(A[j]!=B[i]) {
					count++;
				} else {
					count = 0;
					break;
				}
			}
			if(count == L_M) {
				AB[L_M+k] = A[j];
				k++;
				count = 0;
			}
		}
	}	
	return k + L_M;
}

/**********************************************************************/
ULONG* set_uniq(ULONG L_a,ULONG A[],ULONG& rL_q)
{
	rL_q = 0;
	ULONG i = 0;
	ULONG* AB = new ULONG[L_a];
	ULONG* C = new ULONG[L_a];
	
	for(int i = 0; i < L_a; i++) {
		C[i] = A[i];
	}
	
	Merge_Sort(C,L_a);	
	while(i < L_a) {
		if(C[i+1] != C[i]) {
			AB[rL_q] = C[i];
			rL_q++;
		}
		i++;
	}
	
	delete [] C;
	return AB;
}

/**********************************************************************/
//Вычитает из более длинного множества более короткое, удаляя элементы последнего.//
ULONG* set_differ(ULONG L_a,ULONG L_b,ULONG A[],ULONG B[],ULONG& rL_r)
{
	rL_r = 0;
	ULONG* QA = new ULONG[L_a];
	ULONG* QB = new ULONG[L_b];
	ULONG i = 0,L_qa = 0,L_qb = 0,L_m,count=0,k=0;
	
	//Sorted and uniqued//
	QA = set_uniq(L_a,A,L_qa);
	QB = set_uniq(L_b,B,L_qb);
	printf("SORTED\n");
	
	rL_r = (L_qa > L_qb) ? L_qa : L_qb;
	L_m = (L_qa > L_qb) ? L_qb : L_qa;
	ULONG* R = new ULONG[rL_r];
	
	if(rL_r == L_qa) {
		for(i = 0; i < rL_r; i++) {
			for(ULONG j = 0; j < L_m; j++) {
				if(QB[j] != QA[i]) {
					count++;
				} else {
					count = 0;
					break;
				}
			}
			if(count == L_m) {
				R[k] = QA[i];
				k++;
				count = 0;
			}
		}
	} else if (rL_r == L_qb) {
		for(i = 0; i < rL_r; i++) {
			for(ULONG j = 0; j < L_m; j++) {
				if(QA[j] != QB[i]) {
					count++;
				} else {
					count = 0;
					break;
				}
			}
			if(count == L_m) {
				R[k] = QB[i];
				k++;
				count = 0;
			}
		}
	}
	delete [] QA;
	delete [] QB;
	
	rL_r = k;
	ULONG* FINAL = new ULONG[k];
	for(ULONG j = 0; j < rL_r; j++) {
		FINAL[j] = R[j];
	}
	delete [] R;
	
	return FINAL;
}
		
/************************************************/
ULONG set_minimum(ULONG A[],ULONG L_a)
{
	ULONG min = A[0];
	for(ULONG i = 1; i < L_a; i++) {
		if(min > A[i]) {
			min = A[i];
		}
	}
	return min;
}