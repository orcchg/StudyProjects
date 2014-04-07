#include <iostream>
using namespace std;

int sum(int k, ...) {
  int summa = 0;
  int* ptr = &k;
  ++ptr;
  while (k--) {
    summa += *ptr++;
  }
  return summa;
}

int main() {
  cout << sum(5, 1, 2, 3, 4, 5);
  return 0;
}
