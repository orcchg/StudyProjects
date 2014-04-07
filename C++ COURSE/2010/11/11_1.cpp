#include <algorithm>
#include <string>
#include <iostream>
#include <iterator>
using std::copy;
using std::string;
using std::cout;
using std::endl;

string strip(const string& str) {
  string result = "";
  if (str.end() != str.begin() && *(str.end() - 1) == ' ') {
    copy(str.begin(), str.end() - 1, std::back_inserter(result));
  } else {
    result = str;
  }
  return result;
}

int main() {
  string str = "Hello, my name is Max. Here is a space character at the end... ";
  str = strip(str);
  cout << str;
  return 0;
}
