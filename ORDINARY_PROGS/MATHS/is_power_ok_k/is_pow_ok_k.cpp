#include <conio.h>
#include <stdio.h>
#include <math.h>

bool is_power_of_k(int,int);

int main()
{
	int N,K;
	printf("Enter K and N: ");
	scanf("%d %d",&K,&N);
	printf("\n");
	fflush(stdin);
	
	int* A = new int[N];
	
	printf("\nEnter N numbers: ");
	for(int i = 0; i < N; i++) {
		printf("%d: ",i+1);
		scanf("%d",&A[i]);
		printf("\n");
		fflush(stdin);
	}
	
	for(int i = 0; i < N; i++) {
		if (is_power_of_k(A[i],K)) {
			printf("%d ",A[i]);
		}
	}
	
	delete [] A;
	_getch();
}

bool is_power_of_k(int N,int K)
{
	int C = N;
	while(C > 1 && (C % K == 0)) {
			C /= K;
		}
		
	return (C == 1);
}