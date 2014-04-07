#include <conio.h>
#include "randc.h"

int main()
{
	int N;	
	double R,A,B;
	
	printf("Circle: (x-A)^2 + (y-B)^2 <= R^2\n");
	printf("Enter N; R; A; B;: ");
	scanf("%d %lf %lf %lf",&N,&R,&A,&B);
	printf("\n");
	fflush(stdin);
	
	for(int i = 0; i < N; i++) {
		char* str = new char[100];
		
		str = Randc(R,A,B);
		printf("\n%s",str);
		fflush(stdin);
		
		delete [] str;
	}
		
	_getch();
}