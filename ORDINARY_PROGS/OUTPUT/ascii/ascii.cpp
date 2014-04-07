#include <conio.h>
#include <stdio.h>

int main(){

	int c;
	
	for(int i=0; i<256; i++){
		c = i;
		printf("%c ",c);
		if(i % 16 == 0)
			printf("\n");
		}
		
	_getch();
}