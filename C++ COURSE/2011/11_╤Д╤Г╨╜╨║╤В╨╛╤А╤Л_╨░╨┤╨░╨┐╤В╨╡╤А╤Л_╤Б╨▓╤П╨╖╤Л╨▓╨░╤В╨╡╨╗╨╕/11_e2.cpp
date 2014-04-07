#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>

using std::transform;
using std::cout;
using std::ostream_iterator;
using std::vector;
using std::endl;
using std::plus;
using std::divides;

int main() {
  int a[] = {1, 2, 3, 4, 5, 6, 7};
  int b[] = {7, 6, 5, 4, 3, 2, 1};
  double c[] = {7, 6, 5, 4, 3, 2, 1};
  transform(a, a + 7, b, ostream_iterator<int>(cout, " "), plus<int>());
  cout << endl;
  transform(a, a + 7, c, ostream_iterator<double>(cout, " "), divides<double>());
  return 0;
}