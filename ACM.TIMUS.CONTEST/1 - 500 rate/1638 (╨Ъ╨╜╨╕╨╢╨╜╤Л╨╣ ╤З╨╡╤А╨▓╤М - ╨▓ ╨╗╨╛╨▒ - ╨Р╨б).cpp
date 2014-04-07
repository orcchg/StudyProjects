#include <iostream>
using namespace std;

int main()
{
	int N, M, F, L;
	int W = 0;
	
	cin >> N >> M >> F >> L;
	
	if (F == L)
	{
		W = N;
	}
	else if (F < L)
	{
		W = 2*M + (L - F - 1)*(N + 2*M);
	}
	else if (F > L)
	{
		W = N + (F - L)*(N + 2*M);
	}
	
	cout << W;
			
	return 0;
}