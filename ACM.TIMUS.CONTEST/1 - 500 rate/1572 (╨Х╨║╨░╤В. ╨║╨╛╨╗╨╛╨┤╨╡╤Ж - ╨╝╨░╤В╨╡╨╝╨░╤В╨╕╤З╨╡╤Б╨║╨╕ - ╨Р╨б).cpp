#include <stdio.h>
#include <math.h>
#include <conio.h>

//---------------------------
struct plot
{
	int type;
	int size;
};
//---------------------------

int main()
{
	plot Ekz;
	int N, M = 0;
	
	scanf("%d%d", &Ekz.type, &Ekz.size);
	scanf("%d", &N);
	
	plot* Arr = new plot[N];
	
	for(int i = 0; i < N; ++i)
	{
		scanf("%d%d", &Arr[i].type, &Arr[i].size);
	}
	
	double Ekz_max = 0;
	switch(Ekz.type)
	{
		case 1:
			Ekz_max = 2*Ekz.size;
			break;
		case 2:
			Ekz_max = Ekz.size*sqrt(2.0);
			break;
		case 3:
			Ekz_max = Ekz.size;
			break;
		default:
			break;
	}
	
	
	for(int i = 0; i < N; ++i)
	{
		double min = 0;
		
		switch(Arr[i].type)
		{
			case 1:
				min = 2.0*Arr[i].size;
				break;
			case 2:
				min = Arr[i].size;
				break;
			case 3:
				min = Arr[i].size*0.5*sqrt(3.0);
				break;
			default:
				break;
		}
		
		if (min <= Ekz_max)
		{
			++M;
		}
	}
	
	printf("%d\n", M);
	
//	_getch();
	return 0;
}