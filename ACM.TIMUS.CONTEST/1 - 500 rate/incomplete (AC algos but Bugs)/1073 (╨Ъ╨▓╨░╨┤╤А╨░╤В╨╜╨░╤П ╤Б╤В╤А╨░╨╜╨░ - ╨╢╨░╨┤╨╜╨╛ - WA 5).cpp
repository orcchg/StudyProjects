#include <stdio.h>
#include <math.h>
#include <conio.h>

int main()
{
	int N, M = 0;
	double j = 0; // 1 <= N <= 60000
	
	scanf("%d", &N);
	
	int K = N;
	
	while(N)
	{
		if (modf(sqrt((double)K), &j) == 0)
		{
			++M;
			N -= K;
			K = N;
			continue;
		}
		K -= 1;
	}
	
	printf("%d", M);
//	_getch();
	return 0;
}	
		