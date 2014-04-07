#include <conio.h>
#include <cstdio>

void mult(double[]);
void mult(double*,int);

int main(){

	double s[10] {1,3.14,2.71,0.515,6.28,0.02,81.9,0.9999,11.77,2};
	double* pA;
	
	pA=s; //pA=&s[0];
	
	for(int i=0; i<10; i++){
		printf("%f\n",*(pA+i));
		printf("%f %f\n",pA[i],s[i]);
	}
	printf("\n");
	
	mult(s);
	mult(s,10);
	
	_getch();
}

void mult(double s[]){

	printf("mult array\n");
	for(int i=0; i<10; i++)
		printf("%f\n",s[i]*10);
		
	printf("\n");
}

void mult(double* s,int L){

	printf("mult pointer\n");
	for(int i=0; i<10; i++)
		printf("%f %f\n",s[i]*10,(*(s+i))*10);
		
	printf("\n");
}
		