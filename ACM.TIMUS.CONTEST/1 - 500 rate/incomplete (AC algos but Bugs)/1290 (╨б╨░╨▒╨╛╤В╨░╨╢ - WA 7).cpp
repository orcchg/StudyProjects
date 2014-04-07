#include <iostream>
#include <conio.h>
using namespace std;

//-----------------------------------------------------------
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
//-----------------------------------------------------------


int main()
{

	int N, max;
	
	cin >> N;
	
	int* P = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> P[i];
	}

	Quick_Sort(P, N);
	
	max = P[N-1];
	int* Count = new int[max];
	for(int i = 0; i < max; ++i)
	{
		Count[i] = 0;
	}
	
	Count[0] = N;
	for(int i = 1; i < max; ++i)
	{
		for(int j = 1; j < N; ++j)
		{
			if (P[j] > i)
			{
				Count[i]++;
			}
		}
	}
	delete [] P;
	
	Quick_Sort(Count, max);
	
	int max2 = 0;
	max2 = Count[max-1];
	int* Count2 = new int[max2];
	for(int i = 0; i < max2; ++i)
	{
		Count2[i] = 0;
	}
	
	Count2[0] = max;
	for(int i = 1; i < max2; ++i)
	{
		for(int j = 1; j < max; ++j)
		{
			if (Count[j] > i)
			{
				Count2[i]++;
			}
		}
	}
	delete [] Count;
	
	for(int i = 0; i < max2; ++i)
	{
		cout << Count2[i] << " ";
	}
	delete [] Count2;
	
//	_getch();
	return 0;
}