#include <iostream>
#include <string>
using namespace std;

void input(string* str) {
  cin >> *str;
}

int main() {
  string str;
  input(&str);
  string numeric = "0123456789";
  string::size_type pos = 0;
  while (pos < str.length()) {
    cout << (pos = str.find_first_of(numeric, pos)) << " ";
    ++pos;
  }
  cout << endl;
  pos = 0;
  while (pos < string::npos) {
    cout << (pos = str.find_first_not_of(numeric, pos)) << " ";
    ++pos;
  }
  return 0;
}
