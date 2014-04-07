#include <conio.h>
#include <stdio.h>

char s[50];
int i = 0;

void Magic(int);

int main(){

	int N;
	printf("Enter N: ");
	scanf("%d",&N);
	printf("\n");
	
	Magic(N);
	
	printf("\n\n");
	for(int j = i; j >= 0; j--) {
		printf("%c",s[j]);
	}
	
	_getch();
}

void Magic(int N)
{
	printf("%d",N % 2);
	s[i] = N % 2 + '0';
	i++;
	
	if(N > 1) {
		Magic(N/2);
	}
}