#include <iostream>
#include <conio.h>
#include <stdio.h>
using namespace std;

void Q_S(int*, int, int);

void Quick_Sort(int* pA, int n){

	Q_S(pA,0,n-1);
}

void Q_S(int* pA, int p, int r){

	int i,j,q,temp;
	
	i = p;
	j = r;
	q = (p+r)/2;
	
	do {
		while((pA[i] < pA[q]) && (i < r))
			i++;
		while((pA[q] < pA[j]) && (j > p))
			j--;
		
		if(i <= j){
			temp = pA[i];
			pA[i] = pA[j];
			pA[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	
	if(p < j)
		Q_S(pA,p,j);
	if(i < r)
		Q_S(pA,i,r);
}

int main()
{
	int N, M; // 1..N candidates; M electors;
	double temp = 0.0;
	
	cin >> N >> M;
	
	int* A = new int[M];
	int* R = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		R[i] = 0;
	}
	
	for(int i = 0; i < M; ++i)
	{
		cin >> A[i];
		R[A[i]-1]++;
	}
	
/*	Quick_Sort(A, M);
	
	int j = A[0]-1;
	R[j] = 1;
	
	for(int i = 1; i < M; ++i)
	{
		if (A[i] == A[i-1])
		{
			R[j]++;
		}
		else
		{
			j = A[i] - 1;
			R[j] = 1;
		}
	}
*/
	for(int i = 0; i < N; ++i)
	{
		temp = (double)R[i]*100.0/M;
		printf("%.2lf",temp);
		cout << "\%";
		printf("\n");
	}
	
//	_getch();
	return 0;
}