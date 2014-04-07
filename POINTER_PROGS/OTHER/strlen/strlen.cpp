#include <conio.h>
#include <cstdio>

#define MAXLEN 1000

int strlen(char*);

int main() {
	
	int i=0,c;
	char s[MAXLEN];
	
	while((c=getchar())!='\n'){
		s[i]=c;
		i++;
	}
	s[i++]='\0';
	
	printf("%d\n",strlen(s));
	_getch();
}

int strlen(char* s){

	char* pP=s;
	
	while(*pP!='\0')
		pP++;
		
	return(pP-s);
}