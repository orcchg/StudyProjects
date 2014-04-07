#include <iostream>
#include <conio.h>
using std::cout;
using std::cin;

struct place
{
	char vert;
	int hor;
};

int main()
{
	int N;
	
	cin >> N;
	
	place* P = new place[N];
	int* out = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> P[i].vert;
		cin >> P[i].hor;
		
		if ((P[i].vert > 'b' && P[i].vert < 'g') && (P[i].hor >= 3 && P[i].hor <= 6))
		{
			out[i] = 8;
		}
			
		if ((P[i].vert > 'b' && P[i].vert < 'g') && (P[i].hor == 2 || P[i].hor == 7))
		{
			out[i] = 6;
		}
		
		if ((P[i].vert > 'b' && P[i].vert < 'g') && (P[i].hor == 1 || P[i].hor == 8))
		{
			out[i] = 4;
		}

		if ((P[i].hor >= 3 && P[i].hor <= 6) && (P[i].vert == 'b' || P[i].vert == 'g'))
		{
			out[i] = 6;
		}
		
		if ((P[i].vert == 'b' || P[i].vert == 'g') && (P[i].hor == 2 || P[i].hor == 7))
		{
			out[i] = 4;
		}
		
		if ((P[i].hor >= 3 && P[i].hor <= 6) && (P[i].vert == 'a' || P[i].vert == 'h'))
		{
			out[i] = 4;
		}

		if ((P[i].vert == 'b' || P[i].vert == 'g') && (P[i].hor == 1 || P[i].hor == 8))
		{
			out[i] = 3;
		}
		
		if ((P[i].vert == 'a' || P[i].vert == 'h') && (P[i].hor == 2 || P[i].hor == 7))
		{
			out[i] = 3;
		}
		
		if ((P[i].vert == 'a' || P[i].vert == 'h') && (P[i].hor == 1 || P[i].hor == 8))
		{
			out[i] = 2;
		}
		
	}
	
	for(int i = 0; i < N; ++i)
	{
		cout << out[i] << std::endl;
	}

//	_getch();
	return 0;
}