#include <conio.h>
#include <stdio.h>
#include <math.h>

bool is_square(int);

int main()
{
	int N;
	printf("Enter N: ");
	scanf("%d",&N);
	printf("\n");
	fflush(stdin);
	
	int* A = new int[N];
	
	printf("Enter N numbers: ");
	for(int i = 0; i < N; i++) {
		printf("%d: ",i+1);
		scanf("%d",&A[i]);
		fflush(stdin);
		printf("\n");
	}
	
	for(int i = 0; i < N; i++) {
		if (is_square(A[i])) {
			printf("%d ",A[i]);
		}
	}
	
	_getch();
}

bool is_square(int N)
{
	double X = sqrt(N);
	int Y = (int)X;
	double r = 0;
	
	r = X - Y;
	return (r == 0);
}
	