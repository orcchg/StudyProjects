#include <iostream>
#include <ostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

template <typename T>
void printBinary(T number) {
  vector<int> binary(sizeof(T) * 8, 0);
  int power = 0;
  while (number) {
    binary[power] = number % 2;
    number /= 2;
    ++power;
  }
  reverse(binary.begin(), binary.end());
  copy(binary.begin(), binary.end(), ostream_iterator<int>(cout, ""));
  cout << endl;
}

int main() {
  char ch = 'a';
  int i = 12345;
  long long l = 4000000009;
  printBinary(ch);
  printBinary(i);
  printBinary(l);
  return 0;
}
