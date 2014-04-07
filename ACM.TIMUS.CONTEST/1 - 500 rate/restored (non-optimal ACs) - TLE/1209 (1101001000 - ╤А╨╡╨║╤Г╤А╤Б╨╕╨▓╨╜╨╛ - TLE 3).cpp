#pragma comment(linker, "/STACK:16777216")

#include <iostream>
//#include <conio.h>
#include <limits.h>
using std::cin;
using std::cout;

int POS[100000];
int ind = 0;

int posit(int k)
{
	int pos = 1;
	
	if (k == 1) return 1;
	else 
	{
		pos = ((k - 1) + posit(k - 1));
		POS[ind++] = pos;
		return pos;
	}
}

int main()
{

	int N, one;
	
	cin >> N;
	
	int* pA = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> pA[i];
	}
	
	one = posit(100);
	
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < 100000; ++j)
		{
			if (pA[i] == POS[j])
			{
				cout << 1 << " ";
				break;
			}
			
			if (j == 100000 - 1)
			{
				cout << 0 << " ";
				break;
			}
		}
		
	}
	
//	_getch();
	
	return 0;
}