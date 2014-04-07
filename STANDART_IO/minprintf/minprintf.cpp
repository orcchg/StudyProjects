#include <conio.h>
#include "minprintf.h"

int main(){

	int k;
	char s[] = {'T','H','E','\0'};
	
	k = minprintf("%s %d %f\n",s,15,0.005);
	minprintf("%d\n",k);
	
	_getch();
}