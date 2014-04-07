#include <conio.h>
#include "trans.h"

int main()
{
	int N,c = 0,D;	
	
	printf("Enter N: ");
	scanf("%d",&N);
	D = N;
	printf("\n");
	fflush(stdin);
	
	while(D) {
		D /= 10;
		c++;
	}
	
	char* str = new char[N*c];
	
	str = Trans(N,c);
	
	printf("\n%s",str);
	delete [] str;
	_getch();
	return 0;
}