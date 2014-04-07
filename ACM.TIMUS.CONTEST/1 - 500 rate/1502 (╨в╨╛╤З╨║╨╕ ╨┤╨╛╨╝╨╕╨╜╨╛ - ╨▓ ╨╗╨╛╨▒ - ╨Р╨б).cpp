#include <stdio.h>
#include <conio.h>

int main()
{
	int N;
	double M = 0;
	
	scanf("%d", &N);
	
	for(int k = 1; k <= N; ++k)
	{
		M += 0.5 * (N - k + 1) * (N + 3 * k);
	}
	
	M += 0.5 * N * (N + 1);
	
	printf("%.0lf\n", M);
//	_getch();
	return 0;
}