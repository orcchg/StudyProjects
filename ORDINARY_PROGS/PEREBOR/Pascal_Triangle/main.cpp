#include <conio.h>
#include <stdio.h>
#include "C_n_k.h"
#include "P_T.h"

const int N = 1000;

int main(){

	long n,i,j;
	long c[N];
	
	printf("Enter n: ");
	scanf("%ld",&n);
	printf("\n");
	
//	Graph_C(n);
	for(i = 1; i<= n; i++) c[i]=0;
		c[0] = 1;
	
	for(j = 0; j<= n; j++){
		for(i = j; i>= 1; i--){
			c[i] = c[i-1] + c[i];
			printf("%5ld",c[i]);
		}
		printf("%5ld\n",c[0]);
	}
	
	_getch();
}