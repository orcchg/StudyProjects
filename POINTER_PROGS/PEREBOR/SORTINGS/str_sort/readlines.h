#include "alloc.h"
#include "getline.h"
#include <cstring>

int readlines(char* pLINE[], int MAXLINES){

	int LEN = 0, NLINES;
	char* p;
	char LINE[MAXLEN];
	
	NLINES=0;
	
	while((LEN = getline(LINE,MAXLEN)) > 0){
		
		printf("%d\n",LEN);
		
		if(NLINES >= MAXLINES)
			return -1;
		
		else if ((p = alloc(LEN)) == NULL)
			return -1;
		
		else {
			LINE[LEN-1] = '\0'; //ZAP NEWLINE
			p = strcpy(p,LINE);
			pLINE[NLINES++] = p;
		}
	}
	
	return NLINES;
}

void writelines(char* pLINE[],int NLINES){

	int i;
	
	for(i = 0; i < NLINES; i++)
		printf("%s\n",pLINE[i]);
	
}