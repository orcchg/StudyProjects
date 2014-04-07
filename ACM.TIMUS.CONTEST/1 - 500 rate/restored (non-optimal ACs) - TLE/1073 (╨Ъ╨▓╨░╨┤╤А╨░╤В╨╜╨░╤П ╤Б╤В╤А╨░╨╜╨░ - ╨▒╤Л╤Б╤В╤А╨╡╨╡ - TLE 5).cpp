#include <stdio.h>
#include <math.h>
#include <conio.h>

int main()
{
	int N, M = 0;
	double j = 0; // 1 <= N <= 60000
	
	scanf("%d", &N);
	
	if (modf(sqrt((double)N), &j) == 0)
	{
		M = 1;
		printf("%d", M);
		return 0;
	}
	
	for(int a = 0; a <= N; ++a)
	{
		for(int b = 0; b <= N; ++b)
		{
			for(int c = 0; c <= N; ++c)
			{
				for(int d = 1; d < N; ++d)
				{
					if ( (c*c + d*d) == N )
					{
						M = 2;
						printf("%d", M);
						return 0;
					}
					else if ( (b*b + c*c + d*d) == N)
					{
						M = 3;
						printf("%d", M);
						return 0;
					}
				}
			}
		}
		M = 4;
		printf("%d", M);
//		_getch();
		return 0;
	}
	
	return 0;
}	
		