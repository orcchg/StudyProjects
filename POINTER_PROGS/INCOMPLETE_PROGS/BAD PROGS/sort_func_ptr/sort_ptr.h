void sort(char** V, int N, int (*comp)(char,char), int (*exch)(char*,char*)){
	//int (*comp)() - POINTER TO int-FUNCTION comp(); int *comp() - function, returning int*;
	int i,j,GAP;
	
	for(GAP = N/2; GAP > 0; GAP /=2){
		for(i = GAP; i < N; i++){
			for(j = i - GAP; j >= 0; j -= GAP){
				if((*comp)(V[j],V[j+GAP]) <= 0)
					break;
				(*exch)(&V[j],&V[j+GAP]);
			}
		}
	}
}