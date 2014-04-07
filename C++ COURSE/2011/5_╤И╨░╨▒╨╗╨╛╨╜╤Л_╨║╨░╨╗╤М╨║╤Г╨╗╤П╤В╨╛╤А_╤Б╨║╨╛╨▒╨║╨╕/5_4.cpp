#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

template <typename In, typename Out, typename F>
Out copy_if(In begin, In end, Out dest, F predicate) {
  while (begin != end) {
    if (predicate(*begin)) {
      *dest++ = *begin;
    }
    ++begin;
  }
  return dest;
}

bool isPrime(int number) {
  int divider = 2;
  while (divider < number) {
    if ((number % divider) != 0) {
      ++divider;
    } else {
      return false;
    }
  }
  return true;
}

int main() {
  vector<int> v;
  v.push_back(5);
  v.push_back(9);
  v.push_back(12);
  v.push_back(17);
  v.push_back(35);
  list<int> l(5);
  copy_if(v.begin(), v.end(), l.begin(), isPrime);
  cout << l.size() << endl;
  copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
  return 0;
}
  