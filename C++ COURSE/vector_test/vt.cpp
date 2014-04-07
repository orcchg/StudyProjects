#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
using std::copy;
using std::cout;
using std::ostream_iterator;
using std::ostream;
using std::vector;

class C {
public:
  C(int a) : a(a) {}
  int show() const {
    return a;
  }
  friend ostream& operator << (ostream& out, const C& rhs) {
    out << rhs.a;
	return out;
  }
private:
  int a;
};
  

int main() {
  vector<int> v_i(10, 5);
  //vector<C> v_c(10);
  vector<C> v_d(10, C(15));
  copy(v_i.begin(), v_i.end(), ostream_iterator<int>(cout, " "));
  cout << *v_d.begin();
  copy(v_d.begin(), v_d.end(), ostream_iterator<C>(cout, " "));
  return 0;
}