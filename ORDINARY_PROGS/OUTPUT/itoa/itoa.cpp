#include <conio.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX 10

void reverse(char[],int);
void itoa(int);

int main () {

	int i=0,c;
	char s[MAX];
	
	while((c=getchar())>='0' || c<='9' && i<=MAX){
		s[i]=c;
		i++;
	}

//	printf("%d\n",atoi(s));
	itoa(atoi(s));
	
	_getch();
	return 0;
}

void itoa(int N){

	char s[MAX];
	int i,SIGN;
	
	if((SIGN=N)<0) //RECORD SIGN
		N=-N; //MAKE N POSITIVE
	
	i=0;
	
	do //GENERATE DIGITS IN REVERSE ORDER
		s[i++] = N%10 + '0'; //GET NEXT DIGIT
	while((N/=10)>0);
	
	if(SIGN<0)
		s[i++]='-';
	
	s[i]='\0';
	
	cout << "itoa ended" << endl;
	
	reverse(s,i);
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