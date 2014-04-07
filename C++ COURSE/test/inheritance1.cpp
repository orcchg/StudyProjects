#include <iostream>
using namespace std;

class Base {
private:
  int x;

public:
  virtual void f1() = 0;
  virtual void f1(int) { cout << "Base f1 int\n"; }
  virtual void f2() { cout << "Base f2\n"; }
  void f3() { cout << "Base f3\n"; }
  void f3(int) { cout << "Base f3 int\n"; }
};

class Derived : public Base {
public:
  using Base::f1;
  using Base::f3;
  virtual void f1() { cout << "Derived f1\n"; }
  void f3() { cout << "Derived f3\n"; }
  void f4() { cout << "Derived f4\n"; }
};

int main() {
  Derived d;
  int x;
  d.f1();
  d.f1(x);
  d.f2();
  d.f3();
  d.f3(x);
  d.f4();
  return 0;
}
