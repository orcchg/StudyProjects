#include <iostream>
#include <conio.h>
#include <stdio.h>
using namespace std;

//------------------------------------
inline void Rec(int* pA, int N, int* pR)
{
	for(int i = 0; i < N; ++i)
	{
		pR[i] = pA[i];
	}
}

//------------------------------------


int main()
{
	int N, flag = 2, temp;
	__int64 s = 1;
	
	cin >> N;
	
	int* P = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> P[i];
	}
	
	int* R = new int[N];
	Rec(P, N, R);
	
while(flag != 1)
{		
	int j = 0;
	for(int i = 1; i <= N; ++i)
	{
		if (R[i-1] != i)
		{
			j = 0;
			break;
		}
		j = N;
	}
	
	if (j == N)
	{
		flag = 1;
		continue;
	}
	
	s++;
	
	for(int i = 0; i < N; ++i)
	{
		R[i] = P[R[i]-1];
//		cout << R[i] << " ";
	}	
//	cout << endl;
}	

	delete [] R;
	delete [] P;

	cout << s;
//	_getch();
	return 0;
}