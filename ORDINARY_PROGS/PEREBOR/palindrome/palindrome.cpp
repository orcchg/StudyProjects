#include <stdio.h>
#include <conio.h>

const int MAXLEN = 1000;

int main()
{
	char* s = new char[MAXLEN];
	int i = 0;
	int c;
	
	while((c = getchar()) != '\n')
	{
		s[i++] = c;
	}
	
	for(int j = 0; j < i/2 + 1; ++j)
	{
		int difference = 0;
		difference = s[j] - s[i - 1 - j];
		
		if (difference != 0)
		{
			printf("NO\n");
			_getch();
			return 0;
		}
	}
	
	printf("YES\n");
	
	_getch();
	return 0;
}