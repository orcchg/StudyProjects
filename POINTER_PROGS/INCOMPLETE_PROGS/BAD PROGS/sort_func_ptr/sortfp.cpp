#include <conio.h>
#include <cstdio>
#include "sort_ptr.h"
#include "swap.h"
#include "numcmp.h"
#include "readlines.h"

#define LINES 100 //MAX NUMBER OF LINES TO BE SORTED

int main(int argc,char* argv[][2]){

	char* pLINE[LINES]; //POINTERS TO NEXT LINES
	int NLINES; //NUMBER OF INPUT LINES READ
	int NUMERIC = 0; //1 IF NUMER SORT PROCEDURE, 0 IF LEXIC SORT PROCEDURE
	
	if(argc > 1 && argv[1][0] == '-' && argv[1][1] == 'N')
		NUMERIC = 1;
		
	if((NLINES = readlines(pLINE,LINES)) >= 0){
		if(NUMERIC)
			sort(pLINE,NLINES,numcmp,swap);
		else
			sort(pLINE,NLINES,strcmp,swap);
	writelines(pLINE,NLINES);
	} else {
		printf("INPUT TOO BIG TO SORT\n");
	}
	_getch();
}