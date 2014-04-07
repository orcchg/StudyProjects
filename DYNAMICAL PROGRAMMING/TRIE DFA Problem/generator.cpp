#include <string>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

vector<string> array;

string generate(int n, int l) {
  if (n == 0) {
    return "";
  }
  for (int i = 0; i < l; ++i) {
    char ch = 'a' + i;
    array.push_back(generate(n - 1, l) + ch);
    return (generate(n - 1, l) + ch);
  }
}

int main() {
  copy(array.begin(), array.end(), ostream_iterator<string>(cout, "\n"));
  return 0;
}