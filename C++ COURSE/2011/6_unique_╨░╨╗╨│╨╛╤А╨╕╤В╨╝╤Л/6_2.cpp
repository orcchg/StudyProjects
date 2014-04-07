#include <algorithm>
#include <iterator>
#include <vector>
#include <ostream>
#include <iostream>
using namespace std;

template <typename Iter>
Iter unique(Iter first, Iter last) {
  while (first + 1 != end) {
    if (*(first + 1) == *first)
  }
}

int main() {
  vector<int> v;
  v.push_back(2);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(4);
  v.push_back(4);
  v.push_back(3);
  v.push_back(5);
  v.push_back(5);
  v.push_back(6);
  unique(v.begin(), v.end());
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  return 0;
}
