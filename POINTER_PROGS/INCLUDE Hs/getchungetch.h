#include <cstdio>

#define BUFSIZE 100

char BUF[BUFSIZE];

int BUFP = 0;

int Getch(){
	return((BUFP > 0)? BUF[--BUFP] : getchar());
}

void Ungetch(int c){

		if(BUFP > BUFSIZE)
			printf("UNGETCH: TOO MANY CHARACTERS\n");
		else
			BUF[BUFP++] = c;
}
			