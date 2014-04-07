#include <conio.h>
#include <cstdio>
#include <iostream>
using namespace std;

#define MAX 1000

void reverse(char[],int);

int main () {

	int i=0,c;
	char s[MAX];
	
	while((c=getchar())!='\n' && i<=MAX){
		s[i]=c;
		i++;
	}

	reverse(s,i);
	
	_getch();
	return 0;
}

void reverse(char s[],int length){

	int TEMP,i,j,k=0;
	
	for(i=0,j=length-1;i<j;i++,j--){
		TEMP = s[i];
		s[i] = s[j];
		s[j] = TEMP;
	}
	
	while(k<=length-1){
		cout << s[k];
		k++;
	}
}
