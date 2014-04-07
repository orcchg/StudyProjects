int strlen(const char* str)
{
	int c = 1, i = 0;
	
	while(c)
	{	
		c = str[i];
		++i;
	}
	--i;
	
	return i;
}

#include <stdlib.h>
#include <stdio.h>

char* strcat( char* dest, char* src )
 {
      while (*dest) dest++;
      while (*dest++ = *src++);
	  *dest = '\0';
      return dest;
 }

char* strrev(char* destination, const char* source)
{
	int i = 1;
	int len_src = strlen(source);
	int length = strlen(destination) + len_src + 1;
	
	char* dest = (char*)calloc(length, sizeof(char));
	
	while(i <= len_src)
	{
		dest[i-1] = source[len_src - i];
		++i;
	}
	dest[i-1] = '\0';
	
	return dest;
}

int strcmp(const char* str1, const char* str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i = 0;
	
	if (len1 > len2)
	{
		return 1;
	}
	else if (len1 < len2)
	{
		return 0;
	}
	else
	{
		while(str1[i] - str2[i] == 0 && i <= len1)
		{
			++i;
		}
		return (str1[i] > str2[i]) ? 1 : 0;
	}
}