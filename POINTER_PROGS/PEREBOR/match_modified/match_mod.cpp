#include <conio.h>
#include <iostream>
#include "index.h"
using namespace std;

#define MAXLEN 1000

int main(int argc,char* argv[]){

	char LINE[MAXLEN], *pS;
	long LINENO = 0;
	int EXCEPT = 0, NUMBER = 0;
	
	while(--argc > 0 && (*++argv)[0] == '-'){
		for(pS = argv[0] + 1; *pS != '\0'; pS++){
		
			switch(*pS){
				case 'X':
					EXCEPT = 1;
					break;
				case 'N':
					NUMBER = 1;
					break;
				default:
//					printf("FIND: ILLEGAL OPTION %c\n",*pS);
					cout << "FIND: ILLEGAL OPTION " <<  *pS << endl;
					argc = 0;
					break;
			}
		}
	}	
	if(argc != 1)
		printf("USAGE: FIND -X -N PATTERN\n");
	else
		while(getline(LINE,MAXLEN) > 0){
			LINENO++;
			if((index(LINE,*argv) >= 0) != EXCEPT){
				if(NUMBER)
					printf("%d: ", LINENO);
				printf("%s", LINE);
			}
		}
	_getch();
}