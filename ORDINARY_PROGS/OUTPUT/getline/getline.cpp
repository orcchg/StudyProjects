#include <conio.h>
#include <cstdio>

#define MAXLEN 1000
#define eof -1

int getline(char[], int);
void copy(char[], char[]);

int main() {

	int LEN,MAX;
	char LINE[MAXLEN], SAVE[MAXLEN];
	
	MAX=0;
	
	while((LEN=getline(LINE,MAXLEN))>0){
		if(LEN>MAX) {
			MAX = LEN;
			copy(LINE,SAVE);
			
			if(MAX>0) //THERE WAS A LINE
				printf("%s",SAVE);
		}
	}
	_getch();
	return 0;
}

int getline(char s[],int LIM){
	
	int i=0,c;
		for(i=0; i<LIM-1 && (c=getchar())!=eof && c!='\n'; ++i){
			s[i]=c;
			if(c=='\n')
				s[i]=c;
		}
	++i;
	s[i]='\0';
	
	printf("%d\n",i);
	return (i);
}

void copy(char s1[], char s2[]){
	
	int i=0;
		while((s2[i]=s1[i])!='\0')
			++i;
}
