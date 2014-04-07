#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* str = new char[100];
	int i = 0,Nch=0,NW=0,k=0;
	
	while(!feof(stdin)) {
		str[i] = getchar();
		i++;
		if(i >= 99) {
			str = (char*)(str,210*sizeof(char));
		}
	}
	
	int* Noth = new int[i*sizeof(int)];
	char* temp = new char[i*sizeof(char)];
	char* oth = new char[i*sizeof(char)];
	char* v = new char[i*sizeof(char)];
	
	for(int j = 0; j < i; j++) {
		if((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z')) {
			temp[Nch] = str[j];
			Nch++;
		} else if(str[j] != '\n' || str[j] != '\t' || str[j] != ' ') {	
			oth[k] = str[j];
			Noth[k] = j;
			k++;
		}
	}