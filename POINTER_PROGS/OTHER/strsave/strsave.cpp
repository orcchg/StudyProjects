#include <conio.h>
#include <cstdio>
#include <cstring>
#include "alloc.h"

#define MAXLEN 1000

char* strsave(char*);

int main(){

	int i=0,c;
	char s[MAXLEN];
	char* pS=NULL;
	
	while((c=getchar())!='\n'){
		s[i]=c;
		i++;
	}
	s[i++]='\0';
	
	pS=strsave(s);
	printf("%s\n",pS);
	_getch();
}

char* strsave(char* s){

	char* pS;
	if((pS=alloc(strlen(s)+1))!=NULL)
		strcpy(pS,s);
	
	return(pS);
}