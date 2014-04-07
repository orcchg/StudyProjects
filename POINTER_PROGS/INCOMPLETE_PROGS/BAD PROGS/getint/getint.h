#include "chars.h"

#define eof -1

int getint(int* pN){

	int c,SIGN;
	
	while((c=getch())==' ' || c=='\n' || c=='\t')
		;
		
	SIGN=1;
	
	if(c=='+' || c=='-'){
		SIGN=(c=='+')? 1: -1;
		c=getch();
	}
	
	for(*pN=0; c>='0' && c<='9'; c=getch())
		*pN=10**pN + c - '0';
	
	*pN*=SIGN;
	
	if(c!=eof)
		ungetch(c);
	
	return (c);
}