#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	
	long long N, M, num;
	
	cin >> N >> M;
	
	if (N == 1)
	{
		num = 0;
		cout << num;
		return 0;
	}
	
	if (M == 1)
	{
		num = 1;
		cout << num;
		return 0;
	}
	
	num = ( N > M ) ? (M*2 - 1) : (N*2 - 2);
	
	cout << num;
	
	return 0;
}