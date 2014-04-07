#include <conio.h>
#include <cstdio>
#include <cstdlib>

#define MAXLEN 10
#define eof -1

void Printd(int);
void PrintdRec(int);

int main(){

	int i=0,c,k;
	char s[MAXLEN];
	
	while((c=getchar())!='\n'){
		s[i]=c;
		i++;
	}

	Printd(atoi(s));
	printf("\n");
	PrintdRec(atoi(s));
	
	_getch();
	return 0;
}

void Printd(int N){

	char s[MAXLEN];
	int i;
	
	if(N<0){
		putchar('-');
		N=-N;
	}
	
	i=0;
	
	do {
		s[i++]=N%10+'0';
	} while ((N/=10)>0);
	
	while(--i>=0)
		putchar(s[i]);
}

void PrintdRec(int N){

	int i;
	if(N<0){
		putchar('-');
		N=-N;
	}
	
	if((i=N/10)!=0)
		PrintdRec(i);
	putchar(N%10+'0');
}
