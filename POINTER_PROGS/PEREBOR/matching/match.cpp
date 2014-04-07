#include <iostream>
#include <cstdio>
#include <conio.h>
using namespace std;

#define MAXLEN 1000
#define eof -1

int getline(char[],int);
int index(char[], char[]);

int main(int argc,char* argv[]) {

	char LINE[MAXLEN];
	
	if(argc!=2)
		cout << "USAGE: FIND PATTERN\n";
	else
		while(getline(LINE,MAXLEN) > 0){
			if(index(LINE,argv[1]) >= 0)
				printf("%s",LINE);
		}
	
	_getch();
	return 0;
}

int getline(char s[], int LIM){
	
	int i=0,c;
	while(--LIM>0 && (c=getchar())!=eof && c!='\n')
		s[i++]=c;
		
	if(c=='\n')
		s[i++]=c;
	
	s[i]='\0';
	
	return (i);
}
	
int index(char s[], char t[]){

	int i,j,k;
	
	for(i=0; s[i]!='\0'; i++){
		for(j=i,k=0; t[k]!='\0' && s[j]==t[k]; j++,k++)
		;
		if(t[k]=='\0')
			return (i);
		}
		return -1;
}