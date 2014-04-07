#include <cstdio>
#define MAXLINE 1000
#define eof -1
#include "reverse.h"
#include <conio.h>

int main(){

	int c,i,p;
	char s1[MAXLINE];
	
	i=0;
	while((c=getchar())!='\n'){
		s1[i]=c;
		i++;
	}
	
	p=i;
	printf("\n");
	reverse(s1, p);
	
	_getch();
	
return 0;
}	