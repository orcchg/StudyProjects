#include <iostream>
#include <conio.h>
#include <math.h>
using std::cin;
using std::cout;

int main()
{

	int n, k, sum = 0;
	
	cin >> k >> n;
	
	int* a = new int[n];
	
	for(int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	
	for(int i = 0; i < n; ++i)
	{
		sum += a[i] - k;
		if (sum <= 0)
		{
			sum = 0;
		}
	}
	
	
	cout << sum;
	
//	_getch();
	return 0;
}