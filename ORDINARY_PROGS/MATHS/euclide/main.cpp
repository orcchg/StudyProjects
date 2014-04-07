#include <conio.h>
#include <stdio.h>
#include "euclide.h"

int main() 
{
	long a,b,d,x=0,y=0,z;
	int flag;
	
	printf("Enter a and b: ");
	flag = scanf("%ld %ld",&a,&b);
	printf("%d\n",flag);
	fflush(stdin);
	
	d = HOD(a,b,x,y);
	z = HOK(a,b);
	
	printf("\n(a,b) = %ld\nx = %ld\ny = %ld\nz = %ld\n",d,x,y,z);
	_getch();
}