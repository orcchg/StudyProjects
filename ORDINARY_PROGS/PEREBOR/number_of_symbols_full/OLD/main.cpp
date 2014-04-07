#include <conio.h>
#include <stdio.h>
	
#define MAXLIM 1000//INPUT STRING MAX LENGTH	
#define MAXLEN 256 //NUMBER OF SYMBOLS ASCII
	
int main()
{
	char s[MAXLIM];
	char c;
	int i=1,r=1;
	long count[MAXLEN];
	
	s[0]='\0';
	for(int y=0; y<MAXLEN; y++)
			count[y]=0;
	
	while((c=getchar())!=EOF) {
		s[i]=c;
		for(int j=i-1; j>=0; j--){
			if(s[i]!=s[j]) {
				count[i] = 1;
			} else {
				count[j]++;
			}
		}
		i++;
	}	
	
	for(int p=1; p<=i; p++) {
		printf("%c ->%d\n",s[p],count[p]);
	}
	
	_getch();
}