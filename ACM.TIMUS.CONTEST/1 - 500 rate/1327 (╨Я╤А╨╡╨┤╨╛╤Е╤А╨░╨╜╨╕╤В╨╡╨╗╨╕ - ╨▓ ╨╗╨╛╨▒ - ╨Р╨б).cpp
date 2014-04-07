#include <iostream>
using namespace std;

int main()
{
	int A, B, N = 0;
	
	cin >> A;
	cin >> B;
	
	N = (B + 1)/2 - A/2;
	
	cout << N;

	return 0;
}