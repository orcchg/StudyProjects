#include <stdio.h>
#include <conio.h>

int main()
{
	int n = 3;
	char c = 'a';
	
	int i = 0;
	
	int* A = new int[26];
	int* B = new int[26];
	int* C = new int[26];
	
	for(int i = 0; i < 26; ++i)
	{
		A[i] = i;
		for(int j = 0; j < 26; ++j)
		{
			B[j] = j;
			for(int k = 0; k < 26; ++k)
			{
				C[k] = k;
				printf("%c%c%c\n", A[i]+'a', B[j] + 'a', C[k] + 'a');
			}
		}
	}
	
	_getch();
	return 0;
}
			
				