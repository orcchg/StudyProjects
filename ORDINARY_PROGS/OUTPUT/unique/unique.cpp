#include <conio.h>
#include <iostream>
#include <cstdio>

#define eof -1
#define MAX 1000
using namespace std;

void unique(char[],int);

int main () {

	int c,i=0;
	char s[MAX];
	
	while((c=getchar())!=eof){
		s[i]=c;
		i++;
	}
	
	unique(s,i);
	_getch();
	return 0;
}

void unique(char s[], int length) {

	int i=0,j=0,k=0;
	char v[MAX];
	
	v[j]=s[i]; //i=j=0
	for(i=1; i<length; i++){
		if(s[i]==s[i-1])
			continue;
		v[++j]=s[i];
	}
	
	cout << endl;
	
	while(k<=j){
		cout << v[k];
		k++;
	}
	
	cout << endl;
}