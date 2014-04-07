#include <iostream>
#include <stdexcept>
#include <new>
#include <cstdlib>
using namespace std;

void* operator new(size_t sz, double b) {
  cout << "operator new with sz: " << sz << "\n";
  void* ptr = malloc(sz);
  if (!ptr) {
    throw bad_alloc();
  }
  return ptr;
}

void operator delete(void* ptr, double b) {
  if (!ptr) {
    return;
  }
  cout << "operator delete\n";
  free(ptr);
}

class C {
public:
  explicit C(int a) {
    if (a == -1) {
      throw -1;
    } else {
      this->a = a;
    }
  }

private:
  int a;
};

int main() {
  C* c = new (5.21) C(5);
  try {
    C* d = new (7.63) C(-1);
    delete d;  // custom delete(double)
  } catch(...) {}
  delete c;
  return 0;
}
