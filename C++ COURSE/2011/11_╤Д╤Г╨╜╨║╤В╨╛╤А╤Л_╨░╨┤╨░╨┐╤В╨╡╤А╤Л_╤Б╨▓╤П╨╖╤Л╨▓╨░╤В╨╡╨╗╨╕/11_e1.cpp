#include <iostream>
using std::cout;

class C {
public:
  explicit C(int field, int pf = 0) : field(field), private_field(pf) {}
  void f() const {
    cout << "F function\n";
  }

  void g(int a) const {
    cout << "G(" << a << ") function\n";
  }

  double get() const {
    return private_field;
  }

  int field;

private:
  double private_field;
};

int main() {
  int C::*ptr_to_field = &C::field;
  void (C::*ptr_to_f) () const = &C::f;
  void (C::*ptr_to_g) (int) const = &C::g;
  C c(5, 7);
  C d(10);
  cout << c.*ptr_to_field << " " << d.*ptr_to_field << "\n";
  C* ptr = new C(9, 8);
  (ptr->*ptr_to_f)();
  (ptr->*ptr_to_g)(17);
  cout << ptr->*ptr_to_field << "\n";
  return 0;
}
