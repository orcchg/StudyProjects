#include <conio.h>
#include <cstdio>
#include "fast.h"
#include "C_n_k.h"

int main(){

	int c,a;
	long N=0,i,j=0,Cnk,counter=0;
	
	printf("Enter N: ");
	scanf("%ld",&N);
	printf("\n");
	
	char* s = new char[N];
	
	Cnk = C(2*N,N);
	while(j<Cnk){
	a=0;
	i=0;
	j++;
	s = Generate_Rand(N); //RANDOM SEQUENCE OF PARENTHESES
	
	while(i<N){
	c = s[i++];
		if(c == '(')
			a++;
		else if (c == ')')
				if( --a < 0)
					break;
	} 
	
	if( a == 0){
		printf("%s %ld\n",s,++counter);
		}
	}
		
	_getch();	
	return 0;
}