#include <iostream>
#include <string>
#include <iterator>
using namespace std;

bool is_palindrome(const string& str) {
  string::const_iterator it;
  string::const_reverse_iterator rit;
  for (it = str.begin(), rit = str.rbegin();
       it != str.end(), rit != str.rend();
       ++it, ++rit
      ) {
    if (*it != *rit) {
      return false;
    }
  }
  return true;
}

int main() {
  string str;
  while (getline(cin, str)) {
	  if (is_palindrome(str)) {
      cout << "   YES\n";
    } else {
      cout << "   NO\n";
    }
	}
  return 0;
}
