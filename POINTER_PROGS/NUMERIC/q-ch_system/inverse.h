#include <iostream>
#define MAXLEN 1000

char* inverse(char s[],int length){

	int i,j=length,k=0;
	char* ptr = new char[length];
	
	for(i=0;i<length;i++){
		ptr[i] = s[j];
		j--;
	}
	ptr[i++]='\0';
	
	return ptr;
}