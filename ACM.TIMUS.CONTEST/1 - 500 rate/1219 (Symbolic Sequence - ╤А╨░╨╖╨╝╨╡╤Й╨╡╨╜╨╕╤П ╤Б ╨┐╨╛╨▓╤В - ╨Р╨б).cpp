#include <stdio.h>
#include <conio.h>

int main()
{
	int n = 0;
	char c = 'a';
	
	int* A = new int[26];
	int* B = new int[26];
	int* C = new int[26];

while(1)
{	
	for(int i = 0; i < 26; ++i)
	{
		A[i] = i;
		for(int j = 0; j < 26; ++j)
		{
			B[j] = j;
			for(int k = 0; k < 26; ++k)
			{
				C[k] = k;
				printf("%c%c%c", A[i]+'a', B[j] + 'a', C[k] + 'a');
	//			printf("%d\n",n);
				n += 3;
				if (n == 999999)
				{
					goto LABEL;
				}	
			}
		}
	}
}
LABEL:	printf("%c",'m');
//	_getch();
	return 0;
}
			
				