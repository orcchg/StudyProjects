#include <iostream>
using std::cout;

void foo(int a) {
  ++a;
	cout << a << "few\n";
}
//void foo(int&);
void foo(int* a) {
  ++*a;
}
//void foo(int) const;

#include <cmath>

void foo(double (*F)(double), double a) {
  F(a);
}

void foo(const long long& a) {
  cout << a << "\n";
  cout << sin(a) << "sin\n";;
}

int main() {

		foo(5);
		int a = 6;
		foo(a);
		foo(&a);
		foo(sin, a);
		foo(32134243432532);
		long long b = 42345235525;
		foo(b);
		int c = 3421423423523;
		foo(c);
		foo(static_cast<long long>(c));
		return 0;
}