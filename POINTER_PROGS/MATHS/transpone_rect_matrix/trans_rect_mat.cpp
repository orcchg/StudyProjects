#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N,M,i,j;
	
while(!feof(stdin)) {

	printf("Enter N cold and M strings: ");
	scanf("%d %d",&N,&M);
	printf("\n");
	fflush(stdin);	

	int** mat = new int*[N];
	int** matT = new int*[M];
	
	for( int k = 0; k < N; k++)
        mat[k] = new int[M];
		
	for( int k = 0; k < M; k++)
        matT[k] = new int[N];
		
	for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            mat[i][j] = 100*(double)rand()/RAND_MAX;
		}
	}
	
	printf("INITIAL MATRIX\n\n\n");
	for ( j = 0; j < M; j++) {
        for (i = 0 ; i < N ; i++)
        {
            printf("%d ",mat[i][j]);
        }
		printf("\n\n");
	}
	
	for ( j = 0; j < M; j++)
        for (i = 0 ; i < N ; i++)
        {
            matT[j][i] = mat[i][j];
        }
		
	printf("\n\nTRANSPONED MATRIX\n\n\n");	
	for ( j = 0; j < N; j++) {
        for (i = 0 ; i < M ; i++)
        {
            printf("%d ",matT[i][j]);
        }
		printf("\n\n");
	}
	
}
	
	_getch();
}