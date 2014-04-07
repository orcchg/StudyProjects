#include <cstdio>
#include "defines.h"

int getline(char s[],int LIM){
	
	int i=0,c;
		for(i=0; i<LIM-1 && (c=getchar())!=eof && c!='\n'; ++i)
			s[i]=c;

	if(c=='\n')
		s[i]=c;
		
	s[i]='\0';
	
	return (i);
}

void copy(char s1[], char s2[]){
	
	int i=0;
		while((s2[i]=s1[i])!='\0')
			++i;
}
