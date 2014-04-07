#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "class_matrix.hpp"

int main()
{
	int N,M,i,j;
	
	printf("Enter N cold and M strings: ");
	scanf("%d %d",&N,&M);
	printf("\n");
	fflush(stdin);
	
	srand(5);
	
	elem_t** mat = new elem_t*[N];
	for( int k = 0; k < N; ++k)
        mat[k] = new elem_t[M];
		
	for ( j = 0; j < M; ++j) {
        for ( i = 0; i < N; ++i) {
            mat[i][j] = 100*(double)rand()/RAND_MAX;
		}
	}
	
	elem_t** E = new elem_t*[N];
	for( int k = 0; k < N; ++k)
        E[k] = new elem_t[M];
		
	for ( j = 0; j < M; ++j) {
        for ( i = 0; i < N; ++i) {
            E[i][j] = 0.6 + i;
		}
	}
	
	elem_t** T = new elem_t*[N];
	for( int k = 0; k < N; ++k)
        T[k] = new elem_t[M];
	
	int num = 0;
	for ( j = 0; j < M; ++j) {
        for ( i = 0; i < N; ++i) {
           T[i][j] = ++num;
		}
	}
	
	printf("T MATRIX\n\n\n");
	for ( j = 0; j < M; ++j) {
        for (i = 0 ; i < N ; ++i)
        {
            printf("%lf ",T[i][j]);
        }
		printf("\n\n");
	}	
		
	printf("INITIAL MATRIX\n\n\n");
	for ( j = 0; j < M; ++j) {
        for (i = 0 ; i < N ; ++i)
        {
            printf("%lf ",mat[i][j]);
        }
		printf("\n\n");
	}		
		
	Matrix mtrx(N,M);
	mtrx.Fill(mat);
	mtrx.Mirror();
	
	elem_t det = 0, Tr = 0;
	Matrix Em(N,M), A(N,M), B(M,N), C(M,M),sum(N,M),dif(N,M), AA(N,M),AI(N,M);
	Em.Fill(E);
	
	printf("MATRIX A: \n");
	A.Fill(T);
	A.Print(.0);
	Tr = A.Trace();
	printf("TRACE A: %d\n",Tr);
	
	printf("MATRIX B: \n");
	B = A.Transpose();
	B.Print(.0);
	
	sum = Em + A ;
	dif = Em - A;
	printf("MATRIX sum = A + Em: \n");
	sum.Print(.0);
	printf("MATRIX dif = Em - A: \n");
	dif.Print(.0);
	
	printf("MATRIX C = AB: \n");
	C = A*B;
	C.Print(.0);
	
	AA = A*5.5d;
	printf("MATRIX A*5: \n");
	AA.Print();
	
	printf("MATRIX A*5.5: \n");
	AA.Print(0.0d);
	
	C=AA*B;
	
	printf("DET of C: \n");
	det = C.Determinant();
	printf("%lf \n",det);
	
/*	AI = A.Inverse();
	printf("A INVERSE: \n");
	AI.Print(.0);*/
	
	C.Inverse().Print(.0);
	
	_getch();
	return 0;
}