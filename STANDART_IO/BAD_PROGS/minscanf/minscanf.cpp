#include <conio.H>
#include "minscanf.h"

int main(){

	int k=0;
	int i;
	double d;
	char* s;
	
	k = minscanf("%d %f %s",&i,&d,s);
	//k = minscanf("%d %f",&i,&d);
	printf("%d\n",k);
	
	_getch();
}