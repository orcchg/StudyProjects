#include <iostream>
#include <conio.h>
#include <iomanip>
#include <math.h>
using namespace std;


double Array[128*1024];

int main()
{
	double x = 0;
	int k = 0;
	
	while(cin >> x)
	{
		Array[k++] = sqrt(x);
	}
	
	for(int i = k - 1; i >= 0; --i)
	{
		cout << fixed << setprecision(4) << Array[i] << endl;
	}
	
//	_getch();
	return 0;
}