#include <conio.h>
#include <cstdio>

#define MAXLEN 1000

char* strcat(char*,char*);

int main() {

	int i=0,c;
	char s1[MAXLEN],s2[MAXLEN];
	
	printf("Enter S1: ");
	while((c=getchar())!='\n'){
		s1[i]=c;
		i++;
	}
	s1[i++]='\0';
	
	i=0;
	printf("\nEnter S2: ");
	while((c=getchar())!='\n'){
		s2[i]=c;
		i++;
	}
	s2[i++]='\0';
	
	printf("\n");
	
	printf("%sConcatenated: \n",strcat(s1,s2));
	
	_getch();
}

char* strcat(char* s1, char* s2){

	int i=0,j=0;
	char v[MAXLEN*2];
	char* pV=v,*pVi=0;
	
	while(*pV=*s1){ // (*pV++=*s1++)!='\0';
		i++;
		pV++;
		s1++;
	}
	
	pV=pV+i;
	
	while(*pV=*s2){
		j++;
		pV++;
		s2++;
	}	
	
	s1=0;
	
	for(int k=0; k<(i+j); k++)
		*s1=*(pV-i-j+k);
	
	return s1;
}