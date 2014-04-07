#include <cstring>

void sort(char* V[],int N){

	int GAP,i,j;
	char* TEMP;
	
	for(GAP = N/2; GAP > 0; GAP /= 2){
		for(i = GAP; i < N; i++){
			for(j = i - GAP; j >= 0; j -= GAP){
			
			if(strcmp(V[j],V[j+GAP]) <= 0)
				break;
			
			TEMP = V[j];
			V[j] = V[j+GAP];
			V[j+GAP] = TEMP;
			
			}
		}
	}
}