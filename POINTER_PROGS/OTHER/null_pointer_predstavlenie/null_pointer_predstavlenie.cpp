#include <conio.h>
#include <stdio.h>

struct fudge 
{
	union 
	{
		int i;
		int* p;
	};
};

int main()
{
	struct fudge F;
	F.p = 0;
	int i = F.i;
	
	printf("P: %p\tI: %d",F.p,F.i);

	_getch();
	return 0;
}