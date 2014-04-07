#include <conio.h>
#include <stdio.h>

double P_Horner(double* pA, int n, double x){

	int k=0;
	double y=0;

	while(k<=n){
		y = y*x + pA[n-k];
		k++;
	}
	
	return y;
}

double power(double a, int n){

	double y=1;
	
	if(n == 0) { 
		return 1;
	} else if(n % 2 == 0) {
		y = power(a*a,n/2);
	} else 
		y = power(a,n-1)*a;
	
	return y;
}

double P_General(double* pA, int n, double x){
	
	int k=0;
	double y=0;
	
	while(k<=n){
		y+=pA[k]*power(x,k);
	}
	
	return y;
}

int main(){

	int n,k=0;
	double x;
	
	printf("Enter n: ");
	scanf("%d",&n);
	
	double* ptr = new double[n+1];
	printf("\nEnter elements from 0 to %d",n);
	printf(": \n");
	while(k<=n){
		printf("%d",k);
		printf(": ");
		scanf("%lf",&ptr[k]);
		printf("\n");
		k++;
	}
	printf("\nEnter x: ");
	scanf("%lf",&x);
	
	printf("\nHorner's Rule: %lf\n",P_Horner(ptr,n,x));
	printf("\nGeneral Algo: %lf\n",P_General(ptr,n,x));
		
	_getch();
}

