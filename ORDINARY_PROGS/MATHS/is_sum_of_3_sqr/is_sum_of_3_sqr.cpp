#include <conio.h>
#include <stdio.h>
#include <math.h>

int main()
{
	long N,a,b,c,i=0;
	
	printf("Enter N: ");
	scanf("%ld",&N);
	printf("\n");
	
	for(a = sqrt(N); a*a >= N/3; a--) {
		for(b = sqrt(N-a*a); b > 0; b--) {
			c = sqrt(N - a*a - b*b);
			if(a*a + b*b + c*c == N) {
				goto LABEL1;
			} else { 
				goto LABEL2;
			}
		}
	}
	
	LABEL1: printf("Yes!");
	_getch();
	return 0;
	LABEL2: printf("No!");
	_getch();
	return 0;
}