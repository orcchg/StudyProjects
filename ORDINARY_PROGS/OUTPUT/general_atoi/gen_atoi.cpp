#include <cstdio>
#include <conio.h>

#define MAX 1000
#define eof -1

int gen_atoi(char[]);

int main () {

	int i=0,c;
	char s[MAX];
	
	while((c=getchar())!=eof){
		s[i]=c;
		i++;
	}
	
	printf("%d", gen_atoi(s));
	
	_getch();
	return 0;
}

int gen_atoi(char s[]){
	
	int i,N,SIGN;
		
		for(i=0;s[i]==' ' || s[i]=='\t' || s[i]=='\n';i++)
			; //SKIP SPACE
			
	SIGN=1;
		if(s[i]=='+' || s[i]=='-') //SIGN
			SIGN=(s[i++]=='+')?1:-1;
			
		for(N=0;s[i]>='0' && s[i]<='9';i++)
			N=10*N+s[i]-'0';
	return(SIGN*N);
}