#include <conio.h>
#include <stdio.h>
#include <cstring>

#define MAXLEN 1000

int main()
{
	char ch;
	char s[MAXLEN],v[MAXLEN];
	int len,j=0;
	
	printf("Enter ch and string: ");
	scanf("%c %s",&ch,s);
	printf("%s\n",s);
	
	len = strlen(s);
	for(int i=0; i<len; i++){
		if(s[i] != ch)
			v[j++] = s[i];
	}
	
	printf("\nString: %s\n",v);
	
	_getch();
}