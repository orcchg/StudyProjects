#include <conio.h>
#include "getint.h"
#include <cstdio>

#define SIZE 10

int main(){

	int N,V,ARRAY[SIZE];
	
	for(N=0; N<SIZE && getint(&V)!=eof; N++)
		ARRAY[N]=V;
		
	printf("%d\n",ARRAY);
	_getch();
}	
		