#include <functional>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename F1, typename F2>
class composer : public unary_function<typename F1::result_type, typename F2::argument_type> {
private:
  F1 first_function;
  F2 second_function;

public:
  composer(F1 f_1, F2 f_2) : first_function(f_1), second_function(f_2) {}
  typename F1::result_type operator () (typename F2::argument_type& arg) {
    return first_function(second_function(arg));
  }
};

template <typename F1, typename F2>
composer<F1, F2> compose(F1 first, F2 second) {
  return composer<F1, F2>(first, second);
}

int main() {
  string a[] = {"3.14", "2.71", "0.51", "1.14", "1.21", "7.62", "0.09", "7.8e-3"};
  transform(a, a + 8, ostream_iterator<double>(cout, " "), compose(ptr_fun(atof), mem_fun_ref(&string::c_str)));
  return 0;
}
