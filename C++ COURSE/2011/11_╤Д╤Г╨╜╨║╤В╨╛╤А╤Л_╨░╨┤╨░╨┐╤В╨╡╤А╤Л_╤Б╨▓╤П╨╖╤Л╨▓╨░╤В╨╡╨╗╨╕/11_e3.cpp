#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename F>
class binder_second {
private:
  F binary_function;
  typename F::second_argument_type value;

public:
  binder_second(F binary_function, const typename F::second_argument_type& argument) 
  : binary_function(binary_function) 
  , value(argument)
  {}

  typedef typename F::first_argument_type first_argument_type;
  typedef typename F::result_type result_type;

  result_type operator () (const first_argument_type& x) {
    return binary_function(x, value);
  }
};

template <typename F>
binder_second<F> binder_2nd(F binary_function, const typename F::second_argument_type& value) {
  return binder_second<F>(binary_function, value);
}

int main() {
  int a[] = {1, 2, 3, 4, 5, 6, 7};
  remove_copy_if(a, a + 7, ostream_iterator<int>(cout, " "), bind2nd(less<int>(), 5));
  cout << endl;
  remove_copy_if(a, a + 7, ostream_iterator<int>(cout, " "), binder_2nd(less<int>(), 5));
  cout << endl;
  //remove_copy_if(a, a + 7, ostream_iterator<int>(cout, " "), binder_second<binary_function<int, int, int> >(less<int>(), 5));
  return 0;
}
