#include <cstdio>
#define YES 1
#define NO 0
#define eof -1

int main() {
	int c, NL, NW, NC, INWORD;
	
	INWORD = NO;
	NL = NW = NC = 0;
	
	while((c = getchar())!= eof){
		++NC;
		if (c == '\n')
			++NL;
		if (c == ' ' || c == '\n' || c == '\t')
			INWORD = NO;
		else if (INWORD == NO) {
			INWORD = YES;
			++NW;
		}
	}
	printf("%d %d %d\n", NL, NW, NC);
	return 0;
}