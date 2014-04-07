#include <iostream>
using namespace std;

int main() {
  double total, limit, bank;
  cin >> total >> limit >> bank;
  __int64 years = 0;
  if (total <= limit) {
    cout << 0;
    return 0;
  }
	while (total > limit) {
	  ++years;
	  total -= total * (bank / 100);
  }
	cout << years;
	return 0;
}