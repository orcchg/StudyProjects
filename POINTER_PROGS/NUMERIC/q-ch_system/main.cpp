#include <conio.h>
#include <stdio.h>
#include <cstring>
#include "inverse.h"

int main() {

	long N,k;
	int Q;
	char* s = new char[MAXLEN];
	char* v = new char[MAXLEN];
	char* b;
	
	printf("Enter N and 0 < Q < 10: ");
	scanf("%ld %d",&N,&Q);
	k = N;
	printf("\n");
	
	while(k){
		sprintf(s,"%ld", k % Q);
		v = strcat(v,s);
		k /= Q;
	}
	
	b = inverse(v,strlen(v));
		printf("\n%s",++b);
	
	delete [] s;
	delete [] v;
	delete b;
	_getch();
}