#include <conio.h>
#include <stdio.h>

int main()
{
	double S1=0,S2=0;
	long i,j;
	
	for(i = 1, j = 10000001; i < 10000001, j > 0; i++, j--){
		S1 += 1.0/(double)i;
		S2 += 1.0/(double)j;
	}
	
	printf("S direct: %lf\nS reverse: %lf",S1,S2);
	_getch();
}