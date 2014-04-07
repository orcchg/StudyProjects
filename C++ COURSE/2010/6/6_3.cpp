#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using std::vector;
using std::copy;
using std::ostream_iterator;
using std::cout;
using std::sort;

template <typename Iter>
Iter unique_alov(Iter begin, Iter end) {
  if (begin == end) {
    return;
  }
  sort(begin, end);
  Iter start;
  *start++ = *begin;
  ++begin;
  while (begin != end) {
    if (*begin != *(begin - 1)) {
      *start++ = *begin;
    }
    ++begin;
  }
  return start;
}

int main() {
  vector<int> v = {1, 2, 1, 1, 4, 5, 5, 5, 7, 3, 3, 7, 7, 8, 9, 9, 0};
  unique_alov(v.begin(), v.end());
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  return 0;
}
