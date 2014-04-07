#include <iostream>
#include <conio.h>
using namespace std;

/*inline long long max_el(long long* pA, long long n, long long& imax)
{
	long long max = pA[0];
	imax = 1;
	
	for(long long i = 1; i < n; ++i)
	{
		if (pA[i] > max)
		{
			max = pA[i];
			imax = i;
		}
	}
	
	return max;
}*/

int main()
{
	long long t;
	
	cin >> t;
	
	long long MAX, iMAX = 0;
	
	long long* pN = new long long[t];
	
	for(long long i = 0; i < t; ++i)
	{
		cin >> pN[i];
	}

	for(long long i = 0; i < t; ++i)
	{
//		long long imax = 1;
//		long long max = 1;
		
		long long* D = new long long[pN[i]+1]; // NUMBER OF ANY DIVIDOR OF CURRENT j
		D[0] = 1;
		MAX = 1;
		iMAX = D[0];
		
		for(long long j = 1; j <= pN[i]; ++j)
		{
			D[j] = 1;
			
			for(long long k = 1; k <= j/2; ++k) 
			{ 
				if (j % k == 0) 
				{
					D[j] += 1;
				}
			}
			
			if (iMAX < D[j])
			{
				iMAX = D[j];
				MAX = j;
			}
		}
//		max = max_el(D, pN[i]+1, imax);
		cout << MAX << " " << iMAX << endl;
		
		delete [] D;
	}
	
//	_getch();
	return 0;
}