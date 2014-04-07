#include <conio.h>
#include <cstdio>

int main(int argc, char* argv[]){

	while(--argc > 0)
		printf("%s%c",*++argv, (argc > 1)? ' ':'\n');

	_getch();
}