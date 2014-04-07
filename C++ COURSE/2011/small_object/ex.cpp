#include <iostream>
#include <ostream>
using namespace std;
using std::cout;
using std::endl;

template <typename T = int>
class C {
public:
    C(int n) : data(new T(n)) {}
    C& operator = (const C& rhs) {
        delete data;
        data = new T(*rhs.data);
        return *this;
   }

   friend ostream& operator << (ostream& out, const C& rhs) {
     out << *rhs.data;
	 return out;
    }
private:
    T* data;
};


int main() {
  C<> c(10);
  C<> d(5);
  cout << d << " " << c << endl;
  d = c;
  cout << d << endl;
  c = c;
  cout << c;
  return 0;
}
