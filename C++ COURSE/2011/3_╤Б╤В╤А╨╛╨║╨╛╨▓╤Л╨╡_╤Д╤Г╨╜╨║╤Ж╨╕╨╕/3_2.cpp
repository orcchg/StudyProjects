#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int strlen(const char* str) {
  int length = 0;
  while (*str++ != '\0') {
    ++length;
  }
  return length;
}

int atoi(const char* str) {
  int power = strlen(str) - 1;
  int result = 0;
  while (*str != '\0') {
    result += (*str - '0') * pow(10, power);
    --power;
    ++str;
  }
  return result;
}

int main() {
  string str;
  cin >> str;
  cout << atoi(str.c_str());
  return 0;
}
