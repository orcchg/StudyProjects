#include <conio.h>
#include <iostream>
#include <cstdio>

#define MAXLEN 1000
#define eof -1
using namespace std;

double Atof_exp(char[]);

int main() {

	int i=0,c;
	char s[MAXLEN];
	double f;
	
	while((c=getchar())!=eof){
		s[i]=c;
		i++;
	}
	
	f=Atof_exp(s);
	cout << f << endl;
	_getch();
	return 0;
}

double Atof_exp(char s[]){

	int VAL,POWER,SIGNEXP=1,EXP,MULT;
	int i=0,SIGN=1,j,k,p,q;
	
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
	
	if(s[k]=='e')
		k++;
	if(s[k]=='-'){
		SIGNEXP=-1;
		k++;
	}
	
	for(p=k; s[p]==' ' || s[p]=='\n' || s[p]=='\t'; p++)
		;
		
	EXP=0;	
	for(q=p; s[q]>='0' && s[q]<='9'; q++)
		EXP = 10*EXP + (int)s[q] - '0';
	
	MULT=1;
	for(q=1; q<=EXP; q++)
		MULT*=10; 
	
	if(SIGNEXP<0)
		return ((double)SIGN*(double)VAL/(double)POWER/(double)MULT);
	else
		return ((double)SIGN*(double)VAL/(double)POWER*(double)MULT);
}