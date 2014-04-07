#include <iostream>
#include <math.h>
//#include <conio.h>
using std::cin;
using std::cout;

int main()
{

	int N;
	double done;
	
	cin >> N;
	
	int* pA = new int[N];
	int* buf = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> pA[i];
		done = (sqrt(8 * (double)pA[i] - 7) - 1)/ 2;
		
		if ((done - (int)done) == 0) 
		{
			//cout << "1 ";
			buf[i] = 1;
		}
		else
		{
			//cout << "0 ";
			buf[i] = 0;
		}
	}
	
	for(int i = 0; i < N; ++i)
	{
		cout << buf[i] << " ";
	}
	
//	_getch();
	return 0;
}