#include <stdio.h>
#include <math.h>
#include <conio.h>

int main()
{
	int N, P, A, N2;
	
	scanf("%d", &N);
	
	N2 = 2*N;
	
	A = 1;
//	printf("%d %d\n", A, P);
	
	for(P = (int)sqrt((double)N2) ; ; --P)
	{
		A = N2 / P + 1 - P;
		A /= 2;
//		printf("%d %d\n", A, P);
		if (A > 0 && (2*A + P - 1)*P == N2)
		{
			break;
		}
	}
	
	printf("%d %d", A, P);
//	_getch();
	return 0;
}