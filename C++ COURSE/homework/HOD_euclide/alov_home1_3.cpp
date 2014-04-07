#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//-----------------------------------------------------------------------------
int gcdex(int a, int b, int& rx, int& ry) {
	int p = 1, q = 0; 
	int r = 0, s = 1;
	int gcd = 0;
	
	while (a > 0 && b > 0) {
		if (a >= b) {
			a -= b;
			p -= r;
			q -= s;
		} else {
			b -= a;
			r -= p;
			s -= q;
		}
	}
	
	if (a == 0) {
		gcd = b;
		rx = r;
		ry = s;
	} else if (b == 0) {
		gcd = a;
		rx = p;
		ry = q;
	}
	
	return gcd;
}

//-----------------------------------------------------------------------------
int reversal_element(int a, int n) {
	int x, y;
	int g = gcdex (a, n, x, y);
	if (g != 1) {
		cout << "Reversal element not exists!\n";
		return 0;
	}
	return (x % n + n) % n;;
}

//-----------------------------------------------------------------------------
int main() {
	int a, b, n;
	cout << "Enter a b n:\t";
	cin >> a >> b >> n;
	
	int x = 0, y = 0;
	int gcd = gcdex(a, b, x, y);
	cout << "(a, b): " << gcd << "\nx: " << x << "\ny: " << y << endl;

	int rev = 0;
	if (rev = reversal_element(a, n)) {
		cout << "rev: " << rev << endl;
	}
	return 0;
}