#include <conio.h>
#include <stdio.h>

bool setcmp(int,int,int*,int*,int*,int*);

int main()
{
	int N,M;
	int cr = 0;
	int* len = &cr;
	printf("Enter N and 1st SET: ");
	scanf("%d",&N);
	fflush(stdin);
	
	int* S1 = new int[N];
	for(int i = 0; i < N; i++) {
		scanf("%d",&S1[i]);
		printf(" ");
	}
	fflush(stdin);
	
	printf("Enter M and 2nd SET: ");
	scanf("%d",&M);
	fflush(stdin);
	
	int* S2 = new int[M];
	for(int i = 0; i < M; i++) {
		scanf("%d",&S2[i]);
		printf(" ");
	}
	fflush(stdin);
	
	int* S3 = new int[(M > N) ? N : M];
	
	if(setcmp(N,M,S1,S2,len,S3)) {
		printf("\n\nCross: ");
		for(int i = 0; i < cr; i++) {
			printf("%d ",S3[i]);
		}
	} else {
		printf("Empty!");
	}
	
	_getch();
}

bool setcmp(int N, int M, int* S1, int* S2, int* len, int* S3)
{
	int l = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if (S1[i] == S2[j]) {
				S3[l] = S1[i];
				l++;
			}
		}
	}
	
	*len = l;
	return (l > 0);
}
	