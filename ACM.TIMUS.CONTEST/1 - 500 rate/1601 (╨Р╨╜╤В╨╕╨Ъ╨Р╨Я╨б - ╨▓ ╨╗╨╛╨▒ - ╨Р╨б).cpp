#include <stdio.h>
#include <string.h>
#include <cctype>
#include <conio.h>

int main()
{
	int c, i = 0, count = 0;
	char buf[10005];
	
/*	c = getchar();

	if (islower(c))
	{
		c = toupper(c);
	}

	buf[i++] = c;
	//putchar(c);*/
		
	while((c=getchar())!=EOF)
	{
		if (i > 10000)
		{
			break;
		}
		
		if (c == '.' || c == '!' || c == '?')
		{
			//	putchar(c);
			buf[i++] = c;
			count++;
			continue;
		}	
		
		if (isalpha(c))
		{	
			if (count)
			{
				if (isupper(c))
				{
					count = 0;
				} 
				else
				{
					c = toupper(c);
					count = 0;
				}
			}
			else if (isupper(c))
			{
				c = tolower(c);
			}
			
		}
		
		//putchar(c);
		buf[i++] = c;
	}

	for(int j = 0; j < i; ++j)
	{
		if (isalpha(buf[j]))
		{
			buf[j] = toupper(buf[j]);
			break;
		}
	}
	
	for(int j = 0; j < i; ++j)
	{
		printf("%c", buf[j]);
	}
	
//	_getch();
	return 0;
}