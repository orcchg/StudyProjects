#include <algorithm>
#include <iterator>
#include <iostream>
#include <ostream>
#include <vector>
#include <list>
using std::cout;
using std::endl;
using std::sort;
using std::vector;
using std::random_access_iterator_tag;
using std::copy;
using std::ostream_iterator;
using std::list;
using std::iterator_traits;
using std::back_inserter;

template <typename Iter, typename Tag>
void bd_sort_inner(Iter begin, Iter end, Tag) {
  vector<typename iterator_traits<Iter>::value_type> v;
  copy(begin, end, back_inserter(v));
  sort(v.begin(), v.end());
  copy(v.begin(), v.end(), begin);
}

template <typename Iter>
void bd_sort_inner(
    Iter begin, 
    Iter end, 
    random_access_iterator_tag
    ) {
  sort(begin, end);
}

template <typename Iter>
void bd_sort(Iter begin, Iter end) {
  bd_sort_inner(begin, end, typename iterator_traits<Iter>::iterator_category());
}

int main() {
  vector<int> v = {2, 7, 1, 9, -1, -14, 0, 18, 2, 3, 1, 6};
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  list<int> l = {5, 2, 1, 7, 5, 3, 9, 0, 4, 14, 3, 5};
  copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  bd_sort(v.begin(), v.end());
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  bd_sort(l.begin(), l.end());
  copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  return 0;
}
  