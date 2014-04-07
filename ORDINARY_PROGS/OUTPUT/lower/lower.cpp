#include <conio.h>
#include <cstdio>
#include <cctype>

int main () {

	int C,c;
	
	C=getchar();
	
	printf("%c",(C>='A' && C <='Z') ? (char)tolower(C) : -1);
	
	_getch();
	
	}