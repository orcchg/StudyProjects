#include <conio.h>
#include <cstdio>
#include <ctype.h>

int main(){
	
	int c;
	while((c=getchar())!=EOF)
		putchar(tolower(c));
	
	_getch();
}