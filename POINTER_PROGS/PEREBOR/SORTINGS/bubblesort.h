void Bubble_Sort(int* pA,int n){

	int x=0;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n-i-1; j++){
			
			if(pA[j] > pA[j+1]){
				x = pA[j];
				pA[j] = pA[j+1];
				pA[j+1] = x;
			}
		}
	}
}