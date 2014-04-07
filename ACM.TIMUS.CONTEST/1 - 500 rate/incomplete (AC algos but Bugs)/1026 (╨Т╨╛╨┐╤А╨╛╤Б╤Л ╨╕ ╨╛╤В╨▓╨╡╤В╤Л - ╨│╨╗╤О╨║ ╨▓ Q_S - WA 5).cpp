#include <stdio.h>
#include <conio.h>

//----------------------------------------------------------------
void Q_S(__int64*, __int64, __int64);

void Quick_Sort(__int64* pA, __int64 n){

	Q_S(pA,0,n-1);
}

void Q_S(__int64* pA, __int64 p, __int64 r){

	__int64 i,j,q,temp;
	
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
//----------------------------------------------------------------

int main()
{
	__int64 N; // 1 <= N <= 100000
	
	scanf("%I64d", &N);
	
//	__int64* P = new __int64[N+1]; // 1 <= P[i] <= 5000
	__int64 P[100001];
	
	for(__int64 i = 1; i <= N; ++i)
	{
		scanf("%d", &P[i-1]);
	}
	
	char s[4];
	
	scanf("%s", s); // ###
	
	__int64 K; // 1 <= K <= 100
	
	scanf("%I64d", &K);
	
	__int64* I = new __int64 [K]; // 1 <= I <= N <= 100000
	
	for(__int64 i = 1; i <= K; ++i)
	{
		scanf("%d", &I[i-1]);
	}
	
	//----------------------------------------------------------------
	
	Quick_Sort(P, N);
	
	for(__int64 i = 0; i < K; ++i)
	{
		printf("%I64d\n", P[I[i]-1]);
	}
	
//	_getch();
	return 0;
}
	