#include <stdio.h>
#include <conio.h>
#include "string_methods.h"

int main()
{
	char* s1 = "adsfddgfghkjlkjlkjjjhhggfdgfdgdsfdasdsa";
	char* s2 = "ewwqrewrtetrytuyiyuiouipoxzcvcxcvbcbnvm";
	
/*	char* s1 = "aaad";
	char* s2 = "adab";
*/	char* s3 = new char[10];
	
	printf("1: %d\t2: %d\n\n", strlen(s1), strlen(s2));
	
	printf("1: %s\n2: %s\n2rev: %s", s1, s2, strrev(s2, s2));
	
	printf("\n\n1 > 2 ?: %s\n\n", (strcmp(s1, s2)) ? s1 : s2);
	
//	s3 = strcat(s2, s1);
	
	printf("%s\n", s3);
	
	_getch();
	return 0;
}