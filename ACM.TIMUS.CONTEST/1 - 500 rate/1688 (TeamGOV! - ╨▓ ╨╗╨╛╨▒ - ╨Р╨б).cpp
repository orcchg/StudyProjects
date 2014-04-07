#include <iostream>
#include <conio.h>
#include <stdio.h>
using namespace std;

int main()
{
	__int64 n, sum = 0;
	int m, x = 1;
	
	cin >> n >> m;
	
	int* A = new int[m];
	
	for(int i = 0; i < m; ++i)
	{
		cin >> A[i];
	}
	
	for(int i = 0; i < m; ++i)
	{
		sum += A[i];
		if (sum > 3*n)
		{
			cout << "Free after " << x << " times.";
			break;
		}
		else
		{
			++x;
		}
	}
	
	if (x - 1 == m)
	{
		cout << "Team.GOV!";
	}

//	_getch();
	return 0;
}