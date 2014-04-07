#include <conio.h>
#include <stdio.h>

int SQR(int);

int main()
{
	int N,a,b,c,count=0;
	printf("Enter N: ");
	scanf("%d",&N);
	printf("\n");
	fflush(stdin);
	
	/***************************/
	/***** WITHOUT REPEATS *****/
	
	for(int i = 1; i < N; i++) {
		c = i;
		for(int j = 1; j < N; j++) {
			a = j;
			for(int k = j; k < N; k++) {
			b = k;
				if((SQR(a) + SQR(b)) == SQR(c)) {
					count++;
					printf("%d: (%d  %d  %d)\n",count,a,b,c);
				}
			}
		}
	} //O(N^3);
	
	_getch();
}

int SQR(int x) {
	return x*x;
}
			