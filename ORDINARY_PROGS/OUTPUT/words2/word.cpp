#include <cstdio>
#define YES = 1
#define NO 0
#define eof -1

int main() {
	
	int c, NL, NW, INWORD, NC;
	INWORD = NO;
	NL=NW=NC=0;
	
	while((c=getchar())!=eof){
		++NC;		
		if (c=='\n')
			++NL;
		if(c==' ' || c=='\n' || c=='\t'){
			INWORD = NO;
			printf("\n");
			}
		else if (INWORD==NO){
			putchar(c);
		//	INWORD = YES;
			++NW;
		}
	}
	return 0;
}