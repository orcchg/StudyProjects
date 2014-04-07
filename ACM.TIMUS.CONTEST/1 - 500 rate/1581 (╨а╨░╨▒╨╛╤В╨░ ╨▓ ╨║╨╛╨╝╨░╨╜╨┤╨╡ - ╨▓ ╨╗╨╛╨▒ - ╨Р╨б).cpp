#include <iostream>
#include <conio.h>
using std::cin;
using std::cout;

int main()
{

	int N, count = 1;
	
	cin >> N;
	
	int* a = new int[N];
	int* b = new int[N];
	int* c = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> a[i];
	}
	
	int j = 0;
	c[0] = count;
	b[0] = a[0];
	
	for(int i = 1; i < N; ++i)
	{
		if (a[i] == a[i-1])
		{
			count++;
			b[j] = a[i];
			c[j] = count;
		}
		else
		{
			++j;
			b[j] = a[i];
			count = 1;
			c[j] = count;
		}
	}
	
	for(int i = 0; i <= j; ++i)
	{
		cout << c[i] << " " << b[i] << " ";
	}

//	_getch();
	return 0;
}