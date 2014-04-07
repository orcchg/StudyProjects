#include <cstdio>
#include <conio.h>

#define eof -1

int main () {

	int c,i,ND[10],NS,NO;
	
	NS = NO = 0;
		
		for(i=0; i<10; i++)
			ND[i] = 0;
			
		while((c=getchar())!=eof){
			
			switch (c){
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					ND[c-'0']++;
					break;
				case ' ':
				case '\t':
				case '\n':
					NS++;
					break;
				default:
					NO++;
					break;
			}
		}
		
		printf("DIGITS = ");
			for(i=0; i<10; i++)
				printf("%d", ND[i]);
				
		printf("\nSPACE = %d, OTHER = %d\n", NS, NO);
	
	_getch();
	return 0;
}