#include <conio.h>
#include <stdio.h>

#define CONST 3.1415

int main(){

	printf("%f\n",CONST);
	
#undef CONST
#define CONST 2.7182

	printf("%f\n",CONST);
	_getch();
}