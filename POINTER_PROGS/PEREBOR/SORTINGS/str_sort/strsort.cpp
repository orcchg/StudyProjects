#include <conio.h>
#include "readlines.h"
#include "sort.h"

int main() {

	char* pLINE[LINES]; //POINTERS TO TEXT LINES
	int NLINES; //NUMBER OF INPUT LINES READ
	
	if((NLINES = readlines(pLINE,LINES)) >= 0){
		
		sort(pLINE,NLINES);
		writelines(pLINE,NLINES);
	
	} else 
		printf("INPUT IS TOO BIG TO SORT\n");
	
	_getch();	
	return 0;
}