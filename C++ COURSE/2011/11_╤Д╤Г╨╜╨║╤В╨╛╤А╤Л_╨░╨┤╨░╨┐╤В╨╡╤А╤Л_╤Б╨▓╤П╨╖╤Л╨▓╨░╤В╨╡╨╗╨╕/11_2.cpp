#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <iterator>

template <typename F1, typename F2>
class composer: public std::unary_function<typename F1::result_type, typename F2::argument_type> {
  F1 f1;
  F2 f2;
public:
  composer(F1 f1, F2 f2): f1(f1), f2(f2) {}
  typename F1::result_type operator () (typename F2::argument_type x) const {
    return f1(f2(x));
  }
};

template <typename F1, typename F2>
composer<F1,F2> compose(F1 f1, F2 f2) {
  return composer<F1, F2>(f1, f2);
}


int main() {
  std::string s[] = {"123", "45.6", "78e-1"};
  std::transform(s, s + sizeof(s)/sizeof(std::string), std::ostream_iterator<double>(std::cout, " "), compose(std::ptr_fun(atof), std::mem_fun_ref(&std::string::c_str)));
  std::cout << std::endl;
}

