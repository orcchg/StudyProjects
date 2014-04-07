#include <stdio.h>
#include <conio.h>

//----------------------------------------
void Insertion_Sort(int* pA,int n){

	int key,i;

	for(int j = 1; j < n; j++){
		key = pA[j];
		i = j - 1;
		
		while(i >= 0 && pA[i] > key){
			pA[i+1] = pA[i];
			i--;
			pA[i+1] = key;
		}
	}
}
//----------------------------------------

int main()
{

	int N, W = 0;
	
	scanf("%d", &N);
	
	int* P = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		scanf("%d", &P[i]);
	}
	
	Insertion_Sort(P, N);
	
	int count = 1;
	
	int temp = P[0];
	for(int i = 1; i < N; ++i)
	{
		if (P[i] == temp)
		{
			count++;
		}
		else
		{
			temp = P[i];
			count = 1;
		}
		
		if (count == 4)
		{
			W++;
			if (i != N - 1)
			{
				temp = P[i+1];
			}
			count = 0;
		}
	}
	
	printf("%d\n", W);
	
//	_getch();
	return 0;
}