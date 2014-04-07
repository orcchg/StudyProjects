#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>

template <typename T1, typename T2>
class logical_xor: public std::binary_function<T1, T2, bool> {
public:
  bool operator () (const T1& a, const T2& b) const {
    return a ^ b;
  }
};


int main() {
  int a[] = {1,2,3,4};
  std::transform(a, a+4, std::ostream_iterator<bool>(std::cout, " "), std::bind2nd(logical_xor<int, int>(), 2)); 
  std::cout << std::endl;
}

