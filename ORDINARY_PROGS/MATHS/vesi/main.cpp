#include <conio.h>
#include <stdio.h>

bool is_weighted(int);

int main()
{
	int N;
	printf("Enter weight N: ");
	scanf("%d",&N);
	printf("\n");
	
	if(is_weighted(N)) {
		printf("YES");
	} else {
		printf("NO");
	}
	
	_getch();
}

bool is_weighted(int N)
{
	if(N == 1) return true;
	if(N % 4 == 2) { 
		return false;
	} else if (N % 4 == 0 || N % 4 == 1 || N % 4 == 3) {
		return true;
	}
}