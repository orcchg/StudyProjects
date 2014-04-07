#include <conio.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX 10
#define MAXBIN 1000
#define MAXDEX 100

void reverse(char[],int);
void itoa(int);
void itob(int);
void itoh(int);
int power(int, int);

int main () {

	int i=0,c;
	char s[MAX];
	
	while((c=getchar())>='0' || c<='9'){
		if (c>'9' || i>MAX) {
			printf("wrong number!\n");
			break;
		}
		
		if (c=='\n')
			break;
		s[i]=c;
		i++;
	}

//	printf("%d\n",atoi(s));
	cout << endl;
	
	itoa(atoi(s));
	cout << endl;
	
	itob(atoi(s));
	cout << endl;
	
	itoh(atoi(s));
	
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
	
	reverse(s,i);
	cout << endl;
	cout << "itoa ended" << endl;
}

void itob(int N){
	
	char s[MAXBIN];
	int i=0,SIGN,k=0;
	
	if((SIGN=N)<0) //RECORD SIGN
		N=-N; //MAKE N POSITIVE
		
	do {	
		s[i]=N%2 + '0';
		N=N/2;
		i++;
	} while(N>1);
	
	if(N) 
		s[i]=N + '0';
	else
		s[i]='0';
	
	if(SIGN<0)
		s[i+1]='-';
	
	s[i+2]='\0';
	
	while(k<=i+1){
		cout << s[k];
		k++;
	}
	
	cout << endl;
	cout << "itob ended" << endl;
}

void itoh(int N){

	char s[MAXDEX];
	int i=0,j=0,SIGN,k=0,M=0,TEMP=0,MT=0;
	
	if((SIGN=N)<0) //RECORD SIGN
		N=-N; //MAKE N POSITIVE
	
	M=N;
	do {
		M=M-MT*power(16,TEMP);
		i=0;	
		MT=M;
	
	do {
		MT/=16;
		i++;
	} while(MT>0);
	
	TEMP = i-1;
	MT=M;
	
	for(int u=0; u<TEMP; u++){
		MT/=16;
	}
	
	switch(MT){
		case 0:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			s[j]=MT + '0';
			break;
		case 10:
			s[j]='A';
			break;
		case 11:
			s[j]='B';
			break;
		case 12:
			s[j]='C';
			break;
		case 13:
			s[j]='D';
			break;
		case 14:
			s[j]='E';
			break;
		case 15:
			s[j]='F';
			break;
		default:
			break;
	}
	j++;
} while (M>=16);
	
	j++;
	switch(M){
		case 0:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			s[j]=i + '0';
			break;
		case 10:
			s[j]='A';
			break;
		case 11:
			s[j]='B';
			break;
		case 12:
			s[j]='C';
			break;
		case 13:
			s[j]='D';
			break;
		case 14:
			s[j]='E';
			break;
		case 15:
			s[j]='F';
			break;
		default:
			break;
	}
	
	if(SIGN<0)
		s[j+1]='-';
	
	s[j+2]='\0';
	
	cout << "0x";
	while(k<=i+1){
		cout << s[k];
		k++;
	}
	
	cout << endl;
	cout << "itoh ended" << endl;
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

int power(int a, int n) {
	
	int k=n, b=1, c=a;
	
while (k!=0){	
	if(k % 2 == 0){
		k/=2;
		c*=c;
	} else {
		k--;
		b*=c;
	}
}
	return (b);
}