#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::vector;
using std::greater;
using std::bind2nd;
using std::cout;
using std::ostream_iterator;

template <typename InIter, typename OutIter, typename F>
OutIter copy_if_alov(InIter begin, InIter end, OutIter dest, F predicate) {
  while (begin != end) {
    if (predicate(*begin)) {
      *dest++ = *begin;
    }
    ++begin;
  }
  return dest;
}

int main() {
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  copy_if_alov(v.begin(), v.end(), ostream_iterator<int>(cout, " "), bind2nd(greater<int>(), 5));
  return 0;
}
