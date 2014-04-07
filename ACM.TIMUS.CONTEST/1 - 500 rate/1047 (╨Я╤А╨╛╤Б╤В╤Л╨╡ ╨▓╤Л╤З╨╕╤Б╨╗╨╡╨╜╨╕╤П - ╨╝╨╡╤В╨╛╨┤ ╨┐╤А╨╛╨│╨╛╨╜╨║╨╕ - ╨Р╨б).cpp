#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

//------------------------------------
void solveMatrix (int n, double *a, double *c, double *b, double *f, double *x)
{
        /**
         * n - число уравнений (строк матрицы)
         * c - главная диагональ матрицы A
         * a - диагональ, лежащая под главной
         * b - диагональ, лежащая над главной
         * f - правая часть (столбец)
         * x - решение, массив x будет содержать ответ
         */
        for (int i = 1; i < n; i++)
        {
                double m = a[i]/c[i-1];
                c[i] = c[i] - m*b[i-1];
                f[i] = f[i] - m*f[i-1];
        }
 
        x[n-1] = f[n-1]/c[n-1];  
 
        for (int i = n - 2; i >= 0; i--)  
                x[i]=(f[i]-b[i]*x[i+1])/c[i];
 
}
//------------------------------------

int main()
{
	int N;
	
	scanf("%d", &N);
	
	double a0, aN1, a1;
	
	cin >> a0;
	cin >> aN1;
	
	double* c = new double[N];
	double* X = new double[N];
	double* B = new double[N];
	double* C = new double[N];
	double* A = new double[N];
	double* F = new double[N];
	
	for(int i = 0; i < N; ++i)
	{
		scanf("%lf", &c[i]);
		A[i] = 0.5;
		C[i] = -1.0;
		B[i] = 0.5;
		F[i] = c[i];
	}
	F[0] -= 0.5*a0;
	F[N-1] -= 0.5*aN1;
	
	solveMatrix (N, A, C, B, F, X);
	
	a1 = X[0];
	
	printf("%.2lf", a1);
//	_getch();
	return 0;
}