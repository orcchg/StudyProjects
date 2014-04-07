#include <cstdio>
#define BUFSIZE 100

char BUF[BUFSIZE];
int BUFP = 0;

int getch(){
	return((BUFP>0)? BUF[--BUFP]: getchar());
}

void ungetch(char c){
	if(BUFP>BUFSIZE)
		printf("UNGETCH: TOO MANY CHARACTERS\n");
	else
		BUF[BUFP++]=c;
}