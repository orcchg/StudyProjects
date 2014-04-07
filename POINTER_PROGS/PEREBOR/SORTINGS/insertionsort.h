void Insertion_Sort(int* pA,int n){

	int key,i;

	for(int j = 1; j < n; j++){
		key = pA[j];
		i = j - 1;
		
		while(i >= 0 && pA[i] > key){
			pA[i+1] = pA[i];
			i--;
			pA[i+1] = key;
		}
	}
}