#include <conio.h>
#include <iostream>
#include <cstdio>

#define MAXLEN 1000
#define eof -1
using namespace std;

double Atof(char[]);

int main() {

	int i=0,c;
	char s[MAXLEN];
	double f;
	
	while((c=getchar())!=eof){
		s[i]=c;
		i++;
	}
	
	f=Atof(s);
	cout << f << endl;
	_getch();
	return 0;
}

double Atof(char s[]){

	int VAL,POWER;
	int i=0,SIGN=1,j,k;
	
	for(i=0; s[i]==' ' || s[i]=='\n' || s[i]=='\t';i++)
		;
		
		if(s[i]=='-'){
			SIGN=-1;
			i++;
		}
	
	VAL=0;	
	for(j=i; s[j]>='0' && s[j]<='9'; j++){
		VAL = 10*VAL + (int)s[j] - '0';
	}
	
	if(s[j]=='.' || s[j]==',')
		j++;
	
	POWER=1;
	for(k=j; s[k]>='0' && s[k]<='9';k++){
		VAL = 10*VAL + (int)s[k] - '0';
		POWER*=10;
	}
	
	return ((double)SIGN*(double)VAL/(double)POWER);
}
		
