#include <conio.h>
#include <cstdlib>
#include "readlines.h"

void tail(int,char*);
void Writelines(char*[],int,int); //char*[] == char**

int main(int argc, char* argv[]){

	char* pLINE[LINES]; //POINTERS TO TEXT LINES
	int NLINES; //NUMBER OF INPUT LINES READ
	int N=3; //DEFAULT NUMBER OF LAST LINES TO BE SHOWED
	char* pS=NULL;
	
	if((NLINES = readlines(pLINE,LINES)) >= 0){
	
		if(argc == 1)
			Writelines(pLINE,NLINES,N);
		else {
			while(--argc > 0 && (*++argv)[0] == '-'){
				pS = argv[0] + 1;
				N = atoi(pS);
				Writelines(pLINE,NLINES,N);
			}
		} 
		
	} else 
		printf("INPUT IS TOO BIG\n");
	
	_getch();	
	return 0;
}

void Writelines(char* pLINE[],int NLINES, int POSITION){

	int i;
	
	for(i = POSITION-1; i < NLINES; i++)
		printf("%s\n",pLINE[i]);
	
}