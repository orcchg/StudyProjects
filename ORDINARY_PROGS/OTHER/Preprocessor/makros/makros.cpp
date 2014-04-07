#include <conio.h>
#include <stdio.h>

#define PRINT(A,fmt) printf(#A"=%"#fmt"\n",A);

int main(){

	PRINT(3.1415,f);
	PRINT(2.7182,e);
	PRINT(2.5,d);
	_getch();
}