#include<stdio.h>

int main()
{

	__int64 x,y=0,z=0,q,p,r;

	scanf("%I64d",&r);

	x = r;
	q = r*r;

	do{

		p = q - y * y;
		
		while( x * x >= p && x >= 0 )
		{
			x--;
		}
		
		z += (x + 1);
		y++;
		
	}while(y < r);

	z *= 4;
	printf("%I64d\n",z);

	return 0;
}