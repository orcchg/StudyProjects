#include <cstdio>
#define YES 1
#define NO 0
#define eof -1

void HorizHist(int NW,int length[NW]);
void VertHist(int NW,int length[NW],int MAX);
int getmax(int NW, int length[NW]);

int main() {

	int c, NC, NL, NW, INWORD, length[NW];
	
	INWORD = NO;
	
	NC = NL = NW = 0;
	
	while((c=getchar())!=eof){
		++NC;
		if (c == '\n')
			++NL;
		if (c == ' ' || c == '\n' || c == '\t')
			INWORD = NO;
		else if (INWORD == NO)
			INWORD = YES;
			length[NW]=NC;
			++NW;			
	}
	printf("\n");
	HorizHist(NW,length[NW]);
	
	printf("\n");
//	VertHist(NW, length[NW], getmax(NM,length[NM]));
	
	return 0;
}

void HorizHist(int NW, int length[NW]){
	int j;
	
	for (int i=1; i<=NW; i++){
		j=0;
		while(j<=length[i]){
			printf("#");
			j++;
		}
	printf("\n");
}

void VertHist(int NW, int length[NW], int MAX){
	int j=0;

	while (j<=MAX){
		j++;
		for (int i=1; i<=NW; i++){
			if (length[i]!=0)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}

int getmax(int NW, int length[NW]){
	int MAX=length[0];
	
	for(i=1; i<=NW; i++){
		if (MAX < length[i])
			MAX = length[i];
	}
	
	return MAX;
}
	
		