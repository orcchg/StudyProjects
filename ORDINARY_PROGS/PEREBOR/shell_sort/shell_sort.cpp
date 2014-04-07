#include <conio.h>
#include <cstdio>

void shell(int[], int);

int main() {

	int N=10;
	int V[10] = {3,14,8,7,2,9,0,3,1,5};
	
	shell(V,N);
	
	_getch();
	return 0;
}

void shell(int V[], int N){

	int i,j,GAP,TEMP,k=0;
	
	for(GAP=N/2;GAP>0;GAP/=2){
		for(i=GAP;i<N;i++) {
			for(j=i-GAP;j>=0 && V[j]>V[j+GAP];j-=GAP){
				TEMP = V[j];
				V[j]=V[j+GAP];
				V[j+GAP]=TEMP;
			}
		}
	}
	
	while(k<=N){
		printf("%d",V[k]);
		printf(",");
		k++;
	}
}