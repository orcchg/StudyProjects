#include <iostream>
#include <conio.h>
#include <stdio.h>
using namespace std;

int main()
{

	int N, SUM = 0;
	
	scanf("%d", &N);
	
	int* K = new int[N+1];
	
	for(int i = 1; i <= N; ++i)
	{
		scanf("%d", &K[i]);
		SUM += K[i];
	}
	
	int Q;
	
	scanf("%d", &Q);


	//------------------------------------------------
	
	int* I = new int[Q];
	int* J = new int[Q];	
	int* sum = new int[Q];
	int SUM2 = 0;
	
	for(int i = 0; i < Q; ++i)
	{
//		sum[i] = 0;
		scanf("%d%d", &I[i], &J[i]);
		
		if ((J[i] - I[i] + 1) >= (N + I[i] - J[i] - 1))
		{
			SUM2 = SUM;
			for(int j = 1; j < I[i]; ++j)
			{
				SUM2 -= K[j];
			}
			
			for(int j = J[i] + 1; j <= N; ++j)
			{
				SUM2 -= K[j];
			}
		}
		else
		{
			SUM2 = 0;
			for(int j = I[i]; j <= J[i]; ++j)
			{
				SUM2 += K[j];
			}
		}
		
		sum[i] = SUM2;
	}
	
	for(int i = 0; i < Q; ++i)
	{
		printf("%d\n", sum[i]);
	}

//	_getch();
	return 0;
}
		