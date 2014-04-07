#include <iostream>
#include <vector>
using std::vector;
using std::cout;

#define lam int

class C {
  public:
    C(int a):d(a) {}
	 int d;
};

vector<int> y(2, 4);
C u(5);
int z(int);
//vector<int> y(int, int);

int main() {
	for (int i = 0; i < y.size(); ++i) {
	  cout << y[i] << ' ';
	}
	C i(int);
	cout << u.d << i.d;
	return 0;
}