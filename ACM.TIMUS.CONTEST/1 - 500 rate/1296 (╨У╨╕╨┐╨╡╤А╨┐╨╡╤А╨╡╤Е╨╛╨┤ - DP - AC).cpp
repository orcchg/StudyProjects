#include <stdio.h>
#include <conio.h>

int main()
{

	int N; // 0 <= N <= 60000
	int max = 0, temp = 0;
	
	scanf("%d", &N);
	
	int* P = new int[N]; // -30000 <= P[i] <= 30000
	
	for(int i = 0; i < N; ++i)
	{
		scanf("%d", &P[i]);
	}
	
	if (P[0] > 0)
	{
		max = P[0];
	}
	temp = max;
	
	for(int i = 1; i < N; ++i)
	{
		temp = temp + P[i];
		if (temp <= 0)
		{
			temp = 0;
		}
		else
		{
			if (max <= temp)
			{
				max = (temp > temp - P[i]) ? temp : max;
			}
		}
	}
	
	printf("%d\n", max);
	
//	_getch();
	return 0;
}