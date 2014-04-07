#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int power(int a, int n) {
	int b = 1;
	
	while (n != 0) {
		if (n % 2 == 0) {
			a *= a;
			n /= 2;
		} else {
			--n;
			b *= a;
		}
	}
	return b;
}

int main()
{
	int a, n;
	cin >> a >> n;
	cout << power(a, n);
	
	cin.ignore();
	return 0;
}