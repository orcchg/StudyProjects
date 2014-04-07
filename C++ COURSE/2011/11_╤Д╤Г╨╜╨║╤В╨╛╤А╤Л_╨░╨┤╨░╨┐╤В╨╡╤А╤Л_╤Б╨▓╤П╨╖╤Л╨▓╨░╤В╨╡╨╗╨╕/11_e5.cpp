#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
using namespace std;

bool f(int a, int b) {
  return a > b;
}

class C {
private:
  int a;

public:
  C(int a) : a(a) {}
  bool f(const C& c) const {
    return a > c.a;
  }
};

int main() {
  int a[] = {1, 2, 3, 4, 5, 6, 7};
  remove_copy_if(a, a + 7, ostream_iterator<int>(cout, " "), bind2nd(ptr_fun(f), 5));
  C b[] = {C(1), C(2), C(3), C(4), C(5), C(6), C(7)};
  remove_copy_if(b, b + 7, ostream_iterator<int>(cout, " "), bind2nd(mem_fun_ref(&C::f), C(5)));
  return 0;
}
