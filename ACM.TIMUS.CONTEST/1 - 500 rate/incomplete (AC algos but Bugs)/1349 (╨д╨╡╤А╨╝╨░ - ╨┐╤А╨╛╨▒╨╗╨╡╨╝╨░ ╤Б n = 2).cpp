#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

int main()
{
	int n, a = 1, b = 1, c = 1;
	bool status = false;
	
	cin >> n;
	
	for(int i = 1; i <= 100; ++i)
	{
		a = i;
	//	cout << "a: " << a << endl;
		for(int j = i + 1; j <= 100; ++j)
		{
			b = j;
		//	cout << "b: " << b << endl;
			for(int k = j + 1; k <= 100; ++k)
			{
				c = k;
			//	cout << "c: " << c << endl;
				if ((pow((double)a,n) + pow((double)b,n)) == pow((double)c,n))
				{
					status = true;
					goto LABEL;
			//		_getch();
				}
			}
		}
	}

LABEL: if (status)
		{
			cout << a << " " << b << " " << c;
		}
		else
		{
			cout << -1;
		}
	
	_getch();
	return 0;
}