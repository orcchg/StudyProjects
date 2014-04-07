#include <conio.h>
#include <cstdio>

void Iter(int);
void Ket(int);
void Ord(int);
void Gen(int);
void Bra(int);

int main(){

	int n,c,a=0;
	
	printf("Enter n: ");
	scanf("%d",&n);
	printf("\nKet: ");
	
	Ket(n);
	printf("\nOrd: ");
	Ord(n);
	printf("\nGen: ");
	Gen(n);
	printf("\nBra: ");
	Bra(n);
	printf("\n");
	
	_getch();
}

void Iter(int n){

	int i;
	int c=40,d=41;
	
	if(n % 2 == 0){
		for(i=1; i<=n/2; i++)
			printf("%c",c);
		for(i=n/2+1; i<=n; i++)
			printf("%c",d);
	}
}

void Ket(int n){
	
	int c=40,d=41;
	if(n > 0 && n % 2 == 0){
		printf("%c",c);
		Ket(n-2);
		printf("%c",d);
	}
}

void Ord(int n){

	int c=40,d=41;
	if(n > 0 && n % 2 == 0){
		printf("%c",c);
		printf("%c",d);
		Ord(n-2);
	}
}

void Gen(int n){

	int c=40,d=41;
	if(n > 0 && n % 2 == 0){
		printf("%c",c);
		Ord(n-2);
		printf("%c",d);
	}
}

void Bra(int n){

	int c=40,d=41;
	if(n > 0 && n % 2 == 0){
		for(int i=0; i< n/2-2; i++)
			printf("%c",c);
		Ord(n-4);
		for(int i=0; i< n/2-2; i++)
			printf("%c",d);
	}
}