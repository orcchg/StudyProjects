#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N,M,i,j;
	printf("Enter N cold and M strings: ");
	scanf("%d %d",&N,&M);
	printf("\n");
	fflush(stdin);
	
	int** mat = new int*[N];
	int** mir = new int*[N];
	
	for( int k = 0; k < N; k++)
        mat[k] = new int[M];
		
	for( int k = 0; k < N; k++)
        mir[k] = new int[M];
		
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
	
	for ( j = 0; j < M; j++) {
        for (i = 0 ; i < N ; i++)
        {
            mir[i][j] = mat[N-i-1][M-j-1];
        }
	}
	
	printf("MIRROR MATRIX\n\n\n");
	for ( j = 0; j < M; j++) {
        for (i = 0 ; i < N ; i++)
        {
            printf("%d ",mir[i][j]);
        }
		printf("\n\n");
	}
	
	_getch();
}