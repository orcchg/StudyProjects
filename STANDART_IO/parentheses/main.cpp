#include <conio.h>
#include <cstdio>

int main(){

	int c,a=0;
	
	printf("Input the word of parentheses: ");
	
	do {
	c = getchar();
		if(c == '(')
			a++;
		else if (c == ')')
				if( --a < 0)
					break;
	} while (c != '\n');
	
	printf("\n");
	if( a == 0)
		printf("Success!\n");
	else
		printf("Failure!\n");

	_getch();	
	return 0;
}
			