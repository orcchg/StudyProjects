#include <stdio.h>

int getline(char* s, int len){

	int c,i=0;
	while(--len>0 && (c=getchar())!=EOF && c!='\n'){
		s[i++]=c;
	}
	
//	if(c == '\n')
//		s[i++]=c;
//		
//	s[i] = '\0';
	
//	return i-1;
	return i;
}