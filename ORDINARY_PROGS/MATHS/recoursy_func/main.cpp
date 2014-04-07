// F(1) = 1; 	F(2N) = F(N);	 F(2N+1) = F(N) + F(N+1);

#include <conio.h>
#include <stdio.h>

int main()
{ 
	int N, K, Ans = 1;
	int Even_Sum = 1, Odd_Sum = 1;

	printf("Enter N: ");
	scanf("%d",&N);
	printf("\n");
	fflush(stdin);
	
	K = N;
	
	if (K % 2 == 0)
	{
		while(K % 2 == 0)
		{
			K /= 2;
		}
	}
	
	if (K == 1)
	{
		printf("Answer: %d", Ans);
	}
	else
	{
		int M = 0, c = 0;
		
		while(K > 1)
		{
			if ((K - 1)/2 % 2 == 0)
			{
				M = (K - 1)/2;
				K = M + 1;
			}
			else
			{
				K = (K - 1)/2;
				M = K + 1;
			}
			
			if (M/2 % 2 == 0)
			{
				Even_Sum += Odd_Sum;
			}
			else
			{
				c = Odd_Sum;
				Odd_Sum += Even_Sum;
				Even_Sum = c;
			}
		}
		
	}
	
	Ans = Odd_Sum;
	printf("Answer: %d", Ans);
	
	_getch();
	
	return 0;
}
			