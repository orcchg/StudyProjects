#include <conio.h>
#include <stdio.h>
#include <cctype>

int main()
{
	char c;
	int i=0;
	
	while((c=getchar())!=EOF){
		if (c==',' || c==':' || c==';' || c=='.' || c==' ' || c=='!' || c=='?') {
			ungetch(c);
		} else if (c>='0' && c<='9') {
			ungetch(c);
		} else if (c>='A' && c<='Z') {
			c = tolower(c);
			putchar(c);
		} else if (c==' ' || c=='\n' || c=='\t') {
			ungetch(c);
			i++;
		} else {
			if(i!=0) { 
				putchar(' ');
				i=0;
			}
			putchar(c);
		}
	}
	
	_getch();
}